#include "graphics/TextureManagerF198.hpp"
#include <windows.h>
#include <stddef.h>
#include <new>

typedef char BmpFileHeader40C380[(sizeof(BITMAPFILEHEADER) == 14) ? 1 : -1];
typedef char BmpInfoHeader40C380[(sizeof(BITMAPINFOHEADER) == 40) ? 1 : -1];
typedef char BmpBitCount40C380[(offsetof(BITMAPINFOHEADER, biBitCount) == 14) ? 1 : -1];
typedef char BmpPixelOffset40C380[(offsetof(BITMAPFILEHEADER, bfOffBits) == 10) ? 1 : -1];
typedef char BmpColor40C380[(sizeof(RGBQUAD) == 4) ? 1 : -1];

void TextureManagerF198::LoadPalette(const char* filename) {
    RGBQUAD* colors = 0;
    if (palette) {
        delete[] palette;
        palette = 0;
    }
    HANDLE handle = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, 0);
    if (handle == INVALID_HANDLE_VALUE)
        return;
    DWORD bmpSize = GetFileSize(handle, 0);
    unsigned char* data = new unsigned char[bmpSize];
    DWORD readCount;
    ReadFile(handle, data, bmpSize, &readCount, 0);
    BITMAPFILEHEADER* bmpHeader = reinterpret_cast<BITMAPFILEHEADER*>(data);
    if (bmpHeader->bfType != 0x4D42)
        return;
    DWORD pixelDataOffset = bmpHeader->bfOffBits; // The target snapshots this field without using it later.
    BITMAPINFOHEADER* infoHeader = reinterpret_cast<BITMAPINFOHEADER*>(data + sizeof(BITMAPFILEHEADER));
    unsigned char depth = static_cast<unsigned char>(infoHeader->biBitCount);
    int numEntries = 1 << depth;
    if (depth <= 8 && !palette) {
        colors = reinterpret_cast<RGBQUAD*>(data + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
        palette = new unsigned short[256];
        for (int index = 0; index < numEntries; index++) {
            palette[index] = colors[index].rgbBlue >> 3;
            palette[index] |= (colors[index].rgbGreen >> 3) << 5;
            palette[index] |= (colors[index].rgbRed >> 3) << 10;
            palette[index] |= 0x8000;
        }
        palette[0] &= 0x7FFF;
    }
    delete[] data;
    CloseHandle(handle);
}
