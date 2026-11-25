#include "graphics/TextOverlay.hpp"
#include "graphics/GraphicsTexturedDraw.hpp"
#include "graphics/SpriteGeometryF211.hpp"
#include "graphics/SpriteQuad.hpp"
#include "graphics/SpriteTransform.hpp"

#define TRANSFORM reinterpret_cast<SpriteTransform*>(&quad)
#define TRANSLATE(x,y) TRANSFORM->TranslateQuad((x),(y),0.0f)
#define DRAW(color) Graphics::DrawTexturedQuad(reinterpret_cast<const float (*)[4]>(&quad), &source, (color), texture)
#define SCALE() TRANSFORM->ScaleQuad(0.0f,39.0f,0.0f,1.0f,boxScaleY,1.0f)
void TextOverlay::DrawBox()
{
    RECT source;
    SetRect(&source,0,0,571,78);
    SpriteRectF211 quad(&source);
    SCALE();
    TRANSFORM->TranslateQuad(x,y,0.0f);
    if ((mode))
        textureManager.DrawQuad(0, reinterpret_cast<const SpriteQuad40CA80&>(quad), &source, 0xffffffff);
    else
        (boxScaleY)=1.0f;
    if ((boxScaleY)<1.0f) {
        (boxScaleY)=(boxScaleY)+0.05f;
        return;
    }
    {
        SetRect(&source,0,0,571,((fontSize)+6)*(unfadedLineCount));
        TRANSFORM->BuildQuadFromRect(&source);
        SCALE();
        TRANSFORM->TranslateQuad(x,y,0.0f);
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
        SetRect(&source,0,((fontSize)+6)*(unfadedLineCount),571,128);
        TRANSFORM->BuildQuadFromRect(&source);
        SCALE();
        TRANSFORM->TranslateQuad(x,y,0.0f);
        if ((newTextAlpha)<0xff)
            (newTextAlpha)+=10;
        TRANSLATE(9.0f,9.0f);
        TRANSLATE(-1.0f,0.0f);
        DRAW(((static_cast<DWORD>((newTextAlpha))&0xffu)<<24));
        TRANSLATE(-1.0f,0.0f);
        TRANSLATE(0.0f,-1.0f);
        DRAW(((static_cast<DWORD>((newTextAlpha))&0xffu)<<24));
        TRANSLATE(0.0f,-1.0f);
        TRANSLATE(1.0f,0.0f);
        DRAW(((static_cast<DWORD>((newTextAlpha))&0xffu)<<24));
        TRANSLATE(1.0f,0.0f);
        TRANSLATE(0.0f,1.0f);
        DRAW(((static_cast<DWORD>((newTextAlpha))&0xffu)<<24));
        TRANSLATE(-1.0f,0.0f);
        DRAW((((static_cast<DWORD>((newTextAlpha))&0xffu)<<24))|0x00ff0000|0x0000ff00|0x000000ff);
    }
}
#undef SCALE
#undef DRAW
#undef TRANSLATE
#undef TRANSFORM
