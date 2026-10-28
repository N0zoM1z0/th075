#include <windows.h>
// Independently full R100 original 65-byte frame capture. The native
// actual RECT 16-byte region followed by real 4-byte captured surface
// handle are two *used* contiguous fields, not inert padding. A physical
// 20-byte capture state reproduces true original EBP -0x14..-0x4 slots.
// Full observed 65-byte original frame capture: get real backbuffer/owner
// handle; set exact 640x480 source rectangle; copy via native game function.
struct NativeCaptureArgumentsF460 { RECT rectangle; unsigned int backbuffer; };
typedef char CheckCaptureArgs20F460[(sizeof(NativeCaptureArgumentsF460)==20)?1:-1];
class FrameCaptureF460 {public:void CapturePrimary();};
extern unsigned int __cdecl GetPresentBufferAt004028B0();
extern void __cdecl CapturePresentRectAt00401D80(FrameCaptureF460*,const unsigned int*,const RECT*);
void FrameCaptureF460::CapturePrimary() {
    NativeCaptureArgumentsF460 state;
    state.backbuffer=GetPresentBufferAt004028B0();
    SetRect(&state.rectangle,0,0,640,480);
    CapturePresentRectAt00401D80(this,&state.backbuffer,&state.rectangle);
}
