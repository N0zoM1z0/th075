#pragma once
#include "SpriteDraw40CA80.hpp"

// Pointer-only interfaces; complete original owner/bitmap layouts are unknown.
class BitmapUpload40C590 { public: void CopyTo(void*, unsigned char, unsigned int); };
class TextureUpload40C730 {
public:
    void Upload(BitmapUpload40C590*, IDirect3DTexture8**);
    void UploadByHandle(BitmapUpload40C590*, int);
};

typedef char SurfaceSize40C730[(sizeof(D3DSURFACE_DESC) == 32) ? 1 : -1];
typedef char SurfaceWidth40C730[(offsetof(D3DSURFACE_DESC, Width) == 24) ? 1 : -1];
typedef char LockSize40C730[(sizeof(D3DLOCKED_RECT) == 8) ? 1 : -1];
typedef char LockBits40C730[(offsetof(D3DLOCKED_RECT, pBits) == 4) ? 1 : -1];
