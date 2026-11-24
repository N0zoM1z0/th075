#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
// These interfaces are pointer-only views; complete owner layouts are unknown.
class TexturePalette40C8C0 { public: void Refresh(int); };
class BitmapUpload40C590 { public: void CopyTo(void*, unsigned char, unsigned int); };

typedef char SurfaceDescriptionSize40C590[(sizeof(D3DSURFACE_DESC) == 32) ? 1 : -1];
typedef char SurfaceWidthOffset40C590[(offsetof(D3DSURFACE_DESC, Width) == 24) ? 1 : -1];
typedef char LockedRectSize40C590[(sizeof(D3DLOCKED_RECT) == 8) ? 1 : -1];
typedef char LockedBitsOffset40C590[(offsetof(D3DLOCKED_RECT, pBits) == 4) ? 1 : -1];

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)
#define ENTRY MANAGER->entries[index]

void TexturePalette40C8C0::Refresh(int index) {
    if (index < 0 || index >= static_cast<int>(MANAGER->textures.size()))
        return;
    // The target snapshots these three real metadata fields before selection.
    // Their values have no later consumer in this function.
    int width = ENTRY.storedWidth;
    int height = ENTRY.storedHeight;
    int metadataAt0C = ENTRY.storedStride; // Meaning of this field remains unknown.
    unsigned int surfaceWidth;
    IDirect3DTexture8* pTexture;
    if (ENTRY.paletteFlag) {
        surfaceWidth = 256;
        pTexture = MANAGER->paletteTextures[0];
    } else {
        IDirect3DSurface8* surface;
        D3DSURFACE_DESC desc;
        MANAGER->textures[index]->GetSurfaceLevel(0, &surface);
        surface->GetDesc(&desc);
        surfaceWidth = desc.Width;
        pTexture = MANAGER->textures[index];
        surface->Release();
    }
    D3DLOCKED_RECT rect;
    HRESULT result = pTexture->LockRect(0, &rect, 0, 0);
    if (result == D3D_OK) {
        reinterpret_cast<BitmapUpload40C590*>(&ENTRY)->CopyTo(
            rect.pBits, ENTRY.uploadFormat, surfaceWidth);
        pTexture->UnlockRect(0);
    }
}

#undef ENTRY
#undef MANAGER
