#include "ui/NameEntryScenes.hpp"
#include "engine/GeometryConstants.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"
#include <windows.h>
struct GlyphIndexRectF324 { int index; RECT rect; };
void SharedNameEntryScene::DrawNameGlyphs(float x,float y,DWORD tint,const signed char* name)
{
    SpriteQuad40CA80 quad(x,y,x+GeometryConstants::Nineteen,y+GeometryConstants::Twenty);
    GlyphIndexRectF324 state;
    state.index=0;
    for(;state.index<8;++state.index) {

        SetRect(&state.rect,(name[state.index]%26)*19,(name[state.index]/26)*20,
                (name[state.index]%26)*19+19,(name[state.index]/26)*20+20);
        texture->DrawQuad(2,quad,&state.rect,tint);
        reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(14.0f,0.0f,0.0f);
    }
}
