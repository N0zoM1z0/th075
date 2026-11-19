// Complete research source for original 005A1600 (43,599 CODE bytes).
// All native states are written; still NONEXACT and not an accepted replacement.
#include "CharacterObject.hpp"
#include "YukariFighter.hpp"
#include "EffectServices.hpp"


float __cdecl AngleAt00483300(float,float);
float __cdecl AbsFloatAt00412D90(float);

extern float g_F1211_AngleDivAt00657828;
extern signed char g_F1212_DifficultyAt006714D0;

void YukariObject::Advance()
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
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex = 0; rewardIndex < 3; ++rewardIndex)
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
            if (animationStage < 2)
                SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
            if ((field07C == 1 || field07C == 2 || field07C == 4 || field07C == 6) && animationStage == 1) {
                ResetSecondaryCounter(2);
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
                    if (animationStage > 1) {
                        rotationZ += 15.0f;
                        scaleX *= 0.9f;
                        scaleY *= 0.9f;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 801:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 75.0f;
        }
        scaleX += 0.2f;
        scaleY += 0.2f;
        if (color[0] > 20) color[0] -= 20;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 802:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX += 0.2f;
        if (animationStage > 0) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 803:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field07C = 0;
            field080 = 1;
            velocityX = 25.0f;
        }
        velocityX -= 0.8f;
        if (velocityX < 2.5f) velocityX = 2.5f;
        x = facing * velocityX + x;
        if (animationStage > 1) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 804:
        if (owner->action == 700 && owner->animationStage < 7) {
            x = owner->x + facing * 126;
            y = owner->y + 139.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = -30.0f;
            rotationY = facing * 60;
            field0D8 = 0;
        }
        rotationZ += 5.0f;
        if (scaleX < 1.0f) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        if (scaleX <= 1.0f && field0D8 == 0) {
            owner->SpawnBattleEffect(805, owner->x, owner->y, facing, 0);
            ++field0D8;
        }
        if ((owner->animationStage > 6 && owner->action == 700) || owner->action != 700) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 805:
        if (owner->action == 700 && owner->animationStage < 7) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 99;
        }
        if ((owner->animationStage > 6 && owner->action == 700) || owner->action != 700) {
            ClearFrameInfo(); return;
        }
        else if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(1);
            field07C = 0;
        }
        break;

    case 806:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex806 = 0; rewardIndex806 < 3; ++rewardIndex806)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(field0C8, 10.0f);
            }
            if (animationStage == 0 && animationFrame >= field0CC) {
                ResetSecondaryCounter(1);
                velocityX = 0.0f;
                velocityY = 0.0f;
                field080 = 1;
                field07C = 0;
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (animationStage == 1) {
                SetPolarVelocity(field0D0, field0D8 * 0.1f);
                field0D8 += 10;
                reinterpret_cast<unsigned int&>(owner->field314) = reinterpret_cast<unsigned int&>(field0D0);
                owner->field318 = field0D8;
                owner->SpawnBattleEffect(807, x, y, facing, 1);
                if (field07C != 0) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    ResetSecondaryCounter(2);
                    return;
                }
            }
            if (animationStage == 2) {
                field0D8 -= 20;
                if (field0D8 < 0) field0D8 = 0;
                reinterpret_cast<unsigned int&>(owner->field314) = reinterpret_cast<unsigned int&>(field0D0);
                owner->field318 = field0D8;
                owner->SpawnBattleEffect(807, x, y, facing, 1);
                scaleX *= 0.95f;
                scaleY *= 0.95f;
            }
            if (x > 1800.0f || x < -520.0f || y > 1400.0f || y < -520.0f) {
                ClearFrameInfo(); return;
            }
            else if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 807:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = field0CC * 0.01f + 0.0f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field07C = 0;
            field080 = 1;
            reinterpret_cast<unsigned int&>(rotationZ) = reinterpret_cast<unsigned int&>(field0C8);
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 808:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 255;
            field07C = 0;
            field0D8 = 0;
        }
        if (animationStage < 6) {
            scaleX += 0.2f;
            if (scaleX > 1.5) scaleX = 1.5f;
        }
        if (animationStage > 5 && field07C == 5) {
            field07C = 0;
            ++static_cast<YukariFighter*>(owner)->fieldF30;
            if (static_cast<YukariFighter*>(owner)->fieldF30 > 10) static_cast<YukariFighter*>(owner)->fieldF30 = 10;
        }
        if (field080 == 0) {
            if (scaleX > 0.15f) scaleX -= 0.15f;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(6);
            ++field0D8;
            if (field0D8 > 1) field080 = 0;
        }
        break;

    case 809:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 255;
            field07C = 0;
            field0D8 = 0;
        }
        if (animationStage < 6) {
            scaleX += 0.2f;
            if (scaleX > 1.5) scaleX = 1.5f;
        }
        if (animationStage > 5 && field07C == 5) {
            field07C = 0;
            ++static_cast<YukariFighter*>(owner)->fieldF30;
            if (static_cast<YukariFighter*>(owner)->fieldF30 > 10) static_cast<YukariFighter*>(owner)->fieldF30 = 10;
        }
        if (field080 == 0) {
            if (scaleX > 0.15f) scaleX -= 0.15f;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(6);
            ++field0D8;
            if (field0D8 > 2) field080 = 0;
        }
        break;

    case 810:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        if (animationStage == 3 && animationFrame == 0)
            owner->SpawnBattleEffect(811, x, y - 220.0f, facing, 1);
        break;

    case 811:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        x = facing * velocityX + x;
        y += velocityY;
        if (y + velocityY <= 0.0f && animationStage < 7) {
            velocityY = 0.0f;
            y = 0.0f;
            owner->SetCameraShake(5.0f);
            ResetSecondaryCounter(7);
            owner->PlaySound(10);
            owner->SpawnAuxEffect(129, x - 50.0f, 0.0f, 1, 1);
            owner->SpawnAuxEffect(129, x + 50.0f, 0.0f, -1, 1);
            return;
        }
        else {
            if (animationStage == 8) {
                if (color[0] > 15) color[0] -= 15;
                else { ClearFrameInfo(); return; }
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 6 && animationFrame == 0) {
                velocityY = -18.0f;
                owner->PlaySound(5);
            }
        }
        break;

    case 813:
        owner->fieldF0E = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 20;
            field07C = 0;
            scaleX = 0.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 0;
        }
        if (animationStage == 1) {
            if (scaleX < 1.0f) scaleX += 0.25f;
            if (scaleY > 1.0f) scaleY -= 0.25f;
        }
        if (animationStage == 2 && AbsFloatAt00412D90(x - owner->opponent->x) < 100.0f) {
            ResetSecondaryCounter(3);
            velocityX = 10.0f;
            NoOpAt0045B850(8);
            return;
        }
        else {
            if (animationStage == 3) {
                rotationZ -= 30.0f;
                if (velocityX > 1.0f) velocityX -= 1.0f;
            }
            if (animationStage == 4) {
                velocityY -= 0.4f;
                rotationZ -= 30.0f;
            }
            if (animationStage == 5) {
                rotationZ -= 30.0f;
                if (color[0] > 10) color[0] -= 10;
                else { ClearFrameInfo(); owner->fieldF0E = 0; return; }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (x > 1480.0f || x < -200.0f) {
                ClearFrameInfo(); owner->fieldF0E = 0; return;
            }
            else {
                if (AdvanceNestedFrame() == field070) {
                    ClearFrameInfo(); owner->fieldF0E = 0; return;
                }
                else {
                    if (animationStage == 2 && animationFrame == 0) velocityX = 30.0f;
                    if (animationStage == 4 && animationFrame == 0) {
                        if (field0D8 < 20 && field080 > 0) {
                            ResetSecondaryCounter(3);
                            field07C = 0;
                            ++field0D8;
                            return;
                        }
                        if (field07C != 0) {
                            ResetSecondaryCounter(4);
                            velocityX = -3.0f;
                            velocityY = 15.0f;
                        }
                        else ResetSecondaryCounter(5);
                    }
                    if (animationStage == 5 && animationFrame == 0) NoOpAt0045B850(9);
                }
            }
        }
        break;

    case 814:
        owner->fieldF0E = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 30;
            field07C = 0;
            scaleX = 0.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 0;
        }
        if (field08A > 0 && owner->field3B8 == 0) field08A = 0;
        if (animationStage == 1) {
            if (scaleX < 1.0f) scaleX += 0.25f;
            if (scaleY > 1.0f) scaleY -= 0.25f;
        }
        if (animationStage == 2 && AbsFloatAt00412D90(x - owner->opponent->x) < 100.0f) {
            ResetSecondaryCounter(3);
            velocityX = 10.0f;
            NoOpAt0045B850(8);
            return;
        }
        else {
            if (animationStage == 3) {
                rotationZ -= 30.0f;
                if (velocityX > 1.0f) velocityX -= 1.0f;
            }
            if (animationStage == 4) {
                velocityY -= 0.4f;
                rotationZ -= 30.0f;
            }
            if (animationStage == 5) {
                rotationZ -= 30.0f;
                if (color[0] > 10) color[0] -= 10;
                else { ClearFrameInfo(); owner->fieldF0E = 0; return; }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (x > 1480.0f || x < -200.0f) {
                ClearFrameInfo(); owner->fieldF0E = 0; return;
            }
            else {
                if (AdvanceNestedFrame() == field070) {
                    ClearFrameInfo(); owner->fieldF0E = 0; return;
                }
                else {
                    if (animationStage == 2 && animationFrame == 0) velocityX = 30.0f;
                    if (animationStage == 4 && animationFrame == 0) {
                        if (field0D8 < 30 && field080 > 0) {
                            ResetSecondaryCounter(3);
                            field07C = 0;
                            ++field0D8;
                            return;
                        }
                        if (field07C != 0) {
                            ResetSecondaryCounter(4);
                            velocityX = -2.0f;
                            velocityY = 15.0f;
                        }
                        else ResetSecondaryCounter(5);
                    }
                    if (animationStage == 5 && animationFrame == 0) NoOpAt0045B850(9);
                }
            }
        }
        break;

    case 815:
        static_cast<YukariFighter*>(owner)->fieldF10 = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 20;
            field07C = 0;
            scaleX = 0.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 0;
        }
        if (field08A > 0 && owner->field3B8 == 0) field08A = 0;
        if (animationStage == 1) {
            if (scaleX < 1.0f) scaleX += 0.25f;
            if (scaleY > 1.0f) scaleY -= 0.25f;
        }
        if (animationStage > 1) {
            if ((facing == 1 &&
                 ((velocityX > 0.0f && x > owner->field2DC) ||
                  (velocityX < 0.0f && x < owner->field2D8))) ||
                (facing == -1 &&
                 ((velocityX < 0.0f && x > owner->field2DC) ||
                  (velocityX > 0.0f && x < owner->field2D8))))
                velocityX = -velocityX;
            rotationZ -= 30.0f;
            velocityY -= 0.8f;
            if (y + velocityY < 0.0f && velocityY < 0.0f) {
                ++field0D8;
                field07C = 0;
                field080 = 1;
                velocityY = -velocityY;
                owner->PlaySound(13);
            }
        }
        if (animationStage == 5) {
            rotationZ -= 30.0f;
            if (color[0] > 10) color[0] -= 10;
            else { ClearFrameInfo(); static_cast<YukariFighter*>(owner)->fieldF10 = 0; return; }
        }
        x = facing * velocityX + x;
        y += velocityY;
        if (AdvanceNestedFrame() == field070) {
            ClearFrameInfo(); static_cast<YukariFighter*>(owner)->fieldF10 = 0; return;
        }
        else {
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = 6.0f;
                velocityY = 16.0f;
            }
            if (animationStage == 4 && animationFrame == 0 && field0D8 < 5)
                ResetSecondaryCounter(3);
        }
        break;

    case 816:
        if (owner->action == 703 && owner->animationStage < 7) {
            x = owner->x + facing * 126;
            y = owner->y + 140.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 20.0f;
            rotationY = facing * -50;
            field0D8 = 0;
            field0DA = 0;
            field080 = 99;
            field07C = 0;
        }
        if (animationStage == 3 && animationFrame == 0) owner->field490 = 0.0f;
        rotationZ += 5.0f;
        if (scaleX < 1.0f) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        else {
            scaleX = 1.0f;
            scaleY = 1.0f;
            if (animationStage < 2) { ResetSecondaryCounter(2); return; }
        }
        if (((owner->animationStage > 6 && owner->action == 703) || owner->action != 703) && animationStage == 2) {
            ResetSecondaryCounter(3); return;
        }
        else {
            if (animationStage == 2) {
                ++field0DA;
                if (field0DA > 80) field0DA = 80;
                owner->field490 = -(field0DA * 0.1f) *
                    (facing * owner->opponent->facing) *
                    (((owner->opponent->x - x) * facing > 0.0f) * 2 - 1);
            }
            if (animationStage == 3) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 3 && animationFrame == 0) {
                ResetSecondaryCounter(2);
                field07C = 0;
            }
        }
        break;

    case 817:
        if (owner->action == 703 && owner->animationStage < 7) {
            x = owner->x + facing * 127;
            y = owner->y + 140.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 20.0f;
            rotationY = facing * -50;
            field0D8 = 0;
            field0DA = 0;
            field080 = 99;
            field07C = 0;
        }
        rotationZ -= 5.0f;
        if (scaleX < 1.0f) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        else {
            scaleX = 1.0f;
            scaleY = 1.0f;
            if (animationStage < 2) { ResetSecondaryCounter(2); return; }
        }
        if (((owner->animationStage > 6 && owner->action == 703) || owner->action != 703) && animationStage == 2) {
            ResetSecondaryCounter(3); return;
        }
        else {
            if (animationStage == 3) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 3 && animationFrame == 0) {
                ResetSecondaryCounter(2);
                field07C = 0;
            }
        }
        break;

    case 818:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            SetPolarVelocity(field0C8, 12.0f);
            reinterpret_cast<unsigned int&>(rotationZ) = reinterpret_cast<unsigned int&>(field0C8);
        }
        if (field0C8 == 0.0f) y = 0.0f;
        if (field0C8 == -90.0f) {
            if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
            if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
        }
        if (field0C8 == -180.0f) reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->field2E0);
        if (field0C8 == 90.0f) {
            if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
            if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
        }
        x = facing * velocityX + x;
        y += velocityY;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 819:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 0;
        }
        if (field0D8 > 5 || (owner->action == 702 && owner->animationStage == 3)) {
            ClearFrameInfo(); return;
        }
        else {
            if (animationStage == 1) {
                if (animationStage == 1 && animationFrame == 0) {
                    owner->field314 = 0.0f;
                    owner->SpawnBattleEffect(818, x, y, facing, 1);
                }
                velocityX = 12.0f;
                y = 0.0f;
                if ((x < owner->field2D8 && facing == -1) ||
                    (x > owner->field2DC && facing == 1)) {
                    ResetSecondaryCounter(2);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 2) {
                if (animationStage == 2 && animationFrame == 0) {
                    owner->field314 = -90.0f;
                    owner->SpawnBattleEffect(818, x, y, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = 12.0f;
                if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
                if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
                if (y > owner->field2E0) {
                    ResetSecondaryCounter(3);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 3) {
                if (animationStage == 3 && animationFrame == 0) {
                    owner->field314 = -180.0f;
                    owner->SpawnBattleEffect(818, x, y, facing, 1);
                }
                velocityX = -12.0f;
                velocityY = 0.0f;
                reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->field2E0);
                if ((x < owner->field2D8 && facing == 1) ||
                    (x > owner->field2DC && facing == -1)) {
                    ResetSecondaryCounter(4);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 4) {
                if (animationStage == 4 && animationFrame == 0) {
                    owner->field314 = 90.0f;
                    owner->SpawnBattleEffect(818, x, y, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = -12.0f;
                if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
                if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
                if (y < 0.0f) {
                    ResetSecondaryCounter(1);
                    velocityX = 8.0f;
                    velocityY = 0.0f;
                    y = 0.0f;
                    owner->field314 = 0.0f;
                    owner->SpawnBattleEffect(818, x, y, facing, 1);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) { ResetSecondaryCounter(4); return; }
            else {
                if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
                if (animationStage == 4 && animationFrame == 0) ResetSecondaryCounter(3);
            }
        }
        break;

    case 820:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            SetPolarVelocity(field0C8, 12.0f);
            reinterpret_cast<unsigned int&>(rotationZ) = reinterpret_cast<unsigned int&>(field0C8);
        }
        if (field0C8 == 0.0f) y = 0.0f;
        if (field0C8 == -90.0f) {
            if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
            if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
        }
        if (field0C8 == -180.0f) reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->field2E0);
        if (field0C8 == 90.0f) {
            if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
            if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
        }
        x = facing * velocityX + x;
        y += velocityY;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 821:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 0;
        }
        if (field0D8 > 5 || (owner->action == 706 && owner->animationStage == 3)) {
            ClearFrameInfo(); return;
        }
        else {
            if (animationStage == 1) {
                if (animationStage == 1 && animationFrame == 0) {
                    owner->field314 = 0.0f;
                    owner->SpawnBattleEffect(820, x, y, facing, 1);
                }
                velocityX = 12.0f;
                y = 0.0f;
                if ((x < owner->field2D8 && facing == -1) ||
                    (x > owner->field2DC && facing == 1)) {
                    ResetSecondaryCounter(2);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 2) {
                if (animationStage == 2 && animationFrame == 0) {
                    owner->field314 = -90.0f;
                    owner->SpawnBattleEffect(820, x, y, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = 12.0f;
                if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
                if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
                if (y > owner->field2E0) {
                    ResetSecondaryCounter(3);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 3) {
                if (animationStage == 3 && animationFrame == 0) {
                    owner->field314 = -180.0f;
                    owner->SpawnBattleEffect(820, x, y, facing, 1);
                }
                velocityX = -12.0f;
                velocityY = 0.0f;
                reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->field2E0);
                if ((x < owner->field2D8 && facing == 1) ||
                    (x > owner->field2DC && facing == -1)) {
                    ResetSecondaryCounter(4);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 4) {
                if (animationStage == 4 && animationFrame == 0) {
                    owner->field314 = 90.0f;
                    owner->SpawnBattleEffect(820, x, y, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = -12.0f;
                if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
                if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
                if (y < 0.0f) {
                    ResetSecondaryCounter(1);
                    velocityX = 8.0f;
                    velocityY = 0.0f;
                    y = 0.0f;
                    owner->field314 = 0.0f;
                    owner->SpawnBattleEffect(820, x, y, facing, 1);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) { ResetSecondaryCounter(4); return; }
            else {
                if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
                if (animationStage == 4 && animationFrame == 0) ResetSecondaryCounter(3);
            }
        }
        break;

    case 822:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            SetPolarVelocity(field0C8, 16.0f);
            reinterpret_cast<unsigned int&>(rotationZ) = reinterpret_cast<unsigned int&>(field0C8);
        }
        if (field0C8 == 0.0f) y = 0.0f;
        if (field0C8 == -90.0f) {
            if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
            if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
        }
        if (field0C8 == -180.0f) reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->field2E0);
        if (field0C8 == 90.0f) {
            if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
            if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
        }
        x = facing * velocityX + x;
        y += velocityY;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 823:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 0;
        }
        if (field0D8 > 5 || (owner->action == 706 && owner->animationStage == 3)) {
            ClearFrameInfo(); return;
        }
        else {
            if (animationStage == 1) {
                if (animationStage == 1 && animationFrame == 0) {
                    owner->field314 = 0.0f;
                    owner->SpawnBattleEffect(822, x, y, facing, 1);
                }
                velocityX = 16.0f;
                y = 0.0f;
                if ((x < owner->field2D8 && facing == -1) ||
                    (x > owner->field2DC && facing == 1)) {
                    ResetSecondaryCounter(2);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 2) {
                if (animationStage == 2 && animationFrame == 0) {
                    owner->field314 = -90.0f;
                    owner->SpawnBattleEffect(822, x, y, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = 16.0f;
                if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
                if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
                if (y > owner->field2E0) {
                    ResetSecondaryCounter(3);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 3) {
                if (animationStage == 3 && animationFrame == 0) {
                    owner->field314 = -180.0f;
                    owner->SpawnBattleEffect(822, x, y, facing, 1);
                }
                velocityX = -16.0f;
                velocityY = 0.0f;
                reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->field2E0);
                if ((x < owner->field2D8 && facing == 1) ||
                    (x > owner->field2DC && facing == -1)) {
                    ResetSecondaryCounter(4);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if (animationStage == 4) {
                if (animationStage == 4 && animationFrame == 0) {
                    owner->field314 = 90.0f;
                    owner->SpawnBattleEffect(822, x, y, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = -16.0f;
                if (facing == -1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2DC);
                if (facing == 1) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->field2D8);
                if (y < 0.0f) {
                    ResetSecondaryCounter(1);
                    velocityX = 8.0f;
                    velocityY = 0.0f;
                    y = 0.0f;
                    owner->field314 = 0.0f;
                    owner->SpawnBattleEffect(822, x, y, facing, 1);
                    ++field0D8;
                    field07C = 0;
                    field080 = 1;
                }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) { ResetSecondaryCounter(4); return; }
            else {
                if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
                if (animationStage == 4 && animationFrame == 0) ResetSecondaryCounter(3);
            }
        }
        break;

    case 824:
        if (owner->action == 301 || owner->action == 391) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 825:
        if (owner->action == 321) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 826:
        if (owner->action == 305) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 827:
        if (owner->action == 500 || owner->action == 501) {
            x = owner->x + owner->facing * 8;
            y = owner->y + 135.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        rotationZ += 15.0f;
        if (animationStage == 0 &&
            ((owner->action != 500 && owner->action != 501) ||
             (owner->action == 500 && owner->animationStage > 8) ||
             (owner->action == 501 && owner->animationStage > 8))) {
            ResetSecondaryCounter(1); return;
        }
        else {
            if (animationStage == 1) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 828:
        if (owner->animationStage < 20 &&
            (owner->action == 503 || owner->action == 504 || owner->action == 505)) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 829:
        if (owner->action > 49 && owner->action < 150) { ClearFrameInfo(); return; }
        else {
            if (owner->action > 502 && owner->action < 506 && owner->animationStage < 7)
                reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationY = 60.0f;
                field080 = 255;
                field07C = 0;
            }
            if (animationStage == 1) {
                scaleY += 0.25;
                if (scaleY > 1.0f) scaleY = 1.0f;
            }
            if (animationStage == 2) scaleX += 0.25f;
            if (animationStage == 3) {
                scaleX -= 0.25f;
                if (scaleX < 0.0f) scaleX = 0.0f;
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 1 && animationFrame == 0) scaleX = 0.05f;
        }
        break;

    case 830:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 0.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 20.0f;
            rotationY = facing * -50;
            field0D8 = 0;
            field0DA = 0;
            field080 = 99;
            field07C = 0;
        }
        rotationZ -= 5.0f;
        if (scaleX < 1.0f) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        else {
            scaleX = 1.0f;
            scaleY = 1.0f;
            if (animationStage < 2) { ResetSecondaryCounter(2); return; }
        }
        if (animationStage == 3) {
            if (color[0] > 30) color[0] -= 30;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 831:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 1;
            field07C = 0;
            velocityX = 30.0f;
        }
        x = facing * velocityX + x;
        scaleX += 0.2f;
        scaleY *= 0.95f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 832:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 1;
            field07C = 0;
            velocityY = 30.0f;
        }
        y += velocityY;
        scaleY += 0.2f;
        scaleX *= 0.95f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 833:
        if (owner->action > 49 && owner->action < 150) field0D8 = 0;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field080 = 255;
            field07C = 0;
            field0D8 = static_cast<YukariFighter*>(owner)->fieldF30 + 3;
            static_cast<YukariFighter*>(owner)->fieldF30 = 0;
        }
        if (animationStage < 6) {
            scaleX += 0.2f;
            if (scaleX > 1.5) scaleX = 1.5f;
        }
        if (field0D8 == 0) {
            if (scaleX > 0.15f) scaleX -= 0.15f;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(6);
        if (animationStage > 6 && animationFrame == 0 && field0D8 > 0) {
            --field0D8;
            owner->PlaySound(3);
            owner->field314 = RecordedRange(0, 359);
            owner->field318 = 10.0f;
            owner->field31C = RecordedRange(0, 30) - 15;
            owner->SpawnBattleEffect(806, x, y + 30.0f - RecordedRange(0, 60), facing, 1);
            ResetSecondaryCounter(3);
        }
        break;

    case 834:
        if (owner->action > 49 && owner->action < 150) field0D8 = 0;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = static_cast<YukariFighter*>(owner)->fieldF30 * 2 + 6;
            static_cast<YukariFighter*>(owner)->fieldF30 = 0;
        }
        if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 21 && animationFrame == 0 && field0D8 > 0)
                ResetSecondaryCounter(10);
            if (animationStage > 9 && animationFrame == 0 && field0D8 > 0) {
                --field0D8;
                owner->PlaySound(3);
                owner->field318 = 10.0f;
                owner->field314 = -RecordedRange(0, 30) - 75;
                owner->SpawnBattleEffect(835, x + 60.0f - RecordedRange(0, 120), y, facing, 1);
            }
        }
        break;

    case 835:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex835 = 0; rewardIndex835 < 3; ++rewardIndex835)
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
            if (animationStage < 2) {
                SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
                if (y + velocityY <= 0.0f) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    ResetSecondaryCounter(2);
                    return;
                }
            }
            if ((field07C == 1 || field07C == 2 || field07C == 4 || field07C == 6) && animationStage == 1) {
                ResetSecondaryCounter(2);
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
                    if (animationStage > 1) {
                        rotationZ += 15.0f;
                        scaleX *= 0.9f;
                        scaleY *= 0.9f;
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 836:
        if (owner->action > 49 && owner->action < 150) field0D8 = 0;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = static_cast<YukariFighter*>(owner)->fieldF30 + 3;
            static_cast<YukariFighter*>(owner)->fieldF30 = 0;
        }
        if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 21 && animationFrame == 0 && field0D8 > 0)
                ResetSecondaryCounter(10);
            if (animationStage > 9 && animationFrame == 0 && field0D8 > 0) {
                --field0D8;
                owner->PlaySound(3);
                owner->field318 = 10.0f;
                owner->field314 = -RecordedRange(0, 30) - 75;
                owner->SpawnBattleEffect(837, x + 60.0f - RecordedRange(0, 120), y, facing, 1);
            }
        }
        break;

    case 837:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int rewardIndex837 = 0; rewardIndex837 < 3; ++rewardIndex837)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(-90.0f, 10.0f);
            }
            if (animationStage == 0) {
                ResetSecondaryCounter(1);
                velocityX = 0.0f;
                velocityY = 0.0f;
                field080 = 1;
                field07C = 0;
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (animationStage == 1) {
                SetPolarVelocity(-90.0f, field0D8 * 0.1f);
                field0D8 += 10;
                owner->field314 = -90.0f;
                owner->field318 = 0.0f;
                owner->SpawnBattleEffect(807, x, y, facing, 1);
                if (field07C != 0) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    ResetSecondaryCounter(2);
                    return;
                }
            }
            if (animationStage == 2) {
                field0D8 -= 20;
                if (field0D8 < 0) field0D8 = 0;
                reinterpret_cast<unsigned int&>(owner->field314) = reinterpret_cast<unsigned int&>(field0D0);
                owner->field318 = field0D8;
                owner->SpawnBattleEffect(807, x, y, facing, 1);
                scaleX *= 0.95f;
                scaleY *= 0.95f;
            }
            if (x > 1800.0f || x < -520.0f || y > 1400.0f || y < -520.0f) {
                ClearFrameInfo(); return;
            }
            else if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 838:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 80.0f;
        }
        if (animationStage == 1) {
            scaleX += 0.2f;
            scaleY += 0.2f;
        }
        if (animationStage == 2) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 15) color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 839:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 80.0f;
        }
        if (animationStage == 1) {
            scaleX += 0.2f;
            scaleY += 0.2f;
        }
        if (animationStage == 2) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 15) color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 840:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 80.0f;
        }
        if (animationStage == 1) {
            scaleX += 0.2f;
            scaleY += 0.2f;
        }
        if (animationStage == 2) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 15) color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 841:
        if (owner->action == 309)
            x = owner->x + owner->facing * 155;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage == 0) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        if (animationStage == 1) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 15) color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 842:
        if (owner->action == 309)
            x = owner->x + owner->facing * 155;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 80.0f;
        }
        if (animationStage == 1) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        if (animationStage == 2) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 15) color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 843:
        if (owner->action == 309)
            x = owner->x + owner->facing * 155;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 80.0f;
        }
        if (animationStage == 1) {
            scaleX += 0.1f;
            scaleY += 0.1f;
        }
        if (animationStage == 2) {
            scaleX += 0.01f;
            scaleY += 0.01f;
            if (color[0] > 15) color[0] -= 15;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 844:
        if (owner->action == 303) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 900:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 20;
                field07C = 0;
                scaleX = 0.0f;
                scaleY = 2.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
            }
            if (animationStage == 2 && animationFrame == 0) {
                SetPolarVelocity(field0DA, 30.0f);
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1) {
                if (scaleX < 1.0f) scaleX += 0.25f;
                if (scaleY > 1.0f) scaleY -= 0.25f;
            }
            if (animationStage == 3) {
                rotationZ -= 30.0f;
                SetPolarVelocity(field0DA, 30.0f);
            }
            if (animationStage == 4) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                rotationZ -= 30.0f;
            }
            if (animationStage == 5) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                rotationZ -= 30.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(3);
                field07C = 0;
                field080 = 1;
                return;
            }
            else {
                if (animationStage == 5 && animationFrame == 0) {
                    if (field0DC < 3 - g_F1212_DifficultyAt006714D0) {
                        ResetSecondaryCounter(4);
                        ++field0DC;
                        return;
                    }
                    field0DC = 0;
                }
                if (animationStage == 5 && animationFrame == 0) {
                    owner->PlaySound(15);
                    field0DA = static_cast<short>(AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828 );
                    owner->field314 = field0DA;
                    owner->SpawnBattleEffect(903, x, y, facing, 1);
                }
            }
        }
        break;

    case 901:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        velocityX = 0.0f;
                        velocityY = 0.0f;
                        scaleX *= 0.85f;
                        reinterpret_cast<unsigned int&>(scaleY) = reinterpret_cast<unsigned int&>(scaleX);
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 902:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
            }
            if (field07C != 0 && animationStage == 1) { ResetSecondaryCounter(2); return; }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage > 1) {
                        if (color[0] > 20) color[0] -= 20;
                        else { ClearFrameInfo(); return; }
                    }
                    if (AdvanceNestedFrame() == field070) ClearFrameInfo();
                }
            }
        }
        break;

    case 903:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 7.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = -field0C8;
            }
            scaleY *= 0.95;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 904:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 20;
                field07C = 0;
                scaleX = 0.0f;
                scaleY = 2.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 0;
                field0DA = 45;
            }
            if (animationStage == 2 && animationFrame == 0) {
                SetPolarVelocity(field0DA, 30.0f);
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1) {
                if (scaleX < 1.0f) scaleX += 0.25f;
                if (scaleY > 1.0f) scaleY -= 0.25f;
            }
            if (animationStage == 3) {
                rotationZ -= 30.0f;
                SetPolarVelocity(field0DA, 30.0f);
            }
            if (animationStage == 4) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                rotationZ -= 30.0f;
            }
            if (animationStage == 5) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                rotationZ -= 30.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(3);
                field07C = 0;
                field080 = 1;
                return;
            }
            else {
                if (animationStage == 5 && animationFrame == 0) {
                    if (field0DC < 3 - g_F1212_DifficultyAt006714D0) {
                        ResetSecondaryCounter(4);
                        ++field0DC;
                        return;
                    }
                    field0DC = 0;
                }
                if (animationStage == 5 && animationFrame == 0) {
                    owner->PlaySound(15);
                    field0DA = static_cast<short>(AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828 + RecordedRange(0, 30) - 15.0f );
                    owner->field314 = field0DA;
                    owner->SpawnBattleEffect(913, x, y, facing, 1);
                }
            }
        }
        break;

    case 905:
        if (owner->action == 741 && owner->animationStage < 12) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            y = owner->y + 100.0f;
        }
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (owner->action != 741 || (owner->action == 741 && owner->animationStage > 11)) {
                if (color[0] > 10) color[0] -= 10;
                else { ClearFrameInfo(); return; }
            }
            rotationZ += 2.0f;
            if (scaleX < 1.0f) {
                scaleX += 0.1f;
                scaleY += 0.1f;
                if (scaleX > 1.0f) { scaleX = 1.0f; scaleY = 1.0f; }
            }
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(1);
                reinterpret_cast<unsigned int&>(owner->field314) = reinterpret_cast<unsigned int&>(rotationZ);
                owner->SpawnBattleEffect(909, x, y, facing, 1);
            }
        }
        break;

    case 906:
        if (owner->action == 741 && owner->animationStage < 12) {
            reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
            y = owner->y + 100.0f;
        }
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (owner->action != 741 || (owner->action == 741 && owner->animationStage > 11)) {
                if (color[0] > 10) color[0] -= 10;
                else { ClearFrameInfo(); return; }
            }
            rotationZ -= 2.0f;
            if (scaleX < 1.0f) {
                scaleX += 0.1f;
                scaleY += 0.1f;
                if (scaleX > 1.0f) { scaleX = 1.0f; scaleY = 1.0f; }
            }
            if (AdvanceNestedFrame() == field070) {
                ResetSecondaryCounter(1);
                reinterpret_cast<unsigned int&>(owner->field314) = reinterpret_cast<unsigned int&>(rotationZ);
                owner->SpawnBattleEffect(909, x, y, facing, 1);
            }
        }
        break;

    case 907:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                SetPolarVelocity(field0C8, 7.0f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1 && field07C != 0) { ResetSecondaryCounter(2); return; }
            else {
                if (animationStage == 2) { scaleX *= 0.85f; scaleY *= 0.85f; }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 908:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0DA = RecordedRange(0, 359);
                SetPolarVelocity(field0DA, 20.0f);
                field07C = 0;
                field0D8 = 0;
                field0DC = 0;
            }
            if (animationStage == 1 && animationFrame == 0) {
                if (RecordedRange(0, 100) < 50) SetPolarVelocity(field0DA + 90, 40.0f);
                else SetPolarVelocity(field0DA - 90, 40.0f);
                owner->PlaySound(16);
                owner->field314 = AngleAt00483300(owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / g_F1211_AngleDivAt00657828;
                for (int effectIndex908 = 0; effectIndex908 < g_F1212_DifficultyAt006714D0 * 2 + 3; ++effectIndex908) {
                    if (field0DC == 0) {
                        owner->SpawnBattleEffect(907, effectIndex908 * velocityX + x,
                            effectIndex908 * velocityY + y, facing, 1);
                        field0DC = 1;
                    }
                    if (field0DC == 1) {
                        owner->SpawnBattleEffect(910, effectIndex908 * velocityX + x,
                            effectIndex908 * velocityY + y, facing, 1);
                        field0DC = 0;
                    }
                }
            }
            if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                ClearFrameInfo(); return;
            }
            else {
                x = facing * velocityX + x;
                y += velocityY;
                if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
            }
        }
        break;

    case 909:
        if (owner->action == 741 && owner->animationStage < 12) {
            x = owner->x;
            y = owner->y + 100.0f;
        }
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = field0C8;
            }
            if (owner->action != 741 || (owner->action == 741 && owner->animationStage > 11)) {
                if (color[0] > 10) color[0] -= 10;
                else { ClearFrameInfo(); return; }
            }
            scaleX += 0.05f;
            scaleY += 0.05f;
            if (color[0] > 10) color[0] -= 10;
            else { ClearFrameInfo(); return; }
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
        }
        break;

    case 910:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                SetPolarVelocity(field0C8, 7.0f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1 && field07C != 0) { ResetSecondaryCounter(2); return; }
            else {
                if (animationStage == 2) { scaleX *= 0.85f; scaleY *= 0.85f; }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 911:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            rotationZ += 15.0f;
            if (animationStage == 0) {
                if (owner->action == 732 && owner->animationStage > 6) {
                    ResetSecondaryCounter(1);
                    velocityX = owner->facing * 8.0f;
                    velocityY = -20.0f;
                    field080 = 15;
                    return;
                }
                if (owner->action == 731 || (owner->action == 732 && owner->animationStage < 7)) {
                    x = owner->x + owner->facing * 8;
                    y = owner->y + 135.0f;
                }
                if ((owner->action != 731 && owner->action != 732) ||
                    (owner->action == 500 && owner->animationStage > 8) ||
                    (owner->action == 731 && owner->animationStage > 9)) {
                    ResetSecondaryCounter(2); return;
                }
            }
            if (animationStage == 1) {
                if (y + velocityY <= 0.0f) { y = 0.0f; velocityY = 0.0f; }
                if (x > 1680.0f || x < -400.0f || y < -500.0f || y > 1280.0f) {
                    ClearFrameInfo(); return;
                }
            }
            if (animationStage == 2) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) {
                ResetSecondaryCounter(1);
                field07C = 0;
            }
        }
        break;

    case 912:
        if (owner->action == 733) {
            x = owner->x + owner->facing * 8;
            y = owner->y + 135.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        rotationZ += 15.0f;
        if (animationStage == 0 && (owner->action != 733 || (owner->action == 733 && owner->animationStage > 8))) {
            ResetSecondaryCounter(1); return;
        }
        else {
            if (animationStage == 1) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 913:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 7.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = -field0C8;
            }
            scaleY *= 0.95;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 914:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 7.0f;
                scaleY = 2.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            scaleX += 0.05f;
            scaleY *= 0.95;
            if (AdvanceNestedFrame() == field070) {
                ClearFrameInfo();
                owner->PlaySound(23);
                if (g_F1212_DifficultyAt006714D0 == 0)
                    owner->SpawnBattleEffect(915, x, y, facing, 1);
                else owner->SpawnBattleEffect(916, x, y, facing, 1);
            }
        }
        break;

    case 915:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                owner->SetCameraShake(5.0f);
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 2.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field080 = 1;
                field07C = 0;
            }
            scaleX += 0.5f;
            scaleY *= 0.95;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 916:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                owner->SetCameraShake(5.0f);
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 2.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field080 = 1;
                field07C = 0;
            }
            scaleX += 0.5f;
            scaleY *= 0.95;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        }
        break;

    case 917:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 1;
            field0DC = 0;
            if (owner->opponent->y > 0.0f) ++field0DC;
            if (owner->opponent->y > 250.0f) ++field0DC;
            if (owner->opponent->y > 400.0f) ++field0DC;
            field0DE = RecordedRange(0, 5) - 1;
            if (field0DE == field0DC) {
                --field0DE;
                if (field0DE < 0) field0DE = 3;
            }
            field0E0 = RecordedRange(0, 5) - 1;
            if (field0E0 == field0DC) {
                --field0E0;
                if (field0E0 < 0) field0E0 = 3;
            }
            if (field0E0 == field0DE) {
                --field0E0;
                if (field0E0 < 0) field0E0 = 3;
            }
        }
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (owner->health < 3500) {
                ++field0D8;
                if (g_F1212_DifficultyAt006714D0 <= 1 && field0D8 > 140) {
                    owner->PlaySound(15);
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0DC * 150 + 50, field0DA, 1);
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0DE * 150 + 50, field0DA, 1);
                    field0D8 = 0;
                    field0DA = -field0DA;
                }
                if (g_F1212_DifficultyAt006714D0 == 2 && field0D8 > 120) {
                    owner->PlaySound(15);
                    field0DA = -field0DA;
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0DC * 150 + 50, field0DA, 1);
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0DE * 150 + 50, field0DA, 1);
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0E0 * 150 + 50, field0DA, 1);
                    field0D8 = 0;
                }
                if (g_F1212_DifficultyAt006714D0 == 3 && field0D8 > 90) {
                    owner->PlaySound(15);
                    field0DA = -field0DA;
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0DC * 150 + 50, field0DA, 1);
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0DE * 150 + 50, field0DA, 1);
                    owner->SpawnBattleEffect(914, (field0DA == -1) * 1280,
                        field0E0 * 150 + 50, field0DA, 1);
                    field0D8 = 0;
                }
                field0DC = 0;
                if (owner->opponent->y > 0.0f) ++field0DC;
                if (owner->opponent->y > 250.0f) ++field0DC;
                if (owner->opponent->y > 400.0f) ++field0DC;
                field0DE = RecordedRange(0, 5) - 1;
                if (field0DE == field0DC) {
                    --field0DE;
                    if (field0DE < 0) field0DE = 3;
                }
                field0E0 = RecordedRange(0, 5) - 1;
                if (field0E0 == field0DC) {
                    --field0E0;
                    if (field0E0 < 0) field0E0 = 3;
                }
                if (field0E0 == field0DE) {
                    --field0E0;
                    if (field0E0 < 0) field0E0 = 3;
                }
            }
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
        }
        break;

    case 918:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            facing = 1;
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
                field0DE = 0;
                field0E0 = 0;
            }
            --field0E0;
            SetPolarVelocity(static_cast<YukariFighter*>(owner)->fieldF12 + field0C8, static_cast<YukariFighter*>(owner)->fieldF14);
            x = static_cast<YukariFighter*>(owner)->fieldF18 + facing * velocityX;
            y = static_cast<YukariFighter*>(owner)->fieldF1A + velocityY;
            owner->SpawnBattleEffect(919, x, y, 1, 1);
            if (field0E0 <= 0) {
                owner->PlaySound(18);
                owner->field314 = -(static_cast<YukariFighter*>(owner)->fieldF12 + field0C8) * facing;
                owner->field318 = 5.0f;
                owner->SpawnBattleEffect(921, x, y, 1, 1);
                field0E0 = 4;
            }
            if (static_cast<YukariFighter*>(owner)->fieldF16 == 2) {
                owner->PlaySound(16);
                for (int effectIndex918 = 0; effectIndex918 < g_F1212_DifficultyAt006714D0 * 2 + 4; ++effectIndex918) {
                    owner->field314 = -(static_cast<YukariFighter*>(owner)->fieldF12 + field0C8) * facing;
                    owner->field318 = 4.0f;
                    owner->SpawnBattleEffect(922, x, y, 1, 1);
                }
            }
            if (static_cast<YukariFighter*>(owner)->fieldF16 == 3) {
                owner->PlaySound(18);
                owner->field314 = -(static_cast<YukariFighter*>(owner)->fieldF12 + field0C8) + 180.0f;
                owner->field318 = 5.0f;
                owner->SpawnBattleEffect(923, x, y, 1, 1);
            }
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
        }
        break;

    case 919:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.85f;
        scaleY *= 0.85f;
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 920:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            facing = 1;
            if (owner->field3B8 == 0) {
                static_cast<YukariFighter*>(owner)->fieldF18 = static_cast<short>(x);
                static_cast<YukariFighter*>(owner)->fieldF1A = static_cast<short>(y);
            }
            if (static_cast<YukariFighter*>(owner)->fieldF14 > 340) --static_cast<YukariFighter*>(owner)->fieldF14;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 60;
                field0DE = 0;
                field0E0 = 180;
            }
            --field0E0;
            --field0DC;
            ++field0DA;
            if (field0DC == 1) static_cast<YukariFighter*>(owner)->fieldF16 = 2;
            if (field0DC == 0) {
                --field0DC;
                field0DC = 260;
                static_cast<YukariFighter*>(owner)->fieldF16 = 0;
            }
            if (field0DA == 300) static_cast<YukariFighter*>(owner)->fieldF16 = 3;
            if (field0DA == 301) {
                field0DA = g_F1212_DifficultyAt006714D0 * 20 - 60;
                static_cast<YukariFighter*>(owner)->fieldF16 = 0;
            }
            if (field0DE > 0) {
                --field0DE;
                static_cast<YukariFighter*>(owner)->fieldF16 = 1;
                if (field0DE == 0) static_cast<YukariFighter*>(owner)->fieldF16 = 0;
            }
            velocityX = (owner->opponent->x - x) * 0.02f;
            if (velocityX < 0.25f && velocityX > -0.25f) velocityX = 0.0f;
            velocityY = (owner->opponent->y + 100.0f - y) * 0.02f;
            if (velocityY < 0.25f && velocityY > -0.25f) velocityY = 0.0f;
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(1);
        }
        break;

    case 921:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1 && field07C != 0) { ResetSecondaryCounter(2); return; }
            else {
                if (animationStage == 2) { scaleX *= 0.8f; scaleY *= 0.8f; }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 922:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 3.0f;
                scaleY = 3.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                field0DA = RecordedRange(0, 359);
                SetPolarVelocity(field0DA, field0D8 * 0.05f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / g_F1211_AngleDivAt00657828;
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1) {
                scaleX -= 0.1f;
                scaleY -= 0.1f;
                if (scaleX < 1.0f) { scaleX = 1.0f; scaleY = 1.0f; }
            }
            if (animationStage == 2 && field07C != 0) {
                ResetSecondaryCounter(3);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            else {
                if (animationStage == 3) { scaleX *= 0.8f; scaleY *= 0.8f; }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage == 2) {
                        ++field0D8;
                        x = facing * velocityX + x;
                        y -= velocityY;
                        SetPolarVelocity(field0DA, field0D8 * 0.05f);
                    }
                    if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 923:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                field080 = 1;
                field07C = 0;
                scaleX = 3.0f;
                scaleY = 3.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                field07C = 0;
                field080 = 1;
            }
            if (animationStage == 1) {
                scaleX -= 0.1f;
                scaleY -= 0.1f;
                if (scaleX < 1.0f) { scaleX = 1.0f; scaleY = 1.0f; }
                if (color[0] < 245) color[0] += 10;
                else color[0] = 255;
            }
            if (animationStage == 2 && field07C != 0) {
                ResetSecondaryCounter(3);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            else {
                if (animationStage == 3) { scaleX *= 0.8f; scaleY *= 0.8f; }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                    ClearFrameInfo(); return;
                }
                else {
                    if (animationStage == 2) {
                        ++field0D8;
                        SetPolarVelocity(field0C8, field0CC);
                        x = facing * velocityX + x;
                        y -= velocityY;
                    }
                    if (AdvanceNestedFrame() == field070) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 924:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            rotationZ += 15.0f;
            if (animationStage == 0) {
                if (owner->action == 732 && owner->animationStage > 6) {
                    ResetSecondaryCounter(1);
                    velocityX = owner->facing * 8.0f;
                    velocityY = -20.0f;
                    field080 = 15;
                    return;
                }
                if (owner->action == 731 || (owner->action == 732 && owner->animationStage < 7)) {
                    x = owner->x + owner->facing * 8;
                    y = owner->y + 135.0f;
                }
                if ((owner->action != 731 && owner->action != 732) ||
                    (owner->action == 500 && owner->animationStage > 8)) {
                    ResetSecondaryCounter(2); return;
                }
            }
            if (animationStage == 1) {
                if (y + velocityY <= 0.0f) { y = 0.0f; velocityY = 0.0f; }
                if (x > 1680.0f || x < -400.0f || y < -500.0f || y > 1280.0f) {
                    ClearFrameInfo(); return;
                }
            }
            if (animationStage == 2) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) {
                ResetSecondaryCounter(1);
                field07C = 0;
            }
        }
        break;

    case 925:
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            rotationZ += 15.0f;
            if (animationStage == 0) {
                if (owner->action == 732 && owner->animationStage > 6) {
                    ResetSecondaryCounter(1);
                    velocityX = owner->facing * 10.0f;
                    velocityY = -20.0f;
                    field080 = 15;
                    return;
                }
                if (owner->action == 731 || (owner->action == 732 && owner->animationStage < 7)) {
                    x = owner->x + owner->facing * 8;
                    y = owner->y + 135.0f;
                }
                if ((owner->action != 731 && owner->action != 732) ||
                    (owner->action == 500 && owner->animationStage > 8)) {
                    ResetSecondaryCounter(2); return;
                }
            }
            if (animationStage == 1) {
                if (y + velocityY <= 0.0f) { y = 0.0f; velocityY = 0.0f; }
                if (x > 1680.0f || x < -400.0f || y < -500.0f || y > 1280.0f) {
                    ClearFrameInfo(); return;
                }
            }
            if (animationStage == 2) {
                if (color[0] > 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == field070) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) {
                ResetSecondaryCounter(1);
                field07C = 0;
            }
        }
        break;

    case 988:
        if (owner->animationStage > 10) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
        break;

    case 989:
        if (owner->animationStage < 9) reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
        if (AdvanceNestedFrame() == field070) ClearFrameInfo();
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
                ++owner->fieldEFA;
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
        reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
        y = 2.0f;
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
            field0DA = 0;
        }
        if (owner->field3A0 <= 0) { ClearFrameInfo(); return; }
        else {
            scaleX = static_cast<float>(owner->field3A0) / field0D8 * 2;
            scaleY = static_cast<float>(owner->field3A0) / field0D8 * 2;
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == field070) ResetSecondaryCounter(9);
        }
        break;

    case 999:
        if (animationStage < 1) reinterpret_cast<unsigned int&>(y) = reinterpret_cast<unsigned int&>(owner->y);
        reinterpret_cast<unsigned int&>(x) = reinterpret_cast<unsigned int&>(owner->x);
        owner->fieldF0C = 1;
        if (owner->animationStage == 0 &&
            (((owner->action >= 70 && owner->action <= 88 && owner->action != 76)) ||
             owner->action == 181 || owner->action == 180 || owner->action == 145)) {
            ClearFrameInfo();
            owner->fieldF0C = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(60.0f, 130.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage == 0 && (owner->action == 96 || owner->action == 97) && owner->animationStage == 5) {
            ResetSecondaryCounter(1);
            rotationZ = 0.0f;
            return;
        }
        if (animationStage == 1 && (owner->action == 95 || owner->action == 94 || owner->action == 93 || owner->action == 796) && owner->animationStage == 3) {
            ResetSecondaryCounter(2);
            return;
        }
        if (animationStage == 0) rotationZ -= 35.0f;
        if (AdvanceNestedFrame() == field070) {
            ClearFrameInfo();
            owner->fieldF0C = 0;
        }
        break;

    default:
        AdvanceNestedFrame();
        break;
    }
}
