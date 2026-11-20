// Partial natural-C++ reconstruction of the Yuyuko fighter move state
// machine at 0x00564BE0. Recovered action families retain their observed
// per-state transitions; the shared native default path remains a falsifiable
// fallback for action states that have not yet been reconstructed.
#include "YuyukoFighter.hpp"

extern float g_ThresholdAt0065782C;
extern float g_JumpGroundCorrectionAt00658058;
extern double g_ContactScaleAt006583E8;
extern float g_SubtractAt00657478;
extern double g_RiseAt00658050;
extern float g_ExtraThresholdAt00657D14;
extern float g_ApproachLowerAt00658290;
extern float g_ApproachUpperAt006592A4;
extern float g_StopThresholdAt00657480;
extern float g_ContactProjectionAt00657888;
extern float g_BounceThresholdAt006590C0;
extern float g_BounceScaleAt00657F74;
extern float g_AngleShiftAt00657878;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_BounceXAt006590BC;
extern float g_BounceYAt00658044;
extern float g_F748_SpeedScaleAt006590B8;
extern signed char g_ModeAt006714B4;
extern float g_ReimuLeapDragAt006583FC;
extern float g_ReimuRepeatDragAt00659090;
extern float g_ReimuCommandFrontYAt006590AC;
extern float g_YPlusAt0065929C;
extern float g_YPlusAt00658400;
extern float g_BarrageY1At006591EC;
extern float g_BarrageYAt00659B70;
extern float g_BarrageYAt006595B4;
extern float g_BarrageYAt00659290;
extern float g_BarrageYAt00659298;
extern float g_RepeatScaleAt006583E0;
extern float g_RepeatScaleAt00658348;
extern float g_BarrageXOffsetAt00657874;
extern float g_Stage700EffectYOffsetAt00659460;
extern float g_SpecialMoveDragAt00659888;
extern float g_RadialPatternYOffsetAt00659274;
extern float g_Stage2BFYOffsetAt00658398;
extern float g_Stage2BFY2At00659B6C;
extern float g_Stage2DAEffectYOffsetAt0065908C;
extern signed char g_StateRepeatLevelAt006714D0;
extern float g_ThousandAt006583B4;
extern float g_YuyukoChaseDivisorAt0065788C;
extern float g_YuyukoFanUpperYAt006593D0;
extern float g_YuyukoFanLeftXAt00657D10;
extern float g_YuyukoFanLowerYAt00659238;
extern float g_YuyukoFanRightXAt00659B68;
extern float g_YuyukoFanSpeedScaleAt006590B4;
extern float g_YuyukoFanSpawnXOffsetAt0065784C;
extern float g_YuyukoAnglePeriodAt00657864;
extern float g_YuyukoAngleUpperWrapAt006595E4;
extern float g_CardGaugeStepAt0065747C;

void YuyukoFighter::Advance() {
    if (field082 != 0 || opponent->field3BA != 0)
        return;

    switch (action) {
    case 0:
    case 2:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (g_ThresholdAt0065782C < velocityX) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (g_ThresholdAt0065782C < velocityX) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        AdvanceNestedFrame();
        return;

    case 1:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (g_ThresholdAt0065782C < velocityX) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (g_ThresholdAt0065782C < velocityX) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;

    case 3:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (g_ThresholdAt0065782C < velocityX) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (g_ThresholdAt0065782C < velocityX) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;

    case 4:
        velocityX = 4.0f;
        AdvanceNestedFrame();
        return;

    case 5:
        velocityX = -4.0f;
        AdvanceNestedFrame();
        return;

    case 6:
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 3 || field3AC > 0)) {
            ResetPrimaryCounters(0xCC);
        } else {
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y <= g_ThresholdAt0065782C ||
                    ((velocityY -= field05C), y + velocityY <= g_ThresholdAt0065782C)) {
                if (animationStage == 2 && velocityY < g_ExtraThresholdAt00657D14)
                    ResetSecondaryCounter(3);
                ++animationFrame;
                if (animationFrame >= animationFrameCount) {
                    animationFrame = 0;
                    ++animationStage;
                    if (animationStage == 2) {
                        velocityX = 0.0f;
                        velocityY = 12.0f;
                        field05C = 0.4f;
                    }
                    if (animationStageCount <= animationStage)
                        animationStage -= 2;
                    BindAnimation();
                }
            } else {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
            }
        }
        return;

    case 7:
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 5 || field3AC > 0)) {
            ResetPrimaryCounters(0xCD);
        } else {
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y <= g_ThresholdAt0065782C ||
                    ((velocityY -= field05C), y + velocityY <= g_ThresholdAt0065782C)) {
                if (animationStage == 2 && velocityY < g_ExtraThresholdAt00657D14)
                    ResetSecondaryCounter(3);
                ++animationFrame;
                if (animationFrame >= animationFrameCount) {
                    animationFrame = 0;
                    ++animationStage;
                    if (animationStage == 2) {
                        velocityX = 4.0f;
                        velocityY = 12.0f;
                        field05C = 0.4f;
                    }
                    if (animationStageCount <= animationStage)
                        animationStage -= 2;
                    BindAnimation();
                }
            } else {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
            }
        }
        return;

    case 8:
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 4 || field3AC > 0)) {
            ResetPrimaryCounters(0xCE);
        } else {
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y <= g_ThresholdAt0065782C ||
                    ((velocityY -= field05C), y + velocityY <= g_ThresholdAt0065782C)) {
                ++animationFrame;
                if (animationFrame >= animationFrameCount) {
                    animationFrame = 0;
                    ++animationStage;
                    if (animationStage == 2) {
                        velocityX = -4.0f;
                        velocityY = 12.0f;
                        field05C = 0.4f;
                    }
                    if (animationStageCount <= animationStage)
                        animationStage -= 2;
                    BindAnimation();
                }
            } else {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
            }
        }
        return;

    case 9:
        if (field05C == g_ThresholdAt0065782C)
            field05C = 0.6f;
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            if (AdvanceNestedFrame() == animationStageCount)
                ResetSecondaryCounter(0);
        } else {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
        }
        return;

    case 10:
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(inputY == 0 ? 0 : 1);
        return;
    case 0x32:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;

    case 0x33:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x34:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x35:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage != 7 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x38:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x39:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x3A:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x3B:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage != 7 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x3E:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x3F:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x40:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x41:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage != 7 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x46:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY += field098;
            if (velocityY < g_ApproachLowerAt00658290)
                velocityY = 6.0f;
            field05C = 0.8f;
            if (g_ApproachUpperAt006592A4 < velocityY)
                velocityY = 25.0f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x47:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x48:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 1.3f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x49:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage != 1 || animationFrame != 0 || velocityY == 0.0f)
            return;
        ResetSecondaryCounter(velocityX == 0.0f ? 3 : 2);
        return;

    case 0x4A:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        if (CheckHorizontalLimits() && velocityX <= g_BounceThresholdAt006590C0) {
            ResetPrimaryCounters(0x4C);
            velocityX = -velocityX * g_BounceScaleAt00657F74;
            velocityY = 15.0f;
            field05C = 0.5f;
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            PlaySharedSound(0x16);
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;

    case 0x4C:
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }
        rotationZ += g_AngleShiftAt00657878;
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            PlaySharedSound(0x16);
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            rotationZ = 0.0f;
            SetCameraShake(2.0f);
            ClearTransformFlag();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        return;

    case 0x58:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -field094;
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x59);
            SetCameraShake(3.0f);
            PlaySharedSound(0x16);
            for (int effectIndex58 = 0; effectIndex58 < 10; ++effectIndex58)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA < 26)
                return;
            fieldEFA = 0;
            SpawnBattleEffect(0x3E3, x, y, 1, 1);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage != 1 || animationFrame != 0 || velocityY == 0.0f)
            return;
        ResetSecondaryCounter(velocityX == 0.0f ? 3 : 2);
        return;

    case 0x59:
        if (animationStage == 3) {
            rotationZ += g_F728_RandomOffsetYAt00657858;
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
                scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x61);
                rotationZ = 0.0f;
                SetCameraShake(2.0f);
                ClearTransformFlag();
                PlaySharedSound(0x16);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(3);
            return;
        }
        if (animationStage != 3 || animationFrame != 0)
            return;
        velocityX = scriptCounterF00 * g_BounceXAt006590BC;
        velocityY = -scriptCounterF02 * g_BounceYAt00658044;
        field05C = 0.7f;
        ResetTransform(0.0f, 95.0f, 0.0f);
        return;

    case 0x5D:
    case 0x5E:
        if (animationStage < 7 && y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (opponent->x < x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityY = 8.0f;
            velocityX = action == 0x5D ? 13.5f : -11.5f;
            field05C = action == 0x5D ? 0.6f : 0.5f;
        }
        if (animationStage != 7 || animationFrame != 0)
            return;
        ResetSecondaryCounter(5);
        return;

    case 0x5F:
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(3);
            if (inputY > 0)
                ResetPrimaryCounters(2);
        }
        if (animationStage != animationStageCount - 1)
            return;
        if (opponent->x < x)
            facing = -1;
        if (opponent->x > x)
            facing = 1;
        return;

    case 0x60:
        if (0 < facing * inputX &&
                (inputA != 0 || inputB != 0 || inputC != 0 || inputD != 0))
            scriptCounterF00 = 1;
        if (facing * inputX < 0 &&
                ((inputA != 0 || inputB != 0) || (inputC != 0 || inputD != 0)))
            scriptCounterF00 = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int effectIndex60 = 0; effectIndex60 < 10; ++effectIndex60)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage == 2 || animationStage == 3 || animationStage == 4) {
            velocityY -= field05C;
            if (y + velocityY < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF != 0)
                return;
            ResetPrimaryCounters(99);
            return;
        }
        if (animationStage != 2 || animationFrame != 0)
            return;
        velocityX = scriptCounterF00 * g_F748_SpeedScaleAt006590B8;
        velocityY = -scriptCounterF02 * g_F748_SpeedScaleAt006590B8;
        field05C = 2.0f;
        return;

    case 0x61:
        if (0 < facing * inputX &&
                ((inputA != 0 || inputB != 0) || (inputC != 0 || inputD != 0)))
            scriptCounterF00 = 1;
        if (facing * inputX < 0 &&
                (((inputA != 0 || inputB != 0) || inputC != 0) || inputD != 0))
            scriptCounterF00 = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int effectIndex61 = 0; effectIndex61 < 10; ++effectIndex61)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage == 2 || animationStage == 3 || animationStage == 4) {
            velocityY -= field05C;
            if (y + velocityY < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF != 0)
                return;
            ResetPrimaryCounters(99);
            return;
        }
        if (animationStage != 2 || animationFrame != 0)
            return;
        velocityX = scriptCounterF00 * g_F748_SpeedScaleAt006590B8;
        velocityY = -scriptCounterF02 * g_F748_SpeedScaleAt006590B8;
        field05C = 2.0f;
        return;

    case 0x62:
        if (0 < facing * inputX &&
                (inputA != 0 || inputB != 0 || inputC != 0 || inputD != 0))
            scriptCounterF00 = 1;
        if (facing * inputX < 0 &&
                (inputA != 0 || inputB != 0 || inputC != 0 || inputD != 0))
            scriptCounterF00 = 2;
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0x5F);
        if (scriptCounterF00 == 1)
            ResetPrimaryCounters(0x5D);
        if (scriptCounterF00 != 2)
            return;
        ResetPrimaryCounters(0x5E);
        return;

    case 99:
        if (g_ModeAt006714B4 == 3 && field2CD != 0) {
            if (animationStage > 1 && field39D > 0 && opponent->action < 150 &&
                    field32A[field39D] == 2) {
                ResetPrimaryCounters(0x31C);
                if (field370[field39D] != 4)
                    return;
                ResetPrimaryCounters(0x302);
                return;
            }
            if (animationStage > 0 && field39D > 0 && opponent->action < 150 &&
                    field32A[field39D] == 1) {
                ResetPrimaryCounters(0x31C);
                return;
            }
            if (animationStage > 1 && field39D > 0 && opponent->action < 150 &&
                    field32A[field39D] == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        } else if (animationStage == 2 && field39D > 0 && opponent->action < 150) {
            ResetPrimaryCounters(0x5F);
            field3CF = 1;
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(2);
        return;

    case 0x12D:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (animationStage > 3 && animationStage < 15) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(15);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 5.0f;
            velocityY = 10.0f;
            field05C = 0.8f;
            PlaySound(0x0C);
            SpawnBattleEffect(0x32F, x, y + g_ContactProjectionAt00657888, facing, 1);
        }
        if (animationStage != 15 || animationFrame != 0)
            return;
        ResetSecondaryCounter(14);
        return;

    case 0x12E:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 2;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1B);
        if (animationStage != 1 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x34D, x, y, facing, 1);
        return;

    case 0x12F:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage != 2 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x34F, x, y, facing, 1);
        return;

    case 0x135:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage != 3 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x349, facing * 20.0f + x,
            y + g_F728_RandomOffsetYAt00657858, facing, 1);
        PlaySound(0x0C);
        return;

    case 0x136:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 6 && animationFrame == 0)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x335, facing * 20.0f + x,
                y + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(0x0C);
        }
        if (animationStage != 6 || animationFrame != 0)
            return;
        velocityX = 27.0f;
        return;

    case 0x130:
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage != 2 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x327, facing * 3.0f + x,
            y + g_ReimuCommandFrontYAt006590AC, facing, 1);
        PlaySound(0x0C);
        return;

    case 0x131:
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 4;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationFrame == 0 && animationStage < 9)
            field07C = 0;
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage != 4 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x34E, x, y, facing, 1);
        return;

    case 0x133:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            field080 = 1;
            field07C = 0;
            ClearMotionFields();
        }
        if ((animationStage == 2 || animationStage == 3 || animationStage == 5 ||
                animationStage == 6 || animationStage == 7) && animationFrame == 0)
            velocityX = 0.0f;
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
            PlaySound(0x0C);
            SpawnBattleEffect(0x32E, facing * 20.0f + x, 125.0f, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if ((animationStage == 2 || animationStage == 3 || animationStage == 5 ||
                animationStage == 6 || animationStage == 7) && animationFrame == 0)
            velocityX = 20.0f;
        if (animationStage != 7 || animationFrame != 0)
            return;
        velocityX = 20.0f;
        return;

    case 0x134:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0 && animationStage < 2) {
            velocityX -= g_ReimuLeapDragAt006583FC;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -15.0f;
        if (velocityX < g_ThresholdAt0065782C && animationStage > 1) {
            velocityX += g_ReimuRepeatDragAt00659090;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -50.0f;
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage != 7 || animationFrame != 0)
            return;
        velocityX = 0.0f;
        return;

    case 0x187:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0 && y == g_ThresholdAt0065782C) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage > 3 && animationStage < 15) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(15);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationFrame == 0 && animationStage < 10)
            field07C = 0;
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 10.0f;
            field05C = 0.8f;
            SpawnBattleEffect(0x32F, x, y + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(0x0C);
        }
        if (animationStage != 15 || animationFrame != 0)
            return;
        ResetSecondaryCounter(14);
        return;

    case 0x188:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 4 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x335, facing * 20.0f + x,
            y + g_ContactProjectionAt00657888, facing, 1);
        PlaySound(0x0C);
        return;

    case 0x189:
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 1;
            field07C = 0;
            field05C = 0.0f;
            velocityY = 0.0f;
            velocityX = 10.0f;
        }
        if (g_ThresholdAt0065782C < velocityX)
            velocityX -= g_ReimuLeapDragAt006583FC;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage != 2 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x34F, x, y, facing, 1);
        return;

    case 0x18A:
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            velocityX = 15.0f;
            scriptCounterF00 = 0;
        }
        velocityX -= g_JumpGroundCorrectionAt00658058;
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 5 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x327, facing * 0x97 + x,
            y + g_YPlusAt0065929C, facing, 1);
        return;

    case 0x18B:
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            velocityX = 10.0f;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
            field080 = 1;
            field07C = 0;
        }
        if (animationStage != 6 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x328, (static_cast<int>(facing) << 7) + x,
            y + g_YPlusAt00658400, facing, 1);
        return;

    case 0x191:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 8 || animationFrame != 0)
            return;
        UpdateGaugeTimer(0xFA);
        PlaySound(0);
        for (int burstIndex191 = 0; burstIndex191 < 8; ++burstIndex191) {
            field318 = static_cast<float>(burstIndex191 * 2 + 2);
            SpawnBattleEffect(0x33E, facing * 50.0f + x,
                y + g_BarrageY1At006591EC, facing, 1);
        }
        return;

    case 0x192:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field07C = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 3 && animationStage < 15) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(15);
                return;
            }
        }
        if (animationStage > 3 && animationStage < 11) {
            --scriptCounterF02;
            if (scriptCounterF02 < 1) {
                field318 = 1.0f;
                field314 = 0.0f;
                PlaySound(0);
                UpdateGaugeTimer(40);
                SpawnBattleEffect(800, x, y + g_ReimuCommandFrontYAt006590AC, facing, 1);
                scriptCounterF02 = 4;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 10.0f;
            field05C = 0.3f;
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        if (animationStage != 15 || animationFrame != 0)
            return;
        ResetSecondaryCounter(14);
        return;

    case 0x194:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX *= g_RepeatScaleAt006583E0;
            velocityY *= g_RepeatScaleAt006583E0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 16)
            velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage < 8 || scriptCounterF00 > 0 || scriptCounterF02 > 2)
            return;
        PlaySound(0);
        scriptCounterF00 = 15;
        ++scriptCounterF02;
        UpdateGaugeTimer(100);
        for (int burstIndex194 = 0; burstIndex194 < 5; ++burstIndex194) {
            field318 = 1.0f;
            field314 = static_cast<float>(burstIndex194 * -20 + 40);
            SpawnBattleEffect(0x322, facing * 50.0f + x,
                y + g_BarrageY1At006591EC, facing, 1);
        }
        return;

    case 0x196:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(10);
        if (animationStage < 6 || scriptCounterF00 > 0 || scriptCounterF02 > 4)
            return;
        field314 = static_cast<float>(scriptCounterF02 * -10 + 10);
        field318 = 10.0f;
        SpawnBattleEffect(0x342, facing * 105.0f + x,
            y + g_BarrageYAt00659B70, facing, 1);
        UpdateGaugeTimer(30);
        scriptCounterF00 = 5;
        ++scriptCounterF02;
        return;

    case 0x197:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(10);
        if (animationStage < 6 || scriptCounterF00 > 0 || scriptCounterF02 > 4)
            return;
        field314 = static_cast<float>(scriptCounterF02 * 10 + 10);
        field318 = 10.0f;
        SpawnBattleEffect(0x342, facing * 65.0f + x,
            y + g_BarrageYAt006595B4, facing, 1);
        UpdateGaugeTimer(30);
        scriptCounterF00 = 5;
        ++scriptCounterF02;
        return;

    case 0x198:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(10);
        if (animationStage < 6 || scriptCounterF00 > 0 || scriptCounterF02 > 4)
            return;
        field314 = static_cast<float>(scriptCounterF02 * 10 + 30);
        field318 = 10.0f;
        SpawnBattleEffect(0x342, facing * 65.0f + x,
            y + g_BarrageYAt006595B4, facing, 1);
        UpdateGaugeTimer(30);
        scriptCounterF00 = 5;
        ++scriptCounterF02;
        return;

    case 0x19A:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX *= g_RepeatScaleAt00658348;
            velocityY *= g_RepeatScaleAt00658348;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            fieldF06 = 0;
        }
        if (animationStage > 7) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage != 5 || animationFrame != 0)
            return;
        PlaySound(10);
        scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
        scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
        UpdateGaugeTimer(150);
        for (int burstIndex19A = 0; burstIndex19A < 7; ++burstIndex19A) {
            field314 = static_cast<float>(30 - burstIndex19A * 10);
            field318 = 10.0f;
            SetPolarVelocity(field314, 80.0f);
            SpawnBattleEffect(0x342,
                (g_BarrageXOffsetAt00657874 + velocityX) * facing + x,
                (y + g_BarrageYAt00659290) - velocityY, facing, 1);
        }
        velocityX = static_cast<float>(scriptCounterF00) * g_BounceYAt00658044;
        velocityY = static_cast<float>(scriptCounterF02) * g_BounceYAt00658044;
        return;

    case 0x19C:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (animationStage > 7 && scriptCounterF00 < 1 && scriptCounterF02 < 5) {
            SpawnBattleEffect(0x347, facing * 50.0f + x,
                y + g_BarrageY1At006591EC, facing, 1);
            ++scriptCounterF02;
            scriptCounterF00 = 10;
            UpdateGaugeTimer(30);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 8 || animationFrame != 0)
            return;
        PlaySound(10);
        return;

    case 0x19E:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0 && animationStage < 2) {
            velocityX -= g_ReimuLeapDragAt006583FC;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -15.0f;
        if (velocityX < g_ThresholdAt0065782C && animationStage > 1) {
            velocityX += g_ReimuRepeatDragAt00659090;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -50.0f;
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage != 7 || animationFrame != 0)
            return;
        velocityX = 0.0f;
        return;

    case 0x1A0:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX *= g_RepeatScaleAt006583E0;
            velocityY *= g_RepeatScaleAt006583E0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 16)
            velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
        }
        --scriptCounterF00;
        if (animationStage > 7 && scriptCounterF00 < 1 && scriptCounterF02 < 5) {
            SpawnBattleEffect(0x347, facing * 50.0f + x,
                y + g_BarrageY1At006591EC, facing, 1);
            ++scriptCounterF02;
            scriptCounterF00 = 10;
            UpdateGaugeTimer(30);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage != 8 || animationFrame != 0)
            return;
        PlaySound(10);
        return;

    case 700:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x73, x, y + g_Stage700EffectYOffsetAt00659460,
                facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(4);
            for (int burstIndex700 = 0; burstIndex700 < 12; ++burstIndex700) {
                field314 = static_cast<float>(burstIndex700 * 30);
                field318 = 8.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);

                field314 = static_cast<float>(burstIndex700 * -30);
                field318 = 8.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);

                field314 = static_cast<float>(burstIndex700 * 30);
                field318 = 7.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);

                field314 = static_cast<float>(burstIndex700 * -30);
                field318 = 7.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        if (animationStage != 12 || animationFrame != 0 || scriptCounterF02 > 1)
            return;
        ++scriptCounterF02;
        ResetSecondaryCounter(10);
        return;

    case 0x1F5:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (g_ThresholdAt0065782C < velocityX && animationStage > 5) {
            velocityX -= g_SpecialMoveDragAt00659888;
            if (velocityX < g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (animationStage > 5 && animationStage < 10) {
            --fieldF04;
            if (fieldF04 < 1) {
                fieldF04 = 3;
                SpawnBattleEffect(0x343, facing * 50.0f + x,
                    y + g_BarrageYAt00659298, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            velocityX = 12.0f;
            PlaySound(11);
        }
        if (animationStage == 4 && animationFrame == 0 && scriptCounterF02 < 2) {
            ++scriptCounterF02;
            ResetSecondaryCounter(2);
        }
        if (animationStage == 6 && animationFrame == 0)
            PlaySound(0);
        if (animationStage != 10 || animationFrame != 0 || scriptCounterF00 > 0)
            return;
        ResetSecondaryCounter(6);
        ++scriptCounterF00;
        return;

    case 0x252:
        if (animationStage == 0 && animationFrame == 0) {
            --field366;
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (spiritCooldown == 0 && field07C == 1)
            spirit = 1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 4)
            return;
        if (animationFrame != 0)
            return;
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        PlaySharedSound(0x21);
        opponent->fieldEFA = 0;
        return;

    case 0x253:
        if (animationStage == 0 && animationFrame == 0) {
            --field366;
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (spiritCooldown == 0 && field07C == 1)
            spirit = 1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 4)
            return;
        if (animationFrame != 0)
            return;
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        PlaySharedSound(0x21);
        opponent->fieldEFA = 0;
        return;

    case 0x254:
        if (animationStage == 0 && animationFrame == 0) {
            --field366;
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 5)
            return;
        if (animationFrame != 0)
            return;
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        PlaySharedSound(0x21);
        opponent->fieldEFA = 0;
        return;

    case 0x255:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0)
            SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        if (animationStage != 8 || animationFrame != 0 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
        return;

        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0)
            SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        if (animationStage != 8 || animationFrame != 0 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(6);
        return;

    case 0x256:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage != 5 || animationFrame != 0)
            return;
        SpawnAuxEffect(0x37, x, y + g_ContactProjectionAt00657888, facing, 1);
        return;

    case 600:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(1);
            UpdateGaugeTimer(250);
            for (int burstIndex600 = 0; burstIndex600 < 5; ++burstIndex600) {
                field314 = static_cast<float>(burstIndex600 * 20);
                field318 = 5.0f;
                SpawnBattleEffect(0x32C, facing * 43.0f + x,
                    y + g_BarrageYAt006595B4, facing, 1);
            }
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x259:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            PlaySound(1);
            for (int burstIndex259 = 0; burstIndex259 < 5; ++burstIndex259) {
                field314 = static_cast<float>(burstIndex259 * 20 + 50);
                field318 = 5.0f;
                SpawnBattleEffect(0x330, facing * 43.0f + x,
                    y + g_BarrageYAt006595B4, facing, 1);
            }
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x25A:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(1);
            UpdateGaugeTimer(250);
            for (int burstIndex25A = 0; burstIndex25A < 5; ++burstIndex25A) {
                field314 = static_cast<float>(burstIndex25A * 20 + 110);
                field318 = 5.0f;
                SpawnBattleEffect(0x331, facing * 43.0f + x,
                    y + g_BarrageYAt006595B4, facing, 1);
            }
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x25F:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x336, facing * 105.0f + x,
                y + g_BarrageYAt00659B70, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x260:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x339, facing * 105.0f + x,
                y + g_BarrageYAt00659B70, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x261:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX *= g_RepeatScaleAt00658348;
            velocityY *= g_RepeatScaleAt00658348;
        }
        if (animationStage > 15)
            velocityY -= field05C;
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x336, facing * 85.0f + x,
                y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(9);
        return;

    case 0x262:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX *= g_RepeatScaleAt00658348;
            velocityY *= g_RepeatScaleAt00658348;
        }
        if (animationStage > 15)
            velocityY -= field05C;
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x339, facing * 85.0f + x,
                y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(9);
        return;

    case 0x263:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 0;
            field080 = 8;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            for (int radialIndex263 = 0; radialIndex263 < 6; ++radialIndex263) {
                field318 = facing * 67.0f + x;
                field31C = y + g_RadialPatternYOffsetAt00659274;
                field314 = static_cast<float>(radialIndex263 * 60);
                SpawnBattleEffect(0x33F, facing * 67.0f + x,
                    y + g_RadialPatternYOffsetAt00659274, facing, 1);
            }
            PlaySound(3);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 3) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            field07C = 1;
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        if (animationFrame != 0 || animationStage > 8)
            return;
        field07C = 0;
        return;

    case 0x264:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 0;
            field080 = 10;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            for (int radialIndex264 = 0; radialIndex264 < 8; ++radialIndex264) {
                field318 = facing * 67.0f + x;
                field31C = y + g_RadialPatternYOffsetAt00659274;
                field314 = static_cast<float>(radialIndex264 * 45);
                SpawnBattleEffect(0x346, facing * 67.0f + x,
                    y + g_RadialPatternYOffsetAt00659274, facing, 1);
            }
            PlaySound(3);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 5) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            field07C = 1;
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 4) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        if (animationFrame != 0 || animationStage > 8)
            return;
        field07C = 0;
        return;

    case 0x265:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            field080 = 10;
            field080 = 0;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            for (int radialIndex265 = 0; radialIndex265 < 8; ++radialIndex265) {
                field314 = static_cast<float>(radialIndex265 * 45);
                field318 = facing * 67.0f + x;
                field31C = y + g_RadialPatternYOffsetAt00659274;
                SpawnBattleEffect(0x346, facing * 67.0f + x,
                    y + g_RadialPatternYOffsetAt00659274, facing, 1);
            }
            PlaySound(3);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 1) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            field07C = 1;
        }
        if (animationStage != 11 || animationFrame != 0 || scriptCounterF00 > 6)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
        return;

    case 0x2BD:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x73, x, y + g_Stage700EffectYOffsetAt00659460,
                facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            for (int burstIndex2BD = 0; burstIndex2BD < 12; ++burstIndex2BD) {
                field314 = static_cast<float>(burstIndex2BD * 30);
                field318 = 8.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2BD * -30);
                field318 = 8.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2BD * 30);
                field318 = 7.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2BD * -30);
                field318 = 7.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x323, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        if (animationStage != 12 || animationFrame != 0 || scriptCounterF02 > 1)
            return;
        ++scriptCounterF02;
        ResetSecondaryCounter(10);
        return;

    case 0x2BE:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x73, x, y + g_BarrageY1At006591EC, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(6);
            SpawnBattleEffect(0x326, x, y, facing, 1);
        }
        if (animationStage != 11 || animationFrame != 0 || scriptCounterF00 > 5)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
        return;

    case 0x2BF:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x73, facing * 42.0f + x,
                y + g_Stage2BFYOffsetAt00658398, facing, 1);
        }
        if (animationStage != 7 || animationFrame != 0)
            return;
        PlaySound(8);
        UpdateGaugeTimer(500);
        SpawnBattleEffect(0x328, facing * 83.0f + x,
            y + g_Stage2BFY2At00659B6C, facing, 1);
        return;

    case 0x2C0:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x74, x, y + g_Stage700EffectYOffsetAt00659460,
                facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(300);
            PlaySound(5);
            for (int burstIndex2C0 = 0; burstIndex2C0 < 12; ++burstIndex2C0) {
                field314 = static_cast<float>(burstIndex2C0 * 30);
                field318 = 9.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x340, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2C0 * -30);
                field318 = 9.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x340, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2C0 * 30);
                field318 = 8.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x340, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2C0 * -30);
                field318 = 8.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x340, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(300);
            PlaySound(5);
            for (int burstIndex2C0B = 0; burstIndex2C0B < 12; ++burstIndex2C0B) {
                field314 = static_cast<float>(burstIndex2C0B * 30);
                field318 = 7.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x341, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2C0B * -30);
                field318 = 7.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x341, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2C0B * 30);
                field318 = 6.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x341, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(burstIndex2C0B * -30);
                field318 = 6.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x341, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        if (animationStage != 12 || animationFrame != 0 || scriptCounterF02 > 1)
            return;
        ++scriptCounterF02;
        ResetSecondaryCounter(10);
        return;

    case 0x2C2:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x74, x, y + g_BarrageY1At006591EC, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(6);
            SpawnBattleEffect(0x344, opponent->x, y, facing, 1);
        }
        if (animationStage != 11 || animationFrame != 0 || scriptCounterF00 > 5)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
        return;

    case 0x2C3:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            field36C -= g_ContactProjectionAt00657888;
            SpawnAuxEffect(0x74, facing * 42.0f + x,
                y + g_Stage2BFYOffsetAt00658398, facing, 1);
        }
        if (animationStage != 7 || animationFrame != 0)
            return;
        PlaySound(13);
        UpdateGaugeTimer(500);
        SpawnBattleEffect(0x34B, facing * 83.0f + x,
            y + g_Stage2BFY2At00659B6C, facing, 1);
        return;

    case 0x2DA:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame < 30) {
            ++fieldF04;
            if (fieldF04 > 4) {
                SpawnAuxEffect(0x3E, x, y + g_Stage2DAEffectYOffsetAt0065908C, 1, 1);
                fieldF04 = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > 0.0f)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(
                g_StateRepeatLevelAt006714D0 * -40 + 180);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(4);
            for (int fanIndex2DA4 = 0; fanIndex2DA4 < 9; ++fanIndex2DA4) {
                field314 = static_cast<float>(fanIndex2DA4 * 40);
                field318 = 8.0f;
                field31C = 1.0f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(fanIndex2DA4 * -40 + 20);
                field318 = 8.0f;
                field31C = -1.0f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(4);
            for (int fanIndex2DA6 = 0; fanIndex2DA6 < 9; ++fanIndex2DA6) {
                field314 = static_cast<float>(fanIndex2DA6 * 40);
                field318 = 10.0f;
                field31C = 0.8f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(fanIndex2DA6 * -40 + 20);
                field318 = 10.0f;
                field31C = -0.8f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 8 && animationFrame == 0 &&
                g_StateRepeatLevelAt006714D0 > 1) {
            PlaySound(4);
            for (int fanIndex2DA8 = 0; fanIndex2DA8 < 9; ++fanIndex2DA8) {
                field314 = static_cast<float>(fanIndex2DA8 * 40);
                field318 = 12.0f;
                field31C = 0.6f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(fanIndex2DA8 * -40 + 20);
                field318 = 12.0f;
                field31C = -0.6f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 &&
                g_StateRepeatLevelAt006714D0 > 2) {
            PlaySound(4);
            for (int fanIndex2DA10 = 0; fanIndex2DA10 < 9; ++fanIndex2DA10) {
                field314 = static_cast<float>(fanIndex2DA10 * 40);
                field318 = 14.0f;
                field31C = 0.6f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
                field314 = static_cast<float>(fanIndex2DA10 * -40 + 20);
                field318 = 14.0f;
                field31C = -0.6f;
                SpawnBattleEffect(900, x,
                    y + g_Stage700EffectYOffsetAt00659460, facing, 1);
            }
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(10);
        }
        if (animationStage != 14 || animationFrame != 0 || scriptCounterF02 > 5)
            return;
        ++scriptCounterF02;
        ResetSecondaryCounter(12);
        return;

    case 0x2DB:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (color[0] < 0x81)
            color[0] = 0x80;
        else
            color[0] = static_cast<unsigned char>(
                static_cast<signed char>(color[0]) - 6);
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                ResetPrimaryCounters(0x2DA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 2 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame < animationFrameCount)
            return;
        animationFrame = 0;
        ++animationStage;
        if (animationStage == 2) {
            velocityX = (opponent->x - x) * facing / g_YuyukoChaseDivisorAt0065788C;
            velocityY = 10.0f;
            field05C = 0.4f;
        }
        if (animationStageCount <= animationStage)
            animationStage -= 2;
        BindAnimation();
        return;

    case 0x2E4:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 0;
            field080 = 8;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if ((animationStage == 7 || animationStage == 8) && animationFrame == 0)
            SpawnBattleEffect(0x388, facing * 67.0f + x,
                y + g_RadialPatternYOffsetAt00659274, facing, 1);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            SpawnBattleEffect(0x397, x,
                y + g_ThousandAt006583B4, facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0)
            PlaySound(3);
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < g_StateRepeatLevelAt006714D0 * 4 + 5) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            field07C = 1;
        }
        if (animationStage != 11 || animationFrame != 0 || scriptCounterF00 > 4)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(9);
        return;

    case 0x2EE:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 9 || animationStage == 10) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 20) {
                SpawnBattleEffect(0x386, opponent->x, y, facing, 1);
                PlaySound(6);
                scriptCounterF02 = 0;
                ++scriptCounterF00;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > 0.0f)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(
                g_StateRepeatLevelAt006714D0 * -30 + 240);
        }
        if (animationStage == 11 && animationFrame == 0 &&
                scriptCounterF00 < g_StateRepeatLevelAt006714D0 * 2 + 4) {
            ResetSecondaryCounter(9);
            return;
        }
        if (animationStage != 13 || animationFrame != 0 || fieldF04 > 1)
            return;
        ++fieldF04;
        ResetSecondaryCounter(11);
        return;

    case 0x2EF:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > 0.0f)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(
                g_StateRepeatLevelAt006714D0 * -30 + 240);
        }
        if (animationStage != 4 || animationFrame != 0)
            return;
        SpawnBattleEffect(0x389, opponent->x, y, facing, 1);
        return;

    case 0x2F8:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage < 3 && scriptCounterF00 < 3 && animationFrame < 70) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 4) {
                SpawnAuxEffect(0x40, x, y + g_Stage2DAEffectYOffsetAt0065908C, 1, 1);
                scriptCounterF02 = 0;
            }
        }
        velocityY -= field05C;
        if (velocityY < g_ThresholdAt0065782C)
            velocityY = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2F9);
            fieldF04 = 0;
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityY = 10.0f;
            field05C = 0.3f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x38A, x, y, 1, 0);
            PlaySound(13);
        }
        if (animationStage != 8 || animationFrame != 0 || fieldF04 != 0)
            return;
        ResetSecondaryCounter(6);
        return;

    case 0x2F9:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 120;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            fieldF06 = 0;
            fieldF08 = 60;
        }
        if (opponent->health > 0 && opponent->animationStage == 2 &&
                opponent->field39D > 0 && opponent->action == 99) {
            ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        --scriptCounterF00;
        --fieldF06;
        --fieldF08;
        if (opponent->health > 0) {
            if (scriptCounterF00 < 1) {
                scriptCounterF00 = 180;
                scriptCounterF02 = static_cast<short>(RecordedRange(0, 20) + 30);
                if (RecordedRange(0, 100) < 50) {
                    if (y < g_YuyukoFanUpperYAt006593D0) {
                        if (g_YuyukoFanLeftXAt00657D10 <= x)
                            fieldF04 = -175;
                        else
                            fieldF04 = -5;
                    }
                } else if (g_YuyukoFanLowerYAt00659238 < y) {
                    if (x <= g_YuyukoFanRightXAt00659B68)
                        fieldF04 = 5;
                    else
                        fieldF04 = 175;
                }
            }
            if (scriptCounterF02 > 0)
                --scriptCounterF02;
            SetPolarVelocity(static_cast<float>(fieldF04),
                static_cast<float>(scriptCounterF02) * g_YuyukoFanSpeedScaleAt006590B4);

            if (fieldF06 < 1) {
                PlaySound(13);
                fieldF06 = 180;
                if (g_StateRepeatLevelAt006714D0 == 0) {
                    for (int radialIndex2F9A = 0; radialIndex2F9A < 6; ++radialIndex2F9A) {
                        field314 = static_cast<float>(radialIndex2F9A * 60);
                        SpawnBattleEffect(0x38C, x,
                            y + g_ContactProjectionAt00657888, facing, 1);
                    }
                }
                if (g_StateRepeatLevelAt006714D0 == 1) {
                    for (int radialIndex2F9B = 0; radialIndex2F9B < 9; ++radialIndex2F9B) {
                        field314 = static_cast<float>(radialIndex2F9B * 40);
                        SpawnBattleEffect(0x38C, x,
                            y + g_ContactProjectionAt00657888, facing, 1);
                    }
                }
                if (g_StateRepeatLevelAt006714D0 == 2) {
                    for (int radialIndex2F9C = 0; radialIndex2F9C < 12; ++radialIndex2F9C) {
                        field314 = static_cast<float>(radialIndex2F9C * 30);
                        SpawnBattleEffect(0x38C, x,
                            y + g_ContactProjectionAt00657888, facing, 1);
                    }
                }
                if (g_StateRepeatLevelAt006714D0 == 3) {
                    for (int radialIndex2F9D = 0; radialIndex2F9D < 18; ++radialIndex2F9D) {
                        field314 = static_cast<float>(radialIndex2F9D * 20);
                        SpawnBattleEffect(0x38C, x,
                            y + g_ContactProjectionAt00657888, facing, 1);
                    }
                }
            }

            if (fieldF08 < 1) {
                if (fieldF08 == 0) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9A = 0; burstIndex2F9A < 6; ++burstIndex2F9A) {
                        field314 = static_cast<float>(burstIndex2F9A * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - g_YuyukoFanSpawnXOffsetAt0065784C,
                            y + field31C, facing, 1);
                    }
                }
                if (g_StateRepeatLevelAt006714D0 > 0 && fieldF08 == -20) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9B = 0; burstIndex2F9B < 6; ++burstIndex2F9B) {
                        field314 = static_cast<float>(burstIndex2F9B * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - g_YuyukoFanSpawnXOffsetAt0065784C,
                            y + field31C, facing, 1);
                    }
                }
                if (g_StateRepeatLevelAt006714D0 > 1 && fieldF08 == -40) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9C = 0; burstIndex2F9C < 6; ++burstIndex2F9C) {
                        field314 = static_cast<float>(burstIndex2F9C * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - g_YuyukoFanSpawnXOffsetAt0065784C,
                            y + field31C, facing, 1);
                    }
                }
                if (g_StateRepeatLevelAt006714D0 > 2 && fieldF08 == -60) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9D = 0; burstIndex2F9D < 6; ++burstIndex2F9D) {
                        field314 = static_cast<float>(burstIndex2F9D * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - g_YuyukoFanSpawnXOffsetAt0065784C,
                            y + field31C, facing, 1);
                    }
                }
                if (fieldF08 < -59)
                    fieldF08 = static_cast<short>(g_StateRepeatLevelAt006714D0 * -10 + 120);
            }

            if (scriptCounterF00 == 0 || scriptCounterF00 == -30 ||
                    (g_StateRepeatLevelAt006714D0 > 1 && scriptCounterF00 == -60)) {
                PlaySound(0);
                short effect2F9 = scriptCounterF00 == 0 ? 0x394 :
                    scriptCounterF00 == -30 ? 0x395 : 0x396;
                for (int fanIndex2F9A = 0; fanIndex2F9A < 20; ++fanIndex2F9A) {
                    field314 = static_cast<float>(fanIndex2F9A * 18);
                    field318 = 1.0f;
                    field31C = 1.0f;
                    SpawnBattleEffect(effect2F9, 640.0f, 340.0f, 1, 1);
                    if (g_StateRepeatLevelAt006714D0 == 3) {
                        field314 = static_cast<float>(fanIndex2F9A * 18 + 9);
                        field318 = 3.0f;
                        SpawnBattleEffect(effect2F9, 640.0f, 340.0f, 1, 1);
                    }
                }
                for (int fanIndex2F9B = 0; fanIndex2F9B < 20; ++fanIndex2F9B) {
                    field314 = static_cast<float>(fanIndex2F9B * -18);
                    field318 = 1.0f;
                    field31C = -1.0f;
                    SpawnBattleEffect(effect2F9, 640.0f, 340.0f, 1, 1);
                    if (g_StateRepeatLevelAt006714D0 == 3) {
                        field314 = static_cast<float>(fanIndex2F9B * 18 + 9);
                        field318 = 3.0f;
                        SpawnBattleEffect(effect2F9, 640.0f, 340.0f, 1, 1);
                    }
                }
            }
            if (scriptCounterF00 == -60)
                scriptCounterF00 = static_cast<short>(g_StateRepeatLevelAt006714D0 * -10 + 180);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
            return;
        }
        if (animationStage != 7 || animationFrame != 0)
            return;
        ResetSecondaryCounter(1);
        return;

    case 0x302:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 1) {
            if (color[0] < 6)
                color[0] = 0;
            else
                color[0] = static_cast<unsigned char>(color[0] - 5);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x303);
            field3CF = 1;
            x = 640.0f;
            y = 200.0f;
            facing = 1;
            return;
        }
        if (animationStage != 1 || animationFrame != 0)
            return;
        ResetTransform(0.0f, 0.0f, 0.0f);
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
        return;

    case 0x303:
        facing = 1;
        field010 = 0x82;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 120;
            scriptCounterF02 = -90;
            fieldF04 = 90;
            fieldF06 = 0;
            fieldF08 = 0;
            ClearMotionFields();
        }
        if (opponent->health > 0 && opponent->animationStage == 2 &&
                opponent->field39D > 0 && opponent->action == 99) {
            ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (color[0] < 250)
            color[0] = static_cast<unsigned char>(color[0] + 5);
        else
            color[0] = 255;
        x = 640.0f;
        y = 200.0f;
        if (opponent->health > 0) {
            --scriptCounterF00;
            ++fieldF06;
            opponent->field490 = 0.0f;
            if (fieldF06 > 300 && animationStage == 1 && animationFrame == 0) {
                scriptCounterF02 = static_cast<short>(scriptCounterF02 + 10);
                if (scriptCounterF02 == 180)
                    scriptCounterF02 = -180;
                fieldF04 = static_cast<short>(fieldF04 - 10);
                if (fieldF04 == -180)
                    fieldF04 = 180;
                PlaySound(0x0E);
                field318 = static_cast<float>(scriptCounterF02);
                SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                if (g_StateRepeatLevelAt006714D0 > 0) {
                    field318 = static_cast<float>(fieldF04);
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                }
                if (g_StateRepeatLevelAt006714D0 == 2) {
                    field318 = static_cast<float>(fieldF04 + 180);
                    if (g_YuyukoFanLowerYAt00659238 <= field318)
                        field318 -= g_YuyukoAnglePeriodAt00657864;
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(scriptCounterF02 - 180);
                    if (field318 <= g_YuyukoAngleUpperWrapAt006595E4)
                        field318 += g_YuyukoAnglePeriodAt00657864;
                    SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                }
                if (g_StateRepeatLevelAt006714D0 == 3) {
                    field318 = static_cast<float>(fieldF04 + 120);
                    if (g_YuyukoFanLowerYAt00659238 <= field318)
                        field318 -= g_YuyukoAnglePeriodAt00657864;
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(scriptCounterF02 - 120);
                    if (field318 <= g_YuyukoAngleUpperWrapAt006595E4)
                        field318 += g_YuyukoAnglePeriodAt00657864;
                    SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(fieldF04 + 240);
                    if (g_YuyukoFanLowerYAt00659238 <= field318)
                        field318 -= g_YuyukoAnglePeriodAt00657864;
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(scriptCounterF02 - 240);
                    if (field318 <= g_YuyukoAngleUpperWrapAt006595E4)
                        field318 += g_YuyukoAnglePeriodAt00657864;
                    SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                }
            }
            if (scriptCounterF00 < 1) {
                if (scriptCounterF00 == 0) {
                    PlaySound(0);
                    for (int fanIndex303A = 0; fanIndex303A < 20; ++fanIndex303A) {
                        field314 = static_cast<float>(fanIndex303A * 18);
                        field318 = 1.0f;
                        field31C = 1.0f;
                        SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        if (g_StateRepeatLevelAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303A * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        }
                    }
                    for (int fanIndex303B = 0; fanIndex303B < 20; ++fanIndex303B) {
                        field314 = static_cast<float>(fanIndex303B * -18);
                        field318 = 1.0f;
                        field31C = -1.0f;
                        SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        if (g_StateRepeatLevelAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303B * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        }
                    }
                }
                if (scriptCounterF00 == -30) {
                    PlaySound(0);
                    for (int fanIndex303C = 0; fanIndex303C < 20; ++fanIndex303C) {
                        field314 = static_cast<float>(fanIndex303C * 18);
                        field318 = 1.0f;
                        field31C = 1.0f;
                        SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        if (g_StateRepeatLevelAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303C * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        }
                    }
                    for (int fanIndex303D = 0; fanIndex303D < 20; ++fanIndex303D) {
                        field314 = static_cast<float>(fanIndex303D * -18);
                        field318 = 1.0f;
                        field31C = -1.0f;
                        SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        if (g_StateRepeatLevelAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303D * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        }
                    }
                }
                if (g_StateRepeatLevelAt006714D0 > 1 && scriptCounterF00 == -60) {
                    PlaySound(0);
                    for (int fanIndex303E = 0; fanIndex303E < 20; ++fanIndex303E) {
                        field314 = static_cast<float>(fanIndex303E * 18);
                        field318 = 1.0f;
                        field31C = 1.0f;
                        SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        if (g_StateRepeatLevelAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303E * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        }
                    }
                    for (int fanIndex303F = 0; fanIndex303F < 20; ++fanIndex303F) {
                        field314 = static_cast<float>(fanIndex303F * -18);
                        field318 = 1.0f;
                        field31C = -1.0f;
                        SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        if (g_StateRepeatLevelAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303F * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        }
                    }
                }
                if (scriptCounterF00 == -60) {
                    scriptCounterF00 = static_cast<short>(
                        g_StateRepeatLevelAt006714D0 * -10 + 180);
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(1);
            return;
        }
        if (animationStage != 7 || animationFrame != 0)
            return;
        ResetPrimaryCounters(1);
        return;

    case 0x31B:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x, y, facing, 1);
        }
        if (animationStage != 9 || animationFrame != 0 || scriptCounterF00 > 7)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(7);
        return;

    case 0x31C:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (field370[field39D] == 1) {
                ResetPrimaryCounters(0x2E4);
                return;
            }
            ResetPrimaryCounters(0);
        }
        if (animationStage == 0x0B && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage != 0x0E || animationFrame != 0 || scriptCounterF00 > 7)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(0x0C);
        field3CF = 1;
        return;

    case 0x8F:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 3 || animationFrame != 0 || scriptCounterF00 > 6)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x90:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 3 || animationFrame != 0 || scriptCounterF00 > 6)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    case 0x96:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x97:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x98:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x9F:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0xA0:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0xA1:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0x9A:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x9B:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x9C:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0x9E:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -6.0f;
            velocityY = 8.0f;
            field05C = 0.75f;
        }
        if (g_ThresholdAt0065782C <= y) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(9);
        return;

    case 0xA3:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0xA4:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0xA5:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0xA7:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            PlaySharedSound(0x2C);
            scriptCounterF00 = 180;
            SpawnAuxEffect(0x38, x + facing * 30.0f,
                y + g_ContactProjectionAt00657888, facing, 1);
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        field490 = -static_cast<float>(scriptCounterF00) * g_F748_SpeedScaleAt006590B8;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = static_cast<short>(scriptCounterF00 - 10);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        return;

    case 0xA8:
        cardGauge += g_CardGaugeStepAt0065747C;
        if (g_ThousandAt006583B4 < cardGauge)
            cardGauge = g_ThousandAt006583B4;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            PlaySharedSound(0x2C);
            scriptCounterF00 = 180;
            SpawnAuxEffect(0x38, x + facing * 30.0f,
                y + g_ContactProjectionAt00657888, facing, 1);
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        field490 = -static_cast<float>(scriptCounterF00) * g_F748_SpeedScaleAt006590B8;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = static_cast<short>(scriptCounterF00 - 10);
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(2);
        return;

    case 0xB4:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = 8.0f;
            velocityY = 12.5f;
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (g_ThresholdAt0065782C < y) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetSecondaryCounter(7);
        return;

    case 0xB5:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = -8.0f;
            velocityY = 12.5f;
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (g_ThresholdAt0065782C < y) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetSecondaryCounter(7);
        return;

    case 200:
        field3AC = 1;
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            scriptCounterF00 = 0;
        }
        if (g_BarrageXOffsetAt00657874 < velocityX) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_ApproachLowerAt00658290)
                velocityX = g_ApproachLowerAt00658290;
        }
        if (inputY < 0) {
            ResetPrimaryCounters(facing * inputX > 0 ? 0xCD : 0xCC);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (facing * inputX > 0 && scriptCounterF00 < 5) {
                ResetSecondaryCounter(2);
                ++scriptCounterF00;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (animationStage != 1 || animationFrame != 0)
            return;
        velocityX = 15.0f;
        return;

    case 0xC9:
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 0.0f;
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 2.0f;
            field05C = 0.2f;
        }
        if (g_ThresholdAt0065782C < y && animationStage > 0 && animationStage < 5) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 5 || animationFrame != 0)
            return;
        ResetSecondaryCounter(animationStage - 2);
        return;

    case 0xCA:
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if (g_ThresholdAt0065782C < y && animationStage > 1) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
            return;
        }
        if (animationStage != 2 || animationFrame != 0)
            return;
        velocityX = 7.5f;
        velocityY = 3.5f;
        field05C = 0.45f;
        return;

    case 0xCB:
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if (g_ThresholdAt0065782C < y && animationStage > 0) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -7.5f;
            velocityY = 3.5f;
            field05C = 0.45f;
        }
        if (animationStage != 5 || scriptCounterF00 > 0)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(3);
        return;

    case 0xCC:
        if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3, 4, 0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (g_ThresholdAt0065782C < y) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 2 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame < animationFrameCount)
            return;
        animationFrame = 0;
        ++animationStage;
        if (animationStage == 2) {
            velocityX = 0.0f;
            velocityY = 18.5f;
            field05C = 0.55f;
            SpawnAuxEffect(0x3C, x, y, 1, 1);
        }
        if (animationStageCount <= animationStage)
            animationStage -= 2;
        BindAnimation();
        return;

    case 0xCD:
        if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3, 4, 0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (g_ThresholdAt0065782C < y) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 2 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame < animationFrameCount)
            return;
        animationFrame = 0;
        ++animationStage;
        if (animationStage == 2) {
            velocityX = 0.0f;
            velocityY = 13.5f;
            field05C = 0.5f;
            SpawnAuxEffect(0x3C, x, y, 1, 1);
        }
        if (animationStageCount <= animationStage)
            animationStage -= 2;
        BindAnimation();
        return;

    case 0xCE:
        if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3, 4, 0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (g_ThresholdAt0065782C < y) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        ++animationFrame;
        if (animationFrame < animationFrameCount)
            return;
        animationFrame = 0;
        ++animationStage;
        if (animationStage == 2) {
            velocityX = -10.0f;
            velocityY = 13.5f;
            field05C = 0.5f;
            SpawnAuxEffect(0x3C, x, y, 1, 1);
        }
        if (animationStageCount <= animationStage)
            animationStage -= 2;
        BindAnimation();
        return;

    case 0xCF:
        field3AC = 1;
        velocityX -= g_SubtractAt00657478;
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetPrimaryCounters(0);
        field3AC = 0;
        return;

    case 0xD0:
        if (animationStage == 0 && animationFrame == 0) {
            facing = -facing;
            velocityX = -velocityX;
        }
        if (field05C == g_ThresholdAt0065782C)
            field05C = 0.6f;
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetSecondaryCounter(5);
        return;

    case 0x91:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            field05C = 0.5f;
            field07C = 0;
        }
        if (animationStage == 1 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>(velocityX * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>(velocityY * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() != animationStageCount)
            return;
        ResetSecondaryCounter(6);
        return;

    case 400:
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage < 8 || scriptCounterF00 > 0 || scriptCounterF02 > 2)
            return;
        UpdateGaugeTimer(100);
        PlaySound(0);
        scriptCounterF00 = 15;
        ++scriptCounterF02;
        for (int burstIndex400 = 0; burstIndex400 < 5; ++burstIndex400) {
            field318 = 1.0f;
            field314 = static_cast<float>(burstIndex400 * -20 + 40);
            SpawnBattleEffect(800, facing * 50.0f + x,
                y + g_BarrageY1At006591EC, facing, 1);
        }
        return;

    case 0x8C:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (g_ThresholdAt0065782C < velocityX)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() != 0 && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage != 3 || animationFrame != 0 || scriptCounterF00 > 4)
            return;
        ++scriptCounterF00;
        ResetSecondaryCounter(1);
        return;

    default:
        // The original common default path advances the nested animation and
        // returns to neutral only when the action's stage sequence wraps.
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }
}
