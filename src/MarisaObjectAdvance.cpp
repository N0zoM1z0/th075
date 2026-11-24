#include "GameSharedState.hpp"
// Reconstruction of MarisaObject::Advance at 0049C8F0.
#include "CharacterObject.hpp"
#include "MarisaFighter.hpp"

extern const float g_MarisaEffectYOffsetAt00657888;
extern const float g_MarisaBeamYOffsetAt006590A4;
extern const float g_MarisaBeamYOffsetAt00659294;
extern const float g_MarisaBeamFadeAt00659454;
extern const float g_MarisaAuraYOffsetAt00657CF8;
extern const float g_MarisaAuraYOffsetAt0065929C;
extern const float g_MarisaAuraYOffsetAt00658400;
extern const float g_MarisaAuraYOffsetAt006581DC;
extern const float g_MarisaAuraShrinkAt00659090;
extern const float g_MarisaAuraGrowthAt00658348;
extern const float g_MarisaAuraGrowthAt006583FC;
extern const float g_MarisaAuraGrowthAt006590B8;
extern const float g_MarisaAuraGrowthAt006583F8;
extern const float g_MarisaAuraGrowthAt00658350;
extern const float g_MarisaAuraHeightDecayAt00659450;
extern const float g_MarisaAuraHeightScaleAt00659060;
extern const double g_MarisaAuraJitterAt00659448;

extern const float g_MarisaSpiritHorizontalHitLowerAt00659230;
extern const float g_MarisaSpiritHorizontalHitUpperAt0065786C;
extern const double g_MarisaSpiritSpiritGaugeLimitAt00659228;
extern const float g_MarisaSpiritVerticalHitLowerAt00658268;
extern const float g_MarisaSpiritVerticalHitUpperAt006590A8;
extern float __cdecl AngleAt00483300(float y, float x);

extern const float g_MarisaFollowShrinkAt006590BC;
extern const float g_MarisaShotSpeedAt00658044;
extern const float g_MarisaAngleUnitAt00657828;
extern const float g_MarisaTrailTurnAt00657480;
extern const float g_MarisaGroundAt0065782C;
extern const float g_MarisaShotRightLimitAt0065925C;
extern const float g_MarisaShotLeftLimitAt00659258;
extern const float g_MarisaShotUpperLimitAt006583B4;
extern const double g_MarisaSparkBaseGrowthAt00659430;
extern const double g_MarisaSparkInitialGrowthAt00659438;
extern const double g_MarisaSparkGrowthLossAt00659440;
extern const float g_MarisaSparkTurnAt0065747C;
extern const float g_MarisaSparkDriftAt006590B4;
extern const float g_MarisaSparkFastTurnAt00657874;
extern const float g_MarisaFollowYOffsetAt00659138;
extern const float g_MarisaFollowYOffsetAt00658264;

extern const float g_MarisaBombGravityAt00658058;
extern const float g_MarisaFragmentGrowthAt00659428;
extern const float g_MarisaStreakRightLimitAt00659424;
extern const float g_MarisaStreakLeftLimitAt00658344;
extern const float g_MarisaStreakYOffsetAt00659420;
extern const float g_MarisaStreakRightLimitAt006583D8;
extern const float g_MarisaStreakLeftLimitAt0065941C;
extern const float g_MarisaStreakRightLimitAt00659418;
extern const float g_MarisaStreakLeftLimitAt00659414;

extern const float g_MarisaTrackingRightLimitAt00659410;
extern const float g_MarisaTrackingLeftLimitAt00658404;
extern const float g_MarisaTrackingUpperLimitAt00658E80;
extern const float g_MarisaTrackingDriftAt00657850;
extern const float g_MarisaTrackingFadeGrowthAt006578C0;
extern const double g_MarisaChainJitterAt00659408;
extern const float g_MarisaNodeSelectionAt00657D14;

extern const float g_MarisaHaloShrinkAt00657F74;
extern const float g_MarisaHalfAt00657478;
extern const double g_MarisaDustGrowthAt006593F8;
extern const double g_MarisaDustDecayAt00659400;
extern const float g_MarisaFollowYOffsetAt00659280;
extern const float g_MarisaFollowYOffsetAt00659270;
extern const float g_MarisaStarScaleAt006593F4;
extern const float g_MarisaStarUpperLimitAt00657884;
extern const float g_MarisaStarLowerLimitAt0065924C;
extern const float g_MarisaShowerSpreadAt00658268;
extern const float g_MarisaShowerSpreadAt006590AC;

extern const float g_MarisaVolleyLeftLimitAt006593F0;
extern const float g_MarisaVolleyRightLimitAt006593EC;
extern const float g_MarisaVolleyUpperLimitAt0065920C;
extern const float g_MarisaBeamContactForceAt00658290;
extern const float g_MarisaShowerAngleOffsetAt0065786C;
extern const float g_MarisaStormTargetSpacingAt0065788C;
extern const float g_MarisaStormLeftSpeedAt00659268;
extern const float g_MarisaStormScaleLimitAt006581E0;
extern const float g_MarisaStormScaleLimitAt006593E8;
extern const float g_MarisaStormSpreadAt006590A8;

void MarisaObject::Advance()
{
    if (owner->opponent->field3BA != 0) {
        return;
    }
    if (owner->field3BA != 0 && field08A == 0) {
        return;
    }
    if (field082 != 0) {
        --field082;
        return;
    }
    switch (action) {
    case 800:
        if (owner->action == 400 && field0D8 == 0) {
            x = owner->x + static_cast<float>(facing * 100);
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (field07C == 4) {
            field07C = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++field080;
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
            field080 = 5;
            field07C = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C != 0) {
            if (field0DA < 2) {
                ++field0DA;
            } else {
                field07C = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaBeamYOffsetAt006590A4;
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
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (field07C == 4) {
            field07C = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++field080;
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
            field080 = 5;
            field07C = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C != 0) {
            if (field0DA < 2) {
                ++field0DA;
            } else {
                field07C = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaBeamYOffsetAt00659294;
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
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (field07C == 4) {
            field07C = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++field080;
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
            field080 = 5;
            field07C = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (field07C != 0) {
            if (field0DA < 2) {
                ++field0DA;
            } else {
                field07C = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt00657CF8;
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
        scaleX = (scaleX) * g_MarisaAuraShrinkAt00659090;
        scaleY = (scaleY) * g_MarisaAuraShrinkAt00659090;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt00657CF8;
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
        scaleX = (scaleX) + g_MarisaAuraGrowthAt00658348;
        scaleY = (scaleY) + g_MarisaAuraGrowthAt00658348;
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
        scaleX = (scaleX) + g_MarisaAuraGrowthAt006583FC;
        scaleY = (scaleY) + g_MarisaAuraGrowthAt006583FC;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
        }
        if (owner->action != 701 &&
            (owner->action != 700 || owner->animationStage >= 6) &&
            animationStage < 10) {
            ResetSecondaryCounter(animationStage + 10);
            field080 = 1;
            field07C = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
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
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 10) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
            field0DA = static_cast<short>(field0DA * g_MarisaAuraHeightDecayAt00659450);
            --field0DC;
            scaleY = field0DC * g_MarisaAuraHeightScaleAt00659060 +
                field0DA * g_MarisaAuraJitterAt00659448;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt0065929C;
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
        scaleX = (scaleX) * g_MarisaAuraShrinkAt00659090;
        scaleY = (scaleY) * g_MarisaAuraShrinkAt00659090;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt00658400;
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
        scaleX = (scaleX) * g_MarisaAuraShrinkAt00659090;
        scaleY = (scaleY) * g_MarisaAuraShrinkAt00659090;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
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
        scaleX = (scaleX) * g_MarisaAuraShrinkAt00659090;
        scaleY = (scaleY) * g_MarisaAuraShrinkAt00659090;
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
        scaleX = (scaleX) + g_MarisaAuraGrowthAt00658350;
        scaleY = (scaleY) + g_MarisaAuraGrowthAt00658350;
        if (color[0] > 20) {
            color[0] -= 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 811:
        if (field07C == 5) {
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
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(static_cast<float>(field0DC), field0DA * g_MarisaShotSpeedAt00658044);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / g_MarisaAngleUnitAt00657828;
        }
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        RecordedRange(0, 100);
        if (field07C == 1 || field07C == 2 || field07C == 4 ||
            y + velocityY <= g_MarisaGroundAt0065782C) {
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
        SetPolarVelocity(static_cast<float>(field0DC), field0DA * g_MarisaShotSpeedAt00658044);
        x = facing * velocityX + x;
        y = y - velocityY;
        if (x > g_MarisaShotRightLimitAt0065925C || x < g_MarisaShotLeftLimitAt00659258 ||
            y > g_MarisaShotUpperLimitAt006583B4) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(20);
        }
        break;

    case 812:
        if (field07C == 5) {
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
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(static_cast<float>(field0DC), field0DA * g_MarisaShotSpeedAt00658044);
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        rotationZ = (rotationZ) + g_MarisaTrailTurnAt00657480;
        if (field07C == 5) {
            ClearFrameInfo();
            return;
        }
        RecordedRange(0, 100);
        if (field07C == 1 || field07C == 2 || field07C == 4 ||
            y + velocityY <= g_MarisaGroundAt0065782C) {
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
        SetPolarVelocity(static_cast<float>(field0DC), field0DA * g_MarisaShotSpeedAt00658044);
        x = facing * velocityX + x;
        y = y - velocityY;
        if (x > g_MarisaShotRightLimitAt0065925C || x < g_MarisaShotLeftLimitAt00659258 ||
            y > g_MarisaShotUpperLimitAt006583B4) {
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
            field080 = 1;
            field07C = 0;
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
            field080 = 1;
            field07C = 0;
            field0D8 = static_cast<short>(
                AngleAt00483300(velocityY, velocityX) / g_MarisaAngleUnitAt00657828);
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
        scaleX = (scaleX) + g_MarisaAuraGrowthAt00658348;
        scaleY = (scaleY) + g_MarisaAuraGrowthAt00658348;
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
        rotationZ = (rotationZ) + g_MarisaSparkTurnAt0065747C;
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
            scaleX = RecordedRange(25, 75) * g_MarisaShotSpeedAt00658044;
            scaleY = scaleX;
            color[1] = RecordedRange(0, 255);
            color[2] = RecordedRange(0, 255);
            color[3] = RecordedRange(0, 255);
            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }
        x = (x) - g_MarisaSparkDriftAt006590B4;
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        color[0] -= 7;
        scaleX = (scaleX) - g_MarisaShotSpeedAt00658044;
        scaleY = (scaleY) - g_MarisaShotSpeedAt00658044;
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 817:
        facing = owner->facing;
        if (owner->action > 0x95 && owner->action < 0x9A &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + g_MarisaFollowYOffsetAt00659138;
        }
        if (owner->action > 0x99 && owner->action < 0x9E &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + g_MarisaFollowYOffsetAt00658264;
        }
        if (owner->action == 0x9E && animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
        rotationZ = (rotationZ) + g_MarisaTrailTurnAt00657480;
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
        if (field07C == 5) {
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
            field080 = 1;
            field07C = 0;
            velocityX = (field0C8) * g_MarisaSparkDriftAt006590B4;
            velocityY = (field0CC) * g_MarisaSparkDriftAt006590B4;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        velocityY = (velocityY) - g_MarisaBombGravityAt00658058;
        x = facing * velocityX + x;
        y = y + velocityY;
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (RecordedRange(0, 100) < 30) {
            owner->SpawnBattleEffect(816,
                x + static_cast<float>(RecordedRange(-20, 20)),
                y + static_cast<float>(RecordedRange(-20, 20)), facing, 1);
        }
        if (y < g_MarisaGroundAt0065782C || field07C == 4) {
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
        if (field07C == 5) {
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
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(-60.0f, 15.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        velocityY = (velocityY) - g_MarisaAuraGrowthAt00658350;
        x = facing * velocityX + x;
        y = y + velocityY;
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (RecordedRange(0, 100) < 30) {
            owner->SpawnBattleEffect(816,
                x + static_cast<float>(RecordedRange(-20, 20)),
                y + static_cast<float>(RecordedRange(-20, 20)), facing, 1);
        }
        if (y < g_MarisaGroundAt0065782C) {
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
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
        }
        if (owner->action != 701 &&
            (owner->action != 700 || owner->animationStage >= 6) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            field080 = 1;
            field07C = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
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
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
            field0DA = static_cast<short>(field0DA * g_MarisaAuraHeightDecayAt00659450);
            --field0DC;
            scaleY = field0DC * g_MarisaAuraHeightScaleAt00659060 +
                field0DA * g_MarisaAuraJitterAt00659448;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            field080 = 1;
            field07C = 0;
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
        scaleX = (scaleX) + g_MarisaFragmentGrowthAt00659428;
        scaleY = (scaleY) + g_MarisaFragmentGrowthAt00659428;
        color[0] -= 10;
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 823:
        if (owner->action == 400 && field0D8 == 0) {
            x = owner->x + static_cast<float>(facing * 120);
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
        }
        if (field07C == 6) {
            field07C = 0;
            field080 = 1;
        }
        if (owner->action != 400) {
            field0D8 = 1;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
            scaleX = 1.7f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (animationStage == 3 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        scaleX = (scaleX) + g_MarisaShotSpeedAt00658044;
        if (animationStage == 4) {
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            field080 = 1;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = -30.0f;
            velocityY = 10.0f;
            field05C = 0.01f;
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        if (x > g_MarisaStreakRightLimitAt00659424 || x < g_MarisaStreakLeftLimitAt00658344) {
            ClearFrameInfo();
        }
        velocityY = velocityY - field05C;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(12);
        }
        break;

    case 825:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            field0D8 = 1;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
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
            (y) + g_MarisaStreakYOffsetAt00659420, -facing, 1);
        owner->SpawnBattleEffect(844, x - static_cast<float>(facing * 75),
            (y) + g_MarisaStreakYOffsetAt00659420, -facing, 1);
        owner->SpawnAuxEffect(130, x, 0.0f, facing, 1);
        if (facing > 0 && owner->x < x && owner->animationStage == 4 && owner->action == 704) {
            owner->velocityX = 80.0f;
        }
        if (facing < 0 && owner->x > x && owner->animationStage == 4 && owner->action == 704) {
            owner->velocityX = 80.0f;
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        if (x > g_MarisaStreakRightLimitAt006583D8 || x < g_MarisaStreakLeftLimitAt0065941C ||
            owner->animationStage > 4) {
            ClearFrameInfo();
            owner->scriptCounterF02 = 1;
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
            field07C = 0;
        }
        break;

    case 826:
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            field080 = 1;
            field07C = 0;
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

    case 834:
        if (animationStage < 5 || animationStage == 6) {
            x = owner->x;
        }
        if (animationStage < 5 || animationStage == 6) {
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
            field080 = 15;
            static_cast<MarisaFighter*>(owner)->fieldF12 = 2;
            facing = owner->facing;
        }
        if (animationStage == 4 && owner->action == 708 &&
            owner->animationStage == 5) {
            ResetSecondaryCounter(6);
            static_cast<MarisaFighter*>(owner)->fieldF12 = 3;
            facing = owner->facing;
        }
        if (owner->field3A0 <= 0 && animationStage < 7) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
            ResetSecondaryCounter(7);
            return;
        }
        if (animationStage == 5) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 2;
            if (x > g_MarisaTrackingRightLimitAt00659410 || x < g_MarisaTrackingLeftLimitAt00658404) {
                static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
                ResetSecondaryCounter(7);
                return;
            }
            if (field07C != 0 && field07C != 6 && field07C != 4) {
                x = facing * g_MarisaSparkFastTurnAt00657874 + x;
            } else {
                x = facing * g_MarisaTrackingDriftAt00657850 + x;
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
            field07C = 0;
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
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
            field080 = 20;
            static_cast<MarisaFighter*>(owner)->fieldF12 = 6;
            facing = owner->facing;
            field0DC = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + g_MarisaEffectYOffsetAt00657888) - y,
                (owner->opponent->x - x) * facing) / g_MarisaAngleUnitAt00657828);
            field0DA = 80;
        }
        if (animationStage == 6 && owner->action == 715 &&
            owner->animationStage == 5) {
            ResetSecondaryCounter(8);
            static_cast<MarisaFighter*>(owner)->fieldF12 = 3;
            facing = owner->facing;
        }
        if (owner->field3A0 <= 0 && animationStage < 9) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
            ResetSecondaryCounter(9);
            return;
        }
        if (animationStage == 7) {
            static_cast<MarisaFighter*>(owner)->fieldF12 = 6;
            if (((x > g_MarisaTrackingRightLimitAt00659410 && facing * velocityX > g_MarisaGroundAt0065782C) ||
                 (x < g_MarisaTrackingLeftLimitAt00658404 && facing * velocityX < g_MarisaGroundAt0065782C) ||
                 (y < g_MarisaTrackingLeftLimitAt00658404 && velocityY > g_MarisaGroundAt0065782C) ||
                 (y > g_MarisaTrackingUpperLimitAt00658E80 && velocityY < g_MarisaGroundAt0065782C)) &&
                field0DE > 0) {
                static_cast<MarisaFighter*>(owner)->fieldF12 = 99;
                ResetSecondaryCounter(9);
                return;
            }
            if (field07C == 6 && field07C != 4) {
                field07C = 0;
            }
            if (field0DA == 0) {
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + g_MarisaEffectYOffsetAt00657888) - y,
                    (owner->opponent->x - x) * facing) / g_MarisaAngleUnitAt00657828);
                field0DE = 1;
            }
            --field0DA;
            if (field0DE == 1) {
                field0DA = field0DA + 2;
            }
            SetPolarVelocity(static_cast<float>(field0DC), field0DA * g_MarisaAuraGrowthAt00658348);
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
            field07C = 0;
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
        scaleX = (scaleX) + g_MarisaTrackingFadeGrowthAt006578C0;
        scaleY = (scaleY) + g_MarisaTrackingFadeGrowthAt006578C0;
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

    case 837:
        if ((owner->action == 712 && owner->animationStage < 6) || owner->action == 713) {
            x = owner->x + static_cast<float>(facing * 32);
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
        }
        if (owner->action != 713 &&
            (owner->action != 712 || owner->animationStage >= 6) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            field080 = 1;
            field07C = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            static_cast<MarisaFighter*>(owner)->field1006 = 1;
            static_cast<MarisaFighter*>(owner)->field1008 = x;
            static_cast<MarisaFighter*>(owner)->field100C = y;
            static_cast<MarisaFighter*>(owner)->field1014 = facing;
            field080 = 1;
            field07C = 0;
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
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
            field0DA = static_cast<short>(field0DA * g_MarisaAuraHeightDecayAt00659450);
            --field0DC;
            scaleY = field0DC * g_MarisaAuraHeightScaleAt00659060 +
                field0DA * g_MarisaChainJitterAt00659408;
            static_cast<MarisaFighter*>(owner)->field1010 = scaleY;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
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
        scaleX = (scaleX) * g_MarisaAuraShrinkAt00659090;
        scaleY = (scaleY) * g_MarisaAuraShrinkAt00659090;
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
        scaleX = (scaleX) + g_MarisaAuraGrowthAt00658350;
        scaleY = (scaleY) + g_MarisaAuraGrowthAt00658350;
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
        if (field0C8 == g_MarisaGroundAt0065782C) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF1A);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF26);
        }
        if (field0C8 == g_MarisaSparkTurnAt0065747C) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF1C);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF28);
        }
        if (field0C8 == g_MarisaTrailTurnAt00657480) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF1E);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF2A);
        }
        if (field0C8 == g_MarisaAuraYOffsetAt00657CF8) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF20);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF2C);
        }
        if (field0C8 == g_MarisaNodeSelectionAt00657D14) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF22);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF2E);
        }
        if (field0C8 == g_MarisaSparkFastTurnAt00657874) {
            x = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF24);
            y = static_cast<float>(static_cast<MarisaFighter*>(owner)->fieldF30);
        }
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (field07C == 4) {
            field07C = 0;
            ++field0DA;
            if (field0DA > 1) {
                ++field080;
                field0DA = 0;
            }
        }
        if (animationStage == 0 && animationFrame == 0) {
            field0D8 = 0;
            field0DA = 0;
            ResetTransform(-20.0f, 0.0f, 0.0f);
            field080 = 20;
            field07C = 0;
            scaleX = 2.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = 0;
        }
        if (field07C != 0) {
            if (field0DA < 15) {
                ++field0DA;
            } else {
                field07C = 0;
                field0DA = 0;
            }
        }
        if (animationStage > 19) {
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
        scaleX = (scaleX) - g_MarisaHaloShrinkAt00657F74;
        scaleY = (scaleY) - g_MarisaHaloShrinkAt00657F74;
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
            scaleX = RecordedRange(0, 10) * g_MarisaSparkDriftAt006590B4 + g_MarisaHalfAt00657478;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field0D8 = RecordedRange(0, 60) - 30;
            field0DA = RecordedRange(15, 30);
        }
        SetPolarVelocity(static_cast<float>(field0D8), static_cast<float>(field0DA));
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
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
        rotationZ = (rotationZ) + g_MarisaSparkTurnAt0065747C;
        scaleX = (g_MarisaDustGrowthAt006593F8 - field0D8 * g_MarisaDustDecayAt00659400) *
            (field0D8 < 13) + g_MarisaSparkBaseGrowthAt00659430 + scaleX;
        scaleY = (g_MarisaDustGrowthAt006593F8 - field0D8 * g_MarisaDustDecayAt00659400) *
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
            y = (owner->y) + g_MarisaFollowYOffsetAt00659280;
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
            y = (owner->y) + g_MarisaFollowYOffsetAt00659270;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;

    case 850:
        if (field07C == 5) {
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
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(field0C8, field0D8 * g_MarisaHalfAt00657478 + g_MarisaSparkFastTurnAt00657874);
            scaleX = RecordedRange(0, 10) * g_MarisaStarScaleAt006593F4 + g_MarisaHalfAt00657478;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = AngleAt00483300(velocityY, velocityX) / g_MarisaAngleUnitAt00657828;
        }
        ++field0D8;
        if (animationStage < 2) {
            SetPolarVelocity(field0C8, field0D8 * g_MarisaHalfAt00657478 + g_MarisaSparkFastTurnAt00657874);
        }
        if (field07C != 0 && animationStage == 1) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            ResetSecondaryCounter(2);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            return;
        }
        x = facing * velocityX + x;
        y = y - velocityY;
        if (y - velocityY <= g_MarisaGroundAt0065782C && animationStage == 1) {
            ResetSecondaryCounter(2);
            owner->SpawnBattleEffect(815, x, y, facing, 1);
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
            return;
        }
        if (x > g_MarisaShotRightLimitAt0065925C || x < g_MarisaShotLeftLimitAt00659258 ||
            y > g_MarisaStarUpperLimitAt00657884 || y < g_MarisaStarLowerLimitAt0065924C) {
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
            y = (owner->y) + g_MarisaFollowYOffsetAt00659270;
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
        scaleX = field0D8 * g_MarisaShotSpeedAt00658044 + g_MarisaTrackingFadeGrowthAt006578C0 + scaleX;
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
        scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
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
            field080 = 1;
            field0D8 = 0;
            PlaySharedSound(4);
        }
        if (field07C == 6) {
            field07C = 0;
            ++field080;
        }
        if (animationStage == 1 && animationFrame == 0) {
            owner->SpawnBattleEffect(852,
                static_cast<float>(RecordedRange(0, 160)) + x - g_MarisaShowerSpreadAt00658268,
                static_cast<float>(RecordedRange(0, 160)) + y - g_MarisaShowerSpreadAt00658268, facing, 1);
            owner->SpawnBattleEffect(853,
                static_cast<float>(RecordedRange(0, 220)) + x - g_MarisaShowerSpreadAt006590AC,
                static_cast<float>(RecordedRange(0, 220)) + y - g_MarisaShowerSpreadAt006590AC, facing, 1);
            ++field0D8;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (field0D8 > 15 || (field0D8 > 5 && field07C != 0)) {
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
            y = (owner->y) + g_MarisaFollowYOffsetAt00659280;
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
            scaleX = RecordedRange(0, 5) * g_MarisaSparkDriftAt006590B4 + g_MarisaHalfAt00657478;
            scaleY = scaleX;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            if (g_OptionsModeAt006714D0 == 0) {
                field080 = 0;
            } else {
                field080 = 1;
            }
            field07C = 0;
            field0D8 = RecordedRange(0, 60) - 30;
            field0DA = RecordedRange(5, 15);
        }
        SetPolarVelocity(static_cast<float>(field0D8), static_cast<float>(field0DA));
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (field080 == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (field080 == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (field080 == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(field0C8 + field0CC, field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (field080 == 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
            owner->field490 = (facing * owner->opponent->facing) * g_MarisaBeamContactForceAt00658290 *
                (2 * ((owner->opponent->x - owner->x) * facing > g_MarisaGroundAt0065782C ? 1 : 0) - 1);
            owner->SetCameraShake(3.0f);
        }
        if ((owner->action != 751 || owner->action != 751 || owner->animationStage >= 12) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            field080 = 1;
            field07C = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
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
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
            field0DA = static_cast<short>(field0DA * g_MarisaAuraHeightDecayAt00659450);
            --field0DC;
            scaleY = field0DC * g_MarisaAuraHeightScaleAt00659060 +
                field0DA * g_MarisaAuraJitterAt00659448;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaAuraYOffsetAt006581DC;
            owner->field490 = (facing * owner->opponent->facing) * g_MarisaBeamContactForceAt00658290 *
                (2 * ((owner->opponent->x - owner->x) * facing > g_MarisaGroundAt0065782C ? 1 : 0) - 1);
            owner->SetCameraShake(3.0f);
        }
        if ((owner->action != 752 || owner->action != 752 || owner->animationStage >= 12) &&
            animationStage < 25) {
            ResetSecondaryCounter(animationStage + 25);
            field080 = 1;
            field07C = 0;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            static_cast<MarisaFighter*>(owner)->field1006 = 1;
            static_cast<MarisaFighter*>(owner)->field1008 = x;
            static_cast<MarisaFighter*>(owner)->field100C = y;
            static_cast<MarisaFighter*>(owner)->field1014 = facing;
            field080 = 1;
            field07C = 0;
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
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 25) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
            field0DA = static_cast<short>(field0DA * g_MarisaAuraHeightDecayAt00659450);
            --field0DC;
            scaleY = field0DC * g_MarisaAuraHeightScaleAt00659060 +
                field0DA * g_MarisaChainJitterAt00659408;
            static_cast<MarisaFighter*>(owner)->field1010 = scaleY;
        }
        if (animationStage > 9) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            field0DA = static_cast<short>(field0C8 - RecordedRange(0, 40) + g_MarisaShowerAngleOffsetAt0065786C);
            field0DC = RecordedRange(0, 60) + 150;
        }
        SetPolarVelocity(static_cast<float>(field0DA), field0DC * g_MarisaSparkDriftAt006590B4);
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if (field0DC > 30) {
            field0DC = field0DC - 2;
        }
        if ((field080 == 0 || y + velocityY <= g_MarisaGroundAt0065782C) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(static_cast<float>(RecordedRange(0, 40) + 70), field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if ((field080 == 0 || y + velocityY <= g_MarisaGroundAt0065782C) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(static_cast<float>(RecordedRange(0, 40) + 70), field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if ((field080 == 0 || y + velocityY <= g_MarisaGroundAt0065782C) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 1;
            field0D8 = 0;
            SetPolarVelocity(static_cast<float>(RecordedRange(0, 40) + 70), field0D8 * g_MarisaTrackingFadeGrowthAt006578C0 + field0D0);
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        ++field0D8;
        if ((field080 == 0 || y + velocityY <= g_MarisaGroundAt0065782C) && animationStage == 1) {
            ResetSecondaryCounter(2);
            velocityX = 0.0f;
            velocityY = 0.0f;
            return;
        }
        rotationZ = (rotationZ) + g_MarisaSparkFastTurnAt00657874;
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
                scaleY = (scaleY) * g_MarisaBeamFadeAt00659454;
            } else {
                ClearFrameInfo();
                return;
            }
        }
        if (x < g_MarisaVolleyLeftLimitAt006593F0 || x > g_MarisaVolleyRightLimitAt006593EC ||
            y < g_MarisaGroundAt0065782C || y > g_MarisaVolleyUpperLimitAt0065920C) {
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
            field07C = 0;
            field080 = 0;
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
        if (x < owner->opponent->x - g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478 + g_MarisaSparkTurnAt0065747C;
        }
        if (x > (owner->opponent->x) + g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_MarisaStormLeftSpeedAt00659268 - g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478;
        }
        if (field0D8 < 120 && scaleX < g_MarisaStarScaleAt006593F4) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
        }
        if (field0D8 == 120) {
            field080 = 256;
        }
        if (field0D8 > 120 && field0D8 < 241) {
            if (scaleX < g_MarisaStormScaleLimitAt006581E0) {
                scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + g_MarisaStormSpreadAt006590A8) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                field07C = 0;
            }
        }
        if (field0D8 == 240) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 240) {
            velocityX = 0.0f;
            field080 = 0;
            scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
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
            field07C = 0;
            field080 = 0;
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
        if (x < owner->opponent->x - g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478 + g_MarisaSparkTurnAt0065747C;
        }
        if (x > (owner->opponent->x) + g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_MarisaStormLeftSpeedAt00659268 - g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478;
        }
        if (field0D8 < 120 && scaleX < g_MarisaStarScaleAt006593F4) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
        }
        if (field0D8 == 120) {
            field080 = 256;
        }
        if (field0D8 > 120 && field0D8 < 321) {
            if (scaleX < g_MarisaStormScaleLimitAt006581E0) {
                scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + g_MarisaStormSpreadAt006590A8) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                field07C = 0;
            }
        }
        if (field0D8 == 320) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 320) {
            velocityX = 0.0f;
            field080 = 0;
            scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
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
            field07C = 0;
            field080 = 0;
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
        if (x < owner->opponent->x - g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478 + g_MarisaSparkTurnAt0065747C;
        }
        if (x > (owner->opponent->x) + g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_MarisaStormLeftSpeedAt00659268 - g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478;
        }
        if (field0D8 < 120 && scaleX < g_MarisaStarScaleAt006593F4) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
        }
        if (field0D8 == 120) {
            field080 = 256;
        }
        if (field0D8 > 120 && field0D8 < 321) {
            if (scaleX < g_MarisaStormScaleLimitAt006581E0) {
                scaleX = (scaleX) + g_MarisaAuraGrowthAt006583F8;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + g_MarisaStormSpreadAt006590A8) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                field07C = 0;
            }
        }
        if (field0D8 == 320) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 320) {
            velocityX = 0.0f;
            field080 = 0;
            scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
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
            field07C = 0;
            field080 = 0;
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
        if (x < owner->opponent->x - g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478 + g_MarisaSparkTurnAt0065747C;
        }
        if (x > (owner->opponent->x) + g_MarisaStormTargetSpacingAt0065788C) {
            velocityX = g_MarisaStormLeftSpeedAt00659268 - g_OptionsModeAt006714D0 * g_MarisaHalfAt00657478;
        }
        if (field0D8 < 120 && scaleX < g_MarisaStarScaleAt006593F4) {
            scaleX = (scaleX) + g_MarisaAuraGrowthAt006590B8;
        }
        if (field0D8 == 120) {
            field080 = 256;
        }
        if (field0D8 > 120 && field0D8 < 341) {
            if (scaleX < g_MarisaStormScaleLimitAt006593E8) {
                scaleX = (scaleX) + g_MarisaAuraGrowthAt00658348;
            }
            owner->SetCameraShake(4.0f);
            owner->field314 = -90.0f;
            owner->SpawnBattleEffect(923,
                ((x) + g_MarisaStormSpreadAt006590A8) - static_cast<float>(RecordedRange(0, 240)),
                0.0f, facing, 1);
            if (field0DA <= 0) {
                field0DA = 5;
                field07C = 0;
            }
        }
        if (field0D8 == 340) {
            ++owner->scriptCounterF02;
        }
        if (field0D8 > 340) {
            velocityX = 0.0f;
            field080 = 0;
            scaleX = (scaleX) * g_MarisaBeamFadeAt00659454;
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
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
            rotationZ = (rotationZ) + g_MarisaSparkTurnAt0065747C;
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
            y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
                g_MarisaFollowYOffsetAt00658264;
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
                static_cast<float>(field0DA) * g_MarisaAuraShrinkAt00659090);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + g_MarisaEffectYOffsetAt00657888) - y,
                owner->opponent->x - x) / g_MarisaAngleUnitAt00657828);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < g_MarisaSpiritHorizontalHitUpperAt0065786C &&
                x - owner->opponent->x > g_MarisaSpiritHorizontalHitLowerAt00659230 &&
                y - owner->opponent->y < g_MarisaSpiritVerticalHitUpperAt006590A8 &&
                y - owner->opponent->y > g_MarisaSpiritVerticalHitLowerAt00658268) {
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
                    if (owner->opponent->field39C == 0) {
                        if (owner->opponent->field36C < g_MarisaSpiritSpiritGaugeLimitAt00659228) {
                            owner->opponent->field36C = (owner->opponent->field36C) +
                                g_MarisaHalfAt00657478;
                        }
                        else {
                            owner->opponent->field36C = 900.0f;
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
                static_cast<float>(field0DA) * g_MarisaAuraShrinkAt00659090);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + g_MarisaEffectYOffsetAt00657888) - y,
                owner->opponent->x - x) / g_MarisaAngleUnitAt00657828);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < g_MarisaSpiritHorizontalHitUpperAt0065786C &&
                x - owner->opponent->x > g_MarisaSpiritHorizontalHitLowerAt00659230 &&
                y - owner->opponent->y < g_MarisaSpiritVerticalHitUpperAt006590A8 &&
                y - owner->opponent->y > g_MarisaSpiritVerticalHitLowerAt00658268) {
                ClearFrameInfo();
                if (owner->opponent->field366 < 2) {
                    ++owner->opponent->field366;
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
                static_cast<float>(field0DA) * g_MarisaAuraShrinkAt00659090);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + g_MarisaEffectYOffsetAt00657888) - y,
                owner->opponent->x - x) / g_MarisaAngleUnitAt00657828);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < g_MarisaSpiritHorizontalHitUpperAt0065786C &&
                x - owner->opponent->x > g_MarisaSpiritHorizontalHitLowerAt00659230 &&
                y - owner->opponent->y < g_MarisaSpiritVerticalHitUpperAt006590A8 &&
                y - owner->opponent->y > g_MarisaSpiritVerticalHitLowerAt00658268) {
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
                    if (owner->opponent->field39C == 0) {
                        if (owner->opponent->field36C < g_MarisaSpiritSpiritGaugeLimitAt00659228) {
                            owner->opponent->field36C = (owner->opponent->field36C) +
                                g_MarisaHalfAt00657478;
                        }
                        else {
                            owner->opponent->field36C = 900.0f;
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
            field01A = 0x4E2;
            rotationX = 0.0f;
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
            scaleX = (static_cast<float>(owner->field3A0) /
                static_cast<float>(field0D8)) * 2.0f;
            scaleY = (static_cast<float>(owner->field3A0) /
                static_cast<float>(field0D8)) * 2.0f;
            rotationZ = (rotationZ) + g_MarisaSparkTurnAt0065747C;
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
        y = (owner->y) + g_MarisaEffectYOffsetAt00657888;
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
        scaleX = (scaleX) - g_MarisaFollowShrinkAt006590BC;
        scaleY = (scaleY) - g_MarisaFollowShrinkAt006590BC;
        rotationZ = (rotationZ) + g_MarisaSparkTurnAt0065747C;
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
