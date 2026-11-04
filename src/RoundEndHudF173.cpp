#include "FighterVitalBorrowedF999.hpp"
#include "FighterRoundOutcomeBytesF992.hpp"
#include "RoundEndHudF173.hpp"
#include "CameraUpdate4126C0.hpp"
#include "ComboHudWindowF1060.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FIRST(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x44) + (offset)))
#define SECOND(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x48) + (offset)))
#define MODE_VALUES reinterpret_cast<int (*)[15]>(reinterpret_cast<unsigned char*>(this) + 0x16710)

void RoundEndF173::EnterRoundEnd()
{
    if (F999_VITAL(FIELD(unsigned char*, 0x44)).currentAt324 <= 0 || F999_VITAL(FIELD(unsigned char*, 0x48)).currentAt324 <= 0) {
        FIRST(short, 0x3A0) = 0;
        SECOND(short, 0x3A0) = 0;
        FIRST(unsigned char, 0x39C) = 0;
        SECOND(unsigned char, 0x39C) = 0;
        FIELD(short, 0x1A) = 60;
        if (F999_VITAL(FIELD(unsigned char*, 0x44)).currentAt324 <= 0) {
            if (F999_VITAL(FIELD(unsigned char*, 0x48)).currentAt324 <= 0) {
                FIRST(signed char, 0x39D) = 1;
                SECOND(signed char, 0x39D) = 1;
                FIELD(unsigned char, 0x18) = 2;
                F992_OUTCOME(FIELD(unsigned char*, 0x44)).continuationAt3CF = 0;
                F992_OUTCOME(FIELD(unsigned char*, 0x48)).continuationAt3CF = 0;
                F992_OUTCOME(FIELD(unsigned char*, 0x44)).outcomeAt3CE.unsignedAt3CE = 1;
                F992_OUTCOME(FIELD(unsigned char*, 0x48)).outcomeAt3CE.unsignedAt3CE = 1;
                FIELD(int, 0xC) = 300;
            } else {
                FIRST(signed char, 0x39D)--;
                F992_OUTCOME(FIELD(unsigned char*, 0x44)).continuationAt3CF = 0;
                F992_OUTCOME(FIELD(unsigned char*, 0x44)).outcomeAt3CE.unsignedAt3CE = 1;
                F992_OUTCOME(FIELD(unsigned char*, 0x48)).outcomeAt3CE.unsignedAt3CE = 0;
                FIELD(short, 0x1A) = 60;
                if (FIRST(signed char, 0x39D) != 0) {
                    F999_VITAL(FIELD(unsigned char*, 0x44)).recoverableAt326 = 10000;
                    F999_VITAL(FIELD(unsigned char*, 0x44)).currentAt324 = 10000;
                    FIELD(unsigned char, 0x18) = 2;
                    FIELD(int, 0xC) = 300;
                } else {
                    FIELD(unsigned char, 0x5D) = 1;
                    FIELD(unsigned char, 0x18) = 3;
                    FIELD(int, 0xC) = 180;
                }
            }
        } else if (F999_VITAL(FIELD(unsigned char*, 0x48)).currentAt324 <= 0) {
            SECOND(signed char, 0x39D)--;
            F992_OUTCOME(FIELD(unsigned char*, 0x48)).continuationAt3CF = 0;
            F992_OUTCOME(FIELD(unsigned char*, 0x44)).outcomeAt3CE.unsignedAt3CE = 0;
            F992_OUTCOME(FIELD(unsigned char*, 0x48)).outcomeAt3CE.unsignedAt3CE = 1;
            if (SECOND(signed char, 0x39D) != 0) {
                F999_VITAL(FIELD(unsigned char*, 0x48)).recoverableAt326 = 10000;
                F999_VITAL(FIELD(unsigned char*, 0x48)).currentAt324 = 10000;
                FIELD(unsigned char, 0x18) = 2;
                FIELD(int, 0xC) = 300;
            } else {
                FIELD(unsigned char, 0x5D) = 0;
                FIELD(unsigned char, 0x18) = 3;
                FIELD(int, 0xC) = 180;
            }
        }
    }
}

void ModeCounterF173::IncrementModeCounter(signed char category, signed char key)
{
    MODE_VALUES[category][key]++;
}

ComboCounterF173::ComboCounterF173(void* texture, signed char side)
{
    FIELD(void*, 0) = texture;
    F1060_HUD(this).sideAt0B = side;
    F1060_HUD(this).opacityAt0A = 0;
    F1060_HUD(this).countAt04 = 0;
    F1060_HUD(this).verticalAt10 = -200.0f;
}

void ComboCounterF173::UpdateComboCounter(short count, short value, short extra)
{
    if (count > F1060_HUD(this).countAt04 || count == 1) {
        F1060_HUD(this).opacityAt0A = 255;
        F1060_HUD(this).countAt04 = count;
        F1060_HUD(this).damageAt06 = value;
        F1060_HUD(this).ratioAt08 = extra;
        F1060_HUD(this).holdAt0C = 60;
        if (F1060_HUD(this).countAt04 == 2) {
            F1060_HUD(this).phaseAt0E = 90;
            F1060_HUD(this).verticalAt10 = -CameraSineAt0040D940(
                float(F1060_HUD(this).phaseAt0E) * 0.01745328866f) * 200.0f;
        }
    }
}

#undef MODE_VALUES
#undef SECOND
#undef FIRST
#undef FIELD
