#include "GraphicsTexture.hpp"
#include <stddef.h>
#include <new>

// Complete source-compatible value, identical to the accepted save/load views.
struct TextureRecordSnapshot40BF60 {
    int width, height, stride;
    unsigned char depth;
    DWORD encodedSize;
    void* data;
};

typedef char LoadRecordSize40B7C0[(sizeof(TextureRecordSnapshot40BF60) == 24) ? 1 : -1];
typedef char LoadRecordDepth40B7C0[(offsetof(TextureRecordSnapshot40BF60, depth) == 12) ? 1 : -1];
typedef char LoadRecordEncoded40B7C0[(offsetof(TextureRecordSnapshot40BF60, encodedSize) == 16) ? 1 : -1];
typedef char LoadRecordData40B7C0[(offsetof(TextureRecordSnapshot40BF60, data) == 20) ? 1 : -1];

// These owner/container interfaces are pointer-only and never instantiated.
class TextureEntryCount40C8C0 { public: unsigned int Size(); };
class SpriteEntries40CA80 { public: void* At(unsigned int); };
class TextureHandles40C8C0 { public: IDirect3DTexture8*& At(unsigned int); };
class TexturePalette40C8C0 { public: void Refresh(int); };
class BitmapSerialized41B2B0 { public: void Load(const TextureRecordSnapshot40BF60*); };
class TexturePackLoad40B7C0 {
public:
    void Load(const char*, signed char);
    void LoadDefault(const char*);
};

#define COUNTS reinterpret_cast<TextureEntryCount40C8C0*>(reinterpret_cast<char*>(this) + 8)
#define ENTRIES reinterpret_cast<SpriteEntries40CA80*>(reinterpret_cast<char*>(this) + 8)
#define HANDLES reinterpret_cast<TextureHandles40C8C0*>(reinterpret_cast<char*>(this) + 24)
#define PALETTE (*reinterpret_cast<WORD**>(reinterpret_cast<char*>(this) + 4))
#define FORMAT (*reinterpret_cast<BYTE*>(reinterpret_cast<char*>(this) + 76))
#define ENTRY_BYTE(offset) (*reinterpret_cast<BYTE*>(reinterpret_cast<char*>(ENTRIES->At(index)) + (offset)))
#define ENTRY_WORD(offset) (*reinterpret_cast<WORD*>(reinterpret_cast<char*>(ENTRIES->At(index)) + (offset)))
#define ENTRY_PALETTE (*reinterpret_cast<WORD**>(reinterpret_cast<char*>(ENTRIES->At(index)) + 20))
#define ENTRY_PIXELS (*reinterpret_cast<BYTE**>(reinterpret_cast<char*>(ENTRIES->At(index)) + 28))

void TexturePackLoad40B7C0::LoadDefault(const char* filename) {
    Load(filename, 0);
}

void TexturePackLoad40B7C0::Load(const char* filename, signed char selectedPalette) {
    int nEntriesCount = COUNTS->Size();
    HANDLE sourceFile = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                                    FILE_ATTRIBUTE_NORMAL, 0);
    int index;
    TextureRecordSnapshot40BF60 record;
    DWORD dwRead;
    signed char paletteHeaderCount;
    if (sourceFile == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(sourceFile, 0, 0, FILE_BEGIN);
    ReadFile(sourceFile, &paletteHeaderCount, 1, &dwRead, 0);
    if (PALETTE)
        delete[] PALETTE;
    if (paletteHeaderCount > 0) {
        PALETTE = new WORD[256];
        if (selectedPalette <= paletteHeaderCount) {
            SetFilePointer(sourceFile, (selectedPalette - 1) * 512, 0, FILE_CURRENT);
            ReadFile(sourceFile, PALETTE, 512, &dwRead, 0);
            SetFilePointer(sourceFile, (paletteHeaderCount - selectedPalette) * 512, 0, FILE_CURRENT);
        } else {
            ReadFile(sourceFile, PALETTE, 512, &dwRead, 0);
            SetFilePointer(sourceFile, (paletteHeaderCount - 1) * 512, 0, FILE_CURRENT);
        }
    } else {
        PALETTE = 0;
    }
    for (index = 0; index < nEntriesCount; index++) {
        ENTRY_BYTE(0) = FORMAT;
        ENTRY_PALETTE = PALETTE;
        ENTRY_BYTE(40) = 0;
        ReadFile(sourceFile, &record.width, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.height, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.stride, 4, &dwRead, 0);
        ReadFile(sourceFile, &record.depth, 1, &dwRead, 0);
        ReadFile(sourceFile, &record.encodedSize, 4, &dwRead, 0);
        if (record.encodedSize > 0) {
            record.data = new BYTE[record.encodedSize];
            ReadFile(sourceFile, record.data, record.encodedSize, &dwRead, 0);
        } else if (record.depth >= 24) {
            record.data = new BYTE[record.stride * record.height * 4];
            ReadFile(sourceFile, record.data, record.stride * record.height * 4, &dwRead, 0);
        } else {
            record.data = new BYTE[(static_cast<unsigned int>(record.stride * record.height) * record.depth) >> 3];
            ReadFile(sourceFile, record.data, (static_cast<unsigned int>(record.stride * record.height) * record.depth) >> 3, &dwRead, 0);
        }
        reinterpret_cast<BitmapSerialized41B2B0*>(ENTRIES->At(index))->Load(&record);
        delete[] static_cast<BYTE*>(record.data);
        Graphics::CreateTexture(ENTRY_WORD(4), ENTRY_WORD(8), &HANDLES->At(index), ENTRY_BYTE(0));
        reinterpret_cast<TexturePalette40C8C0*>(this)->Refresh(index);
        delete[] ENTRY_PIXELS;
        ENTRY_PIXELS = 0;
    }
    CloseHandle(sourceFile);
}

#undef ENTRY_PIXELS
#undef ENTRY_PALETTE
#undef ENTRY_WORD
#undef ENTRY_BYTE
#undef FORMAT
#undef PALETTE
#undef HANDLES
#undef ENTRIES
#undef COUNTS
