#include "GeometryConstants.hpp"
#include "TextureManagerF198.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
#include "ResultListScene.hpp"
// Borrows the complete 132-byte physical quad and the observed renderer
// receiver at +8 only, not a speculative complete scene layout.
struct GlyphIndexRectF324 { int index; RECT rect; };
void ResultListScene::DrawNameGlyphs(float x,float y,DWORD tint,const signed char* name)
{
    SpriteQuad40CA80 quad(x,y,x+GeometryConstants::Nineteen,y+GeometryConstants::Twenty);
    GlyphIndexRectF324 state;
    state.index=0;
    for(;state.index<8;++state.index) {

        SetRect(&state.rect,(name[state.index]%26)*19,(name[state.index]/26)*20,
                (name[state.index]%26)*19+19,(name[state.index]/26)*20+20);
        mainTexture->DrawQuad(2,quad,&state.rect,tint);
        reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(14.0f,0.0f,0.0f);
    }
}
