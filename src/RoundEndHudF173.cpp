#include "BattleScene.hpp"
#include "FighterRoundOutcomeBytesF992.hpp"
#include "RoundEndHudF173.hpp"
#include "CameraUpdate4126C0.hpp"
#include "ComboHudWindowF1060.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define MODE_VALUES reinterpret_cast<int (*)[15]>(reinterpret_cast<unsigned char*>(this) + 0x16710)

void BattleScene::EnterRoundEnd()
{
    if (fighters[0]->health <= 0 || fighters[1]->health <= 0) {
        fighters[0]->field3A0 = 0;
        fighters[1]->field3A0 = 0;
        fighters[0]->field39C = 0;
        fighters[1]->field39C = 0;
        field01A = 60;
        if (fighters[0]->health <= 0) {
            if (fighters[1]->health <= 0) {
                fighters[0]->field39D = 1;
                fighters[1]->field39D = 1;
                reinterpret_cast<unsigned char&>(field018) = 2;
                F992_OUTCOME(fighters[0]).continuationAt3CF = 0;
                F992_OUTCOME(fighters[1]).continuationAt3CF = 0;
                F992_OUTCOME(fighters[0]).outcomeAt3CE.unsignedAt3CE = 1;
                F992_OUTCOME(fighters[1]).outcomeAt3CE.unsignedAt3CE = 1;
                reinterpret_cast<int&>(field00C) = 300;
            } else {
                fighters[0]->field39D--;
                F992_OUTCOME(fighters[0]).continuationAt3CF = 0;
                F992_OUTCOME(fighters[0]).outcomeAt3CE.unsignedAt3CE = 1;
                F992_OUTCOME(fighters[1]).outcomeAt3CE.unsignedAt3CE = 0;
                field01A = 60;
                if (fighters[0]->field39D != 0) {
                    fighters[0]->recoverableHealth = 10000;
                    fighters[0]->health = 10000;
                    reinterpret_cast<unsigned char&>(field018) = 2;
                    reinterpret_cast<int&>(field00C) = 300;
                } else {
                    reinterpret_cast<unsigned char&>(field05D) = 1;
                    reinterpret_cast<unsigned char&>(field018) = 3;
                    reinterpret_cast<int&>(field00C) = 180;
                }
            }
        } else if (fighters[1]->health <= 0) {
            fighters[1]->field39D--;
            F992_OUTCOME(fighters[1]).continuationAt3CF = 0;
            F992_OUTCOME(fighters[0]).outcomeAt3CE.unsignedAt3CE = 0;
            F992_OUTCOME(fighters[1]).outcomeAt3CE.unsignedAt3CE = 1;
            if (fighters[1]->field39D != 0) {
                fighters[1]->recoverableHealth = 10000;
                fighters[1]->health = 10000;
                reinterpret_cast<unsigned char&>(field018) = 2;
                reinterpret_cast<int&>(field00C) = 300;
            } else {
                reinterpret_cast<unsigned char&>(field05D) = 0;
                reinterpret_cast<unsigned char&>(field018) = 3;
                reinterpret_cast<int&>(field00C) = 180;
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
