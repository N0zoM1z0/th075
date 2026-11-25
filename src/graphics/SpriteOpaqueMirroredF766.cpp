#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "graphics/GraphicsTexturedDraw.hpp"
#include "graphics/SpriteGeometryF211.hpp"
#include <windows.h>
void TextureManagerF198::DrawOpaqueSpriteMirrored(int texture,int x,int y,DWORD color,unsigned char flip) {
    RECT textureBounds;
    textureBounds.left=0;
    textureBounds.top=0;
    textureBounds.right=entries[texture].storedWidth;
    textureBounds.bottom=entries[texture].storedHeight;
    {RECT destination;
    if (flip & 1) {
        destination.right=x;
        destination.left=x+textureBounds.right;
        destination.top=y;
        destination.bottom=y+textureBounds.bottom;
    } else {
        destination.left=x;
        destination.right=x+textureBounds.right;
        destination.top=y;
        destination.bottom=y+textureBounds.bottom;
    }
    Graphics::SetBlendMode(0);
    Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(
        &static_cast<const SpriteRectF211&>(SpriteRectF211(&destination))),
        &textureBounds, color, GetTexture(texture));
    }
}
