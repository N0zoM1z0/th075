#include "NameEntryScenes.hpp"
#include "GeometryConstants.hpp"
#include "TextureManagerF198.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>

#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void PlayerNameEntryScene::DrawNumber(float x, float y, DWORD color,
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
                texture->DrawQuad(2,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-11.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) * 19, 40,
                        ((remaining % 10) * 19) + 19, 60);
                texture->DrawQuad(2,quad,&rect,color);
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
