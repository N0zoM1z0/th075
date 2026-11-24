#include "MeilingFighter.hpp"

extern double g_ContactScaleAt006583E8;
extern double g_RiseAt00658050;
extern float g_AdditionalGravityAt00659090;
extern float g_AngleShiftAt00657878;
extern float g_AnimationDeltaAt0065747C;
extern float g_AnimationMaximumAt006583B4;
extern float g_ApproachUpperAt006592A4;
extern float g_BounceScaleAt00657F74;
extern float g_BounceThresholdAt006590C0;
extern float g_BounceXAt006590BC;
extern float g_BounceYAt00658044;
extern float g_CommandSpeedLowerAt00657850;
extern float g_ContactProjectionAt00657888;
extern float g_ExtraThresholdAt00657D14;
extern float g_JumpGroundCorrectionAt00658058;
extern float g_LandingSpeedScaleAt006590B8;
extern float g_MeilingActivationEffectYAt0065788C;
extern float g_MeilingAirShotYAt00659288;
extern float g_MeilingAirVolleyYAt0065908C;
extern float g_MeilingAttackDragAt006598B0;
extern float g_MeilingBounceSpeedLimitAt006590C4;
extern float g_MeilingCommandEffectYAt00658268;
extern float g_MeilingDoubleShotYAt00659F3C;
extern float g_MeilingDownVolleyYAt0065826C;
extern float g_MeilingEffectYAt006590A8;
extern float g_MeilingEffectYAt006590AC;
extern float g_MeilingLateAttackDragAt006595E8;
extern float g_MeilingLotusEffectYAt00659F38;
extern float g_MeilingLowVolleyYAt006590A0;
extern float g_MeilingParticleOffsetYAt0065927C;
extern float g_MeilingParticleRadiusAt0065835C;
extern float g_MeilingRisingEffectYAt00657858;
extern float g_MeilingStageSixSpeedAt00659308;
extern float g_MeilingStandingShotYAt00659280;
extern float g_MeilingSuperRecoveryDragAt00658350;
extern float g_ProjectileFallAt006590B4;
extern float g_StopThresholdAt00657480;
extern float g_SubtractAt00657478;
extern float g_ThresholdAt0065782C;
extern signed char g_ModeAt006714B4;
extern signed char g_RepeatSettingAt006714D0;

void MeilingFighter::Advance() {
    if (field082 != 0 || opponent->field3BA != 0)
        return;

    switch (action) {
    case 0: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > g_ThresholdAt0065782C) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (velocityX > g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        goto advanceFrame;
    }

    case 0x1: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > g_ThresholdAt0065782C) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (velocityX > g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        break;
    }

    case 0x2: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > g_ThresholdAt0065782C) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (velocityX > g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        goto advanceFrame;
    }

    case 0x3: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > g_ThresholdAt0065782C) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX += g_RiseAt00658050;
                if (velocityX > g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;
    }

    case 0x4: {
        velocityX = 6.0f;
        goto advanceFrame;
    }

    case 0x5: {
        velocityX = -4.5f; goto advanceFrame;
    }

    case 0x6: {
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 3 || field3AC > 0)) {
            ResetPrimaryCounters(0xCC);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 14.0f;
                field05C = 0.7f;
                field3AC = 0;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x7: {
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 5 || field3AC > 0)) {
            ResetPrimaryCounters(0xCD);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 6.0f;
                velocityY = 14.0f;
                field05C = 0.7f;
                field3AC = 0;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x8: {
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 4 || field3AC > 0)) {
            ResetPrimaryCounters(0xCE);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -4.0f;
                velocityY = 14.0f;
                field05C = 0.7f;
                field3AC = 0;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x9: {
        if (field05C == g_ThresholdAt0065782C)
            field05C = 0.6f;
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;
    }

    case 0xA: {
        if (animationStage == 0 && animationFrame == 0)
            PlaySharedSound(30);
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount) {
            if (inputY == 0)
                ResetPrimaryCounters(0);
            else
                ResetPrimaryCounters(2);
        }
        break;
    }

    case 0x32: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if (velocityX > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE != 0)
            field490 = static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x33: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x34: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x35: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x38: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x39: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x3A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x3B: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x3E: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x3F: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x40: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x41: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            field490 =
                static_cast<float>((velocityX) * g_ContactScaleAt006583E8);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x46: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(field094);
            velocityY += field098;
            if (velocityY < g_StopThresholdAt00657480)
                velocityY = 2.0f;
            field05C = 0.8f;
            if (velocityY > g_MeilingBounceSpeedLimitAt006590C4)
                velocityY = 12.0f;
            field07C = 0;
        }
        if (animationStage == 2 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
        return;
    }

    case 0x47: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(field094);
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (animationStage == 2 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
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
    }

    case 0x48: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(field094);
            velocityY = field098;
            field05C = 1.3f;
            field07C = 0;
        }
        if (animationStage == 2 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
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
    }

    case 0x49: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(field094);
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage == 1 && animationFrame == 0 && velocityY != g_ThresholdAt0065782C) {
            if (velocityX == (g_ThresholdAt0065782C)) {
                ResetSecondaryCounter(3);
                return;
            } else {
                ResetSecondaryCounter(2);
                return;
            }
        }
        return;
    }

    case 0x4A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(field094);
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (animationStage == 2 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(3);
            return;
        }
        if (CheckHorizontalLimits() && (velocityX) <= g_BounceThresholdAt006590C0) {
            ResetPrimaryCounters(0x4C);
            velocityX = -(velocityX) * g_BounceScaleAt00657F74;
            velocityY = 15.0f;
            field05C = 0.5f;
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
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
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }

        rotationZ = (rotationZ) + g_AngleShiftAt00657878;
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            PlaySharedSound(0x16);
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
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
    }

    case 0x58: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(field094);
            velocityY = field098;
            field05C = 0.8f;
            field07C = 0;
        }
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x59);
            SetCameraShake(3.0f);
            PlaySharedSound(0x16);
            for (int burst = 0; burst < 10; ++burst)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage == 1 && animationFrame == 0) {
            if (velocityY != g_ThresholdAt0065782C) {
                if (velocityX == (g_ThresholdAt0065782C)) {
                    ResetSecondaryCounter(3);
                    return;
                } else {
                    ResetSecondaryCounter(2);
                    return;
                }
            }
        } else if (animationStage == 1 && animationFrame != 0) {
            // Continue the impact animation.
        }
        return;
    }

    case 0x59: {
        if (animationStage == 3) {
            rotationZ = (rotationZ) + g_MeilingRisingEffectYAt00657858;
            velocityY = velocityY - field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                scriptCounterF00 = (velocityX) * g_ContactProjectionAt00657888;
                scriptCounterF02 = (velocityY) * g_ContactProjectionAt00657888;
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x61);
                rotationZ = 0.0f;
                SetCameraShake(2.0f);
                ClearTransformFlag(); PlaySharedSound(0x16);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(3);
        else if (animationStage == 3 && animationFrame == 0) {
            velocityX = float(int(scriptCounterF00)) * g_BounceXAt006590BC;
            velocityY = float(-int(scriptCounterF02)) * g_BounceYAt00658044;
            field05C = 0.7f;
            ResetTransform(-7.0f, 75.0f, 0.0f);
        } else if (animationStage == 3 && animationFrame != 0) {
            // Continue the spinning animation.
        }
        break;
    }

    case 0x5D: {
        if (animationStage < 6 && y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(6);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityY = 4.5f;
            velocityX = 20.0f;
            field05C = 0.5f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 6 && animationFrame != 0) {
            // Continue the landing animation.
        }
        break;
    }

    case 0x5E: {
        if (animationStage < 6 && y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(6);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityY = 4.5f;
            velocityX = -20.0f;
            field05C = 0.5f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 6 && animationFrame != 0) {
            // Continue the landing animation.
        }
        break;
    }

    case 0x5F: {
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        return;
    }

    case 0x61: {
        if (0 < facing * inputX &&
                ((static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0) || (static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0)))
            scriptCounterF00 = 1;
        if (facing * inputX < 0 &&
                (((static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0) || static_cast<unsigned int>(inputC) > 0) || static_cast<unsigned int>(inputD) > 0))
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
            if (velocityY + y < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0) {
                ResetPrimaryCounters(99);
            }
        } else {
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = scriptCounterF00 * g_LandingSpeedScaleAt006590B8;
                velocityY = -scriptCounterF02 * g_LandingSpeedScaleAt006590B8;
                field05C = 2.0f;
            }
            if (animationStage == 5 && animationFrame == 0) {
                ResetSecondaryCounter(4);
            } else if (animationStage == 5 && animationFrame != 0) {
                // Continue the landing animation.
            }
        }
        break;
    }

    case 0x62: {
        if (static_cast<int>(facing) * inputX > 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 1;
        if (static_cast<int>(facing) * inputX < 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 2;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x5F);
            if (scriptCounterF00 == 1)
                ResetPrimaryCounters(0x5D);
            if (scriptCounterF00 == 2)
                ResetPrimaryCounters(0x5E);
        }
        return;
    }

    case 0x63: {
        if (g_ModeAt006714B4 != 3 ||
            field2CD == 0) {
            if (animationStage == 2 &&
                field39D > 0 &&
                opponent->action < 150) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                break;
            }
        } else {
            if (animationStage > 1 &&
                field39D > 0 &&
                opponent->action < 150 &&
                field370[field39D] == 5 &&
                static_cast<signed char>(field32A[field39D]) == 2) {
                ResetPrimaryCounters(0x303);
                break;
            }
            if (animationStage > 1 &&
                field39D > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(field32A[field39D]) == 2) {
                ResetPrimaryCounters(0x31C);

                break;
            }
            if (animationStage > 0 &&
                field39D > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(field32A[field39D]) == 1) {
                ResetPrimaryCounters(0x31C);
                break;
            }
            if (animationStage > 1 &&
                field39D > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(field32A[field39D]) == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(2);
        break;
    }

    case 0x8C: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x8F: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x90: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x91: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            field05C = 0.5f;
            field07C = 0;
        }
        if (animationStage == 2 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;
    }

    case 0x96: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x97: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x98: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x9A: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9B: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9C: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9E: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            velocityX = -6.0f;
            velocityY = 8.0f;
            field05C = 0.75f;
        }

        if (y > g_ThresholdAt0065782C) {

            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x9F: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA0: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA1: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA3: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA4: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA5: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_ContactScaleAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA7: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing) * 30) + (x),

                (y) + g_ContactProjectionAt00657888,
                facing, 1);
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        field490 = (-scriptCounterF00) * g_ProjectileFallAt006590B4;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00 - 10;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA8: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing) * 30) + (x),

                (y) + g_ContactProjectionAt00657888,
                facing, 1);
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        field490 = (-scriptCounterF00) * g_ProjectileFallAt006590B4;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00 - 10;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xB4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = 8.0f;
            velocityY = 12.5f;
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(7);
            break;
        }
        break;
    }

    case 0xB5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = -8.0f;
            velocityY = 12.5f;
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(6);
            break;
        }
        break;
    }

    case 0xC8: {
        field3AC = 1;
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            scriptCounterF00 = 0;
        }
        if (velocityX > g_CommandSpeedLowerAt00657850) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_CommandSpeedLowerAt00657850)
                velocityX = 10.0f;
        }
        if (inputY < 0) {
            if (static_cast<int>(facing) * inputX > 0) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            ResetPrimaryCounters(0xCC);
            return;
        }
        if (scriptCounterF00 > 0 && static_cast<int>(facing) * inputX <= 0) {
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<int>(facing) * inputX > 0 && scriptCounterF00 < 3) {
                ResetSecondaryCounter(2);
                ++scriptCounterF00;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 13.0f;
            SpawnAuxEffect(0x7D,
                static_cast<float>(facing * 80) + x,
                (y) + g_MeilingCommandEffectYAt00658268, facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + g_MeilingCommandEffectYAt00658268, facing, 1);
            PlaySharedSound(0x1F);
        }
        return;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (y > g_ThresholdAt0065782C && animationStage > 2 && animationStage < 5) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 7.0f;
            field05C = 0.7f;
            SpawnAuxEffect(0x7D, x,
                (y) + g_MeilingCommandEffectYAt00658268, -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + g_MeilingCommandEffectYAt00658268, -facing, 1);
            PlaySharedSound(0x1F);
        }
        if (animationStage == 5 && animationFrame == 0) {
            ResetSecondaryCounter(animationStage - 2);
        }
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 11.0f;
            velocityY = 5.0f;
            field05C = 0.45f;
            SpawnAuxEffect(0x7D, float(facing * 80) + (x),
                (y) + g_MeilingEffectYAt006590AC, facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + g_MeilingEffectYAt006590AC,
                facing, 1);
            PlaySharedSound(31);
        }
        if (y > g_ThresholdAt0065782C && animationStage > 1) {
            velocityY = velocityY - field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f; y = 0.0f; animationFrame = 0;
                ResetPrimaryCounters(10);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(10);
        break;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { scriptCounterF00 = 0; velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; }
        if (y > g_ThresholdAt0065782C && animationStage > 0) {
            velocityY = velocityY - field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f; y = 0.0f; animationFrame = 0;
                ResetPrimaryCounters(10);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(10);
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 5.0f;
            field05C = 0.45f;
            SpawnAuxEffect(0x7D, x, (y) + g_MeilingEffectYAt006590A8,
                -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + g_MeilingEffectYAt006590A8,
                -facing, 1);
            PlaySharedSound(31);
        }
        break;
    }

    case 0xCC: {
        if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3, 4, 0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 3 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(4);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 21.0f;
                field05C = 0.75f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
    }

    case 0xCD: {
        if ((y == (g_ThresholdAt0065782C)) ||
            velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3, 4, 0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 3 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(4);

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 11.0f;
                velocityY = 16.0f;
                field05C = 0.7f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage = animationStage - 2;
            BindAnimation();
        }
        break;
    }

    case 0xCE: {
        if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3, 4, 0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -8.0f;
                velocityY = 16.0f;
                field05C = 0.7f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
    }

    case 0xCF: {
        field3AC = 1;
        velocityX -= g_SubtractAt00657478;
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            field3AC = 0;
        }
        return;
    }

    case 0xD0: {
        if (animationStage == 0 && animationFrame == 0) {
            facing = -facing;
            velocityX = -(velocityX);
        }
        if (field05C == (g_ThresholdAt0065782C)) field05C = 0.6f;
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(4);
        break;
    }

    case 0xD1: {
        if (spirit < 2) {
            ResetPrimaryCounters(0);
            break;
        }
        spirit = spirit - 3;
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            PlaySharedSound(0x2C);
            SpawnBattleEffect(0x3e5, x,
                    (y) + g_ContactProjectionAt00657888,
                    facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(0);
        }
        break;
    }

    case 0xD2: {
        if (spirit < 2) {
            ResetPrimaryCounters(9);
            break;
        }
        spirit = spirit - 3;
        if (animationStage == 0 && animationFrame == 0) {

            velocityX = (velocityX) * g_BounceScaleAt00657F74;
            velocityY = (velocityY) * g_BounceScaleAt00657F74;
            PlaySharedSound(0x2C);

            SpawnBattleEffect(0x3e5, x,
                    (y) + g_ContactProjectionAt00657888,
                    facing, 1);
        }

        velocityY = velocityY - (field05C) * g_BounceScaleAt00657F74;
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
        }
        break;
    }

    case 0x12C: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if ((velocityX) < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1B);
        return;
    }

    case 0x12D: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) - g_ApproachUpperAt006592A4;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) - g_MeilingStageSixSpeedAt00659308;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) + g_ApproachUpperAt006592A4;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) + g_MeilingStageSixSpeedAt00659308;
        }
        break;
    }

    case 0x12F: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if ((velocityX) < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1B);
        return;
    }

    case 0x130: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x131: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field080 = 1;
            field07C = 0;
        }
        if (animationStage == 8 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnBattleEffect(0x34E, x, y, facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(9);
        }
        if (animationStage == 8 && animationFrame == 0) {
            PlaySound(9);
        }
        break;
    }

    case 0x132: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) { field080 = 1; field07C = 0; }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 2 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x133: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0 || animationStage > 2) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x134: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if ((velocityX) < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x135: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if ((velocityX) < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x136: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 5 && velocityX > g_ThresholdAt0065782C) {
            velocityX = (velocityX) - g_AdditionalGravityAt00659090;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (animationStage > 4 && velocityX > g_ThresholdAt0065782C) {
            velocityX = (velocityX) - g_MeilingLateAttackDragAt006595E8;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = 12.5f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 25.0f;
            PlaySharedSound(0x1D);
        } else if (animationStage == 5 && animationFrame != 0) {
            // Continue the recovery animation.
        }
        break;
    }

    case 0x140: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        break;
    }

    case 0x141: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) - g_ApproachUpperAt006592A4;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) - g_MeilingStageSixSpeedAt00659308;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) + g_ApproachUpperAt006592A4;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) + g_MeilingStageSixSpeedAt00659308;
        }
        break;
    }

    case 0x142: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - g_AnimationDeltaAt0065747C;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            PlaySharedSound(0x1C);
            velocityX = 12.0f;
        }
        break;
    }

    case 0x143: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0 || animationStage > 2) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x144: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x145: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1C);
            velocityX = 30.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 10.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 10.0f;
        }
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 10.0f;
        }
        break;
    }

    case 0x146: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 1;
            field07C = 0;
            velocityX = 11.0f;
        }
        if (animationStage == 0) {
            velocityX = (velocityX) - g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 0) {
            velocityX = (velocityX) - g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage > 1) {
            velocityX = (velocityX) - g_ExtraThresholdAt00657D14;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            PlaySharedSound(0x1D);
            velocityX = 20.0f;
        } else if (animationStage == 1 && animationFrame != 0) {
            // Continue the follow-through.
        }
        break;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 1;
            field07C = 0;
            velocityX = 12.0f;
        }
        velocityX = (velocityX) - g_MeilingAttackDragAt006598B0;
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) - g_ApproachUpperAt006592A4;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) - g_MeilingStageSixSpeedAt00659308;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) + g_ApproachUpperAt006592A4;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) + g_MeilingStageSixSpeedAt00659308;
        }
        break;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field07C = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 2 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
            velocityX = 12.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
        }
        velocityX = (velocityX) - g_MeilingAttackDragAt006598B0;
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        break;
    }

    case 0x190: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(800,
                static_cast<float>(facing * 90) + x,
                (y) + g_MeilingStandingShotYAt00659280, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(250);
        }
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33F, static_cast<float>(facing * 120) + x, (y) + g_ThresholdAt0065782C, facing, 1);
            PlaySound(7);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            scriptCounterF00 = 0;
        }
        velocityY -= field05C;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 8.0f;
            field05C = 0.55f;
            SpawnBattleEffect(0x320, static_cast<float>(facing * 125) + x, (y) + g_MeilingAirShotYAt00659288, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x195: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            scriptCounterF00 = 0;
        }
        velocityY = velocityY - field05C;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 8.0f;
            field05C = 0.55f;

            field314 = -30.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -40.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -50.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -60.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -70.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);

            PlaySound(0);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 6 && animationFrame == 0 && scriptCounterF00 < 2 &&
            static_cast<unsigned int>(inputC) > 0) {

            field314 = -30.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -40.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -50.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -60.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);
            field314 = -70.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + g_MeilingDownVolleyYAt0065826C, facing, 1);

            PlaySound(0);
            UpdateGaugeTimer(25);
            ++scriptCounterF00;
            ResetSecondaryCounter(4);
        }
        break;
    }

    case 0x196: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(36 - shot * 12);
                SpawnBattleEffect(shot + 0x32B, (x) + g_ThresholdAt0065782C,
                    (y) + g_ContactProjectionAt00657888, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(15 - shot * 5);
                SpawnBattleEffect(shot + 0x32B, (x) + g_ThresholdAt0065782C,
                    (y) + g_ContactProjectionAt00657888, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x323, static_cast<float>(facing * 134) + x, (y) + g_MeilingDoubleShotYAt00659F3C, facing, 1);
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x324, static_cast<float>(facing * 134) + x, (y) + g_MeilingDoubleShotYAt00659F3C, facing, 1);
            PlaySound(8);
        }
        break;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_ProjectileFallAt006590B4;
            velocityY = (velocityY) * g_ProjectileFallAt006590B4;
            field07C = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6)
            velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(36 - shot * 12);
                SpawnBattleEffect(shot + 0x32B, static_cast<float>(facing * 10) + x,
                    (y) + g_MeilingAirVolleyYAt0065908C, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x19B: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_ProjectileFallAt006590B4;
            velocityY = (velocityY) * g_ProjectileFallAt006590B4;
            field07C = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6)
            velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(15 - shot * 5);
                SpawnBattleEffect(shot + 0x32B, static_cast<float>(facing * 10) + x,
                    (y) + g_MeilingAirVolleyYAt0065908C, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x339, static_cast<float>(facing * 100) + x, y, facing, 1);
            PlaySound(6);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage < 10 && animationStage > 1) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(10);
                ClearMotionFields();
                y = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 4.0f;
            velocityY = 8.0f;
            field05C = 0.4f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33B, static_cast<float>(facing * 50) + x, (y) + g_MeilingRisingEffectYAt00657858, facing, 1);
            PlaySound(6);
            UpdateGaugeTimer(250);
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(8);
        }
        break;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_ProjectileFallAt006590B4;
            velocityY = (velocityY) * g_ProjectileFallAt006590B4;
            field07C = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 4)
            velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x33A, static_cast<float>(facing * 100) + x, y, facing, 1);
            PlaySound(6);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x1A1: {
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_ProjectileFallAt006590B4;
            velocityY = (velocityY) * g_ProjectileFallAt006590B4;
            field07C = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0) {
            field314 = 30.0f;
            field318 = 8.0f;
            SpawnBattleEffect(0x32C, float(facing * 12) + (x),
                (y) + g_MeilingEffectYAt006590A8, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        break;
    }

    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 12 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage > 7 && animationStage < 11 && RecordedRange(0, 100) < 80) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, static_cast<float>((RecordedRange(0, 75) + 90) * facing) + x,
                ((y) + g_MeilingParticleOffsetYAt0065927C) + static_cast<float>(RecordedRange(0, 70)), facing, 1);
            SpawnBattleEffect(0x352, static_cast<float>(facing * 130) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
        }
        if (y > g_ThresholdAt0065782C && animationStage < 11) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(11);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 16.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 54.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 11.0f;
            velocityY = 3.0f;
            field05C = 0.3f;
            SpawnBattleEffect(0x34F, static_cast<float>(facing * 110) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            PlaySound(0);
        }
        if (animationStage == 11 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        break;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 12 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage > 7 && animationStage < 11 && RecordedRange(0, 100) < 80) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, static_cast<float>((RecordedRange(0, 75) + 90) * facing) + x,
                ((y) + g_MeilingParticleOffsetYAt0065927C) + static_cast<float>(RecordedRange(0, 70)), facing, 1);
            SpawnBattleEffect(0x352, static_cast<float>(facing * 130) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
        }
        if (y > g_ThresholdAt0065782C && animationStage < 11) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(11);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 16.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 54.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 13.0f;
            velocityY = 3.0f;
            field05C = 0.2f;
            SpawnBattleEffect(0x34F, static_cast<float>(facing * 110) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            PlaySound(0);
        }
        if (animationStage == 11 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        break;
    }

    case 0x1FA: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x33C, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x33D, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x33E, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
            SetCameraShake(5.0f);
            PlaySound(2);
            UpdateGaugeTimer(200);
        }
        break;
    }

    case 0x1FB: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x33C, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x33D, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x33E, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
            SetCameraShake(5.0f);
            PlaySound(2);
            UpdateGaugeTimer(200);
        }
        break;
    }

    case 0x1FC: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (y > g_ThresholdAt0065782C && animationStage < 12) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(12);
                break;
            }
        }
        if (animationStage > 2 && animationStage < 12 && RecordedRange(0, 100) < 60) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, ((x) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)),
                ((y) + g_MeilingParticleRadiusAt0065835C) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 3.0f;
            velocityY = 13.0f;
            field05C = 0.9f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x34D, x, y, facing, 1);
        }
        if (animationStage == 9 && animationFrame == 0) {
            PlaySound(1);
        }
        if (animationStage == 12 && animationFrame == 0) {
            ResetSecondaryCounter(11);
        }
        break;
    }

    case 0x1FD: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            velocityX = 0.0f;
        }
        if (y > g_ThresholdAt0065782C && animationStage < 16) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(16);
                break;
            }
        }
        if (animationStage > 5 && animationStage < 16 && RecordedRange(0, 100) < 80) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, ((x) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)),
                ((y) + g_MeilingParticleRadiusAt0065835C) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 16.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 54.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 44.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 8.5f;
            velocityY = 15.0f;
            field05C = 0.95f;
        }
        if (animationStage == 11 && animationFrame == 0) {
            SpawnBattleEffect(0x34D, x, y, facing, 1);
        }
        if (animationStage == 12 && animationFrame == 0) {
            PlaySound(1);
        }
        if (animationStage == 16 && animationFrame == 0) {
            ResetSecondaryCounter(15);
        }
        break;
    }

    case 0x252: {
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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x253: {
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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x254: {
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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x258: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            SpawnBattleEffect(0x323, static_cast<float>(facing * 80) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1);
            UpdateGaugeTimer(0);
        }
        if (animationStage == 8 && animationFrame == 0) {
            field314 = 1.0f;
            if (scriptCounterF00 > 3)
                field314 = 2.0f;
            if (scriptCounterF00 > 6)
                field314 = 3.0f;
            if (scriptCounterF00 > 10)
                field314 = 5.0f;
            SpawnBattleEffect(0x324, static_cast<float>(facing * 120) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1);
        }
        break;
    }

    case 0x259: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 8 && animationFrame == 0) {
            field314 = 0.0f;
            field318 = (y) + g_MeilingLowVolleyYAt006590A0;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + g_MeilingLowVolleyYAt006590A0, facing, 1);
            field314 = 1.0f;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + g_MeilingLowVolleyYAt006590A0, facing, 1);
            field314 = 2.0f;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + g_MeilingLowVolleyYAt006590A0, facing, 1);
            field314 = 3.0f;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + g_MeilingLowVolleyYAt006590A0, facing, 1);
            UpdateGaugeTimer(300);
            PlaySound(4);
        }
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetCameraShake(5.0f);
            SpawnBattleEffect(0x343, static_cast<float>(facing * 70) + x, y, facing, 0);
            SpawnAuxEffect(0x3, static_cast<float>(facing * 70) + x, y, facing, 1);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 100) + x, y, -facing, 1);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 40) + x, y, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(3);
        }
        break;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetCameraShake(10.0f);
            SpawnBattleEffect(0x344, static_cast<float>(facing * 70) + x, y, facing, 0);
            SpawnAuxEffect(0x3, static_cast<float>(facing * 70) + x, y, facing, 1);
            SpawnAuxEffect(0x7F, static_cast<float>(facing * 100) + x, y, -facing, 1);
            SpawnAuxEffect(0x7F, static_cast<float>(facing * 40) + x, y, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(3);
        }
        break;
    }

    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 0;
            field080 = 99;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x326, x, (y) + g_ContactProjectionAt00657888, -facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x326, x, (y) + g_ContactProjectionAt00657888, -facing, 1);
        }
        if (animationStage > 10 && animationStage < 18) {
            velocityY = (velocityY) - g_SubtractAt00657478;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(18);
                ClearMotionFields();
                y = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationFrame == 0)
            field07C = 0;
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 18), (y) + g_MeilingActivationEffectYAt0065788C, facing, 1);
            field36C = (field36C) - g_ContactProjectionAt00657888;
            UpdateGaugeTimer(500);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityY = 3.0f;
            PlaySound(10);
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        }
        if (animationStage == 18 && animationFrame == 0) {
            ResetSecondaryCounter(16);
        }
        break;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 0;
            field080 = 99;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, -facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, -facing, 1);
        }
        if (animationStage > 6 && animationStage < 11 && RecordedRange(0, 100) < 75) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, ((x) + g_MeilingParticleRadiusAt0065835C) - static_cast<float>(RecordedRange(0, 401)),
                ((y) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (animationStage > 10 && animationStage < 18) {
            velocityY = (velocityY) - g_SubtractAt00657478;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(18);
                ClearMotionFields();
                y = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationFrame == 0)
            field07C = 0;
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 18), (y) + g_MeilingActivationEffectYAt0065788C, facing, 1);
            field36C = (field36C) - g_ContactProjectionAt00657888;
            UpdateGaugeTimer(500);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityY = 2.5f;
            PlaySound(11);
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 14) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        }
        if (animationStage == 18 && animationFrame == 0) {
            ResetSecondaryCounter(16);
        }
        break;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1);
            field36C = (field36C) - g_ContactProjectionAt00657888;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x327, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1, 0, 1);
            PlaySound(12);
        }
        if (animationStage == 3 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x328, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1, 0, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x329, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1, 0, 1);
        }
        if (animationStage == 15 && animationFrame == 0) {
            PlaySound(13);
            UpdateGaugeTimer(500);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        break;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1);
            field36C = (field36C) - g_ContactProjectionAt00657888;
        }
        if (animationStage > 11 && animationStage < 27 && inputD <= 0) {
            ResetSecondaryCounter(27);
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x349, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1, 0, 1);
            PlaySound(14);
        }
        if (animationStage == 3 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x34A, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1, 0, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x34B, static_cast<float>(facing * 100) + x, (y) + g_MeilingEffectYAt006590AC, facing, 1, 0, 1);
        }
        if (animationStage == 29 && animationFrame == 0) {
            PlaySound(15);
            UpdateGaugeTimer(500);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        break;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 20) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
            field36C = (field36C) - g_ContactProjectionAt00657888;
            field080 = 1;
            UpdateGaugeTimer(500);
            field07C = 0;
        }
        if (animationStage == 15 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
            if (field07C == 1) {
                SetCameraShake(10.0f);
                PlaySound(16);
                PlaySound(17);
                SpawnBattleEffect(0x345, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
                SpawnBattleEffect(0x346, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
                SpawnBattleEffect(0x347, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 0;
            field080 = 1;
            ClearMotionFields();
        }
        if (velocityX > g_ThresholdAt0065782C) {
            velocityX = (velocityX) - g_MeilingSuperRecoveryDragAt00658350;
        } else {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(16);
            PlaySound(17);
            SpawnBattleEffect(0x345, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x346, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x347, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
        }
        break;
    }

    case 0x2C2: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 20) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
            field36C = (field36C) - g_ContactProjectionAt00657888;
            field080 = 1;
            UpdateGaugeTimer(500);
            field07C = 0;
        }
        if (animationStage == 14 && field07C == 1) {
            PlaySound(18);
            ResetPrimaryCounters(0x2C3);
            SpawnBattleEffect(0x350, static_cast<float>(facing * 94) + x, (y) + g_ContactProjectionAt00657888, facing, 1);
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 13 && animationFrame == 0) {
            SpawnAuxEffect(0x81, static_cast<float>(facing * 100) + x, y, -facing, 1);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 40) + x, y, facing, 1);
        }
        break;
    }

    case 0x2C3: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            field07C = 0;
            field080 = 2;
            ClearMotionFields();
        }
        if (animationStage == 7 && field07C == 1) {
            PlaySound(19);
            SpawnBattleEffect(0x351, static_cast<float>(facing * 45) + x, (y) + g_MeilingEffectYAt006590A8, facing, 1);
        }
        if (velocityX > g_ThresholdAt0065782C) {
            velocityX = (velocityX) - g_MeilingSuperRecoveryDragAt00658350;
        } else {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        if (animationStage == 16 && animationFrame == 0) {
            SetCameraShake(10.0f);
            field07C = 0;
            PlaySound(20);
            PlaySound(21);
            SpawnBattleEffect(0x345, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x346, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnBattleEffect(0x347, static_cast<float>(facing * 76) + x, (y) + g_MeilingLotusEffectYAt00659F38, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 12.0f;
        }
        break;
    }

    case 0x31B: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(4);
        }
        return;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (field370[field39D] == 4) {
                fieldF26 = 0;
                aiCardTimer = 0;
                field318 = 0.0f;
                SpawnBattleEffect(0x3A3, x, (y) + g_ContactProjectionAt00657888, 1, 1);
                if (g_RepeatSettingAt006714D0 == 0) {

            for (int echoEasy = 0; echoEasy < 6; ++echoEasy) {
                field314 = float(echoEasy * 60);
                SpawnBattleEffect(0x397, x, (y) + g_ContactProjectionAt00657888, 1, 1);
            }
                }
                if (g_RepeatSettingAt006714D0 == 1) {

            for (int echoNormal = 0; echoNormal < 6; ++echoNormal) {
                field314 = float(echoNormal * 60);
                SpawnBattleEffect(0x397, x, (y) + g_ContactProjectionAt00657888, 1, 1);
            }
                }
                if (g_RepeatSettingAt006714D0 == 2) {

            for (int echoHard = 0; echoHard < 8; ++echoHard) {
                field314 = float(echoHard * 45);
                SpawnBattleEffect(0x397, x, (y) + g_ContactProjectionAt00657888, 1, 1);
            }
                }
                if (g_RepeatSettingAt006714D0 == 3) {

            for (int echoLunatic = 0; echoLunatic < 8; ++echoLunatic) {
                field314 = float(echoLunatic * 45);
                SpawnBattleEffect(0x397, x, (y) + g_ContactProjectionAt00657888, 1, 1);
            }
                }
            }
        }
        if (animationStage == 20 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 24 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(22);
            field3CF = 1;
        }
        break;
    }

    default:
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;

    advanceFrame:
        AdvanceNestedFrame();
    }
}
