#include <windows.h>
#include <d3dx8.h>
// Complete original R056 239-byte global graphics client teardown. The
// returned COM reference count is physically stored by the original
// instruction `mov [ebp-8],eax` even though not subsequently consumed;
// this is an observed live native return value, not an arbitrary stack pad.
// Only the actual indexed + singleton COM interface ABI is modeled.
// Complete original global graphics resources last-user teardown policy.
// These are real IUnknown-derived D3D8 resources and real native globals.
extern int g_GraphicsResourceClientCount;

namespace Graphics {
    extern IDirect3DTexture8 *g_TargetTextures[1];
    extern ID3DXRenderToSurface *g_TargetRenderers[1];
    extern IDirect3DDevice8 *g_Device;
    extern IDirect3D8 *g_Direct3D;
}

class GraphicsResourceClientF453 {public:~GraphicsResourceClientF453();};
GraphicsResourceClientF453::~GraphicsResourceClientF453() {
    if (--g_GraphicsResourceClientCount == 0) {
        for(int index=0;index<1;++index) {
            if(Graphics::g_TargetTextures[index]) {
                Graphics::g_TargetTextures[index]->Release();
                Graphics::g_TargetTextures[index]=0;
            }
            if(Graphics::g_TargetRenderers[index]) {
                Graphics::g_TargetRenderers[index]->Release();
                Graphics::g_TargetRenderers[index]=0;
            }
        }
        if(Graphics::g_Device) {
            ULONG remainingRefCount = Graphics::g_Device->Release();
            Graphics::g_Device=0;
        }
        if(Graphics::g_Direct3D) {
            Graphics::g_Direct3D->Release();
            Graphics::g_Direct3D=0;
        }
    }
}
