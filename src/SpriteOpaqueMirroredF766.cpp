#include "SpriteDraw40CA80.hpp"
#include "GraphicsTexturedDraw.hpp"
#include <windows.h>
// R011 0040D6B0: actual 132-byte native quad with real 0040DB50 RECT ctor.
class RectQuadF765 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    RenderQuadPayload5E68C0 payload;
    RectQuadF765(const RECT*);
};
typedef char AssertRectQuadF765[(sizeof(RectQuadF765)==132)?1:-1];
struct SpriteEntryF765 {DWORD unknown0;int rightAt4;int bottomAt8;};
class SpriteRecordListF765 {public: SpriteEntryF765* At(int);};
namespace Graphics {
void SetBlendMode(int);
void DrawTexturedQuad(const RectQuadF765&,const RECT*,D3DCOLOR,IDirect3DTexture8*);
}
class SpriteDrawingF765 {
public:
    IDirect3DTexture8* GetTexture(int);
    void DrawOpaqueSpriteMirrored(int texture,int x,int y,DWORD color,unsigned char flip);
};
void SpriteDrawingF765::DrawOpaqueSpriteMirrored(int texture,int x,int y,DWORD color,unsigned char flip) {
    RECT textureBounds;
    textureBounds.left=0;
    textureBounds.top=0;
    textureBounds.right=reinterpret_cast<SpriteRecordListF765*>(reinterpret_cast<char*>(this)+8)->At(texture)->rightAt4;
    textureBounds.bottom=reinterpret_cast<SpriteRecordListF765*>(reinterpret_cast<char*>(this)+8)->At(texture)->bottomAt8;
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
    Graphics::DrawTexturedQuad(RectQuadF765(&destination),&textureBounds,color,GetTexture(texture));
    }
}
