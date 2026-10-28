#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>

// Borrowed drawing interface at scene+8; original parent layout unproven.
class ReplayNumberF253Drawer {
public: void DrawQuad(int texture,const SpriteQuad40CA80&, const RECT*, DWORD);
};
extern const float g_ResultDigitWidthAt00657F78;
extern const float g_ResultDigitHeightAt0065786C;
class ReplayNumberF253 {
public:
    void DrawNumber(float x, float y, DWORD color, int number,
                           int minDigits);
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void ReplayNumberF253::DrawNumber(float x, float y, DWORD color,
                                        int number, int minDigits)
{
    int remaining=number;
    {
    SpriteQuad40CA80 quad(x - g_ResultDigitWidthAt00657F78,y,x,y + g_ResultDigitHeightAt0065786C);
    {
        RECT rect;
        if (minDigits > 0) {
            while (minDigits > 0) {
                SetRect(&rect, (remaining % 10) * 19, 40,
                        ((remaining % 10) * 19) + 19, 60);
                reinterpret_cast<ReplayNumberF253Drawer*>(FIELD(void*,8))->DrawQuad(2,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-11.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) * 19, 40,
                        ((remaining % 10) * 19) + 19, 60);
                reinterpret_cast<ReplayNumberF253Drawer*>(FIELD(void*,8))->DrawQuad(2,quad,&rect,color);
                if (remaining < 10)
                    remaining=-1;
                else
                    remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-11.0f,0.0f,0.0f);
            }
        }
    }
    }
}
#undef TRANSFORM
#undef FIELD
