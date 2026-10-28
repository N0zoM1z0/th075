#include <windows.h>
#include <d3d8.h>
// Independently exact native R100 authored 98-byte D3D8 presentation.
// The borrowed quad storage has 132 known geometry bytes and 136
// observed physical stack bytes; its final four are untyped.
// Native whole 98-byte draw: a 16-byte actual 640x480 source RECT
// contiguous with native 136-byte physical quad carrier, real local usage.
class NativeQuadF461 {
    unsigned int physicalWords[34];
public: void InitializeFromRectangle(const RECT*);
};
struct NativePresentFrameF461 {
    RECT rectangle;
    NativeQuadF461 quad;
};
typedef char Frame152F461[(sizeof(NativePresentFrameF461)==152)?1:-1];
extern void __cdecl SetGraphicsModeAt00401F50(int);
extern void __cdecl DrawTexturedQuadAt004029F0(const NativeQuadF461*,const RECT*,unsigned int,IDirect3DTexture8*);
namespace FrameCapturePresentF461 { void PresentPrimary(IDirect3DTexture8** texture); }
void FrameCapturePresentF461::PresentPrimary(IDirect3DTexture8** texture) {
    NativePresentFrameF461 frame;
    SetRect(&frame.rectangle,0,0,640,480);
    frame.quad.InitializeFromRectangle(&frame.rectangle);
    SetGraphicsModeAt00401F50(0);
    DrawTexturedQuadAt004029F0(&frame.quad,&frame.rectangle,0xffffffff,*texture);
}
