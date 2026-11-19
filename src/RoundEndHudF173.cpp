#include "GameProgress.hpp"
#include "BattleScene.hpp"
#include "RoundEndHudF173.hpp"
#include "CameraUpdate4126C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

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
                field018 = 2;
                fighters[0]->field3CF = 0;
                fighters[1]->field3CF = 0;
                fighters[0]->field3CE.unsignedAt3CE = 1;
                fighters[1]->field3CE.unsignedAt3CE = 1;
                field00C = 300;
            } else {
                fighters[0]->field39D--;
                fighters[0]->field3CF = 0;
                fighters[0]->field3CE.unsignedAt3CE = 1;
                fighters[1]->field3CE.unsignedAt3CE = 0;
                field01A = 60;
                if (fighters[0]->field39D != 0) {
                    fighters[0]->recoverableHealth = 10000;
                    fighters[0]->health = 10000;
                    field018 = 2;
                    field00C = 300;
                } else {
                    field05D = 1;
                    field018 = 3;
                    field00C = 180;
                }
            }
        } else if (fighters[1]->health <= 0) {
            fighters[1]->field39D--;
            fighters[1]->field3CF = 0;
            fighters[0]->field3CE.unsignedAt3CE = 0;
            fighters[1]->field3CE.unsignedAt3CE = 1;
            if (fighters[1]->field39D != 0) {
                fighters[1]->recoverableHealth = 10000;
                fighters[1]->health = 10000;
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

void GameProgress::IncrementModeCounter(signed char category, signed char key)
{
    modeCounts[category][key]++;
}

ComboDisplay::ComboDisplay(IDirect3DTexture8* texture, signed char side)
{
    this->texture = texture;
    this->side = side;
    alpha = 0;
    count = 0;
    slide = -200.0f;
}

// A longer combo, or a new one, shows the counter and restarts its timers.
void ComboDisplay::UpdateCounter(short count, short damage, short rate)
{
    if (count > this->count || count == 1) {
        alpha = 255;
        this->count = count;
        this->damage = damage;
        this->rate = rate;
        hold = 60;
        if (this->count == 2) {
            phase = 90;
            slide = -CameraSineAt0040D940(float(phase) * 0.01745328866f) * 200.0f;
        }
    }
}

#undef FIELD
