#include "assets/TexturePackRecord.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <stdio.h>

#define ENTRY entries[index]

void TextureManagerF198::SavePackFile(const char* directory, const char* outputFilename, signed char paletteCount) {
    TexturePackRecord record;
    int index;
    HANDLE outputHandle;
    char filename[MAX_PATH];
    {
        int count = static_cast<int>(entries.size());
        DWORD written;
        signed char header;
        outputHandle = CreateFileA(outputFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL, 0);
        if (outputHandle == INVALID_HANDLE_VALUE)
            return;
        SetFilePointer(outputHandle, 0, 0, FILE_BEGIN);
        if (palette) {
            if (paletteCount > 1) {
                header = paletteCount;
                WriteFile(outputHandle, &header, 1, &written, 0);
                WriteFile(outputHandle, palette, 512, &written, 0);
                for (int paletteIndex = 2; paletteIndex <= paletteCount; paletteIndex++) {
                    sprintf(filename, "%s\\pal%dp.bmp", directory, paletteIndex);
                    LoadPalette(filename);
                    WriteFile(outputHandle, palette, 512, &written, 0);
                }
            } else {
                header = 1;
                WriteFile(outputHandle, &header, 1, &written, 0);
                WriteFile(outputHandle, palette, 512, &written, 0);
            }
        } else {
            header = 0;
            WriteFile(outputHandle, &header, 1, &written, 0);
        }
        for (index = 0; index < count; index++) {
            ENTRY.bitsPerPixel = textureDepth;
            ENTRY.palette = palette;
            sprintf(filename, "%s\\%04d.bmp", directory, index);
            ENTRY.LoadFile(filename);
            ENTRY.Encode();
            record.width = ENTRY.storedWidth;
            record.height = ENTRY.storedHeight;
            record.stridePixels = ENTRY.stridePixels;
            record.bitsPerPixel = ENTRY.bitsPerPixel;
            record.compressedBytes = ENTRY.compressedBytes;
            record.pixelData = ENTRY.pixels;
            WriteFile(outputHandle, &record.width, 4, &written, 0);
            WriteFile(outputHandle, &record.height, 4, &written, 0);
            WriteFile(outputHandle, &record.stridePixels, 4, &written, 0);
            WriteFile(outputHandle, &record.bitsPerPixel, 1, &written, 0);
            WriteFile(outputHandle, &record.compressedBytes, 4, &written, 0);
            if (record.compressedBytes > 0) {
                WriteFile(outputHandle, ENTRY.pixels, record.compressedBytes, &written, 0);
            } else if (record.bitsPerPixel >= 24) {
                WriteFile(outputHandle, record.pixelData, record.stridePixels * record.height * 4, &written, 0);
            } else {
                WriteFile(outputHandle, record.pixelData, (record.stridePixels * record.height * static_cast<unsigned int>(record.bitsPerPixel)) >> 3, &written, 0);
            }
        }
        CloseHandle(outputHandle);
    }
}

void TextureManagerF198::SavePackFileDefaultPalette(const char* directory, const char* filename) {
    SavePackFile(directory, filename, 0);
}

#undef ENTRY
