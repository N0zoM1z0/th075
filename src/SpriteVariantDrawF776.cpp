#include "SpriteDraw40CA80.hpp"
#include "GraphicsTexturedDraw.hpp"
#include <windows.h>
// R011 0040CEF0: full original 994-B variant source, native ctor/copy
// lifetimes include 132-B quad, nested real RECT, alternate native
// scale/no-angle path, cosine/sine rotation and actual vector swapping.
// Branch-source order is native: scale!=1 & angle==0 first, then rotation.
// Historical owner/private payload meanings remain provisional.
class SpriteScaledQuadF776 {
public:
    D3DXVECTOR4 first, second, third, fourth;
    RenderQuadPayload5E68C0 payload;
    SpriteScaledQuadF776();
    SpriteScaledQuadF776(float,float,float,float);
};
typedef char ScaledQuadSizeF776[(sizeof(SpriteScaledQuadF776)==132)?1:-1];
class SpriteScaledListF776 {public: void* At(unsigned int);};
class SpriteDrawingF776 {
public:
    IDirect3DTexture8* GetTexture(int);
    void DrawBase(int texture,float x,float y,DWORD color,
         float pivotX,float pivotY,float scale,float angle,unsigned char flags);
    void DrawVariant(int texture,float x,float y,DWORD color,
         float pivotX,float pivotY,float scale,float angle,
         unsigned char flags,unsigned char mode);
};
extern float g_ZeroAngleF776;
extern float g_AngleUnitF776;
float __cdecl CosAt0040D900(float);
float __cdecl SinAt0040D940(float);
#define ENTRY_AT(fld) (*reinterpret_cast<int*>(reinterpret_cast<char*>(reinterpret_cast<SpriteScaledListF776*>(reinterpret_cast<char*>(this)+8)->At(texture))+(fld)))
void SpriteDrawingF776::DrawVariant(int texture,float x,float y,DWORD color,
    float pivotX,float pivotY,float scale,float angle,
    unsigned char flags,unsigned char mode) {
    if (mode == 0) {
        DrawBase(texture,x,y,color,pivotX,pivotY,scale,angle,flags);
    } else {
    SpriteScaledQuadF776 quad;
    { RECT region;
    region.left=0;
    region.top=0;
    region.right=ENTRY_AT(4);
    region.bottom=ENTRY_AT(8);
    if (scale==1.0f && angle==g_ZeroAngleF776) {
        quad=SpriteScaledQuadF776(x-pivotX,y-pivotY,
             x-pivotX+region.right,y-pivotY+region.bottom);
    } else if (scale!=1.0f && angle==g_ZeroAngleF776) {
        quad=SpriteScaledQuadF776(x-pivotX*scale,y-pivotY*scale,
             (region.right-pivotX)*scale+x,
             (region.bottom-pivotY)*scale+y);
    } else {
        float cosine=CosAt0040D900(angle*g_AngleUnitF776)*scale;
        float sine=SinAt0040D940(angle*g_AngleUnitF776)*scale;
        quad.first.x=(x-pivotX*cosine)+pivotY*sine;
        quad.first.y=(y-pivotX*sine)-pivotY*cosine;
        quad.fourth.x=(x-pivotX*cosine)-(region.bottom-pivotY)*sine;
        quad.fourth.y=(y-pivotX*sine)+(region.bottom-pivotY)*cosine;
        quad.second.x=(region.right-pivotX)*cosine+x+pivotY*sine;
        quad.second.y=((region.right-pivotX)*sine+y)-pivotY*cosine;
        quad.third.x=((region.right-pivotX)*cosine+x)-(region.bottom-pivotY)*sine;
        quad.third.y=((region.right-pivotX)*sine+y)+(region.bottom-pivotY)*cosine;
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
}
#undef ENTRY_AT
