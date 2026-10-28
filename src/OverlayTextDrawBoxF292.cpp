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
class OverlayTextF292 {
public:
    void DrawBox();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define TRANSLATE(x,y) quad.Translate((x),(y),0.0f)
#define DRAW(color) OverlayDrawerF292::DrawQuad(&quad,&source,(color),FIELD(DWORD,0))
#define SCALE() quad.Scale(0.0f,39.0f,0.0f,1.0f,FIELD(DWORD,0x10),1.0f)
void OverlayTextF292::DrawBox()
{
    RECT source;
    OverlayQuadF292 quad;
    SetRect(&source,0,0,571,78);
    quad.AssignRect(&source);
    SCALE();
    quad.TranslateRaw(FIELD(DWORD,4),FIELD(DWORD,8),0);
    if (FIELD(unsigned char,0x25))
        reinterpret_cast<OverlayTextureF292*>(reinterpret_cast<unsigned char*>(this)+0x28)->ApplyMode(0,&quad,&source,0xffffffff);
    else
        FIELD(float,0x10)=1.0f;
    if (FIELD(float,0x10)<g_OverlayMinScaleAt0065747C) {
        FIELD(float,0x10)=FIELD(float,0x10)+g_OverlayScaleDeltaAt006578C0;
        return;
    }
    {
        SetRect(&source,0,0,571,(FIELD(unsigned char,0x24)+6)*FIELD(signed char,0x15));
        quad.BuildFromRect(&source);
        SCALE();
        quad.TranslateRaw(FIELD(DWORD,4),FIELD(DWORD,8),0);
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
        SetRect(&source,0,(FIELD(unsigned char,0x24)+6)*FIELD(signed char,0x15),571,128);
        quad.BuildFromRect(&source);
        SCALE();
        quad.TranslateRaw(FIELD(DWORD,4),FIELD(DWORD,8),0);
        if (FIELD(unsigned char,0x0c)<0xff)
            FIELD(unsigned char,0x0c)+=10;
        TRANSLATE(9.0f,9.0f);
        TRANSLATE(-1.0f,0.0f);
        DRAW(((static_cast<DWORD>(FIELD(unsigned char,0x0c))&0xffu)<<24));
        TRANSLATE(-1.0f,0.0f);
        TRANSLATE(0.0f,-1.0f);
        DRAW(((static_cast<DWORD>(FIELD(unsigned char,0x0c))&0xffu)<<24));
        TRANSLATE(0.0f,-1.0f);
        TRANSLATE(1.0f,0.0f);
        DRAW(((static_cast<DWORD>(FIELD(unsigned char,0x0c))&0xffu)<<24));
        TRANSLATE(1.0f,0.0f);
        TRANSLATE(0.0f,1.0f);
        DRAW(((static_cast<DWORD>(FIELD(unsigned char,0x0c))&0xffu)<<24));
        TRANSLATE(-1.0f,0.0f);
        DRAW((((static_cast<DWORD>(FIELD(unsigned char,0x0c))&0xffu)<<24))|0x00ff0000|0x0000ff00|0x000000ff);
    }
}
#undef SCALE
#undef DRAW
#undef TRANSLATE
#undef FIELD
