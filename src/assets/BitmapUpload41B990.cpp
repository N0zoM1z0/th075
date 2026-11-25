#include "graphics/TextureEntry.hpp"

void TextureEntryStorageF769::CopyTo(void* output, unsigned char depth, unsigned int outputWidth) {
    if (compressedBytes) {
        switch (depth) {
        case 8: {
            unsigned short* out = static_cast<unsigned short*>(output);
            unsigned char* input = pixels;
            unsigned int consumedPixels = 0;
            unsigned int sourceIndex = 0;
            unsigned int runLength = input[0];
            unsigned short value = palette[input[1]];
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++) {
                    out[y * outputWidth + x] = value;
                    consumedPixels++;
                    if (consumedPixels >= runLength) {
                        sourceIndex += 2;
                        // Preserve the native unsigned run-overflow boolean.
                        consumedPixels = consumedPixels > runLength;
                        if (x == storedWidth - 1 && y == storedHeight - 1)
                            break;
                        runLength = input[sourceIndex];
                        value = palette[input[sourceIndex + 1]];
                    }
                }
            }
            break;
        }
        case 16: {
            unsigned short* out = static_cast<unsigned short*>(output);
            unsigned short* input = reinterpret_cast<unsigned short*>(pixels);
            unsigned int consumedPixels = 0;
            unsigned int sourceIndex = 0;
            unsigned int runLength = input[0];
            unsigned short value = input[1];
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++) {
                    out[y * outputWidth + x] = value;
                    consumedPixels++;
                    if (consumedPixels >= runLength) {
                        sourceIndex += 2;
                        consumedPixels = 0;
                        if (x == storedWidth - 1 && y == storedHeight - 1)
                            break;
                        runLength = input[sourceIndex];
                        value = input[sourceIndex + 1];
                    }
                }
            }
            break;
        }
        case 24:
        case 32: {
            unsigned int* out = static_cast<unsigned int*>(output);
            unsigned int* input = reinterpret_cast<unsigned int*>(pixels);
            unsigned int consumedPixels = 0;
            unsigned int sourceIndex = 0;
            unsigned int runLength = input[0];
            unsigned int value = input[1];
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++) {
                    out[y * outputWidth + x] = value;
                    consumedPixels++;
                    if (consumedPixels >= runLength) {
                        sourceIndex += 2;
                        consumedPixels = 0;
                        if (x == storedWidth - 1 && y == storedHeight - 1)
                            break;
                        runLength = input[sourceIndex];
                        value = input[sourceIndex + 1];
                    }
                }
            }
        }
        }
    } else {
        switch (depth) {
        case 8: {
            unsigned short* out = static_cast<unsigned short*>(output);
            unsigned char* input = pixels;
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++)
                    out[y * outputWidth + x] = palette[input[y * stridePixels + x]];
            }
            break;
        }
        case 16: {
            // Native 16-bit copying groups pairs into DWORD elements.
            outputWidth >>= 1;
            unsigned int width16 = storedWidth >> 1;
            unsigned int sourcePitch = stridePixels >> 1;
            unsigned int* out = static_cast<unsigned int*>(output);
            unsigned int* input = reinterpret_cast<unsigned int*>(pixels);
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < width16; x++)
                    out[y * outputWidth + x] = input[y * sourcePitch + x];
            }
            break;
        }
        case 24:
        case 32: {
            unsigned int* out = static_cast<unsigned int*>(output);
            unsigned int* input = reinterpret_cast<unsigned int*>(pixels);
            for (unsigned int y = 0; y < storedHeight; y++) {
                for (unsigned int x = 0; x < storedWidth; x++)
                    out[y * outputWidth + x] = input[y * stridePixels + x];
            }
        }
        }
    }
}
