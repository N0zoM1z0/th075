#include "BattleDamageFlash4406C0.hpp"
#include "FighterVitalBorrowedF999.hpp"
#include "FrameActorMotionPairsF1037.hpp"
#include "FlashGaugeBorrowF1067.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define LEFT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44) + (offset)))
#define RIGHT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x48) + (offset)))
#define LEFT_FLAGS F1067_FRAME_FLAGS(LEFT(char*, 0x74)).flagsAt3C
#define RIGHT_FLAGS F1067_FRAME_FLAGS(RIGHT(char*, 0x74)).flagsAt3C
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
    if ((LEFT_FLAGS & 0x100000) == 0 && F999_VITAL(FIELD(char*, 0x44)).currentAt324 > 0 &&
        LEFT_STATE->IsState50To149() && F1037_POSITION(FIELD(char*, 0x44)).yPosition > 0.0f &&
        F1067_FLASH_BAR(FIELD(char*, 0x44)).barLengthAt3C8 < 75 && !LEFT_PREDICATE->IsState95To99()) {
        if (F1067_FLASH_BAR(FIELD(char*, 0x44)).barLengthAt3C8 > 40) {
            component = static_cast<unsigned char>((float(F1067_FLASH_BAR(FIELD(char*, 0x44)).barLengthAt3C8) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (F1067_FLASH_BAR(FIELD(char*, 0x44)).barLengthAt3C8 > 20) {
            component = static_cast<unsigned char>((float(F1067_FLASH_BAR(FIELD(char*, 0x44)).barLengthAt3C8) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + F1037_POSITION(FIELD(char*, 0x44)).xPosition),
            int(screenY + 420.0f - F1037_POSITION(FIELD(char*, 0x44)).yPosition),
            int(x + F1037_POSITION(FIELD(char*, 0x44)).xPosition + LEFT(signed char, 0x66) * F1067_FLASH_BAR(FIELD(char*, 0x44)).barLengthAt3C8 * 4),
            int(screenY + 420.0f - F1037_POSITION(FIELD(char*, 0x44)).yPosition + 3.0f));
        Graphics::DrawFilledRectangle(&region, color);
        region.top += 3;
        region.bottom += 1;
        Graphics::DrawFilledRectangle(&region, 0xFF000000);
    }
    if ((RIGHT_FLAGS & 0x100000) == 0 && F999_VITAL(FIELD(char*, 0x48)).currentAt324 > 0 &&
        RIGHT_STATE->IsState50To149() && F1037_POSITION(FIELD(char*, 0x48)).yPosition > 0.0f &&
        F1067_FLASH_BAR(FIELD(char*, 0x48)).barLengthAt3C8 < 75 && !RIGHT_PREDICATE->IsState95To99()) {
        if (F1067_FLASH_BAR(FIELD(char*, 0x48)).barLengthAt3C8 > 40) {
            component = static_cast<unsigned char>((float(F1067_FLASH_BAR(FIELD(char*, 0x48)).barLengthAt3C8) - 40.0f) / 35.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255 - component, 255, 0);
        } else if (F1067_FLASH_BAR(FIELD(char*, 0x48)).barLengthAt3C8 > 20) {
            component = static_cast<unsigned char>((float(F1067_FLASH_BAR(FIELD(char*, 0x48)).barLengthAt3C8) - 20.0f) / 20.0f * 255.0f);
            color = D3DCOLOR_ARGB(255, 255, component, 0);
        } else {
            color = 0xFFFF0000;
        }
        SetRect(&region,
            int(x + F1037_POSITION(FIELD(char*, 0x48)).xPosition),
            int(screenY + 420.0f - F1037_POSITION(FIELD(char*, 0x48)).yPosition),
            int(x + F1037_POSITION(FIELD(char*, 0x48)).xPosition + RIGHT(signed char, 0x66) * F1067_FLASH_BAR(FIELD(char*, 0x48)).barLengthAt3C8 * 4),
            int(screenY + 420.0f - F1037_POSITION(FIELD(char*, 0x48)).yPosition + 3.0f));
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
#undef RIGHT
#undef LEFT
#undef FIELD
