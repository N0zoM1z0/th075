#include "assets/TexturePack40BF60.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <stdio.h>

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)
#define ENTRY MANAGER->entries[index]

void TexturePack40BF60::Save(const char* directory, const char* outputFilename, signed char paletteCount) {
    TextureRecordSnapshot40BF60 record;
    int index;
    HANDLE outputHandle;
    char filename[MAX_PATH];
    {
        int count = static_cast<int>(MANAGER->entries.size());
        DWORD written;
        signed char header;
        outputHandle = CreateFileA(outputFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL, 0);
        if (outputHandle == INVALID_HANDLE_VALUE)
            return;
        SetFilePointer(outputHandle, 0, 0, FILE_BEGIN);
        if (MANAGER->palette) {
            if (paletteCount > 1) {
                header = paletteCount;
                WriteFile(outputHandle, &header, 1, &written, 0);
                WriteFile(outputHandle, MANAGER->palette, 512, &written, 0);
                for (int paletteIndex = 2; paletteIndex <= paletteCount; paletteIndex++) {
                    sprintf(filename, "%s\\pal%dp.bmp", directory, paletteIndex);
                    MANAGER->LoadPalette(filename);
                    WriteFile(outputHandle, MANAGER->palette, 512, &written, 0);
                }
            } else {
                header = 1;
                WriteFile(outputHandle, &header, 1, &written, 0);
                WriteFile(outputHandle, MANAGER->palette, 512, &written, 0);
            }
        } else {
            header = 0;
            WriteFile(outputHandle, &header, 1, &written, 0);
        }
        for (index = 0; index < count; index++) {
            ENTRY.uploadFormat = MANAGER->textureDepth;
            ENTRY.palette = MANAGER->palette;
            sprintf(filename, "%s\\%04d.bmp", directory, index);
            ENTRY.LoadFile(filename);
            ENTRY.Encode();
            record.width = ENTRY.storedWidth;
            record.height = ENTRY.storedHeight;
            record.stride = ENTRY.storedStride;
            record.depth = ENTRY.uploadFormat;
            record.encodedSize = ENTRY.encodedSize;
            record.data = ENTRY.pixels;
            WriteFile(outputHandle, &record.width, 4, &written, 0);
            WriteFile(outputHandle, &record.height, 4, &written, 0);
            WriteFile(outputHandle, &record.stride, 4, &written, 0);
            WriteFile(outputHandle, &record.depth, 1, &written, 0);
            WriteFile(outputHandle, &record.encodedSize, 4, &written, 0);
            if (record.encodedSize > 0) {
                WriteFile(outputHandle, ENTRY.pixels, record.encodedSize, &written, 0);
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

#undef ENTRY
#undef MANAGER
