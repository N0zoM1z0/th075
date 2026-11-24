#include "GameSharedState.hpp"
#include "AliceFighter.hpp"

extern float g_AliceArenaLeftAt00658370;
extern float g_AliceEffectYAt00658264;
extern float g_AliceEffectYAt006582E0;
extern float g_AliceEffectYAt00658364;
extern float g_AliceEffectYAt00658368;
extern float g_AliceEffectYAt0065909C;
extern float g_AliceEffectYAt006590A0;
extern float g_AliceEffectYAt006590A8;
extern float g_AliceEffectYAt006591F8;
extern float g_AliceEffectYAt00659478;
extern float g_AliceEffectYAt006595F4;
extern float g_AngleShiftAt00657878;
extern float g_AnimationDeltaAt0065747C;
extern float g_AnimationMaximumAt006583B4;
extern float g_ApproachAt00658058;
extern float g_ApproachLowerAt00658290;
extern float g_ApproachUpperAt006592A4;
extern float g_BounceScaleAt00657F74;
extern float g_BounceThresholdAt006590C0;
extern float g_ContactProjectionAt00657888;
extern double g_ContactScaleAt006583E8;
extern float g_EightShotY1At00658264;
extern float g_ExtraThresholdAt00657D14;
extern float g_F728_RandomOffsetXAt00657878;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_F747_BounceXAt006590BC;
extern float g_F747_BounceYAt00658044;
extern float g_F748_SpeedScaleAt006590B8;
extern float g_JumpGroundCorrectionAt00658058;
extern double g_JumpReflectionAt006583E8;
extern float g_MarisaCommandSpeedLowerAt00657850;
extern float g_MarisaCommandYAt00658268;
extern float g_MarisaResourceYAt006590AC;
extern float g_MarisaResourceYAt00659274;
extern float g_MarisaResourceYAt00659280;
extern float g_MarisaSpecialProjectileYAt00658400;
extern float g_MarisaSpecialProjectileYAt0065929C;
extern float g_OneShotYAt0065928C;
extern float g_ProjectileFallAt006590B4;
extern float g_ReimuC8ClampAt006590B0;
extern float g_ReimuCommandYAt00658268;
extern float g_ReimuLeapDragAt006583FC;
extern float g_ReimuRepeatDragAt00659090;
extern float g_RepeatScaleAt00658348;
extern double g_RiseAt00658050;
extern float g_StopThresholdAt00657480;
extern float g_SubtractAt00657478;
extern float g_ThresholdAt0065782C;
extern float g_YPlusAt00658400;

void AliceFighter::Advance() {
    if (field082 != 0 || opponent->field3BA != 0)
        return;

    switch (action) {
    case 0x0: {
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
        velocityX = -6.0f;
        goto advanceFrame;
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
                velocityY = 15.0f;
                field05C = 0.65f;
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
        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 5.0f;
                velocityY = 15.0f;
                field05C = 0.65f;
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
        if (y > g_ThresholdAt0065782C &&
            ((velocityY = velocityY - field05C), y + velocityY <= g_ThresholdAt0065782C)) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -5.0f;
                velocityY = 15.0f;
                field05C = 0.65f;
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
        if (AdvanceNestedFrame() == field070) {
            if (inputY == 0)
                ResetPrimaryCounters(0);
            else
                ResetPrimaryCounters(1);
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
            field490 = static_cast<float>((velocityX) * g_JumpReflectionAt006583E8);
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            velocityX = (velocityX) + g_ApproachAt00658058;
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
            if (velocityY < g_ApproachLowerAt00658290)
                velocityY = 6.0f;
            field05C = 0.8f;
            if (velocityY > g_ApproachUpperAt006592A4)
                velocityY = 25.0f;
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(animationStage-1);
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
            Fighter::PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {

            Fighter::PlaySharedSound(0x16);

            scriptCounterF00 = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);

            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f,95.0f,0.0f);
        }

        rotationZ = (rotationZ) + g_AngleShiftAt00657878;
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            Fighter::PlaySharedSound(0x16);
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
            scriptCounterF00 = static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x59);
            SetCameraShake(3.0f);
            Fighter::PlaySharedSound(0x16);
            for (int burst=0;burst < 10;++burst)
                SpawnBattleEffect(0x3E4,x,y,1,1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3,x,y,1,1);
            }
            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(animationStage-1);
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

        }
        return;
    }

    case 0x59: {
        if (animationStage == 3) {
            rotationZ = (rotationZ)+g_F728_RandomOffsetYAt00657858;
            velocityY = velocityY-field05C;
            if (velocityY+y <= g_ThresholdAt0065782C) {
                scriptCounterF00 = (velocityX)*g_ContactProjectionAt00657888;
                scriptCounterF02 = (velocityY)*g_ContactProjectionAt00657888;
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x61);
                rotationZ = 0.0f;
                SetCameraShake(2.0f);
                ClearTransformFlag();
                Fighter::PlaySharedSound(0x16);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(3);
        else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*g_F747_BounceXAt006590BC;
            velocityY = static_cast<float>(-scriptCounterF02)*g_F747_BounceYAt00658044;
            field05C = 0.7f;
            ResetTransform(0.0f,95.0f,0.0f);
        }
        return;
    }

    case 0x5D: {
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 15.0f;
        if (animationStage < 11 && y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(11);
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
        if (animationStage == 8 && animationFrame == 0)
            velocityX = 0.0f;
        return;
    }

    case 0x5E: {
        if (animationStage == 0 && animationFrame == 0)
            velocityX = -15.0f;
        if (animationStage < 12 && y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(12);
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
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
        } else if (animationStage == 8 && animationFrame != 0) {
            // Continue the landing animation.
        }
        return;
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

    case 0x60: {
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
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot=0;shot < 10;++shot)
                SpawnBattleEffect(0x3E4,x,y,1,1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3,x,y,1,1);
            }
        }
        if (animationStage <= 6 && animationStage > 2) {
            velocityY = velocityY-field05C;
            if (velocityY + y < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                break;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0x62);
            if ((field3CF) == 0)
                ResetPrimaryCounters(0x63);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*g_F748_SpeedScaleAt006590B8;
            velocityY = static_cast<float>(-scriptCounterF02)*g_F748_SpeedScaleAt006590B8;
            field05C = 2.0f;
        }
        break;
    }

    case 0x61: {
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
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot=0;shot < 10;++shot)
                SpawnBattleEffect(0x3E4,x,y,1,1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3,x,y,1,1);
            }
        }
        if (animationStage <= 6 && animationStage > 2) {
            velocityY = velocityY-field05C;
            if (velocityY + y < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                break;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0x62);
            if ((field3CF) == 0)
                ResetPrimaryCounters(0x63);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*g_F748_SpeedScaleAt006590B8;
            velocityY = static_cast<float>(-scriptCounterF02)*g_F748_SpeedScaleAt006590B8;
            field05C = 2.0f;
        } else if (animationStage == 3 && animationFrame != 0) {

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
        if (g_CombatMode != 3 ||
            field2CD == 0) {
            if (animationStage == 2 &&
                field39D > 0 &&
                opponent->action < 150) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        } else {
            if (animationStage > 1 &&
                field39D > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(field32A[field39D]) == 2) {
                ResetPrimaryCounters(0x31C);

                return;
            }
            if (animationStage > 0 &&
                field39D > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(field32A[field39D]) == 1) {
                ResetPrimaryCounters(0x31C);
                return;
            }
            if (animationStage > 1 &&
                field39D > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(field32A[field39D]) == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(2);
        return;
    }

    case 0x8C: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 0.0f;
            field07C = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
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
        velocityY = velocityY-field05C;
        if (velocityY+y <= g_ThresholdAt0065782C) {
            scriptCounterF00 = static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
            scriptCounterF02 = static_cast<short>((velocityY)*g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x96: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x97: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x98: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x9A: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9B: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9C: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9E: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            velocityX = -6.0f;
            velocityY = 8.0f;
            field05C = 0.75f;

        }

        if (y >= g_ThresholdAt0065782C) {

            velocityY = velocityY-field05C;
            if (y+velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x9F: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA0: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA1: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;

        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA3: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA4: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA5: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -13.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX)*g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA7: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            Fighter::PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing)*30)+(x),

                (y)+g_ContactProjectionAt00657888,
                facing,1);
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        field490 = (-scriptCounterF00)*g_ProjectileFallAt006590B4;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00-10;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA8: {
        cardGauge = (cardGauge)+g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            Fighter::PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing)*30)+(x),

                (y)+g_ContactProjectionAt00657888,
                facing,1);
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX)+g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        field490 = (-scriptCounterF00)*g_ProjectileFallAt006590B4;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00-10;
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityY = velocityY-field05C;
            if (y+velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
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
        if ((y) > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(7);
            return;
        }
        break;
    }

    case 0xC8: {
        field3AC = 1;
        SetCommandSelection(3,4,0xFF);
        if (animationStage == 0 && animationFrame == 0) { velocityX=0.0f; scriptCounterF00=0; }
        if ((velocityX) > g_ReimuC8ClampAt006590B0) {
            velocityX = (velocityX)-g_SubtractAt00657478;
            if ((velocityX) < g_ReimuC8ClampAt006590B0) velocityX=9.0f;
        }
        if (inputY < 0) {
            if (facing*inputX > 0) {
                ResetPrimaryCounters(0xCD);
                break;
            }
            ResetPrimaryCounters(0xCC);
            break;
        }
        if (scriptCounterF00 > 0 && facing*inputX <= 0) {
            ResetPrimaryCounters(0xCF);
            break;
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            if (facing*inputX > 0 && scriptCounterF00 < 6) {
                ResetSecondaryCounter(3);
                ++scriptCounterF00;
                break;
            }
            ResetPrimaryCounters(0xCF);
            break;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 10.0f;
            SpawnAuxEffect(0x7D,float(facing*80)+(x),
                (y)+g_ReimuCommandYAt00658268,facing,1);
            SpawnAuxEffect(0x7E,x,(y)+g_ReimuCommandYAt00658268,
                facing,1);
            PlaySharedSound(31);
        }
        break;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 0.0f;
        if (y > g_ThresholdAt0065782C && animationStage > 2 && animationStage < 11) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(11);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 4.5f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D, x - static_cast<float>(facing * 80),
                (y) + g_MarisaCommandYAt00658268, -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + g_MarisaCommandYAt00658268, -facing, 1);
            PlaySharedSound(0x1F);
        }
        if (animationStage == 11 && animationFrame == 0)
            ResetSecondaryCounter(9);
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.5f;
            velocityY = 5.0f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D,
                static_cast<float>(facing * 80) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (y > g_ThresholdAt0065782C && animationStage > 1) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if (y > g_ThresholdAt0065782C && animationStage > 0) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -8.5f;
            velocityY = 5.0f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D,
                x - static_cast<float>(facing * 80),
                (y) + g_ContactProjectionAt00657888, -facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + g_ContactProjectionAt00657888, -facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (animationStage == 4 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(2);
        }
        return;
    }

    case 0xCC: {
        if ((y == (g_ThresholdAt0065782C)) || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3,4,0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0) ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY-field05C;
            if (y+velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);

        ++animationFrame;
        if (animationFrame>=animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 19.0f;
                field05C = 0.65f;
                field3AC = 0;
                SpawnAuxEffect(0x3C,x,y,1,1);
            }
            if (animationStage>=animationStageCount) animationStage=animationStage-2;
            BindAnimation();
        }
        break;
    }

    case 0xCD: {
        if ((y == (g_ThresholdAt0065782C)) || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3,4,0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0) ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY-field05C;
            if (y+velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);

        ++animationFrame;
        if (animationFrame>=animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 9.0f;
                velocityY = 15.0f;
                field05C = 0.65f;
                field3AC = 0;
                SpawnAuxEffect(0x3C,x,y,1,1);
            }
            if (animationStage>=animationStageCount) animationStage=animationStage-2;
            BindAnimation();
        }
        break;
    }

    case 0xCE: {
        if ((y == (g_ThresholdAt0065782C)) || velocityY > g_ThresholdAt0065782C) {
            SetCommandSelection(3,4,0xFF);
            field088 = 2;
        }
        if (animationStage == 0 && field3AC == 0) ClearMotionFields();
        if (y > g_ThresholdAt0065782C) {
            velocityY = velocityY-field05C;
            if (y+velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        ++animationFrame;
        if (animationFrame>=animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -9.0f;
                velocityY = 15.0f;
                field05C = 0.65f;
                field3AC = 0;
                SpawnAuxEffect(0x3C,x,y,1,1);
            }
            if (animationStage>=animationStageCount) animationStage=animationStage-2;
            BindAnimation();
        }
        break;
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
            facing = static_cast<signed char>(-facing);
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
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0xD1: {
        if (spirit < 2) {
            ResetPrimaryCounters(0);
            return;
        }
        spirit = static_cast<short>(spirit - 3);
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            Fighter::PlaySharedSound(0x2C);
            SpawnBattleEffect(0x3E6, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(0);
        }
        return;
    }

    case 0xD2: {
        if (spirit < 2) {
            ResetPrimaryCounters(9);
            return;
        }
        spirit = static_cast<short>(spirit - 3);
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x3E6, x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            velocityX *= 0.25f;
            velocityY *= 0.25f;
            Fighter::PlaySharedSound(0x2C);
        }
        velocityY -= field05C * 0.25f;
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
        }
        return;
    }

    case 0x12C: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 5;
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
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 8 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 10 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage < 11 && animationFrame == 0)
            field07C = 0;
        return;
    }

    case 0x12D: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0) ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX)-g_JumpGroundCorrectionAt00658058;
            if ((velocityX) < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0);

            scriptCounterF00 = 0;

        }
        if (animationStage == 2 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x12E: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 6;
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
            PlaySharedSound(0x1c);
        if (animationStage == 5 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 7 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 9 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage < 11 && animationFrame == 0)
            field07C = 0;
        return;
    }

    case 0x12F: {
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
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x130: {
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
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 8 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage < 8 && animationFrame == 0)
            field07C = 0;
        return;
    }

    case 0x131: {
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
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x133: {
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
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x370, static_cast<float>(facing * 260) + x,
                (y) + g_AliceEffectYAt006590A0, facing, 1);
        }
        return;
    }

    case 0x134: {
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
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1d);
        return;
    }

    case 0x135: {
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
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x1D);
            SpawnBattleEffect(0x34F, x, y, facing, 1);
            SpawnBattleEffect(0x34E, (x) + g_YPlusAt00658400,
                (y) + g_MarisaCommandSpeedLowerAt00657850, facing, 1);
            SpawnBattleEffect(0x34E, x - g_YPlusAt00658400,
                (y) + g_MarisaCommandSpeedLowerAt00657850, facing, 1);
            SpawnBattleEffect(0x34E, x, (y) + g_AngleShiftAt00657878, facing, 0);
        }
        return;
    }

    case 0x136: {
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
        if (animationStage > 8 && velocityX > g_ThresholdAt0065782C) {
            velocityX -= g_ReimuRepeatDragAt00659090;
            if (velocityX < g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0)
            velocityX = 8.0f;
        if (animationStage == 10 && animationFrame == 0)
            PlaySharedSound(0x1d);
        return;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 5;
            field07C = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 8 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 10 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationFrame == 0 && animationStage < 11)
            field07C = 0;
        return;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 1;
            field07C = 0;
            velocityX = 12.5f;
        }
        if (animationStage > 0) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1d);
        return;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 5;
            field07C = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 5 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 7 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 9 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationFrame == 0 && animationStage < 11)
            field07C = 0;
        return;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 1;
            field07C = 0;
            velocityX = 12.5f;
        }
        if (animationStage > 0) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
        return;
    }

    case 0x18A: {
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
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x327,
                static_cast<float>(facing * 151) + x,
                (y) + g_MarisaSpecialProjectileYAt0065929C, facing, 1);
        }
        return;
    }

    case 0x18B: {
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
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x328,
                static_cast<float>(static_cast<int>(facing) << 7) + x,
                (y) + g_MarisaSpecialProjectileYAt00658400, facing, 1);
        }
        return;
    }

    case 0x190: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x330, static_cast<float>(facing * 7) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x191: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 10 && animationFrame == 0)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 10 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            velocityX = 41.0f;
            SpawnBattleEffect(0x331, static_cast<float>(facing * 51) + x,
                (y) + g_AliceEffectYAt006595F4, facing, 1);
            PlaySound(0);
        }
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x332, static_cast<float>(facing * 93) + x,
                (y) + g_AliceEffectYAt006582E0, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0)
            field07C = 1;
        velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = -6.0f;
            velocityY = 8.0f;
            field05C = 0.5f;
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x34A, static_cast<float>(facing * 26) + x,
                (y) + g_AliceEffectYAt00658364, facing, 1);
            PlaySound(0);
        }
        return;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX = (velocityX) * g_RepeatScaleAt00658348;
            velocityY = (velocityY) * g_RepeatScaleAt00658348;
        }
        if (animationStage > 3)
            velocityY -= field05C;
        if (y + velocityY <= g_ThresholdAt0065782C)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            field314 = 10.0f;
            field318 = -40.0f;
            SpawnBattleEffect(0x34B, static_cast<float>(facing * 27) + x,
                (y) + g_AliceEffectYAt0065909C, facing, 1);
            PlaySound(0);
        }
        return;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);

        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 2) {
            ResetSecondaryCounter(4);
            ++scriptCounterF00;
        }

        return;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + g_AliceEffectYAt00658264, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);

        return;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX = (velocityX) * g_RepeatScaleAt00658348;
            velocityY = (velocityY) * g_RepeatScaleAt00658348;
            scriptCounterF00 = 0;
        }
        if (y + velocityY <= g_ThresholdAt0065782C) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19D: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            velocityX = (velocityX) * g_RepeatScaleAt00658348;
            velocityY = (velocityY) * g_RepeatScaleAt00658348;
            scriptCounterF00 = 0;
        }
        if (y + velocityY <= g_ThresholdAt0065782C) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 4.0f;
            field318 = 15.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 6.0f;
            field318 = 18.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 8.0f;
            field318 = 21.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x19F: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 8.0f;
            field318 = 17.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 10.0f;
            field318 = 18.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 12.0f;
            field318 = 21.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 2.0f;
            field318 = 22.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 3.0f;
            field318 = 24.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 4.0f;
            field318 = 26.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x1A2: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (y > g_ThresholdAt0065782C && animationStage < 9) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 12.0f;
            field05C = 0.8f;
            PlaySound(3);
            UpdateGaugeTimer(250);
            field314 = 6.0f;
            field318 = 8.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 8.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 10.0f;
            field318 = 12.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
            SpawnBattleEffect(0x330,
                (x) + g_F728_RandomOffsetXAt00657878 - static_cast<float>(RecordedRange(0, 60)),
                (y) + g_F728_RandomOffsetYAt00657858 + static_cast<float>(RecordedRange(0, 140)),
                facing, 1);
        }
        if (velocityX > g_ThresholdAt0065782C) {
            velocityX -= g_ReimuLeapDragAt006583FC;
            if (velocityX < g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                ResetSecondaryCounter(12);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 14.0f;
            field05C = 0.8f;
        }
        if (animationStage == 12 && animationFrame == 0)
            ResetSecondaryCounter(10);
        return;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (velocityX > g_ThresholdAt0065782C) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
            SpawnBattleEffect(0x330,
                (x) + g_F728_RandomOffsetXAt00657878 - static_cast<float>(RecordedRange(0, 60)),
                (y) + g_F728_RandomOffsetYAt00657858 + static_cast<float>(RecordedRange(0, 140)),
                facing, 1);
        }
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                ResetSecondaryCounter(12);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 18.0f;
            velocityY = 16.0f;
            field05C = 0.8f;
        }
        if (animationStage == 12 && animationFrame == 0)
            ResetSecondaryCounter(10);
        return;
    }

    case 0x252: {
        if (animationStage == 0 && animationFrame == 0) {
            field366 = field366 - 1;
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
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x21);
            SpawnAuxEffect(0x37, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x253: {
        if (animationStage == 0 && animationFrame == 0) {
            field366 = field366 - 1;
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
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x21);
            SpawnAuxEffect(0x37, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x254: {
        if (animationStage == 0 && animationFrame == 0) {
            field366 = field366 - 1;
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x21);
            SpawnAuxEffect(0x37, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x255: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + g_ContactProjectionAt00657888,
                facing,1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x256: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + g_ContactProjectionAt00657888,
                facing,1);
        }

        break;
    }

    case 0x257: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + g_ContactProjectionAt00657888,
                facing,1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x258: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x327, static_cast<float>(facing * 10) + x,
                (y) + g_MarisaResourceYAt00659280, facing, 1);
            PlaySound(1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x259: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x328, static_cast<float>(facing * 10) + x,
                (y) + g_MarisaResourceYAt00659280, facing, 1);
            PlaySound(1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x329, static_cast<float>(facing * 10) + x,
                (y) + g_MarisaResourceYAt00659280, facing, 1);
            PlaySound(1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX)*g_BounceScaleAt00657F74;
            velocityY = (velocityY)*g_BounceScaleAt00657F74;
            field07C = 1;
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x32D,
                float(facing*100)+(x),
                (y)+g_EightShotY1At00658264,
                facing,1);
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(9);
        break;
    }

    case 0x25E: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 85.0f;
            field318 = 2.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 75.0f;
            field318 = 3.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 95.0f;
            field318 = 1.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 105.0f;
            field318 = 0.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            PlaySound(5);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x25F: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 90.0f;
            field318 = 0.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 100.0f;
            field318 = 1.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 110.0f;
            field318 = 2.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 120.0f;
            field318 = 3.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            PlaySound(5);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x260: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 90.0f;
            field318 = 0.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 80.0f;
            field318 = 1.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 70.0f;
            field318 = 2.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 60.0f;
            field318 = 3.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            PlaySound(5);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x264: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (y > g_ThresholdAt0065782C && animationStage < 9) {
            velocityX = (velocityX) + g_ReimuLeapDragAt006583FC;
            velocityY = velocityY + field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(3);
            UpdateGaugeTimer(250);
            field314 = 0.0f;
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            velocityX = -8.0f;
            velocityY = 16.0f;
            field05C = -1.2f;
            field314 = 1.0f;
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 2.0f;
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x265: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (y > g_ThresholdAt0065782C && animationStage < 9) {
            velocityY = velocityY + field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = -6.0f;
            velocityY = 16.0f;
            field05C = -0.8f;
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 4 && spirit > 0) {
            UpdateGaugeTimer(30);
            field314 = static_cast<float>(70 - scriptCounterF00 * 15);
            SpawnBattleEffect(0x32C, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(3);
            ++scriptCounterF00;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x25D: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x333,
                float(facing*70)+(x),
                (y)+g_OneShotYAt0065928C,
                facing,1);
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        break;
    }

    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            field36C -= g_ContactProjectionAt00657888;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 40),
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (animationStage == 14 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x340, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            field36C -= g_ContactProjectionAt00657888;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 40),
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            field314 = 180.0f;
            SpawnBattleEffect(0x345, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 120.0f;
            SpawnBattleEffect(0x345, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x345, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x345, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x345, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = -120.0f;
            SpawnBattleEffect(0x345, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            SpawnBattleEffect(0x346, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(11);
        }
        return;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33c, static_cast<float>(facing * 65) + x,
                (y) + g_MarisaResourceYAt006590AC, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            field36C -= g_ContactProjectionAt00657888;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 61),
                (y) + g_AliceEffectYAt006591F8, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(13);
            SpawnBattleEffect(0x33e, static_cast<float>(facing * 140) + x,
                (y) + g_MarisaResourceYAt006590AC, facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 6) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            field36C -= g_ContactProjectionAt00657888;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 40),
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (animationStage == 14 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x341, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(9);
        }
        return;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            field36C -= g_ContactProjectionAt00657888;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 40),
                (y) + g_AliceEffectYAt006590A8, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(12);
            UpdateGaugeTimer(500);
            field314 = 180.0f;
            SpawnBattleEffect(0x347, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 120.0f;
            SpawnBattleEffect(0x347, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x347, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x347, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x347, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = -120.0f;
            SpawnBattleEffect(0x347, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 180.0f;
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 120.0f;
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            field314 = -120.0f;
            SpawnBattleEffect(0x348, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            SpawnBattleEffect(0x349, x, (y) + g_ContactProjectionAt00657888, facing, 1);
        }
        return;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33d, static_cast<float>(facing * 65) + x,
                (y) + g_MarisaResourceYAt006590AC, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            field36C -= g_ContactProjectionAt00657888;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 61),
                (y) + g_AliceEffectYAt006591F8, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x33f, static_cast<float>(facing * 180) + x,
                (y) + g_MarisaResourceYAt006590AC, facing, 1);
            PlaySound(14);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 10) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x2D0: {
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
        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                if (RecordedRange(0, 100) < 50)
                    velocityX = 12.0f;
                else
                    velocityX = -12.0f;
                if (facing == 1 && x > g_AnimationMaximumAt006583B4)
                    velocityX = -12.0f;
                if (facing == -1 && x < g_AliceArenaLeftAt00658370)
                    velocityX = -12.0f;
                velocityY = 17.0f;
                field05C = 0.65f;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
    }

    case 0x2DB: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (y > g_ThresholdAt0065782C) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                ClearMotionFields();
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(16);
        if (animationStage == 2 && animationFrame == 0) {
            velocityY = 16.0f;
            velocityX = static_cast<float>(RecordedRange(0, 4) + 10);
            field05C = 0.4f;
        }
        if (animationStage == 10 && animationFrame == 0) {
            if (g_OptionsModeAt006714D0 == 0) {
                for (int shot = 0; shot < 3; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 80);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + g_AliceEffectYAt00658368, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 1) {
                for (int shot = 0; shot < 4; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 120);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + g_AliceEffectYAt00658368, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 2) {
                for (int shot = 0; shot < 5; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 160);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + g_AliceEffectYAt00658368, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 3) {
                for (int shot = 0; shot < 6; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 200);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + g_AliceEffectYAt00658368, facing, 1);
                }
            }
            PlaySound(7);
        }
        return;
    }

    case 0x2DC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 14 && animationFrame == 0) {
            if (g_OptionsModeAt006714D0 == 0) {
                for (int shot = 0; shot < 3; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 1) {
                for (int shot = 0; shot < 4; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 2) {
                for (int shot = 0; shot < 5; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 3) {
                for (int shot = 0; shot < 6; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            PlaySound(7);
        }
        return;
    }

    case 0x2DD: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (y > g_ThresholdAt0065782C && animationStage < 9) {
            velocityY = velocityY + field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            field05C = -0.5f;
        }
        if (animationStage == 8 && animationFrame == 0 &&
                scriptCounterF00 < g_OptionsModeAt006714D0 * 2 + 2) {
            field314 = static_cast<float>(scriptCounterF00 * 20);
            field318 = static_cast<float>(scriptCounterF00 * 30);
            SpawnBattleEffect(900, static_cast<float>(facing * 10) + x,
                (y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(3);
            ++scriptCounterF00;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x2E5: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x38A,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            aiCardTimer = static_cast<short>(360 - g_OptionsModeAt006714D0 * 60);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x2EF: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (y > g_ThresholdAt0065782C && animationStage < 9) {
            velocityY = velocityY + field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            if ((x > g_AnimationMaximumAt006583B4 && facing == -1) ||
                    (x < g_AliceArenaLeftAt00658370 && facing == 1)) {
                velocityX = 10.0f;
                velocityY = 15.0f;
                field05C = -0.4f;
            } else {
                velocityX = -1.5f;
                velocityY = 8.0f;
                field05C = -0.09f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(3);
            for (int shot = 0; shot < g_OptionsModeAt006714D0 * 3 + 6; ++shot) {
                field314 = static_cast<float>(RecordedRange(0, 180) - 90);
                field318 = static_cast<float>(RecordedRange(0, 80) + 150);
                SpawnBattleEffect(0x38B, static_cast<float>(facing * 10) + x,
                    (y) + g_ContactProjectionAt00657888, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x31B: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x, y, facing, 1);
        }
        if (animationStage == 9 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        }
        break;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 11 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 15 && animationFrame == 0 && scriptCounterF00 < 4) {
            ++scriptCounterF00;
            ResetSecondaryCounter(0xD);
            field3CF = 1;
        }
        return;
    }

    default:
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;

    advanceFrame:
        AdvanceNestedFrame();
    }
}
