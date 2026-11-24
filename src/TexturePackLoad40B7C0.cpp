#include "GraphicsTexture.hpp"
#include "TextureManagerF198.hpp"
#include "TexturePack40BF60.hpp"
#include <new>

// These owner/container interfaces are pointer-only and never instantiated.
class TexturePackLoad40B7C0 {
public:
    void Load(const char*, signed char);
    void LoadDefault(const char*);
};

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)
#define ENTRY MANAGER->entries[index]

void TexturePackLoad40B7C0::LoadDefault(const char* filename) {
    Load(filename, 0);
}

void TexturePackLoad40B7C0::Load(const char* filename, signed char selectedPalette) {
    int nEntriesCount = MANAGER->entries.size();
    HANDLE sourceFile = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL, 0);
    int index;
    TextureRecordSnapshot40BF60 record;
    DWORD dwRead;
    signed char paletteHeaderCount;
    if (sourceFile == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(sourceFile, 0, 0, FILE_BEGIN);
    ReadFile(sourceFile, &paletteHeaderCount, 1, &dwRead, 0);
    if (MANAGER->palette)
        delete[] MANAGER->palette;
    if (paletteHeaderCount > 0) {
        MANAGER->palette = new WORD[256];
        if (selectedPalette <= paletteHeaderCount) {
            SetFilePointer(sourceFile, (selectedPalette - 1) * 512, 0, FILE_CURRENT);
            ReadFile(sourceFile, MANAGER->palette, 512, &dwRead, 0);
            SetFilePointer(sourceFile, (paletteHeaderCount - selectedPalette) * 512, 0, FILE_CURRENT);
        } else {
            ReadFile(sourceFile, MANAGER->palette, 512, &dwRead, 0);
            SetFilePointer(sourceFile, (paletteHeaderCount - 1) * 512, 0, FILE_CURRENT);
        }
    } else {
        MANAGER->palette = 0;
    }
    for (index = 0; index < nEntriesCount; index++) {
        ENTRY.uploadFormat = MANAGER->textureDepth;
        ENTRY.palette = MANAGER->palette;
        ENTRY.paletteFlag = 0;
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
        ENTRY.LoadSerialized(&record);
        delete[] static_cast<BYTE*>(record.data);
        Graphics::CreateTexture(static_cast<unsigned short>(ENTRY.storedWidth), static_cast<unsigned short>(ENTRY.storedHeight), &MANAGER->textures[index], ENTRY.uploadFormat);
        MANAGER->Refresh(index);
        delete[] ENTRY.pixels;
        ENTRY.pixels = 0;
    }
    CloseHandle(sourceFile);
}

#undef ENTRY
#undef MANAGER
