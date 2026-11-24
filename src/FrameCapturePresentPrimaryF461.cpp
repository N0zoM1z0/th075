#include "Graphics.hpp"
#include "GraphicsTexturedDraw.hpp"
#include <windows.h>
#include <d3d8.h>
#include "SpriteGeometryF211.hpp"

namespace FrameCapturePresentF461 { void PresentPrimary(IDirect3DTexture8** texture); }

void FrameCapturePresentF461::PresentPrimary(IDirect3DTexture8** texture)
{
    RECT region;
    SetRect(&region, 0, 0, 640, 480);
    SpriteRectF211 spriteQuad(&region);
    Graphics::SetBlendMode(0);
    Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&spriteQuad),
        &region, 0xffffffff, *texture);
}
