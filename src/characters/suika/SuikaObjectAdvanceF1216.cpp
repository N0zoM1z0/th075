#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/MathFloatHelpers.hpp"
#include "engine/GameSharedState.hpp"
// Natural-C++ reconstruction of SuikaObject::Advance at 005C9CC0.
// Replays 43,501 code bytes plus 470 bytes of switch data with VC7.1 build 3077.
// Compiler profile and relocation bindings are in config/match-units.toml.
#include "characters/CharacterObject.hpp"
#include "characters/suika/SuikaFighter.hpp"
#include "battle/EffectServices.hpp"


float __cdecl AngleAt00483300(float, float);
float __cdecl AbsFloatAt00412D90(float);

void SuikaObject::Advance()
{
    if (owner->opponent->opponentFreezeSnapshot != 0) return;
    if (owner->opponentFreezeSnapshot != 0 && field08A == 0) return;
    if (hitstopFrames != 0) {
        --hitstopFrames;
        return;
    }
    switch (action) {
    case 800:
        if (owner->action != 301 && animationStage < 18)
            ResetSecondaryCounter(18);
        if (owner->action == 301) {
            x = owner->x + facing * 128;
            y = owner->y + 66.0f;
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.2f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            remainingHits = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 801:
        if (owner->action > 49 && owner->action < 150 && animationStage < 9) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex801 = 0; cancelIndex801 < 6; cancelIndex801++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(field0C8, field0CC);
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (animationStage < 5) {
                scaleX += 0.1f;
                scaleY += 0.1f;
                if (scaleX >= 0.5f) {
                    ResetSecondaryCounter(animationStage + 4);
                    scaleX = 0.5f;
                    scaleY = 0.5f;
                }
            }
            if (remainingHits == 0 && animationStage < 9) {
                ResetSecondaryCounter(9);
                velocityX = -2.0f - RecordedRange(0, 4);
                velocityY = RecordedRange(0, 6) + 8.0f;
            }
            if (animationStage < 9) {
                if (velocityY > 3.0f) field0D8 = 1;
                if (velocityY < -3.0f) field0D8 = -1;
                if (field0D8 == 1) velocityY -= 0.2f;
                if (field0D8 == -1) velocityY += 0.2f;
            }
            if (animationStage > 8 && animationStage < 19) {
                velocityY -= 0.8f;
                if (y + velocityY <= 0.0f) {
                    ResetSecondaryCounter(19);
                    velocityY = 0.0f;
                    velocityX = 0.0f;
                    return;
                }
            }
            if (animationStage == 29) {
                if (color[0] >= 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            if (x > 1480.0f || x < -200.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(1);
                if (animationStage == 9 && animationFrame == 0) ResetSecondaryCounter(5);
                if (animationStage == 19 && animationFrame == 0) ResetSecondaryCounter(17);
            }
        }
        break;

    case 802:
        if (owner->action > 49 && owner->action < 150 && animationStage < 16) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex802 = 0; cancelIndex802 < 6; cancelIndex802++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(field0C8, field0CC);
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (animationStage < 6) {
                scaleX += 0.1f;
                scaleY += 0.1f;
                if (scaleX >= 0.5f) {
                    scaleX = 0.5f;
                    scaleY = 0.5f;
                }
                velocityY -= 0.6f;
                if (y + velocityY <= 0.0f) {
                    ResetSecondaryCounter(6);
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                }
            }
            if (remainingHits == 0 && animationStage < 16) {
                ResetSecondaryCounter(16);
                velocityX = -2.0f - RecordedRange(0, 4);
                velocityY = RecordedRange(0, 6) + 8.0f;
            }
            if (animationStage > 15 && animationStage < 26) {
                velocityY -= 0.8f;
                if (y + velocityY <= 0.0f) {
                    ResetSecondaryCounter(26);
                    velocityY = 0.0f;
                    velocityX = 0.0f;
                    return;
                }
            }
            if (animationStage == 36) {
                if (color[0] >= 20) color[0] -= 20;
                else { ClearFrameInfo(); return; }
            }
            if (x > 1480.0f || x < -200.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 6 && animationFrame == 0) ResetSecondaryCounter(4);
                if (animationStage == 8 && animationFrame == 0)
                    velocityX = RecordedRange(0, 3) + 5;
                if (animationStage == 16 && animationFrame == 0) ResetSecondaryCounter(8);
                if (animationStage == 26 && animationFrame == 0) ResetSecondaryCounter(24);
            }
        }
        break;

    case 803:
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex803 = 0; cancelIndex803 < 15; cancelIndex803++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 10.0f;
                velocityY = 8.0f;
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (velocityX > 2.5f) velocityX -= 1.0f;
            else velocityX = 2.5f;
            velocityY -= 0.6f;
            owner->SpawnBattleEffect(804, x, y, facing, 1);
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                owner->PlaySound(18);
                owner->SetCameraShake(5.0f);
                for (int burstIndex803 = 0; burstIndex803 < 18; burstIndex803++) {
                    owner->field314 = burstIndex803 * 20;
                    owner->field318 = 17.0f;
                    owner->SpawnBattleEffect(805, x, y, facing, 0);
                }
            }
        }
        break;

    case 804:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 0.6f;
            scaleY = 0.6f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            SetPolarVelocity(RecordedRange(0, 359), RecordedRange(0, 5) + 5);
        }
        x = facing * velocityX + x;
        y += velocityY;
        scaleX *= 0.85f;
        scaleY *= 0.85f;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 805:
        if (owner->action > 49 && owner->action < 150 && animationStage < 1) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex805 = 0; cancelIndex805 < 2; cancelIndex805++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 2;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 0 && animationFrame == 1) {
                field0D8 = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            SetPolarVelocity(field0C8, field0CC);
            if (field0CC > 2.0f) field0CC -= 1.0f;
            x = facing * velocityX + x;
            y += velocityY;
            if (animationStage == 0) {
                owner->SpawnBattleEffect(806, x, y, facing, 1);
                scaleX = RecordedRange(0, 4) * 0.1f + 0.8f;
                scaleY = scaleX;
                if (remainingHits == 0) ResetSecondaryCounter(1);
            }
            if (animationStage == 1) {
                scaleX *= 0.85f;
                scaleY *= 0.85f;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 806:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 0.75f;
            scaleY = 0.75f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX *= 0.85f;
        scaleY *= 0.85f;
        if (color[0] > 15) {
            color[0] -= 15;
            color[3] -= 15;
            color[2] -= 15;
        }
        else { ClearFrameInfo(); return; }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 807:
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex807 = 0; cancelIndex807 < 15; cancelIndex807++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (x < owner->cameraState.viewLeft && field0D8 == 0 &&
                ((facing == -1 && velocityX > 0.0f) ||
                 (facing == 1 && velocityX < 0.0f))) {
                facing = -facing;
                ++field0D8;
            }
            if (x > owner->viewRight && field0D8 == 0 &&
                ((facing == -1 && velocityX < 0.0f) ||
                 (facing == 1 && velocityX > 0.0f))) {
                facing = -facing;
                ++field0D8;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 20.0f;
                velocityY = 10.0f;
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (velocityX > 10.0f) velocityX -= 1.0f;
            else velocityX = 10.0f;
            velocityY -= 0.6f;
            owner->SpawnBattleEffect(804, x, y, facing, 1);
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                owner->PlaySound(18);
                owner->SetCameraShake(5.0f);
                for (int burstIndex807 = 0; burstIndex807 < 18; burstIndex807++) {
                    owner->field314 = burstIndex807 * 20;
                    owner->field318 = 17.0f;
                    owner->SpawnBattleEffect(805, x, y, facing, 1);
                }
            }
        }
        break;

    case 808:
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex808 = 0; cancelIndex808 < 15; cancelIndex808++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 2.5f;
                velocityY = 15.0f;
            }
            x = facing * velocityX + x;
            y += velocityY;
            velocityY -= 0.45f;
            owner->SpawnBattleEffect(804, x, y, facing, 1);
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                owner->PlaySound(18);
                owner->SetCameraShake(5.0f);
                for (int burstIndex808 = 0; burstIndex808 < 18; burstIndex808++) {
                    owner->field314 = burstIndex808 * 20;
                    owner->field318 = 17.0f;
                    owner->SpawnBattleEffect(805, x, y, facing, 1);
                }
            }
        }
        break;

    case 809:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex809 = 0; cancelIndex809 < 10; cancelIndex809++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 810:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = RecordedRange(0, 120) - 60;
            rotationY = RecordedRange(0, 120) - 60;
            rotationZ = RecordedRange(0, 120) - 60;
            field0D8 = 0;
        }
        scaleX = (0.2f - field0D8 * 0.05f * (field0D8 < 5)) + 0.005f + scaleX;
        scaleY = (0.2f - field0D8 * 0.05f * (field0D8 < 5)) + 0.005f + scaleY;
        ++field0D8;
        if (animationStage > 1) {
            if (color[0] > 20) {
                color[0] -= 20;
                color[2] -= 20;
                color[3] -= 20;
            }
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 811:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field0D8 = 0;
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            SetPolarVelocity(field0C8, 10.0f);
        }
        if (animationStage == 1 && animationFrame == 0) {
            field0DA = RecordedRange(0, 60) - 30;
            field0DC = RecordedRange(0, 60) - 30;
            owner->SpawnBattleEffect(809, field0DA + x, field0DC + y, facing, 1);
            owner->field314 = field0C8;
            owner->SpawnBattleEffect(810, field0DA + x, field0DC + y, facing, 1);
        }
        x = facing * velocityX + x;
        y -= velocityY;
        if (x > 1480.0f || x < -200.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (AdvanceNestedFrame() == animationStageCount) {
                if (field0D8 < 6) {
                    ResetSecondaryCounter(1);
                    ++field0D8;
                }
                else ClearFrameInfo();
            }
        }
        break;

    case 812:
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex812 = 0; cancelIndex812 < 4; cancelIndex812++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.5f;
                scaleY = 0.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                remainingHits = 1;
                collisionResult = 0;
            }
            SetPolarVelocity(field0C8, field0CC);
            if (field0CC > 2.0f) field0CC -= 1.0f;
            if (animationStage < 2 && field0CC == FloatConstants::Two)
                ResetSecondaryCounter(2);
            x = facing * velocityX + x;
            y += velocityY;
            --field0DC;
            if (field0DC <= 0) {
                owner->SpawnBattleEffect(813, x - 10.0f + RecordedRange(0, 20),
                    y - 10.0f + RecordedRange(0, 20), facing, 1);
                field0DC = 4;
            }
            if (animationFrame == 0) {
                field0DA = RecordedRange(0, 20);
                scaleX = field0DA * 0.01f + 0.5f;
                scaleY = field0DA * 0.01f + 0.5f;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
            if (animationStage == 3 && animationFrame == 0 && field0D8 < 25) {
                ResetSecondaryCounter(2);
                ++field0D8;
            }
        }
        break;

    case 813:
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
        velocityY -= 0.15f;
        x = facing * velocityX + x;
        y += velocityY;
        if (color[0] > 13) color[0] -= 13;
        else color[0] = 0;
        scaleX *= 0.94f;
        scaleY *= 0.94f;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 814:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 815:
        if (animationStage == 0 && animationFrame == 0 && field0D8 != 1) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        scaleX += 0.08f;
        scaleY += 0.08f;
        color[0] -= 7;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 816:
        if (animationStage == 0 && animationFrame == 0 && field0D8 != 1) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(25, 75) * 0.01f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = RecordedRange(0, 255);
            color[2] = RecordedRange(0, 255);
            color[3] = RecordedRange(0, 255);
        }
        x -= 0.1f;
        rotationZ += 5.0f;
        color[0] -= 7;
        scaleX -= 0.01f;
        scaleY -= 0.01f;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 817:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(75, 150) * 0.01f;
            scaleY = scaleX;
            rotationZ = RecordedRange(0, 359);
            field0DC = AngleAt00483300(
                owner->opponent->y + 20.0f - y,
                (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
            SetPolarVelocity(field0DC, 36.0f);
        }
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage < 2) {
            rotationZ += 5.0f;
            if (AbsFloatAt00412D90(x - owner->opponent->x) < 60.0f &&
                AbsFloatAt00412D90(y - owner->opponent->y + 20.0f) < 60.0f) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                owner->PlaySharedSound(4);
                field0D8 = x - owner->opponent->x;
                field0DA = y - owner->opponent->y + 20.0f;
                ResetSecondaryCounter(2);
            }
        }
        if (animationStage == 2 && (owner->action == 700 || owner->action == 771)) {
            if (owner->animationStage == 23) {
                x = owner->x + (field0D8 + 60) * facing;
                y = owner->y + (field0DA + 140);
            }
            if (owner->animationStage == 24) {
                x = owner->x + (field0D8 + 94) * facing;
                y = owner->y + (field0DA + 178);
            }
            if (owner->animationStage == 25) {
                x = owner->x + (field0D8 + 150) * facing;
                y = owner->y + (field0DA + 82);
            }
            if (owner->animationStage == 26) {
                x = owner->x + (field0D8 + 75) * facing;
                y = owner->y + (field0DA + 17);
            }
            if (owner->animationStage == 27) {
                x = owner->x + (field0D8 - 30) * facing;
                y = owner->y + (field0DA + 10);
            }
            if (owner->animationStage == 28) {
                x = owner->x + (field0D8 - 110) * facing;
                y = owner->y + (field0DA + 85);
            }
            if (owner->animationStage == 29) {
                x = owner->x + (field0D8 - 95) * facing;
                y = owner->y + (field0DA + 185);
            }
            if (owner->animationStage == 30) {
                x = owner->x + (field0D8 - 10) * facing;
                y = owner->y + (field0DA + 230);
            }
            if (owner->animationStage == 31) {
                x = owner->x + (field0D8 + 54) * facing;
                y = owner->y + (field0DA + 160);
            }
            if (owner->animationStage == 32) {
                x = owner->x + (field0D8 + 80) * facing;
                y = owner->y + (field0DA + 135);
            }
            if (owner->animationStage > 32) {
                x = owner->opponent->x + field0D8 * facing;
                y = owner->opponent->y + (field0DA + 70);
                if (owner->opponent->action == 97) {
                    ResetSecondaryCounter(3);
                    velocityX = RecordedRange(0, 20) - 10;
                    velocityY = -RecordedRange(5, 20);
                    return;
                }
            }
        }
        if (animationStage == 3) {
            velocityY += 0.5f;
            if (y + velocityY <= 0.0f && velocityY > 0.0f)
                velocityY = -velocityY;
            if (color[0] > 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 818:
        if (animationStage == 0 && animationFrame == 0 && field0D8 != 1) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        scaleX += 0.08f;
        scaleY += 0.08f;
        if (color[0] > 10) color[0] -= 10;
        else { ClearFrameInfo(); return; }
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
        break;

    case 819:
        if (owner->action != 703) ClearFrameInfo();
        if (owner->action == 703) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        ++field0DA;
        if (field0D8 == 0) {
            if (color[0] < 235) color[0] += 20;
            else {
                color[0] = 255;
                field0D8 = 1;
            }
        }
        if (field0D8 == 1 && field0DA > 90) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
        break;

    case 820:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(100, 300) * 0.01f;
            scaleY = scaleX;
            rotationZ = RecordedRange(0, 359);
            field0DC = AngleAt00483300(
                owner->opponent->y + 20.0f - y,
                (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
            SetPolarVelocity(field0DC, 36.0f);
        }
        x = facing * velocityX + x;
        y -= velocityY;
        if (animationStage < 2) {
            rotationZ += 5.0f;
            if (AbsFloatAt00412D90(x - owner->opponent->x) < 80.0f &&
                AbsFloatAt00412D90(y - owner->opponent->y + 20.0f) < 80.0f) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                owner->PlaySharedSound(4);
                field0D8 = x - owner->opponent->x;
                field0DA = y - owner->opponent->y + 20.0f;
                ResetSecondaryCounter(2);
            }
        }
        if (animationStage == 2 && (owner->action == 720 || owner->action == 773)) {
            if (owner->animationStage == 23) {
                x = owner->x + (field0D8 + 60) * facing;
                y = owner->y + (field0DA + 140);
            }
            if (owner->animationStage == 24) {
                x = owner->x + (field0D8 + 94) * facing;
                y = owner->y + (field0DA + 178);
            }
            if (owner->animationStage == 25) {
                x = owner->x + (field0D8 + 150) * facing;
                y = owner->y + (field0DA + 82);
            }
            if (owner->animationStage == 26) {
                x = owner->x + (field0D8 + 75) * facing;
                y = owner->y + (field0DA + 17);
            }
            if (owner->animationStage == 27) {
                x = owner->x + (field0D8 - 30) * facing;
                y = owner->y + (field0DA + 10);
            }
            if (owner->animationStage == 28) {
                x = owner->x + (field0D8 - 110) * facing;
                y = owner->y + (field0DA + 85);
            }
            if (owner->animationStage == 29) {
                x = owner->x + (field0D8 - 95) * facing;
                y = owner->y + (field0DA + 185);
            }
            if (owner->animationStage == 30) {
                x = owner->x + (field0D8 - 10) * facing;
                y = owner->y + (field0DA + 230);
            }
            if (owner->animationStage == 31) {
                x = owner->x + (field0D8 + 54) * facing;
                y = owner->y + (field0DA + 160);
            }
            if (owner->animationStage == 32) {
                x = owner->x + (field0D8 + 80) * facing;
                y = owner->y + (field0DA + 135);
            }
            if (owner->animationStage > 32) {
                x = owner->opponent->x + field0D8 * facing;
                y = owner->opponent->y + (field0DA + 70);
                if (owner->opponent->action == 89) {
                    ResetSecondaryCounter(3);
                    velocityX = RecordedRange(0, 20) - 10;
                    velocityY = -RecordedRange(5, 20);
                    return;
                }
            }
        }
        if (animationStage == 3) {
            velocityY += 0.5f;
            if (y + velocityY <= 0.0f && velocityY > 0.0f)
                velocityY = -velocityY;
            if (color[0] > 5) color[0] -= 5;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 821:
        if (owner->action != 723) ClearFrameInfo();
        if (owner->action == 723) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        ++field0DA;
        if (field0D8 == 0) {
            if (color[0] < 235) color[0] += 20;
            else {
                color[0] = 255;
                field0D8 = 1;
            }
        }
        if (field0D8 == 1 && field0DA > 90) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
        break;

    case 822:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f - RecordedRange(0, 5) * 0.1f;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityY = 0.0f;
            velocityX = RecordedRange(0, 10) - 5;
        }
        if (animationStage == 1) {
            if (color[0] > 10) color[0] -= 10;
            else {
                color[0] = 0;
                ClearFrameInfo();
            }
        }
        velocityY -= 0.3f;
        y -= velocityY;
        x = facing * velocityX + x;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 823:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f - RecordedRange(0, 5) * 0.1f;
            scaleY = scaleX;
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
            field0D8 = AngleAt00483300(
                owner->y + 100.0f - y, owner->x - x) / GeometryConstants::RadiansPerDegree;
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->x < 20.0f && x - owner->x > -20.0f &&
                y - owner->y < 120.0f && y - owner->y > 80.0f) {
                ClearFrameInfo();
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
        break;

    case 824:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex824 = 0; cancelIndex824 < 7; cancelIndex824++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            owner->SpawnBattleEffect(806, x + 10.0f - RecordedRange(0, 20),
                y + 10.0f - RecordedRange(0, 20), facing, 1);
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                SetPolarVelocity(field0C8, 30.0f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 1 &&
                ((collisionResult != 0 && collisionResult != 6) || y + velocityY <= 0.0f)) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                remainingHits = 1;
                collisionResult = 0;
                NoOpAt0045B850(1);
                ResetSecondaryCounter(2);
                owner->SpawnBattleEffect(827, x, y, facing, 1);
                scaleX = 1.0f;
                scaleY = 1.0f;
                rotationZ = 0.0f;
                return;
            }
            else {
                if (animationStage == 3 && animationFrame == 0)
                    owner->SpawnBattleEffect(827, x + 50.0f - RecordedRange(0, 100),
                        y + 50.0f - RecordedRange(0, 100), facing, 1);
                if (animationStage == 4 && animationFrame == 0)
                    owner->SpawnBattleEffect(827, x + 50.0f - RecordedRange(0, 100),
                        y + 50.0f - RecordedRange(0, 100), facing, 1);
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                                ClearFrameInfo();
                                return;
                            }
                            else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 825:
        if (owner->action > 69 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex825 = 0; cancelIndex825 < 15; cancelIndex825++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = field0C8;
                velocityY = 10.0f;
                field0DE = 0;
            }
            x = facing * velocityX + x;
            y += velocityY;
            rotationZ += 5.0f;
            if (animationStage < 2 && owner->animationStage == 0 &&
                (owner->action == 408 || owner->action == 414)) {
                ResetSecondaryCounter(2);
                velocityY = 0.0f;
                velocityX = 0.0f;
                return;
            }
            else {
                if (animationStage == 0) {
                    if (velocityX > 2.5f) velocityX -= 1.0f;
                    else velocityX = 2.5f;
                    velocityY -= 0.6f;
                }
                if (animationStage == 1) {
                    --field0DE;
                    owner->opponentVelocityDeltaX = (facing * owner->opponent->facing) * -6.0f *
                        (((owner->opponent->x - x) * facing > 0.0f) * 2 - 1);
                    if (field0DE <= 0) {
                        owner->SpawnBattleEffect(826, x, y, facing, 0);
                        field0DE = 15;
                    }
                }
                if (animationStage == 2) {
                    scaleX *= 0.85f;
                    scaleY *= 0.85f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 1 && animationFrame == 0) {
                    owner->PlaySound(31);
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                }
                if (animationStage == 2 && animationFrame == 0 && field0DA < 45) {
                    ++field0DA;
                    ResetSecondaryCounter(1);
                }
            }
        }
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
        }
        scaleX -= 0.05f;
        scaleY -= 0.05f;
        if (animationFrame > 5) color[0] -= 15;
        rotationZ += 10.0f;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 827:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex827 = 0; cancelIndex827 < 7; cancelIndex827++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                collisionResult = 0;
                remainingHits = 1;
            }
            if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) { ClearFrameInfo(); return; }
            }
        }
        break;

    case 828:
        if (owner->action > 69 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex828 = 0; cancelIndex828 < 15; cancelIndex828++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            rotationZ += 5.0f;
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = field0C8;
                velocityY = 10.0f;
                field0DE = 0;
            }
            x = facing * velocityX + x;
            y += velocityY;
            if (animationStage < 2 && owner->animationStage == 0 &&
                (owner->action == 408 || owner->action == 414)) {
                ResetSecondaryCounter(2);
                velocityY = 0.0f;
                velocityX = 0.0f;
                return;
            }
            else {
                if (animationStage == 0) {
                    if (velocityX > 2.5f) velocityX -= 1.0f;
                    else velocityX = 2.5f;
                    velocityY -= 0.6f;
                }
                if (animationStage == 1) {
                    --field0DE;
                    owner->opponentVelocityDeltaX = (facing * owner->opponent->facing) * -6.0f *
                        (((owner->opponent->x - x) * facing > 0.0f) * 2 - 1);
                    if (field0DE <= 0) {
                        owner->SpawnBattleEffect(826, x, y, facing, 0);
                        field0DE = 15;
                    }
                }
                if (animationStage == 2) {
                    scaleX *= 0.85f;
                    scaleY *= 0.85f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 1 && animationFrame == 0) {
                    owner->PlaySound(31);
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                }
                if (animationStage == 2 && animationFrame == 0 && field0DA < 45) {
                    ++field0DA;
                    ResetSecondaryCounter(1);
                }
            }
        }
        break;

    case 829:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex829 = 0; cancelIndex829 < 5; cancelIndex829++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                velocityX = 15.0f;
                velocityY = 10.0f;
                collisionResult = 0;
                remainingHits = 1;
            }
            rotationZ += 5.0f;
            velocityY -= 1.5f;
            if (y + velocityY < 0.0f) {
                y = 0.0f;
                velocityY = -velocityY;
            }
            if (animationStage == 1 && collisionResult != 0 && collisionResult != 6) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                remainingHits = 1;
                collisionResult = 0;
                NoOpAt0045B850(1);
                ClearFrameInfo();
                owner->SpawnBattleEffect(830, x, y, facing, 1);
                scaleX = 1.0f;
                scaleY = 1.0f;
                rotationZ = 0.0f;
                return;
            }
            else {
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                                ClearFrameInfo();
                                return;
                            }
                            else {
                    x = facing * velocityX + x;
                    y += velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) { ClearFrameInfo(); return; }
                }
            }
        }
        break;

    case 830:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            for (int cancelIndex830 = 0; cancelIndex830 < 5; cancelIndex830++)
                owner->SpawnBattleEffect(996, x, y, 1, 1);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                collisionResult = 0;
                remainingHits = 1;
            }
            if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) { ClearFrameInfo(); return; }
            }
        }
        break;

    case 831:
        if (owner->action != 723) ClearFrameInfo();
        if (owner->action == 723) {
            x = owner->opponent->x;
            y = owner->opponent->y + 100.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
        }
        ++field0DA;
        if (field0DA > 90) {
            if (color[0] > 20) color[0] -= 20;
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
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
            field0D8 = 0;
        }
        scaleX = (0.2f - field0D8 * 0.02f * (field0D8 < 5)) + 0.005f + scaleX;
        scaleY = (0.2f - field0D8 * 0.02f * (field0D8 < 5)) + 0.005f + scaleY;
        ++field0D8;
        if (animationStage > 1) {
            if (color[0] > 20) {
                color[0] -= 20;
                color[2] -= 20;
                color[3] -= 20;
            }
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 833:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        if (animationStage > 0) {
        scaleX = (0.2f - field0D8 * 0.02f * (field0D8 < 5)) + 0.005f + scaleX;
        scaleY = (0.2f - field0D8 * 0.02f * (field0D8 < 5)) + 0.005f + scaleY;
        ++field0D8;
        }
        if (animationStage > 1) {
            if (color[0] > 20) {
                color[0] -= 20;
                color[2] -= 20;
                color[3] -= 20;
            }
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        if (animationStage == 1 && animationFrame == 0) {
            color[0] = 255;
            for (int burstIndex833 = 0; burstIndex833 < 12; burstIndex833++) {
                owner->field314 = RecordedRange(0, 40) - 90;
                owner->field318 = RecordedRange(0, 22) + 5;
                owner->SpawnBattleEffect(812, (RecordedRange(0, 200) - 100) * facing + x,
                    0.0f, facing, 1);
            }
        }
        break;

    case 834:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = -80.0f;
            field0D8 = 0;
        }
        scaleX = (0.3f - field0D8 * 0.05f * (field0D8 < 5)) + 0.005f + scaleX;
        scaleY = (0.3f - field0D8 * 0.05f * (field0D8 < 5)) + 0.005f + scaleY;
        ++field0D8;
        if (animationStage > 1) {
            if (color[0] > 20) {
                color[0] -= 20;
                color[2] -= 20;
                color[3] -= 20;
            }
            else { ClearFrameInfo(); return; }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 835:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 850:
        facing = owner->facing;
        if (owner->action > 149 && owner->action < 154 && animationStage == 0) {
            x = owner->x + facing * 57;
            y = owner->y + 94.0f;
        }
        if (owner->action > 153 && owner->action < 158 && animationStage == 0) {
            x = owner->x + facing * 57;
            y = owner->y + 60.0f;
        }
        if (owner->action == 158 && animationStage == 0) {
            x = owner->x + facing * 57;
            y = owner->y + 100.0f;
        }
        if ((owner->action < 150 || owner->action > 158) && animationStage == 0) {
            ResetSecondaryCounter(1);
            owner->fieldF06 = 0;
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
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        if (animationStage == 1 && animationFrame == 0) ResetSecondaryCounter(0);
        break;

    case 900:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            collisionResult = 0;
            velocityX = RecordedRange(0, 30) - 15;
            velocityY = RecordedRange(0, 15);
        }
        if (animationStage < 3) {
            velocityY -= 0.6f;
            if (velocityY + y <= 0.0f) {
                y = 0.0f;
                ResetSecondaryCounter(3);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
        }
        if (y > 960.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            x = facing * velocityX + x;
            y += velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0);
                ResetTransform(0.0f, 0.0f, 0.0f);
            }
            if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(1);
            if (animationStage == 5 && animationFrame == 0) velocityY = 24.0f;
        }
        break;

    case 901:
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 902:
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 903:
        x = owner->x;
        y = owner->y;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 904:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(0, 4) * 0.1f + 0.4f;
            scaleY = scaleX;
            color[0] = 64;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX += 0.01f;
        scaleY += 0.01f;
        color[0] -= 1;
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;

    case 905:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (RecordedRange(0, 100) < 20)
                owner->SpawnBattleEffect(904, x + 50.0f - RecordedRange(0, 100),
                    y + 50.0f - RecordedRange(0, 100), facing, 1);
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 100;
                field0DA = 0;
                field0DC = field0C8;
                field0DE = 120;
                field0E0 = g_OptionsModeAt006714D0 * 2 + 1;
            }
            if (owner->animationStage < 2) {
                --field0DE;
                if (field0DE <= 0 && owner->opponent->health > 0 && MagnitudeAt00428D20(
                    (owner->opponent->x - x) * (owner->opponent->x - x) +
                    (owner->opponent->y - y) * (owner->opponent->y - y)) > 256 - g_OptionsModeAt006714D0 * 48 &&
                    y > 0.0f && x > 0.0f && x < 1280.0f) {
                    if (field0E0 > 0) {
                        owner->SpawnBattleEffect(906, x, y, facing, 1);
                        owner->PlaySound(28);
                        --field0E0;
                        field0DE = 8;
                    }
                    else {
                        owner->SpawnBattleEffect(906, x, y, facing, 1);
                        owner->PlaySound(28);
                        field0E0 = g_OptionsModeAt006714D0 * 2 + 1;
                        field0DE = 180 - g_OptionsModeAt006714D0 * 30;
                    }
                }
                field0DA = AngleAt00483300(
                    owner->opponent->y - y + 100.0f,
                    (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                if (field0DC > field0DA) {
                    if (field0DC - field0DA <= 180) {
                        field0DC = field0DC - 1;
                        if (field0DC < -180) field0DC = field0DC + 360;
                    }
                    else {
                        field0DC = field0DC + 1;
                        if (field0DC > 180) field0DC = field0DC - 360;
                    }
                }
                if (field0DC <= field0DA) {
                    if (field0DC - field0DA >= -180) {
                        field0DC = field0DC + 1;
                        if (field0DC > 180) field0DC = field0DC - 360;
                    }
                    else {
                        field0DC = field0DC - 1;
                        if (field0DC < -180) field0DC = field0DC + 360;
                    }
                }
            }
            if (owner->animationStage > 1) {
                --field0DE;
                if (field0DE <= 0 && MagnitudeAt00428D20(
                    (owner->opponent->x - x) * (owner->opponent->x - x) +
                    (owner->opponent->y - y) * (owner->opponent->y - y)) > 128.0f &&
                    y > 0.0f && x > 0.0f && x < 1280.0f) {
                    if (field0E0 > 0) {
                        owner->SpawnBattleEffect(906, x, y, facing, 1);
                        owner->PlaySound(28);
                        --field0E0;
                        field0DE = 8;
                    }
                    else {
                        owner->SpawnBattleEffect(906, x, y, facing, 1);
                        owner->PlaySound(28);
                        field0E0 = 5;
                        field0DE = 180 - g_OptionsModeAt006714D0 * 30;
                    }
                }
                field0DA = AngleAt00483300(
                    owner->y - y,
                    (owner->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                if (field0DC > field0DA) {
                    if (field0DC - field0DA <= 180) {
                        field0DC = field0DC - 3;
                        if (field0DC < -180) field0DC = field0DC + 360;
                    }
                    else {
                        field0DC = field0DC + 3;
                        if (field0DC > 180) field0DC = field0DC - 360;
                    }
                }
                if (field0DC <= field0DA) {
                    if (field0DC - field0DA >= -180) {
                        field0DC = field0DC + 3;
                        if (field0DC > 180) field0DC = field0DC - 360;
                    }
                    else {
                        field0DC = field0DC - 3;
                        if (field0DC < -180) field0DC = field0DC + 360;
                    }
                }
            }
            if (field0D8 > 50) --field0D8;
            SetPolarVelocity(field0DC, field0D8 * 0.1f);
            x = facing * velocityX + x;
            y -= velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                if (owner->animationStage < 3) {
                    ++field0D8;
                    ResetSecondaryCounter(1);
                    return;
                }
                else { ClearFrameInfo(); return; }
            }
        }
        break;

    case 906:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 6.0f;
                scaleY = 6.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage == 0) {
                if (scaleX > 1.0f) {
                    scaleX -= 0.2f;
                    scaleY -= 0.2f;
                }
                else {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
                if (color[0] < 235) color[0] += 20;
                else color[0] = 255;
            }
            if (animationStage == 1 && collisionResult != 0) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                if (animationStage == 2) {
                    scaleX *= 0.85f;
                    scaleY *= 0.85f;
                }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                                ClearFrameInfo();
                                return;
                            }
                            else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                        return;
                    }
                    else if (animationStage == 1 && animationFrame == 0) {
                        SetPolarVelocity(AngleAt00483300(owner->opponent->y + 100.0f - y,
                            (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree, 6.0f);
                        rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                        collisionResult = 0;
                        remainingHits = 1;
                    }
                }
            }
        }
        break;

    case 907:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                collisionResult = 0;
            }
            field0CC += 1.0f;
            SetPolarVelocity(field0C8, field0CC * 0.1f);
            if (animationStage == 2) {
                scaleX *= 0.85f;
                scaleY *= 0.85f;
            }
            if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                x = facing * velocityX + x;
                y -= velocityY;
                if (AdvanceNestedFrame() == animationStageCount) { ClearFrameInfo(); return; }
            }
        }
        break;

    case 910:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
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
            }
            if (owner->action == 761) {
                x = owner->x + facing * 140;
                y = owner->y + 35.0f;
            }
            if (owner->action != 761 || (owner->action == 761 && owner->animationStage > 12)) {
                ClearFrameInfo();
                return;
            }
            else {
                scaleY *= 0.9f;
                scaleX += 0.1f;
                if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(4);
            }
        }
        break;

    case 911:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        scaleX = RecordedRange(75, 150) * 0.01f;
                        scaleY = scaleX;
                        rotationZ = RecordedRange(0, 359);
                        field0DC = AngleAt00483300(
                            static_cast<SuikaFighter*>(owner)->fieldF24 - y,
                            (static_cast<SuikaFighter*>(owner)->fieldF22 - x) * facing) / GeometryConstants::RadiansPerDegree;
                        SetPolarVelocity(field0DC, 36.0f);
                    }
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (animationStage < 2) {
                        rotationZ += 5.0f;
                        if (AbsFloatAt00412D90(x - static_cast<SuikaFighter*>(owner)->fieldF22) < 60.0f &&
                            AbsFloatAt00412D90(y - static_cast<SuikaFighter*>(owner)->fieldF24) < 60.0f) {
                            velocityX = 0.0f;
                            velocityY = 0.0f;
                            owner->PlaySharedSound(4);
                            field0D8 = x - static_cast<SuikaFighter*>(owner)->fieldF22;
                            field0DA = y - static_cast<SuikaFighter*>(owner)->fieldF24;
                            ResetSecondaryCounter(2);
                        }
                    }
                    if (animationStage == 2 && owner->action == 774) {
                        if (owner->animationStage == 6) {
                            x = owner->x + (field0D8 + 60) * facing;
                            y = owner->y + (field0DA + 140);
                        }
                        if (owner->animationStage == 7) {
                            x = owner->x + (field0D8 + 94) * facing;
                            y = owner->y + (field0DA + 178);
                        }
                        if (owner->animationStage == 8) {
                            x = owner->x + (field0D8 + 150) * facing;
                            y = owner->y + (field0DA + 82);
                        }
                        if (owner->animationStage == 9) {
                            x = owner->x + (field0D8 + 75) * facing;
                            y = owner->y + (field0DA + 17);
                        }
                        if (owner->animationStage == 10) {
                            x = owner->x + (field0D8 - 30) * facing;
                            y = owner->y + (field0DA + 10);
                        }
                        if (owner->animationStage == 11) {
                            x = owner->x + (field0D8 - 110) * facing;
                            y = owner->y + (field0DA + 85);
                        }
                        if (owner->animationStage == 12) {
                            x = owner->x + (field0D8 - 95) * facing;
                            y = owner->y + (field0DA + 185);
                        }
                        if (owner->animationStage == 13) {
                            x = owner->x + (field0D8 - 10) * facing;
                            y = owner->y + (field0DA + 230);
                        }
                        if (owner->animationStage == 14) {
                            x = owner->x + (field0D8 + 54) * facing;
                            y = owner->y + (field0DA + 160);
                        }
                        if (owner->animationStage == 15) {
                            x = owner->x + (field0D8 + 80) * facing;
                            y = owner->y + (field0DA + 135);
                        }
                        if (owner->animationStage == 16) ResetSecondaryCounter(3);
                    }
                    if (animationStage == 3) {
                        if (x > 1400.0f || x < -200.0f || y > 960.0f ||
                            (owner->action == 774 && owner->animationStage == 5)) {
                            ClearFrameInfo();
                            return;
                        }
                        x = static_cast<SuikaFighter*>(owner)->fieldF22 + field0D8 * facing;
                        y = static_cast<SuikaFighter*>(owner)->fieldF24 + field0DA;
                        if (static_cast<SuikaFighter*>(owner)->fieldF24 <= 0) {
                            ResetSecondaryCounter(4);
                            velocityX = RecordedRange(0, 20) - 10;
                            velocityY = -RecordedRange(5, 20);
                            return;
                        }
                    }
                    if (animationStage == 4) {
                        velocityY += 0.5f;
                        if (y + velocityY <= 0.0f && velocityY > 0.0f)
                            velocityY = -velocityY;
                        if (color[0] > 5) color[0] -= 5;
                        else { ClearFrameInfo(); return; }
                    }
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 912:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            static_cast<SuikaFighter*>(owner)->fieldF22 = x;
            static_cast<SuikaFighter*>(owner)->fieldF24 = y;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                remainingHits = 1;
                collisionResult = 0;
            }
            if (owner->action == 774 && owner->animationStage > 15 && animationStage == 0) {
                x = owner->x + facing * 140;
                y = owner->y + 35.0f;
                ResetSecondaryCounter(1);
                field0DC = AngleAt00483300(
                    owner->opponent->y + 100.0f - y,
                    (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree;
                SetPolarVelocity(field0DC, g_OptionsModeAt006714D0 * 3 + 15);
            }
            if (animationStage == 1 && y < 0.0f) {
                owner->PlaySound(23);
                ClearFrameInfo();
                return;
            }
            else {
                if (x > 1700.0f || x < -500.0f || y > 1280.0f) {
                    ClearFrameInfo();
                    return;
                }
                else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
                }
            }
        }
        break;

    case 913:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                owner->SpawnBattleEffect(914, x, y, facing, 0);
            }
            if (field0D8 < 60) ++field0D8;
            --field0DC;
            rotationZ -= 5.0f;
            if (animationStage == 1) {
                scaleX += 0.15f;
                scaleY += 0.15f;
                --field0DE;
            }
            if (animationStage == 2) {
                owner->opponentVelocityDeltaX = -(field0D8 * 0.1f) *
                    (facing * owner->opponent->facing) *
                    (((owner->opponent->x - x) * facing > 0.0f) * 2 - 1);
                owner->SetCameraShake(2.0f);
                if (field0DC <= 0) {
                    owner->field31C = RecordedRange(0, 359);
                    SetPolarVelocity(owner->field31C, 960.0f);
                    owner->SpawnBattleEffect(916, facing * velocityX + x,
                        y + velocityY, facing, 1);
                    owner->field31C = RecordedRange(0, 359);
                    SetPolarVelocity(owner->field31C, 960.0f);
                    owner->SpawnBattleEffect(916, facing * velocityX + x,
                        y + velocityY, facing, 1);
                    field0DC = 6 - g_OptionsModeAt006714D0;
                }
            }
            if (animationStage == 4) {
                scaleX *= 0.85f;
                scaleY *= 0.85f;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 1 && animationFrame == 0) {
                NoOpAt0045B850(31);
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage == 3 && animationFrame == 0 &&
                field0DA < g_OptionsModeAt006714D0 + 2) {
                ++field0DA;
                ResetSecondaryCounter(2);
            }
        }
        break;

    case 914:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            ++field0D8;
            rotationZ -= 6.0f;
            if (animationStage == 4) {
                scaleX *= 0.85f;
                scaleY *= 0.85f;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 3 && animationFrame == 0 &&
                field0DA < g_OptionsModeAt006714D0 + 2) {
                ++field0DA;
                ResetSecondaryCounter(2);
            }
        }
        break;

    case 915:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                velocityX = RecordedRange(0, 8) + 6;
            }
            if (x > 1180.0f || x < 100.0f) {
                ClearFrameInfo();
                owner->SpawnBattleEffect(913, x, y, facing, 0);
                return;
            }
            else {
                if (animationStage == 1) {
                    scaleX = RecordedRange(0, 5) * 0.1f + 0.8f;
                    scaleY = scaleX;
                }
                x = facing * velocityX + x;
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                    owner->SpawnBattleEffect(913, x, y, facing, 0);
                    return;
                }
            }
        }
        break;

    case 916:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                field0D8 = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                SetPolarVelocity(-field0D0 + 180.0f, 30.0f);
                rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            if ((collisionResult != 0 || field0D0 <= 0.0f) && animationStage == 1) {
                ResetSecondaryCounter(2);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            else {
                if (animationStage > 1) {
                    if (color[0] > 20) color[0] -= 20;
                    else { ClearFrameInfo(); return; }
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 2 && animationFrame == 0) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                }
            }
        }
        break;

    case 918:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 99;
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
            } else if (animationStage == 0 && animationFrame != 0) {
                // Keep the transform established on the first frame.
            }
            if (animationStage == 1) {
                scaleX += 0.033f;
                scaleY += 0.033f;
                if (scaleX > 1.0f) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 3) {
                scaleX = RecordedRange(0, 5) * 0.025f + 0.95;
                scaleY = scaleX;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            rotationZ += 1.0f;
            if (x > 1800.0f || x < -680.0f || y > 1280.0f || y < -380.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) {
                    ResetSecondaryCounter(3);
                    collisionResult = 0;
                    return;
                }
                else if (animationStage == 3 && animationFrame == 0) {
                    owner->PlaySound(16);
                    SetPolarVelocity(AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree, 5.0f);
                }
            }
        }
        break;

    case 919:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 3.0f;
                scaleY = 3.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                collisionResult = 0;
                remainingHits = 1;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage == 0) {
                if (color[0] < 220) color[0] += 35;
                else color[0] = 255;
                scaleX -= 0.1f;
                scaleY -= 0.1f;
            }
            if (animationStage == 1) {
                if (field0D8 < 15) ++field0D8;
                SetPolarVelocity(field0C8, 20 - field0D8);
            }
            if (animationStage == 1 && collisionResult != 0) {
                ResetSecondaryCounter(2);
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            else {
                if (animationStage == 2) {
                    scaleX *= 0.85f;
                    scaleY *= 0.85f;
                }
                if (x > 1380.0f || x < -100.0f || y > 960.0f || y < -100.0f) {
                                ClearFrameInfo();
                                return;
                            }
                            else {
                    x = facing * velocityX + x;
                    y -= velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                        return;
                    }
                    else if (animationStage == 1 && animationFrame == 0) {
                        SetPolarVelocity(field0C8, 20.0f);
                        rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
                    }
                }
            }
        }
        break;

    case 920:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                owner->SpawnBattleEffect(921, x, y, facing, 0);
            }
            if (field0D8 < g_OptionsModeAt006714D0 * 8 + 10) ++field0D8;
            --field0DC;
            rotationZ -= 5.0f;
            if (animationStage == 1) {
                scaleX += 0.15f;
                scaleY += 0.15f;
                --field0DE;
            }
            if (animationStage == 2) {
                owner->opponentVelocityDeltaX = -(field0D8 * 0.1f) *
                    (facing * owner->opponent->facing) *
                    (((owner->opponent->x - x) * facing > 0.0f) * 2 - 1);
                owner->SetCameraShake(2.0f);

            }
            if (animationStage == 4) {
                scaleX *= 0.85f;
                scaleY *= 0.85f;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 1 && animationFrame == 0) {
                NoOpAt0045B850(31);
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        }
        break;

    case 921:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                field0DA = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            ++field0D8;
            rotationZ -= 6.0f;
            if (animationStage == 4) {
                scaleX *= 0.85f;
                scaleY *= 0.85f;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        }
        break;

    case 922:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = RecordedRange(0, 359);
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 923:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                velocityX = RecordedRange(0, 8) - 4;
                velocityY = -RecordedRange(0, 3) - 13;
            }
            if (animationFrame == 0)
                owner->SpawnBattleEffect(922, x + 10.0f - RecordedRange(0, 20),
                    y + 10.0f - RecordedRange(0, 20), facing, 1);
            if (x > 1380.0f || x < -100.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                velocityY += 0.2f;
                x = facing * velocityX + x;
                y -= velocityY;
                if (y - velocityY <= 0.0f) {
                    ClearFrameInfo();
                    owner->SpawnBattleEffect(925, x, y, facing, 1);
                    owner->SpawnBattleEffect(925, x, y, facing, 1);
                }
                if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
            }
        }
        break;

    case 924:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = RecordedRange(0, 359);
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 925:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                velocityX = RecordedRange(0, 8) - 4;
                velocityY = -RecordedRange(0, 3) - 13;
            }
            if (animationFrame == 0)
                owner->SpawnBattleEffect(924, x + 5.0f - RecordedRange(0, 10),
                    y + 5.0f - RecordedRange(0, 10), facing, 1);
            if (x > 1380.0f || x < -100.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                velocityY += 0.2f;
                x = facing * velocityX + x;
                y -= velocityY;
                if (y - velocityY <= 0.0f) {
                    ClearFrameInfo();
                    owner->SpawnBattleEffect(927, x, y, facing, 1);
                    owner->SpawnBattleEffect(927, x, y, facing, 1);
                }
                if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
            }
        }
        break;

    case 926:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationZ = RecordedRange(0, 359);
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;

    case 927:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 0;
                velocityX = RecordedRange(0, 8) - 4;
                velocityY = -RecordedRange(0, 3) - 13;
            }
            if (animationFrame == 0)
                owner->SpawnBattleEffect(926, x, y, facing, 1);
            if (x > 1380.0f || x < -100.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                velocityY += 0.2f;
                x = facing * velocityX + x;
                y -= velocityY;
                if (y - velocityY <= 0.0f) {
                    if (field0D8 == 0) {
                        velocityY = -velocityY * 0.75f;
                        remainingHits = 1;
                        collisionResult = 0;
                        ++field0D8;
                        return;
                    }
                    ClearFrameInfo();
                }
                if (AdvanceNestedFrame() == animationStageCount) ResetSecondaryCounter(1);
            }
        }
        break;

    case 928:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 99;
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
            } else if (animationStage == 0 && animationFrame != 0) {
                // Keep the transform established on the first frame.
            }
            if (animationStage == 1) {
                scaleX += 0.033f;
                scaleY += 0.033f;
                if (scaleX > 1.0f) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 3) {
                scaleX = RecordedRange(0, 5) * 0.025f + 0.95;
                scaleY = scaleX;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            rotationZ += 1.0f;
            if (x > 1800.0f || x < -680.0f || y > 1280.0f || y < -380.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) {
                    ResetSecondaryCounter(3);
                    collisionResult = 0;
                    return;
                }
                else if (animationStage == 3 && animationFrame == 0) {
                    owner->PlaySound(16);
                    SetPolarVelocity(AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree, 5.0f);
                }
            }
        }
        break;

    case 929:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 99;
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
            } else if (animationStage == 0 && animationFrame != 0) {
                // Keep the transform established on the first frame.
            }
            if (animationStage == 1) {
                scaleX += 0.033f;
                scaleY += 0.033f;
                if (scaleX > 1.0f) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 3) {
                scaleX = RecordedRange(0, 5) * 0.025f + 0.95;
                scaleY = scaleX;
            }
            x = facing * velocityX + x;
            y -= velocityY;
            rotationZ += 1.0f;
            if (x > 1800.0f || x < -680.0f || y > 1280.0f || y < -380.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) {
                    ResetSecondaryCounter(3);
                    collisionResult = 0;
                    return;
                }
                else if (animationStage == 3 && animationFrame == 0) {
                    owner->PlaySound(16);
                    SetPolarVelocity(AngleAt00483300(owner->opponent->y + 100.0f - y,
                        (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree, 5.0f);
                }
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
            spriteOffsetZ = 1250;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            rotationX = -80.0f;
            field0D8 = owner->spellTimer;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            scaleX = static_cast<float>(owner->spellTimer) / field0D8 * 2;
            scaleY = static_cast<float>(owner->spellTimer) / field0D8 * 2;
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(10);
                break;
            }
        }
        break;
    default:
        AdvanceNestedFrame();
        break;
    }
}
