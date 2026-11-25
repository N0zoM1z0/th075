#include "graphics/TextureEntry.hpp"
#include "assets/TexturePackRecord.hpp"
#include <string.h>

void TextureEntryStorageF769::LoadSerialized(const TexturePackRecord* record) {
    storedWidth = record->width;
    storedHeight = record->height;
    stridePixels = record->stridePixels;
    bitsPerPixel = record->bitsPerPixel;
    compressedBytes = record->compressedBytes;
    if (compressedBytes > 0) {
        pixels = new BYTE[compressedBytes];
        memcpy(pixels, record->pixelData, compressedBytes);
    } else if (bitsPerPixel >= 24) {
        pixels = new BYTE[stridePixels * storedHeight * 4];
        memcpy(pixels, record->pixelData, stridePixels * storedHeight * 4);
    } else {
        pixels = new BYTE[(stridePixels * storedHeight * bitsPerPixel) >> 3];
        memcpy(pixels, record->pixelData, (stridePixels * storedHeight * bitsPerPixel) >> 3);
    }
}
