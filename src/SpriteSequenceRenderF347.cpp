#include "CommandListF283.hpp"
#include "GeometryConstants.hpp"
#include "SpriteTransform.hpp"
#include "TextureManagerF198.hpp"

extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;

void CommandListF283::RenderElements()
{
    if (!queue.size())
        return;
    if (static_cast<signed char>(mode) <= 0)
        return;
    {
        float renderY;
        std::list<SpriteHistoryElementF325>::iterator it = queue.begin();
        int counter;
        RECT rect;
        DWORD drawTint;
        std::list<SpriteHistoryElementF325>::iterator endOfList = queue.end();
        float x = g_CombatViewOffsetX - GeometryConstants::HundredSixty;
        renderY = g_CombatViewOffsetY;
        SpriteQuad40CA80 nativeQuad;
        {
            counter = 0;
            for (; it != endOfList; it++, ++counter) {
                if (counter % static_cast<signed char>(mode) == static_cast<signed char>(mode) - 1) {
                    texture->GetTextureRect(it->texture, &rect);
                    switch(static_cast<unsigned char>(it->blend)) {
                    case 0: texture->SetBlendMode(0); break;
                    case 1: texture->SetBlendMode(2); break;
                    case 2: texture->SetBlendMode(3); break;
                    }
                    nativeQuad = it->quad;
                    drawTint = (((it->tint >> 24) * counter) / capacity << 24)
                        | (colorMask & it->tint);
                    reinterpret_cast<SpriteTransform*>(&nativeQuad)->TranslateQuad(x, renderY + GeometryConstants::FourHundredTwenty, 0.0f);
                    if (it->offset.x != 0.0f ||
                        it->offset.y != 0.0f ||
                        it->offset.z != 0.0f) {
                        texture->DrawProjectedQuad(it->texture, nativeQuad, &rect,
                            it->offset.x, it->offset.y,
                            it->offset.z, drawTint);
                    } else {
                        texture->DrawQuad(it->texture, nativeQuad, &rect, drawTint);
                    }
                }
            }
        }
    }
}
