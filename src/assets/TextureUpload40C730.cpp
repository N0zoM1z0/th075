#include "graphics/TextureManagerF198.hpp"
#include "assets/TextureUpload40C730.hpp"
#include "graphics/TextureManagerBorrowedF925.hpp"

void TextureUpload40C730::Upload(TextureEntryStorageF769* bitmap, IDirect3DTexture8** textureSlot) {
    // These three genuine target reads/stores have no later consumer here.
    int width = bitmap->storedWidth;
    int height = bitmap->storedHeight;
    int metadataAt0C = bitmap->storedStride;
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
        bitmap->CopyTo(lockInfo.pBits, bitmap->uploadFormat, surfaceWidth);
        pTexture->UnlockRect(0);
    }
}

void TextureUpload40C730::UploadByHandle(TextureEntryStorageF769* bitmap, int index) {
    IDirect3DTexture8* texture = reinterpret_cast<TextureManagerF198*>(this)->GetTexture(index);
    if (!texture)
        return;
    Upload(bitmap, &texture);
}
