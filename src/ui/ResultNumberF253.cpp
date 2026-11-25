#include "engine/GeometryConstants.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>
#include "ui/ResultListScene.hpp"

// Borrowed drawing interface at scene+8; original parent layout unproven.
class ResultNumberF253Drawer {
public: void DrawQuad(int texture,const SpriteQuad40CA80&, const RECT*, DWORD);
};
#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void ResultListScene::DrawCounter(float x, float y, DWORD color,
                                        int number, int minDigits)
{
    int remaining=number;
    {
    SpriteQuad40CA80 quad(x - GeometryConstants::Nineteen,y,x,y + GeometryConstants::Twenty);
    {
        RECT rect;
        if (minDigits > 0) {
            while (minDigits > 0) {
                SetRect(&rect, (remaining % 10) * 19, 40,
                        ((remaining % 10) * 19) + 19, 60);
                reinterpret_cast<TextureManagerF198*>(mainTexture)->DrawQuad(2,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-11.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) * 19, 40,
                        ((remaining % 10) * 19) + 19, 60);
                reinterpret_cast<TextureManagerF198*>(mainTexture)->DrawQuad(2,quad,&rect,color);
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
