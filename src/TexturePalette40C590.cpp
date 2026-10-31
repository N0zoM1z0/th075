#include "SpriteDraw40CA80.hpp"
// These interfaces are pointer-only views; complete owner layouts are unknown.
class TexturePalette40C8C0 { public: void Refresh(int); };
class TextureHandles40C8C0 { public: IDirect3DTexture8*& At(unsigned int); };
class TextureHandleCount40C590 { public: unsigned int Size(); };
class BitmapUpload40C590 { public: void CopyTo(void*, unsigned char, unsigned int); };

typedef char SurfaceDescriptionSize40C590[(sizeof(D3DSURFACE_DESC) == 32) ? 1 : -1];
typedef char SurfaceWidthOffset40C590[(offsetof(D3DSURFACE_DESC, Width) == 24) ? 1 : -1];
typedef char LockedRectSize40C590[(sizeof(D3DLOCKED_RECT) == 8) ? 1 : -1];
typedef char LockedBitsOffset40C590[(offsetof(D3DLOCKED_RECT, pBits) == 4) ? 1 : -1];

// The pinned original getter uses these five observed entry offsets:
// signed 32-bit metadata at +4/+8/+0xC, bytes at +0 and +0x28.
// This is a BORROWED incomplete entry view; do not instantiate it,
// infer the full entry layout, or treat the unknown spans as fields.
struct NativeSpriteEntryViewF920 {
    unsigned char uploadFormatAt0;
    unsigned char unknown01to03[3];
    int storedWidthAt4;
    int storedHeightAt8;
    int metadataAt0C;
    unsigned char otherOccupied10to27[0x18];
    unsigned char paletteFlagAt28;
};
typedef char EntryF920FormatOffset[(offsetof(NativeSpriteEntryViewF920, uploadFormatAt0)==0)?1:-1];
typedef char EntryF920WidthOffset[(offsetof(NativeSpriteEntryViewF920, storedWidthAt4)==4)?1:-1];
typedef char EntryF920HeightOffset[(offsetof(NativeSpriteEntryViewF920, storedHeightAt8)==8)?1:-1];
typedef char EntryF920MetadataOffset[(offsetof(NativeSpriteEntryViewF920, metadataAt0C)==12)?1:-1];
typedef char EntryF920PaletteOffset[(offsetof(NativeSpriteEntryViewF920, paletteFlagAt28)==0x28)?1:-1];
#define ENTRIES reinterpret_cast<SpriteEntries40CA80*>(reinterpret_cast<char*>(this) + 8)
#define ENTRY_VIEW (*reinterpret_cast<NativeSpriteEntryViewF920*>(ENTRIES->At(index)))
#define HANDLES reinterpret_cast<TextureHandles40C8C0*>(reinterpret_cast<char*>(this) + 0x18)
#define HANDLE_COUNT reinterpret_cast<TextureHandleCount40C590*>(reinterpret_cast<char*>(this) + 0x18)
#define PALETTE_HANDLES reinterpret_cast<TextureHandles40C8C0*>(reinterpret_cast<char*>(this) + 0x28)

void TexturePalette40C8C0::Refresh(int index) {
    if (index < 0 || index >= static_cast<int>(HANDLE_COUNT->Size()))
        return;
    // The target snapshots these three real metadata fields before selection.
    // Their values have no later consumer in this function.
    int width = ENTRY_VIEW.storedWidthAt4;
    int height = ENTRY_VIEW.storedHeightAt8;
    int metadataAt0C = ENTRY_VIEW.metadataAt0C; // Meaning of this field remains unknown.
    unsigned int surfaceWidth;
    IDirect3DTexture8* pTexture;
    if (ENTRY_VIEW.paletteFlagAt28) {
        surfaceWidth = 256;
        pTexture = PALETTE_HANDLES->At(0);
    } else {
        IDirect3DSurface8* surface;
        D3DSURFACE_DESC desc;
        HANDLES->At(index)->GetSurfaceLevel(0, &surface);
        surface->GetDesc(&desc);
        surfaceWidth = desc.Width;
        pTexture = HANDLES->At(index);
        surface->Release();
    }
    D3DLOCKED_RECT rect;
    HRESULT result = pTexture->LockRect(0, &rect, 0, 0);
    if (result == D3D_OK) {
        reinterpret_cast<BitmapUpload40C590*>(ENTRIES->At(index))->CopyTo(
            rect.pBits, ENTRY_VIEW.uploadFormatAt0, surfaceWidth);
        pTexture->UnlockRect(0);
    }
}

#undef ENTRY_VIEW
#undef PALETTE_HANDLES
#undef HANDLE_COUNT
#undef HANDLES
#undef ENTRIES


