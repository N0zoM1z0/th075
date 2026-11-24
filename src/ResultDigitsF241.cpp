#include "GeometryConstants.hpp"
#include "TextureManagerF198.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>
#include "ResultScene.hpp"

// Borrowed drawing interface at scene+8; original parent layout unproven.
class ResultDigitDrawerF241 {
public: void DrawQuad(int texture,const SpriteQuad40CA80&, const RECT*, DWORD);
};
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void ResultScene::DrawDecimalDigits(float x, float y, DWORD color,
                                        int number, signed char style, int minDigits)
{
    int remaining=number;
    {
    SpriteQuad40CA80 quad(x - GeometryConstants::Sixteen,y,x,y + GeometryConstants::Twenty);
    {
        RECT rect;
        if (minDigits > 0) {
            while (minDigits > 0) {
                SetRect(&rect, (remaining % 10) << 4, style * 20 + 0x80,
                        ((remaining % 10) << 4) + 0x10, style * 20 + 0x94);
                reinterpret_cast<TextureManagerF198*>(textures)->DrawQuad(2,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-16.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) << 4, style * 20 + 0x80,
                        ((remaining % 10) << 4) + 0x10, style * 20 + 0x94);
                reinterpret_cast<TextureManagerF198*>(textures)->DrawQuad(2,quad,&rect,color);
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
