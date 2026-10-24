#include <windows.h>

// Pointer-only view of the bitmap owner. Its complete layout is unresolved;
// never instantiate, embed, or use sizeof this declaration.
class BitmapLifecycle41A2D0 {
public:
    BitmapLifecycle41A2D0();
    explicit BitmapLifecycle41A2D0(BYTE format);
    ~BitmapLifecycle41A2D0();
};
#define FORMAT (*reinterpret_cast<BYTE*>(this))
#define ENCODED_SIZE (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 16))
#define PALETTE (*reinterpret_cast<WORD**>(reinterpret_cast<char*>(this) + 20))
#define OWNS_PALETTE (*reinterpret_cast<BYTE*>(reinterpret_cast<char*>(this) + 24))
#define PIXELS (*reinterpret_cast<BYTE**>(reinterpret_cast<char*>(this) + 28))

BitmapLifecycle41A2D0::BitmapLifecycle41A2D0() {
    FORMAT = 0;
    PIXELS = 0;
    PALETTE = 0;
    ENCODED_SIZE = 0;
    OWNS_PALETTE = 0;
}

BitmapLifecycle41A2D0::BitmapLifecycle41A2D0(BYTE format) {
    if (format != 8 && format != 16 && format != 24 && format != 32)
        FORMAT = 0;
    else
        FORMAT = format;
    PIXELS = 0;
    PALETTE = 0;
    ENCODED_SIZE = 0;
    OWNS_PALETTE = 0;
}

BitmapLifecycle41A2D0::~BitmapLifecycle41A2D0() {
    if (PIXELS)
        delete[] PIXELS;
    if (OWNS_PALETTE)
        delete[] PALETTE;
}

#undef FORMAT
#undef ENCODED_SIZE
#undef PALETTE
#undef OWNS_PALETTE
#undef PIXELS
