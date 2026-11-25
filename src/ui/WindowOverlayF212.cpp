#include "ui/WindowOverlayF212.hpp"
#include "graphics/GraphicsTexture.hpp"

WindowOverlayF212* g_WindowOverlayAt006714C4;

// Native constructor at 00417000. It creates a 1024x512 texture, clears the
// visible 640x480 region to opaque black, then disables the overlay.
WindowOverlayF212::WindowOverlayF212()
{
    Graphics::CreateTexture(1024, 512, &texture, 32);

    D3DLOCKED_RECT locked;
    texture->LockRect(0, &locked, 0, 0);
    for (int x = 0; x < 640; ++x) {
        for (int y = 0; y < 480; ++y) {
            reinterpret_cast<DWORD*>(locked.pBits)[y * 1024 + x] = 0xFF000000;
        }
    }
    texture->UnlockRect(0);
    enabled = 0;
}

// Native destructor at 004170B0. The texture is the first owner field and
// its COM Release slot is called directly, as in the original object.
WindowOverlayF212::~WindowOverlayF212()
{
    texture->Release();
}
