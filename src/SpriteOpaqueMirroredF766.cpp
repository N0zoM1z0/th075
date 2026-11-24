#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include "GraphicsTexturedDraw.hpp"
#include "SpriteGeometryF211.hpp"
#include <windows.h>
class SpriteDrawingF765 {
public:
    void DrawOpaqueSpriteMirrored(int texture,int x,int y,DWORD color,unsigned char flip);
};
void SpriteDrawingF765::DrawOpaqueSpriteMirrored(int texture,int x,int y,DWORD color,unsigned char flip) {
    RECT textureBounds;
    textureBounds.left=0;
    textureBounds.top=0;
    textureBounds.right=reinterpret_cast<TextureManagerF198*>(this)->entries[texture].storedWidth;
    textureBounds.bottom=reinterpret_cast<TextureManagerF198*>(this)->entries[texture].storedHeight;
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
        &textureBounds, color, reinterpret_cast<SpriteTextures40CA80*>(this)->GetTexture(texture));
    }
}
