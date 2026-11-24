#include "TextureManagerBorrowedF925.hpp"
#include <windows.h>
#include <string.h>


void TextureEntryStorageF769::Encode() {
    if (encodedSize)
        return;
    switch (uploadFormat) {
    case 8: {
        BYTE* temp = new BYTE[storedHeight * storedWidth * 2];
        // Used run-length field index; this compiler folds its reads into addresses.
        const int lengthField = 0;
        int runIndex = 0;
        BYTE numPixels = 0;
        BYTE runColor = pixels[0];
        for (unsigned int y = 0; y < storedHeight; y++) {
            for (unsigned int x = 0; x < storedWidth; x++) {
                if (runColor == pixels[y * storedStride + x] && numPixels < 255) {
                    numPixels++;
                } else {
                    temp[runIndex + lengthField] = numPixels;
                    temp[runIndex + 1] = runColor;
                    runIndex += 2;
                    runColor = pixels[y * storedStride + x];
                    numPixels = 1;
                }
            }
        }
        temp[runIndex + lengthField] = numPixels;
        temp[runIndex + 1] = runColor;
        runIndex += 2;
        delete[] pixels;
        pixels = new BYTE[runIndex];
        encodedSize = runIndex;
        memcpy(pixels, temp, runIndex);
        delete[] temp;
        break;
    }
    case 16: {
        WORD* pPixels = reinterpret_cast<WORD*>(pixels);
        WORD* temp = new WORD[storedHeight * storedWidth * 2];
        // Used run-length field index; this compiler folds its reads into addresses.
        const int lengthField = 0;
        int runIndex = 0;
        WORD numPixels = 0;
        WORD runColor = pPixels[0];
        for (unsigned int y = 0; y < storedHeight; y++) {
            for (unsigned int x = 0; x < storedWidth; x++) {
                if (runColor == pPixels[y * storedStride + x]) {
                    numPixels++;
                } else {
                    temp[runIndex + lengthField] = numPixels;
                    temp[runIndex + 1] = runColor;
                    runIndex += 2;
                    runColor = pPixels[y * storedStride + x];
                    numPixels = 1;
                }
            }
        }
        temp[runIndex + lengthField] = numPixels;
        temp[runIndex + 1] = runColor;
        runIndex += 2;
        delete[] pixels;
        pixels = new BYTE[runIndex * 2];
        encodedSize = runIndex * 2;
        memcpy(pixels, temp, runIndex * 2);
        delete[] temp;
        break;
    }
    case 24:
    case 32: {
        DWORD* temp = new DWORD[storedHeight * storedWidth * 2];
        // Used run-length field index; this compiler folds its reads into addresses.
        const int lengthField = 0;
        int runIndex = 0;
        DWORD numPixels = 0;
        DWORD runColor = reinterpret_cast<DWORD*>(pixels)[0];
        for (unsigned int y = 0; y < storedHeight; y++) {
            for (unsigned int x = 0; x < storedWidth; x++) {
                if (runColor == reinterpret_cast<DWORD*>(pixels)[y * storedStride + x]) {
                    numPixels++;
                } else {
                    temp[runIndex + lengthField] = numPixels;
                    temp[runIndex + 1] = runColor;
                    runIndex += 2;
                    runColor = reinterpret_cast<DWORD*>(pixels)[y * storedStride + x];
                    numPixels = 1;
                }
            }
        }
        temp[runIndex + lengthField] = numPixels;
        temp[runIndex + 1] = runColor;
        runIndex += 2;
        delete[] pixels;
        pixels = new BYTE[runIndex * 4];
        encodedSize = runIndex * 4;
        memcpy(pixels, temp, runIndex * 4);
        delete[] temp;
    }
    }
}
