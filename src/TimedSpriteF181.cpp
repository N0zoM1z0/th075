#include "TimedSpriteF181.hpp"
#include "BattleHud43E040.hpp"
#include "FighterEffectPolicies.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <math.h>


void TimedSpriteF181::RenderTimedSprite()
{
    int cameraHorizontal = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    int y = static_cast<int>(g_CombatViewOffsetY);
    RECT rectangle = {0, 0, 64, 256};
    SpriteQuad40CA80 quad;
    quad.first.x = 0.0f;
    quad.first.y = 0.0f;
    quad.first.z = 0.0f;
    quad.fourth.x = 0.0f;
    quad.fourth.y = 128.0f;
    quad.fourth.z = 0.0f;
    quad.second.x = 64.0f;
    quad.second.y = 0.0f;
    quad.second.z = 0.0f;
    quad.third.x = 64.0f;
    quad.third.y = 128.0f;
    quad.third.z = 0.0f;
    reinterpret_cast<SpriteTransform*>(&quad)->ScaleQuad(32.0f, 0.0f, 0.0f,
        32.0f, static_cast<float>((sin((field068 / 0.01745328866f) * 0.0005)
                                  + 12.0) * 0.1), 1.0f);
    reinterpret_cast<SpriteTransform*>(&quad)->TranslateQuad(float(cameraHorizontal + 240), float(y + 388), 0.25f);
    drawing.SetDepthMode(3);
    drawing.SetDepthMode(7);
    drawing.SetBlendMode(2);
    drawing.DrawQuad(4, quad, &rectangle, 0xFFFFFFFF);
    drawing.SetBlendMode(0);
}
