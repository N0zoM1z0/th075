#include "graphics/TextureManagerBorrowedF925.hpp"
#include "assets/TexturePack40BF60.hpp"
#include <string.h>

void TextureEntryStorageF769::LoadSerialized(const TextureRecordSnapshot40BF60* record) {
    storedWidth = record->width;
    storedHeight = record->height;
    storedStride = record->stride;
    uploadFormat = record->depth;
    encodedSize = record->encodedSize;
    if (encodedSize > 0) {
        pixels = new BYTE[encodedSize];
        memcpy(pixels, record->data, encodedSize);
    } else if (uploadFormat >= 24) {
        pixels = new BYTE[storedStride * storedHeight * 4];
        memcpy(pixels, record->data, storedStride * storedHeight * 4);
    } else {
        pixels = new BYTE[(storedStride * storedHeight * uploadFormat) >> 3];
        memcpy(pixels, record->data, (storedStride * storedHeight * uploadFormat) >> 3);
    }
}
