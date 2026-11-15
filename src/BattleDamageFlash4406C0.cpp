#include "BattleDamageFlash4406C0.hpp"

#define LEFT_PREDICATE reinterpret_cast<FlashPredicate4406C0*>(reinterpret_cast<void*&>(field044))
#define RIGHT_PREDICATE reinterpret_cast<FlashPredicate4406C0*>(reinterpret_cast<void*&>(field048))
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(field008)

void BattleDamageFlash4406C0::RenderFlash() {
    float x;
    float screenY;
    D3DCOLOR color;
    RECT region;
    unsigned char component;
    STYLE->SetBlendMode(0);
    x = g_CombatViewOffsetX - 160.0f;
    screenY = g_CombatViewOffsetY;
    if ((field044->frameInfo->flags & 0x100000) == 0 && field044->health > 0 &&
        field044->IsState50To149() && field044->y > 0.0f &&
        field044->flashGauge < 75 && !LEFT_PREDICATE->IsState95To99()) {
        if (field044->flashGauge > 40) {
            component = static_cast<unsigned char>((float(field044->flashGauge) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (field044->flashGauge > 20) {
            component = static_cast<unsigned char>((float(field044->flashGauge) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + field044->x),
            int(screenY + 420.0f - field044->y),
            int(x + field044->x + field044->facing * field044->flashGauge * 4),
            int(screenY + 420.0f - field044->y + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
    if ((field048->frameInfo->flags & 0x100000) == 0 && field048->health > 0 &&
        field048->IsState50To149() && field048->y > 0.0f &&
        field048->flashGauge < 75 && !RIGHT_PREDICATE->IsState95To99()) {
        if (field048->flashGauge > 40) {
            component = static_cast<unsigned char>((float(field048->flashGauge) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (field048->flashGauge > 20) {
            component = static_cast<unsigned char>((float(field048->flashGauge) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + field048->x),
            int(screenY + 420.0f - field048->y),
            int(x + field048->x + field048->facing * field048->flashGauge * 4),
            int(screenY + 420.0f - field048->y + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
}

#undef STYLE
#undef RIGHT_PREDICATE
#undef LEFT_PREDICATE
#undef field048->frameInfo->flags
#undef field044->frameInfo->flags
