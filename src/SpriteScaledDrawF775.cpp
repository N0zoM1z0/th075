#include "SpriteDraw40CA80.hpp"
#include "GraphicsTexturedDraw.hpp"
#include <windows.h>
// R011 0040D2E0: original complete 970-B source. Native ctor/copy
// lifetimes include 132-B quad, nested real RECT, two scale axes,
// cosine/sine rotation and genuine quad vector swapping. Three x87
// source evaluation orders were independently decoded from original PE.
// Historical owner/private payload meanings remain provisional.
class SpriteScaledQuadF775 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    RenderQuadPayload5E68C0 payload;
    SpriteScaledQuadF775();
    SpriteScaledQuadF775(float,float,float,float);
};
typedef char ScaledQuadSizeF775[(sizeof(SpriteScaledQuadF775)==132)?1:-1];
class SpriteScaledListF775 {public: void* At(unsigned int);};
class SpriteDrawingF775 {
public:
    IDirect3DTexture8* GetTexture(int);
    void DrawScaled(int texture,float x,float y,DWORD color,
         float pivotX,float pivotY,float scaleX,float scaleY,
         float angle,unsigned char flags);
};
extern float g_ZeroAngleF775;
extern float g_AngleUnitF775;
float __cdecl CosAt0040D900(float);
float __cdecl SinAt0040D940(float);
#define ENTRY_AT(fld) (*reinterpret_cast<int*>(reinterpret_cast<char*>(reinterpret_cast<SpriteScaledListF775*>(reinterpret_cast<char*>(this)+8)->At(texture))+(fld)))
void SpriteDrawingF775::DrawScaled(int texture,float x,float y,DWORD color,
    float pivotX,float pivotY,float scaleX,float scaleY,float angle,unsigned char flags) {
    SpriteScaledQuadF775 quad;
    { RECT region;
    region.left=0;
    region.top=0;
    region.right=ENTRY_AT(4);
    region.bottom=ENTRY_AT(8);
    if (scaleX==1.0f && scaleY==1.0f && angle==g_ZeroAngleF775) {
        quad=SpriteScaledQuadF775(x-pivotX,y-pivotY,
             x-pivotX+region.right,y-pivotY+region.bottom);
    } else if (angle==g_ZeroAngleF775) {
        quad=SpriteScaledQuadF775(x-pivotX*scaleX,y-pivotY*scaleY,
             (region.right-pivotX)*scaleX+x,
             (region.bottom-pivotY)*scaleY+y);
    } else {
        float cosine=CosAt0040D900(angle*g_AngleUnitF775);
        float sine=SinAt0040D940(angle*g_AngleUnitF775);
        quad.first.x=(x-pivotX*scaleX*cosine)+pivotY*sine;
        quad.first.y=(y-pivotX*scaleX*sine)-pivotY*cosine;
        quad.fourth.x=(x-pivotX*scaleX*cosine)-(region.bottom-pivotY)*scaleY*sine;
        quad.fourth.y=(y-pivotX*scaleX*sine)+(region.bottom-pivotY)*scaleY*cosine;
        quad.second.x=(region.right-pivotX)*scaleX*cosine+x+pivotY*scaleY*sine;
        quad.second.y=((region.right-pivotX)*scaleX*sine+y)-pivotY*scaleY*cosine;
        quad.third.x=((region.right-pivotX)*scaleX*cosine+x)-(region.bottom-pivotY)*scaleY*sine;
        quad.third.y=((region.right-pivotX)*scaleX*sine+y)+(region.bottom-pivotY)*scaleY*cosine;
    }
    if (flags & 1) {
        D3DXVECTOR4 temp;
        temp=quad.first;
        quad.first=quad.second;
        quad.second=temp;
        temp=quad.fourth;
        quad.fourth=quad.third;
        quad.third=temp;
    }
    Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&quad),
         &region,color,GetTexture(texture));
    }
}
#undef ENTRY_AT
