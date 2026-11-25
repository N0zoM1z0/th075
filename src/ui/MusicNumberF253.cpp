#include "ui/MusicRoomScene.hpp"
#include "engine/GeometryConstants.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"
#include <windows.h>
#include <d3d8.h>

#define TRANSFORM(q) reinterpret_cast<SpriteTransform*>(&(q))
void MusicRoomScene::DrawNumber(float x, float y, DWORD color,
                                        int number, int minDigits)
{
    int remaining=number;
    {
    SpriteQuad40CA80 quad(x - GeometryConstants::Fifteen,y,x,y + GeometryConstants::Sixteen);
    {
        RECT rect;
        if (minDigits > 0) {
            while (minDigits > 0) {
                SetRect(&rect, (remaining % 10) * 15, 0,
                        ((remaining % 10) * 15) + 15, 16);
                texture->DrawQuad(1,quad,&rect,color);
                remaining=remaining/10;
                TRANSFORM(quad)->TranslateQuad(-14.0f,0.0f,0.0f);
                --minDigits;
            }
        } else {
            while (remaining >= 0) {
                SetRect(&rect, (remaining % 10) * 15, 0,
                        ((remaining % 10) * 15) + 15, 16);
                texture->DrawQuad(1,quad,&rect,color);
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
