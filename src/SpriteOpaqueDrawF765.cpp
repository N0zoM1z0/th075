#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include "GraphicsTexturedDraw.hpp"
#include "SpriteGeometryF211.hpp"
#include <windows.h>
void TextureManagerF198::DrawOpaqueSprite(int texture,int x,int y,DWORD color) {
    RECT textureBounds;
    textureBounds.left=0;
    textureBounds.top=0;
    textureBounds.right=entries[texture].storedWidth;
    textureBounds.bottom=entries[texture].storedHeight;
    {RECT destination;
    destination.left=x;
    destination.right=x+textureBounds.right;
    destination.top=y;
    destination.bottom=y+textureBounds.bottom;
    Graphics::SetBlendMode(0);
    Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(
        &static_cast<const SpriteRectF211&>(SpriteRectF211(&destination))),
        &textureBounds, color, GetTexture(texture));
    }
}
