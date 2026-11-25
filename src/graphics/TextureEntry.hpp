#pragma once
#include <windows.h>
#include <stddef.h>

struct TexturePackRecord;

// Storage for one complete 44-byte vector entry. Bitmap operations receive
// the entry address and access its leading fields.
struct TextureEntryStorageF769 {
    BYTE bitsPerPixel;
    BYTE unknown01[3];
    unsigned int storedWidth;
    unsigned int storedHeight;
    unsigned int stridePixels;        // row width including alignment
    DWORD compressedBytes;            // zero for uncompressed pixels
    WORD* palette;
    BYTE ownsPalette;
    BYTE unknown19[3];
    BYTE* pixels;
    BYTE unknown20[8];
    BYTE usesSharedPaletteTexture;     // upload through the shared GPU slot
    BYTE unknown29[3];

    bool LoadFile(const char* filename);
    void Encode();
    void LoadSerialized(const TexturePackRecord* record);
    void CopyTo(void* output, unsigned char depth, unsigned int outputWidth);

protected:
    TextureEntryStorageF769();
    explicit TextureEntryStorageF769(BYTE format);
    ~TextureEntryStorageF769();
};

struct NativeTextureElementF769 : public TextureEntryStorageF769 {
    NativeTextureElementF769();
    ~NativeTextureElementF769();
};
typedef char NativeTextureElementSizeF925[(sizeof(NativeTextureElementF769)==44)?1:-1];
typedef char TextureEntryOffsets[(offsetof(TextureEntryStorageF769, stridePixels) == 0x0C &&
                                 offsetof(TextureEntryStorageF769, compressedBytes) == 0x10 &&
                                 offsetof(TextureEntryStorageF769, usesSharedPaletteTexture) == 0x28) ? 1 : -1];
