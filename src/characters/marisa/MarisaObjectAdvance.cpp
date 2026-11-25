#include "engine/MathFloatHelpers.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
// Reconstruction of MarisaObject::Advance at 0049C8F0.
#include "characters/CharacterObject.hpp"
#include "characters/marisa/MarisaFighter.hpp"


extern float __cdecl AngleAt00483300(float y, float x);

extern const double g_MarisaSparkBaseGrowthAt00659430;
extern const double g_MarisaSparkInitialGrowthAt00659438;

extern const float g_MarisaStreakLeftLimitAt0065941C;
extern const float g_MarisaStreakRightLimitAt00659418;
extern const float g_MarisaStreakLeftLimitAt00659414;


extern const double g_MarisaDustGrowthAt006593F8;

extern const float g_MarisaVolleyRightLimitAt006593EC;

void MarisaObject::Advance()
{
    if (owner->opponent->opponentFreezeSnapshot != 0) {
        return;
    }
    if (owner->opponentFreezeSnapshot != 0 && field08A == 0) {
        return;
    }
    if (hitstopFrames != 0) {
        --hitstopFrames;
        return;
    }
    switch (action) {
    // 0x320–0x322 share the owner-action check and projectile impact effects.
    case 800:
        if (owner->action == 400 && field0D8 == 0) {
            x = owner->x + static_cast<float>(facing * 100);
            y = (owner->y) + GeometryConstants::Hundred;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 20) {
            ResetSecondaryCounter(20);
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E2, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 40) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 80) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 120) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 160) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 200) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 240) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 280) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 320) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 360) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 400) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 440) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 480) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 520) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 560) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 600) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 640) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 680) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 720) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 760) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 800) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 840) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 880) + x, y, 1, 1);
            return;
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            ++remainingHits;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++remainingHits;
                field0DA = 0;
            }
        }
        if (owner->action != 400) {
            field0D8 = 1;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 5;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (collisionResult != 0) {
            if (field0DA < 2) {
                ++field0DA;
            } else {
                collisionResult = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
        }
        if (animationStage > 19) {
            if (color[0] > 20) {
                color[0] -= 20;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(20);
        }
        if (animationStage == 20 && owner->action == 400 &&
            owner->animationStage > 5 && owner->animationStage < 10) {
            ResetSecondaryCounter(12);
        }
        break;

    case 801:
        if (owner->action == 402 && field0D8 == 0) {
            x = owner->x + static_cast<float>(facing * 100);
            y = (owner->y) + GeometryConstants::SixtySix;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 20) {
            ResetSecondaryCounter(20);
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E2, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 40) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 80) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 120) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 160) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 200) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 240) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 280) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 320) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 360) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 400) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 440) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 480) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 520) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 560) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 600) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 640) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 680) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 720) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 760) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 800) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 840) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 880) + x, y, 1, 1);
            return;
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            ++remainingHits;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++remainingHits;
                field0DA = 0;
            }
        }
        if (owner->action != 400) {
            field0D8 = 1;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 5;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (collisionResult != 0) {
            if (field0DA < 2) {
                ++field0DA;
            } else {
                collisionResult = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
        }
        if (animationStage > 19) {
            if (color[0] > 20) {
                color[0] -= 20;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(20);
        }
        if (animationStage == 20 && owner->action == 400 &&
            owner->animationStage > 5 && owner->animationStage < 10) {
            ResetSecondaryCounter(12);
        }
        break;

    case 802:
        if (owner->action == 404 && field0D8 == 0) {
            x = owner->x + static_cast<float>(facing * 70);
            y = (owner->y) + GeometryConstants::HundredSixteen;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 20) {
            ResetSecondaryCounter(20);
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E2, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 40) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 80) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 120) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 160) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 200) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 240) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 280) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 320) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 360) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 400) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 440) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 480) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 520) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 560) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 600) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 640) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 680) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 720) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 760) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 800) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 840) + x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E2, static_cast<float>(facing * 880) + x, y, 1, 1);
            return;
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            ++remainingHits;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++remainingHits;
                field0DA = 0;
            }
        }
        if (owner->action != 404) {
            field0D8 = 1;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 5;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (collisionResult != 0) {
            if (field0DA < 2) {
                ++field0DA;
            } else {
                collisionResult = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
        }
        if (animationStage > 19) {
            if (color[0] > 20) {
                color[0] -= 20;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(20);
        }
        if (animationStage == 20 && owner->action == 404 &&
            owner->animationStage > 5 && owner->animationStage < 10) {
            ResetSecondaryCounter(12);
        }
        break;

    case 803:
        if (owner->action == 305) {
            x = owner->x + static_cast<float>(facing * 38);
            y = (owner->y) + FloatConstants::Three;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) * FloatConstants::FourFifths;
        scaleY = (scaleY) * FloatConstants::FourFifths;
        if (animationStage > 1 && color[0] > 10) {
            color[0] -= 10;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 804:
        if (owner->action == 305) {
            x = owner->x + static_cast<float>(facing * 38);
            y = (owner->y) + FloatConstants::Three;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 60.0f;
            rotationY = static_cast<float>(facing * 60);
        }
        scaleX = (scaleX) + FloatConstants::OneFifth;
        scaleY = (scaleY) + FloatConstants::OneFifth;
        if (color[0] > 20) {
            color[0] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 805:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 4.0f;
            scaleY = 4.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 75.0f;
        }
        scaleX = (scaleX) + FloatConstants::ThreeTenths;
        scaleY = (scaleY) + FloatConstants::ThreeTenths;
        if (color[0] > 20) {
            color[0] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 806:
        if ((owner->action == 700 && animationStage < 6) || owner->action == 701) {
            x = owner->x + static_cast<float>(facing * 32);
            y = (owner->y) + GeometryConstants::Ninety;
        }
        if (owner->action != 701 &&
            (owner->action != 700 || owner->animationStage >= 6) &&
            animationStage < 10) {
            ResetSecondaryCounter(animationStage + 10);
            remainingHits = 1;
            collisionResult = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            if (field0D8 != 1) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.5f;
                scaleY = 2.0f;
                field0D8 = 1;
                field0DA = 100;
                field0DC = 1300;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage < 10) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
            field0DA = static_cast<short>(field0DA * FloatConstants::NinetyEightHundredths);
            --field0DC;
            scaleY = field0DC * FloatConstants::OneThousandth +
                field0DA * FloatConstants::OneHundredthDouble;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            color[0] -= 5;
            if (color[0] < 10) {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(10);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 807:
        if (owner->action == 394) {
            x = owner->x + static_cast<float>(facing * 151);
            y = (owner->y) + GeometryConstants::HundredFour;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) * FloatConstants::FourFifths;
        scaleY = (scaleY) * FloatConstants::FourFifths;
        if (animationStage > 1 && color[0] > 10) {
            color[0] -= 10;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 808:
        if (owner->action == 395) {
            x = owner->x + static_cast<float>(facing * 128);
            y = (owner->y) + GeometryConstants::Seventy;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) * FloatConstants::FourFifths;
        scaleY = (scaleY) * FloatConstants::FourFifths;
        if (animationStage > 1 && color[0] > 10) {
            color[0] -= 10;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 809:
        if ((owner->action == 700 && animationStage < 6) || owner->action == 701 ||
            (owner->action == 751 && owner->animationStage < 12) ||
            (owner->action == 752 && owner->animationStage < 12)) {
            x = owner->x + static_cast<float>(facing * 64);
            y = (owner->y) + GeometryConstants::Ninety;
        }
        if (owner->action != 701 &&
            (owner->action != 700 || owner->animationStage >= 6) &&
            (owner->action != 751 || owner->animationStage >= 12) &&
            (owner->action != 752 || owner->animationStage >= 12) &&
            animationStage == 0) {
            ResetSecondaryCounter(1);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) * FloatConstants::FourFifths;
        scaleY = (scaleY) * FloatConstants::FourFifths;
        if (animationStage > 0 && color[0] > 10) {
            color[0] -= 10;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetSecondaryCounter(0);
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
            rotationY = static_cast<float>(facing * 70);
        }
        scaleX = (scaleX) + FloatConstants::ThreeQuarters;
        scaleY = (scaleY) + FloatConstants::ThreeQuarters;
        if (color[0] > 20) {
            color[0] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    // 0x32B and 0x32C launch moving shots and switch to different cleanup actions.
    case 811:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0 && field0D8 != 1) {
            field0D8 = 1;
            field0DA = 200;
            field0DC = static_cast<short>(field0C8);
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            SetPolarVelocity(static_cast<float>(field0DC), field0DA * FloatConstants::OneHundredth);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
        }
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        RecordedRange(0, 100);
        if (collisionResult == 1 || collisionResult == 2 || collisionResult == 4 ||
            y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(813);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            scaleX = 0.5f;
            scaleY = 0.5f;
            return;
        }
        field0DA = field0DA + 50;
        SetPolarVelocity(static_cast<float>(field0DC), field0DA * FloatConstants::OneHundredth);
        x = facing * velocityX + x;
        y = y - velocityY;
        if (x > GeometryConstants::ThirteenHundredEighty || x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(20);
        }
        break;

    case 812:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 69 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0 && field0D8 != 1) {
            field0D8 = 1;
            field0DA = 100;
            field0DC = static_cast<short>(field0C8);
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            SetPolarVelocity(static_cast<float>(field0DC), field0DA * FloatConstants::OneHundredth);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        rotationZ = (rotationZ) + FloatConstants::Two;
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        RecordedRange(0, 100);
        if (collisionResult == 1 || collisionResult == 2 || collisionResult == 4 ||
            y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(814);
            owner->SpawnBattleEffect(845, x, y, facing, 1);
            owner->SpawnBattleEffect(845, x, y, facing, 1);
            owner->SpawnBattleEffect(845, x, y, facing, 1);
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            scaleX = 0.5f;
            scaleY = 0.5f;
            return;
        }
        field0DA = field0DA + 10;
        SetPolarVelocity(static_cast<float>(field0DC), field0DA * FloatConstants::OneHundredth);
        x = facing * velocityX + x;
        y = y - velocityY;
        if (x > GeometryConstants::ThirteenHundredEighty || x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 813:
        if (animationStage == 0 && animationFrame == 0) {
            NoOpAt0045B850(7);
            ResetTransform(0.0f, 0.0f, 0.0f);
            field0D8 = 0;
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 0.25f;
            scaleY = 0.25f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        ++field0D8;
        scaleX = (g_MarisaSparkInitialGrowthAt00659438 - field0D8 * g_MarisaSparkGrowthLossAt00659440) *
            (field0D8 < 5) + g_MarisaSparkBaseGrowthAt00659430 + scaleX;
        scaleY = (g_MarisaSparkInitialGrowthAt00659438 - field0D8 * g_MarisaSparkGrowthLossAt00659440) *
            (field0D8 < 5) + g_MarisaSparkBaseGrowthAt00659430 + scaleY;
        if (color[0] > 10) {
            color[0] -= 10;
        } else {
            color[0] = 0;
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 814:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 1) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            field0D8 = static_cast<short>(
                AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree);
            SetPolarVelocity(static_cast<float>(field0D8 - 20 + RecordedRange(0, 40)), 2.0f);
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            NoOpAt0045B850(8);
        }
        scaleX = (scaleX) + FloatConstants::OneFifth;
        scaleY = (scaleY) + FloatConstants::OneFifth;
        if (animationStage > 1) {
            color[0] -= 16;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 815:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field0D8 = 0;
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
        ++field0D8;
        rotationZ = (rotationZ) + FloatConstants::One;
        scaleX = (g_MarisaSparkInitialGrowthAt00659438 - field0D8 * g_MarisaSparkGrowthLossAt00659440) *
            (field0D8 < 5) + g_MarisaSparkBaseGrowthAt00659430 + scaleX;
        scaleY = (g_MarisaSparkInitialGrowthAt00659438 - field0D8 * g_MarisaSparkGrowthLossAt00659440) *
            (field0D8 < 5) + g_MarisaSparkBaseGrowthAt00659430 + scaleY;
        if (animationStage > 0) {
            if (color[0] > 10) {
                color[0] -= 10;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 816:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(25, 75) * FloatConstants::OneHundredth;
            scaleY = scaleX;
            color[1] = RecordedRange(0, 255);
            color[2] = RecordedRange(0, 255);
            color[3] = RecordedRange(0, 255);
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        x = (x) - FloatConstants::OneTenth;
        rotationZ = (rotationZ) + FloatConstants::Five;
        color[0] -= 7;
        scaleX = (scaleX) - FloatConstants::OneHundredth;
        scaleY = (scaleY) - FloatConstants::OneHundredth;
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 817:
        facing = owner->facing;
        if (owner->action > 0x95 && owner->action < 0x9A &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + GeometryConstants::NinetyFour;
        }
        if (owner->action > 0x99 && owner->action < 0x9E &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + GeometryConstants::Sixty;
        }
        if (owner->action == 0x9E && animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + GeometryConstants::Hundred;
        }
        if ((owner->action < 0x96 || owner->action > 0x9E) &&
            animationStage == 0) {
            ResetSecondaryCounter(1);
            owner->fieldF0A = 0;
        }
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationY = 50.0f;
            field0D8 = 1;
        }
        rotationZ = (rotationZ) + FloatConstants::Two;
        if (animationStage > 0) {
            if (color[0] > 0x1E) {
                color[0] -= 0x1E;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 818:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            velocityX = (field0C8) * FloatConstants::OneTenth;
            velocityY = (field0CC) * FloatConstants::OneTenth;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        velocityY = (velocityY) - FloatConstants::ThreeFifths;
        x = facing * velocityX + x;
        y = y + velocityY;
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (RecordedRange(0, 100) < 30) {
            owner->SpawnBattleEffect(816,
                x + static_cast<float>(RecordedRange(-20, 20)),
                y + static_cast<float>(RecordedRange(-20, 20)), facing, 1);
        }
        if (y < FloatConstants::Zero || collisionResult == 4) {
            ResetPrimaryCounters(854);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            owner->SpawnBattleEffect(821, x, y, facing, 1);
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            scaleX = 0.5f;
            scaleY = 0.5f;
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 819:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150) {
            ClearFrameInfo();
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            SetPolarVelocity(-60.0f, 15.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        velocityY = (velocityY) - FloatConstants::ThreeQuarters;
        x = facing * velocityX + x;
        y = y + velocityY;
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (RecordedRange(0, 100) < 30) {
            owner->SpawnBattleEffect(816,
                x + static_cast<float>(RecordedRange(-20, 20)),
                y + static_cast<float>(RecordedRange(-20, 20)), facing, 1);
        }
        if (y < FloatConstants::Zero) {
            ResetPrimaryCounters(822);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            owner->SpawnBattleEffect(821, x, y, facing, 1);
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            scaleX = 0.5f;
            scaleY = 0.5f;
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 820:
        if ((owner->action == 700 && owner->animationStage < 6) || owner->action == 701) {
            x = owner->x + static_cast<float>(facing * 32);
            y = (owner->y) + GeometryConstants::Ninety;
        }
        if (owner->action != 701 &&
            (owner->action != 700 || owner->animationStage >= 6) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            remainingHits = 1;
            collisionResult = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            if (field0D8 != 1) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 2.0f;
                field0D8 = 1;
                field0DA = 100;
                field0DC = 2000;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
            field0DA = static_cast<short>(field0DA * FloatConstants::NinetyEightHundredths);
            --field0DC;
            scaleY = field0DC * FloatConstants::OneThousandth +
                field0DA * FloatConstants::OneHundredthDouble;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            color[0] -= 5;
            if (color[0] < 10) {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(25);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 821:
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 822:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 1) {
            field0D8 = 0;
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            velocityY = 0.0f;
            velocityX = 0.0f;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            NoOpAt0045B850(9);
        }
        scaleX = (scaleX) + FloatConstants::SevenHundredths;
        scaleY = (scaleY) + FloatConstants::SevenHundredths;
        color[0] -= 10;
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 823:
        if (owner->action == 400 && field0D8 == 0) {
            x = owner->x + static_cast<float>(facing * 120);
            y = (owner->y) + GeometryConstants::Hundred;
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->action != 400) {
            field0D8 = 1;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.7f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage == 3 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        scaleX = (scaleX) + FloatConstants::OneHundredth;
        if (animationStage == 4) {
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
        }
        if (animationStage > 3 && color[0] > 3) {
            color[0] -= 3;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 4 && owner->action == 400 && owner->animationStage == 6) {
            ResetSecondaryCounter(3);
        }
        break;

    case 824:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = -30.0f;
            velocityY = 10.0f;
            verticalAcceleration = 0.01f;
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        if (x > GeometryConstants::FourteenHundred || x < GeometryConstants::NegativeTwoHundred) {
            ClearFrameInfo();
        }
        velocityY = velocityY - verticalAcceleration;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(12);
        }
        break;

    case 825:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            field0D8 = 1;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 80.0f;
            velocityY = 0.0f;
        }
        owner->SpawnBattleEffect(844, x - static_cast<float>(facing * 75),
            (y) + GeometryConstants::TwoHundredTwenty, -facing, 1);
        owner->SpawnBattleEffect(844, x - static_cast<float>(facing * 75),
            (y) + GeometryConstants::TwoHundredTwenty, -facing, 1);
        owner->SpawnAuxEffect(130, x, 0.0f, facing, 1);
        if (facing > 0 && owner->x < x && owner->animationStage == 4 && owner->action == 704) {
            owner->velocityX = 80.0f;
        }
        if (facing < 0 && owner->x > x && owner->animationStage == 4 && owner->action == 704) {
            owner->velocityX = 80.0f;
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        if (x > GeometryConstants::TwoThousand || x < g_MarisaStreakLeftLimitAt0065941C ||
            owner->animationStage > 4) {
            ClearFrameInfo();
            owner->scriptCounterF02 = 1;
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
            collisionResult = 0;
        }
        break;

    case 826:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 80.0f;
            velocityY = 0.0f;
        }
        owner->SpawnBattleEffect(840, x - static_cast<float>(facing * 481), 250.0f, 1, 1);
        x = facing * velocityX + x;
        y = y + velocityY;
        if (x > g_MarisaStreakRightLimitAt00659418 || x < g_MarisaStreakLeftLimitAt00659414) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 827:
        if (owner->action == 703) {
            x = owner->x;
            y = owner->y;
            if (owner->animationStage > 22) {
                ClearFrameInfo();
                return;
            }
        }
        if (owner->action != 703) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 828:
        UpdateTrackingNode();
        break;

    case 829:
        UpdateTrackingNode();
        break;

    case 830:
        UpdateTrackingNode();
        break;

    case 831:
        UpdateTrackingNode();
        break;

    case 832:
        UpdateTrackingNode();
        break;

    case 833:
        UpdateTrackingNode();
        break;

    // 0x342 and 0x343 update the shared angle and phase used by the orbiting objects.
    case 834:
        if (animationStage < 5 || animationStage == 6) {
            x = owner->x;
        }
        if (animationStage < 5 || animationStage == 6) {
            y = (owner->y) + GeometryConstants::Hundred;
        }
        owner->fieldF0C = static_cast<short>(x);
        owner->fieldF0E = static_cast<short>(y);
        static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 3;
        if (static_cast<MarisaFighter*>(owner)->fieldF12 == 2) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 7;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF12 == 3) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 3;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF10 < 0) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = 0;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF10 >= 360) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            owner->field314 = 0.0f;
            owner->SpawnBattleEffect(828, x, y, 1, 1);
        }
        if (animationStage == 1 && animationFrame == 0) {
            owner->field314 = 90.0f;
            owner->SpawnBattleEffect(829, x, y, 1, 1);
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->field314 = 180.0f;
            owner->SpawnBattleEffect(830, x, y, 1, 1);
        }
        if (animationStage == 3 && animationFrame == 0) {
            owner->field314 = 270.0f;
            owner->SpawnBattleEffect(831, x, y, 1, 1);
        }
        if (animationStage == 4) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 1;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF14 == 0 && animationStage < 7) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
            ResetSecondaryCounter(7);
            return;
        }
        if (animationStage == 4 && owner->action == 707 &&
            owner->animationStage == 5) {
            ResetSecondaryCounter(5);
            remainingHits = 15;
            static_cast<MarisaFighter*>(owner)->fieldF12 = 2;
            facing = owner->facing;
        }
        if (animationStage == 4 && owner->action == 708 &&
            owner->animationStage == 5) {
            ResetSecondaryCounter(6);
            static_cast<MarisaFighter*>(owner)->fieldF12 = 3;
            facing = owner->facing;
        }
        if (owner->spellTimer <= 0 && animationStage < 7) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
            ResetSecondaryCounter(7);
            return;
        }
        if (animationStage == 5) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 2;
            if (x > GeometryConstants::FifteenHundredEighty || x < GeometryConstants::NegativeThreeHundred) {
                static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
                ResetSecondaryCounter(7);
                return;
            }
            if (collisionResult != 0 && collisionResult != 6 && collisionResult != 4) {
                x = facing * FloatConstants::Five + x;
            } else {
                x = facing * FloatConstants::Ten + x;
            }
        }
        if (animationStage == 6) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 3;
            --static_cast<MarisaFighter*>(owner)->fieldF18;
            if (static_cast<MarisaFighter*>(owner)->fieldF14 == 0 || static_cast<MarisaFighter*>(owner)->fieldF18 <= 0) {
                static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
                ResetSecondaryCounter(7);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
            static_cast<MarisaFighter*>(owner)->fieldF12 = 0;
            static_cast<MarisaFighter*>(owner)->fieldF14 = 0;
            return;
        }
        if (animationStage == 5 && animationFrame == 0) {
            ResetSecondaryCounter(4);
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
            collisionResult = 0;
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetSecondaryCounter(6);
        }
        break;

    case 835:
        if (animationStage < 7 || animationStage == 8) {
            x = owner->x;
        }
        if (animationStage < 7 || animationStage == 8) {
            y = (owner->y) + GeometryConstants::Hundred;
        }
        owner->fieldF0C = static_cast<short>(x);
        owner->fieldF0E = static_cast<short>(y);
        static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 3;
        if (static_cast<MarisaFighter*>(owner)->fieldF12 == 2) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 7;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF12 == 3) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 3;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF12 == 6) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = static_cast<MarisaFighter*>(owner)->fieldF10 + 7;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF10 < 0) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = 0;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF10 >= 360) {
            static_cast<MarisaFighter*>(owner)->fieldF10 = 0;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF18 < 0) {
            static_cast<MarisaFighter*>(owner)->fieldF18 = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0DE = 0;
            owner->field314 = 0.0f;
            owner->SpawnBattleEffect(828, x, y, 1, 1);
        }
        if (animationStage == 1 && animationFrame == 0) {
            owner->field314 = 60.0f;
            owner->SpawnBattleEffect(829, x, y, 1, 1);
        }
        if (animationStage == 2 && animationFrame == 0) {
            owner->field314 = 120.0f;
            owner->SpawnBattleEffect(830, x, y, 1, 1);
        }
        if (animationStage == 3 && animationFrame == 0) {
            owner->field314 = 180.0f;
            owner->SpawnBattleEffect(831, x, y, 1, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            owner->field314 = 240.0f;
            owner->SpawnBattleEffect(832, x, y, 1, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            owner->field314 = 300.0f;
            owner->SpawnBattleEffect(833, x, y, 1, 1);
        }
        if (animationStage == 6) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 1;
        }
        if (static_cast<MarisaFighter*>(owner)->fieldF14 == 0 && animationStage < 9) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
            ResetSecondaryCounter(9);
            return;
        }
        if (animationStage == 6 && owner->action == 714 &&
            owner->animationStage == 5) {
            ResetSecondaryCounter(7);
            remainingHits = 20;
            static_cast<MarisaFighter*>(owner)->fieldF12 = 6;
            facing = owner->facing;
            field0DC = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree);
            field0DA = 80;
        }
        if (animationStage == 6 && owner->action == 715 &&
            owner->animationStage == 5) {
            ResetSecondaryCounter(8);
            static_cast<MarisaFighter*>(owner)->fieldF12 = 3;
            facing = owner->facing;
        }
        if (owner->spellTimer <= 0 && animationStage < 9) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
            ResetSecondaryCounter(9);
            return;
        }
        if (animationStage == 7) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 6;
            if (((x > GeometryConstants::FifteenHundredEighty && facing * velocityX > FloatConstants::Zero) ||
                 (x < GeometryConstants::NegativeThreeHundred && facing * velocityX < FloatConstants::Zero) ||
                 (y < GeometryConstants::NegativeThreeHundred && velocityY > FloatConstants::Zero) ||
                 (y > GeometryConstants::TwelveHundredEighty && velocityY < FloatConstants::Zero)) &&
                field0DE > 0) {
                static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
                ResetSecondaryCounter(9);
                return;
            }
            if (collisionResult == 6 && collisionResult != 4) {
                collisionResult = 0;
            }
            if (field0DA == 0) {
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) / GeometryConstants::RadiansPerDegree);
                field0DE = 1;
            }
            --field0DA;
            if (field0DE == 1) {
                field0DA = field0DA + 2;
            }
            SetPolarVelocity(static_cast<float>(field0DC), field0DA * FloatConstants::OneFifth);
            x = facing * velocityX + x;
            y = y - velocityY;
        }
        if (animationStage == 8) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 3;
            --static_cast<MarisaFighter*>(owner)->fieldF18;
            if (static_cast<MarisaFighter*>(owner)->fieldF14 == 0 || static_cast<MarisaFighter*>(owner)->fieldF18 <= 0) {
                static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
            static_cast<MarisaFighter*>(owner)->fieldF12 = 0;
            static_cast<MarisaFighter*>(owner)->fieldF14 = 0;
            return;
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetSecondaryCounter(6);
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetSecondaryCounter(7);
            collisionResult = 0;
        }
        if (animationStage == 9 && animationFrame == 0) {
            ResetSecondaryCounter(8);
        }
        break;

    case 836:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) + FloatConstants::OneTwentieth;
        scaleY = (scaleY) + FloatConstants::OneTwentieth;
        if (color[0] > 20) {
            color[0] -= 20;
            color[1] -= 20;
            color[2] -= 20;
        } else {
            color[0] = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    // 0x345 supplies the origin, facing and scale read by Marisa's chain renderer.
    case 837:
        if ((owner->action == 712 && owner->animationStage < 6) || owner->action == 713) {
            x = owner->x + static_cast<float>(facing * 32);
            y = (owner->y) + GeometryConstants::Ninety;
        }
        if (owner->action != 713 &&
            (owner->action != 712 || owner->animationStage >= 6) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            remainingHits = 1;
            collisionResult = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            static_cast<MarisaFighter*>(owner)->field1006 = 1;
            static_cast<MarisaFighter*>(owner)->field1008 = x;
            static_cast<MarisaFighter*>(owner)->field100C = y;
            static_cast<MarisaFighter*>(owner)->field1014 = facing;
            remainingHits = 1;
            collisionResult = 0;
            if (field0D8 != 1) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 4.0f;
                field0D8 = 1;
                field0DA = 100;
                field0DC = 3500;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
            field0DA = static_cast<short>(field0DA * FloatConstants::NinetyEightHundredths);
            --field0DC;
            scaleY = field0DC * FloatConstants::OneThousandth +
                field0DA * g_MarisaChainJitterAt00659408;
            static_cast<MarisaFighter*>(owner)->field1010 = scaleY;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            color[0] -= 5;
            static_cast<MarisaFighter*>(owner)->field1010 = scaleY;
            if (color[0] < 10) {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            static_cast<MarisaFighter*>(owner)->field1006 = 0;
            ResetSecondaryCounter(25);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 838:
        if ((owner->action == 712 && animationStage < 6) || owner->action == 713) {
            x = owner->x + static_cast<float>(facing * 64);
            y = (owner->y) + GeometryConstants::Ninety;
        }
        if (owner->action != 712 &&
            (owner->action != 713 || owner->animationStage >= 6) &&
            animationStage == 0) {
            ResetSecondaryCounter(1);
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) * FloatConstants::FourFifths;
        scaleY = (scaleY) * FloatConstants::FourFifths;
        if (animationStage > 0 && color[0] > 10) {
            color[0] -= 10;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
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
            rotationY = static_cast<float>(facing * 70);
        }
        scaleX = (scaleX) + FloatConstants::ThreeQuarters;
        scaleY = (scaleY) + FloatConstants::ThreeQuarters;
        if (color[0] > 20) {
            color[0] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 840:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (color[0] > 15) {
            color[0] -= 15;
        } else {
            color[0] = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 841:
        if (field0C8 == FloatConstants::Zero) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF1A);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF26);
        }
        if (field0C8 == FloatConstants::One) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF1C);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF28);
        }
        if (field0C8 == FloatConstants::Two) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF1E);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF2A);
        }
        if (field0C8 == FloatConstants::Three) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF20);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF2C);
        }
        if (field0C8 == FloatConstants::Four) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF22);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF2E);
        }
        if (field0C8 == FloatConstants::Five) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF24);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF30);
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            ++remainingHits;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++remainingHits;
                field0DA = 0;
            }
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            remainingHits = 20;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        if (collisionResult != 0) {
            if (field0DA < 15) {
                ++field0DA;
            } else {
                collisionResult = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
        }
        if (animationStage > 19) {
            if (color[0] > 20) {
                color[0] -= 20;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(20);
        }
        if (animationStage == 20 && field0D8 < 10) {
            ResetSecondaryCounter(12);
            ++field0D8;
        }
        break;

    case 843:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.5f;
            scaleY = 2.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) - FloatConstants::Quarter;
        scaleY = (scaleY) - FloatConstants::Quarter;
        if (color[0] > 25) {
            color[0] -= 25;
        } else {
            color[0] = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 844:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(0, 10) * FloatConstants::OneTenth + FloatConstants::Half;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = RecordedRange(0, 60) - 30;
            field0DA = RecordedRange(15, 30);
        }
        SetPolarVelocity(static_cast<float>(field0D8), static_cast<float>(field0DA));
        rotationZ = (rotationZ) + FloatConstants::Five;
        x = facing * velocityX + x;
        y = y - velocityY;
        if (animationStage > 0) {
            if (color[0] > 12) {
                color[0] -= 12;
                color[1] -= 12;
                color[2] -= 12;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 845:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            field0D8 = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 360));
        }
        ++field0D8;
        rotationZ = (rotationZ) + FloatConstants::One;
        scaleX = (g_MarisaDustGrowthAt006593F8 - field0D8 * FloatConstants::ThreeHundredthsDouble) *
            (field0D8 < 13) + g_MarisaSparkBaseGrowthAt00659430 + scaleX;
        scaleY = (g_MarisaDustGrowthAt006593F8 - field0D8 * FloatConstants::ThreeHundredthsDouble) *
            (field0D8 < 13) + g_MarisaSparkBaseGrowthAt00659430 + scaleY;
        if (animationStage > 0) {
            if (color[0] > 10) {
                color[0] -= 10;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 846:
        if (owner->action == 703 && owner->animationStage > 14 &&
            owner->animationStage < 23) {
            x = owner->x - static_cast<float>(facing * 110);
            y = (owner->y) + GeometryConstants::NinetyFive;
        } else {
            ClearFrameInfo();
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 847:
        if (owner->action != 701 && owner->action != 713) {
            ClearFrameInfo();
            return;
        }
        if (owner->action == 701 || owner->action == 713) {
            x = owner->x - static_cast<float>(facing * 82);
            y = (owner->y) + GeometryConstants::HundredThirtyTwo;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 850:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 49 && owner->action < 150 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            SetPolarVelocity(field0C8, field0D8 * FloatConstants::Half + FloatConstants::Five);
            scaleX = RecordedRange(0, 10) * FloatConstants::OneFortieth + FloatConstants::Half;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / GeometryConstants::RadiansPerDegree;
        }
        ++field0D8;
        if (animationStage < 2) {
            SetPolarVelocity(field0C8, field0D8 * FloatConstants::Half + FloatConstants::Five);
        }
        if (collisionResult != 0 && animationStage == 1) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            ResetSecondaryCounter(2);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            return;
        }
        x = facing * velocityX + x;
        y = y - velocityY;
        if (y - velocityY <= FloatConstants::Zero && animationStage == 1) {
            ResetSecondaryCounter(2);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
            return;
        }
        if (x > GeometryConstants::ThirteenHundredEighty || x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::SixHundredForty || y < GeometryConstants::NegativeHundredTwenty) {
            ClearFrameInfo();
            return;
        }
        if (animationStage > 1) {
            if (color[0] >= 25) {
                color[0] -= 25;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 851:
        if ((owner->action != 751 || (owner->action == 751 && owner->animationStage > 11)) &&
            (owner->action != 752 || (owner->action == 752 && owner->animationStage > 11))) {
            ClearFrameInfo();
            return;
        }
        if ((owner->action == 751 && owner->animationStage < 12) ||
            (owner->action == 752 && owner->animationStage < 12)) {
            x = owner->x - static_cast<float>(facing * 82);
            y = (owner->y) + GeometryConstants::HundredThirtyTwo;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 852:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = static_cast<float>(RecordedRange(0, 360));
            field0D8 = 10;
        }
        scaleX = field0D8 * FloatConstants::OneHundredth + FloatConstants::OneTwentieth + scaleX;
        scaleY = scaleX;
        if (field0D8 > 0) {
            --field0D8;
        }
        if (animationStage > 1) {
            color[0] -= 25;
            color[1] -= 20;
            color[2] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 853:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
        scaleY = scaleX;
        if (field0D8 > 0) {
            --field0D8;
        }
        if (animationStage > 1) {
            color[0] -= 25;
            color[1] -= 20;
            color[2] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 854:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            remainingHits = 1;
            field0D8 = 0;
            PlaySharedSound(4);
        }
        if (collisionResult == 6) {
            collisionResult = 0;
            ++remainingHits;
        }
        if (animationStage == 1 && animationFrame == 0) {
            owner->SpawnBattleEffect(852,
                static_cast<float>(RecordedRange(0, 160)) + x - GeometryConstants::Eighty,
                static_cast<float>(RecordedRange(0, 160)) + y - GeometryConstants::Eighty, facing, 1);
            owner->SpawnBattleEffect(853,
                static_cast<float>(RecordedRange(0, 220)) + x - GeometryConstants::HundredTen,
                static_cast<float>(RecordedRange(0, 220)) + y - GeometryConstants::HundredTen, facing, 1);
            ++field0D8;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (field0D8 > 15 || (field0D8 > 5 && collisionResult != 0)) {
                ClearFrameInfo();
            } else {
                ResetSecondaryCounter(1);
            }
        }
        break;

    case 900:
        if (owner->action == 731 && owner->animationStage > 8 &&
            owner->animationStage < 17) {
            x = owner->x - static_cast<float>(facing * 110);
            y = (owner->y) + GeometryConstants::NinetyFive;
        } else {
            ClearFrameInfo();
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.5f;
            scaleY = 1.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 901:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = RecordedRange(0, 5) * FloatConstants::OneTenth + FloatConstants::Half;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            if (g_OptionsModeAt006714D0 == 0) {
                remainingHits = 0;
            } else {
                remainingHits = 1;
            }
            collisionResult = 0;
            field0D8 = RecordedRange(0, 60) - 30;
            field0DA = RecordedRange(5, 15);
        }
        SetPolarVelocity(static_cast<float>(field0D8), static_cast<float>(field0DA));
        rotationZ = (rotationZ) + FloatConstants::Five;
        x = facing * velocityX + x;
        y = y - velocityY;
        if (animationStage > 1) {
            if (color[0] > 12) {
                color[0] -= 12;
                color[1] -= 12;
                color[2] -= 12;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 910:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (remainingHits == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 911:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (remainingHits == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 912:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (remainingHits == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 913:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (remainingHits == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 921:
        if (owner->action == 751 && owner->animationStage < 12) {
            x = owner->x + static_cast<float>(facing * 32);
            y = (owner->y) + GeometryConstants::Ninety;
            owner->opponentVelocityDeltaX = (facing * owner->opponent->facing) * GeometryConstants::Six *
                (2 * ((owner->opponent->x - owner->x) * facing > FloatConstants::Zero ? 1 : 0) - 1);
            owner->SetCameraShake(3.0f);
        }
        if ((owner->action != 751 || owner->action != 751 || owner->animationStage >= 12) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            remainingHits = 1;
            collisionResult = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            if (field0D8 != 1) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 1.0f;
                field0D8 = 1;
                field0DA = 100;
                field0DC = 2000;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
            field0DA = static_cast<short>(field0DA * FloatConstants::NinetyEightHundredths);
            --field0DC;
            scaleY = field0DC * FloatConstants::OneThousandth +
                field0DA * FloatConstants::OneHundredthDouble;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            color[0] -= 5;
            if (color[0] < 10) {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(25);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 922:
        if (owner->action == 752 && owner->animationStage < 12) {
            x = owner->x + static_cast<float>(facing * 32);
            y = (owner->y) + GeometryConstants::Ninety;
            owner->opponentVelocityDeltaX = (facing * owner->opponent->facing) * GeometryConstants::Six *
                (2 * ((owner->opponent->x - owner->x) * facing > FloatConstants::Zero ? 1 : 0) - 1);
            owner->SetCameraShake(3.0f);
        }
        if ((owner->action != 752 || owner->action != 752 || owner->animationStage >= 12) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            remainingHits = 1;
            collisionResult = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            static_cast<MarisaFighter*>(owner)->field1006 = 1;
            static_cast<MarisaFighter*>(owner)->field1008 = x;
            static_cast<MarisaFighter*>(owner)->field100C = y;
            static_cast<MarisaFighter*>(owner)->field1014 = facing;
            remainingHits = 1;
            collisionResult = 0;
            if (field0D8 != 1) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 2.0f;
                field0D8 = 1;
                field0DA = 100;
                field0DC = 3500;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
            field0DA = static_cast<short>(field0DA * FloatConstants::NinetyEightHundredths);
            --field0DC;
            scaleY = field0DC * FloatConstants::OneThousandth +
                field0DA * g_MarisaChainJitterAt00659408;
            static_cast<MarisaFighter*>(owner)->field1010 = scaleY;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            color[0] -= 5;
            static_cast<MarisaFighter*>(owner)->field1010 = scaleY;
            if (color[0] < 10) {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            static_cast<MarisaFighter*>(owner)->field1006 = 0;
            ResetSecondaryCounter(25);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 923:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            field0DA = static_cast<short>(field0C8 - RecordedRange(0, 40) + GeometryConstants::Twenty);
            field0DC = RecordedRange(0, 60) + 150;
        }
        SetPolarVelocity(static_cast<float>(field0DA), field0DC * FloatConstants::OneTenth);
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (field0DC > 30) {
            field0DC = field0DC - 2;
        }
        if ((remainingHits == 0 || y + velocityY <= FloatConstants::Zero) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 924:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(static_cast<float>(RecordedRange(0, 40) + 70), field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if ((remainingHits == 0 || y + velocityY <= FloatConstants::Zero) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 925:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(static_cast<float>(RecordedRange(0, 40) + 70), field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if ((remainingHits == 0 || y + velocityY <= FloatConstants::Zero) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 926:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.5f;
            scaleY = scaleX;
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = static_cast<float>(RecordedRange(0, 359));
            collisionResult = 0;
            remainingHits = 1;
            field0D8 = 0;
            SetPolarVelocity(static_cast<float>(RecordedRange(0, 40) + 70), field0D8 * FloatConstants::OneTwentieth + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if ((remainingHits == 0 || y + velocityY <= FloatConstants::Zero) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
                scaleY = (scaleY) * FloatConstants::EightyFiveHundredths;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < GeometryConstants::NegativeEighty || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < FloatConstants::Zero || y > GeometryConstants::NineHundredSixty) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 927:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.005f;
            scaleY = 4.0f;
            collisionResult = 0;
            remainingHits = 0;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            owner->PlaySound(0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        --field0DA;
        velocityX = 0.0f;
        if (x < owner->opponent->x - GeometryConstants::Fifty) {
            velocityX = g_OptionsModeAt006714D0 * FloatConstants::Half + FloatConstants::One;
        }
        if (x > (owner->opponent->x) + GeometryConstants::Fifty) {
            velocityX = GeometryConstants::NegativeOne - g_OptionsModeAt006714D0 * FloatConstants::Half;
        }
        if (field0D8 < 120 && scaleX < FloatConstants::OneFortieth) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
        }
        if (field0D8 == 120) {
            remainingHits = 256;
        }
        if (field0D8 > 120 && field0D8 < 241) {
            if (scaleX < FloatConstants::OneAndHalf) {
                scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + GeometryConstants::HundredTwenty) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                collisionResult = 0;
            }
        }
        if (field0D8 == 240) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 240) {
            velocityX = 0.0f;
            remainingHits = 0;
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
            if (color[0] > 10) {
                color[0] -= 10;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 928:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.005f;
            scaleY = 4.0f;
            collisionResult = 0;
            remainingHits = 0;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            owner->PlaySound(0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        --field0DA;
        velocityX = 0.0f;
        if (x < owner->opponent->x - GeometryConstants::Fifty) {
            velocityX = g_OptionsModeAt006714D0 * FloatConstants::Half + FloatConstants::One;
        }
        if (x > (owner->opponent->x) + GeometryConstants::Fifty) {
            velocityX = GeometryConstants::NegativeOne - g_OptionsModeAt006714D0 * FloatConstants::Half;
        }
        if (field0D8 < 120 && scaleX < FloatConstants::OneFortieth) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
        }
        if (field0D8 == 120) {
            remainingHits = 256;
        }
        if (field0D8 > 120 && field0D8 < 321) {
            if (scaleX < FloatConstants::OneAndHalf) {
                scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + GeometryConstants::HundredTwenty) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                collisionResult = 0;
            }
        }
        if (field0D8 == 320) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 320) {
            velocityX = 0.0f;
            remainingHits = 0;
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
            if (color[0] > 10) {
                color[0] -= 10;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 929:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.005f;
            scaleY = 4.0f;
            collisionResult = 0;
            remainingHits = 0;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            owner->PlaySound(0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        --field0DA;
        velocityX = 0.0f;
        if (x < owner->opponent->x - GeometryConstants::Fifty) {
            velocityX = g_OptionsModeAt006714D0 * FloatConstants::Half + FloatConstants::One;
        }
        if (x > (owner->opponent->x) + GeometryConstants::Fifty) {
            velocityX = GeometryConstants::NegativeOne - g_OptionsModeAt006714D0 * FloatConstants::Half;
        }
        if (field0D8 < 120 && scaleX < FloatConstants::OneFortieth) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
        }
        if (field0D8 == 120) {
            remainingHits = 256;
        }
        if (field0D8 > 120 && field0D8 < 321) {
            if (scaleX < FloatConstants::OneAndHalf) {
                scaleX = (scaleX) + FloatConstants::FifteenHundredths;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + GeometryConstants::HundredTwenty) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                collisionResult = 0;
            }
        }
        if (field0D8 == 320) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 320) {
            velocityX = 0.0f;
            remainingHits = 0;
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
            if (color[0] > 10) {
                color[0] -= 10;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 930:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.005f;
            scaleY = 4.0f;
            collisionResult = 0;
            remainingHits = 0;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            owner->PlaySound(0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        --field0DA;
        velocityX = 0.0f;
        if (x < owner->opponent->x - GeometryConstants::Fifty) {
            velocityX = g_OptionsModeAt006714D0 * FloatConstants::Half + FloatConstants::One;
        }
        if (x > (owner->opponent->x) + GeometryConstants::Fifty) {
            velocityX = GeometryConstants::NegativeOne - g_OptionsModeAt006714D0 * FloatConstants::Half;
        }
        if (field0D8 < 120 && scaleX < FloatConstants::OneFortieth) {
            scaleX = (scaleX) + FloatConstants::OneTwoHundredth;
        }
        if (field0D8 == 120) {
            remainingHits = 256;
        }
        if (field0D8 > 120 && field0D8 < 341) {
            if (scaleX < FloatConstants::TwoAndHalf) {
                scaleX = (scaleX) + FloatConstants::OneFifth;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + GeometryConstants::HundredTwenty) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                collisionResult = 0;
            }
        }
        if (field0D8 == 340) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 340) {
            velocityX = 0.0f;
            remainingHits = 0;
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredths;
            if (color[0] > 10) {
                color[0] -= 10;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 990: {
        if (static_cast<MarisaFighter*>(owner)->fieldF32 == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = (owner->y) + GeometryConstants::Hundred;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
            }
            rotationZ = (rotationZ) + FloatConstants::One;
            if (animationStage == 0) {
                if (color[0] < 0xB4) {
                    color[0] = static_cast<unsigned char>(color[0] + 0x19);
                }
                else {
                    color[0] = 0xB4;
                }
                if (static_cast<MarisaFighter*>(owner)->fieldF32 >= 0x78) {
                    ResetSecondaryCounter(1);
                    color[0] = 0xB4;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 0x1E) {
                    color[0] -= 0x1E;
                } else {
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
    }

    case 991: {
        if (static_cast<MarisaFighter*>(owner)->fieldF32 == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = (owner->y) + GeometryConstants::Hundred;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 0;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
            }
            scaleX = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF32) /
                GeometryConstants::Sixty;
            scaleY = scaleX;
            if (animationStage == 0) {
                if (color[0] < 0xE6) {
                    color[0] = static_cast<unsigned char>(color[0] + 0x19);
                }
                else {
                    color[0] = 0xFF;
                }
                if (static_cast<MarisaFighter*>(owner)->fieldF32 >= 0x78) {
                    ResetSecondaryCounter(1);
                    color[0] = 0xFF;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 0x0A) {
                    color[0] -= 0x0A;
                } else {
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
    }

    case 994:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = 110 - RecordedRange(0, 40);
            field0DA = 15 - RecordedRange(0, 7);
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) {
                field0DA = 3;
            }
            SetPolarVelocity(static_cast<float>(field0D8),
                static_cast<float>(field0DA) * FloatConstants::FourFifths);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                owner->opponent->x - x) / GeometryConstants::RadiansPerDegree);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < GeometryConstants::Twenty &&
                x - owner->opponent->x > GeometryConstants::NegativeTwenty &&
                y - owner->opponent->y < GeometryConstants::HundredTwenty &&
                y - owner->opponent->y > GeometryConstants::Eighty) {
                ++owner->fieldEFA;
                PlaySharedSound(0x2E);
                ClearFrameInfo();
                if (owner->opponent->spiritCooldown > 0) {
                    if (owner->opponent->spiritCooldown > 5) {
                        owner->opponent->spiritCooldown =
                            owner->opponent->spiritCooldown - 5;
                    }
                    else {
                        owner->opponent->spiritCooldown = 0;
                    }
                    return;
                }
                if (owner->opponent->spirit < 0x3DE) {
                    owner->opponent->spirit = owner->opponent->spirit + 10;
                }
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->spellDeclarationExpired == 0) {
                        if (owner->opponent->spellPower < FloatConstants::NineHundredNinetyEightAndNineTenths) {
                            owner->opponent->spellPower = (owner->opponent->spellPower) +
                                FloatConstants::Half;
                        }
                        else {
                            owner->opponent->spellPower = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x = x + velocityX;
        y = y - velocityY;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 995:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = static_cast<short>(RecordedRange(0, 360) - 0xB4);
            field0DA = 0x0F;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) {
                field0DA = 3;
            }
            SetPolarVelocity(static_cast<float>(field0D8),
                static_cast<float>(field0DA) * FloatConstants::FourFifths);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                owner->opponent->x - x) / GeometryConstants::RadiansPerDegree);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < GeometryConstants::Twenty &&
                x - owner->opponent->x > GeometryConstants::NegativeTwenty &&
                y - owner->opponent->y < GeometryConstants::HundredTwenty &&
                y - owner->opponent->y > GeometryConstants::Eighty) {
                ClearFrameInfo();
                if (owner->opponent->bombCount < 2) {
                    ++owner->opponent->bombCount;
                }
                else {
                    owner->opponent->score = owner->opponent->score + 0x4E20;
                }
                PlaySharedSound(0x2E);
                return;
            }
        }
        x = x + velocityX;
        y = y - velocityY;
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
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = static_cast<short>(RecordedRange(0, 360) - 0xB4);
            field0DA = 0x0F;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) {
                field0DA = 3;
            }
            SetPolarVelocity(static_cast<float>(field0D8),
                static_cast<float>(field0DA) * FloatConstants::FourFifths);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                owner->opponent->x - x) / GeometryConstants::RadiansPerDegree);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < GeometryConstants::Twenty &&
                x - owner->opponent->x > GeometryConstants::NegativeTwenty &&
                y - owner->opponent->y < GeometryConstants::HundredTwenty &&
                y - owner->opponent->y > GeometryConstants::Eighty) {
                ++owner->fieldEFA;
                PlaySharedSound(0x2E);
                ClearFrameInfo();
                if (owner->opponent->spiritCooldown > 0) {
                    if (owner->opponent->spiritCooldown > 5) {
                        owner->opponent->spiritCooldown =
                            owner->opponent->spiritCooldown - 5;
                    }
                    else {
                        owner->opponent->spiritCooldown = 0;
                        owner->opponent->spirit = 1000;
                    }
                    return;
                }
                if (owner->opponent->spirit < 0x3DE) {
                    owner->opponent->spirit = owner->opponent->spirit + 10;
                }
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->spellDeclarationExpired == 0) {
                        if (owner->opponent->spellPower < FloatConstants::NineHundredNinetyEightAndNineTenths) {
                            owner->opponent->spellPower = (owner->opponent->spellPower) +
                                FloatConstants::Half;
                        }
                        else {
                            owner->opponent->spellPower = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x = x + velocityX;
        y = y - velocityY;
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
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            spriteOffsetZ = 0x4E2;
            rotationX = 0.0f;
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
            scaleX = (static_cast<float>(owner->spellTimer) /
                static_cast<float>(field0D8)) * 2.0f;
            scaleY = (static_cast<float>(owner->spellTimer) /
                static_cast<float>(field0D8)) * 2.0f;
            rotationZ = (rotationZ) + FloatConstants::One;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(10);
            }
        }
        break;

    case 998:
        if (owner->action != 0xD1 && owner->action != 0xD2 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        x = owner->x;
        y = (owner->y) + GeometryConstants::Hundred;
        if (animationStage == 0 && animationFrame == 0) {
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
        scaleX = (scaleX) - FloatConstants::OneFourHundredth;
        scaleY = (scaleY) - FloatConstants::OneFourHundredth;
        rotationZ = (rotationZ) + FloatConstants::One;
        if (animationStage == 2) {
            color[0] -= 12;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 2 && animationFrame == 0) {
            ResetSecondaryCounter(1);
        }
        return;

    default:
        AdvanceNestedFrame();
        break;
    }
}
