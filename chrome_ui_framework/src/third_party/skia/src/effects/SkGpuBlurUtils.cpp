/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkGpuBlurUtils.h"

#include "SkRect.h"

#if SK_SUPPORT_GPU
#include "effects/GrConvolutionEffect.h"
#include "effects/GrMatrixConvolutionEffect.h"
#include "GrContext.h"
#include "GrCaps.h"
#include "GrDrawContext.h"
#endif

namespace SkGpuBlurUtils {

#if SK_SUPPORT_GPU

#define MAX_BLUR_SIGMA 4.0f

static void scale_rect(SkRect* rect, float xScale, float yScale) {
    rect->fLeft   = SkScalarMul(rect->fLeft,   xScale);
    rect->fTop    = SkScalarMul(rect->fTop,    yScale);
    rect->fRight  = SkScalarMul(rect->fRight,  xScale);
    rect->fBottom = SkScalarMul(rect->fBottom, yScale);
}

static float adjust_sigma(float sigma, int maxTextureSize, int *scaleFactor, int *radius) {
    *scaleFactor = 1;
    while (sigma > MAX_BLUR_SIGMA) {
        *scaleFactor *= 2;
        sigma *= 0.5f;
        if (*scaleFactor > maxTextureSize) {
            *scaleFactor = maxTextureSize;
            sigma = MAX_BLUR_SIGMA;
        }
    }
    *radius = static_cast<int>(ceilf(sigma * 3.0f));
    SkASSERT(*radius <= GrConvolutionEffect::kMaxKernelRadius);
    return sigma;
}

static void convolve_gaussian_1d(GrDrawContext* drawContext,
                                 const GrClip& clip,
                                 const SkRect& srcRect,
                                 const SkRect& dstRect,
                                 GrTexture* texture,
                                 Gr1DKernelEffect::Direction direction,
                                 int radius,
                                 float sigma,
                                 bool useBounds,
                                 float bounds[2]) {
    GrPaint paint;
    SkAutoTUnref<GrFragmentProcessor> conv(GrConvolutionEffect::CreateGaussian(
        texture, direction, radius, sigma, useBounds, bounds));
    paint.addColorFragmentProcessor(conv);
    drawContext->drawNonAARectToRect(clip, paint, SkMatrix::I(), dstRect, srcRect);
}

static void convolve_gaussian_2d(GrDrawContext* drawContext,
                                 const GrClip& clip,
                                 const SkRect& srcRect,
                                 const SkRect& dstRect,
                                 GrTexture* texture,
                                 int radiusX,
                                 int radiusY,
                                 SkScalar sigmaX,
                                 SkScalar sigmaY,
                                 bool useBounds,
                                 SkIRect bounds) {
    SkISize size = SkISize::Make(2 * radiusX + 1,  2 * radiusY + 1);
    SkIPoint kernelOffset = SkIPoint::Make(radiusX, radiusY);
    GrPaint paint;
    SkAutoTUnref<GrFragmentProcessor> conv(GrMatrixConvolutionEffect::CreateGaussian(
            texture, bounds, size, 1.0, 0.0, kernelOffset,
            useBounds ? GrTextureDomain::kClamp_Mode : GrTextureDomain::kIgnore_Mode,
            true, sigmaX, sigmaY));
    paint.addColorFragmentProcessor(conv);
    drawContext->drawNonAARectToRect(clip, paint, SkMatrix::I(), dstRect, srcRect);
}

static void convolve_gaussian(GrDrawContext* drawContext,
                              const GrClip& clip,
                              const SkRect& srcRect,
                              const SkRect& dstRect,
                              GrTexture* texture,
                              Gr1DKernelEffect::Direction direction,
                              int radius,
                              float sigma,
                              bool cropToSrcRect) {
    float bounds[2] = { 0.0f, 1.0f };
    if (!cropToSrcRect) {
        convolve_gaussian_1d(drawContext, clip, srcRect, dstRect, texture,
                             direction, radius, sigma, false, bounds);
        return;
    }
    SkRect lowerSrcRect = srcRect, lowerDstRect = dstRect;
    SkRect middleSrcRect = srcRect, middleDstRect = dstRect;
    SkRect upperSrcRect = srcRect, upperDstRect = dstRect;
    SkScalar size;
    SkScalar rad = SkIntToScalar(radius);
    if (direction == Gr1DKernelEffect::kX_Direction) {
        bounds[0] = SkScalarToFloat(srcRect.left()) / texture->width();
        bounds[1] = SkScalarToFloat(srcRect.right()) / texture->width();
        size = srcRect.width();
        lowerSrcRect.fRight = srcRect.left() + rad;
        lowerDstRect.fRight = dstRect.left() + rad;
        upperSrcRect.fLeft = srcRect.right() - rad;
        upperDstRect.fLeft = dstRect.right() - rad;
        middleSrcRect.inset(rad, 0);
        middleDstRect.inset(rad, 0);
    } else {
        bounds[0] = SkScalarToFloat(srcRect.top()) / texture->height();
        bounds[1] = SkScalarToFloat(srcRect.bottom()) / texture->height();
        size = srcRect.height();
        lowerSrcRect.fBottom = srcRect.top() + rad;
        lowerDstRect.fBottom = dstRect.top() + rad;
        upperSrcRect.fTop = srcRect.bottom() - rad;
        upperDstRect.fTop = dstRect.bottom() - rad;
        middleSrcRect.inset(0, rad);
        middleDstRect.inset(0, rad);
    }
    if (radius >= size * SK_ScalarHalf) {
        // Blur radius covers srcRect; use bounds over entire draw
        convolve_gaussian_1d(drawContext, clip, srcRect, dstRect, texture,
                            direction, radius, sigma, true, bounds);
    } else {
        // Draw upper and lower margins with bounds; middle without.
        convolve_gaussian_1d(drawContext, clip, lowerSrcRect, lowerDstRect, texture,
                             direction, radius, sigma, true, bounds);
        convolve_gaussian_1d(drawContext, clip, upperSrcRect, upperDstRect, texture,
                             direction, radius, sigma, true, bounds);
        convolve_gaussian_1d(drawContext, clip, middleSrcRect, middleDstRect, texture,
                             direction, radius, sigma, false, bounds);
    }
}

GrTexture* GaussianBlur(GrContext* context,
                        GrTexture* srcTexture,
                        bool canClobberSrc,
                        const SkRect& rect,
                        bool cropToRect,
                        float sigmaX,
                        float sigmaY) {
    SkASSERT(context);

    SkIRect clearRect;
    int scaleFactorX, radiusX;
    int scaleFactorY, radiusY;
    int maxTextureSize = context->caps()->maxTextureSize();
    sigmaX = adjust_sigma(sigmaX, maxTextureSize, &scaleFactorX, &radiusX);
    sigmaY = adjust_sigma(sigmaY, maxTextureSize, &scaleFactorY, &radiusY);

    SkRect srcRect(rect);
    scale_rect(&srcRect, 1.0f / scaleFactorX, 1.0f / scaleFactorY);
    srcRect.roundOut(&srcRect);
    scale_rect(&srcRect, static_cast<float>(scaleFactorX),
                         static_cast<float>(scaleFactorY));

    // setup new clip
    GrClip clip(SkRect::MakeWH(srcRect.width(), srcRect.height()));

    SkASSERT(kBGRA_8888_GrPixelConfig == srcTexture->config() ||
             kRGBA_8888_GrPixelConfig == srcTexture->config() ||
             kAlpha_8_GrPixelConfig == srcTexture->config());

    GrSurfaceDesc desc;
    desc.fFlags = kRenderTarget_GrSurfaceFlag;
    desc.fWidth = SkScalarFloorToInt(srcRect.width());
    desc.fHeight = SkScalarFloorToInt(srcRect.height());
    desc.fConfig = srcTexture->config();

    GrTexture* dstTexture;
    GrTexture* tempTexture;
    SkAutoTUnref<GrTexture> temp1, temp2;

    temp1.reset(context->textureProvider()->createApproxTexture(desc));
    dstTexture = temp1.get();
    if (canClobberSrc) {
        tempTexture = srcTexture;
    } else {
        temp2.reset(context->textureProvider()->createApproxTexture(desc));
        tempTexture = temp2.get();
    }

    if (nullptr == dstTexture || nullptr == tempTexture) {
        return nullptr;
    }

    SkAutoTUnref<GrDrawContext> srcDrawContext;

    for (int i = 1; i < scaleFactorX || i < scaleFactorY; i *= 2) {
        GrPaint paint;
        SkMatrix matrix;
        matrix.setIDiv(srcTexture->width(), srcTexture->height());
        SkRect dstRect(srcRect);
        if (cropToRect && i == 1) {
            dstRect.offset(-dstRect.fLeft, -dstRect.fTop);
            SkRect domain;
            matrix.mapRect(&domain, rect);
            domain.inset(i < scaleFactorX ? SK_ScalarHalf / srcTexture->width() : 0.0f,
                         i < scaleFactorY ? SK_ScalarHalf / srcTexture->height() : 0.0f);
            SkAutoTUnref<const GrFragmentProcessor> fp(GrTextureDomainEffect::Create(
                srcTexture,
                matrix,
                domain,
                GrTextureDomain::kDecal_Mode,
                GrTextureParams::kBilerp_FilterMode));
            paint.addColorFragmentProcessor(fp);
        } else {
            GrTextureParams params(SkShader::kClamp_TileMode, GrTextureParams::kBilerp_FilterMode);
            paint.addColorTextureProcessor(srcTexture, matrix, params);
        }
        scale_rect(&dstRect, i < scaleFactorX ? 0.5f : 1.0f,
                             i < scaleFactorY ? 0.5f : 1.0f);

        SkAutoTUnref<GrDrawContext> dstDrawContext(
                                             context->drawContext(dstTexture->asRenderTarget()));
        if (!dstDrawContext) {
            return nullptr;
        }
        dstDrawContext->drawNonAARectToRect(clip, paint, SkMatrix::I(), dstRect, srcRect);

        srcDrawContext.swap(dstDrawContext);
        srcRect = dstRect;
        srcTexture = dstTexture;
        SkTSwap(dstTexture, tempTexture);
    }

    const SkIRect srcIRect = srcRect.roundOut();

    // For really small blurs (certainly no wider than 5x5 on desktop gpus) it is faster to just
    // launch a single non separable kernel vs two launches
    if (sigmaX > 0.0f && sigmaY > 0.0f &&
            (2 * radiusX + 1) * (2 * radiusY + 1) <= MAX_KERNEL_SIZE) {
        // We shouldn't be scaling because this is a small size blur
        SkASSERT((1 == scaleFactorX) && (1 == scaleFactorY));
        SkRect dstRect = SkRect::MakeWH(srcRect.width(), srcRect.height());

        SkAutoTUnref<GrDrawContext> dstDrawContext(
                                             context->drawContext(dstTexture->asRenderTarget()));
        if (!dstDrawContext) {
            return nullptr;
        }
        convolve_gaussian_2d(dstDrawContext, clip, srcRect, dstRect,
                             srcTexture, radiusX, radiusY, sigmaX, sigmaY, cropToRect, srcIRect);

        srcDrawContext.swap(dstDrawContext);
        srcRect = dstRect;
        srcTexture = dstTexture;
        SkTSwap(dstTexture, tempTexture);

    } else {
        if (sigmaX > 0.0f) {
            if (scaleFactorX > 1) {
                // TODO: if we pass in the source draw context we don't need this here
                if (!srcDrawContext) {
                    srcDrawContext.reset(context->drawContext(srcTexture->asRenderTarget()));
                    if (!srcDrawContext) {
                        return nullptr;
                    }        
                }

                // Clear out a radius to the right of the srcRect to prevent the
                // X convolution from reading garbage.
                clearRect = SkIRect::MakeXYWH(srcIRect.fRight, srcIRect.fTop,
                                              radiusX, srcIRect.height());
                srcDrawContext->clear(&clearRect, 0x0, false);
            }
            SkRect dstRect = SkRect::MakeWH(srcRect.width(), srcRect.height());

            SkAutoTUnref<GrDrawContext> dstDrawContext(
                                             context->drawContext(dstTexture->asRenderTarget()));
            if (!dstDrawContext) {
                return nullptr;
            }
            convolve_gaussian(dstDrawContext, clip, srcRect, dstRect,
                              srcTexture, Gr1DKernelEffect::kX_Direction, radiusX, sigmaX,
                              cropToRect);

            srcDrawContext.swap(dstDrawContext);
            srcTexture = dstTexture;
            srcRect = dstRect;
            SkTSwap(dstTexture, tempTexture);
        }

        if (sigmaY > 0.0f) {
            if (scaleFactorY > 1 || sigmaX > 0.0f) {
                // TODO: if we pass in the source draw context we don't need this here
                if (!srcDrawContext) {
                    srcDrawContext.reset(context->drawContext(srcTexture->asRenderTarget()));
                    if (!srcDrawContext) {
                        return nullptr;
                    }        
                }

                // Clear out a radius below the srcRect to prevent the Y
                // convolution from reading garbage.
                clearRect = SkIRect::MakeXYWH(srcIRect.fLeft, srcIRect.fBottom,
                                              srcIRect.width(), radiusY);
                srcDrawContext->clear(&clearRect, 0x0, false);
            }

            SkRect dstRect = SkRect::MakeWH(srcRect.width(), srcRect.height());

            SkAutoTUnref<GrDrawContext> dstDrawContext(
                                               context->drawContext(dstTexture->asRenderTarget()));
            if (!dstDrawContext) {
                return nullptr;
            }
            convolve_gaussian(dstDrawContext, clip, srcRect,
                              dstRect, srcTexture, Gr1DKernelEffect::kY_Direction, radiusY, sigmaY,
                              cropToRect);

            srcDrawContext.swap(dstDrawContext);
            srcTexture = dstTexture;
            srcRect = dstRect;
            SkTSwap(dstTexture, tempTexture);
        }
    }

    if (scaleFactorX > 1 || scaleFactorY > 1) {
        SkASSERT(srcDrawContext);

        // Clear one pixel to the right and below, to accommodate bilinear
        // upsampling.
        clearRect = SkIRect::MakeXYWH(srcIRect.fLeft, srcIRect.fBottom,
                                      srcIRect.width() + 1, 1);
        srcDrawContext->clear(&clearRect, 0x0, false);
        clearRect = SkIRect::MakeXYWH(srcIRect.fRight, srcIRect.fTop,
                                      1, srcIRect.height());
        srcDrawContext->clear(&clearRect, 0x0, false);
        SkMatrix matrix;
        matrix.setIDiv(srcTexture->width(), srcTexture->height());

        GrPaint paint;
        // FIXME:  this should be mitchell, not bilinear.
        GrTextureParams params(SkShader::kClamp_TileMode, GrTextureParams::kBilerp_FilterMode);
        paint.addColorTextureProcessor(srcTexture, matrix, params);

        SkRect dstRect(srcRect);
        scale_rect(&dstRect, (float) scaleFactorX, (float) scaleFactorY);

        SkAutoTUnref<GrDrawContext> dstDrawContext(
                                context->drawContext(dstTexture->asRenderTarget()));
        if (!dstDrawContext) {
            return nullptr;
        }
        dstDrawContext->drawNonAARectToRect(clip, paint, SkMatrix::I(), dstRect, srcRect);

        srcDrawContext.swap(dstDrawContext);
        srcRect = dstRect;
        srcTexture = dstTexture;
        SkTSwap(dstTexture, tempTexture);
    }

    return SkRef(srcTexture);
}
#endif

}
