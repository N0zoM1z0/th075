#include "engine/MathFloatHelpers.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/GameSharedState.hpp"
// Natural-C++ reconstruction of SakuyaObject::Advance at 004CA6E0.
// Replays 42,511 code bytes plus 422 bytes of switch data with VC7.1 build 3077.
// Compiler profile and relocation bindings are in config/match-units.toml.
#include "characters/CharacterObject.hpp"
#include "characters/SakuyaFighter.hpp"


float __cdecl AngleAt00483300(float, float);

void SakuyaObject::Advance()
{
    if (owner->opponent->opponentFreezeSnapshot != 0) return;
    if (owner->opponentFreezeSnapshot != 0 && field08A == 0) return;
    if (hitstopFrames != 0) {
        --hitstopFrames;
        return;
    }
    switch (action) {
    case 800:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 5) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage < 4) {
                SetPolarVelocity(field0C8, field0D8 * 0.5f + field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
                static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
            }
            if ((field07C == 2 || field07C == 4) && animationStage == 0) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 6 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 6) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 4 && animationFrame == 0) ResetSecondaryCounter(0);
                if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
            }
        }
        break;

    case 801:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field07C = 0;
            scaleX = RecordedRange(0, 7) * 0.1f + 1.0f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = RecordedRange(0, 50) + 30 + (RecordedRange(0, 100) < 50) * 180;
            rotationZ = RecordedRange(0, 60);
            rotationY = (RecordedRange(0, 90) - 25) * facing;
            field0DA = RecordedRange(0, 2);
        }
        x = field0DA * 6.0f * facing + x;
        scaleX += 0.1f;
        scaleY += 0.02f;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 802:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            field07C = 0;
            scaleX = RecordedRange(0, 9) * 0.1f + 1.7f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = RecordedRange(0, 50) + 30 + (RecordedRange(0, 100) < 50) * 180;
            rotationZ = RecordedRange(0, 60);
            rotationY = (RecordedRange(0, 90) - 25) * facing;
        }
        scaleX += 0.02f;
        scaleX += 0.5f;
        scaleY += 0.02f;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 803:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 2 && animationFrame == 0 && field0D8 == 0) {
                field080 = 1;
                field07C = 0;
                field0DC = AngleAt00483300(owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                ++field0D8;
            }
            if (animationStage < 2) {
                rotationZ += 15.0f;
                SetPolarVelocity(field0C8, 4.5f);
            }
            if (animationStage > 1) {
                ++field0DA;
                SetPolarVelocity(field0DC, field0DA);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                scaleX += 0.5f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (x > 1600.0f || x < -400.0f || y > 1400.0f || y < -400.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(2);
                if (animationStage == 1 && animationFrame == 0) color[0] = 255;
            }
        }
        break;

    case 804:
        if (owner->action == 307 || owner->action == 390) {
            x = owner->x + facing * 60;
            y = owner->y;
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
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 805:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 69 && owner->action < 150 && animationStage < 1) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                velocityX = 0.0f;
                velocityY = 0.0f;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0DA = 0;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (field0D8 > 10) field0D8 = 10;
            if (animationStage == 0) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field314 = rotationZ;
                owner->field318 = field0D8;
                owner->SpawnBattleEffect(812, x, y, facing, 1);
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
                static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                if (y > owner->field2E0 && field0DA < 2 && velocityY < 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x < owner->cameraState.field04 && field0DA < 2 &&
                    ((facing == -1 && velocityX > 0.0f) ||
                     (facing == 1 && velocityX < 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x > owner->field2DC && field0DA < 2 &&
                    ((facing == -1 && velocityX < 0.0f) ||
                     (facing == 1 && velocityX > 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage == 0) {
                ResetSecondaryCounter(1);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 1 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 1) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;

    case 806:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 1) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0DA = 0;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (field0D8 > 10) field0D8 = 10;
            if (animationStage == 0) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field314 = rotationZ;
                owner->field318 = field0D8;
                owner->SpawnBattleEffect(812, x, y, facing, 1);
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
                static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                if (y > owner->field2E0 && field0DA < 1 && velocityY < 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (y < 0.0f && field0DA < 1 && velocityY > 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x < owner->cameraState.field04 && field0DA < 1 &&
                    ((facing == -1 && velocityX > 0.0f) ||
                     (facing == 1 && velocityX < 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 >= 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x > owner->field2DC && field0DA < 1 &&
                    ((facing == -1 && velocityX < 0.0f) ||
                     (facing == 1 && velocityX > 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 >= 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage == 0) {
                ResetSecondaryCounter(1);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 1 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 1) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;

    case 807:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (((owner->action > 69 && animationStage < 2) ||
                  (owner->action > 59 && animationStage == 2)) && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else if (owner->action >= 400 && owner->action <= 405 &&
                     owner->animationFrame == 0 && animationStage == 0) {
                color[0] = 255;
                ResetSecondaryCounter(1);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 128;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    field07C = 0;
                    field080 = 1;
                    field0D8 = 0;
                    field0DA = 0;
                }
                if (animationStage == 1) rotationZ += 40.0f;
                if (animationStage == 2) {
                    ++field0D8;
                    owner->field314 = rotationZ;
                    owner->field318 = field0D8;
                    owner->SpawnBattleEffect(812, x, y, facing, 1);
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                }
                if (animationStage == 0 || animationStage == 2) {
                    SetPolarVelocity(field0C8, field0D8 * 0.1f + field0CC);
                    rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                }
                x = facing * velocityX + x;
                y -= velocityY;
                if ((field07C == 2 || field07C == 4) && animationStage < 3) {
                    ResetSecondaryCounter(3);
                    return;
                }
                else {
                    if (animationStage == 3) {
                        velocityY += 0.5f;
                        rotationZ += 40.0f;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    if (animationStage == 2 && animationFrame == 0) {
                        field080 = 1;
                        field07C = 0;
                        field0C8 = AngleAt00483300(owner->opponent->y + 100.0f - y,
                            (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                        field0CC = 17.5f;
                        SetPolarVelocity(field0C8, field0CC);
                        rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    }
                }
            }
        }
        break;

    case 808:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 4) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
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
                field07C = 0;
                field080 = 1;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage > 0) {
                SetPolarVelocity(field0C8, field0D8 * 0.5f + field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage == 0 && animationFrame != 0) {
                // Later startup frames proceed to the same arena bounds check.
            }
            if (x > GeometryConstants::TwoThousand || x < g_SakuyaObjectMinXAt006595E0 || y > GeometryConstants::Thousand || y < GeometryConstants::NegativeHundredSixty) {
                ClearFrameInfo();
                return;
            }
            else {
                if (field080 == 0) {
                    if (color[0] > 10) color[0] -= 10;
                    else {
                        color[0] = 0;
                        ClearFrameInfo();
                        return;
                    }
                }
                if (animationStage == 1) scaleX += 0.3f;
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;

    case 809:
        if (owner->action != 500 && owner->action != 501 &&
            owner->action != 502 && owner->action != 503 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            if (((owner->action == 500 || owner->action == 501) && owner->animationStage < 10) ||
                ((owner->action == 502 || owner->action == 503) && owner->animationStage < 4)) {
                x = owner->x;
                y = owner->y + 132.0f;
            }
            else if (animationStage < 2) { ResetSecondaryCounter(2); return; }
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = field0C8 * 0.1f;
                scaleY = field0C8 * 0.1f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field01A = 1250;
                rotationX = 0.0f;
                rotationY = facing * field0CC;
                rotationZ = 0.0f;
                rotationX = field0D0;
            }
            rotationZ += 10.0f;
            if (animationStage == 2) color[0] -= 12;
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        }
        break;

    case 810:
        if (owner->action != 500 && owner->action != 501 &&
            owner->action != 502 && owner->action != 503 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            if (((owner->action == 500 || owner->action == 501) && owner->animationStage < 10) ||
                ((owner->action == 502 || owner->action == 503) && owner->animationStage < 4)) {
                x = owner->x;
                y = owner->y + 132.0f;
            }
            else if (animationStage < 2) { ResetSecondaryCounter(2); return; }
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = field0C8 * 0.1f;
                scaleY = field0C8 * 0.1f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field01A = 1250;
                rotationX = 0.0f;
                rotationY = facing * field0CC;
                rotationZ = 0.0f;
                rotationX = field0D0;
            }
            rotationZ += 10.0f;
            if (animationStage == 2) color[0] -= 12;
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        }
        break;

    case 811:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field080 = 0;
                field07C = 0;
            }
            if (animationStage > 1 && animationStage < 6) {
                ++field0DA;
                SetPolarVelocity(field0C8, field0DA);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                scaleX += 0.5f;
            }
            if (animationStage > 5 && animationStage < 10) {
                ++field0DA;
                SetPolarVelocity(field0DC, field0DA);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                scaleX += 0.5f;
            }
            if (animationStage < 2) {
                rotationZ += 15.0f;
                SetPolarVelocity(field0C8, 4.5f);
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(6);
                ++field0D8;
                if (field0D8 > 40) ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 1 && animationFrame == 0) color[0] = 255;
                if (animationStage == 6 && animationFrame == 0 && field0D8 < 20) {
                    ++field0D8;
                    ResetSecondaryCounter(2);
                    return;
                }
                else if (animationStage == 6 && animationFrame == 0) {
                    static_cast<SakuyaFighter*>(owner)->fieldF14 = 0;
                    scaleX = 1.0f;
                    field0D8 = 0;
                    field0DA = 0;
                    field080 = 1;
                    field07C = 0;
                    field0DC = AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                }
            }
        }
        break;

    case 812:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = field0CC * 0.2f + 0.25f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field07C = 0;
            field080 = 1;
            rotationZ = field0C8;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 813:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 814:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.3f;
            scaleY = 1.3f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->fieldF0C > 0) {
            if (color[0] < 245) color[0] += 10;
            else color[0] = 255;
        }
        if (owner->fieldF0C <= 0) {
            if (color[0] > 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        rotationZ += 0.25f;
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
        break;

    case 815:
        x = owner->x;
        y = owner->y + 100.0f;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0DA = owner->fieldF0C;
        }
        scaleX = static_cast<float>(owner->fieldF0C) / field0DA * 2;
        scaleY = static_cast<float>(owner->fieldF0C) / field0DA * 2;
        if (animationStage == 1 && owner->fieldF0C > 0) {
            if (color[0] < 245) color[0] += 10;
            else {
                color[0] = 255;
                ResetSecondaryCounter(2);
                return;
            }
        }
        if (animationStage == 2 && owner->fieldF0C <= 0) {
            ResetSecondaryCounter(3);
            return;
        }
        else if (animationStage == 3) { ClearFrameInfo(); return; }
        else {
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(3);
            if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        }
        break;

    case 816:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (static_cast<SakuyaFighter*>(owner)->fieldF10 > 0) {
            if (color[0] < 245) color[0] += 10;
            else color[0] = 255;
        }
        if (static_cast<SakuyaFighter*>(owner)->fieldF10 <= 0) {
            if (color[0] > 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
        break;

    case 817:
        facing = owner->facing;
        if (owner->action > 149 && owner->action < 154) {
            x = owner->x + facing * 30;
            y = owner->y + 94.0f;
        }
        if (owner->action > 153 && owner->action < 158) {
            x = owner->x + facing * 70;
            y = owner->y + 60.0f;
        }
        if (owner->action == 158) {
            x = owner->x + facing * 57;
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
            field0D8 = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
            owner->fieldF0A = 0;
        }
        break;

    case 818:
        x = owner->x;
        y = owner->y + 100.0f;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0DA = static_cast<SakuyaFighter*>(owner)->fieldF10;
        }
        scaleX = static_cast<float>(static_cast<SakuyaFighter*>(owner)->fieldF10) / field0DA * 2;
        scaleY = static_cast<float>(static_cast<SakuyaFighter*>(owner)->fieldF10) / field0DA * 2;
        if (animationStage == 1 && static_cast<SakuyaFighter*>(owner)->fieldF10 > 0) {
            if (color[0] < 245) color[0] += 10;
            else {
                color[0] = 255;
                ResetSecondaryCounter(2);
                return;
            }
        }
        if (animationStage == 2 && static_cast<SakuyaFighter*>(owner)->fieldF10 <= 0) {
            ResetSecondaryCounter(3);
            return;
        }
        else if (animationStage == 3) { ClearFrameInfo(); return; }
        else {
            if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(3);
            if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        }
        break;

    case 819:
        if (owner->action == 302) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 302) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 820:
        if (owner->action == 304) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 304) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 821:
        if (owner->action == 404 || owner->action == 405) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 404 && owner->action != 405) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 822:
        if (owner->action == 308) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 308) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 823:
        if (owner->action == 310) {
            x = owner->x;
            y = owner->y;
        }
        if (owner->action != 310) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
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
            rotationZ = RecordedRange(0, 90) - 45;
            field0D8 = RecordedRange(0, 10);
            field0DA = RecordedRange(0, 10);
            field0DC = RecordedRange(0, 10);
            field0DE = RecordedRange(0, 5);
            field0E0 = RecordedRange(0, 5);
            velocityX = RecordedRange(0, 6) - 3;
            velocityY = -RecordedRange(0, 2);
        }
        velocityY -= 0.2f;
        y += velocityY;
        x = facing * velocityX + x;
        if (field0D8 < 5) rotationZ = field0DE + rotationZ;
        if (field0D8 > 4) rotationZ -= field0DE;
        if (field0DA < 5) rotationX = field0E0 + rotationX;
        if (field0DA > 4) rotationX -= field0E0;
        if (field0DC < 5) rotationY = field0E0 + rotationY;
        if (field0DC > 4) rotationY -= field0E0;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 825:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 90) - 45;
            field0D8 = RecordedRange(0, 10);
            field0DA = RecordedRange(0, 10);
            field0DC = RecordedRange(0, 10);
            field0DE = RecordedRange(0, 5);
            field0E0 = RecordedRange(0, 5);
            velocityX = RecordedRange(0, 6) - 3;
            velocityY = -RecordedRange(0, 2);
        }
        velocityY -= 0.2f;
        y += velocityY;
        x = facing * velocityX + x;
        if (field0D8 < 5) rotationZ = field0DE + rotationZ;
        if (field0D8 > 4) rotationZ -= field0DE;
        if (field0DA < 5) rotationX = field0E0 + rotationX;
        if (field0DA > 4) rotationX -= field0E0;
        if (field0DC < 5) rotationY = field0E0 + rotationY;
        if (field0DC > 4) rotationY -= field0E0;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 826:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 90) - 45;
            field0D8 = RecordedRange(0, 10);
            field0DA = RecordedRange(0, 10);
            field0DC = RecordedRange(0, 10);
            field0DE = RecordedRange(0, 5);
            field0E0 = RecordedRange(0, 5);
            velocityX = RecordedRange(0, 6) - 3;
            velocityY = -RecordedRange(0, 2);
        }
        velocityY -= 0.2f;
        y += velocityY;
        x = facing * velocityX + x;
        if (field0D8 < 5) rotationZ = field0DE + rotationZ;
        if (field0D8 > 4) rotationZ -= field0DE;
        if (field0DA < 5) rotationX = field0E0 + rotationX;
        if (field0DA > 4) rotationX -= field0E0;
        if (field0DC < 5) rotationY = field0E0 + rotationY;
        if (field0DC > 4) rotationY -= field0E0;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 827:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 90) - 45;
            field0D8 = RecordedRange(0, 10);
            field0DA = RecordedRange(0, 10);
            field0DC = RecordedRange(0, 10);
            field0DE = RecordedRange(0, 5);
            field0E0 = RecordedRange(0, 5);
            velocityX = RecordedRange(0, 6) - 3;
            velocityY = -RecordedRange(0, 2);
        }
        velocityY -= 0.2f;
        y += velocityY;
        x = facing * velocityX + x;
        if (field0D8 < 5) rotationZ = field0DE + rotationZ;
        if (field0D8 > 4) rotationZ -= field0DE;
        if (field0DA < 5) rotationX = field0E0 + rotationX;
        if (field0DA > 4) rotationX -= field0E0;
        if (field0DC < 5) rotationY = field0E0 + rotationY;
        if (field0DC > 4) rotationY -= field0E0;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 828:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 90) - 45;
            field0D8 = RecordedRange(0, 10);
            field0DA = RecordedRange(0, 10);
            field0DC = RecordedRange(0, 10);
            field0DE = RecordedRange(0, 5);
            field0E0 = RecordedRange(0, 5);
            velocityX = RecordedRange(0, 6) - 3;
            velocityY = -RecordedRange(0, 2);
        }
        velocityY -= 0.2f;
        y += velocityY;
        x = facing * velocityX + x;
        if (field0D8 < 5) rotationZ = field0DE + rotationZ;
        if (field0D8 > 4) rotationZ -= field0DE;
        if (field0DA < 5) rotationX = field0E0 + rotationX;
        if (field0DA > 4) rotationX -= field0E0;
        if (field0DC < 5) rotationY = field0E0 + rotationY;
        if (field0DC > 4) rotationY -= field0E0;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 829:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 90) - 45;
            field0D8 = RecordedRange(0, 10);
            field0DA = RecordedRange(0, 10);
            field0DC = RecordedRange(0, 10);
            field0DE = RecordedRange(0, 5);
            field0E0 = RecordedRange(0, 5);
            velocityX = RecordedRange(0, 10) - 5;
            velocityY = -RecordedRange(0, 2);
        }
        velocityY -= 0.2f;
        y += velocityY;
        x = facing * velocityX + x;
        if (field0D8 < 5) rotationZ = field0DE + rotationZ;
        if (field0D8 > 4) rotationZ -= field0DE;
        if (field0DA < 5) rotationX = field0E0 + rotationX;
        if (field0DA > 4) rotationX -= field0E0;
        if (field0DC < 5) rotationY = field0E0 + rotationY;
        if (field0DC > 4) rotationY -= field0E0;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 830:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            scaleX = RecordedRange(0, 15) * 0.1f + 0.5f;
            scaleY = scaleX;
            velocityY = -RecordedRange(0, 2);
            velocityX = 0.0f;
        }
        velocityY += 0.4f;
        y += velocityY;
        x = facing * velocityX + x;
        color[0] -= 8;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 831:
        if (owner->action > 49 && owner->action < 150 && animationStage < 5 && owner->action != 702) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                field080 = 1;
                SetPolarVelocity(RecordedRange(0, 90) - 45, 20.0f);
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                if (field0D8 < 4) {
                    ++field0D8;
                    ResetSecondaryCounter(1);
                }
                else ClearFrameInfo();
            }
        }
        break;

    case 832:
        if (owner->action > 49 && owner->action < 150 && animationStage < 5 && owner->action != 703) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                field080 = 1;
                SetPolarVelocity(RecordedRange(0, 80) - 40, 30.0f);
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                if (field0D8 < 9) {
                    ++field0D8;
                    ResetSecondaryCounter(1);
                }
                else ClearFrameInfo();
            }
        }
        break;

    case 833:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 60;
            field0DC = 20 - RecordedRange(0, 40);
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage > 0) {
            ++field0DA;
            SetPolarVelocity(field0DC, field0DA);
            rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
            scaleX += 0.5f;
            scaleY *= 0.98f;
        }
        x = facing * velocityX + x;
        y -= velocityY;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 834:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 5) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                velocityX = 0.0f;
                velocityY = 0.0f;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0DC = 0;
                field0DA = 0;
                field0D8 = 0;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (field0D8 > 10) field0D8 = 10;
            if (animationStage < 5 && animationFrame == 0) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
                static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(835, x, y, facing, 0, 1);
                ++field0DC;
                ++field0DA;
                field0CC += 1.0f;
                if (field0CC > 15.0f) field0CC = 15.0f;
                if (field0DA > 5 && field0DC > 0) {
                    field0DA = 0;
                    field0C8 = RecordedRange(0, 180) - 90;
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage < 5) ResetSecondaryCounter(5);
            if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 5 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 5) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
            }
        }
        break;

    case 835:
        if (animationStage == 0 && animationFrame == 0) {
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        color[0] -= 12;
        color[1] -= 12;
        color[2] -= 12;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 836:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 6) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
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
                field07C = 0;
                field080 = 1;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage < 6) {
                SetPolarVelocity(field0C8, field0D8 * 0.5f + field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                if (animationStage > 0) {
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(835, x, y, facing, 0, 1);
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage < 6) {
                ResetSecondaryCounter(7);
                velocityX = -velocityX * 0.25;
                velocityY = -14.0f;
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 7) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 1 && animationFrame == 0) field08A = 0;
                if (animationStage == 2 && animationFrame == 0) {
                    field07C = 0;
                    field080 = 1;
                }
                if (animationStage == 6 && animationFrame == 0) ResetSecondaryCounter(2);
                if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
            }
        }
        break;

    case 837:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (owner->action > 49 && owner->action < 150 && animationStage < 5) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
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
                field07C = 0;
                field080 = 1;
                field0DA = 0;
                field0D8 = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage < 5) {
                SetPolarVelocity(field0C8, field0D8 * 0.5f + field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                if (y > owner->field2E0 && field0DA < 2 && velocityY < 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (y < 0.0f && field0DA < 2 && velocityY > 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x < owner->cameraState.field04 && field0DA < 2 &&
                    ((facing == -1 && velocityX > 0.0f) ||
                     (facing == 1 && velocityX < 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x > owner->field2DC && field0DA < 2 &&
                    ((facing == -1 && velocityX < 0.0f) ||
                     (facing == 1 && velocityX > 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (animationStage > 0) {
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(835, x, y, facing, 0, 1);
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage == 0) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 7 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 7) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 1 && animationFrame == 0) field08A = 0;
                if (animationStage == 2 && animationFrame == 0) {
                    field07C = 0;
                    field080 = 1;
                }
                if (animationStage == 6 && animationFrame == 0) ResetSecondaryCounter(2);
                if (animationStage == 8 && animationFrame == 0) ResetSecondaryCounter(7);
            }
        }
        break;

    case 838:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (((owner->action > 69 && animationStage < 2) ||
                  (owner->action > 59 && animationStage == 2)) && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 128;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0D8 = 0;
                field0DA = 0;
            }
            if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage != 2 && animationStage != 4) {
                    SetPolarVelocity(field0C8, field0CC);
                    rotationZ = -field0C8;
                }
                if (animationStage == 2) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                }
                x = facing * velocityX + x;
                y -= velocityY;
                if (animationStage == 3) {
                    owner->field314 = rotationZ;
                    owner->field318 = field0D8;
                    owner->SpawnBattleEffect(812, x, y, facing, 0);
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                }
                if ((field07C == 2 || field07C == 4 || field07C == 6) && animationStage < 4) {
                    ResetSecondaryCounter(4);
                    velocityX = -RecordedRange(0, 5) + 7;
                    velocityY = -RecordedRange(0, 7) + 7;
                    return;
                }
                else {
                    if (animationStage == 4) {
                        velocityY += 0.5f;
                        rotationZ += 40.0f;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                }
            }
        }
        break;

    case 839:
        if (field07C == 5) { ClearFrameInfo(); return; }
        else if (((owner->action > 69 && animationStage < 2) ||
                  (owner->action > 59 && animationStage == 2)) && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 128;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0D8 = 0;
                field0DA = 0;
            }
            if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage != 2 && animationStage != 4) {
                    SetPolarVelocity(field0C8, field0CC);
                    rotationZ = -field0C8;
                }
                if (animationStage == 2) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                }
                x = facing * velocityX + x;
                y -= velocityY;
                if (animationStage == 3) {
                    owner->field314 = rotationZ;
                    owner->field318 = field0D8;
                    owner->SpawnBattleEffect(812, x, y, facing, 0);
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                }
                if ((field07C == 2 || field07C == 4 || field07C == 6) && animationStage < 4) {
                    ResetSecondaryCounter(4);
                    velocityX = -RecordedRange(0, 5) + 7;
                    velocityY = -RecordedRange(0, 7) + 7;
                    return;
                }
                else {
                    if (animationStage == 4) {
                        velocityY += 0.5f;
                        rotationZ += 40.0f;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    if (animationStage == 2 && animationFrame == 0) facing = -facing;
                }
            }
        }
        break;

    case 901:
        if (owner->spellTimer == 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage < 5) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
            }
            if (field07C == 6) field080 = 1;
            if ((field07C == 2 || field07C == 4) && animationStage < 5) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 6 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 6) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
            }
        }
        break;

    case 903:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 2 && animationFrame == 0 && field0D8 == 0) {
                field080 = 1;
                field07C = 0;
                field0DC = AngleAt00483300(owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                ++field0D8;
            }
            if (animationStage < 2) {
                rotationZ += 15.0f;
                SetPolarVelocity(field0C8, 4.5f);
            }
            if (animationStage > 1) {
                ++field0DA;
                SetPolarVelocity(field0DC, field0DA);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                scaleX += 0.5f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if (x > 1600.0f || x < -400.0f || y > 1400.0f || y < -400.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(2);
                if (animationStage == 1 && animationFrame == 0) color[0] = 255;
            }
        }
        break;

    case 904:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0CC = 15.0f;
                ResetTransform(0.0f, 0.0f, 0.0f);
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0DA = 0;
            }
            if (field07C != 0) color[0] = 128;
            else color[0] = 255;
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (field0D8 > 5) field0D8 = 5;
            if (animationStage == 1) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                if (field07C == 0) {
                    owner->field314 = rotationZ;
                    owner->field318 = field0D8;
                    owner->SpawnBattleEffect(812, x, y, facing, 1);
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                }
                if (y > owner->field2E0 && field0DA < 1 && velocityY < 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                    field0CC = 4.0f;
                }
                if (y < 0.0f && field0DA < 1 && velocityY > 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                    field0CC = 4.0f;
                }
                if (x < owner->cameraState.field04 && field0DA < 1 &&
                    ((facing == -1 && velocityX > 0.0f) ||
                     (facing == 1 && velocityX < 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                    field0CC = 4.0f;
                }
                if (x > owner->field2DC && field0DA < 1 &&
                    ((facing == -1 && velocityX < 0.0f) ||
                     (facing == 1 && velocityX > 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                    field0CC = 4.0f;
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage == 1) {
                ResetSecondaryCounter(2);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 2 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 2) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;

    case 905:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field07C = 0;
                field080 = 1;
                field0DA = 0;
            }
            if (field07C != 0) color[0] = 128;
            else color[0] = 255;
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (field0D8 > 5) field0D8 = 5;
            if (animationStage == 1) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                if (field07C == 0) {
                    owner->field314 = rotationZ;
                    owner->field318 = field0D8;
                    owner->SpawnBattleEffect(812, x, y, facing, 1);
                    owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    owner->field2F0 = 0;
                    owner->field2F6 = 0;
                    owner->field2F8 = 0;
                    owner->field2FA = 0;
                    owner->field2FC = 1.0f;
                    owner->field300 = 1.0f;
                    owner->field2F1 = 255;
                    owner->field2F2 = 255;
                    owner->field2F3 = 255;
                    owner->field2F4 = 255;
                    owner->field308 = 0.0f;
                    owner->field30C = 0.0f;
                    static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                }
                if (y > owner->field2E0 && field0DA < 2 && velocityY < 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (y < 0.0f && field0DA < 2 && velocityY > 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x < owner->cameraState.field04 && field0DA < 2 &&
                    ((facing == -1 && velocityX > 0.0f) ||
                     (facing == 1 && velocityX < 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x > owner->field2DC && field0DA < 2 &&
                    ((facing == -1 && velocityX < 0.0f) ||
                     (facing == 1 && velocityX > 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
            }
            if ((field07C == 2 || field07C == 4) && animationStage == 1) {
                ResetSecondaryCounter(2);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 2 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 2) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;

    case 906:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field08A = 0;
                field07C = 0;
                field080 = 1;
                field0DC = 5;
                field0DA = RecordedRange(0, 30) - 15;
                field0D8 = RecordedRange(0, 50);
                SetPolarVelocity(field0DA, field0DC * 0.01f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            SetPolarVelocity(field0DA, field0DC * 0.01f);
            field0DC += 5 + field0D8;
            x = facing * velocityX + x;
            y -= velocityY;
            if (field080 == 0 && animationStage < 5) { ResetSecondaryCounter(6); return; }
            else if (x > 1320.0f || x < -40.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 6) {
                    if (color[0] > 20) color[0] -= 20;
                    else { ClearFrameInfo(); return; }
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
            }
        }
        break;

    case 907:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
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
                field0D8 = RecordedRange(0, 50);
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            velocityX = field0D8 * 0.01 + 0.05f + velocityX;
            x = facing * velocityX + x;
            y -= velocityY;
            if (field080 == 0 && animationStage < 5) { ResetSecondaryCounter(6); return; }
            else if (x > 1320.0f || x < -40.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 6) {
                    if (color[0] > 20) color[0] -= 20;
                    else { ClearFrameInfo(); return; }
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
            }
        }
        break;

    case 908:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
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
                field0D8 = RecordedRange(0, 50);
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            velocityX = field0D8 * 0.01 + 0.05f + velocityX;
            x = facing * velocityX + x;
            y -= velocityY;
            if (field080 == 0 && animationStage < 5) { ResetSecondaryCounter(6); return; }
            else if (x > 1320.0f || x < -40.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 6) {
                    if (color[0] > 20) color[0] -= 20;
                    else { ClearFrameInfo(); return; }
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
            }
        }
        break;

    case 909:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
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
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage < 5) {
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
                static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
            }
            if ((field07C == 2 || field07C == 4) && animationStage < 5) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 6 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 6) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
            }
        }
        break;

    case 910:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
            if (animationStage == 0 && animationFrame == 0) field0D8 = 0;
            if (animationStage == 1 && animationFrame == 0) {
                owner->field314 = field0C8;
                owner->field318 = 10.0f;
                owner->SpawnBattleEffect(909, x, y, facing, 1);
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                if (field0D8 < g_OptionsModeAt006714D0 * 2 + 1) {
                    ResetSecondaryCounter(1);
                    ++field0D8;
                    return;
                }
                else ClearFrameInfo();
            }
        }
        break;

    case 911:
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
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
                field0DA = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            ++field0D8;
            if (animationStage < 5) {
                if (y > owner->field2E0 && field0DA < g_OptionsModeAt006714D0 && velocityY < 0.0f) {
                    owner->PlaySound(11);
                    field0C8 = -field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x < owner->cameraState.field04 && field0DA < g_OptionsModeAt006714D0 &&
                    ((facing == -1 && velocityX > 0.0f) ||
                     (facing == 1 && velocityX < 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                if (x > owner->field2DC && field0DA < g_OptionsModeAt006714D0 &&
                    ((facing == -1 && velocityX < 0.0f) ||
                     (facing == 1 && velocityX > 0.0f))) {
                    owner->PlaySound(11);
                    if (field0C8 > 0.0f) field0C8 = 180.0f - field0C8;
                    if (field0C8 < 0.0f) field0C8 = -180.0f - field0C8;
                    ++field0DA;
                    field07C = 0;
                    field080 = 1;
                }
                SetPolarVelocity(field0C8, field0CC);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field310 = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                owner->field2F0 = 0;
                owner->field2F6 = 0;
                owner->field2F8 = 0;
                owner->field2FA = 0;
                owner->field2FC = 1.0f;
                owner->field300 = 1.0f;
                owner->field2F1 = 255;
                owner->field2F2 = 255;
                owner->field2F3 = 255;
                owner->field2F4 = 255;
                owner->field308 = 0.0f;
                owner->field30C = 0.0f;
                static_cast<SakuyaFighter*>(owner)->SpawnTrackedEffect(813, x, y, facing, 0, 1);
                owner->field314 = rotationZ;
                owner->field318 = field0CC;
                owner->SpawnBattleEffect(812, x, y, facing, 1);
            }
            if ((field07C == 2 || field07C == 4 || field07C == 6) && animationStage < 5) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (x > 1400.0f || x < -160.0f || y > 1000.0f || y < -160.0f) { ClearFrameInfo(); return; }
            else {
                if (animationStage == 6 && animationFrame == 0) {
                    velocityX = -velocityX * 0.25;
                    velocityY = -14.0f;
                }
                if (animationStage == 6) {
                    velocityY += 0.5f;
                    rotationZ += 40.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
            }
        }
        break;

    case 990:
        if (static_cast<SakuyaFighter*>(owner)->fieldF16 == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = owner->y + 100.0f;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            rotationZ += 1.0f;
            if (animationStage == 0) {
                if (color[0] < 180) {
                    color[0] += 25;
                }
                else {
                    color[0] = 180;
                }
                if (static_cast<SakuyaFighter*>(owner)->fieldF16 >= 120) {
                    ResetSecondaryCounter(1);
                    color[0] = 180;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 30) {
                    color[0] -= 30;
                }
                else {
                    color[0] = 0;
                }
                if (color[0] == 0) {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                return;
            }
        }
        break;

    case 991:
        if (static_cast<SakuyaFighter*>(owner)->fieldF16 == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = owner->y + 100.0f;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            scaleX = static_cast<SakuyaFighter*>(owner)->fieldF16 / 60.0f;
            scaleY = scaleX;
            if (animationStage == 0) {
                if (color[0] < 230) {
                    color[0] += 25;
                }
                else {
                    color[0] = 255;
                }
                if (static_cast<SakuyaFighter*>(owner)->fieldF16 >= 120) {
                    ResetSecondaryCounter(1);
                    color[0] = 255;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 10) {
                    color[0] -= 10;
                }
                else {
                    color[0] = 0;
                }
                if (color[0] == 0) {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                return;
            }
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
            field0D8 = AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f;
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ClearFrameInfo();
                if (owner->opponent->bombCount < 2) {
                    ++owner->opponent->bombCount;
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
        if (AdvanceNestedFrame() == animationStageCount) {
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
            field0D8 = AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f;
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
                    if (owner->opponent->spellDeclarationExpired == 0) {
                        if (owner->opponent->spellPower < 998.9) {
                            owner->opponent->spellPower += 0.5f;
                        }
                        else {
                            owner->opponent->spellPower = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 997:
        x = owner->x;
        y = owner->y * 0.0f + 20.0f;
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
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            rotationX = -80.0f;
            field0D8 = owner->spellTimer;
        }
        if (owner->spellTimer <= 0) { ClearFrameInfo(); return; }
        else {
            scaleX = static_cast<float>(owner->spellTimer) / field0D8 * 2;
            scaleY = static_cast<float>(owner->spellTimer) / field0D8 * 2;
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(40);
            if (animationStage == 40 && animationFrame == 0) color[0] = 255;
        }
        break;

    default:
        AdvanceNestedFrame();
        break;
    }
}
