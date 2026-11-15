#include "FighterRoundOutcomeBytesF992.hpp"
#include "RoundEndHudF173.hpp"
#include "CameraUpdate4126C0.hpp"
#include "ComboHudWindowF1060.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define MODE_VALUES reinterpret_cast<int (*)[15]>(reinterpret_cast<unsigned char*>(this) + 0x16710)

void RoundEndF173::EnterRoundEnd()
{
    if (field044->health <= 0 || field048->health <= 0) {
        field044->field3A0 = 0;
        field048->field3A0 = 0;
        field044->field39C = 0;
        field048->field39C = 0;
        field01A = 60;
        if (field044->health <= 0) {
            if (field048->health <= 0) {
                field044->field39D = 1;
                field048->field39D = 1;
                field018 = 2;
                F992_OUTCOME(field044).continuationAt3CF = 0;
                F992_OUTCOME(field048).continuationAt3CF = 0;
                F992_OUTCOME(field044).outcomeAt3CE.unsignedAt3CE = 1;
                F992_OUTCOME(field048).outcomeAt3CE.unsignedAt3CE = 1;
                field00C = 300;
            } else {
                field044->field39D--;
                F992_OUTCOME(field044).continuationAt3CF = 0;
                F992_OUTCOME(field044).outcomeAt3CE.unsignedAt3CE = 1;
                F992_OUTCOME(field048).outcomeAt3CE.unsignedAt3CE = 0;
                field01A = 60;
                if (field044->field39D != 0) {
                    field044->recoverableHealth = 10000;
                    field044->health = 10000;
                    field018 = 2;
                    field00C = 300;
                } else {
                    field05D = 1;
                    field018 = 3;
                    field00C = 180;
                }
            }
        } else if (field048->health <= 0) {
            field048->field39D--;
            F992_OUTCOME(field048).continuationAt3CF = 0;
            F992_OUTCOME(field044).outcomeAt3CE.unsignedAt3CE = 0;
            F992_OUTCOME(field048).outcomeAt3CE.unsignedAt3CE = 1;
            if (field048->field39D != 0) {
                field048->recoverableHealth = 10000;
                field048->health = 10000;
                field018 = 2;
                field00C = 300;
            } else {
                field05D = 0;
                field018 = 3;
                field00C = 180;
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
#undef FIELD
