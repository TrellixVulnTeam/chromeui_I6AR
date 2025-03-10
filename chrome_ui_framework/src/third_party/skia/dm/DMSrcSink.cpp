/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "DMSrcSink.h"
#include "SamplePipeControllers.h"
#include "SkCodec.h"
#include "SkCodecTools.h"
#include "SkCommonFlags.h"
#include "SkData.h"
#include "SkDocument.h"
#include "SkError.h"
#include "SkFunction.h"
#include "SkImageGenerator.h"
#include "SkMultiPictureDraw.h"
#include "SkNullCanvas.h"
#include "SkOSFile.h"
#include "SkPictureData.h"
#include "SkPictureRecorder.h"
#include "SkRandom.h"
#include "SkRecordDraw.h"
#include "SkRecorder.h"
#include "SkRemote.h"
#include "SkSVGCanvas.h"
#include "SkScaledCodec.h"
#include "SkStream.h"
#include "SkTLogic.h"
#include "SkXMLWriter.h"
#include "SkScaledCodec.h"
#include "SkSwizzler.h"

DEFINE_bool(multiPage, false, "For document-type backends, render the source"
            " into multiple pages");

static bool lazy_decode_bitmap(const void* src, size_t size, SkBitmap* dst) {
    SkAutoTUnref<SkData> encoded(SkData::NewWithCopy(src, size));
    return encoded && SkDEPRECATED_InstallDiscardablePixelRef(encoded, dst);
}

namespace DM {

GMSrc::GMSrc(skiagm::GMRegistry::Factory factory) : fFactory(factory) {}

Error GMSrc::draw(SkCanvas* canvas) const {
    SkAutoTDelete<skiagm::GM> gm(fFactory(nullptr));
    canvas->concat(gm->getInitialTransform());
    gm->draw(canvas);
    return "";
}

SkISize GMSrc::size() const {
    SkAutoTDelete<skiagm::GM> gm(fFactory(nullptr));
    return gm->getISize();
}

Name GMSrc::name() const {
    SkAutoTDelete<skiagm::GM> gm(fFactory(nullptr));
    return gm->getName();
}

void GMSrc::modifyGrContextOptions(GrContextOptions* options) const {
    SkAutoTDelete<skiagm::GM> gm(fFactory(nullptr));
    gm->modifyGrContextOptions(options);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BRDSrc::BRDSrc(Path path, SkBitmapRegionDecoderInterface::Strategy strategy, Mode mode,
        CodecSrc::DstColorType dstColorType, uint32_t sampleSize)
    : fPath(path)
    , fStrategy(strategy)
    , fMode(mode)
    , fDstColorType(dstColorType)
    , fSampleSize(sampleSize)
{}

bool BRDSrc::veto(SinkFlags flags) const {
    // No need to test to non-raster or indirect backends.
    return flags.type != SinkFlags::kRaster
        || flags.approach != SinkFlags::kDirect;
}

static SkBitmapRegionDecoderInterface* create_brd(Path path,
        SkBitmapRegionDecoderInterface::Strategy strategy) {
    SkAutoTUnref<SkData> encoded(SkData::NewFromFileName(path.c_str()));
    if (!encoded) {
        return NULL;
    }
    return SkBitmapRegionDecoderInterface::CreateBitmapRegionDecoder(new SkMemoryStream(encoded),
            strategy);
}

Error BRDSrc::draw(SkCanvas* canvas) const {
    SkColorType colorType = canvas->imageInfo().colorType();
    if (kRGB_565_SkColorType == colorType &&
            CodecSrc::kGetFromCanvas_DstColorType != fDstColorType) {
        return Error::Nonfatal("Testing non-565 to 565 is uninteresting.");
    }
    switch (fDstColorType) {
        case CodecSrc::kGetFromCanvas_DstColorType:
            break;
        case CodecSrc::kIndex8_Always_DstColorType:
            colorType = kIndex_8_SkColorType;
            break;
        case CodecSrc::kGrayscale_Always_DstColorType:
            colorType = kGray_8_SkColorType;
            break;
    }

    SkAutoTDelete<SkBitmapRegionDecoderInterface> brd(create_brd(fPath, fStrategy));
    if (nullptr == brd.get()) {
        return Error::Nonfatal(SkStringPrintf("Could not create brd for %s.", fPath.c_str()));
    }

    if (!brd->conversionSupported(colorType)) {
        return Error::Nonfatal("Cannot convert to color type.\n");
    }

    const uint32_t width = brd->width();
    const uint32_t height = brd->height();
    // Visually inspecting very small output images is not necessary.
    if ((width / fSampleSize <= 10 || height / fSampleSize <= 10) && 1 != fSampleSize) {
        return Error::Nonfatal("Scaling very small images is uninteresting.");
    }
    switch (fMode) {
        case kFullImage_Mode: {
            SkAutoTDelete<SkBitmap> bitmap(brd->decodeRegion(0, 0, width, height, fSampleSize,
                    colorType));
            if (nullptr == bitmap.get() || colorType != bitmap->colorType()) {
                return Error::Nonfatal("Cannot convert to color type.\n");
            }
            canvas->drawBitmap(*bitmap, 0, 0);
            return "";
        }
        case kDivisor_Mode: {
            const uint32_t divisor = 2;
            if (width < divisor || height < divisor) {
                return Error::Nonfatal("Divisor is larger than image dimension.\n");
            }

            // Use a border to test subsets that extend outside the image.
            // We will not allow the border to be larger than the image dimensions.  Allowing
            // these large borders causes off by one errors that indicate a problem with the
            // test suite, not a problem with the implementation.
            const uint32_t maxBorder = SkTMin(width, height) / (fSampleSize * divisor);
            const uint32_t scaledBorder = SkTMin(5u, maxBorder);
            const uint32_t unscaledBorder = scaledBorder * fSampleSize;

            // We may need to clear the canvas to avoid uninitialized memory.
            // Assume we are scaling a 780x780 image with sampleSize = 8.
            // The output image should be 97x97.
            // Each subset will be 390x390.
            // Each scaled subset be 48x48.
            // Four scaled subsets will only fill a 96x96 image.
            // The bottom row and last column will not be touched.
            // This is an unfortunate result of our rounding rules when scaling.
            // Maybe we need to consider testing scaled subsets without trying to
            // combine them to match the full scaled image?  Or maybe this is the
            // best we can do?
            canvas->clear(0);

            for (uint32_t x = 0; x < divisor; x++) {
                for (uint32_t y = 0; y < divisor; y++) {
                    // Calculate the subset dimensions
                    uint32_t subsetWidth = width / divisor;
                    uint32_t subsetHeight = height / divisor;
                    const int left = x * subsetWidth;
                    const int top = y * subsetHeight;

                    // Increase the size of the last subset in each row or column, when the
                    // divisor does not divide evenly into the image dimensions
                    subsetWidth += (x + 1 == divisor) ? (width % divisor) : 0;
                    subsetHeight += (y + 1 == divisor) ? (height % divisor) : 0;

                    // Increase the size of the subset in order to have a border on each side
                    const int decodeLeft = left - unscaledBorder;
                    const int decodeTop = top - unscaledBorder;
                    const uint32_t decodeWidth = subsetWidth + unscaledBorder * 2;
                    const uint32_t decodeHeight = subsetHeight + unscaledBorder * 2;
                    SkAutoTDelete<SkBitmap> bitmap(brd->decodeRegion(decodeLeft,
                            decodeTop, decodeWidth, decodeHeight, fSampleSize, colorType));
                    if (nullptr == bitmap.get() || colorType != bitmap->colorType()) {
                        return Error::Nonfatal("Cannot convert to color type.\n");
                    }

                    canvas->drawBitmapRect(*bitmap,
                            SkRect::MakeXYWH((SkScalar) scaledBorder, (SkScalar) scaledBorder,
                                    (SkScalar) (subsetWidth / fSampleSize),
                                    (SkScalar) (subsetHeight / fSampleSize)),
                            SkRect::MakeXYWH((SkScalar) (left / fSampleSize),
                                    (SkScalar) (top / fSampleSize),
                                    (SkScalar) (subsetWidth / fSampleSize),
                                    (SkScalar) (subsetHeight / fSampleSize)),
                            nullptr);
                }
            }
            return "";
        }
        default:
            SkASSERT(false);
            return "Error: Should not be reached.\n";
    }
}

SkISize BRDSrc::size() const {
    SkAutoTDelete<SkBitmapRegionDecoderInterface> brd(create_brd(fPath, fStrategy));
    if (brd) {
        return SkISize::Make(SkTMax(1, brd->width() / (int) fSampleSize),
                SkTMax(1, brd->height() / (int) fSampleSize));
    }
    return SkISize::Make(0, 0);
}

static SkString get_scaled_name(const Path& path, float scale) {
    return SkStringPrintf("%s_%.3f", SkOSPath::Basename(path.c_str()).c_str(), scale);
}

Name BRDSrc::name() const {
    // We will replicate the names used by CodecSrc so that images can
    // be compared in Gold.
    if (1 == fSampleSize) {
        return SkOSPath::Basename(fPath.c_str());
    }
    return get_scaled_name(fPath, get_scale_from_sample_size(fSampleSize));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CodecSrc::CodecSrc(Path path, Mode mode, DstColorType dstColorType, float scale)
    : fPath(path)
    , fMode(mode)
    , fDstColorType(dstColorType)
    , fScale(scale)
{}

bool CodecSrc::veto(SinkFlags flags) const {
    // No need to test decoding to non-raster or indirect backend.
    // TODO: Once we implement GPU paths (e.g. JPEG YUV), we should use a deferred decode to
    // let the GPU handle it.
    return flags.type != SinkFlags::kRaster
        || flags.approach != SinkFlags::kDirect;
}

Error CodecSrc::draw(SkCanvas* canvas) const {
    SkAutoTUnref<SkData> encoded(SkData::NewFromFileName(fPath.c_str()));
    if (!encoded) {
        return SkStringPrintf("Couldn't read %s.", fPath.c_str());
    }
    SkAutoTDelete<SkCodec> codec(NULL);
    if (kScaledCodec_Mode == fMode) {
        codec.reset(SkScaledCodec::NewFromData(encoded));
        // TODO (msarett): This should fall through to a fatal error once we support scaled
        //                 codecs for all image types.
        if (nullptr == codec.get()) {
            return Error::Nonfatal(SkStringPrintf("Couldn't create scaled codec for %s.",
                    fPath.c_str()));
        }
    } else {
        codec.reset(SkCodec::NewFromData(encoded));
    }
    if (nullptr == codec.get()) {
        return SkStringPrintf("Couldn't create codec for %s.", fPath.c_str());
    }

    // Choose the color type to decode to
    SkImageInfo decodeInfo = codec->getInfo();
    SkColorType canvasColorType = canvas->imageInfo().colorType();
    switch (fDstColorType) {
        case kIndex8_Always_DstColorType:
            decodeInfo = codec->getInfo().makeColorType(kIndex_8_SkColorType);
            if (kRGB_565_SkColorType == canvasColorType) {
                return Error::Nonfatal("Testing non-565 to 565 is uninteresting.");
            }
            break;
        case kGrayscale_Always_DstColorType:
            decodeInfo = codec->getInfo().makeColorType(kGray_8_SkColorType);
            if (kRGB_565_SkColorType == canvasColorType) {
                return Error::Nonfatal("Testing non-565 to 565 is uninteresting.");
            }
            break;
        default:
            decodeInfo = decodeInfo.makeColorType(canvasColorType);
            break;
    }

    // Try to scale the image if it is desired
    SkISize size = codec->getScaledDimensions(fScale);
    if (size == decodeInfo.dimensions() && 1.0f != fScale) {
        return Error::Nonfatal("Test without scaling is uninteresting.");
    }

    // Visually inspecting very small output images is not necessary.  We will
    // cover these cases in unit testing.
    if ((size.width() <= 10 || size.height() <= 10) && 1.0f != fScale) {
        return Error::Nonfatal("Scaling very small images is uninteresting.");
    }
    decodeInfo = decodeInfo.makeWH(size.width(), size.height());

    // Construct a color table for the decode if necessary
    SkAutoTUnref<SkColorTable> colorTable(nullptr);
    SkPMColor* colorPtr = nullptr;
    int* colorCountPtr = nullptr;
    int maxColors = 256;
    if (kIndex_8_SkColorType == decodeInfo.colorType()) {
        SkPMColor colors[256];
        colorTable.reset(new SkColorTable(colors, maxColors));
        colorPtr = const_cast<SkPMColor*>(colorTable->readColors());
        colorCountPtr = &maxColors;
    }

    // FIXME: Currently we cannot draw unpremultiplied sources.
    if (decodeInfo.alphaType() == kUnpremul_SkAlphaType) {
        decodeInfo = decodeInfo.makeAlphaType(kPremul_SkAlphaType);
    }

    SkBitmap bitmap;
    if (!bitmap.tryAllocPixels(decodeInfo, nullptr, colorTable.get())) {
        return SkStringPrintf("Image(%s) is too large (%d x %d)\n", fPath.c_str(),
                              decodeInfo.width(), decodeInfo.height());
    }

    switch (fMode) {
        case kScaledCodec_Mode:
        case kCodec_Mode: {
            switch (codec->getPixels(decodeInfo, bitmap.getPixels(), bitmap.rowBytes(), nullptr,
                    colorPtr, colorCountPtr)) {
                case SkCodec::kSuccess:
                    // We consider incomplete to be valid, since we should still decode what is
                    // available.
                case SkCodec::kIncompleteInput:
                    break;
                case SkCodec::kInvalidConversion:
                    return Error::Nonfatal("Incompatible colortype conversion");
                default:
                    // Everything else is considered a failure.
                    return SkStringPrintf("Couldn't getPixels %s.", fPath.c_str());
            }
            canvas->drawBitmap(bitmap, 0, 0);
            break;
        }
        case kScanline_Mode: {
            if (SkCodec::kSuccess != codec->startScanlineDecode(decodeInfo, NULL, colorPtr,
                                                                colorCountPtr)) {
                return Error::Nonfatal("Could not start scanline decoder");
            }

            void* dst = bitmap.getAddr(0, 0);
            size_t rowBytes = bitmap.rowBytes();
            uint32_t height = decodeInfo.height();
            switch (codec->getScanlineOrder()) {
                case SkCodec::kTopDown_SkScanlineOrder:
                case SkCodec::kBottomUp_SkScanlineOrder:
                case SkCodec::kNone_SkScanlineOrder:
                    // We do not need to check the return value.  On an incomplete
                    // image, memory will be filled with a default value.
                    codec->getScanlines(dst, height, rowBytes);
                    break;
                case SkCodec::kOutOfOrder_SkScanlineOrder: {
                    for (int y = 0; y < decodeInfo.height(); y++) {
                        int dstY = codec->outputScanline(y);
                        void* dstPtr = bitmap.getAddr(0, dstY);
                        // We complete the loop, even if this call begins to fail
                        // due to an incomplete image.  This ensures any uninitialized
                        // memory will be filled with the proper value.
                        codec->getScanlines(dstPtr, 1, bitmap.rowBytes());
                    }
                    break;
                }
            }

            canvas->drawBitmap(bitmap, 0, 0);
            break;
        }
        case kScanline_Subset_Mode: {
            //this mode decodes the image in divisor*divisor subsets, using a scanline decoder
            const int divisor = 2;
            const int w = decodeInfo.width();
            const int h = decodeInfo.height();
            if (divisor > w || divisor > h) {
                return Error::Nonfatal(SkStringPrintf("Cannot decode subset: divisor %d is too big"
                        "for %s with dimensions (%d x %d)", divisor, fPath.c_str(), w, h));
            }
            const int subsetWidth = w/divisor;
            const int subsetHeight = h/divisor;
            // One of our subsets will be larger to contain any pixels that do not divide evenly.
            const int extraX = w % divisor;
            const int extraY = h % divisor;
            /*
            * if w or h are not evenly divided by divisor need to adjust width and height of end
            * subsets to cover entire image.
            * Add extraX and extraY to largestSubsetBm's width and height to adjust width
            * and height of end subsets.
            * subsetBm is extracted from largestSubsetBm.
            * subsetBm's size is determined based on the current subset and may be larger for end
            * subsets.
            */
            SkImageInfo largestSubsetDecodeInfo =
                    decodeInfo.makeWH(subsetWidth + extraX, subsetHeight + extraY);
            SkBitmap largestSubsetBm;
            if (!largestSubsetBm.tryAllocPixels(largestSubsetDecodeInfo, nullptr,
                    colorTable.get())) {
                return SkStringPrintf("Image(%s) is too large (%d x %d)\n", fPath.c_str(),
                        largestSubsetDecodeInfo.width(), largestSubsetDecodeInfo.height());
            }
            for (int col = 0; col < divisor; col++) {
                //currentSubsetWidth may be larger than subsetWidth for rightmost subsets
                const int currentSubsetWidth = (col + 1 == divisor) ?
                        subsetWidth + extraX : subsetWidth;
                const int x = col * subsetWidth;
                for (int row = 0; row < divisor; row++) {
                    //currentSubsetHeight may be larger than subsetHeight for bottom subsets
                    const int currentSubsetHeight = (row + 1 == divisor) ?
                            subsetHeight + extraY : subsetHeight;
                    const int y = row * subsetHeight;
                    //create scanline decoder for each subset
                    SkCodec::Options options;
                    SkIRect subset = SkIRect::MakeXYWH(x, 0, currentSubsetWidth, h);
                    options.fSubset = &subset;
                    // TODO (msarett): Support this mode for all scanline orderings.
                    if (SkCodec::kSuccess != codec->startScanlineDecode(decodeInfo, &options,
                            colorPtr, colorCountPtr) ||
                            SkCodec::kTopDown_SkScanlineOrder != codec->getScanlineOrder()) {
                        if (x == 0 && y == 0) {
                            //first try, image may not be compatible
                            return Error::Nonfatal("Could not start top-down scanline decoder");
                        } else {
                            return "Error scanline decoder is nullptr";
                        }
                    }
                    // Skip to the first line of subset.  We ignore the result value here.
                    // If the skip value fails, this will indicate an incomplete image.
                    // This means that the call to getScanlines() will also fail, but it
                    // will fill the buffer with a default value, so we can still draw the
                    // image.
                    codec->skipScanlines(y);

                    //create and set size of subsetBm
                    SkBitmap subsetBm;
                    SkIRect bounds = SkIRect::MakeWH(currentSubsetWidth, currentSubsetHeight);
                    SkAssertResult(largestSubsetBm.extractSubset(&subsetBm, bounds));
                    SkAutoLockPixels autolock(subsetBm, true);
                    codec->getScanlines(subsetBm.getAddr(0, 0), currentSubsetHeight,
                            subsetBm.rowBytes());
                    subsetBm.notifyPixelsChanged();
                    canvas->drawBitmap(subsetBm, SkIntToScalar(x), SkIntToScalar(y));
                }
            }
            break;
        }
        case kStripe_Mode: {
            const int height = decodeInfo.height();
            // This value is chosen arbitrarily.  We exercise more cases by choosing a value that
            // does not align with image blocks.
            const int stripeHeight = 37;
            const int numStripes = (height + stripeHeight - 1) / stripeHeight;

            // Decode odd stripes
            if (SkCodec::kSuccess != codec->startScanlineDecode(decodeInfo, NULL, colorPtr,
                                                                colorCountPtr)
                    || SkCodec::kTopDown_SkScanlineOrder != codec->getScanlineOrder()) {
                // This mode was designed to test the new skip scanlines API in libjpeg-turbo.
                // Jpegs have kTopDown_SkScanlineOrder, and at this time, it is not interesting
                // to run this test for image types that do not have this scanline ordering.
                return Error::Nonfatal("Could not start top-down scanline decoder");
            }

            for (int i = 0; i < numStripes; i += 2) {
                // Skip a stripe
                const int linesToSkip = SkTMin(stripeHeight, height - i * stripeHeight);
                codec->skipScanlines(linesToSkip);

                // Read a stripe
                const int startY = (i + 1) * stripeHeight;
                const int linesToRead = SkTMin(stripeHeight, height - startY);
                if (linesToRead > 0) {
                    codec->getScanlines(bitmap.getAddr(0, startY), linesToRead, bitmap.rowBytes());
                }
            }

            // Decode even stripes
            const SkCodec::Result startResult = codec->startScanlineDecode(decodeInfo, nullptr,
                    colorPtr, colorCountPtr);
            if (SkCodec::kSuccess != startResult) {
                return "Failed to restart scanline decoder with same parameters.";
            }
            for (int i = 0; i < numStripes; i += 2) {
                // Read a stripe
                const int startY = i * stripeHeight;
                const int linesToRead = SkTMin(stripeHeight, height - startY);
                codec->getScanlines(bitmap.getAddr(0, startY), linesToRead, bitmap.rowBytes());

                // Skip a stripe
                const int linesToSkip = SkTMin(stripeHeight, height - (i + 1) * stripeHeight);
                if (linesToSkip > 0) {
                    codec->skipScanlines(linesToSkip);
                }
            }
            canvas->drawBitmap(bitmap, 0, 0);
            break;
        }
        case kSubset_Mode: {
            // Arbitrarily choose a divisor.
            int divisor = 2;
            // Total width/height of the image.
            const int W = codec->getInfo().width();
            const int H = codec->getInfo().height();
            if (divisor > W || divisor > H) {
                return Error::Nonfatal(SkStringPrintf("Cannot codec subset: divisor %d is too big "
                                                      "for %s with dimensions (%d x %d)", divisor,
                                                      fPath.c_str(), W, H));
            }
            // subset dimensions
            // SkWebpCodec, the only one that supports subsets, requires even top/left boundaries.
            const int w = SkAlign2(W / divisor);
            const int h = SkAlign2(H / divisor);
            SkIRect subset;
            SkCodec::Options opts;
            opts.fSubset = &subset;
            SkBitmap subsetBm;
            // We will reuse pixel memory from bitmap.
            void* pixels = bitmap.getPixels();
            // Keep track of left and top (for drawing subsetBm into canvas). We could use
            // fScale * x and fScale * y, but we want integers such that the next subset will start
            // where the last one ended. So we'll add decodeInfo.width() and height().
            int left = 0;
            for (int x = 0; x < W; x += w) {
                int top = 0;
                for (int y = 0; y < H; y+= h) {
                    // Do not make the subset go off the edge of the image.
                    const int preScaleW = SkTMin(w, W - x);
                    const int preScaleH = SkTMin(h, H - y);
                    subset.setXYWH(x, y, preScaleW, preScaleH);
                    // And scale
                    // FIXME: Should we have a version of getScaledDimensions that takes a subset
                    // into account?
                    decodeInfo = decodeInfo.makeWH(
                            SkTMax(1, SkScalarRoundToInt(preScaleW * fScale)),
                            SkTMax(1, SkScalarRoundToInt(preScaleH * fScale)));
                    size_t rowBytes = decodeInfo.minRowBytes();
                    if (!subsetBm.installPixels(decodeInfo, pixels, rowBytes, colorTable.get(),
                                                nullptr, nullptr)) {
                        return SkStringPrintf("could not install pixels for %s.", fPath.c_str());
                    }
                    const SkCodec::Result result = codec->getPixels(decodeInfo, pixels, rowBytes,
                            &opts, colorPtr, colorCountPtr);
                    switch (result) {
                        case SkCodec::kSuccess:
                        case SkCodec::kIncompleteInput:
                            break;
                        case SkCodec::kInvalidConversion:
                            if (0 == (x|y)) {
                                // First subset is okay to return unimplemented.
                                return Error::Nonfatal("Incompatible colortype conversion");
                            }
                            // If the first subset succeeded, a later one should not fail.
                            // fall through to failure
                        case SkCodec::kUnimplemented:
                            if (0 == (x|y)) {
                                // First subset is okay to return unimplemented.
                                return Error::Nonfatal("subset codec not supported");
                            }
                            // If the first subset succeeded, why would a later one fail?
                            // fall through to failure
                        default:
                            return SkStringPrintf("subset codec failed to decode (%d, %d, %d, %d) "
                                                  "from %s with dimensions (%d x %d)\t error %d",
                                                  x, y, decodeInfo.width(), decodeInfo.height(),
                                                  fPath.c_str(), W, H, result);
                    }
                    canvas->drawBitmap(subsetBm, SkIntToScalar(left), SkIntToScalar(top));
                    // translate by the scaled height.
                    top += decodeInfo.height();
                }
                // translate by the scaled width.
                left += decodeInfo.width();
            }
            return "";
        }
    }
    return "";
}

SkISize CodecSrc::size() const {
    SkAutoTUnref<SkData> encoded(SkData::NewFromFileName(fPath.c_str()));
    SkAutoTDelete<SkCodec> codec(nullptr);

    if (kScaledCodec_Mode == fMode) {
        codec.reset(SkScaledCodec::NewFromData(encoded));
    } else {
        codec.reset(SkCodec::NewFromData(encoded));
    }

    if (nullptr == codec) {
        return SkISize::Make(0, 0);
    }
    return codec->getScaledDimensions(fScale);
}

Name CodecSrc::name() const {
    if (1.0f == fScale) {
        return SkOSPath::Basename(fPath.c_str());
    }
    return get_scaled_name(fPath, fScale);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ImageSrc::ImageSrc(Path path, int divisor) : fPath(path), fDivisor(divisor) {}

bool ImageSrc::veto(SinkFlags flags) const {
    // No need to test decoding to non-raster or indirect backend.
    // TODO: Instead, use lazy decoding to allow the GPU to handle cases like YUV.
    return flags.type != SinkFlags::kRaster
        || flags.approach != SinkFlags::kDirect;
}

Error ImageSrc::draw(SkCanvas* canvas) const {
    SkAutoTUnref<SkData> encoded(SkData::NewFromFileName(fPath.c_str()));
    if (!encoded) {
        return SkStringPrintf("Couldn't read %s.", fPath.c_str());
    }
    const SkColorType dstColorType = canvas->imageInfo().colorType();
    if (fDivisor == 0) {
        // Decode the full image.
        SkBitmap bitmap;
        if (!SkImageDecoder::DecodeMemory(encoded->data(), encoded->size(), &bitmap,
                                          dstColorType, SkImageDecoder::kDecodePixels_Mode)) {
            return SkStringPrintf("Couldn't decode %s.", fPath.c_str());
        }
        if (kRGB_565_SkColorType == dstColorType && !bitmap.isOpaque()) {
            // Do not draw a bitmap with alpha to a destination without alpha.
            return Error::Nonfatal("Uninteresting to decode image with alpha into 565.");
        }
        encoded.reset((SkData*)nullptr);  // Might as well drop this when we're done with it.
        canvas->drawBitmap(bitmap, 0,0);
        return "";
    }
    // Decode subsets.  This is a little involved.
    SkAutoTDelete<SkMemoryStream> stream(new SkMemoryStream(encoded));
    SkAutoTDelete<SkImageDecoder> decoder(SkImageDecoder::Factory(stream.get()));
    if (!decoder) {
        return SkStringPrintf("Can't find a good decoder for %s.", fPath.c_str());
    }
    stream->rewind();
    int w,h;
    if (!decoder->buildTileIndex(stream.detach(), &w, &h)) {
        return Error::Nonfatal("Subset decoding not supported.");
    }

    // Divide the image into subsets that cover the entire image.
    if (fDivisor > w || fDivisor > h) {
        return Error::Nonfatal(SkStringPrintf("Cannot decode subset: divisor %d is too big"
                "for %s with dimensions (%d x %d)", fDivisor, fPath.c_str(), w, h));
    }
    const int subsetWidth  = w / fDivisor,
              subsetHeight = h / fDivisor;
    for (int y = 0; y < h; y += subsetHeight) {
        for (int x = 0; x < w; x += subsetWidth) {
            SkBitmap subset;
            SkIRect rect = SkIRect::MakeXYWH(x, y, subsetWidth, subsetHeight);
            if (!decoder->decodeSubset(&subset, rect, dstColorType)) {
                return SkStringPrintf("Could not decode subset (%d, %d, %d, %d).",
                                      x, y, x+subsetWidth, y+subsetHeight);
            }
            if (kRGB_565_SkColorType == dstColorType && !subset.isOpaque()) {
                // Do not draw a bitmap with alpha to a destination without alpha.
                // This is not an error, but there is nothing interesting to show.

                // This should only happen on the first iteration through the loop.
                SkASSERT(0 == x && 0 == y);

                return Error::Nonfatal("Uninteresting to decode image with alpha into 565.");
            }
            canvas->drawBitmap(subset, SkIntToScalar(x), SkIntToScalar(y));
        }
    }
    return "";
}

SkISize ImageSrc::size() const {
    SkAutoTUnref<SkData> encoded(SkData::NewFromFileName(fPath.c_str()));
    SkBitmap bitmap;
    if (!encoded || !SkImageDecoder::DecodeMemory(encoded->data(),
                                                  encoded->size(),
                                                  &bitmap,
                                                  kUnknown_SkColorType,
                                                  SkImageDecoder::kDecodeBounds_Mode)) {
        return SkISize::Make(0,0);
    }
    return bitmap.dimensions();
}

Name ImageSrc::name() const {
    return SkOSPath::Basename(fPath.c_str());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const SkRect kSKPViewport = {0,0, 1000,1000};

SKPSrc::SKPSrc(Path path) : fPath(path) {}

Error SKPSrc::draw(SkCanvas* canvas) const {
    SkAutoTDelete<SkStream> stream(SkStream::NewFromFile(fPath.c_str()));
    if (!stream) {
        return SkStringPrintf("Couldn't read %s.", fPath.c_str());
    }
    SkAutoTUnref<SkPicture> pic(SkPicture::CreateFromStream(stream, &lazy_decode_bitmap));
    if (!pic) {
        return SkStringPrintf("Couldn't decode %s as a picture.", fPath.c_str());
    }
    stream.reset((SkStream*)nullptr);  // Might as well drop this when we're done with it.

    canvas->clipRect(kSKPViewport);
    canvas->drawPicture(pic);
    return "";
}

SkISize SKPSrc::size() const {
    SkAutoTDelete<SkStream> stream(SkStream::NewFromFile(fPath.c_str()));
    if (!stream) {
        return SkISize::Make(0,0);
    }
    SkPictInfo info;
    if (!SkPicture::InternalOnly_StreamIsSKP(stream, &info)) {
        return SkISize::Make(0,0);
    }
    SkRect viewport = kSKPViewport;
    if (!viewport.intersect(info.fCullRect)) {
        return SkISize::Make(0,0);
    }
    return viewport.roundOut().size();
}

Name SKPSrc::name() const { return SkOSPath::Basename(fPath.c_str()); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Error NullSink::draw(const Src& src, SkBitmap*, SkWStream*, SkString*) const {
    SkAutoTDelete<SkCanvas> canvas(SkCreateNullCanvas());
    return src.draw(canvas);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

DEFINE_bool(gpuStats, false, "Append GPU stats to the log for each GPU task?");

GPUSink::GPUSink(GrContextFactory::GLContextType ct,
                 GrGLStandard api,
                 int samples,
                 bool diText,
                 bool threaded)
    : fContextType(ct)
    , fGpuAPI(api)
    , fSampleCount(samples)
    , fUseDIText(diText)
    , fThreaded(threaded) {}

int GPUSink::enclave() const {
    return fThreaded ? kAnyThread_Enclave : kGPU_Enclave;
}

void PreAbandonGpuContextErrorHandler(SkError, void*) {}

Error GPUSink::draw(const Src& src, SkBitmap* dst, SkWStream*, SkString* log) const {
    GrContextOptions options;
    src.modifyGrContextOptions(&options);

    GrContextFactory factory(options);
    const SkISize size = src.size();
    const SkImageInfo info =
        SkImageInfo::Make(size.width(), size.height(), kN32_SkColorType, kPremul_SkAlphaType);
    SkAutoTUnref<SkSurface> surface(
            NewGpuSurface(&factory, fContextType, fGpuAPI, info, fSampleCount, fUseDIText));
    if (!surface) {
        return "Could not create a surface.";
    }
    if (FLAGS_preAbandonGpuContext) {
        SkSetErrorCallback(&PreAbandonGpuContextErrorHandler, nullptr);
        factory.abandonContexts();
    }
    SkCanvas* canvas = surface->getCanvas();
    Error err = src.draw(canvas);
    if (!err.isEmpty()) {
        return err;
    }
    canvas->flush();
    if (FLAGS_gpuStats) {
        canvas->getGrContext()->dumpCacheStats(log);
        canvas->getGrContext()->dumpGpuStats(log);
    }
    dst->allocPixels(info);
    canvas->readPixels(dst, 0, 0);
    if (FLAGS_abandonGpuContext) {
        factory.abandonContexts();
    }
    return "";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Error draw_skdocument(const Src& src, SkDocument* doc, SkWStream* dst) {
    // Print the given DM:Src to a document, breaking on 8.5x11 pages.
    SkASSERT(doc);
    int width  = src.size().width(),
        height = src.size().height();

    if (FLAGS_multiPage) {
        const int kLetterWidth = 612,  // 8.5 * 72
                kLetterHeight = 792;   // 11 * 72
        const SkRect letter = SkRect::MakeWH(SkIntToScalar(kLetterWidth),
                                             SkIntToScalar(kLetterHeight));

        int xPages = ((width - 1) / kLetterWidth) + 1;
        int yPages = ((height - 1) / kLetterHeight) + 1;

        for (int y = 0; y < yPages; ++y) {
            for (int x = 0; x < xPages; ++x) {
                int w = SkTMin(kLetterWidth, width - (x * kLetterWidth));
                int h = SkTMin(kLetterHeight, height - (y * kLetterHeight));
                SkCanvas* canvas =
                        doc->beginPage(SkIntToScalar(w), SkIntToScalar(h));
                if (!canvas) {
                    return "SkDocument::beginPage(w,h) returned nullptr";
                }
                canvas->clipRect(letter);
                canvas->translate(-letter.width() * x, -letter.height() * y);
                Error err = src.draw(canvas);
                if (!err.isEmpty()) {
                    return err;
                }
                doc->endPage();
            }
        }
    } else {
        SkCanvas* canvas =
                doc->beginPage(SkIntToScalar(width), SkIntToScalar(height));
        if (!canvas) {
            return "SkDocument::beginPage(w,h) returned nullptr";
        }
        Error err = src.draw(canvas);
        if (!err.isEmpty()) {
            return err;
        }
        doc->endPage();
    }
    if (!doc->close()) {
        return "SkDocument::close() returned false";
    }
    dst->flush();
    return "";
}

PDFSink::PDFSink(const char* rasterizer) : fRasterizer(rasterizer) {}

Error PDFSink::draw(const Src& src, SkBitmap*, SkWStream* dst, SkString*) const {
    SkAutoTUnref<SkDocument> doc(SkDocument::CreatePDF(dst));
    if (!doc) {
        return "SkDocument::CreatePDF() returned nullptr";
    }
    SkTArray<SkDocument::Attribute> info;
    info.emplace_back(SkString("Title"), src.name());
    info.emplace_back(SkString("Subject"),
                      SkString("rendering correctness test"));
    info.emplace_back(SkString("Creator"), SkString("Skia/DM"));

    info.emplace_back(SkString("Keywords"),
                      SkStringPrintf("Rasterizer:%s;", fRasterizer));
    doc->setMetadata(info, nullptr, nullptr);
    return draw_skdocument(src, doc.get(), dst);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

XPSSink::XPSSink() {}

Error XPSSink::draw(const Src& src, SkBitmap*, SkWStream* dst, SkString*) const {
    SkAutoTUnref<SkDocument> doc(SkDocument::CreateXPS(dst));
    if (!doc) {
        return "SkDocument::CreateXPS() returned nullptr";
    }
    return draw_skdocument(src, doc.get(), dst);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SKPSink::SKPSink() {}

Error SKPSink::draw(const Src& src, SkBitmap*, SkWStream* dst, SkString*) const {
    SkSize size;
    size = src.size();
    SkPictureRecorder recorder;
    Error err = src.draw(recorder.beginRecording(size.width(), size.height()));
    if (!err.isEmpty()) {
        return err;
    }
    SkAutoTUnref<SkPicture> pic(recorder.endRecording());
    pic->serialize(dst);
    return "";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SVGSink::SVGSink() {}

Error SVGSink::draw(const Src& src, SkBitmap*, SkWStream* dst, SkString*) const {
    SkAutoTDelete<SkXMLWriter> xmlWriter(new SkXMLStreamWriter(dst));
    SkAutoTUnref<SkCanvas> canvas(SkSVGCanvas::Create(
        SkRect::MakeWH(SkIntToScalar(src.size().width()), SkIntToScalar(src.size().height())),
        xmlWriter));
    return src.draw(canvas);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

RasterSink::RasterSink(SkColorType colorType) : fColorType(colorType) {}

Error RasterSink::draw(const Src& src, SkBitmap* dst, SkWStream*, SkString*) const {
    const SkISize size = src.size();
    // If there's an appropriate alpha type for this color type, use it, otherwise use premul.
    SkAlphaType alphaType = kPremul_SkAlphaType;
    (void)SkColorTypeValidateAlphaType(fColorType, alphaType, &alphaType);

    dst->allocPixels(SkImageInfo::Make(size.width(), size.height(), fColorType, alphaType));
    dst->eraseColor(SK_ColorTRANSPARENT);
    SkCanvas canvas(*dst);
    return src.draw(&canvas);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Handy for front-patching a Src.  Do whatever up-front work you need, then call draw_to_canvas(),
// passing the Sink draw() arguments, a size, and a function draws into an SkCanvas.
// Several examples below.

static Error draw_to_canvas(Sink* sink, SkBitmap* bitmap, SkWStream* stream, SkString* log,
                            SkISize size, SkFunction<Error(SkCanvas*)> draw) {
    class ProxySrc : public Src {
    public:
        ProxySrc(SkISize size, SkFunction<Error(SkCanvas*)> draw) : fSize(size), fDraw(draw) {}
        Error   draw(SkCanvas* canvas) const override { return fDraw(canvas); }
        Name                    name() const override { sk_throw(); return ""; } // Won't be called.
        SkISize                 size() const override { return fSize; }
    private:
        SkISize                      fSize;
        SkFunction<Error(SkCanvas*)> fDraw;
    };
    return sink->draw(ProxySrc(size, draw), bitmap, stream, log);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static SkISize auto_compute_translate(SkMatrix* matrix, int srcW, int srcH) {
    SkRect bounds = SkRect::MakeIWH(srcW, srcH);
    matrix->mapRect(&bounds);
    matrix->postTranslate(-bounds.x(), -bounds.y());
    return SkISize::Make(SkScalarRoundToInt(bounds.width()), SkScalarRoundToInt(bounds.height()));
}

ViaMatrix::ViaMatrix(SkMatrix matrix, Sink* sink) : Via(sink), fMatrix(matrix) {}

Error ViaMatrix::draw(const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    SkMatrix matrix = fMatrix;
    SkISize size = auto_compute_translate(&matrix, src.size().width(), src.size().height());
    return draw_to_canvas(fSink, bitmap, stream, log, size, [&](SkCanvas* canvas) {
        canvas->concat(matrix);
        return src.draw(canvas);
    });
}

// Undoes any flip or 90 degree rotate without changing the scale of the bitmap.
// This should be pixel-preserving.
ViaUpright::ViaUpright(SkMatrix matrix, Sink* sink) : Via(sink), fMatrix(matrix) {}

Error ViaUpright::draw(const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    Error err = fSink->draw(src, bitmap, stream, log);
    if (!err.isEmpty()) {
        return err;
    }

    SkMatrix inverse;
    if (!fMatrix.rectStaysRect() || !fMatrix.invert(&inverse)) {
        return "Cannot upright --matrix.";
    }
    SkMatrix upright = SkMatrix::I();
    upright.setScaleX(SkScalarSignAsScalar(inverse.getScaleX()));
    upright.setScaleY(SkScalarSignAsScalar(inverse.getScaleY()));
    upright.setSkewX(SkScalarSignAsScalar(inverse.getSkewX()));
    upright.setSkewY(SkScalarSignAsScalar(inverse.getSkewY()));

    SkBitmap uprighted;
    SkISize size = auto_compute_translate(&upright, bitmap->width(), bitmap->height());
    uprighted.allocPixels(bitmap->info().makeWH(size.width(), size.height()));

    SkCanvas canvas(uprighted);
    canvas.concat(upright);
    SkPaint paint;
    paint.setXfermodeMode(SkXfermode::kSrc_Mode);
    canvas.drawBitmap(*bitmap, 0, 0, &paint);

    *bitmap = uprighted;
    bitmap->lockPixels();
    return "";
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Error ViaPipe::draw(const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    auto size = src.size();
    return draw_to_canvas(fSink, bitmap, stream, log, size, [&](SkCanvas* canvas) {
        PipeController controller(canvas, &SkImageDecoder::DecodeMemory);
        SkGPipeWriter pipe;
        const uint32_t kFlags = 0;
        return src.draw(pipe.startRecording(&controller, kFlags, size.width(), size.height()));
    });
}

Error ViaRemote::draw(const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    return draw_to_canvas(fSink, bitmap, stream, log, src.size(), [&](SkCanvas* canvas) {
        SkAutoTDelete<SkRemote::Cache> cache(fCache ? SkRemote::Cache::CreateAlwaysCache()
                                                    : SkRemote::Cache::CreateNeverCache());
        SkRemote::Server server(canvas);
        SkRemote::Client client(cache, &server);
        return src.draw(&client);
    });
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Error ViaSerialization::draw(
        const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    // Record our Src into a picture.
    auto size = src.size();
    SkPictureRecorder recorder;
    Error err = src.draw(recorder.beginRecording(SkIntToScalar(size.width()),
                                                 SkIntToScalar(size.height())));
    if (!err.isEmpty()) {
        return err;
    }
    SkAutoTUnref<SkPicture> pic(recorder.endRecording());

    // Serialize it and then deserialize it.
    SkDynamicMemoryWStream wStream;
    pic->serialize(&wStream);
    SkAutoTDelete<SkStream> rStream(wStream.detachAsStream());
    SkAutoTUnref<SkPicture> deserialized(SkPicture::CreateFromStream(rStream, &lazy_decode_bitmap));

    return draw_to_canvas(fSink, bitmap, stream, log, size, [&](SkCanvas* canvas) {
        canvas->drawPicture(deserialized);
        return "";
    });
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ViaTiles::ViaTiles(int w, int h, SkBBHFactory* factory, Sink* sink)
    : Via(sink)
    , fW(w)
    , fH(h)
    , fFactory(factory) {}

Error ViaTiles::draw(const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    auto size = src.size();
    SkPictureRecorder recorder;
    Error err = src.draw(recorder.beginRecording(SkIntToScalar(size.width()),
                                                 SkIntToScalar(size.height()),
                                                 fFactory.get()));
    if (!err.isEmpty()) {
        return err;
    }
    SkAutoTUnref<SkPicture> pic(recorder.endRecordingAsPicture());

    return draw_to_canvas(fSink, bitmap, stream, log, src.size(), [&](SkCanvas* canvas) {
        const int xTiles = (size.width()  + fW - 1) / fW,
                  yTiles = (size.height() + fH - 1) / fH;
        SkMultiPictureDraw mpd(xTiles*yTiles);
        SkTDArray<SkSurface*> surfaces;
        surfaces.setReserve(xTiles*yTiles);

        SkImageInfo info = canvas->imageInfo().makeWH(fW, fH);
        for (int j = 0; j < yTiles; j++) {
            for (int i = 0; i < xTiles; i++) {
                // This lets our ultimate Sink determine the best kind of surface.
                // E.g., if it's a GpuSink, the surfaces and images are textures.
                SkSurface* s = canvas->newSurface(info);
                if (!s) {
                    s = SkSurface::NewRaster(info);  // Some canvases can't create surfaces.
                }
                surfaces.push(s);
                SkCanvas* c = s->getCanvas();
                c->translate(SkIntToScalar(-i * fW),
                             SkIntToScalar(-j * fH));  // Line up the canvas with this tile.
                mpd.add(c, pic);
            }
        }
        mpd.draw();
        for (int j = 0; j < yTiles; j++) {
            for (int i = 0; i < xTiles; i++) {
                SkAutoTUnref<SkImage> image(surfaces[i+xTiles*j]->newImageSnapshot());
                canvas->drawImage(image, SkIntToScalar(i*fW), SkIntToScalar(j*fH));
            }
        }
        surfaces.unrefAll();
        return "";
    });
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Draw the Src into two pictures, then draw the second picture into the wrapped Sink.
// This tests that any shortcuts we may take while recording that second picture are legal.
Error ViaSecondPicture::draw(
        const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    auto size = src.size();
    return draw_to_canvas(fSink, bitmap, stream, log, size, [&](SkCanvas* canvas) -> Error {
        SkPictureRecorder recorder;
        SkAutoTUnref<SkPicture> pic;
        for (int i = 0; i < 2; i++) {
            Error err = src.draw(recorder.beginRecording(SkIntToScalar(size.width()),
                                                         SkIntToScalar(size.height())));
            if (!err.isEmpty()) {
                return err;
            }
            pic.reset(recorder.endRecordingAsPicture());
        }
        canvas->drawPicture(pic);
        return "";
    });
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Draw the Src twice.  This can help exercise caching.
Error ViaTwice::draw(const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    return draw_to_canvas(fSink, bitmap, stream, log, src.size(), [&](SkCanvas* canvas) -> Error {
        for (int i = 0; i < 2; i++) {
            SkAutoCanvasRestore acr(canvas, true/*save now*/);
            canvas->clear(SK_ColorTRANSPARENT);
            Error err = src.draw(canvas);
            if (err.isEmpty()) {
                return err;
            }
        }
        return "";
    });
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// This is like SkRecords::Draw, in that it plays back SkRecords ops into a Canvas.
// Unlike SkRecords::Draw, it builds a single-op sub-picture out of each Draw-type op.
// This is an only-slightly-exaggerated simluation of Blink's Slimming Paint pictures.
struct DrawsAsSingletonPictures {
    SkCanvas* fCanvas;
    const SkDrawableList& fDrawables;

    template <typename T>
    void draw(const T& op, SkCanvas* canvas) {
        // We must pass SkMatrix::I() as our initial matrix.
        // By default SkRecords::Draw() uses the canvas' matrix as its initial matrix,
        // which would have the funky effect of applying transforms over and over.
        SkRecords::Draw d(canvas, nullptr, fDrawables.begin(), fDrawables.count(), &SkMatrix::I());
        d(op);
    }

    // Draws get their own picture.
    template <typename T>
    SK_WHEN(T::kTags & SkRecords::kDraw_Tag, void) operator()(const T& op) {
        SkPictureRecorder rec;
        this->draw(op, rec.beginRecording(SkRect::MakeLargest()));
        SkAutoTUnref<SkPicture> pic(rec.endRecordingAsPicture());
        fCanvas->drawPicture(pic);
    }

    // We'll just issue non-draws directly.
    template <typename T>
    skstd::enable_if_t<!(T::kTags & SkRecords::kDraw_Tag), void> operator()(const T& op) {
        this->draw(op, fCanvas);
    }
};

// Record Src into a picture, then record it into a macro picture with a sub-picture for each draw.
// Then play back that macro picture into our wrapped sink.
Error ViaSingletonPictures::draw(
        const Src& src, SkBitmap* bitmap, SkWStream* stream, SkString* log) const {
    auto size = src.size();
    return draw_to_canvas(fSink, bitmap, stream, log, size, [&](SkCanvas* canvas) -> Error {
        // Use low-level (Skia-private) recording APIs so we can read the SkRecord.
        SkRecord skr;
        SkRecorder recorder(&skr, size.width(), size.height());
        Error err = src.draw(&recorder);
        if (!err.isEmpty()) {
            return err;
        }

        // Record our macro-picture, with each draw op as its own sub-picture.
        SkPictureRecorder macroRec;
        SkCanvas* macroCanvas = macroRec.beginRecording(SkIntToScalar(size.width()),
                                                        SkIntToScalar(size.height()));

        SkAutoTDelete<SkDrawableList> drawables(recorder.detachDrawableList());
        const SkDrawableList empty;

        DrawsAsSingletonPictures drawsAsSingletonPictures = {
            macroCanvas,
            drawables ? *drawables : empty,
        };
        for (int i = 0; i < skr.count(); i++) {
            skr.visit<void>(i, drawsAsSingletonPictures);
        }
        SkAutoTUnref<SkPicture> macroPic(macroRec.endRecordingAsPicture());

        canvas->drawPicture(macroPic);
        return "";
    });
}

}  // namespace DM
