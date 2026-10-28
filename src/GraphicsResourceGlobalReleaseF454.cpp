#include <windows.h>
#include <d3d8.h>
// Complete original R056 239-byte global graphics client teardown. The
// returned COM reference count is physically stored by the original
// instruction `mov [ebp-8],eax` even though not subsequently consumed;
// this is an observed live native return value, not an arbitrary stack pad.
// Only the actual indexed + singleton COM interface ABI is modeled.
// Complete original global graphics resources last-user teardown policy.
// These are real IUnknown-derived D3D8 resources and real native globals.
extern unsigned int g_GraphicsClientCountAt00671210;
extern IDirect3DTexture8* g_GraphicsTextureSetAt006711D4[1];
extern IDirect3DSurface8* g_GraphicsSurfaceSetAt006711FC[1];
extern IDirect3DTexture8* g_GraphicsExtraTextureAt00671230;
extern IDirect3DSurface8* g_GraphicsExtraSurfaceAt0067122C;
class GraphicsResourceClientF453 {public:~GraphicsResourceClientF453();};
GraphicsResourceClientF453::~GraphicsResourceClientF453() {
    if (--g_GraphicsClientCountAt00671210 == 0) {
        for(int index=0;index<1;++index) {
            if(g_GraphicsTextureSetAt006711D4[index]) {
                g_GraphicsTextureSetAt006711D4[index]->Release();
                g_GraphicsTextureSetAt006711D4[index]=0;
            }
            if(g_GraphicsSurfaceSetAt006711FC[index]) {
                g_GraphicsSurfaceSetAt006711FC[index]->Release();
                g_GraphicsSurfaceSetAt006711FC[index]=0;
            }
        }
        if(g_GraphicsExtraTextureAt00671230) {
            ULONG remainingRefCount = g_GraphicsExtraTextureAt00671230->Release();
            g_GraphicsExtraTextureAt00671230=0;
        }
        if(g_GraphicsExtraSurfaceAt0067122C) {
            g_GraphicsExtraSurfaceAt0067122C->Release();
            g_GraphicsExtraSurfaceAt0067122C=0;
        }
    }
}
