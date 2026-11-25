#include "graphics/GraphicsTexture.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "assets/TexturePackRecord.hpp"
#include <new>

#define ENTRY entries[index]

void TextureManagerF198::LoadPackFileDefaultPalette(const char* filename) {
    LoadPackFile(filename, 0);
}

void TextureManagerF198::LoadPackFile(const char* filename, signed char selectedPalette) {
    int nEntriesCount = entries.size();
    HANDLE sourceFile = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL, 0);
    int index;
    TexturePackRecord record;
    DWORD dwRead;
    signed char paletteHeaderCount;
    if (sourceFile == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(sourceFile, 0, 0, FILE_BEGIN);
    ReadFile(sourceFile, &paletteHeaderCount, 1, &dwRead, 0);
    if (palette)
        delete[] palette;
    if (paletteHeaderCount > 0) {
        palette = new WORD[256];
        if (selectedPalette <= paletteHeaderCount) {
            SetFilePointer(sourceFile, (selectedPalette - 1) * 512, 0, FILE_CURRENT);
            ReadFile(sourceFile, palette, 512, &dwRead, 0);
            SetFilePointer(sourceFile, (paletteHeaderCount - selectedPalette) * 512, 0, FILE_CURRENT);
        } else {
            ReadFile(sourceFile, palette, 512, &dwRead, 0);
            SetFilePointer(sourceFile, (paletteHeaderCount - 1) * 512, 0, FILE_CURRENT);
        }
    } else {
        palette = 0;
    }
    for (index = 0; index < nEntriesCount; index++) {
        ENTRY.bitsPerPixel = textureDepth;
        ENTRY.palette = palette;
        ENTRY.usesSharedPaletteTexture = 0;
        ReadFile(sourceFile, &record.width, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.height, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.stridePixels, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.bitsPerPixel, 1, &dwRead, 0);
        ReadFile(sourceFile, &record.compressedBytes, 4, &dwRead, 0);
        if (record.compressedBytes > 0) {
            record.pixelData = new BYTE[record.compressedBytes];
            ReadFile(sourceFile, record.pixelData, record.compressedBytes, &dwRead, 0);
        } else if (record.bitsPerPixel >= 24) {
            record.pixelData = new BYTE[record.stridePixels * record.height * 4];
            ReadFile(sourceFile, record.pixelData, record.stridePixels * record.height * 4, &dwRead, 0);
        } else {
            record.pixelData = new BYTE[(static_cast<unsigned int>(record.stridePixels * record.height) * record.bitsPerPixel) >> 3];
            ReadFile(sourceFile, record.pixelData, (static_cast<unsigned int>(record.stridePixels * record.height) * record.bitsPerPixel) >> 3, &dwRead, 0);
        }
        ENTRY.LoadSerialized(&record);
        delete[] record.pixelData;
        Graphics::CreateTexture(static_cast<unsigned short>(ENTRY.storedWidth), static_cast<unsigned short>(ENTRY.storedHeight), &textures[index], ENTRY.bitsPerPixel);
        Refresh(index);
        delete[] ENTRY.pixels;
        ENTRY.pixels = 0;
    }
    CloseHandle(sourceFile);
}

#undef ENTRY
