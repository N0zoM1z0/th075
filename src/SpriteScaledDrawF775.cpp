#include "GeometryConstants.hpp"
#include "FloatConstants.hpp"
#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include "GraphicsTexturedDraw.hpp"
#include <windows.h>
// R011 0040D2E0: original complete 970-B source. Native ctor/copy
// lifetimes include 132-B quad, nested real RECT, two scale axes,
// cosine/sine rotation and genuine quad vector swapping. Three x87
// source evaluation orders were independently decoded from original PE.
// Historical owner/private payload meanings remain provisional.
class SpriteDrawingF775 {
public:
    void DrawScaled(int texture,float x,float y,DWORD color,
         float pivotX,float pivotY,float scaleX,float scaleY,
         float angle,unsigned char flags);
};
float __cdecl CameraCosineAt0040D900(float);
float __cdecl CameraSineAt0040D940(float);
#define ENTRY reinterpret_cast<TextureManagerF198*>(this)->entries[texture]
void SpriteDrawingF775::DrawScaled(int texture,float x,float y,DWORD color,
    float pivotX,float pivotY,float scaleX,float scaleY,float angle,unsigned char flags) {
    SpriteQuad40CA80 quad;
    { RECT region;
    region.left=0;
    region.top=0;
    region.right=ENTRY.storedWidth;
    region.bottom=ENTRY.storedHeight;
    if (scaleX==1.0f && scaleY==1.0f && angle==FloatConstants::Zero) {
        quad=SpriteQuad40CA80(x-pivotX,y-pivotY,
             x-pivotX+region.right,y-pivotY+region.bottom);
    } else if (angle==FloatConstants::Zero) {
        quad=SpriteQuad40CA80(x-pivotX*scaleX,y-pivotY*scaleY,
             (region.right-pivotX)*scaleX+x,
             (region.bottom-pivotY)*scaleY+y);
    } else {
        float cosine=CameraCosineAt0040D900(angle*GeometryConstants::RadiansPerDegree);
        float sine=CameraSineAt0040D940(angle*GeometryConstants::RadiansPerDegree);
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
         &region,color,reinterpret_cast<SpriteTextures40CA80*>(this)->GetTexture(texture));
    }
}
#undef ENTRY
