#include "graphics/TextureManagerBorrowedF925.hpp"
#include <windows.h>
#include <stddef.h>


// A complete temporary color value, separate from the incomplete bitmap owner.
struct BitmapColor41A3D0 { BYTE red, green, blue, alpha; };
typedef char BitmapColorSize41A3D0[(sizeof(BitmapColor41A3D0) == 4) ? 1 : -1];
typedef char BitmapFileSize41A3D0[(sizeof(BITMAPFILEHEADER) == 14) ? 1 : -1];
typedef char BitmapInfoSize41A3D0[(sizeof(BITMAPINFOHEADER) == 40) ? 1 : -1];
typedef char BitmapBitsOffset41A3D0[(offsetof(BITMAPINFOHEADER, biBitCount) == 14) ? 1 : -1];

bool TextureEntryStorageF769::LoadFile(const char* filename) {
    RGBQUAD* pColors = 0;
    WORD* pRgbPalette = 0;
    DWORD* colorMap32 = 0;
    BYTE* pDest8 = 0;
    WORD* out16 = 0;
    DWORD* pDest32 = 0;
    // Transparent palette entry; its uses fold into addresses with this compiler.
    // This is a source-compatible policy constant, not an original name claim.
    const BYTE kKeyIndex = 0;
    BitmapColor41A3D0* pRgbaEntries;
    HANDLE handle = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL, 0);
    if (handle == INVALID_HANDLE_VALUE)
        return false;
    DWORD dataSize = GetFileSize(handle, 0);
    BYTE* inputData = new BYTE[dataSize];
    DWORD bytesReadFromFile;
    ReadFile(handle, inputData, dataSize, &bytesReadFromFile, 0);
    BITMAPFILEHEADER* bfh = reinterpret_cast<BITMAPFILEHEADER*>(inputData);
    if (bfh->bfType != 0x4D42)
        return false;
    DWORD nOffset = bfh->bfOffBits;
    BITMAPINFOHEADER* pInfo = reinterpret_cast<BITMAPINFOHEADER*>(inputData + sizeof(BITMAPFILEHEADER));
    BYTE bitCount = static_cast<BYTE>(pInfo->biBitCount);
    if (uploadFormat == 0) {
        uploadFormat = bitCount;
        if (uploadFormat < 8)
            uploadFormat = 8;
    }
    if (uploadFormat == 32 && bitCount <= 24)
        uploadFormat = 24;
    if (bitCount == 32)
        uploadFormat = 32;
    int paletteCount = 1 << bitCount;
    storedWidth = pInfo->biWidth;
    storedHeight = pInfo->biHeight;
    storedStride = storedWidth;
    if (storedStride % 4 > 0)
        storedStride = (storedStride / 4 + 1) * 4;
    unsigned int nLineBytes = (bitCount * storedWidth) >> 3;
    if (nLineBytes % 4 > 0)
        nLineBytes = (nLineBytes / 4 + 1) * 4;
    if (bitCount <= 8) {
        if (!palette) {
            pColors = reinterpret_cast<RGBQUAD*>(inputData + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
            palette = new WORD[256];
            for (int index = 0; index < paletteCount; index++) {
                palette[index] = pColors[index].rgbBlue >> 3;
                palette[index] |= (pColors[index].rgbGreen >> 3) << 5;
                palette[index] |= (pColors[index].rgbRed >> 3) << 10;
                palette[index] |= 0x8000;
            }
            palette[kKeyIndex] &= 0x7FFF;
            ownsPalette = 1;
        }
        if (uploadFormat >= 16) {
            pColors = reinterpret_cast<RGBQUAD*>(inputData + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
            pRgbaEntries = new BitmapColor41A3D0[256];
            for (int index = 0; index < paletteCount; index++) {
                pRgbaEntries[index].red = pColors[index].rgbRed;
                pRgbaEntries[index].green = pColors[index].rgbGreen;
                pRgbaEntries[index].blue = pColors[index].rgbBlue;
                pRgbaEntries[index].alpha = pColors[index].rgbReserved;
            }
            if (uploadFormat == 16) {
                pRgbPalette = new WORD[256];
                for (int index = 0; index < 256; index++) {
                    pRgbPalette[index] = pRgbaEntries[index].blue >> 3;
                    pRgbPalette[index] |= (pRgbaEntries[index].green >> 3) << 5;
                    pRgbPalette[index] |= (pRgbaEntries[index].red >> 3) << 10;
                    pRgbPalette[index] |= 0x8000;
                }
                pRgbPalette[kKeyIndex] &= 0x7FFF;
            } else if (uploadFormat == 24) {
                colorMap32 = new DWORD[256];
                for (int index = 0; index < 256; index++) {
                    colorMap32[index] = pRgbaEntries[index].blue;
                    colorMap32[index] = (pRgbaEntries[index].green << 8) | colorMap32[index];
                    colorMap32[index] = (pRgbaEntries[index].red << 16) | colorMap32[index];
                    colorMap32[index] |= 0xFF000000;
                }
                colorMap32[kKeyIndex] &= 0xFFFFFF;
            }
            delete[] pRgbaEntries;
        }
    }
    switch (uploadFormat) {
    case 8:
        pixels = new BYTE[storedHeight * storedStride];
        pDest8 = pixels;
        for (unsigned int y = 0; y < storedHeight; y++) {
            for (unsigned int x = 0; x < storedWidth; x++)
                pDest8[(storedHeight - 1 - y) * storedStride + x] = inputData[y * nLineBytes + x + nOffset];
        }
        break;
    case 16:
        pixels = reinterpret_cast<BYTE*>(new WORD[storedHeight * storedStride]);
        out16 = reinterpret_cast<WORD*>(pixels);
        if (bitCount <= 8) {
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++)
                    out16[(storedHeight - 1 - y) * storedStride + x] = pRgbPalette[inputData[y * nLineBytes + x + nOffset]];
            }
        } else {
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++) {
                    out16[(storedHeight - 1 - y) * storedStride + x] = inputData[x * 3 + y * nLineBytes + nOffset] >> 3;
                    out16[(storedHeight - 1 - y) * storedStride + x] |= (inputData[x * 3 + y * nLineBytes + nOffset + 1] >> 3) << 5;
                    out16[(storedHeight - 1 - y) * storedStride + x] |= (inputData[x * 3 + y * nLineBytes + nOffset + 2] >> 3) << 10;
                    if ((inputData[x * 3 + y * nLineBytes + nOffset] | inputData[x * 3 + y * nLineBytes + nOffset + 1] | inputData[x * 3 + y * nLineBytes + nOffset + 2]) == 0)
                        out16[(storedHeight - 1 - y) * storedStride + x] &= 0x7FFF;
                    else
                        out16[(storedHeight - 1 - y) * storedStride + x] |= 0x8000;
                }
            }
        }
        break;
    case 24:
        pixels = reinterpret_cast<BYTE*>(new DWORD[storedHeight * storedStride]);
        pDest32 = reinterpret_cast<DWORD*>(pixels);
        if (bitCount <= 8) {
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++)
                    pDest32[(storedHeight - 1 - y) * storedStride + x] = colorMap32[inputData[y * nLineBytes + x + nOffset]];
            }
        } else {
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++) {
                    pDest32[(storedHeight - 1 - y) * storedStride + x] = inputData[x * 3 + y * nLineBytes + nOffset];
                    pDest32[(storedHeight - 1 - y) * storedStride + x] |= inputData[x * 3 + y * nLineBytes + nOffset + 1] << 8;
                    pDest32[(storedHeight - 1 - y) * storedStride + x] |= inputData[x * 3 + y * nLineBytes + nOffset + 2] << 16;
                    if ((inputData[x * 3 + y * nLineBytes + nOffset] | inputData[x * 3 + y * nLineBytes + nOffset + 1] | inputData[x * 3 + y * nLineBytes + nOffset + 2]) == 0)
                        pDest32[(storedHeight - 1 - y) * storedStride + x] &= 0xFFFFFF;
                    else
                        pDest32[(storedHeight - 1 - y) * storedStride + x] |= 0xFF000000;
                }
            }
        }
        break;
    case 32:
        pixels = reinterpret_cast<BYTE*>(new DWORD[storedHeight * storedStride]);
        pDest32 = reinterpret_cast<DWORD*>(pixels);
        if (bitCount <= 8) {
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++)
                    pDest32[(storedHeight - 1 - y) * storedStride + x] = colorMap32[inputData[y * nLineBytes + x + nOffset]];
            }
        } else {
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++)
                    pDest32[(storedHeight - 1 - y) * storedStride + x] = *reinterpret_cast<DWORD*>(inputData + y * nLineBytes + x * 4 + nOffset);
            }
        }
    }
    CloseHandle(handle);
    if (pRgbPalette)
        delete[] pRgbPalette;
    if (colorMap32)
        delete[] colorMap32;
    delete[] inputData;
    return true;
}
