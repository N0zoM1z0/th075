#include "assets/ArchiveCatalog.hpp"
#include "assets/DataArchive.hpp"
#include "graphics/GraphicsTexture.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "assets/TexturePackRecord.hpp"
#include <new>

void TextureManagerF198::LoadDefault(const char* filename, const char* archiveName) {
    Load(filename, 0, archiveName);
}

void TextureManagerF198::Load(const char* filename, signed char selectedPalette, const char* archiveName) {
    int nEntriesCount = entries.size();
    // The archive context owns this positioned handle.
    HANDLE sourceFile = ResourceLookupF217::FindByName(archiveName)->SeekNamedEntry(filename);
    int index;
    TexturePackRecord record;
    DWORD dwRead;
    signed char paletteHeaderCount;
    if (sourceFile == INVALID_HANDLE_VALUE)
        return;
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
        entries[index].bitsPerPixel = textureDepth;
        entries[index].palette = palette;
        entries[index].usesSharedPaletteTexture = 0;
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
        entries[index].LoadSerialized(&record);
        delete[] record.pixelData;
        Graphics::CreateTexture(static_cast<unsigned short>(entries[index].storedWidth), static_cast<unsigned short>(entries[index].storedHeight), &textures[index], entries[index].bitsPerPixel);
        Refresh(index);
        delete[] entries[index].pixels;
        entries[index].pixels = 0;
    }
}
