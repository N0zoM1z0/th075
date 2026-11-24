#include "TextureManagerF198.hpp"
#include "BattleScene.hpp"
#include "BattleHud43E040.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)

void BattleScene::RenderDamageFlash() {
    float x;
    float screenY;
    D3DCOLOR color;
    RECT region;
    unsigned char component;
    reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
    x = g_CombatViewOffsetX - 160.0f;
    screenY = g_CombatViewOffsetY;
    if ((fighters[0]->frameInfo->flags & 0x100000) == 0 && fighters[0]->health > 0 &&
        fighters[0]->IsState50To149() && fighters[0]->y > 0.0f &&
        fighters[0]->flashGauge < 75 && !fighters[0]->IsState95To99()) {
        if (fighters[0]->flashGauge > 40) {
            component = static_cast<unsigned char>((float(fighters[0]->flashGauge) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (fighters[0]->flashGauge > 20) {
            component = static_cast<unsigned char>((float(fighters[0]->flashGauge) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + fighters[0]->x),
            int(screenY + 420.0f - fighters[0]->y),
            int(x + fighters[0]->x + fighters[0]->facing * fighters[0]->flashGauge * 4),
            int(screenY + 420.0f - fighters[0]->y + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
    if ((fighters[1]->frameInfo->flags & 0x100000) == 0 && fighters[1]->health > 0 &&
        fighters[1]->IsState50To149() && fighters[1]->y > 0.0f &&
        fighters[1]->flashGauge < 75 && !fighters[1]->IsState95To99()) {
        if (fighters[1]->flashGauge > 40) {
            component = static_cast<unsigned char>((float(fighters[1]->flashGauge) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (fighters[1]->flashGauge > 20) {
            component = static_cast<unsigned char>((float(fighters[1]->flashGauge) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + fighters[1]->x),
            int(screenY + 420.0f - fighters[1]->y),
            int(x + fighters[1]->x + fighters[1]->facing * fighters[1]->flashGauge * 4),
            int(screenY + 420.0f - fighters[1]->y + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
}

#undef STYLE
#undef fighters[1]->frameInfo->flags
#undef fighters[0]->frameInfo->flags
