#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include "GraphicsTexturedDraw.hpp"
#include "SpriteGeometryF211.hpp"
#include <windows.h>
class SpriteDrawingF765 {
public:
    void DrawOpaqueSprite(int texture,int x,int y,DWORD color);
};
void SpriteDrawingF765::DrawOpaqueSprite(int texture,int x,int y,DWORD color) {
    RECT textureBounds;
    textureBounds.left=0;
    textureBounds.top=0;
    textureBounds.right=reinterpret_cast<TextureManagerF198*>(this)->entries[texture].storedWidth;
    textureBounds.bottom=reinterpret_cast<TextureManagerF198*>(this)->entries[texture].storedHeight;
    {RECT destination;
    destination.left=x;
    destination.right=x+textureBounds.right;
    destination.top=y;
    destination.bottom=y+textureBounds.bottom;
    Graphics::SetBlendMode(0);
    Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(
        &static_cast<const SpriteRectF211&>(SpriteRectF211(&destination))),
        &textureBounds, color, reinterpret_cast<SpriteTextures40CA80*>(this)->GetTexture(texture));
    }
}
