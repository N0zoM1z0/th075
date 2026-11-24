#include "SpriteDraw40CA80.hpp"
#include "GraphicsTexturedDraw.hpp"
#include "SpriteGeometryF211.hpp"
#include <windows.h>
struct SpriteEntryF765 {DWORD unknown0;int rightAt4;int bottomAt8;};
class SpriteRecordListF765 {public: SpriteEntryF765* At(int);};
class SpriteDrawingF765 {
public:
    void DrawOpaqueSprite(int texture,int x,int y,DWORD color);
};
void SpriteDrawingF765::DrawOpaqueSprite(int texture,int x,int y,DWORD color) {
    RECT textureBounds;
    textureBounds.left=0;
    textureBounds.top=0;
    textureBounds.right=reinterpret_cast<SpriteRecordListF765*>(reinterpret_cast<char*>(this)+8)->At(texture)->rightAt4;
    textureBounds.bottom=reinterpret_cast<SpriteRecordListF765*>(reinterpret_cast<char*>(this)+8)->At(texture)->bottomAt8;
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
