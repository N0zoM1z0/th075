#include "BattleDamageFlash4406C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define LEFT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44) + (offset)))
#define RIGHT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x48) + (offset)))
#define LEFT_FLOAT(offset) *reinterpret_cast<float*>(FIELD(char*, 0x44) + (offset))
#define RIGHT_FLOAT(offset) *reinterpret_cast<float*>(FIELD(char*, 0x48) + (offset))
#define LEFT_FLAGS *reinterpret_cast<unsigned int*>(LEFT(char*, 0x74) + 0x3C)
#define RIGHT_FLAGS *reinterpret_cast<unsigned int*>(RIGHT(char*, 0x74) + 0x3C)
#define LEFT_STATE reinterpret_cast<FighterState*>(FIELD(void*, 0x44))
#define RIGHT_STATE reinterpret_cast<FighterState*>(FIELD(void*, 0x48))
#define LEFT_PREDICATE reinterpret_cast<FlashPredicate4406C0*>(FIELD(void*, 0x44))
#define RIGHT_PREDICATE reinterpret_cast<FlashPredicate4406C0*>(FIELD(void*, 0x48))
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(FIELD(void*, 8))

void BattleDamageFlash4406C0::RenderFlash() {
    float x;
    float screenY;
    D3DCOLOR color;
    RECT region;
    unsigned char component;
    STYLE->SetBlendMode(0);
    x = g_CombatViewOffsetX - 160.0f;
    screenY = g_CombatViewOffsetY;
    if ((LEFT_FLAGS & 0x100000) == 0 && LEFT(short, 0x324) > 0 &&
        LEFT_STATE->IsState50To149() && LEFT_FLOAT(0x48) > 0.0f &&
        LEFT(short, 0x3C8) < 75 && !LEFT_PREDICATE->IsState95To99()) {
        if (LEFT(short, 0x3C8) > 40) {
            component = static_cast<unsigned char>((float(LEFT(short, 0x3C8)) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (LEFT(short, 0x3C8) > 20) {
            component = static_cast<unsigned char>((float(LEFT(short, 0x3C8)) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + LEFT_FLOAT(0x44)),
            int(screenY + 420.0f - LEFT_FLOAT(0x48)),
            int(x + LEFT_FLOAT(0x44) + LEFT(signed char, 0x66) * LEFT(short, 0x3C8) * 4),
            int(screenY + 420.0f - LEFT_FLOAT(0x48) + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
    if ((RIGHT_FLAGS & 0x100000) == 0 && RIGHT(short, 0x324) > 0 &&
        RIGHT_STATE->IsState50To149() && RIGHT_FLOAT(0x48) > 0.0f &&
        RIGHT(short, 0x3C8) < 75 && !RIGHT_PREDICATE->IsState95To99()) {
        if (RIGHT(short, 0x3C8) > 40) {
            component = static_cast<unsigned char>((float(RIGHT(short, 0x3C8)) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (RIGHT(short, 0x3C8) > 20) {
            component = static_cast<unsigned char>((float(RIGHT(short, 0x3C8)) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + RIGHT_FLOAT(0x44)),
            int(screenY + 420.0f - RIGHT_FLOAT(0x48)),
            int(x + RIGHT_FLOAT(0x44) + RIGHT(signed char, 0x66) * RIGHT(short, 0x3C8) * 4),
            int(screenY + 420.0f - RIGHT_FLOAT(0x48) + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
}

#undef STYLE
#undef RIGHT_PREDICATE
#undef LEFT_PREDICATE
#undef RIGHT_STATE
#undef LEFT_STATE
#undef RIGHT_FLAGS
#undef LEFT_FLAGS
#undef RIGHT_FLOAT
#undef LEFT_FLOAT
#undef RIGHT
#undef LEFT
#undef FIELD
