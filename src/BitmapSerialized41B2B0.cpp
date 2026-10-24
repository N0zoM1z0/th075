#include <windows.h>
#include <stddef.h>
#include <string.h>

// Complete source-compatible descriptor, identical to the accepted save value.
// The original type name and grouping remain unknown.
struct TextureRecordSnapshot40BF60 {
    int width, height, stride;
    unsigned char depth;
    DWORD encodedSize;
    void* data;
};
typedef char RecordSize41B2B0[(sizeof(TextureRecordSnapshot40BF60) == 24) ? 1 : -1];
typedef char RecordDepth41B2B0[(offsetof(TextureRecordSnapshot40BF60, depth) == 12) ? 1 : -1];
typedef char RecordEncoded41B2B0[(offsetof(TextureRecordSnapshot40BF60, encodedSize) == 16) ? 1 : -1];
typedef char RecordData41B2B0[(offsetof(TextureRecordSnapshot40BF60, data) == 20) ? 1 : -1];

// Pointer-only owner view; never instantiate or embed this incomplete owner.
class BitmapSerialized41B2B0 {
public:
    void Load(const TextureRecordSnapshot40BF60*);
};
#define FORMAT (*reinterpret_cast<BYTE*>(this))
#define WIDTH (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 4))
#define HEIGHT (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 8))
#define STRIDE (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 12))
#define ENCODED_SIZE (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 16))
#define PIXELS (*reinterpret_cast<BYTE**>(reinterpret_cast<char*>(this) + 28))

void BitmapSerialized41B2B0::Load(const TextureRecordSnapshot40BF60* record) {
    WIDTH = record->width;
    HEIGHT = record->height;
    STRIDE = record->stride;
    FORMAT = record->depth;
    ENCODED_SIZE = record->encodedSize;
    if (ENCODED_SIZE > 0) {
        PIXELS = new BYTE[ENCODED_SIZE];
        memcpy(PIXELS, record->data, ENCODED_SIZE);
    } else if (FORMAT >= 24) {
        PIXELS = new BYTE[STRIDE * HEIGHT * 4];
        memcpy(PIXELS, record->data, STRIDE * HEIGHT * 4);
    } else {
        PIXELS = new BYTE[(STRIDE * HEIGHT * FORMAT) >> 3];
        memcpy(PIXELS, record->data, (STRIDE * HEIGHT * FORMAT) >> 3);
    }
}

#undef FORMAT
#undef WIDTH
#undef HEIGHT
#undef STRIDE
#undef ENCODED_SIZE
#undef PIXELS
