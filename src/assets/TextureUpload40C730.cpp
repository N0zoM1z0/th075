#include "graphics/TextureManagerF198.hpp"

void TextureManagerF198::UploadBitmap(TextureEntryStorageF769* bitmap, IDirect3DTexture8** textureSlot) {
    // These three genuine target reads/stores have no later consumer here.
    int width = bitmap->storedWidth;
    int height = bitmap->storedHeight;
    int metadataAt0C = bitmap->stridePixels;
    IDirect3DSurface8* pSurface;
    D3DSURFACE_DESC desc;
    (*textureSlot)->GetSurfaceLevel(0, &pSurface);
    pSurface->GetDesc(&desc);
    unsigned int surfaceWidth = desc.Width;
    IDirect3DTexture8* pTexture = *textureSlot;
    pSurface->Release();
    D3DLOCKED_RECT lockInfo;
    HRESULT result = pTexture->LockRect(0, &lockInfo, 0, 0);
    if (result == D3D_OK) {
        bitmap->CopyTo(lockInfo.pBits, bitmap->bitsPerPixel, surfaceWidth);
        pTexture->UnlockRect(0);
    }
}

void TextureManagerF198::UploadBitmapByIndex(TextureEntryStorageF769* bitmap, int index) {
    IDirect3DTexture8* texture = GetTexture(index);
    if (!texture)
        return;
    UploadBitmap(bitmap, &texture);
}
