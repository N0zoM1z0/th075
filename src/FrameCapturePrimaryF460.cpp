#include "GraphicsCopy.hpp"
#include "WindowOverlayF212.hpp"

struct NativeCaptureArgumentsF460 {
    RECT rectangle;
    IDirect3DTexture8* backbuffer;
};

void WindowOverlayF212::CapturePrimary()
{
    NativeCaptureArgumentsF460 state;
    state.backbuffer=Graphics::GetPrimaryTargetTexture();
    SetRect(&state.rectangle,0,0,640,480);
    Graphics::CopyTextureOpaque(&texture,&state.backbuffer,&state.rectangle);
}
