#include <windows.h>
#include <stddef.h>

// Pointer-only interface; the complete original bitmap owner remains unknown.
class BitmapPackSource40BF60 { public: bool LoadFile(const char*); void Encode(); };
#define FORMAT (*reinterpret_cast<BYTE*>(this))
#define WIDTH (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 4))
#define HEIGHT (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 8))
#define STRIDE (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 12))
#define PALETTE (*reinterpret_cast<WORD**>(reinterpret_cast<char*>(this) + 20))
#define OWNS_PALETTE (*reinterpret_cast<BYTE*>(reinterpret_cast<char*>(this) + 24))
#define PIXELS (*reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 28))

// A complete temporary color value, separate from the incomplete bitmap owner.
struct BitmapColor41A3D0 { BYTE red, green, blue, alpha; };
typedef char BitmapColorSize41A3D0[(sizeof(BitmapColor41A3D0) == 4) ? 1 : -1];
typedef char BitmapFileSize41A3D0[(sizeof(BITMAPFILEHEADER) == 14) ? 1 : -1];
typedef char BitmapInfoSize41A3D0[(sizeof(BITMAPINFOHEADER) == 40) ? 1 : -1];
typedef char BitmapBitsOffset41A3D0[(offsetof(BITMAPINFOHEADER, biBitCount) == 14) ? 1 : -1];

bool BitmapPackSource40BF60::LoadFile(const char* filename) {
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
    if (FORMAT == 0) {
        FORMAT = bitCount;
        if (FORMAT < 8)
            FORMAT = 8;
    }
    if (FORMAT == 32 && bitCount <= 24)
        FORMAT = 24;
    if (bitCount == 32)
        FORMAT = 32;
    int paletteCount = 1 << bitCount;
    WIDTH = pInfo->biWidth;
    HEIGHT = pInfo->biHeight;
    STRIDE = WIDTH;
    if (STRIDE % 4 > 0)
        STRIDE = (STRIDE / 4 + 1) * 4;
    unsigned int nLineBytes = (bitCount * WIDTH) >> 3;
    if (nLineBytes % 4 > 0)
        nLineBytes = (nLineBytes / 4 + 1) * 4;
    if (bitCount <= 8) {
        if (!PALETTE) {
            pColors = reinterpret_cast<RGBQUAD*>(inputData + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
            PALETTE = new WORD[256];
            for (int index = 0; index < paletteCount; index++) {
                PALETTE[index] = pColors[index].rgbBlue >> 3;
                PALETTE[index] |= (pColors[index].rgbGreen >> 3) << 5;
                PALETTE[index] |= (pColors[index].rgbRed >> 3) << 10;
                PALETTE[index] |= 0x8000;
            }
            PALETTE[kKeyIndex] &= 0x7FFF;
            OWNS_PALETTE = 1;
        }
        if (FORMAT >= 16) {
            pColors = reinterpret_cast<RGBQUAD*>(inputData + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
            pRgbaEntries = new BitmapColor41A3D0[256];
            for (int index = 0; index < paletteCount; index++) {
                pRgbaEntries[index].red = pColors[index].rgbRed;
                pRgbaEntries[index].green = pColors[index].rgbGreen;
                pRgbaEntries[index].blue = pColors[index].rgbBlue;
                pRgbaEntries[index].alpha = pColors[index].rgbReserved;
            }
            if (FORMAT == 16) {
                pRgbPalette = new WORD[256];
                for (int index = 0; index < 256; index++) {
                    pRgbPalette[index] = pRgbaEntries[index].blue >> 3;
                    pRgbPalette[index] |= (pRgbaEntries[index].green >> 3) << 5;
                    pRgbPalette[index] |= (pRgbaEntries[index].red >> 3) << 10;
                    pRgbPalette[index] |= 0x8000;
                }
                pRgbPalette[kKeyIndex] &= 0x7FFF;
            } else if (FORMAT == 24) {
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
    switch (FORMAT) {
    case 8:
        PIXELS = new BYTE[HEIGHT * STRIDE];
        pDest8 = static_cast<BYTE*>(PIXELS);
        for (unsigned int y = 0; y < HEIGHT; y++) {
            for (unsigned int x = 0; x < WIDTH; x++)
                pDest8[(HEIGHT - 1 - y) * STRIDE + x] = inputData[y * nLineBytes + x + nOffset];
        }
        break;
    case 16:
        PIXELS = new WORD[HEIGHT * STRIDE];
        out16 = static_cast<WORD*>(PIXELS);
        if (bitCount <= 8) {
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++)
                    out16[(HEIGHT - 1 - y) * STRIDE + x] = pRgbPalette[inputData[y * nLineBytes + x + nOffset]];
            }
        } else {
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    out16[(HEIGHT - 1 - y) * STRIDE + x] = inputData[x * 3 + y * nLineBytes + nOffset] >> 3;
                    out16[(HEIGHT - 1 - y) * STRIDE + x] |= (inputData[x * 3 + y * nLineBytes + nOffset + 1] >> 3) << 5;
                    out16[(HEIGHT - 1 - y) * STRIDE + x] |= (inputData[x * 3 + y * nLineBytes + nOffset + 2] >> 3) << 10;
                    if ((inputData[x * 3 + y * nLineBytes + nOffset] | inputData[x * 3 + y * nLineBytes + nOffset + 1] | inputData[x * 3 + y * nLineBytes + nOffset + 2]) == 0)
                        out16[(HEIGHT - 1 - y) * STRIDE + x] &= 0x7FFF;
                    else
                        out16[(HEIGHT - 1 - y) * STRIDE + x] |= 0x8000;
                }
            }
        }
        break;
    case 24:
        PIXELS = new DWORD[HEIGHT * STRIDE];
        pDest32 = static_cast<DWORD*>(PIXELS);
        if (bitCount <= 8) {
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++)
                    pDest32[(HEIGHT - 1 - y) * STRIDE + x] = colorMap32[inputData[y * nLineBytes + x + nOffset]];
            }
        } else {
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    pDest32[(HEIGHT - 1 - y) * STRIDE + x] = inputData[x * 3 + y * nLineBytes + nOffset];
                    pDest32[(HEIGHT - 1 - y) * STRIDE + x] |= inputData[x * 3 + y * nLineBytes + nOffset + 1] << 8;
                    pDest32[(HEIGHT - 1 - y) * STRIDE + x] |= inputData[x * 3 + y * nLineBytes + nOffset + 2] << 16;
                    if ((inputData[x * 3 + y * nLineBytes + nOffset] | inputData[x * 3 + y * nLineBytes + nOffset + 1] | inputData[x * 3 + y * nLineBytes + nOffset + 2]) == 0)
                        pDest32[(HEIGHT - 1 - y) * STRIDE + x] &= 0xFFFFFF;
                    else
                        pDest32[(HEIGHT - 1 - y) * STRIDE + x] |= 0xFF000000;
                }
            }
        }
        break;
    case 32:
        PIXELS = new DWORD[HEIGHT * STRIDE];
        pDest32 = static_cast<DWORD*>(PIXELS);
        if (bitCount <= 8) {
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++)
                    pDest32[(HEIGHT - 1 - y) * STRIDE + x] = colorMap32[inputData[y * nLineBytes + x + nOffset]];
            }
        } else {
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++)
                    pDest32[(HEIGHT - 1 - y) * STRIDE + x] = *reinterpret_cast<DWORD*>(inputData + y * nLineBytes + x * 4 + nOffset);
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

#undef FORMAT
#undef WIDTH
#undef HEIGHT
#undef STRIDE
#undef PALETTE
#undef OWNS_PALETTE
#undef PIXELS
