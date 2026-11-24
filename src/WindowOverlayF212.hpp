#ifndef TH075_WINDOW_OVERLAY_F212_HPP
#define TH075_WINDOW_OVERLAY_F212_HPP

#include <windows.h>
#include <d3d8.h>

class SpriteQuad40CA80;

// The 8-byte owner allocated by GameGlobals::InitializeSound. Its constructor
// initializes a black D3D8 texture; GameGlobals::Release destroys the same
// owner through the scalar-deleting wrapper at 0041A140. The nominal class
// name is inferred; only the observed pointer and byte state are modeled.
class WindowOverlayF212 {
    IDirect3DTexture8* texture; // +0x00
    unsigned char enabled;      // +0x04

public:
    WindowOverlayF212();
    ~WindowOverlayF212();
    void CapturePrimary();
    void InstallPresentCallback();
    void EnableDirectDraw();
    void DrawIfEnabled(const SpriteQuad40CA80& quad, const RECT* rectangle, DWORD color);
};

extern WindowOverlayF212* g_WindowOverlayAt006714C4;

typedef char AssertWindowOverlaySizeF212[
    (sizeof(WindowOverlayF212) == 8) ? 1 : -1];

#endif
