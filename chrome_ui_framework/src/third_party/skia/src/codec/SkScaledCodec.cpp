/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkCodecPriv.h"
#include "SkScaledCodec.h"
#include "SkStream.h"
#include "SkWebpCodec.h"


SkCodec* SkScaledCodec::NewFromStream(SkStream* stream) {
    SkAutoTDelete<SkCodec> codec(SkCodec::NewFromStream(stream));
    if (nullptr == codec) {
        return nullptr;
    }

    switch (codec->getEncodedFormat()) {
        case kWEBP_SkEncodedFormat:
            // Webp codec supports scaling and subsetting natively
            return codec.detach();
        case kPNG_SkEncodedFormat:
        case kJPEG_SkEncodedFormat:
            // wrap in new SkScaledCodec
            return new SkScaledCodec(codec.detach());
        default:
            // FIXME: SkScaledCodec is temporarily disabled for other formats
            // while focusing on the formats that are supported by
            // BitmapRegionDecoder.
            return nullptr;
    }
}

SkCodec* SkScaledCodec::NewFromData(SkData* data) {
    if (!data) {
        return nullptr;
    }
    return NewFromStream(new SkMemoryStream(data));
}

SkScaledCodec::SkScaledCodec(SkCodec* codec)
    : INHERITED(codec->getInfo(), nullptr)
    , fCodec(codec)
{}

SkScaledCodec::~SkScaledCodec() {}

bool SkScaledCodec::onRewind() {
    return fCodec->onRewind();
}

static SkISize best_scaled_dimensions(const SkISize& origDims, const SkISize& nativeDims,
                                      const SkISize& scaledCodecDims, float desiredScale) {
    if (nativeDims == scaledCodecDims) {
        // does not matter which to return if equal. Return here to skip below calculations
        return nativeDims;
    }
    float idealWidth = origDims.width() * desiredScale;
    float idealHeight = origDims.height() * desiredScale;

    // calculate difference between native dimensions and ideal dimensions
    float nativeWDiff = SkTAbs(idealWidth - nativeDims.width());
    float nativeHDiff = SkTAbs(idealHeight - nativeDims.height());
    float nativeDiff = nativeWDiff + nativeHDiff;

    // Native scaling is preferred to sampling.  If we can scale natively to
    // within one of the ideal value, we should choose to scale natively.
    if (nativeWDiff < 1.0f && nativeHDiff < 1.0f) {
        return nativeDims;
    }

    // calculate difference between scaledCodec dimensions and ideal dimensions
    float scaledCodecWDiff = SkTAbs(idealWidth - scaledCodecDims.width());
    float scaledCodecHDiff = SkTAbs(idealHeight - scaledCodecDims.height());
    float scaledCodecDiff = scaledCodecWDiff + scaledCodecHDiff;

    // return dimensions closest to ideal dimensions.
    // If the differences are equal, return nativeDims, as native scaling is more efficient.
    return nativeDiff > scaledCodecDiff ? scaledCodecDims : nativeDims;
}

/*
 * Return a valid set of output dimensions for this decoder, given an input scale
 */
SkISize SkScaledCodec::onGetScaledDimensions(float desiredScale) const {
    SkISize nativeDimensions = fCodec->getScaledDimensions(desiredScale);
    // support scaling down by integer numbers. Ex: 1/2, 1/3, 1/4 ...
    SkISize scaledCodecDimensions;
    if (desiredScale > 0.5f) {
        // sampleSize = 1
        scaledCodecDimensions = fCodec->getInfo().dimensions();
    }
    // sampleSize determines the step size between samples
    // Ex: sampleSize = 2, sample every second pixel in x and y directions
    int sampleSize = int ((1.0f / desiredScale) + 0.5f);

    int scaledWidth = get_scaled_dimension(this->getInfo().width(), sampleSize);
    int scaledHeight = get_scaled_dimension(this->getInfo().height(), sampleSize);

    // Return the calculated output dimensions for the given scale
    scaledCodecDimensions = SkISize::Make(scaledWidth, scaledHeight);

    return best_scaled_dimensions(this->getInfo().dimensions(), nativeDimensions,
                                  scaledCodecDimensions, desiredScale);
}

// check if scaling to dstInfo size from srcInfo size using sampleSize is possible
static bool scaling_supported(const SkISize& dstDim, const SkISize& srcDim,
                              int* sampleX, int* sampleY) {
    SkScaledCodec::ComputeSampleSize(dstDim, srcDim, sampleX, sampleY);
    const int dstWidth = dstDim.width();
    const int dstHeight = dstDim.height();
    const int srcWidth = srcDim.width();
    const int srcHeight = srcDim.height();
     // only support down sampling, not up sampling
    if (dstWidth > srcWidth || dstHeight  > srcHeight) {
        return false;
    }
    // check that srcWidth is scaled down by an integer value
    if (get_scaled_dimension(srcWidth, *sampleX) != dstWidth) {
        return false;
    }
    // check that src height is scaled down by an integer value
    if (get_scaled_dimension(srcHeight, *sampleY) != dstHeight) {
        return false;
    }
    // sampleX and sampleY should be equal unless the original sampleSize requested was larger
    // than srcWidth or srcHeight. If so, the result of this is dstWidth or dstHeight = 1.
    // This functionality allows for tall thin images to still be scaled down by scaling factors.
    if (*sampleX != *sampleY){
        if (1 != dstWidth && 1 != dstHeight) {
            return false;
        }
    }
    return true;
}

bool SkScaledCodec::onDimensionsSupported(const SkISize& dim) {
    // Check with fCodec first. No need to call the non-virtual version, which
    // just checks if it matches the original, since a match means this method
    // will not be called.
    if (fCodec->onDimensionsSupported(dim)) {
        return true;
    }

    // FIXME: These variables are unused, but are needed by scaling_supported.
    // This class could also cache these values, and avoid calling this in
    // onGetPixels (since getPixels already calls it).
    int sampleX;
    int sampleY;
    return scaling_supported(dim, this->getInfo().dimensions(), &sampleX, &sampleY);
}

// calculates sampleSize in x and y direction
void SkScaledCodec::ComputeSampleSize(const SkISize& dstDim, const SkISize& srcDim,
                                      int* sampleXPtr, int* sampleYPtr) {
    int srcWidth = srcDim.width();
    int dstWidth = dstDim.width();
    int srcHeight = srcDim.height();
    int dstHeight = dstDim.height();

    int sampleX = srcWidth / dstWidth;
    int sampleY = srcHeight / dstHeight;

    // only support down sampling, not up sampling
    SkASSERT(dstWidth <= srcWidth);
    SkASSERT(dstHeight <= srcHeight);

    // sampleX and sampleY should be equal unless the original sampleSize requested was
    // larger than srcWidth or srcHeight.
    // If so, the result of this is dstWidth or dstHeight = 1. This functionality
    // allows for tall thin images to still be scaled down by scaling factors.

    if (sampleX != sampleY){
        if (1 != dstWidth && 1 != dstHeight) {

            // rounding during onGetScaledDimensions can cause different sampleSizes
            // Ex: srcWidth = 79, srcHeight = 20, sampleSize = 10
            // dstWidth = 7, dstHeight = 2, sampleX = 79/7 = 11, sampleY = 20/2 = 10
            // correct for this rounding by comparing width to sampleY and height to sampleX

            if (get_scaled_dimension(srcWidth, sampleY) == dstWidth) {
                sampleX = sampleY;
            } else if (get_scaled_dimension(srcHeight, sampleX) == dstHeight) {
                sampleY = sampleX;
            }
        }
    }

    if (sampleXPtr) {
        *sampleXPtr = sampleX;
    }
    if (sampleYPtr) {
        *sampleYPtr = sampleY;
    }
}

// TODO: Implement subsetting in onGetPixels which works when and when not sampling 

SkCodec::Result SkScaledCodec::onGetPixels(const SkImageInfo& requestedInfo, void* dst,
                                           size_t rowBytes, const Options& options,
                                           SkPMColor ctable[], int* ctableCount,
                                           int* rowsDecoded) {

    if (options.fSubset) {
        // Subsets are not supported.
        return kUnimplemented;
    }

    if (fCodec->dimensionsSupported(requestedInfo.dimensions())) {
        // Make sure that the parent class does not fill on an incomplete decode, since
        // fCodec will take care of filling the uninitialized lines.
        *rowsDecoded = requestedInfo.height();
        return fCodec->getPixels(requestedInfo, dst, rowBytes, &options, ctable, ctableCount);
    }

    // scaling requested
    int sampleX;
    int sampleY;
    if (!scaling_supported(requestedInfo.dimensions(), fCodec->getInfo().dimensions(),
                           &sampleX, &sampleY)) {
        // onDimensionsSupported would have returned false, meaning we should never reach here.
        SkASSERT(false);
        return kInvalidScale;
    }

    // set first sample pixel in y direction
    const int Y0 = get_start_coord(sampleY);

    const int dstHeight = requestedInfo.height();
    const int srcWidth = fCodec->getInfo().width();
    const int srcHeight = fCodec->getInfo().height();

    const SkImageInfo info = requestedInfo.makeWH(srcWidth, srcHeight);

    Result result = fCodec->startScanlineDecode(info, &options, ctable, ctableCount);

    if (kSuccess != result) {
        return result;
    }

    SkSampler* sampler = fCodec->getSampler(true);
    if (!sampler) {
        return kUnimplemented;
    }

    if (sampler->setSampleX(sampleX) != requestedInfo.width()) {
        return kInvalidScale;
    }

    switch(fCodec->getScanlineOrder()) {
        case SkCodec::kTopDown_SkScanlineOrder: {
            if (!fCodec->skipScanlines(Y0)) {
                *rowsDecoded = 0;
                return kIncompleteInput;
            }
            for (int y = 0; y < dstHeight; y++) {
                if (1 != fCodec->getScanlines(dst, 1, rowBytes)) {
                    // The failed call to getScanlines() will take care of
                    // filling the failed row, so we indicate that we have
                    // decoded (y + 1) rows.
                    *rowsDecoded = y + 1;
                    return kIncompleteInput;
                }
                if (y < dstHeight - 1) {
                    if (!fCodec->skipScanlines(sampleY - 1)) {
                        *rowsDecoded = y + 1;
                        return kIncompleteInput;
                    }
                }
                dst = SkTAddOffset<void>(dst, rowBytes);
            }
            return kSuccess;
        }
        case SkCodec::kBottomUp_SkScanlineOrder:
        case SkCodec::kOutOfOrder_SkScanlineOrder: {
            Result result = kSuccess;
            int y;
            for (y = 0; y < srcHeight; y++) {
                int srcY = fCodec->nextScanline();
                if (is_coord_necessary(srcY, sampleY, dstHeight)) {
                    void* dstPtr = SkTAddOffset<void>(dst, rowBytes * get_dst_coord(srcY, sampleY));
                    if (1 != fCodec->getScanlines(dstPtr, 1, rowBytes)) {
                        result = kIncompleteInput;
                        break;
                    }
                } else {
                    if (!fCodec->skipScanlines(1)) {
                        result = kIncompleteInput;
                        break;
                    }
                }
            }

            // We handle filling uninitialized memory here instead of in the parent class.
            // The parent class does not know that we are sampling.
            if (kIncompleteInput == result) {
                const uint32_t fillValue = fCodec->getFillValue(requestedInfo.colorType(),
                        requestedInfo.alphaType());
                for (; y < srcHeight; y++) {
                    int srcY = fCodec->outputScanline(y);
                    if (is_coord_necessary(srcY, sampleY, dstHeight)) {
                        void* dstRow = SkTAddOffset<void>(dst,
                                rowBytes * get_dst_coord(srcY, sampleY));
                        SkSampler::Fill(requestedInfo.makeWH(requestedInfo.width(), 1), dstRow,
                                rowBytes, fillValue, options.fZeroInitialized);
                    }
                }
                *rowsDecoded = dstHeight;
            }
            return result;
        }
        case SkCodec::kNone_SkScanlineOrder: {
            SkAutoMalloc storage(srcHeight * rowBytes);
            uint8_t* storagePtr = static_cast<uint8_t*>(storage.get());
            int scanlines = fCodec->getScanlines(storagePtr, srcHeight, rowBytes);
            storagePtr += Y0 * rowBytes;
            scanlines -= Y0;
            int y = 0;
            while (y < dstHeight && scanlines > 0) {
                memcpy(dst, storagePtr, rowBytes);
                storagePtr += sampleY * rowBytes;
                dst = SkTAddOffset<void>(dst, rowBytes);
                scanlines -= sampleY;
                y++;
            }
            if (y < dstHeight) {
                // fCodec has already handled filling uninitialized memory.
                *rowsDecoded = dstHeight;
                return kIncompleteInput;
            }
            return kSuccess;
        }
        default:
            SkASSERT(false);
            return kUnimplemented;
    }
}

uint32_t SkScaledCodec::onGetFillValue(SkColorType colorType, SkAlphaType alphaType) const {
    return fCodec->onGetFillValue(colorType, alphaType);
}

SkCodec::SkScanlineOrder SkScaledCodec::onGetScanlineOrder() const {
    return fCodec->onGetScanlineOrder();
}
