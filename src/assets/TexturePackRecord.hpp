#pragma once
#include <windows.h>
#include <stddef.h>

// In-memory record. The pack serializes the first five fields individually.
struct TexturePackRecord {
    int width, height, stridePixels;
    unsigned char bitsPerPixel;
    DWORD compressedBytes;
    BYTE* pixelData;
};
typedef char TexturePackRecordSize[(sizeof(TexturePackRecord) == 24) ? 1 : -1];
typedef char TexturePackFormatOffset[(offsetof(TexturePackRecord, bitsPerPixel) == 12) ? 1 : -1];
typedef char TexturePackCompressedSizeOffset[(offsetof(TexturePackRecord, compressedBytes) == 16) ? 1 : -1];
typedef char TexturePackPixelDataOffset[(offsetof(TexturePackRecord, pixelData) == 20) ? 1 : -1];

typedef char TexturePackWidthOffset[(offsetof(TexturePackRecord, width) == 0) ? 1 : -1];
typedef char TexturePackHeightOffset[(offsetof(TexturePackRecord, height) == 4) ? 1 : -1];
typedef char TexturePackStrideOffset[(offsetof(TexturePackRecord, stridePixels) == 8) ? 1 : -1];
