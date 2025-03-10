/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkBitmapCache.h"
#include "SkImage_Gpu.h"
#include "GrCaps.h"
#include "GrContext.h"
#include "GrDrawContext.h"
#include "GrTextureMaker.h"
#include "effects/GrYUVtoRGBEffect.h"
#include "SkCanvas.h"
#include "SkGpuDevice.h"
#include "SkGr.h"
#include "SkPixelRef.h"

SkImage_Gpu::SkImage_Gpu(int w, int h, uint32_t uniqueID, SkAlphaType at, GrTexture* tex,
                         SkSurface::Budgeted budgeted)
    : INHERITED(w, h, uniqueID)
    , fTexture(SkRef(tex))
    , fAlphaType(at)
    , fBudgeted(budgeted)
    , fAddedRasterVersionToCache(false)
    {}

SkImage_Gpu::~SkImage_Gpu() {
    if (fAddedRasterVersionToCache.load()) {
        SkNotifyBitmapGenIDIsStale(this->uniqueID());
    }
}

extern void SkTextureImageApplyBudgetedDecision(SkImage* image) {
    if (as_IB(image)->getTexture()) {
        ((SkImage_Gpu*)image)->applyBudgetDecision();
    }
}

static SkImageInfo make_info(int w, int h, bool isOpaque) {
    return SkImageInfo::MakeN32(w, h, isOpaque ? kOpaque_SkAlphaType : kPremul_SkAlphaType);
}

bool SkImage_Gpu::getROPixels(SkBitmap* dst) const {
    if (SkBitmapCache::Find(this->uniqueID(), dst)) {
        SkASSERT(dst->getGenerationID() == this->uniqueID());
        SkASSERT(dst->isImmutable());
        SkASSERT(dst->getPixels());
        return true;
    }

    if (!dst->tryAllocPixels(make_info(this->width(), this->height(), this->isOpaque()))) {
        return false;
    }
    if (!fTexture->readPixels(0, 0, dst->width(), dst->height(), kSkia8888_GrPixelConfig,
                              dst->getPixels(), dst->rowBytes())) {
        return false;
    }

    dst->pixelRef()->setImmutableWithID(this->uniqueID());
    SkBitmapCache::Add(this->uniqueID(), *dst);
    fAddedRasterVersionToCache.store(true);
    return true;
}

static void make_raw_texture_stretched_key(uint32_t imageID, const SkGrStretch& stretch,
                                           GrUniqueKey* stretchedKey) {
    SkASSERT(SkGrStretch::kNone_Type != stretch.fType);

    uint32_t width = SkToU16(stretch.fWidth);
    uint32_t height = SkToU16(stretch.fHeight);

    static const GrUniqueKey::Domain kDomain = GrUniqueKey::GenerateDomain();
    GrUniqueKey::Builder builder(stretchedKey, kDomain, 3);
    builder[0] = imageID;
    builder[1] = stretch.fType;
    builder[2] = width | (height << 16);
    builder.finish();
}

class Texture_GrTextureMaker : public GrTextureMaker {
public:
    Texture_GrTextureMaker(const SkImage* image, GrTexture* unstretched)
        : INHERITED(image->width(), image->height())
        , fImage(image)
        , fUnstretched(unstretched)
    {}

protected:
    GrTexture* onRefUnstretchedTexture(GrContext* ctx) override {
        return SkRef(fUnstretched);
    }

    bool onMakeStretchedKey(const SkGrStretch& stretch, GrUniqueKey* stretchedKey) override {
        make_raw_texture_stretched_key(fImage->uniqueID(), stretch, stretchedKey);
        return stretchedKey->isValid();
    }

    void onNotifyStretchCached(const GrUniqueKey& stretchedKey) override {
        as_IB(fImage)->notifyAddedToCache();
    }

    bool onGetROBitmap(SkBitmap* bitmap) override {
        return as_IB(fImage)->getROPixels(bitmap);
    }

private:
    const SkImage*  fImage;
    GrTexture*      fUnstretched;

    typedef GrTextureMaker INHERITED;
};

GrTexture* SkImage_Gpu::asTextureRef(GrContext* ctx, const GrTextureParams& params) const {
    return Texture_GrTextureMaker(this, fTexture).refCachedTexture(ctx, params);
}

bool SkImage_Gpu::isOpaque() const {
    return GrPixelConfigIsOpaque(fTexture->config()) || fAlphaType == kOpaque_SkAlphaType;
}

static void apply_premul(const SkImageInfo& info, void* pixels, size_t rowBytes) {
    switch (info.colorType()) {
        case kRGBA_8888_SkColorType:
        case kBGRA_8888_SkColorType:
            break;
        default:
            return; // nothing to do
    }

    // SkColor is not necesarily RGBA or BGRA, but it is one of them on little-endian,
    // and in either case, the alpha-byte is always in the same place, so we can safely call
    // SkPreMultiplyColor()
    //
    SkColor* row = (SkColor*)pixels;
    for (int y = 0; y < info.height(); ++y) {
        for (int x = 0; x < info.width(); ++x) {
            row[x] = SkPreMultiplyColor(row[x]);
        }
    }
}

bool SkImage_Gpu::onReadPixels(const SkImageInfo& info, void* pixels, size_t rowBytes,
                               int srcX, int srcY) const {
    GrPixelConfig config = SkImageInfo2GrPixelConfig(info.colorType(), info.alphaType(),
                                                     info.profileType());
    uint32_t flags = 0;
    if (kUnpremul_SkAlphaType == info.alphaType() && kPremul_SkAlphaType == fAlphaType) {
        // let the GPU perform this transformation for us
        flags = GrContext::kUnpremul_PixelOpsFlag;
    }
    if (!fTexture->readPixels(srcX, srcY, info.width(), info.height(), config,
                              pixels, rowBytes, flags)) {
        return false;
    }
    // do we have to manually fix-up the alpha channel?
    //      src         dst
    //      unpremul    premul      fix manually
    //      premul      unpremul    done by kUnpremul_PixelOpsFlag
    // all other combos need to change.
    //
    // Should this be handled by Ganesh? todo:?
    //
    if (kPremul_SkAlphaType == info.alphaType() && kUnpremul_SkAlphaType == fAlphaType) {
        apply_premul(info, pixels, rowBytes);
    }
    return true;
}

SkImage* SkImage_Gpu::onNewSubset(const SkIRect& subset) const {
    GrContext* ctx = fTexture->getContext();
    GrSurfaceDesc desc = fTexture->desc();
    desc.fWidth = subset.width();
    desc.fHeight = subset.height();

    GrTexture* subTx = ctx->textureProvider()->createTexture(desc,
                                                             SkSurface::kYes_Budgeted == fBudgeted);
    if (!subTx) {
        return nullptr;
    }
    ctx->copySurface(subTx, fTexture, subset, SkIPoint::Make(0, 0));
    return new SkImage_Gpu(desc.fWidth, desc.fHeight, kNeedNewImageUniqueID, fAlphaType, subTx,
                           fBudgeted);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SkGrPixelRef.h"
#include "SkImageFilter.h"

class SkGpuImageFilterProxy : public SkImageFilter::Proxy {
    GrContext* fCtx;

public:
    SkGpuImageFilterProxy(GrContext* ctx) : fCtx(ctx) {}

    SkBaseDevice* createDevice(int width, int height) override {
        GrSurfaceDesc desc;
        desc.fConfig = kSkia8888_GrPixelConfig;
        desc.fFlags = kRenderTarget_GrSurfaceFlag;
        desc.fWidth = width;
        desc.fHeight = height;
        desc.fSampleCnt = 0;

        SkAutoTUnref<GrTexture> texture(fCtx->textureProvider()->createTexture(desc, true));

        if (texture) {
            SkSurfaceProps props(0, kUnknown_SkPixelGeometry);
            return SkGpuDevice::Create(texture->asRenderTarget(), width, height, &props,
                                       SkGpuDevice::kClear_InitContents);
        } else {
            return nullptr;
        }
    }

    bool filterImage(const SkImageFilter* filter, const SkBitmap& src,
                     const SkImageFilter::Context& ctx, SkBitmap* dst, SkIPoint* offset) override {
        return filter->canFilterImageGPU() &&
               filter->filterImageGPU(this, src, ctx, dst, offset);
    }
};

static SkIRect compute_fast_ibounds(SkImageFilter* filter, const SkIRect& srcBounds) {
    SkRect fastBounds;
    fastBounds.set(srcBounds);
    filter->computeFastBounds(fastBounds, &fastBounds);
    return fastBounds.roundOut();
}

SkImage* SkImage_Gpu::onApplyFilter(SkImageFilter* filter, SkIPoint* offsetResult,
                                    bool forceResultToOriginalSize) const {
    const SkIRect srcBounds = SkIRect::MakeWH(this->width(), this->height());

    if (forceResultToOriginalSize) {
        SkBitmap src;
        GrWrapTextureInBitmap(fTexture, this->width(), this->height(), this->isOpaque(), &src);

        const SkIRect clipBounds = srcBounds;
        SkGpuImageFilterProxy proxy(fTexture->getContext());
        SkImageFilter::Context ctx(SkMatrix::I(), clipBounds, SkImageFilter::Cache::Get());

        SkBitmap dst;
        if (!filter->filterImage(&proxy, src, ctx, &dst, offsetResult)) {
            return nullptr;
        }
        return new SkImage_Gpu(dst.width(), dst.height(), kNeedNewImageUniqueID, dst.alphaType(),
                               dst.getTexture(), SkSurface::kNo_Budgeted);
    }

    const SkIRect dstR = compute_fast_ibounds(filter, srcBounds);

    SkImageInfo info = SkImageInfo::MakeN32Premul(dstR.width(), dstR.height());
    SkAutoTUnref<SkSurface> surface(this->onNewSurface(info));

    SkPaint paint;
    paint.setImageFilter(filter);
    surface->getCanvas()->drawImage(this, SkIntToScalar(-dstR.x()), SkIntToScalar(-dstR.y()),
                                    &paint);

    offsetResult->set(dstR.x(), dstR.y());
    return surface->newImageSnapshot();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

static SkImage* new_wrapped_texture_common(GrContext* ctx, const GrBackendTextureDesc& desc,
                                           SkAlphaType at, GrWrapOwnership ownership,
                                           SkImage::TextureReleaseProc releaseProc,
                                           SkImage::ReleaseContext releaseCtx) {
    if (desc.fWidth <= 0 || desc.fHeight <= 0) {
        return nullptr;
    }
    SkAutoTUnref<GrTexture> tex(ctx->textureProvider()->wrapBackendTexture(desc, ownership));
    if (!tex) {
        return nullptr;
    }
    if (releaseProc) {
        tex->setRelease(releaseProc, releaseCtx);
    }

    const SkSurface::Budgeted budgeted = SkSurface::kNo_Budgeted;
    return new SkImage_Gpu(desc.fWidth, desc.fHeight, kNeedNewImageUniqueID, at, tex, budgeted);
}

SkImage* SkImage::NewFromTexture(GrContext* ctx, const GrBackendTextureDesc& desc, SkAlphaType at,
                                 TextureReleaseProc releaseP, ReleaseContext releaseC) {
    return new_wrapped_texture_common(ctx, desc, at, kBorrow_GrWrapOwnership, releaseP, releaseC);
}

SkImage* SkImage::NewFromAdoptedTexture(GrContext* ctx, const GrBackendTextureDesc& desc,
                                        SkAlphaType at) {
    return new_wrapped_texture_common(ctx, desc, at, kAdopt_GrWrapOwnership, nullptr, nullptr);
}

SkImage* SkImage::NewFromTextureCopy(GrContext* ctx, const GrBackendTextureDesc& desc,
                                     SkAlphaType at) {
    if (desc.fWidth <= 0 || desc.fHeight <= 0) {
        return nullptr;
    }

    SkAutoTUnref<GrTexture> src(ctx->textureProvider()->wrapBackendTexture(
        desc, kBorrow_GrWrapOwnership));
    if (!src) {
        return nullptr;
    }

    const bool isBudgeted = true;
    SkAutoTUnref<GrTexture> dst(GrDeepCopyTexture(src, isBudgeted));
    if (!dst) {
        return nullptr;
    }

    const SkSurface::Budgeted budgeted = SkSurface::kYes_Budgeted;
    return new SkImage_Gpu(desc.fWidth, desc.fHeight, kNeedNewImageUniqueID, at, dst,
                           budgeted);
}

SkImage* SkImage::NewFromYUVTexturesCopy(GrContext* ctx , SkYUVColorSpace colorSpace,
                                         const GrBackendObject yuvTextureHandles[3],
                                         const SkISize yuvSizes[3],
                                         GrSurfaceOrigin origin) {
    const SkSurface::Budgeted budgeted = SkSurface::kYes_Budgeted;

    if (yuvSizes[0].fWidth <= 0 || yuvSizes[0].fHeight <= 0 ||
        yuvSizes[1].fWidth <= 0 || yuvSizes[1].fHeight <= 0 ||
        yuvSizes[2].fWidth <= 0 || yuvSizes[2].fHeight <= 0) {
        return nullptr;
    }
    static const GrPixelConfig kConfig = kAlpha_8_GrPixelConfig;
    GrBackendTextureDesc yDesc;
    yDesc.fConfig = kConfig;
    yDesc.fOrigin = origin;
    yDesc.fSampleCnt = 0;
    yDesc.fTextureHandle = yuvTextureHandles[0];
    yDesc.fWidth = yuvSizes[0].fWidth;
    yDesc.fHeight = yuvSizes[0].fHeight;

    GrBackendTextureDesc uDesc;
    uDesc.fConfig = kConfig;
    uDesc.fOrigin = origin;
    uDesc.fSampleCnt = 0;
    uDesc.fTextureHandle = yuvTextureHandles[1];
    uDesc.fWidth = yuvSizes[1].fWidth;
    uDesc.fHeight = yuvSizes[1].fHeight;

    GrBackendTextureDesc vDesc;
    vDesc.fConfig = kConfig;
    vDesc.fOrigin = origin;
    vDesc.fSampleCnt = 0;
    vDesc.fTextureHandle = yuvTextureHandles[2];
    vDesc.fWidth = yuvSizes[2].fWidth;
    vDesc.fHeight = yuvSizes[2].fHeight;

    SkAutoTUnref<GrTexture> yTex(ctx->textureProvider()->wrapBackendTexture(
        yDesc, kBorrow_GrWrapOwnership));
    SkAutoTUnref<GrTexture> uTex(ctx->textureProvider()->wrapBackendTexture(
        uDesc, kBorrow_GrWrapOwnership));
    SkAutoTUnref<GrTexture> vTex(ctx->textureProvider()->wrapBackendTexture(
        vDesc, kBorrow_GrWrapOwnership));
    if (!yTex || !uTex || !vTex) {
        return nullptr;
    }

    GrSurfaceDesc dstDesc;
    // Needs to be a render target in order to draw to it for the yuv->rgb conversion.
    dstDesc.fFlags = kRenderTarget_GrSurfaceFlag;
    dstDesc.fOrigin = origin;
    dstDesc.fWidth = yuvSizes[0].fWidth;
    dstDesc.fHeight = yuvSizes[0].fHeight;
    dstDesc.fConfig = kRGBA_8888_GrPixelConfig;
    dstDesc.fSampleCnt = 0;

    SkAutoTUnref<GrTexture> dst(ctx->textureProvider()->createTexture(dstDesc, true));
    if (!dst) {
        return nullptr;
    }

    GrPaint paint;
    paint.setPorterDuffXPFactory(SkXfermode::kSrc_Mode);
    paint.addColorFragmentProcessor(GrYUVtoRGBEffect::Create(yTex, uTex, vTex, yuvSizes,
                                                             colorSpace))->unref();

    const SkRect rect = SkRect::MakeWH(SkIntToScalar(dstDesc.fWidth),
                                       SkIntToScalar(dstDesc.fHeight));
    SkAutoTUnref<GrDrawContext> drawContext(ctx->drawContext(dst->asRenderTarget()));
    if (!drawContext) {
        return nullptr;
    }

    drawContext->drawRect(GrClip::WideOpen(), paint, SkMatrix::I(), rect);
    ctx->flushSurfaceWrites(dst);
    return new SkImage_Gpu(dstDesc.fWidth, dstDesc.fHeight, kNeedNewImageUniqueID,
                           kOpaque_SkAlphaType, dst, budgeted);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

GrTexture* GrDeepCopyTexture(GrTexture* src, bool budgeted) {
    GrContext* ctx = src->getContext();

    GrSurfaceDesc desc = src->desc();
    GrTexture* dst = ctx->textureProvider()->createTexture(desc, budgeted, nullptr, 0);
    if (!dst) {
        return nullptr;
    }
    
    const SkIRect srcR = SkIRect::MakeWH(desc.fWidth, desc.fHeight);
    const SkIPoint dstP = SkIPoint::Make(0, 0);
    ctx->copySurface(dst, src, srcR, dstP, GrContext::kFlushWrites_PixelOp);
    return dst;
}

