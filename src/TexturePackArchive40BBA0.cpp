#include "ArchiveCatalog.hpp"
#include "DataArchive.hpp"
#include "GraphicsTexture.hpp"
#include "TextureManagerF198.hpp"
#include "TexturePack40BF60.hpp"
#include <new>

void TextureManagerF198::LoadDefault(const char* filename, const char* archiveName) {
    Load(filename, 0, archiveName);
}

void TextureManagerF198::Load(const char* filename, signed char selectedPalette, const char* archiveName) {
    int nEntriesCount = entries.size();
    // The archive context owns this positioned handle.
    HANDLE sourceFile = ResourceLookupF217::FindByName(archiveName)->SeekNamedEntry(filename);
    int index;
    TextureRecordSnapshot40BF60 record;
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
        entries[index].uploadFormat = textureDepth;
        entries[index].palette = palette;
        entries[index].paletteFlag = 0;
        ReadFile(sourceFile, &record.width, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.height, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.stride, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.depth, 1, &dwRead, 0);
        ReadFile(sourceFile, &record.encodedSize, 4, &dwRead, 0);
        if (record.encodedSize > 0) {
            record.data = new BYTE[record.encodedSize];
            ReadFile(sourceFile, record.data, record.encodedSize, &dwRead, 0);
        } else if (record.depth >= 24) {
            record.data = new BYTE[record.stride * record.height * 4];
            ReadFile(sourceFile, record.data, record.stride * record.height * 4, &dwRead, 0);
        } else {
            record.data = new BYTE[(static_cast<unsigned int>(record.stride * record.height) * record.depth) >> 3];
            ReadFile(sourceFile, record.data, (static_cast<unsigned int>(record.stride * record.height) * record.depth) >> 3, &dwRead, 0);
        }
        entries[index].LoadSerialized(&record);
        delete[] static_cast<BYTE*>(record.data);
        Graphics::CreateTexture(static_cast<unsigned short>(entries[index].storedWidth), static_cast<unsigned short>(entries[index].storedHeight), &textures[index], entries[index].uploadFormat);
        Refresh(index);
        delete[] entries[index].pixels;
        entries[index].pixels = 0;
    }
}
