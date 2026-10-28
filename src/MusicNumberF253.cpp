#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>

// Borrowed drawing interface at scene+8; original parent layout unproven.
class MusicNumberF253Drawer {
public: void DrawQuad(int texture,const SpriteQuad40CA80&, const RECT*, DWORD);
};
extern const float g_ResultDigitWidthAt00657CBC;
extern const float g_ResultDigitHeightAt00657CC0;
class MusicNumberF253 {
public:
    void DrawNumber(float x, float y, DWORD color, int number,
                           int minDigits);
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void MusicNumberF253::DrawNumber(float x, float y, DWORD color,
                                        int number, int minDigits)
{
    int remaining=number;
    {
    SpriteQuad40CA80 quad(x - g_ResultDigitWidthAt00657CBC,y,x,y + g_ResultDigitHeightAt00657CC0);
    {
        RECT rect;
        if (minDigits > 0) {
            while (minDigits > 0) {
                SetRect(&rect, (remaining % 10) * 15, 0,
                        ((remaining % 10) * 15) + 15, 16);
                reinterpret_cast<MusicNumberF253Drawer*>(FIELD(void*,8))->DrawQuad(1,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-14.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) * 15, 0,
                        ((remaining % 10) * 15) + 15, 16);
                reinterpret_cast<MusicNumberF253Drawer*>(FIELD(void*,8))->DrawQuad(1,quad,&rect,color);
                if (remaining < 10)
                    remaining=-1;
                else
                    remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-14.0f,0.0f,0.0f);
            }
        }
    }
    }
}
#undef TRANSFORM
#undef FIELD
