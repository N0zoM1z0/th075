#include <windows.h>
#include <d3d8.h>
// Complete observed native black-surface initializer: original actual
// D3D8 texture LockRect/UnlockRect, 640x480 black pixels in 1024-pitch map.
// The private resource owner has only a proven texture pointer at +0
// and the observed byte state at +4; no private extension is inferred.
extern void __cdecl CreateBlackSurfaceAt00401C20(int width,int height,IDirect3DTexture8** output,int format);
class BlackSurfaceF459 {
    IDirect3DTexture8* texture;
    unsigned char enabled;
public: BlackSurfaceF459* InitializeBlackSurface();
};
BlackSurfaceF459* BlackSurfaceF459::InitializeBlackSurface() {
    CreateBlackSurfaceAt00401C20(1024,512,&texture,32);
    D3DLOCKED_RECT locked;
    texture->LockRect(0,&locked,0,0);
    for(int x=0;x<640;++x) {
      for(int y=0;y<480;++y)
        reinterpret_cast<DWORD*>(locked.pBits)[y*1024+x]=0xFF000000;
    }
    texture->UnlockRect(0);
    enabled=0;
    return this;
}
