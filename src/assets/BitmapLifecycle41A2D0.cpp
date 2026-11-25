#include "graphics/TextureManagerBorrowedF925.hpp"

TextureEntryStorageF769::TextureEntryStorageF769()
{
    uploadFormat = 0;
    pixels = 0;
    palette = 0;
    encodedSize = 0;
    ownsPalette = 0;
}

TextureEntryStorageF769::TextureEntryStorageF769(BYTE format)
{
    if (format != 8 && format != 16 && format != 24 && format != 32)
        uploadFormat = 0;
    else
        uploadFormat = format;
    pixels = 0;
    palette = 0;
    encodedSize = 0;
    ownsPalette = 0;
}

TextureEntryStorageF769::~TextureEntryStorageF769()
{
    if (pixels)
        delete[] pixels;
    if (ownsPalette)
        delete[] palette;
}

NativeTextureElementF769::NativeTextureElementF769()
{
}

NativeTextureElementF769::~NativeTextureElementF769()
{
}
