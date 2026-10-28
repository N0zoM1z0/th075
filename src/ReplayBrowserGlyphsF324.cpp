#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
// Borrows the complete 132-byte physical quad and the observed renderer
// receiver at +8 only, not a speculative complete scene layout.
extern const float g_CharacterGlyphWidthAt00657F78;
extern const float g_CharacterGlyphHeightAt0065786C;
class NameGlyphRendererF324 {
public:
    void DrawQuad(int texture,const SpriteQuad40CA80& quad,const RECT* rectangle,DWORD tint);
};
struct GlyphIndexRectF324 { int index; RECT rect; };
class ReplayBrowserGlyphsF324 {
public:
    void DrawNameGlyphs(float x,float y,DWORD tint,const signed char* name);
};
#define R(T,off) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReplayBrowserGlyphsF324::DrawNameGlyphs(float x,float y,DWORD tint,const signed char* name)
{
    SpriteQuad40CA80 quad(x,y,x+g_CharacterGlyphWidthAt00657F78,y+g_CharacterGlyphHeightAt0065786C);
    GlyphIndexRectF324 state;
    state.index=0;
    for(;state.index<8;++state.index) {

        SetRect(&state.rect,(name[state.index]%26)*19,(name[state.index]/26)*20,
                (name[state.index]%26)*19+19,(name[state.index]/26)*20+20);
        R(NameGlyphRendererF324*,8)->DrawQuad(2,quad,&state.rect,tint);
        reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(14.0f,0.0f,0.0f);
    }
}
#undef R
