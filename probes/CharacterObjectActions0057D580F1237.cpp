// Complete research source for original 0057D580 (43,845 CODE bytes).
// All native states are written; NONEXACT and not an accepted replacement.
#include "CharacterObject.hpp"
#include "YuyukoFighter.hpp"
#include "EffectServices.hpp"
#include "MathLookup.hpp"


float __cdecl AngleAt00483300(float, float);
float __cdecl AbsFloatAt00412D90(float);

extern float g_F1211_AngleDivAt00657828;
extern signed char g_F1212_DifficultyAt006714D0;
extern unsigned int g_F1239_DwordAt0067149C;
extern unsigned char g_F1239_ByteAt006714D1;

void YuyukoObject::Advance()
{
    if (owner->opponent->field3BA != 0) return;
    if (owner->field3BA != 0 && field08A == 0) return;
    if (field082 != 0) {
        --field082;
        return;
    }
    switch (action) {
case 800:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex800 = 0; rewardIndex800 < 3; ++rewardIndex800)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            SetPolarVelocity(field0C8, field0D8 * 0.2f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 801:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex801 = 0; rewardIndex801 < 3; ++rewardIndex801)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            SetPolarVelocity(field0C8, field0D8 * 0.2f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 802:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex802 = 0; rewardIndex802 < 3; ++rewardIndex802)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            SetPolarVelocity(field0C8, field0D8 * 0.2f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 803:
        if (field07C == 5) { ClearFrameInfo(); return; }
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
            ClearFrameInfo(); return;
        }
        if ((owner->action != 700 || (owner->action == 700 && owner->animationStage > 9)) && animationStage < 2)
            field0D0 *= 0.9f;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 3;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage < 2) field0C8 = field0D0 * 0.1f + field0C8;
        SetPolarVelocity(field0C8, field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage > 1) {
            if (color[0] >= 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0 && field0D8 < 50) {
            ResetSecondaryCounter(1);
            field07C = 0;
            ++field0D8;
        }
        break;

case 804:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
        }
        SetPolarVelocity(field0C8, field0CC);
        if (field0CC > 2.0f) field0CC -= 1.0f;
        if (animationStage < 2 && field0CC == 2.0f) ResetSecondaryCounter(2);
        if (field080 == 0) { ClearFrameInfo(); return; }
        else {
            x = facing * velocityX + x;
            y += velocityY;
            owner->SpawnBattleEffect(805, x - 10.0f + RecordedRange(0, 20),
                y - 10.0f + RecordedRange(0, 20), facing, 1);
            if (animationFrame == 0) {
                field0DA = RecordedRange(0, 20);
                scaleX = field0DA * 0.01f + 0.5f;
                scaleY = field0DA * 0.01f + 0.5f;
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
            if (animationStage == 3 && animationFrame == 0 && field0D8 < 45) {
                ResetSecondaryCounter(2);
                ++field0D8;
            }
        }
        break;

case 805:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 8.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.15f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 806:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 8.0f;
            velocityY = 0.0f;
        }
        x = facing * velocityX + x;
        y += velocityY;
        --field0DA;
        if (animationStage == 2 && field0DA < 0) {
            owner->field314 = RecordedRange(0, 40) - 90;
            owner->field318 = RecordedRange(0, 22) + 5;
            owner->SpawnBattleEffect(804, (100 - RecordedRange(0, 200)) * facing + x,
                y, facing, 1);
            field0DA = 2;
        }
        if (animationStage == 3) {
            if (color[0] > 13) color[0] -= 13;
            else color[0] = 0;
        }
        if (animationStage < 2) {
            scaleX += 0.8f;
            scaleY += 0.2f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) owner->PlaySound(7);
        break;

case 807:
        if (owner->action == 304) {
            x = owner->x + facing * 3;
            y = owner->y + 110.0f;
        }
        if (owner->action != 304) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->field082 == 0 && AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 808:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
            field0DC = AngleAt00483300(owner->opponent->y + 128.0f - y,
                (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
            if (field0DC < -20) field0DC = -20;
            if (field0DC > 20) field0DC = 20;
        }
        if (animationStage < 3) SetPolarVelocity(field0DC, 20.0f);
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage < 3)
            owner->SpawnBattleEffect(809, x - 10.0f + RecordedRange(0, 20),
                y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (field07C == 6) {
            ++field080;
            field07C = 0;
        }
        if (animationStage == 2 && field07C == 1) {
            ResetSecondaryCounter(3);
            UnknownAt0045B850(9);
            velocityX = 0.0f;
            velocityY = 0.0f;
            owner->fieldF0C = 0;
            return;
        }
        if (animationStage == 3 && animationFrame == 0 && field07C == 1) {
            for (int burstIndex808 = 0; burstIndex808 < 8; ++burstIndex808) {
                owner->field314 = burstIndex808;
                owner->SpawnBattleEffect(810, owner->opponent->x, owner->opponent->y + 100.0f, 1, 1);
                ++owner->fieldF0C;
            }
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        break;

case 809:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 0.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.15f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 810:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        SetPolarVelocity(owner->fieldF0E + 45.0f * field0C8, 140.0f);
        x = velocityX + owner->opponent->x;
        y = velocityY * 0.5f + owner->opponent->y + 100.0f;
        if (velocityY > 0.0f) field04C = -5.0f;
        else field04C = 5.0f;
        if (animationStage < 15) {
            if (owner->opponent->health > 2) --owner->opponent->health;
            if (owner->opponent->field3A0 > 0 && owner->opponent->recoverableHealth > 2) --owner->opponent->recoverableHealth;
            if (color[0] < 235) color[0] += 20;
            else color[0] = 255;
        }
        if ((owner->opponent->health <= 0 || owner->field3A0 <= 0 || owner->health <= 0 || owner->fieldF0C == 0 ||
            (owner->action > 49 && owner->action < 150)) && animationStage < 15) {
            ResetSecondaryCounter(animationStage + 14);
            --owner->fieldF0C;
            if (owner->fieldF0C < 0) owner->fieldF0C = 0;
        }
        if (animationStage > 14) {
            if (color[0] > 10) color[0] -= 10;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) { ResetSecondaryCounter(15); return; }
        if (animationStage == 15 && animationFrame == 0) {
            if (field0D8 - 1 < field0C8 * 2) {
                ResetSecondaryCounter(1);
                ++field0D8;
            }
            else {
                --owner->fieldF0C;
                if (owner->fieldF0C < 0) owner->fieldF0C = 0;
            }
        }
        break;

case 812:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
        }
        SetPolarVelocity(field0C8, field0CC);
        x = facing * velocityX + x;
        y -= velocityY;
        owner->SpawnBattleEffect(827, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationStage == 1) {
            if (y > owner->field2E0 && velocityY < 0.0f) field0D8 = 1;
            if (y < 0.0f && velocityY > 0.0f) field0D8 = 1;
            if (x < owner->field2D8 && facing * velocityX < 0.0f) field0D8 = 1;
            if (x > owner->field2DC && facing * velocityX > 0.0f) field0D8 = 1;
            if (field0D8 == 1) {
                owner->PlaySound(0);
                for (int collisionIndex812 = 0; collisionIndex812 < 1; ++collisionIndex812) {
                    owner->field318 = collisionIndex812 * 2 + 1;
                    owner->field314 = AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                    owner->SpawnBattleEffect(813, x, y, facing, 1);
                }
                ClearFrameInfo();
                return;
            }
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 30) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;


case 813:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex813 = 0; rewardIndex813 < 2; ++rewardIndex813)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 814:
        if (owner->action == 307) {
            x = owner->x + facing * 20;
            y = owner->y + 125.0f;
        }
        if (owner->action != 307) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationX = 110.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 815:
        if (owner->action == 301 || owner->action == 391) {
            x = owner->x;
            y = owner->y + 100.0f;
        }
        if (owner->action != 301 && owner->action != 391) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationX = 110.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 816:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
        }
        SetPolarVelocity(field0C8, field0CC);
        x = facing * velocityX + x;
        y -= velocityY;
        owner->SpawnBattleEffect(828, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationStage == 1) {
            if (y > owner->field2E0 && velocityY < 0.0f) field0D8 = 1;
            if (y < 0.0f && velocityY > 0.0f) field0D8 = 1;
            if (x < owner->field2D8 && facing * velocityX < 0.0f) field0D8 = 1;
            if (x > owner->field2DC && facing * velocityX > 0.0f) field0D8 = 1;
            if (field0D8 == 1) {
                owner->PlaySound(0);
                for (int collisionIndex816 = 0; collisionIndex816 < 1; ++collisionIndex816) {
                    owner->field318 = collisionIndex816 * 2 + 1;
                    owner->field314 = AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                    owner->SpawnBattleEffect(818, x, y, facing, 1);
                }
                ClearFrameInfo();
                return;
            }
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 30) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;

case 817:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
        }
        SetPolarVelocity(field0C8, field0CC);
        x = facing * velocityX + x;
        y -= velocityY;
        owner->SpawnBattleEffect(829, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationStage == 1) {
            if (y > owner->field2E0 && velocityY < 0.0f) field0D8 = 1;
            if (y < 0.0f && velocityY > 0.0f) field0D8 = 1;
            if (x < owner->field2D8 && facing * velocityX < 0.0f) field0D8 = 1;
            if (x > owner->field2DC && facing * velocityX > 0.0f) field0D8 = 1;
            if (field0D8 == 1) {
                owner->PlaySound(0);
                for (int collisionIndex817 = 0; collisionIndex817 < 1; ++collisionIndex817) {
                    owner->field318 = collisionIndex817 * 2 + 1;
                    owner->field314 = AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                    owner->SpawnBattleEffect(819, x, y, facing, 1);
                }
                ClearFrameInfo();
                return;
            }
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 30) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;



case 818:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex818 = 0; rewardIndex818 < 2; ++rewardIndex818)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 819:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex819 = 0; rewardIndex819 < 2; ++rewardIndex819)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 820:
        if (owner->action == 390) {
            x = owner->x + facing * 146;
            y = owner->y + 80.0f;
        }
        if (owner->action != 390) { ClearFrameInfo(); return; }
        owner->SpawnBattleEffect(805, x - 10.0f + RecordedRange(0, 40),
            y - 10.0f + RecordedRange(0, 40), facing, 1);
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 1.5f;
            scaleY = field0DA * 0.01f + 1.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 30) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;

case 821:
        if (owner->action == 310 || owner->action == 392) {
            x = owner->x + facing * 20;
            y = owner->y + 100.0f;
        }
        if (owner->action != 310 && owner->action != 392) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationX = 140.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;



case 822:
        if (owner->action == 607 || owner->action == 609) {
            x = owner->x + facing * 105;
            y = owner->y + 145.0f;
        }
        if (owner->action != 607 && owner->action != 609) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.2f;
            scaleY = 0.2f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 1;
            field07C = 0;
            field0D8 = 0;
        }
        if (field07C == 6) field07C = 0;
        if (animationStage == 1 && field0D8 == 0) {
            if (scaleX < 1.0f) {
                scaleX += 0.1f;
                scaleY += 0.1f;
            }
            else {
                scaleX = 1.0f;
                scaleY = 1.0f;
                ++field0D8;
            }
        }
        if (animationStage < 4 && field0D8 > 0) {
            scaleX = RecordedRange(0, 8) * 0.25f + 1.0;
            scaleY = scaleX;
        }
        if (animationStage == 4) {
            scaleX *= 0.85f;
            scaleY = scaleX;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 1 && animationFrame == 0) {
            for (int burstIndex822 = 0; burstIndex822 < 5; ++burstIndex822) {
                owner->PlaySound(2);
                owner->field314 = 8 - burstIndex822 * 4;
                owner->SpawnBattleEffect(823, x, y, facing, 1);
            }
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->SpawnBattleEffect(824, x, y, facing, 1);
            owner->SetCameraShake(4.0f);
        }
        break;

case 823:
        if (owner->action == 607 || owner->action == 609) {
            x = owner->x + facing * 105;
            y = owner->y + 145.0f;
        }
        if (owner->action != 607 && owner->action != 609) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.1f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = field0C8;
            field0D8 = 0;
        }
        if (animationStage == 1) {
            scaleX += 0.2f;
            scaleY += 0.0025f;
        }
        if (animationStage == 2) {
            scaleX += 0.1f;
            scaleY *= 0.85f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) scaleY += 3.0f;
        break;

case 824:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 70.0f;
            field01A = 1250;
            rotationZ = RecordedRange(0, 359);
        }
        scaleX += 0.2f;
        scaleY += 0.2f;
        if (color[0] > 20) color[0] -= 20;
        else { ClearFrameInfo(); return; }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;



case 825:
        if (owner->action == 608 || owner->action == 610) {
            x = owner->x + facing * 105;
            y = owner->y + 145.0f;
        }
        if (owner->action != 608 && owner->action != 610) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.2f;
            scaleY = 0.2f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 3;
            field07C = 0;
            field0D8 = 0;
        }
        if (field07C == 6) field07C = 0;
        if (animationStage == 1 && field0D8 == 0) {
            if (scaleX < 1.0f) {
                scaleX += 0.1f;
                scaleY += 0.1f;
            }
            else {
                scaleX = 1.0f;
                scaleY = 1.0f;
                ++field0D8;
            }
        }
        if (animationStage < 6 && field0D8 > 0) {
            scaleX = RecordedRange(0, 8) * 0.25f + 1.0;
            scaleY = scaleX;
        }
        if (animationStage == 6) {
            scaleX *= 0.85f;
            scaleY = scaleX;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 1 && animationFrame == 0) {
            for (int burstIndex825 = 0; burstIndex825 < 5; ++burstIndex825) {
                owner->PlaySound(2);
                owner->field314 = 8 - burstIndex825 * 4;
                owner->SpawnBattleEffect(826, x, y, facing, 1);
            }
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->SpawnBattleEffect(824, x, y, facing, 1);
            owner->SetCameraShake(4.0f);
            field07C = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            owner->SpawnBattleEffect(824, x, y, facing, 1);
            owner->SetCameraShake(4.0f);
            field07C = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            owner->SpawnBattleEffect(824, x, y, facing, 1);
            owner->SetCameraShake(4.0f);
            field07C = 0;
        }
        break;

case 826:
        if (owner->action == 608 || owner->action == 610) {
            x = owner->x + facing * 105;
            y = owner->y + 145.0f;
        }
        if (owner->action != 608 && owner->action != 610) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.1f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = field0C8;
            field0D8 = 0;
        }
        if (animationStage == 1) {
            scaleX += 0.2f;
            scaleY += 0.0025f;
        }
        if (animationStage > 1) {
            scaleX += 0.1f;
            scaleY *= 0.85f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) scaleY += 3.0f;
        if (animationStage == 3 && animationFrame == 0) scaleY += 3.0f;
        if (animationStage == 4 && animationFrame == 0) scaleY += 3.0f;
        break;




case 827:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 6.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.15f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 828:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 6.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.15f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 829:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 6.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.15f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 830:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex830 = 0; rewardIndex830 < 3; ++rewardIndex830)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 100;
            }
            --field0D8;
            if (field0D8 < 0) field0D8 = 0;
            SetPolarVelocity(0.0f, field0D8 * field0CC * 0.01f);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] >= 25) color[0] -= 25;
                        else color[0] = 0;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

case 831:
        if (owner->action > 49 && owner->action < 150 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field07C = 0;
            field080 = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DC = 0;
        }
        if (animationStage < 3) {
            SetPolarVelocity(owner->fieldF0E * 2 + field0C8, field0D8);
            field0D8 = field0D8 + 10;
            if (field0D8 > 80) field0D8 = 80;
            x = velocityX + field0CC;
            y = velocityY + field0D0;
            if ((owner->action == 611 || owner->action == 612 || owner->action == 613) && owner->animationStage == 0) {
                ResetSecondaryCounter(3);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
        }
        owner->SpawnBattleEffect(827, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
        if (animationStage == 2 && animationFrame == 0) {
            if (field0DC < 5) {
                ResetSecondaryCounter(1);
                ++field0DC;
            }
            else field0DC = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            if (field0DC < 15) {
                ++field0DC;
                ResetSecondaryCounter(2);
                return;
            }
            else { ClearFrameInfo(); return; }
        }
        break;



case 832:
        if (field07C == 5) { ClearFrameInfo(); return; }
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
            ClearFrameInfo(); return;
        }
        if ((owner->action != 704 || (owner->action == 704 && owner->animationStage > 9)) && animationStage < 2)
            field0D0 *= 0.9f;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 3;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage < 2) field0C8 = field0D0 * 0.1f + field0C8;
        SetPolarVelocity(field0C8, field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage > 1) {
            if (color[0] >= 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0 && field0D8 < 50) {
            ResetSecondaryCounter(1);
            field07C = 0;
            ++field0D8;
        }
        break;

case 833:
        if (field07C == 5) { ClearFrameInfo(); return; }
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
            ClearFrameInfo(); return;
        }
        if ((owner->action != 704 || (owner->action == 704 && owner->animationStage > 9)) && animationStage < 2)
            field0D0 *= 0.75f;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 3;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage < 2) field0C8 = field0D0 * 0.1f + field0C8;
        SetPolarVelocity(field0C8, field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage > 1) {
            if (color[0] >= 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0 && field0D8 < 50) {
            ResetSecondaryCounter(1);
            field07C = 0;
            ++field0D8;
        }
        break;

case 834:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 38) {
            ClearFrameInfo();
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex834 = 0; rewardIndex834 < 3; ++rewardIndex834)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 2;
                field07C = 0;
                SetPolarVelocity(field0C8, field0CC);
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            ++field0D8;
            if (animationStage < 38) SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
            if (field07C == 4 && field080 > 0) field07C = 0;
            if (field07C != 0 && animationStage < 38) {
                ResetSecondaryCounter(38);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 37) {
                        if (color[0] >= 15) {
                            color[0] -= 15;
                            scaleX *= 0.9f;
                            scaleY = scaleX;
                        }
                        else { ClearFrameInfo(); return; }
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        if (animationStage == 38 && animationFrame == 0) ResetSecondaryCounter(21);
        break;

case 835:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 40.0f;
            rotationY = facing * -40;
            rotationZ = RecordedRange(0, 359);
        }
        scaleX += 0.05f;
        scaleY += 0.05f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 836:
        if (owner->action > 49 && owner->action < 150 && animationStage < 3) ResetSecondaryCounter(3);
        if (owner->action == 706 && owner->animationStage == 0 && animationStage < 3) ResetSecondaryCounter(3);
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        x = facing * velocityX + x;
        y += velocityY;
        --field0DA;
        if (animationStage == 2) {
            velocityX = 0.0f;
            if (owner->opponent->x + 40.0f < x) velocityX = facing * -2;
            if (owner->opponent->x - 40.0f > x) velocityX = facing * 2;
        }
        if (animationStage == 2 && field0DA < 0) {
            owner->field314 = -RecordedRange(0, 80) - 50;
            owner->field318 = RecordedRange(0, 18) + 15;
            owner->SpawnBattleEffect(837, (100 - RecordedRange(0, 200)) * facing + x,
                y, facing, 1);
            field0DA = 1;
        }
        if (animationStage == 3) {
            if (color[0] > 13) color[0] -= 13;
            else color[0] = 0;
        }
        if (animationStage < 2) {
            scaleX += 0.8f;
            scaleY += 0.1f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) owner->PlaySound(7);
        break;

case 837:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
        }
        SetPolarVelocity(field0C8, field0CC);
        if (animationStage < 2 && field0CC == 2.0f) ResetSecondaryCounter(2);
        x = facing * velocityX + x;
        y += velocityY;
        owner->SpawnBattleEffect(805, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 30) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;

case 838:
        if (owner->action > 49 && owner->action < 150 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field07C = 0;
            if (owner->action == 613) field080 = 1;
            else field080 = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DC = 0;
        }
        if (animationStage < 3) {
            SetPolarVelocity(owner->fieldF0E * 2 + field0C8, field0D8);
            field0D8 = field0D8 + 10;
            if (field0D8 > 120) field0D8 = 120;
            x = velocityX + field0CC;
            y = velocityY + field0D0;
            if ((field080 == 0 && owner->action != 611 && owner->action != 612) ||
                ((owner->action == 611 || owner->action == 612 || owner->action == 613) && owner->animationStage == 0)) {
                ResetSecondaryCounter(3);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
        }
        owner->SpawnBattleEffect(827, x - 10.0f + RecordedRange(0, 20),
            y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
        if (animationStage == 2 && animationFrame == 0) {
            if (field0DC < 5) {
                ResetSecondaryCounter(1);
                ++field0DC;
            }
            else field0DC = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            if (field0DC < 40) {
                ++field0DC;
                ResetSecondaryCounter(2);
                return;
            }
            else { ClearFrameInfo(); return; }
        }
        break;

case 839:
        if (field07C == 5) { ClearFrameInfo(); return; }
        if (owner->action > 49 && owner->action < 150 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            if (reinterpret_cast<short&>(owner->fieldEFA) > 25) {
                reinterpret_cast<short&>(owner->fieldEFA) = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            SetPolarVelocity(RecordedRange(0, 60) - 30, 4.0f);
            field080 = 1;
            field07C = 0;
        }
        if (field07C != 0) { ClearFrameInfo(); return; }
        if (owner->opponent->y + 100.0f < y) velocityY -= 0.02f;
        if (owner->opponent->y + 100.0f >= y) velocityY += 0.02f;
        velocityX += 0.05f;
        if (field0D8 <= 0) {
            field07C = 0;
            field0D8 = 10;
        }
        --field0D8;
        x = facing * velocityX + x;
        y += velocityY;
        if (animationFrame == 0)
            owner->SpawnBattleEffect(840, x - 10.0f + RecordedRange(0, 20),
                y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.9f;
            scaleY = field0DA * 0.01f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) {
            if (field0DC < 60 && field080 > 0) {
                ResetSecondaryCounter(1);
                ++field0DC;
            }
            else ClearFrameInfo();
        }
        break;



case 840:
        reinterpret_cast<unsigned char&>(facing) = reinterpret_cast<unsigned char&>(owner->facing);
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 1;
            velocityY = 4.0f;
            velocityX = 0.0f;
        }
        velocityY -= 0.1f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;






case 841:
        if (owner->action == 309) {
            x = owner->x + facing * 20;
            y = owner->y + 40.0f;
        }
        if (owner->action != 309) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationX = -70.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 842:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        SetPolarVelocity(owner->fieldF0E + 45.0f * field0C8, 140.0f);
        x = velocityX + owner->opponent->x;
        y = velocityY * 0.5f + owner->opponent->y + 100.0f;
        if (velocityY > 0.0f) field04C = -5.0f;
        else field04C = 5.0f;
        if (animationStage < 21) {
            if (owner->opponent->health > 2) owner->opponent->health = owner->opponent->health - 1;
            if (owner->opponent->field3A0 > 0 && owner->opponent->recoverableHealth > 2) owner->opponent->recoverableHealth = owner->opponent->recoverableHealth - 1;
            if (color[0] < 235) color[0] += 20;
            else color[0] = 255;
        }
        if ((owner->opponent->health <= 0 || owner->field3A0 <= 0 || owner->health <= 0 || owner->fieldF0C == 0 ||
            (owner->action > 49 && owner->action < 150)) && animationStage < 21) {
            ResetSecondaryCounter(animationStage + 20);
            --owner->fieldF0C;
            if (owner->fieldF0C < 0) owner->fieldF0C = 0;
        }
        if (animationStage > 20) {
            if (color[0] > 10) color[0] -= 10;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) { ResetSecondaryCounter(21); return; }
        if (animationStage == 21 && animationFrame == 0) {
            if (field0D8 - 1 < field0C8 * 5.0f) {
                ResetSecondaryCounter(1);
                ++field0D8;
            }
            else {
                --owner->fieldF0C;
                if (owner->fieldF0C < 0) owner->fieldF0C = 0;
            }
        }
        break;

case 843:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field080 = 1;
            field07C = 0;
            field0DC = AngleAt00483300(owner->opponent->y + 128.0f - y,
                (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
            if (field0DC < -40) field0DC = -40;
            if (field0DC > 40) field0DC = 40;
        }
        if (animationStage < 3) SetPolarVelocity(field0DC, 20.0f);
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage < 3)
            owner->SpawnBattleEffect(809, x - 10.0f + RecordedRange(0, 20),
                y - 10.0f + RecordedRange(0, 20), facing, 1);
        if (field07C == 6) {
            ++field080;
            field07C = 0;
        }
        if (animationStage == 2 && field07C == 1) {
            UnknownAt0045B850(14);
            ResetSecondaryCounter(3);
            velocityX = 0.0f;
            velocityY = 0.0f;
            owner->fieldF0C = 0;
            return;
        }
        if (animationStage == 3 && animationFrame == 0 && field07C == 1) {
            for (int burstIndex843 = 0; burstIndex843 < 8; ++burstIndex843) {
                owner->field314 = burstIndex843;
                owner->SpawnBattleEffect(842, owner->opponent->x, owner->opponent->y + 100.0f, 1, 1);
                ++owner->fieldF0C;
            }
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 0.5f;
            scaleY = field0DA * 0.01f + 0.5f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        break;

case 844:
        if (owner->action == 300) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 300) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->field082 == 0 && AdvanceNestedFrame() == field070) ClearFrameInfo();
        return;

case 845:
        if (owner->action == 302) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 302 || (owner->action == 302 && owner->animationStage == 0)) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->field082 == 0 && AdvanceNestedFrame() == field070) ClearFrameInfo();
        return;


case 846:
        if (owner->action == 305) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 305) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->field082 == 0 && AdvanceNestedFrame() == field070) ClearFrameInfo();
        return;

case 847:
        if ((owner->action == 303 || owner->action == 393)) {
            x = owner->x;
            y = owner->y;
        }
        if ((owner->action != 303 && owner->action != 393)) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->field082 == 0 && AdvanceNestedFrame() == field070) ClearFrameInfo();
        return;


case 899:
        reinterpret_cast<unsigned char&>(facing) = reinterpret_cast<unsigned char&>(owner->facing);
        if (owner->action > 149 && owner->action < 154 && animationStage == 0) {
            x = owner->x + float(facing * 57);
            y = owner->y + 94.0f;
        }
        if (owner->action > 153 && owner->action < 158 && animationStage == 0) {
            x = owner->x + float(facing * 57);
            y = owner->y + 60.0f;
        }
        if (owner->action == 158 && animationStage == 0) {
            x = owner->x + float(facing * 57);
            y = owner->y + 100.0f;
        }
        if ((owner->action < 150 || owner->action > 158) && animationStage == 0) {
            ResetSecondaryCounter(1);
            owner->fieldF0A = 0;
        }
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 50.0f;
            field0D8 = 1;
        }
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (color[0] > 30) color[0] -= 30;
            else color[0] = 0;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 1 && animationFrame == 0) ResetSecondaryCounter(0);
        return;

case 900:
        if (field07C == 5) { ClearFrameInfo(); return; }
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 3;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        SetPolarVelocity(field0C8, field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        if (field0D8 == 0) {
            field0CC -= 0.2f;
            if (field0CC < 1.0) {
                field0CC = 1.0f;
                field0D8 = 1;
                ResetSecondaryCounter(2);
            }
        }
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage > 2) {
            if (color[0] >= 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) {
            field07C = 0;
            ResetSecondaryCounter(1);
        }
        if (animationStage == 3 && animationFrame == 0 && field0D8 < g_F1212_DifficultyAt006714D0 * 2) {
            ResetSecondaryCounter(2);
            field07C = 0;
            ++field0D8;
        }
        break;

case 902:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DA = 0;
        }
        --field0DA;
        if (animationStage == 2 && field0DA < 0) {
            owner->field314 = -RecordedRange(0, 40) - 70;
            owner->field318 = RecordedRange(0, 6) + 15;
            owner->SpawnBattleEffect(903, (10 - RecordedRange(0, 20)) * facing + x,
                y, facing, 1);
            if (g_F1212_DifficultyAt006714D0 == 3 && RecordedRange(0, 100) < 20)
                owner->SpawnBattleEffect(904, (10 - RecordedRange(0, 20)) * facing + x,
                    y, facing, 1);
            field0DA = 3;
        }
        if (animationStage == 3) {
            if (color[0] > 13) color[0] -= 13;
            else color[0] = 0;
        }
        if (animationStage < 2 && animationFrame < 10) {
            scaleX += 0.4f;
            scaleY += 0.1f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) owner->PlaySound(7);
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 0) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;

case 903:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DA = 0;
            field080 = 1;
            field07C = 0;
        }
        SetPolarVelocity(field0C8, field0CC);
        if (animationStage < 2 && field0CC == 2.0f) ResetSecondaryCounter(2);
        x = facing * velocityX + x;
        y += velocityY;
        --field0DA;
        if (field0DA <= 0) {
            owner->SpawnBattleEffect(805, x - 10.0f + RecordedRange(0, 20),
                y - 10.0f + RecordedRange(0, 20), facing, 1);
            field0DA = 4;
        }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.01f + 1.0f;
            scaleY = field0DA * 0.01f + 1.0f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 3 && animationFrame == 0 && field0D8 < 30) {
            ResetSecondaryCounter(2);
            ++field0D8;
        }
        break;

case 904:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            field080 = 1;
            field07C = 0;
            field0C8 = -RecordedRange(0, 90) - 30;
            field0CC = RecordedRange(0, 9) + 8;
            SetPolarVelocity(field0C8, field0CC);
            velocityX = RecordedRange(0, 10) - 3;
            velocityY = RecordedRange(0, 10) + 5;
        }
        if (animationStage == 2) {
            velocityY -= 0.4f;
            if (velocityY < -4.0f) velocityY = -4.0f;
            if (y + velocityY <= 0.0f) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(3);
            }
        }
        x = facing * velocityX + x;
        y += velocityY;
        --field0DC;
        if (field0DC <= 0) {
            owner->SpawnBattleEffect(805, x - 10.0f + RecordedRange(0, 20),
                y - 10.0f + RecordedRange(0, 20), facing, 1);
            field0DC = 2;
        }
        if (field07C != 0 && animationStage == 2) { ResetSecondaryCounter(3); return; }
        if (animationFrame == 0) {
            field0DA = RecordedRange(0, 20);
            scaleX = field0DA * 0.02f + 0.9f;
            scaleY = field0DA * 0.02f + 0.9f;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0 && field0D8 < 15) {
            ++field0D8;
            ResetSecondaryCounter(1);
        }
        if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        break;





case 905:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        if (animationStage == 1 && animationFrame == 0) {
            UnknownAt0045B850(6);
            if (g_F1212_DifficultyAt006714D0 <= 1 && field0D8 < 5)
                owner->SpawnBattleEffect(902, field0D8 * 300 + RecordedRange(0, 50),
                    0.0f, facing, 1);
            if (g_F1212_DifficultyAt006714D0 == 2 && field0D8 < 5)
                owner->SpawnBattleEffect(902, field0D8 * 270 + RecordedRange(0, 50),
                    0.0f, facing, 1);
            if (g_F1212_DifficultyAt006714D0 == 3 && field0D8 < 6)
                owner->SpawnBattleEffect(902, field0D8 * 240 + RecordedRange(0, 50),
                    0.0f, facing, 1);
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0 && field0D8 < 13) {
            ++field0D8;
            ResetSecondaryCounter(1);
        }
        break;

case 906:
        if (animationStage < 3) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 760 && owner->action != 761 && animationStage < 3) { ResetSecondaryCounter(3); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 150.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.05f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        if (animationStage == 0) {
            scaleX += 0.1f;
            if (scaleX > 1.0f) scaleX = 1.0f;
        }
        if (animationStage == 0) {
            g_F1239_DwordAt0067149C = 0xFFFFFF;
            if (field0D8 == 0) {
                g_F1239_ByteAt006714D1 = 255;
                field0D8 = 1;
            }
            if (field0D8 == 1) {
                if (g_F1239_ByteAt006714D1 > 15) g_F1239_ByteAt006714D1 -= 15;
                else {
                    g_F1239_ByteAt006714D1 = 0;
                    field0D8 = 2;
                }
            }
        }
        if (animationStage == 1) {
            scaleY += 0.1f;
            if (scaleY > 1.0f) scaleY = 1.0f;
        }
        if (animationStage == 3) {
            if (color[0] > 25) color[0] -= 25;
            else { ClearFrameInfo(); return; }
        }
        if (animationStage == 2 && animationFrame == 0) {
            ResetSecondaryCounter(2);
            owner->SpawnBattleEffect(907, x, y, 1, 0);
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) owner->fieldF04 = 1;
        if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        break;

case 907:
        if (animationStage < 3) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 150.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage == 0) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 25) color[0] -= 25;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 908:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = field0C8;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 256;
            field07C = 0;
            SetPolarVelocity(field0DA, field0D8 * 0.1f + 5.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        ++field0D8;
        SetPolarVelocity(field0DA, field0D8 * 0.1f + 5.0f);
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
        if (color[0] > 20 && animationStage == 2) color[0] -= 20;
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
            field07C = 0;
            return;
        }
        break;

case 909:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = field0C8;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(field0C8, 1.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage < 2) field0C8 += 1.0f;
        ++field0D8;
        SetPolarVelocity(field0C8, field0D8 * 0.05f);
        if (animationStage == 1) SetPolarVelocity(field0C8, 1.0f);
        x = facing * velocityX + x;
        y -= velocityY;
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
        if (field07C != 0 && animationStage < 3) { ResetSecondaryCounter(3); return; }
        if (color[0] > 20 && animationStage == 3) color[0] -= 20;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) {
            field07C = 0;
            field0D8 = 0;
            field0C8 = AngleAt00483300(owner->opponent->y + 100.0f - y,
                (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
        }
        break;

case 910:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            rotationZ = field0CC;
            if (field0CC > 0.0f && field0CC < 180.0f)
                scaleX = y / MathLookup::ReadPhaseTable(field0CC) / 256.0f * 1.1f;
            else scaleX = 6.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        if (animationStage == 1 && animationFrame == 5 && field0CC > 0.0f && field0CC < 180.0f)
            owner->SpawnBattleEffect(911, MathLookup::ReadRatio(90.0f - field0CC) * y + 640.0f, 0.0f, 1, 1);
        scaleY *= 0.85;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 911:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            velocityY = 0.0f;
            velocityX = 0.0f;
            scaleX = 0.25f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (animationStage == 1 && animationFrame == 0)
            owner->SpawnBattleEffect(912, x, y, facing, 1);
        if (animationStage < 3) {
            scaleX += 0.07f;
            scaleY += 0.07f;
        }
        if (animationStage == 4) {
            scaleX *= 0.85f;
            if (color[0] >= 15) color[0] -= 15;
            else { color[0] = 0; ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;








case 912:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationX = -75.0f;
        }
        scaleX += 0.15f;
        scaleY += 0.15f;
        if (animationStage > 1) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 913:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            rotationZ = field0CC;
            if (field0CC > 0.0f && field0CC < 180.0f)
                scaleX = y / MathLookup::ReadPhaseTable(field0CC) / 256.0f * 1.1f;
            else scaleX = 6.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage == 1 && animationFrame == 5 && field0CC > 0.0f && field0CC < 180.0f)
            owner->SpawnBattleEffect(914, MathLookup::ReadRatio(90.0f - field0CC) * y + 640.0f, 0.0f, 1, 1);
        scaleY *= 0.85;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 914:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            velocityY = 0.0f;
            velocityX = 0.0f;
            scaleX = 0.25f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (animationStage == 1 && animationFrame == 0)
            owner->SpawnBattleEffect(915, x, y, facing, 1);
        if (animationStage < 3) {
            scaleX += 0.07f;
            scaleY += 0.07f;
        }
        if (animationStage == 4) {
            scaleX *= 0.85f;
            if (color[0] >= 15) color[0] -= 15;
            else { color[0] = 0; ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;



case 915:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationX = -75.0f;
        }
        scaleX += 0.15f;
        scaleY += 0.15f;
        if (animationStage > 1) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 916:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        ++field0D8;
        field0C8 += field0D0;
        SetPolarVelocity(field0C8, field0D8 * 0.2f + field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) { ClearFrameInfo(); return; }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 917:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        ++field0D8;
        field0C8 += field0D0;
        SetPolarVelocity(field0C8, field0D8 * 0.2f + field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) { ClearFrameInfo(); return; }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 918:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        ++field0D8;
        field0C8 += field0D0;
        SetPolarVelocity(field0C8, field0D8 * 0.2f + field0CC);
        rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) { ClearFrameInfo(); return; }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

case 919:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field0D8 = 0;
            field0DA = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == field070) {
            if (field0D8 < 2 - g_F1212_DifficultyAt006714D0) ++field0D8;
            else {
                owner->SpawnBattleEffect(904, RecordedRange(0, 1200) + 60, RecordedRange(0, 120) + 700,
                    1 - (RecordedRange(0, 100) < 50) * 2, 1);
                field0D8 = 0;
            }
            ResetSecondaryCounter(2);
        }
        break;





case 995:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = RecordedRange(0, 360) - 180;
            field0DA = 15;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) field0DA = 3;
            SetPolarVelocity(field0D8, field0DA * 0.8f);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f);
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ClearFrameInfo();
                if (owner->opponent->field366 < 2) {
                    ++owner->opponent->field366;
                }
                else {
                    owner->opponent->score += 20000;
                }
                PlaySharedSound(46);
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
        }
        break;

case 996:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = RecordedRange(0, 360) - 180;
            field0DA = 15;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) field0DA = 3;
            SetPolarVelocity(field0D8, field0DA * 0.8f);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f);
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ++reinterpret_cast<short&>(owner->fieldEFA);
                PlaySharedSound(46);
                ClearFrameInfo();
                if (owner->opponent->spiritCooldown > 0) {
                    if (owner->opponent->spiritCooldown > 5) {
                        owner->opponent->spiritCooldown -= 5;
                    }
                    else {
                        owner->opponent->spiritCooldown = 0;
                        owner->opponent->spirit = 1000;
                    }
                    return;
                }
                else if (owner->opponent->spirit < 990) {
                    owner->opponent->spirit += 10;
                }
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->field39C == 0) {
                        if (owner->opponent->field36C < 998.9) {
                            owner->opponent->field36C += 0.5f;
                        }
                        else {
                            owner->opponent->field36C = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
        }
        break;

case 997:
        x = owner->x;
        y = 0.0f;
        field08A = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            rotationX = -80.0f;
            field0D8 = owner->field3A0;
        }
        if (owner->field3A0 <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            scaleX = static_cast<float>(owner->field3A0) / field0D8 * 2;
            scaleY = static_cast<float>(owner->field3A0) / field0D8 * 2;
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(9);
                break;
            }
        }
        break;

    default:
        AdvanceNestedFrame();
        break;
    }
}
