#include "TextureUpload40C730.hpp"

void TextureUpload40C730::Upload(BitmapUpload40C590* bitmap, IDirect3DTexture8** textureSlot) {
    // These three genuine target reads/stores have no later consumer here.
    int width = *reinterpret_cast<int*>(reinterpret_cast<char*>(bitmap) + 4);
    int height = *reinterpret_cast<int*>(reinterpret_cast<char*>(bitmap) + 8);
    int metadataAt0C = *reinterpret_cast<int*>(reinterpret_cast<char*>(bitmap) + 12);
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
        bitmap->CopyTo(lockInfo.pBits, *reinterpret_cast<unsigned char*>(bitmap), surfaceWidth);
        pTexture->UnlockRect(0);
    }
}

void TextureUpload40C730::UploadByHandle(BitmapUpload40C590* bitmap, int index) {
    IDirect3DTexture8* texture = reinterpret_cast<SpriteTextures40CA80*>(this)->GetTexture(index);
    if (!texture)
        return;
    Upload(bitmap, &texture);
}
