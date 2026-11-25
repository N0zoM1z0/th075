#include "graphics/TextureEntry.hpp"

TextureEntryStorageF769::TextureEntryStorageF769()
{
    bitsPerPixel = 0;
    pixels = 0;
    palette = 0;
    compressedBytes = 0;
    ownsPalette = 0;
}

TextureEntryStorageF769::TextureEntryStorageF769(BYTE format)
{
    if (format != 8 && format != 16 && format != 24 && format != 32)
        bitsPerPixel = 0;
    else
        bitsPerPixel = format;
    pixels = 0;
    palette = 0;
    compressedBytes = 0;
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
