#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>

// Borrowed drawing interface at scene+8; original parent layout unproven.
class ResultDigitDrawerF241 {
public: void DrawQuad(int texture,const SpriteQuad40CA80&, const RECT*, DWORD);
};
extern const float g_ResultDigitWidthAt00657CC0;
extern const float g_ResultDigitHeightAt0065786C;
class ResultDigitsF241 {
public:
    void DrawDecimalDigits(float x, float y, DWORD color, int number,
                           signed char style, int minDigits);
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void ResultDigitsF241::DrawDecimalDigits(float x, float y, DWORD color,
                                        int number, signed char style, int minDigits)
{
    int remaining=number;
    {
    SpriteQuad40CA80 quad(x - g_ResultDigitWidthAt00657CC0,y,x,y + g_ResultDigitHeightAt0065786C);
    {
        RECT rect;
        if (minDigits > 0) {
            while (minDigits > 0) {
                SetRect(&rect, (remaining % 10) << 4, style * 20 + 0x80,
                        ((remaining % 10) << 4) + 0x10, style * 20 + 0x94);
                reinterpret_cast<ResultDigitDrawerF241*>(FIELD(void*,8))->DrawQuad(2,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-16.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) << 4, style * 20 + 0x80,
                        ((remaining % 10) << 4) + 0x10, style * 20 + 0x94);
                reinterpret_cast<ResultDigitDrawerF241*>(FIELD(void*,8))->DrawQuad(2,quad,&rect,color);
                if (remaining < 10)
                    remaining=-1;
                else
                    remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-15.0f,0.0f,0.0f);
            }
        }
    }
    }
}
#undef TRANSFORM
#undef FIELD
