#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/TextureManagerF198.hpp"

typedef char SurfaceDescriptionSize40C590[(sizeof(D3DSURFACE_DESC) == 32) ? 1 : -1];
typedef char SurfaceWidthOffset40C590[(offsetof(D3DSURFACE_DESC, Width) == 24) ? 1 : -1];
typedef char LockedRectSize40C590[(sizeof(D3DLOCKED_RECT) == 8) ? 1 : -1];
typedef char LockedBitsOffset40C590[(offsetof(D3DLOCKED_RECT, pBits) == 4) ? 1 : -1];

#define ENTRY entries[index]

void TextureManagerF198::Refresh(int index) {
    if (index < 0 || index >= static_cast<int>(textures.size()))
        return;
    // The target snapshots these three real metadata fields before selection.
    // Their values have no later consumer in this function.
    int width = ENTRY.storedWidth;
    int height = ENTRY.storedHeight;
    int metadataAt0C = ENTRY.storedStride;
    unsigned int surfaceWidth;
    IDirect3DTexture8* pTexture;
    if (ENTRY.paletteFlag) {
        surfaceWidth = 256;
        pTexture = paletteTextures[0];
    } else {
        IDirect3DSurface8* surface;
        D3DSURFACE_DESC desc;
        textures[index]->GetSurfaceLevel(0, &surface);
        surface->GetDesc(&desc);
        surfaceWidth = desc.Width;
        pTexture = textures[index];
        surface->Release();
    }
    D3DLOCKED_RECT rect;
    HRESULT result = pTexture->LockRect(0, &rect, 0, 0);
    if (result == D3D_OK) {
        ENTRY.CopyTo(
            rect.pBits, ENTRY.uploadFormat, surfaceWidth);
        pTexture->UnlockRect(0);
    }
}

#undef ENTRY
