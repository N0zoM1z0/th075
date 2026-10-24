#include "TexturePack40BF60.hpp"

#define PALETTE (*reinterpret_cast<unsigned short**>(reinterpret_cast<char*>(this) + 4))
#define COUNT reinterpret_cast<TextureEntryCount40C8C0*>(reinterpret_cast<char*>(this) + 8)
#define ENTRIES reinterpret_cast<SpriteEntries40CA80*>(reinterpret_cast<char*>(this) + 8)
#define ENTRY(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(ENTRIES->At(index)) + (offset)))
#define FORMAT (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x4C))
#define PALETTE_LOADER reinterpret_cast<BitmapPalette40C380*>(this)
#define BITMAP reinterpret_cast<BitmapPackSource40BF60*>(ENTRIES->At(index))

void TexturePack40BF60::Save(const char* directory, const char* outputFilename, signed char paletteCount) {
    TextureRecordSnapshot40BF60 record;
    int index;
    HANDLE outputHandle;
    char filename[MAX_PATH];
    {
        int count = static_cast<int>(COUNT->Size());
        DWORD written;
        signed char header;
        outputHandle = CreateFileA(outputFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL, 0);
        if (outputHandle == INVALID_HANDLE_VALUE)
            return;
        SetFilePointer(outputHandle, 0, 0, FILE_BEGIN);
        if (PALETTE) {
            if (paletteCount > 1) {
                header = paletteCount;
                WriteFile(outputHandle, &header, 1, &written, 0);
                WriteFile(outputHandle, PALETTE, 512, &written, 0);
                for (int paletteIndex = 2; paletteIndex <= paletteCount; paletteIndex++) {
                    sprintf(filename, "%s\\pal%dp.bmp", directory, paletteIndex);
                    PALETTE_LOADER->Load(filename);
                    WriteFile(outputHandle, PALETTE, 512, &written, 0);
                }
            } else {
                header = 1;
                WriteFile(outputHandle, &header, 1, &written, 0);
                WriteFile(outputHandle, PALETTE, 512, &written, 0);
            }
        } else {
            header = 0;
            WriteFile(outputHandle, &header, 1, &written, 0);
        }
        for (index = 0; index < count; index++) {
            ENTRY(unsigned char, 0) = FORMAT;
            ENTRY(unsigned short*, 0x14) = PALETTE;
            sprintf(filename, "%s\\%04d.bmp", directory, index);
            BITMAP->LoadFile(filename);
            BITMAP->Encode();
            record.width = ENTRY(int, 4);
            record.height = ENTRY(int, 8);
            record.stride = ENTRY(int, 12);
            record.depth = ENTRY(unsigned char, 0);
            record.encodedSize = ENTRY(DWORD, 16);
            record.data = ENTRY(void*, 28);
            WriteFile(outputHandle, &record.width, 4, &written, 0);
            WriteFile(outputHandle, &record.height, 4, &written, 0);
            WriteFile(outputHandle, &record.stride, 4, &written, 0);
            WriteFile(outputHandle, &record.depth, 1, &written, 0);
            WriteFile(outputHandle, &record.encodedSize, 4, &written, 0);
            if (record.encodedSize > 0) {
                WriteFile(outputHandle, ENTRY(void*, 28), record.encodedSize, &written, 0);
            } else if (record.depth >= 24) {
                WriteFile(outputHandle, record.data, record.stride * record.height * 4, &written, 0);
            } else {
                WriteFile(outputHandle, record.data, (record.stride * record.height * static_cast<unsigned int>(record.depth)) >> 3, &written, 0);
            }
        }
        CloseHandle(outputHandle);
    }
}

void TexturePack40BF60::SaveDefault(const char* directory, const char* filename) {
    Save(directory, filename, 0);
}

#undef BITMAP
#undef PALETTE_LOADER
#undef FORMAT
#undef ENTRY
#undef ENTRIES
#undef COUNT
#undef PALETTE
