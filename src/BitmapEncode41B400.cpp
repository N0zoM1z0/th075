#include <windows.h>
#include <string.h>

// Pointer-only interface; the complete original owner remains unknown.
class BitmapPackSource40BF60 { public: bool LoadFile(const char*); void Encode(); };
#define FORMAT (*reinterpret_cast<BYTE*>(this))
#define WIDTH (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 4))
#define HEIGHT (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 8))
#define STRIDE (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 12))
#define ENCODED_SIZE (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 16))
#define PIXELS (*reinterpret_cast<BYTE**>(reinterpret_cast<char*>(this) + 28))

void BitmapPackSource40BF60::Encode() {
    if (ENCODED_SIZE)
        return;
    switch (FORMAT) {
    case 8: {
        BYTE* temp = new BYTE[HEIGHT * WIDTH * 2];
        // Used run-length field index; this compiler folds its reads into addresses.
        const int lengthField = 0;
        int runIndex = 0;
        BYTE numPixels = 0;
        BYTE runColor = PIXELS[0];
        for (unsigned int y = 0; y < HEIGHT; y++) {
            for (unsigned int x = 0; x < WIDTH; x++) {
                if (runColor == PIXELS[y * STRIDE + x] && numPixels < 255) {
                    numPixels++;
                } else {
                    temp[runIndex + lengthField] = numPixels;
                    temp[runIndex + 1] = runColor;
                    runIndex += 2;
                    runColor = PIXELS[y * STRIDE + x];
                    numPixels = 1;
                }
            }
        }
        temp[runIndex + lengthField] = numPixels;
        temp[runIndex + 1] = runColor;
        runIndex += 2;
        delete[] PIXELS;
        PIXELS = new BYTE[runIndex];
        ENCODED_SIZE = runIndex;
        memcpy(PIXELS, temp, runIndex);
        delete[] temp;
        break;
    }
    case 16: {
        WORD* pPixels = reinterpret_cast<WORD*>(PIXELS);
        WORD* temp = new WORD[HEIGHT * WIDTH * 2];
        // Used run-length field index; this compiler folds its reads into addresses.
        const int lengthField = 0;
        int runIndex = 0;
        WORD numPixels = 0;
        WORD runColor = pPixels[0];
        for (unsigned int y = 0; y < HEIGHT; y++) {
            for (unsigned int x = 0; x < WIDTH; x++) {
                if (runColor == pPixels[y * STRIDE + x]) {
                    numPixels++;
                } else {
                    temp[runIndex + lengthField] = numPixels;
                    temp[runIndex + 1] = runColor;
                    runIndex += 2;
                    runColor = pPixels[y * STRIDE + x];
                    numPixels = 1;
                }
            }
        }
        temp[runIndex + lengthField] = numPixels;
        temp[runIndex + 1] = runColor;
        runIndex += 2;
        delete[] PIXELS;
        PIXELS = new BYTE[runIndex * 2];
        ENCODED_SIZE = runIndex * 2;
        memcpy(PIXELS, temp, runIndex * 2);
        delete[] temp;
        break;
    }
    case 24:
    case 32: {
        DWORD* temp = new DWORD[HEIGHT * WIDTH * 2];
        // Used run-length field index; this compiler folds its reads into addresses.
        const int lengthField = 0;
        int runIndex = 0;
        DWORD numPixels = 0;
        DWORD runColor = reinterpret_cast<DWORD*>(PIXELS)[0];
        for (unsigned int y = 0; y < HEIGHT; y++) {
            for (unsigned int x = 0; x < WIDTH; x++) {
                if (runColor == reinterpret_cast<DWORD*>(PIXELS)[y * STRIDE + x]) {
                    numPixels++;
                } else {
                    temp[runIndex + lengthField] = numPixels;
                    temp[runIndex + 1] = runColor;
                    runIndex += 2;
                    runColor = reinterpret_cast<DWORD*>(PIXELS)[y * STRIDE + x];
                    numPixels = 1;
                }
            }
        }
        temp[runIndex + lengthField] = numPixels;
        temp[runIndex + 1] = runColor;
        runIndex += 2;
        delete[] PIXELS;
        PIXELS = new BYTE[runIndex * 4];
        ENCODED_SIZE = runIndex * 4;
        memcpy(PIXELS, temp, runIndex * 4);
        delete[] temp;
    }
    }
}

#undef FORMAT
#undef WIDTH
#undef HEIGHT
#undef STRIDE
#undef ENCODED_SIZE
#undef PIXELS
