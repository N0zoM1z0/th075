// Pointer-only bitmap interface; complete original owner layout remains unknown.
class BitmapUpload40C590 { public: void CopyTo(void*, unsigned char, unsigned int); };
#define FIELD(type, sourceIndex) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (sourceIndex)))
#define WIDTH FIELD(unsigned int, 4)
#define HEIGHT FIELD(unsigned int, 8)
#define STRIDE FIELD(unsigned int, 12)
#define ENCODED FIELD(unsigned int, 16)
#define PALETTE FIELD(unsigned short*, 20)
#define PIXELS FIELD(void*, 28)

void BitmapUpload40C590::CopyTo(void* output, unsigned char depth, unsigned int outputWidth) {
    if (ENCODED) {
        switch (depth) {
        case 8: {
            unsigned short* out = static_cast<unsigned short*>(output);
            unsigned char* input = static_cast<unsigned char*>(PIXELS);
            unsigned int consumedPixels = 0;
            unsigned int sourceIndex = 0;
            unsigned int runLength = input[0];
            unsigned short value = PALETTE[input[1]];
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    out[y * outputWidth + x] = value;
                    consumedPixels++;
                    if (consumedPixels >= runLength) {
                        sourceIndex += 2;
                        // Preserve the native unsigned run-overflow boolean.
                        consumedPixels = consumedPixels > runLength;
                        if (x == WIDTH - 1 && y == HEIGHT - 1)
                            break;
                        runLength = input[sourceIndex];
                        value = PALETTE[input[sourceIndex + 1]];
                    }
                }
            }
            break;
        }
        case 16: {
            unsigned short* out = static_cast<unsigned short*>(output);
            unsigned short* input = static_cast<unsigned short*>(PIXELS);
            unsigned int consumedPixels = 0;
            unsigned int sourceIndex = 0;
            unsigned int runLength = input[0];
            unsigned short value = input[1];
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    out[y * outputWidth + x] = value;
                    consumedPixels++;
                    if (consumedPixels >= runLength) {
                        sourceIndex += 2;
                        consumedPixels = 0;
                        if (x == WIDTH - 1 && y == HEIGHT - 1)
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
            unsigned int* input = static_cast<unsigned int*>(PIXELS);
            unsigned int consumedPixels = 0;
            unsigned int sourceIndex = 0;
            unsigned int runLength = input[0];
            unsigned int value = input[1];
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    out[y * outputWidth + x] = value;
                    consumedPixels++;
                    if (consumedPixels >= runLength) {
                        sourceIndex += 2;
                        consumedPixels = 0;
                        if (x == WIDTH - 1 && y == HEIGHT - 1)
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
            unsigned char* input = static_cast<unsigned char*>(PIXELS);
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++)
                    out[y * outputWidth + x] = PALETTE[input[y * STRIDE + x]];
            }
            break;
        }
        case 16: {
            // Native 16-bit copying groups pairs into DWORD elements.
            outputWidth >>= 1;
            unsigned int width16 = WIDTH >> 1;
            unsigned int sourcePitch = STRIDE >> 1;
            unsigned int* out = static_cast<unsigned int*>(output);
            unsigned int* input = static_cast<unsigned int*>(PIXELS);
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < width16; x++)
                    out[y * outputWidth + x] = input[y * sourcePitch + x];
            }
            break;
        }
        case 24:
        case 32: {
            unsigned int* out = static_cast<unsigned int*>(output);
            unsigned int* input = static_cast<unsigned int*>(PIXELS);
            for (unsigned int y = 0; y < HEIGHT; y++) {
                for (unsigned int x = 0; x < WIDTH; x++)
                    out[y * outputWidth + x] = input[y * STRIDE + x];
            }
        }
        }
    }
}
#undef PIXELS
#undef PALETTE
#undef ENCODED
#undef STRIDE
#undef HEIGHT
#undef WIDTH
#undef FIELD
