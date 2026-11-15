#include "TextOverlay.hpp"
#include <windows.h>

// 136 bytes are the actual native observed quad transformation extent on the
// stack. Its private geometry members are not asserted from caller accesses.
class OverlayQuadF292 {
    unsigned int observedPhysicalWords[34];
public:
    void AssignRect(const RECT* rect);
    void BuildFromRect(const RECT* rect);
    void Scale(float,float,float,float,DWORD,float);
    void Translate(float,float,float);
    void TranslateRaw(DWORD,DWORD,DWORD);
};
typedef char AssertOverlayQuadF292[(sizeof(OverlayQuadF292)==136)?1:-1];
namespace OverlayDrawerF292 {
    void DrawQuad(OverlayQuadF292* transformed,const RECT* source,DWORD tint,DWORD image);
}
class OverlayTextureF292 {public:
    void ApplyMode(int style,OverlayQuadF292* quad,const RECT* source,DWORD tint);
};
extern const float g_OverlayMinScaleAt0065747C;
extern const float g_OverlayScaleDeltaAt006578C0;
#define TRANSLATE(x,y) quad.Translate((x),(y),0.0f)
#define DRAW(color) OverlayDrawerF292::DrawQuad(&quad,&source,(color),reinterpret_cast<DWORD&>(texture))
#define SCALE() quad.Scale(0.0f,39.0f,0.0f,1.0f,reinterpret_cast<DWORD&>(field010),1.0f)
void TextOverlay::DrawBox()
{
    RECT source;
    OverlayQuadF292 quad;
    SetRect(&source,0,0,571,78);
    quad.AssignRect(&source);
    SCALE();
    quad.TranslateRaw((reinterpret_cast<DWORD&>(x)),(reinterpret_cast<DWORD&>(y)),0);
    if ((mode))
        reinterpret_cast<OverlayTextureF292*>(reinterpret_cast<unsigned char*>(this)+0x28)->ApplyMode(0,&quad,&source,0xffffffff);
    else
        (field010)=1.0f;
    if ((field010)<g_OverlayMinScaleAt0065747C) {
        (field010)=(field010)+g_OverlayScaleDeltaAt006578C0;
        return;
    }
    {
        SetRect(&source,0,0,571,((field024)+6)*(field015));
        quad.BuildFromRect(&source);
        SCALE();
        quad.TranslateRaw((reinterpret_cast<DWORD&>(x)),(reinterpret_cast<DWORD&>(y)),0);
        TRANSLATE(9.0f,9.0f);
        TRANSLATE(-1.0f,0.0f);
        DRAW(0xff000000);
        TRANSLATE(-1.0f,0.0f);
        TRANSLATE(0.0f,-1.0f);
        DRAW(0xff000000);
        TRANSLATE(0.0f,-1.0f);
        TRANSLATE(1.0f,0.0f);
        DRAW(0xff000000);
        TRANSLATE(1.0f,0.0f);
        TRANSLATE(0.0f,1.0f);
        DRAW(0xff000000);
        TRANSLATE(-1.0f,0.0f);
        DRAW(0xffffffff);
        SetRect(&source,0,((field024)+6)*(field015),571,128);
        quad.BuildFromRect(&source);
        SCALE();
        quad.TranslateRaw((reinterpret_cast<DWORD&>(x)),(reinterpret_cast<DWORD&>(y)),0);
        if ((field00C)<0xff)
            (field00C)+=10;
        TRANSLATE(9.0f,9.0f);
        TRANSLATE(-1.0f,0.0f);
        DRAW(((static_cast<DWORD>((field00C))&0xffu)<<24));
        TRANSLATE(-1.0f,0.0f);
        TRANSLATE(0.0f,-1.0f);
        DRAW(((static_cast<DWORD>((field00C))&0xffu)<<24));
        TRANSLATE(0.0f,-1.0f);
        TRANSLATE(1.0f,0.0f);
        DRAW(((static_cast<DWORD>((field00C))&0xffu)<<24));
        TRANSLATE(1.0f,0.0f);
        TRANSLATE(0.0f,1.0f);
        DRAW(((static_cast<DWORD>((field00C))&0xffu)<<24));
        TRANSLATE(-1.0f,0.0f);
        DRAW((((static_cast<DWORD>((field00C))&0xffu)<<24))|0x00ff0000|0x0000ff00|0x000000ff);
    }
}
#undef SCALE
#undef DRAW
#undef TRANSLATE
