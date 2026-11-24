#include "SuikaFighter.hpp"

extern float g_AdditionalGravityAt00659090;
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
extern float g_ExtraThresholdAt00657D14;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_F747_BounceXAt006590BC;
extern float g_F747_BounceYAt00658044;
extern float g_F748_SpeedScaleAt006590B8;
extern float g_JumpGroundCorrectionAt00658058;
extern double g_JumpReflectionAt006583E8;
extern float g_MarisaSpecialProjectileYAt00658400;
extern float g_MarisaSpecialProjectileYAt0065929C;
extern signed char g_ModeAt006714B4;
extern float g_ProjectileFallAt006590B4;
extern float g_RepeatScaleAt00658348;
extern double g_RiseAt00658050;
extern unsigned char g_SequenceByteAt0066C239;
extern unsigned char g_SequenceByteAt0066C23A;
extern unsigned char g_SequenceCounterAt00671622;
extern signed char g_StateRepeatLevelAt006714D0;
extern float g_StopThresholdAt00657480;
extern unsigned char g_StoryStatusAt00671623;
extern float g_SubtractAt00657478;
extern float g_SuikaOffsetAt00657834;
extern float g_SuikaOffsetAt00657850;
extern float g_SuikaOffsetAt00657874;
extern float g_SuikaOffsetAt00657884;
extern float g_SuikaOffsetAt00657888;
extern float g_SuikaOffsetAt0065788C;
extern float g_SuikaOffsetAt00657CF8;
extern float g_SuikaOffsetAt00657D10;
extern float g_SuikaOffsetAt006581DC;
extern float g_SuikaOffsetAt00658264;
extern float g_SuikaOffsetAt00658268;
extern float g_SuikaOffsetAt00658368;
extern float g_SuikaOffsetAt00658398;
extern float g_SuikaOffsetAt006583F8;
extern float g_SuikaOffsetAt00658400;
extern float g_SuikaOffsetAt00659094;
extern float g_SuikaOffsetAt006590A4;
extern float g_SuikaOffsetAt006590A8;
extern float g_SuikaOffsetAt006590AC;
extern float g_SuikaOffsetAt00659138;
extern float g_SuikaOffsetAt006591E4;
extern float g_SuikaOffsetAt006591EC;
extern float g_SuikaOffsetAt006591F8;
extern float g_SuikaOffsetAt0065920C;
extern float g_SuikaOffsetAt00659238;
extern float g_SuikaOffsetAt0065927C;
extern float g_SuikaOffsetAt00659280;
extern float g_SuikaOffsetAt00659290;
extern float g_SuikaOffsetAt0065929C;
extern float g_SuikaOffsetAt006593F4;
extern float g_SuikaOffsetAt006595B4;
extern float g_SuikaOffsetAt00659B68;
extern float g_SuikaOffsetAt00659B70;
extern float g_SuikaOffsetAt00659E14;
extern float g_SuikaOffsetAt00659E18;
extern float g_SuikaOffsetAt00659E1C;
extern float g_SuikaOffsetAt00659E20;
extern float g_ThresholdAt0065782C;

void SuikaFighter::Advance() {
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
        velocityX = 5.5f; goto advanceFrame;
    }

    case 0x5: {
        velocityX = -5.5f; goto advanceFrame;
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
        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= (field072)) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 16.0f;
                field05C = 0.75f;
                if (field3AC > 0) {
                    velocityX = 3.0f;
                    velocityY = 15.0f;
                    field05C = 1.25f;
                }
            }
            if (animationStage >= (field070))
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
                velocityX = 8.0f;
                velocityY = 16.0f;
                field05C = 0.75f;
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
                velocityX = -8.0f;
                velocityY = 16.0f;
                field05C = 0.75f;
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
            Fighter::PlaySharedSound(30);
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount) {
            if (inputY == 0)
                ResetPrimaryCounters(3);
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
            sequenceTimer = 0;
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
            sequenceTimer = 0;
            return;
        }
        if (animationStage == 7 && sequenceTimer < 1) {
            ++sequenceTimer;
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
            sequenceTimer = 0;
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
            sequenceTimer = 0;
            return;
        }
        if (animationStage == 7 && sequenceTimer < 1) {
            ++sequenceTimer;
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
            sequenceTimer = 0;
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
            sequenceTimer = 0;
            return;
        }
        if (animationStage == 7 && sequenceTimer < 1) {
            ++sequenceTimer;
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
        if (animationStage == 3 && velocityY < g_StopThresholdAt00657480) {
            ResetSecondaryCounter(4);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
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
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
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
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
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
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
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
            Fighter::PlaySharedSound(0x16);
            sequenceTimer = 0;
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {

            Fighter::PlaySharedSound(0x16);

            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);

            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
        return;
    }

    case 0x4C: {
        if (sequenceTimer == 0) {
            ++sequenceTimer;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }

        rotationZ = (rotationZ) + g_AngleShiftAt00657878;
        velocityY = velocityY - field05C;
        if (velocityY + y <= g_ThresholdAt0065782C) {
            Fighter::PlaySharedSound(0x16);
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
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
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x59);
            SetCameraShake(3.0f);
            Fighter::PlaySharedSound(0x16);
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
            rotationZ = (rotationZ) + g_F728_RandomOffsetYAt00657858;
            velocityY = velocityY - field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                sequenceTimer = (velocityX) * g_ContactProjectionAt00657888;
                fieldEFE = (velocityY) * g_ContactProjectionAt00657888;
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
            velocityX = static_cast<float>(sequenceTimer) * g_F747_BounceXAt006590BC;
            velocityY = static_cast<float>(-fieldEFE) * g_F747_BounceYAt00658044;
            field05C = 0.7f;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }
        return;
    }

    case 0x5D: {
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 11.0f;
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
        if (animationStage == 14 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        return;
    }

    case 0x5E: {
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -11.0f;
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
        if (animationStage == 14 && animationFrame == 0) {
            velocityX = 0.0f;
        } else if (animationStage == 14 && animationFrame != 0) {
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
        if (facing * inputX > 0 &&
                (static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0 ||
                 static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0))
            sequenceTimer = 1;
        if (facing * inputX < 0 &&
                (static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0 ||
                 static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0))
            sequenceTimer = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot = 0; shot < 10; ++shot)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage >= 3 && animationStage <= 5) {
            velocityY -= field05C;
            if (velocityY + y < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(6);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0)
                ResetPrimaryCounters(0x63);
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(sequenceTimer) * g_F748_SpeedScaleAt006590B8;
            velocityY = static_cast<float>(-fieldEFE) * g_F748_SpeedScaleAt006590B8;
            field05C = 2.0f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x61: {
        if (facing * inputX > 0 &&
                (static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0 ||
                 static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0))
            sequenceTimer = 1;
        if (facing * inputX < 0 &&
                (static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0 ||
                 static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0))
            sequenceTimer = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot = 0; shot < 10; ++shot)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage >= 3 && animationStage <= 5) {
            velocityY -= field05C;
            if (velocityY + y < g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(6);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0)
                ResetPrimaryCounters(0x63);
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(sequenceTimer) * g_F748_SpeedScaleAt006590B8;
            velocityY = static_cast<float>(-fieldEFE) * g_F748_SpeedScaleAt006590B8;
            field05C = 2.0f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 6 && animationFrame != 0) {
            // Continue the landing animation.
        }
        return;
    }

    case 0x62: {
        if (static_cast<int>(facing) * inputX > 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            sequenceTimer = 1;
        if (static_cast<int>(facing) * inputX < 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            sequenceTimer = 2;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x5F);
            if (sequenceTimer == 1)
                ResetPrimaryCounters(0x5D);
            if (sequenceTimer == 2)
                ResetPrimaryCounters(0x5E);
        }
        return;
    }

    case 0x63: {
        if (g_ModeAt006714B4 != 3 || field2CD == 0) {
            if (animationStage == 2 && field39D > 0 && opponent->action < 150) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        } else {
            if (animationStage > 1 && field39D > 0 && opponent->action < 150 &&
                    static_cast<signed char>(field32A[field39D]) == 2) {
                ResetPrimaryCounters(0x31C);
                if (field370[field39D] == 5) {
                    ResetPrimaryCounters(0x31D);
                }
                return;
            }
            if (animationStage > 0 && field39D > 0 && opponent->action < 150 &&
                    static_cast<signed char>(field32A[field39D]) == 1) {
                ResetPrimaryCounters(0x31C);
                return;
            }
            if (animationStage > 1 && field39D > 0 && opponent->action < 150 &&
                    static_cast<signed char>(field32A[field39D]) == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
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
            sequenceTimer = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && sequenceTimer < 5) {
            ++sequenceTimer;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x8F: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
            sequenceTimer = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && sequenceTimer < 7) {
            ++sequenceTimer;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x90: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            field07C = 0;
            sequenceTimer = 0;
        }
        if ((velocityX) < g_ThresholdAt0065782C) {
            velocityX = (velocityX) + g_JumpGroundCorrectionAt00658058;
            if ((velocityX) > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && sequenceTimer < 7) {
            ++sequenceTimer;
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
            sequenceTimer = static_cast<short>((velocityX) * g_ContactProjectionAt00657888);
            fieldEFE = static_cast<short>((velocityY) * g_ContactProjectionAt00657888);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x96: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x97: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x98: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x9A: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9B: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9C: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
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

        if (y >= g_ThresholdAt0065782C) {

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
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA0: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA1: {
        cardGauge = (cardGauge) + g_AnimationDeltaAt0065747C;
        if ((cardGauge) > g_AnimationMaximumAt006583B4)
            cardGauge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
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
            field490 = (velocityX) * g_JumpReflectionAt006583E8;
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
            Fighter::PlaySharedSound(0x2C);
            sequenceTimer = 0xB4;
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
        field490 = (-sequenceTimer) * g_ProjectileFallAt006590B4;
        if (sequenceTimer > 0)
            sequenceTimer = sequenceTimer - 10;
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
            Fighter::PlaySharedSound(0x2C);
            sequenceTimer = 0xB4;
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
        field490 = (-sequenceTimer) * g_ProjectileFallAt006590B4;
        if (sequenceTimer > 0)
            sequenceTimer = sequenceTimer - 10;
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
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(8);
            return;
        }
        return;
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
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(10);
            return;
        }
        return;
    }

    case 0xC8: {
        SetCommandSelection(3, 4, 0xFF);
        field3AC = 1;
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            velocityX = 9.0f;
        }
        if (velocityX > g_SuikaOffsetAt00657850) {
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_SuikaOffsetAt00657850)
                velocityX = 10.0f;
        }
        if (inputY < 0) {
            if (facing * inputX > 0) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            ResetPrimaryCounters(0xCC);
            return;
        }
        if (animationStage > 5 && facing * inputX <= 0) {
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (facing * inputX > 0 && sequenceTimer < 4) {
                ResetSecondaryCounter(5);
                ++sequenceTimer;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        return;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            sequenceTimer = 0;
        }
        if (animationStage > 5 && facing * inputX >= 0) {
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (facing * inputX < 0 && sequenceTimer < 4) {
                ResetSecondaryCounter(6);
                ++sequenceTimer;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            sequenceTimer = 0;
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
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.5f;
            velocityY = 4.5f;
            field05C = 0.45f;
        }
        if (animationStage == 7 && animationFrame == 0 && sequenceTimer < 1) {
            ResetSecondaryCounter(3);
            ++sequenceTimer;
        }
        return;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -7.5f;
            velocityY = 4.0f;
            field05C = 0.45f;
        }
        if (animationStage == 7 && animationFrame == 0 && sequenceTimer < 1) {
            ResetSecondaryCounter(3);
            ++sequenceTimer;
        }
        return;
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
        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
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
        if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 10.0f;
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
            if (animationStage == 4) {
                velocityX = -10.0f;
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

    case 0x12C: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 8;
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
        if (animationFrame == 0 && animationStage < 12)
            field07C = 0;
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x12D: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 1;
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
            sequenceTimer = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(800, static_cast<float>(facing * 128) + x,
                y - g_SuikaOffsetAt006590A4, facing, 1);
            PlaySound(10);
        }
        return;
    }

    case 0x12E: {
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
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1D);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetCameraShake(5.0f);
            SpawnBattleEffect(0x340, static_cast<float>(facing * 190) + x, 0.0f, facing, 0);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 190) + x, 0.0f, 1, 0);
            PlaySound(0x11);
        }
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
        if (animationStage > 2) {
            velocityX -= g_AdditionalGravityAt00659090;
            if (velocityX < g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0) {
            field3AC = 0;
            velocityX = 8.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        return;
    }

    case 0x130: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(0xA);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        } else if (animationStage < animationStageCount) {
            // Continue the current animation.
        }
        if (animationStage == 5 && animationFrame == 0)
            PlaySharedSound(0x1B);
        return;
    }

    case 0x131: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(0xA);
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
        if (animationStage == 3 && animationFrame == 0) {
            SetCameraShake(5.0f);
            SpawnBattleEffect(0x342, static_cast<float>(facing * 90) + x, (y) + g_SuikaOffsetAt00658268, facing, 1);
            SpawnBattleEffect(0x343, static_cast<float>(facing * 90) + x, (y) + g_SuikaOffsetAt00658268, facing, 1);
            PlaySound(0x18);
        }
        return;
    }

    case 0x132: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f; field05C = 0.0f; velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) { field080 = 1; field07C = 0; }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0)
            PlaySound(0x20);
        break;
    }

    case 0x133: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            field080 = 1;
            field07C = 0;
        }
        if (y > g_ThresholdAt0065782C && animationStage > 2 && animationStage < 6) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(6);
                SetCameraShake(10.0f);
                SpawnBattleEffect(0x340, x, 0.0f, facing, 0);
                SpawnAuxEffect(0x81, x, 0.0f, 1, 0);
                SpawnAuxEffect(0x81, x, 0.0f, -1, 0);
                PlaySound(0x11);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 14.0f;
            field05C = 1.5f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
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
            sequenceTimer = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(0x20);
        }
        return;
    }

    case 0x135: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (y == g_ThresholdAt0065782C) {
            velocityX -= g_AdditionalGravityAt00659090;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (y > g_ThresholdAt0065782C && animationStage > 3 && animationStage < 6) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(6);
                velocityY = 0.0f;
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            sequenceTimer = 0;
            return;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 13.5f;
            velocityY = 6.5f;
            field05C = 1.0f;
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
        if (y == g_ThresholdAt0065782C) {
            velocityX -= g_AdditionalGravityAt00659090;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (y > g_ThresholdAt0065782C && animationStage > 4 && animationStage < 7) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(7);
                y = 0.0f;
                velocityY = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 15.0f;
            velocityY = 6.0f;
            field05C = 0.9f;
        }
        return;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 2;
            field07C = 0;
            velocityX = 7.0f;
        }
        if (animationStage > 16) {
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 17 && animationFrame == 0) {
            field07C = 0;
        }
        return;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            field080 = 1;
            field07C = 0;
            field05C = 0.0f;
            velocityY = 0.0f;
            velocityX = 10.0f;
        }
        if (velocityX > g_ThresholdAt0065782C && y == g_ThresholdAt0065782C) {
            velocityX -= g_SuikaOffsetAt006583F8;
            if (velocityX < g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (y > g_ThresholdAt0065782C && animationStage > 3 && animationStage < 17) {
            if (field07C != 0) {
                ResetSecondaryCounter(17);
                velocityX = -3.0f;
                velocityY = 13.0f;
                field05C = 0.75f;
                field07C = 1;
                return;
            }
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(23);
                return;
            }
        }
        if (y > g_ThresholdAt0065782C && animationStage > 16 && animationStage < 23) {
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                ResetSecondaryCounter(23);
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 12.0f;
            velocityY = 9.0f;
            field05C = 0.5f;
        }
        if (animationStage == 17 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        if (animationStage == 23 && animationFrame == 0) {
            ResetSecondaryCounter(21);
        }
        return;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
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
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 6;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationFrame == 0 && animationStage < 11)
            field07C = 0;
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        if (animationStage == 7 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        if (animationStage == 9 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        return;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            field080 = 3;
            field07C = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 7) {
            velocityX -= g_SuikaOffsetAt00659094;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationFrame == 0 && animationStage < 9)
            field07C = 0;
        return;
    }

    case 0x18A: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            velocityX = 15.0f;
            sequenceTimer = 0;
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
            sequenceTimer = 0;
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
        if (animationStage == 7 && animationFrame == 0 && sequenceTimer < 2) {
            ++sequenceTimer;
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
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x323, static_cast<float>(facing * 100) + x, (y) + g_SuikaOffsetAt00657888, facing, 1);
            UpdateGaugeTimer(150);
            PlaySound(0);
        }
        return;
    }

    case 0x191: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x327, static_cast<float>(facing * 100) + x, (y) + g_SuikaOffsetAt00657888, facing, 1);
            UpdateGaugeTimer(150);
            PlaySound(0);
        }
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x328, static_cast<float>(facing * 20) + x, (y) + g_SuikaOffsetAt006581DC, facing, 1);
            UpdateGaugeTimer(150);
            PlaySound(0);
        }
        return;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_BounceScaleAt00657F74;
            velocityY = (velocityY) * g_BounceScaleAt00657F74;
            field07C = 1;
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x323, static_cast<float>(facing * 85) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            UpdateGaugeTimer(150);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x195: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_BounceScaleAt00657F74;
            velocityY = (velocityY) * g_BounceScaleAt00657F74;
            field07C = 1;
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x327, static_cast<float>(facing * 85) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            UpdateGaugeTimer(150);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x196: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x338, static_cast<float>(facing * 100) + x, (y) + g_SuikaOffsetAt00657888, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(0);
        }
        return;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 30.0f;
            SpawnBattleEffect(0x338, static_cast<float>(facing * 100) + x, (y) + g_SuikaOffsetAt00657888, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(0);
        }
        return;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0) {
            field314 = 20.0f;
            SpawnBattleEffect(0x339, static_cast<float>(facing * 20) + x, (y) + g_SuikaOffsetAt006581DC, facing, 0);
            UpdateGaugeTimer(300);
            PlaySound(0);
        }
        return;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_BounceScaleAt00657F74;
            velocityY = (velocityY) * g_BounceScaleAt00657F74;
            field07C = 1;
        }
        if (animationStage == 5 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x338, static_cast<float>(facing * 85) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19B: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_BounceScaleAt00657F74;
            velocityY = (velocityY) * g_BounceScaleAt00657F74;
            field07C = 1;
        }
        if (animationStage == 5 && animationFrame == 0) {
            field314 = -30.0f;
            SpawnBattleEffect(0x338, static_cast<float>(facing * 85) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
            sequenceTimer = 0;
        }
        if (animationStage > 6 && sequenceTimer < 2 && inputB == 1 && spirit > 0) {
            ++sequenceTimer;
            ResetSecondaryCounter(1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x33D, static_cast<float>(facing * 100) + x, (y) + g_SuikaOffsetAt00657888, facing, 1);
            UpdateGaugeTimer(100);
            PlaySound(0);
        }
        return;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0) {
            field314 = 35.0f;
            SpawnBattleEffect(0x33C, static_cast<float>(facing * 20) + x, (y) + g_SuikaOffsetAt006581DC, facing, 0);
            UpdateGaugeTimer(300);
            PlaySound(0);
        }
        return;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * g_BounceScaleAt00657F74;
            velocityY = (velocityY) * g_BounceScaleAt00657F74;
            field07C = 1;
            sequenceTimer = 0;
        }
        if (animationStage > 5 && sequenceTimer < 2 && inputB == 1 && spirit > 0) {
            ++sequenceTimer;
            ResetSecondaryCounter(1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x33D, static_cast<float>(facing * 85) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            UpdateGaugeTimer(100);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if (animationStage > 9) {
            if (velocityX > g_ThresholdAt0065782C)
                velocityX -= g_SubtractAt00657478;
            else
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        } else if (animationStage < animationStageCount) {
            // Continue the current animation.
        }
        if (animationStage == 11 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x32B, static_cast<float>(facing * 130) + x, (y) + g_SuikaOffsetAt00658400, facing, 1);
            UpdateGaugeTimer(250);
            SetCameraShake(5.0f);
            PlaySound(1);
            SpawnAuxEffect(0x7F, x, 0.0f, facing, 0);
        }
        if (animationStage == 13 && animationFrame == 0) {
            if (sequenceTimer > 4) {
                ++sequenceTimer;
                ResetSecondaryCounter(12);
            }
        }
        return;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if (animationStage > 9) {
            if (velocityX > g_ThresholdAt0065782C)
                velocityX -= g_SubtractAt00657478;
            else
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            field314 = 75.0f;
            SpawnBattleEffect(0x32B, static_cast<float>(facing * 83) + x, (y) + g_SuikaOffsetAt006595B4, facing, 1);
            UpdateGaugeTimer(250);
            SetCameraShake(5.0f);
            PlaySound(1);
            SpawnAuxEffect(0x7F, x, 0.0f, facing, 0);
        }
        return;
    }

    case 0x1F6: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 8 && y + velocityY <= g_ThresholdAt0065782C) {
            PlaySound(3);
            velocityX = -4.0f;
            velocityY = 10.0f;
            y = 0.0f;
            SetCameraShake(5.0f);
            SpawnBattleEffect(0x32E, static_cast<float>(facing * 80) + x, y, facing, 1);
            ResetSecondaryCounter(9);
            return;
        }
        if (animationStage > 8 && animationStage < 29) {
            velocityY -= g_AdditionalGravityAt00659090;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(29);
                velocityX = 0.0f;
                velocityY = 0.0f;
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            velocityX = 16.0f;
            velocityY = -16.0f;
            PlaySound(2);
        }
        if (animationStage == 29 && animationFrame == 0) {
            ResetSecondaryCounter(27);
        }
        return;
    }

    case 0x1F7: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
        }
        if (animationStage == 8 && y + velocityY <= g_ThresholdAt0065782C) {
            PlaySound(3);
            velocityX = -3.0f;
            velocityY = 8.0f;
            y = 0.0f;
            SetCameraShake(5.0f);
            SpawnBattleEffect(0x32E, static_cast<float>(facing * 80) + x, y, facing, 1);
            ResetSecondaryCounter(9);
            return;
        }
        if (animationStage > 8 && animationStage < 29) {
            velocityY -= g_AdditionalGravityAt00659090;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(29);
                velocityX = 0.0f;
                velocityY = 0.0f;
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            velocityX = 16.0f;
            velocityY = -16.0f;
            PlaySound(2);
        }
        if (animationStage == 29 && animationFrame == 0) {
            ResetSecondaryCounter(27);
        }
        return;
    }

    case 0x252: {
        if (animationStage == 0 && animationFrame == 0) {
            --field366;
            ClearMotionFields();
                    field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if ((spiritCooldown) == 0 && field07C == 1)
            spirit = 1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888,
                facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        break;
    }

    case 0x253: {
        if (animationStage == 0 && animationFrame == 0) {
            --field366;
            ClearMotionFields();
                    field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if ((spiritCooldown) == 0 && field07C == 1)
            spirit = 1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888,
                facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        break;
    }

    case 0x254: {
        if (animationStage == 0 && animationFrame == 0) {
            --field366;
            ClearMotionFields();
                    field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888,
                facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        break;
    }

    case 0x255: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888,
                facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && sequenceTimer < 1) {
            ++sequenceTimer;
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
            sequenceTimer = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888,
                facing, 1);
        }

        break;
    }

    case 0x257: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
            field3AC = 0;
            sequenceTimer = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + g_ContactProjectionAt00657888,
                facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && sequenceTimer < 1) {
            ++sequenceTimer;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x258: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            PlaySound(4);
            for (int shot = 0; shot < 8; ++shot) {
                field314 = static_cast<float>(RecordedRange(0, 120) - 60);
                field318 = static_cast<float>(RecordedRange(0, 2) + 6);
                SpawnBattleEffect(0x321, static_cast<float>(facing * 50) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            }
        }
        return;
    }

    case 0x259: {
        if (animationStage == 0 && animationFrame == 0) {
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(9);
            UpdateGaugeTimer(250);
            for (int shot = 0; shot < 16; ++shot) {
                field314 = static_cast<float>(-RecordedRange(40, 70));
                field318 = static_cast<float>(RecordedRange(0, 6) + 6);
                SpawnBattleEffect(0x322, static_cast<float>(facing * 50) + x, (y) + g_SuikaOffsetAt00659280, facing, 1);
            }
        }
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(5);
            SetCameraShake(5.0f);
            UpdateGaugeTimer(250);
            for (int shot = 0; shot < 12; ++shot) {
                field314 = static_cast<float>(RecordedRange(0, 40) - 90);
                field318 = static_cast<float>(RecordedRange(0, 22) + 5);
                SpawnBattleEffect(0x32C, static_cast<float>((RecordedRange(0, 190) + 10) * facing) + x,
                    y, facing, 1);
            }
            SpawnBattleEffect(0x340, static_cast<float>(facing * 100) + x, 0.0f, facing, 0);
            SpawnAuxEffect(0x7F, x, 0.0f, facing, 0);
        }
        return;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            field07C = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(5);
            SetCameraShake(5.0f);
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x340, static_cast<float>(facing * 100) + x, 0.0f, facing, 0);
            SpawnBattleEffect(0x341, static_cast<float>(facing * 100) + x, 0.0f, facing, 0);
            SpawnAuxEffect(0x7F, x, 0.0f, facing, 0);
        }
        return;
    }

    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            fieldEFE = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field080 = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (fieldF04 == 0 && opponent->action == 0x61 && animationStage > 32) {
            SetCameraShake(15.0f);
            ++fieldF04;
            PlaySound(23);
            ApplyOpponentGaugeChange(2000, 100, 1);
        }
        if (animationStage > 8 && animationStage < 17) {
            if (opponent->y == g_ThresholdAt0065782C)
                field080 = 1;
            else
                field080 = 0;
            if (field07C == 1) {
                ClearMotionFields();
                ResetSecondaryCounter(17);
                opponent->ResetPrimaryCounters(0x65);
                opponent->velocityX = 0.0f;
                opponent->velocityY = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                return;
            }
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x2BD);
                return;
            }
        }
        if (animationStage > 16 && animationStage < 35) {
            if (animationStage < 21) {
                AdjustCameraOffset(0);
                velocityY -= g_SubtractAt00657478;
                if (velocityY < g_ThresholdAt0065782C)
                    velocityY = 0.0f;
                velocityX = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
            }
            if (animationStage > 20 && animationStage < 31) {
                AdjustCameraOffset(0);
                --fieldEFE;
                SetCameraShake(2.0f);
                if (scriptCounterF00 < 60) {
                    if (fieldEFE <= 0) {
                        SpawnBattleEffect(0x331, x - static_cast<float>(facing * 960),
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        fieldEFE = 8;
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 2) {
                        SpawnBattleEffect(0x331, static_cast<float>(facing * 960) + x,
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 4) {
                        SpawnBattleEffect(0x331, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            (y) + g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 6) {
                        SpawnBattleEffect(0x331, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            y - g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                }
                if (animationStage < 23) {
                    opponent->x = static_cast<float>(facing * 45) + x;
                    opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                }
            }
        }
        if (animationStage > 34) {
            velocityY -= g_JumpGroundCorrectionAt00658058;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (scriptCounterF02 == 0 && opponent->action == 0x61) {
            ++scriptCounterF02;
            SetCameraShake(15.0f);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(42);
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 15.0f;
            velocityY = 10.0f;
            field05C = 0.6f;
        }
        if (animationStage == 17 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        if (animationStage == 19 && animationFrame == 0) {
            velocityY = 12.5f;
        }
        if (animationStage == 21 && animationFrame == 0) {
            if (sequenceTimer < 2) {
                ++sequenceTimer;
                ResetSecondaryCounter(19);
                return;
            }
            sequenceTimer = 0;
        }
        if (animationStage == 23 && animationFrame == 0) {
            if (sequenceTimer < 0) {
                ++sequenceTimer;
                ResetSecondaryCounter(21);
                return;
            }
            PlaySound(19);
            sequenceTimer = 0;
            opponent->ResetPrimaryCounters(0x6D);
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591EC;
            opponent->facing = facing;
        }
        if (animationStage == 24 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 45.0f;
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658398;
        }
        if (animationStage == 25 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 5.0f;
            opponent->x = static_cast<float>(facing * 50) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 26 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 25.0f;
            opponent->x = static_cast<float>(facing * 25) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658368;
        }
        if (animationStage == 27 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 85.0f;
            opponent->x = x - static_cast<float>(facing * 20);
            opponent->y = (y) + g_SuikaOffsetAt0065788C;
        }
        if (animationStage == 28 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 160.0f;
            opponent->x = x - static_cast<float>(facing * 60);
            opponent->y = (y) + g_SuikaOffsetAt006581DC;
        }
        if (animationStage == 29 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -165.0f;
            opponent->x = x - static_cast<float>(facing * 45);
            opponent->y = (y) + g_SuikaOffsetAt00659B70;
        }
        if (animationStage == 30 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -110.0f;
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591F8;
        }
        if (animationStage == 31 && animationFrame == 0) {
            if (sequenceTimer < 11) {
                ++sequenceTimer;
                ResetSecondaryCounter(24);
                opponent->ResetTransform(0.0f, 0.0f, 0.0f);
                opponent->rotationZ = -45.0f;
                opponent->x = static_cast<float>(facing * 44) + x;
                opponent->y = (y) + g_SuikaOffsetAt00658398;
                return;
            }
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt006590AC;
        }
        if (animationStage == 32 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->ResetPrimaryCounters(0x6F);
            opponent->facing = -facing;
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 33 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
            opponent->ResetPrimaryCounters(0x49);
            opponent->field094 = 36.0f;
            opponent->field098 = -18.0f;
            opponent->facing = -facing;
            PlaySound(20);
        }
        return;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
            field080 = 5;
        }
        if (animationStage == 11 && field07C == 1 && field3CF == 1) {
            ResetPrimaryCounters(0x2BF);
            opponent->ResetPrimaryCounters(0x66);
            if (x > g_SuikaOffsetAt00659E20 && facing == 1)
                x = 750.0f;
            if (x < g_SuikaOffsetAt00659E1C && facing == -1)
                x = 550.0f;
            opponent->x = static_cast<float>(facing * 510) + x;
            opponent->velocityX = 0.0f;
            opponent->y = 0.0f;
            opponent->ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(6);
        }
        if (animationStage == 7 && animationFrame == 0 && sequenceTimer < 5) {
            ++sequenceTimer;
            ResetSecondaryCounter(5);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            PlaySound(7);
        }
        if (animationStage == 11 && animationFrame == 0) {
            UpdateGaugeTimer(500);
        }
        return;
    }

    case 0x2BF: {
        if (animationStage == 2)
            SetCameraShake(2.0f);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetCameraShake(5.0f);
            opponent->x = static_cast<float>(facing * 470) + x;
            SpawnBattleEffect(0x333, x, y, facing, 1);
            PlaySound(8);
        }
        if (animationStage == 3 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 450) + x;
        }
        if (animationStage == 4 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 400) + x;
        }
        if (animationStage == 5 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 330) + x;
        }
        if (animationStage == 6 && animationFrame == 0) {
            opponent->ResetPrimaryCounters(0x35);
            opponent->facing = facing;
            fieldF1C = 450;
        }
        return;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
            field080 = 1;
        }
        if (animationStage > 6 && animationStage < 16) {
            if (scaleX < g_StopThresholdAt00657480) {
                scaleX = (scaleX) + g_RepeatScaleAt00658348;
                scaleY = (scaleY) + g_RepeatScaleAt00658348;
            } else {
                scaleX = 2.0f;
                scaleY = 2.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            fieldF1E = 900;
            return;
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(0xB);
            SpawnBattleEffect(0x332, x, y, facing, 0);
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (animationStage == 16 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        ClearMotionFields();
        if (fieldF1E <= 0) {
            ResetPrimaryCounters(0x2C9);
            return;
        }
        if (inputA == 1) {
            ResetPrimaryCounters(0x2C4);
            return;
        }
        if (inputB == 1) {
            ResetPrimaryCounters(0x2C5);
            return;
        }
        if (inputC == 1) {
            ResetPrimaryCounters(0x2C6);
            return;
        }
        if (inputY < 0) {
            ResetPrimaryCounters(0x2C3);
            if (facing * inputX > 0)
                sequenceTimer = 1;
            else
                sequenceTimer = 0;
            return;
        }
        if (inputX > 1) {
            facing = 1;
            ResetPrimaryCounters(0x2C2);
            return;
        }
        if (inputX < -1) {
            facing = -1;
            ResetPrimaryCounters(0x2C2);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        return;
    }

    case 0x2C2: {
        if (fieldF1E <= 0) {
            ResetPrimaryCounters(0x2C9);
            return;
        }
        velocityX = 3.25f;
        if (inputA == 1) {
            ResetPrimaryCounters(0x2C4);
            return;
        }
        if (inputB == 1) {
            ResetPrimaryCounters(0x2C5);
            return;
        }
        if (inputC == 1) {
            ResetPrimaryCounters(0x2C6);
            return;
        }
        if (inputY < 0) {
            ResetPrimaryCounters(0x2C3);
            if (facing * inputX > 0)
                sequenceTimer = 1;
            else
                sequenceTimer = 0;
            return;
        }
        if (facing * inputX <= 0) {
            ResetPrimaryCounters(0x2C1);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetCameraShake(3.0f);
            PlaySound(0x11);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SetCameraShake(3.0f);
            PlaySound(0x11);
        }
        return;
    }

    case 0x2C3: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            ClearMotionFields();
        }
        if (y > g_ThresholdAt0065782C) {
            if (inputA == 1) {
                ResetPrimaryCounters(0x2C7);
                return;
            }
            if (inputB == 1) {
                ResetPrimaryCounters(0x2C8);
                return;
            }
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(15);
                y = 0.0f;
                ClearMotionFields();
                PlaySound(17);
                SetCameraShake(20.0f);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2C9);
            field07C = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityY = 10.0f;
            field05C = 0.3f;
            if (sequenceTimer == 1)
                velocityX = 7.0f;
            else
                velocityX = 0.0f;
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(13);
        }
        return;
    }

    case 0x2C4: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2C9);
            field07C = 0;
        }
        if (animationStage == 11 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(12);
        }
        return;
    }

    case 0x2C5: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2C9);
            field07C = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(13);
        }
        return;
    }

    case 0x2C6: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2C9);
            field07C = 0;
        }
        if (animationStage == 7 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(14);
        }
        return;
    }

    case 0x2C7: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 6) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(6);
                y = 0.0f;
                ClearMotionFields();
                PlaySound(17);
                SetCameraShake(10.0f);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2C9);
            field07C = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(12);
        }
        return;
    }

    case 0x2C8: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            velocityY = 5.0f;
            field05C = 0.45f;
        }
        if (animationStage < 3) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(3);
                y = 0.0f;
                ClearMotionFields();
                PlaySound(15);
                SetCameraShake(20.0f);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2C1);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2C9);
            field07C = 0;
        }
        return;
    }

    case 0x2C9: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            field080 = 1;
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x10);
            fieldF1E = 0;
        }
        if (animationStage == 0) {
            if (scaleX > g_SubtractAt00657478) {
                scaleX -= g_SuikaOffsetAt006593F4;
                scaleY -= g_SuikaOffsetAt006593F4;
            } else {
                scaleX = 0.5f;
                scaleY = 0.5f;
                ResetSecondaryCounter(1);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x2D0: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            fieldEFE = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field080 = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (fieldF04 == 0 && opponent->action == 0x59 && animationStage > 32) {
            SetCameraShake(25.0f);
            ++fieldF04;
            PlaySound(24);
            ApplyOpponentGaugeChange(3000, 50, 1);
        }
        if (animationStage > 8 && animationStage < 17) {
            if (opponent->y == g_ThresholdAt0065782C)
                field080 = 1;
            else
                field080 = 0;
            if (field07C == 1) {
                ClearMotionFields();
                ResetSecondaryCounter(17);
                opponent->ResetPrimaryCounters(0x65);
                opponent->velocityX = 0.0f;
                opponent->velocityY = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                return;
            }
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x2BD);
                return;
            }
        }
        if (animationStage > 16 && animationStage < 35) {
            if (animationStage < 21) {
                AdjustCameraOffset(0);
                velocityY -= g_SubtractAt00657478;
                if (velocityY < g_ThresholdAt0065782C)
                    velocityY = 0.0f;
                velocityX = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
            }
            if (animationStage > 20 && animationStage < 31) {
                AdjustCameraOffset(0);
                --fieldEFE;
                SetCameraShake(2.0f);
                if (scriptCounterF00 < 60) {
                    if (fieldEFE <= 0) {
                        SpawnBattleEffect(0x334, x - static_cast<float>(facing * 960),
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        fieldEFE = 8;
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 2) {
                        SpawnBattleEffect(0x334, static_cast<float>(facing * 960) + x,
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 4) {
                        SpawnBattleEffect(0x334, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            (y) + g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 6) {
                        SpawnBattleEffect(0x334, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            y - g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                }
                if (animationStage < 23) {
                    opponent->x = static_cast<float>(facing * 45) + x;
                    opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                }
            }
        }
        if (animationStage > 34) {
            velocityY -= g_JumpGroundCorrectionAt00658058;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (scriptCounterF02 == 0 && opponent->action == 0x61) {
            ++scriptCounterF02;
            SetCameraShake(15.0f);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(42);
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 15.0f;
            velocityY = 10.0f;
            field05C = 0.6f;
        }
        if (animationStage == 17 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        if (animationStage == 19 && animationFrame == 0) {
            velocityY = 12.5f;
        }
        if (animationStage == 21 && animationFrame == 0) {
            if (sequenceTimer < 2) {
                ++sequenceTimer;
                ResetSecondaryCounter(19);
                return;
            }
            sequenceTimer = 0;
        }
        if (animationStage == 23 && animationFrame == 0) {
            if (sequenceTimer < 0) {
                ++sequenceTimer;
                ResetSecondaryCounter(21);
                return;
            }
            PlaySound(21);
            sequenceTimer = 0;
            opponent->ResetPrimaryCounters(0x6D);
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591EC;
            opponent->facing = facing;
        }
        if (animationStage == 24 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 45.0f;
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658398;
        }
        if (animationStage == 25 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 5.0f;
            opponent->x = static_cast<float>(facing * 50) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 26 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 25.0f;
            opponent->x = static_cast<float>(facing * 25) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658368;
        }
        if (animationStage == 27 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 85.0f;
            opponent->x = x - static_cast<float>(facing * 20);
            opponent->y = (y) + g_SuikaOffsetAt0065788C;
        }
        if (animationStage == 28 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 160.0f;
            opponent->x = x - static_cast<float>(facing * 60);
            opponent->y = (y) + g_SuikaOffsetAt006581DC;
        }
        if (animationStage == 29 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -165.0f;
            opponent->x = x - static_cast<float>(facing * 45);
            opponent->y = (y) + g_SuikaOffsetAt00659B70;
        }
        if (animationStage == 30 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -110.0f;
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591F8;
        }
        if (animationStage == 31 && animationFrame == 0) {
            if (sequenceTimer < 33) {
                ++sequenceTimer;
                ResetSecondaryCounter(24);
                opponent->ResetTransform(0.0f, 0.0f, 0.0f);
                opponent->rotationZ = -45.0f;
                opponent->x = static_cast<float>(facing * 44) + x;
                opponent->y = (y) + g_SuikaOffsetAt00658398;
                return;
            }
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt006590AC;
        }
        if (animationStage == 32 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->ResetPrimaryCounters(0x6F);
            opponent->facing = -facing;
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 33 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
            opponent->ResetPrimaryCounters(0x58);
            opponent->field094 = 18.0f;
            opponent->field098 = -36.0f;
            opponent->facing = -facing;
            PlaySound(22);
        }
        return;
    }

    case 0x2D1: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x2D2: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
            field080 = 5;
        }
        if (animationStage == 11 && field07C == 1 && field3CF == 1) {
            ResetPrimaryCounters(0x2D3);
            opponent->ResetPrimaryCounters(0x66);
            if (x > g_SuikaOffsetAt00659E20 && facing == 1)
                x = 750.0f;
            if (x < g_SuikaOffsetAt00659E1C && facing == -1)
                x = 550.0f;
            opponent->x = static_cast<float>(facing * 510) + x;
            opponent->velocityX = 0.0f;
            opponent->y = 0.0f;
            opponent->ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(6);
        }
        if (animationStage == 7 && animationFrame == 0 && sequenceTimer < 5) {
            ++sequenceTimer;
            ResetSecondaryCounter(5);
            return;
        }
        if (animationStage == 10 && animationFrame == 0) {
            PlaySound(7);
        }
        if (animationStage == 11 && animationFrame == 0) {
            UpdateGaugeTimer(500);
        }
        return;
    }

    case 0x2D3: {
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 470) + x;
            SpawnBattleEffect(0x335, x, y, facing, 1);
            SpawnBattleEffect(0x33F, opponent->x,
                (opponent->y) + g_ContactProjectionAt00657888, facing, 1);
            PlaySound(8);
        }
        if (animationStage == 3 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 450) + x;
        }
        if (animationStage == 4 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 400) + x;
        }
        if (animationStage == 5 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 330) + x;
        }
        if (animationStage == 6 && animationFrame == 0) {
            opponent->ResetPrimaryCounters(0x35);
            opponent->facing = facing;
            fieldF1C = 450;
        }
        return;
    }

    case 0x2D4: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
            field080 = 1;
        }
        if (animationStage > 6 && animationStage < 16) {
            if (scaleX < g_SuikaOffsetAt00657CF8) {
                scaleX = (scaleX) + g_RepeatScaleAt00658348;
                scaleY = (scaleY) + g_RepeatScaleAt00658348;
            } else {
                scaleX = 3.0f;
                scaleY = 3.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            fieldF1E = 900;
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(0xB);
            SpawnBattleEffect(0x332, x, y, facing, 0);
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (animationStage == 16 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x2D5: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        ClearMotionFields();
        if (fieldF1E <= 0) {
            ResetPrimaryCounters(0x2DD);
            return;
        }
        if (inputA == 1) {
            ResetPrimaryCounters(0x2D8);
            return;
        }
        if (inputB == 1) {
            ResetPrimaryCounters(0x2D9);
            return;
        }
        if (inputC == 1) {
            ResetPrimaryCounters(0x2DA);
            return;
        }
        if (inputY < 0) {
            ResetPrimaryCounters(0x2D7);
            if (facing * inputX > 0)
                sequenceTimer = 1;
            else
                sequenceTimer = 0;
            return;
        }
        if (inputX > 1) {
            facing = 1;
            ResetPrimaryCounters(0x2D6);
            return;
        }
        if (inputX < -1) {
            facing = -1;
            ResetPrimaryCounters(0x2D6);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        return;
    }

    case 0x2D6: {
        if (fieldF1E <= 0) {
            ResetPrimaryCounters(0x2DD);
            return;
        }
        velocityX = 2.0f;
        if (inputA == 1) {
            ResetPrimaryCounters(0x2D8);
            return;
        }
        if (inputB == 1) {
            ResetPrimaryCounters(0x2D9);
            return;
        }
        if (inputC == 1) {
            ResetPrimaryCounters(0x2DA);
            return;
        }
        if (inputY < 0) {
            ResetPrimaryCounters(0x2D7);
            if (facing * inputX > 0)
                sequenceTimer = 1;
            else
                sequenceTimer = 0;
            return;
        }
        if (facing * inputX <= 0) {
            ResetPrimaryCounters(0x2D5);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetCameraShake(3.0f);
            PlaySound(0x11);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SetCameraShake(3.0f);
            PlaySound(0x11);
        }
        return;
    }

    case 0x2D7: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            ClearMotionFields();
        }
        if (y > g_ThresholdAt0065782C) {
            if (inputA == 1) {
                ResetPrimaryCounters(0x2DB);
                return;
            }
            if (inputB == 1) {
                ResetPrimaryCounters(0x2DC);
                return;
            }
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(15);
                y = 0.0f;
                ClearMotionFields();
                PlaySound(17);
                SetCameraShake(20.0f);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2DD);
            field07C = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityY = 10.0f;
            field05C = 0.3f;
            if (sequenceTimer == 1)
                velocityX = 5.0f;
            else
                velocityX = 0.0f;
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(13);
        }
        return;
    }

    case 0x2D8: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2DD);
            field07C = 0;
        }
        if (animationStage == 11 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(12);
        }
        return;
    }

    case 0x2D9: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2DD);
            field07C = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(13);
        }
        return;
    }

    case 0x2DA: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2DD);
            field07C = 0;
        }
        if (animationStage == 7 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(14);
        }
        return;
    }

    case 0x2DB: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
        }
        if (animationStage < 6) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(6);
                y = 0.0f;
                ClearMotionFields();
                PlaySound(17);
                SetCameraShake(10.0f);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2DD);
            field07C = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(12);
        }
        return;
    }

    case 0x2DC: {
        if (animationStage == 0 && animationFrame == 0) {
            field080 = 1;
            field07C = 0;
            velocityY = 5.0f;
            field05C = 0.45f;
        }
        if (animationStage < 3) {
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(3);
                y = 0.0f;
                ClearMotionFields();
                PlaySound(15);
                SetCameraShake(20.0f);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2D5);
            if (fieldF1E <= 0)
                ResetPrimaryCounters(0x2DD);
            field07C = 0;
        }
        return;
    }

    case 0x2DD: {
        ClearMotionFields();
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            field080 = 1;
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x10);
            fieldF1E = 0;
        }
        if (animationStage == 0) {
            if (scaleX > g_SuikaOffsetAt00659E18) {
                scaleX -= g_SuikaOffsetAt006593F4;
                scaleY -= g_SuikaOffsetAt006593F4;
            } else {
                scaleX = 0.333f;
                scaleY = 0.333f;
                ResetSecondaryCounter(1);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x2E4: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (animationStage > 4) {
            AdjustCameraOffset(1);
            ++sequenceTimer;
            if (sequenceTimer == 60)
                PlaySound(0x19);
            if (sequenceTimer > 180) {
                ResetPrimaryCounters(0x2E5);
                x = opponent->x;
                y = 640.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 24.0f;
        }
        return;
    }

    case 0x2E5: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            field080 = 1;
            velocityY = static_cast<float>(-24 - g_StateRepeatLevelAt006714D0 * 2);
        }
        if (animationStage == 0 && y + velocityY <= g_ThresholdAt0065782C) {
            ClearMotionFields();
            y = 0.0f;
            ResetSecondaryCounter(1);
            SetCameraShake(10.0f);
            PlaySound(0x1A);
            return;
        }
        if (animationStage == 6 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            field080 = 1;
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x10);
        }
        if (animationStage == 6) {
            if (scaleX > g_SuikaOffsetAt00659E18) {
                scaleX -= g_SuikaOffsetAt006593F4;
                scaleY -= g_SuikaOffsetAt006593F4;
            } else {
                scaleX = 0.333f;
                scaleY = 0.333f;
                ResetSecondaryCounter(7);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            ResetPrimaryCounters(0);
        }
        return;
    }

    case 0x2EF: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame > 9) {
            if (color[0] > 10)
                color[0] -= 10;
            else
                color[0] = 0;
            if (RecordedRange(0, 100) < 50) {
                SpawnBattleEffect(0x388, ((x) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)),
                    ((y) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2F0);
            PlaySound(0x1D);
            if (g_StateRepeatLevelAt006714D0 > 0) {
                for (int shot = 0; shot < 3; ++shot) {
                    field314 = static_cast<float>(shot * 60 + 30);
                    SpawnBattleEffect(0x389, x, y, facing, 1);
                }
            } else {
                for (int shot = 0; shot < 2; ++shot) {
                    field314 = static_cast<float>(shot * 60 + 60);
                    SpawnBattleEffect(0x389, x, y, facing, 1);
                }
            }
            for (int shot = 0; shot < 18; ++shot) {
                field314 = static_cast<float>(shot * 20);
                field318 = 3.0f;
                SpawnBattleEffect(0x38B, x, y, facing, 1);
                if (g_StateRepeatLevelAt006714D0 > 1) {
                    field314 = static_cast<float>(shot * 20);
                    field318 = 15.0f;
                    SpawnBattleEffect(0x38B, x, y, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 > 2) {
                    field314 = static_cast<float>(shot * 20);
                    field318 = 27.0f;
                    SpawnBattleEffect(0x38B, x, y, facing, 1);
                }
            }
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x387, x, y, facing, 1);
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x1B);
        }
        return;
    }

    case 0x2F0: {
        if (opponent->health > 0 && opponent->animationStage == 2 && opponent->field39D > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
            scriptCounterF00 = static_cast<short>(RecordedRange(0, 5) + 5);
        }
        if (animationStage == 1 && animationFrame == 0) {
            fieldEFE = static_cast<short>(RecordedRange(0, 60) + 100);
            if (y < g_SuikaOffsetAt00659238) {
                if (x < g_SuikaOffsetAt00657D10) {
                    if (facing == 1)
                        scriptCounterF00 = -15;
                    else
                        scriptCounterF00 = -165;
                } else if (facing == 1) {
                    scriptCounterF00 = -165;
                } else {
                    scriptCounterF00 = -15;
                }
            }
            if (y > g_SuikaOffsetAt006591E4) {
                if (x > g_SuikaOffsetAt00659B68) {
                    if (facing == 1)
                        scriptCounterF00 = 165;
                    else
                        scriptCounterF00 = 15;
                } else if (facing == 1) {
                    scriptCounterF00 = 15;
                } else {
                    scriptCounterF00 = 165;
                }
            }
            if (y == g_ThresholdAt0065782C)
                scriptCounterF00 = static_cast<short>(-RecordedRange(0, 50) - 65);
        }
        if (animationStage == 1) {
            if (fieldEFE > 0)
                fieldEFE -= 2;
            SetPolarVelocity(static_cast<float>(scriptCounterF00), static_cast<float>(fieldEFE) * g_ProjectileFallAt006590B4);
        }
        if (animationStage == 3 || animationStage == 4) {
            if (color[0] < 245) {
                color[0] += 10;
            } else {
                color[0] = 255;
                ResetSecondaryCounter(animationStage + 2);
                return;
            }
        }
        if (animationStage == 5 || animationStage == 6) {
            velocityY -= g_SuikaOffsetAt006583F8;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ResetSecondaryCounter(7);
                ClearMotionFields();
                y = 0.0f;
                return;
            }
        }
        if (animationStage < 5 && RecordedRange(0, 100) < 50) {
            SpawnBattleEffect(0x388,
                ((x) + g_SuikaOffsetAt0065788C) - static_cast<float>(RecordedRange(0, 100)),
                ((y) + g_SuikaOffsetAt0065788C) - static_cast<float>(RecordedRange(0, 100)), facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(180 - g_StateRepeatLevelAt006714D0 * 30);
        }
        if (animationStage == 2 && animationFrame == 0) {
            if (sequenceTimer < g_StateRepeatLevelAt006714D0 + 1) {
                ++sequenceTimer;
                ResetSecondaryCounter(1);
                return;
            }
            if (x > opponent->x)
                facing = -1;
            else
                facing = 1;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            ResetSecondaryCounter(3);
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x2F9: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 300 - g_StateRepeatLevelAt006714D0 * 40);
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(5);
            SpawnBattleEffect(0x393, static_cast<float>(facing * 107) + x, (y) + g_SuikaOffsetAt00659138, facing, 1);
        }
        return;
    }

    case 0x303: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            fieldEFE = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field080 = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (fieldF04 == 0 && opponent->action == 0x61 && animationStage > 32) {
            SetCameraShake(15.0f);
            ++fieldF04;
            PlaySound(23);
            ApplyOpponentGaugeChange(1800, 100, 1);
        }
        if (animationStage < 5 && animationFrame < 20) {
            ++fieldF04;
            if (fieldF04 > 4) {
                SpawnAuxEffect(0x40, x - static_cast<float>(facing * 3),
                    (y) + g_SuikaOffsetAt0065929C, 1, 1);
                fieldF04 = 0;
            }
        }
        if (animationStage > 8 && animationStage < 17) {
            if (opponent->y == g_ThresholdAt0065782C)
                field080 = 1;
            else
                field080 = 0;
            if (field07C == 1) {
                ClearMotionFields();
                ResetSecondaryCounter(17);
                opponent->ResetPrimaryCounters(0x65);
                opponent->velocityX = 0.0f;
                opponent->velocityY = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                return;
            }
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x304);
                return;
            }
        }
        if (animationStage > 16 && animationStage < 35) {
            if (animationStage < 21) {
                AdjustCameraOffset(0);
                velocityY -= g_SubtractAt00657478;
                if (velocityY < g_ThresholdAt0065782C)
                    velocityY = 0.0f;
                velocityX = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
            }
            if (animationStage > 20 && animationStage < 31) {
                AdjustCameraOffset(0);
                --fieldEFE;
                SetCameraShake(2.0f);
                if (scriptCounterF00 < 60) {
                    if (fieldEFE <= 0) {
                        SpawnBattleEffect(0x331, x - static_cast<float>(facing * 960),
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        fieldEFE = 8;
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 2) {
                        SpawnBattleEffect(0x331, static_cast<float>(facing * 960) + x,
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 4) {
                        SpawnBattleEffect(0x331, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            (y) + g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 6) {
                        SpawnBattleEffect(0x331, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            y - g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                }
                if (animationStage < 23) {
                    opponent->x = static_cast<float>(facing * 45) + x;
                    opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                }
            }
        }
        if (animationStage > 34) {
            velocityY -= g_JumpGroundCorrectionAt00658058;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                aiCardTimer = static_cast<short>(RecordedRange(0, 120) + 120 - g_StateRepeatLevelAt006714D0 * 20);
                return;
            }
        }
        if (scriptCounterF02 == 0 && opponent->action == 0x61) {
            ++scriptCounterF02;
            SetCameraShake(15.0f);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(42);
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 10.0f;
            velocityY = 10.0f;
            field05C = 0.6f;
            fieldF04 = 0;
        }
        if (animationStage == 17 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        if (animationStage == 19 && animationFrame == 0) {
            velocityY = 12.5f;
        }
        if (animationStage == 21 && animationFrame == 0) {
            if (sequenceTimer < 2) {
                ++sequenceTimer;
                ResetSecondaryCounter(19);
                return;
            }
            sequenceTimer = 0;
        }
        if (animationStage == 23 && animationFrame == 0) {
            if (sequenceTimer < 0) {
                ++sequenceTimer;
                ResetSecondaryCounter(21);
                return;
            }
            PlaySound(19);
            sequenceTimer = 0;
            opponent->ResetPrimaryCounters(0x6D);
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591EC;
            opponent->facing = facing;
        }
        if (animationStage == 24 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 45.0f;
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658398;
        }
        if (animationStage == 25 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 5.0f;
            opponent->x = static_cast<float>(facing * 50) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 26 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 25.0f;
            opponent->x = static_cast<float>(facing * 25) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658368;
        }
        if (animationStage == 27 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 85.0f;
            opponent->x = x - static_cast<float>(facing * 20);
            opponent->y = (y) + g_SuikaOffsetAt0065788C;
        }
        if (animationStage == 28 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 160.0f;
            opponent->x = x - static_cast<float>(facing * 60);
            opponent->y = (y) + g_SuikaOffsetAt006581DC;
        }
        if (animationStage == 29 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -165.0f;
            opponent->x = x - static_cast<float>(facing * 45);
            opponent->y = (y) + g_SuikaOffsetAt00659B70;
        }
        if (animationStage == 30 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -110.0f;
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591F8;
        }
        if (animationStage == 31 && animationFrame == 0) {
            if (sequenceTimer < 11) {
                ++sequenceTimer;
                ResetSecondaryCounter(24);
                opponent->ResetTransform(0.0f, 0.0f, 0.0f);
                opponent->rotationZ = -45.0f;
                opponent->x = static_cast<float>(facing * 44) + x;
                opponent->y = (y) + g_SuikaOffsetAt00658398;
                return;
            }
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt006590AC;
        }
        if (animationStage == 32 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->ResetPrimaryCounters(0x6F);
            opponent->facing = -facing;
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 33 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
            opponent->ResetPrimaryCounters(0x49);
            opponent->field094 = 36.0f;
            opponent->field098 = -18.0f;
            opponent->facing = -facing;
            PlaySound(20);
        }
        return;
    }

    case 0x304: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(60, 120) - g_StateRepeatLevelAt006714D0 * 20);
        }
        return;
    }

    case 0x305: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            fieldEFE = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field080 = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (fieldF04 == 0 && opponent->action == 0x59) {
            SetCameraShake(25.0f);
            ++fieldF04;
            PlaySound(24);
            ApplyOpponentGaugeChange(3000, 50, 1);
        }
        if (animationStage > 8 && animationStage < 17) {
            if (opponent->y == g_ThresholdAt0065782C)
                field080 = 1;
            else
                field080 = 0;
            if (field07C == 1) {
                ClearMotionFields();
                ResetSecondaryCounter(17);
                opponent->ResetPrimaryCounters(0x65);
                opponent->velocityX = 0.0f;
                opponent->velocityY = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                return;
            }
            velocityY -= field05C;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x304);
                return;
            }
        }
        if (animationStage > 16 && animationStage < 35) {
            if (animationStage < 21) {
                AdjustCameraOffset(0);
                velocityY -= g_SubtractAt00657478;
                if (velocityY < g_ThresholdAt0065782C)
                    velocityY = 0.0f;
                velocityX = 0.0f;
                opponent->x = static_cast<float>(facing * 45) + x;
                opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
            }
            if (animationStage > 20 && animationStage < 31) {
                AdjustCameraOffset(0);
                --fieldEFE;
                SetCameraShake(2.0f);
                if (scriptCounterF00 < 60) {
                    if (fieldEFE <= 0) {
                        SpawnBattleEffect(0x334, x - static_cast<float>(facing * 960),
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        fieldEFE = 8;
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 2) {
                        SpawnBattleEffect(0x334, static_cast<float>(facing * 960) + x,
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 4) {
                        SpawnBattleEffect(0x334, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            (y) + g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 6) {
                        SpawnBattleEffect(0x334, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            y - g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                }
                if (animationStage < 23) {
                    opponent->x = static_cast<float>(facing * 45) + x;
                    opponent->y = (y) + g_SuikaOffsetAt006590A8 + velocityY;
                }
            }
        }
        if (animationStage > 34) {
            velocityY -= g_JumpGroundCorrectionAt00658058;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (scriptCounterF02 == 0 && opponent->action == 0x61) {
            ++scriptCounterF02;
            SetCameraShake(15.0f);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(42);
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 52) + x, (y) + g_SuikaOffsetAt00657834, facing, 1);
            field36C -= g_ContactProjectionAt00657888;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 10.0f;
            velocityY = 10.0f;
            field05C = 0.6f;
        }
        if (animationStage == 17 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        if (animationStage == 19 && animationFrame == 0) {
            velocityY = 12.5f;
        }
        if (animationStage == 21 && animationFrame == 0) {
            if (sequenceTimer < 2) {
                ++sequenceTimer;
                ResetSecondaryCounter(19);
                return;
            }
            sequenceTimer = 0;
        }
        if (animationStage == 23 && animationFrame == 0) {
            if (sequenceTimer < 0) {
                ++sequenceTimer;
                ResetSecondaryCounter(21);
                return;
            }
            PlaySound(21);
            sequenceTimer = 0;
            opponent->ResetPrimaryCounters(0x6D);
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591EC;
            opponent->facing = facing;
        }
        if (animationStage == 24 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 45.0f;
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658398;
        }
        if (animationStage == 25 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 5.0f;
            opponent->x = static_cast<float>(facing * 50) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 26 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 25.0f;
            opponent->x = static_cast<float>(facing * 25) + x;
            opponent->y = (y) + g_SuikaOffsetAt00658368;
        }
        if (animationStage == 27 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 85.0f;
            opponent->x = x - static_cast<float>(facing * 20);
            opponent->y = (y) + g_SuikaOffsetAt0065788C;
        }
        if (animationStage == 28 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = 160.0f;
            opponent->x = x - static_cast<float>(facing * 60);
            opponent->y = (y) + g_SuikaOffsetAt006581DC;
        }
        if (animationStage == 29 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -165.0f;
            opponent->x = x - static_cast<float>(facing * 45);
            opponent->y = (y) + g_SuikaOffsetAt00659B70;
        }
        if (animationStage == 30 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->rotationZ = -110.0f;
            opponent->x = x;
            opponent->y = (y) + g_SuikaOffsetAt006591F8;
        }
        if (animationStage == 31 && animationFrame == 0) {
            if (sequenceTimer < 33) {
                ++sequenceTimer;
                ResetSecondaryCounter(24);
                opponent->ResetTransform(0.0f, 0.0f, 0.0f);
                opponent->rotationZ = -45.0f;
                opponent->x = static_cast<float>(facing * 44) + x;
                opponent->y = (y) + g_SuikaOffsetAt00658398;
                return;
            }
            opponent->x = static_cast<float>(facing * 44) + x;
            opponent->y = (y) + g_SuikaOffsetAt006590AC;
        }
        if (animationStage == 32 && animationFrame == 0) {
            opponent->ResetTransform(0.0f, 0.0f, 0.0f);
            opponent->ResetPrimaryCounters(0x6F);
            opponent->facing = -facing;
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
        }
        if (animationStage == 33 && animationFrame == 0) {
            opponent->x = static_cast<float>(facing * 80) + x;
            opponent->y = (y) + g_SuikaOffsetAt0065927C;
            opponent->ResetPrimaryCounters(0x58);
            opponent->field094 = 36.0f;
            opponent->field098 = -18.0f;
            opponent->facing = -facing;
            PlaySound(22);
        }
        return;
    }

    case 0x306: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            fieldEFE = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            field080 = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (animationStage > 6 && animationStage < 14 && scriptCounterF02 < 15) {
            ++fieldF04;
            if (fieldF04 > 4) {
                SpawnAuxEffect(0x40, x - static_cast<float>(facing * 12), (y) + g_SuikaOffsetAt00659E14, 1, 1);
                fieldF04 = 0;
                ++scriptCounterF02;
            }
        }
        if (animationStage > 3 && animationStage < 14) {
            velocityY -= g_SuikaOffsetAt00659094;
            if (velocityY < g_AnimationDeltaAt0065747C)
                velocityY = 1.0f;
            velocityX = 0.0f;
            if (animationStage > 6 && animationStage < 14) {
                --fieldEFE;
                SetCameraShake(2.0f);
                if (scriptCounterF00 < 45) {
                    if (fieldEFE <= 0) {
                        SpawnBattleEffect(0x38F, x - static_cast<float>(facing * 960),
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        fieldEFE = 8;
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 2) {
                        SpawnBattleEffect(0x38F, static_cast<float>(facing * 960) + x,
                            ((y) + g_SuikaOffsetAt0065920C) - static_cast<float>(RecordedRange(0, 1920)), facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 4) {
                        SpawnBattleEffect(0x38F, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            (y) + g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                    if (fieldEFE == 6) {
                        SpawnBattleEffect(0x38F, static_cast<float>((960 - RecordedRange(0, 1920)) * facing) + x,
                            y - g_SuikaOffsetAt0065920C, facing, 1);
                        ++scriptCounterF00;
                    }
                }
            }
        }
        if (animationStage > 17) {
            velocityY -= g_SuikaOffsetAt00659094;
            if (y + velocityY <= g_ThresholdAt0065782C) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 100 - g_StateRepeatLevelAt006714D0 * 20);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(25);
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 12.5f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            sequenceTimer = 0;
            fieldF22 = static_cast<short>(x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt006591EC);
            PlaySound(0x13);
        }
        if (animationStage == 7 && animationFrame == 0) {
            fieldF22 = static_cast<short>(static_cast<float>(facing * 44) + x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt00658398);
        }
        if (animationStage == 8 && animationFrame == 0) {
            fieldF22 = static_cast<short>(static_cast<float>(facing * 50) + x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt0065927C);
        }
        if (animationStage == 9 && animationFrame == 0) {
            fieldF22 = static_cast<short>(static_cast<float>(facing * 25) + x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt00658368);
        }
        if (animationStage == 10 && animationFrame == 0) {
            fieldF22 = static_cast<short>(x - static_cast<float>(facing * 20));
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt0065788C);
        }
        if (animationStage == 11 && animationFrame == 0) {
            fieldF22 = static_cast<short>(x - static_cast<float>(facing * 60));
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt006581DC);
        }
        if (animationStage == 12 && animationFrame == 0) {
            fieldF22 = static_cast<short>(x - static_cast<float>(facing * 45));
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt00659B70);
        }
        if (animationStage == 13 && animationFrame == 0) {
            fieldF22 = static_cast<short>(x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt006591F8);
        }
        if (animationStage == 14 && animationFrame == 0) {
            if (sequenceTimer < 11) {
                ++sequenceTimer;
                ResetSecondaryCounter(7);
                fieldF22 = static_cast<short>(static_cast<float>(facing * 44) + x);
                fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt00658398);
                return;
            }
            fieldF22 = static_cast<short>(static_cast<float>(facing * 44) + x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt006590AC);
        }
        if (animationStage == 15 && animationFrame == 0) {
            fieldF22 = static_cast<short>(static_cast<float>(facing * 80) + x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt0065927C);
        }
        if (animationStage == 16 && animationFrame == 0) {
            fieldF22 = static_cast<short>(static_cast<float>(facing * 80) + x);
            fieldF24 = static_cast<short>((y) + g_SuikaOffsetAt0065927C);
            PlaySound(0x14);
            SpawnBattleEffect(0x390, static_cast<float>(facing * 80) + x, (y) + g_SuikaOffsetAt0065927C, facing, 1);
        }
        return;
    }

    case 0x30C: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field080 = 1;
            fieldEFE = 0;
            field07C = 0;
        }
        if (animationStage == 2 && animationFrame < 30) {
            ++fieldEFE;
            if (fieldEFE > 4) {
                SpawnAuxEffect(0x3E, static_cast<float>(facing * 14) + x, (y) + g_SuikaOffsetAt00659B70, 1, 1);
                fieldEFE = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 300 - g_StateRepeatLevelAt006714D0 * 40);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x340, static_cast<float>(facing * 100) + x, 0.0f, facing, 0);
            SpawnBattleEffect(0x340, opponent->x, 0.0f, facing, 0);
            SpawnAuxEffect(0x7F, x, 0.0f, facing, 0);
            PlaySound(5);
            SetCameraShake(15.0f);
            if (g_StateRepeatLevelAt006714D0 == 3) {
                SpawnBattleEffect(0x39B, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39B, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39B, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39B, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 2) {
                SpawnBattleEffect(0x39B, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39B, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 1) {
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39F, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39F, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 0) {
                SpawnBattleEffect(0x39F, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39F, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39F, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39F, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
                SpawnBattleEffect(0x39D, ((opponent->x) + g_SuikaOffsetAt006591F8)
                    - static_cast<float>(RecordedRange(0, 300)), y, facing, 1);
            }
        }
        return;
    }

    case 0x316: {
        x = 640.0f;
        opponent->field490 = 0.0f;
        facing = -1;
        if (opponent->health > 0 && opponent->animationStage == 2 && opponent->field39D > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            sequenceTimer = 0;
            fieldEFE = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (animationStage < 2) {
            if (RecordedRange(0, 100) < 50) {
                SpawnBattleEffect(0x388, ((x) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)),
                    ((y) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
            }
            if (color[0] < 255) {
                color[0] += 5;
            } else {
                color[0] = 255;
                ResetSecondaryCounter(animationStage + 2);
                sequenceTimer = 0;
                return;
            }
        }
        if (animationStage > 1) {
            ++fieldEFE;
            ++scriptCounterF00;
            if (fieldEFE > 4) {
                SpawnAuxEffect(0x3E, x, (y) + g_SuikaOffsetAt006581DC, 1, 1);
                fieldEFE = 0;
            }
            if (health < 7500) {
                ResetPrimaryCounters(0x317);
                sequenceTimer = 0;
                return;
            }
            if (scriptCounterF00 > 240 - g_StateRepeatLevelAt006714D0 * 30) {
                PlaySound(0x1D);
                for (int shot = 0; shot < 18; ++shot) {
                    field314 = static_cast<float>(shot * 20);
                    field318 = 12.0f;
                    SpawnBattleEffect(0x38B, x, (y) + g_ContactProjectionAt00657888, facing, 1);
                }
                scriptCounterF00 = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(2);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        return;
    }

    case 0x317: {
        x = 640.0f;
        opponent->field490 = 0.0f;
        ++fieldEFE;
        if (opponent->health > 0 && opponent->animationStage == 2 && opponent->field39D > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (fieldEFE > 4) {
            SpawnAuxEffect(0x40, x, (y) + g_SuikaOffsetAt006581DC, 1, 1);
            fieldEFE = 0;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
        }
        if (animationStage > 1) {
            ++scriptCounterF00;
            g_SequenceByteAt0066C23A = 0;
            if (health < 5000) {
                ResetPrimaryCounters(0x318);
                sequenceTimer = 0;
                return;
            }
            if (scriptCounterF00 > 240 - g_StateRepeatLevelAt006714D0 * 30) {
                PlaySound(0x1D);
                for (int shot = 0; shot < 18; ++shot) {
                    field314 = static_cast<float>(shot * 20);
                    field318 = 12.0f;
                    SpawnBattleEffect(0x38B, x, (y) + g_ContactProjectionAt00657888, facing, 1);
                }
                scriptCounterF00 = 0;
            }
            if (animationFrame == 0) {
                PlaySound(0x1C);
                field314 = static_cast<float>(scriptCounterF02);
                field318 = 15.0f;
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                if (g_StateRepeatLevelAt006714D0 == 1) {
                    field314 = static_cast<float>(scriptCounterF02 + 180);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 == 2) {
                    field314 = static_cast<float>(scriptCounterF02 + 120);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                    field314 = static_cast<float>(scriptCounterF02 - 120);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 == 3) {
                    field314 = static_cast<float>(scriptCounterF02 + 180);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                    field314 = static_cast<float>(scriptCounterF02 + 90);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                    field314 = static_cast<float>(scriptCounterF02 - 90);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = 0.0f;
                scriptCounterF02 += 5;
                if (scriptCounterF02 > 180)
                    scriptCounterF02 -= 360;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(2);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            if (sequenceTimer < 20) {
                ResetSecondaryCounter(0);
                ++sequenceTimer;
                return;
            }
            PlaySound(0x21);
            SpawnTrackedEffectWithFlags(0x386, 0.0f, 480.0f, 1, 3, 1, 0, 0);
        }
        return;
    }

    case 0x318: {
        x = 640.0f;
        opponent->field490 = 0.0f;
        ++fieldEFE;
        if (opponent->health > 0 && opponent->animationStage == 2 && opponent->field39D > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (fieldEFE > 4) {
            SpawnAuxEffect(0x3E, x, (y) + g_SuikaOffsetAt006581DC, 1, 1);
            fieldEFE = 0;
        }
        g_SequenceByteAt0066C23A = 0;
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
        }
        if (animationStage > 1) {
            ++scriptCounterF00;
            ++fieldF04;
            g_SequenceByteAt0066C239 = 0;
            if (health < 2500) {
                ResetPrimaryCounters(0x319);
                SpawnBattleEffect(0x398, x, (y) + g_ContactProjectionAt00657888, 1, 0);
                sequenceTimer = 0;
                return;
            }
            if (scriptCounterF00 > 240 - g_StateRepeatLevelAt006714D0 * 30) {
                PlaySound(0x1D);
                for (int shot = 0; shot < 18; ++shot) {
                    field314 = static_cast<float>(shot * 20);
                    field318 = 12.0f;
                    SpawnBattleEffect(0x38B, x, (y) + g_ContactProjectionAt00657888, facing, 1);
                }
                scriptCounterF00 = 0;
            }
            if (fieldF04 > 360 - g_StateRepeatLevelAt006714D0 * 40) {
                if (g_StateRepeatLevelAt006714D0 < 2) {
                    SpawnBattleEffect(0x3A1, x,
                        (y) + g_SuikaOffsetAt006591E4, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 == 2) {
                    SpawnBattleEffect(0x3A0, x,
                        (y) + g_SuikaOffsetAt006591E4, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 == 3) {
                    SpawnBattleEffect(0x396, x,
                        (y) + g_SuikaOffsetAt006591E4, facing, 1);
                }
                fieldF04 = 0;
            }
            if (animationFrame == 0) {
                PlaySound(0x1C);
                field314 = static_cast<float>(scriptCounterF02);
                field318 = 15.0f;
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                if (g_StateRepeatLevelAt006714D0 == 1) {
                    field314 = static_cast<float>(scriptCounterF02 + 180);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 == 2) {
                    field314 = static_cast<float>(scriptCounterF02 + 120);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                    field314 = static_cast<float>(scriptCounterF02 - 120);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                }
                if (g_StateRepeatLevelAt006714D0 == 3) {
                    field314 = static_cast<float>(scriptCounterF02 + 180);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                    field314 = static_cast<float>(scriptCounterF02 + 90);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                    field314 = static_cast<float>(scriptCounterF02 - 90);
                    SetPolarVelocity(field314, 200.0f);
                    SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                        ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                }
                velocityX = 0.0f;
                velocityY = 0.0f;
                scriptCounterF02 += 5;
                if (scriptCounterF02 > 180)
                    scriptCounterF02 -= 360;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(2);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            if (sequenceTimer < 20) {
                ResetSecondaryCounter(0);
                ++sequenceTimer;
                return;
            }
            PlaySound(0x21);
            SpawnTrackedEffectWithFlags(0x385, 0.0f, 0.0f, 1, 3, 1, 0, 0);
        }
        return;
    }

    case 0x319: {
        x = 640.0f;
        opponent->field490 = 0.0f;
        ++fieldEFE;
        ++scriptCounterF00;
        ++fieldF04;
        if (opponent->health > 0 && opponent->animationStage == 2 && opponent->field39D > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (fieldEFE > 4) {
            SpawnAuxEffect(0x3E, x, (y) + g_SuikaOffsetAt006581DC, 1, 1);
            fieldEFE = 0;
        }
        if (scriptCounterF00 > 240 - g_StateRepeatLevelAt006714D0 * 30) {
            PlaySound(0x1D);
            for (int shot = 0; shot < 18; ++shot) {
                field314 = static_cast<float>(shot * 20);
                field318 = 12.0f;
                SpawnBattleEffect(0x38B, x, (y) + g_ContactProjectionAt00657888, facing, 1);
            }
            scriptCounterF00 = 0;
        }
        if (fieldF04 > 360 - g_StateRepeatLevelAt006714D0 * 40) {
            if (g_StateRepeatLevelAt006714D0 < 2) {
                SpawnBattleEffect(0x3A1, x,
                    (y) + g_SuikaOffsetAt006591E4, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 2) {
                SpawnBattleEffect(0x3A0, x,
                    (y) + g_SuikaOffsetAt006591E4, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 3) {
                SpawnBattleEffect(0x396, x,
                    (y) + g_SuikaOffsetAt006591E4, facing, 1);
            }
            fieldF04 = 0;
        }
        if (animationFrame == 0) {
            PlaySound(0x1C);
            field314 = static_cast<float>(scriptCounterF02);
            field318 = 15.0f;
            SetPolarVelocity(field314, 200.0f);
            SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
            if (g_StateRepeatLevelAt006714D0 == 1) {
                field314 = static_cast<float>(scriptCounterF02 + 180);
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 2) {
                field314 = static_cast<float>(scriptCounterF02 + 120);
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                field314 = static_cast<float>(scriptCounterF02 - 120);
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
            }
            if (g_StateRepeatLevelAt006714D0 == 3) {
                field314 = static_cast<float>(scriptCounterF02 + 180);
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                field314 = static_cast<float>(scriptCounterF02 + 90);
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
                field314 = static_cast<float>(scriptCounterF02 - 90);
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x397, (g_SuikaOffsetAt00657874 + velocityX) * facing + x,
                    ((y) + g_SuikaOffsetAt00659290) - velocityY, facing, 1);
            }
            velocityX = 0.0f;
            velocityY = 0.0f;
            scriptCounterF02 += 5;
            if (scriptCounterF02 > 180)
                scriptCounterF02 -= 360;
        }
        g_SequenceByteAt0066C23A = 0;
        g_SequenceByteAt0066C239 = 0;
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
        }

        if (AdvanceNestedFrame() == animationStageCount)
            {
                ResetSecondaryCounter(0);
                return;
            }
        return;
    }

    case 0x31A: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 0;
            ClearMotionFields();
        }
        if (sequenceTimer > 20) {
            g_SequenceByteAt0066C23A = 0;
            opponent->field366 = 0;
            opponent->UpdateGaugeTimer(1000);
        }
        if (sequenceTimer > 40) {
            g_SequenceByteAt0066C239 = 0;
            g_StoryStatusAt00671623 = 0;
            g_SequenceCounterAt00671622 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            ResetSecondaryCounter(7);
            ++sequenceTimer;
            if (sequenceTimer == 21)
                SpawnTrackedEffectWithFlags(0x386, 0.0f, 480.0f, 1, 3, 1, 0, 0);
            if (sequenceTimer == 41)
                SpawnTrackedEffectWithFlags(0x385, 0.0f, 0.0f, 1, 3, 1, 0, 0);
        }
        return;
    }

    case 0x31B: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
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
        if (animationStage == 7 && animationFrame == 0 && sequenceTimer < 8) {
            ++sequenceTimer;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 20 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 23 && animationFrame == 0 && sequenceTimer < 8) {
            ++sequenceTimer;
            ResetSecondaryCounter(21);
            field3CF = 1;
        }
        return;
    }

    case 0x31D: {
        if (animationStage == 0 && animationFrame == 0) {
            sequenceTimer = 0;
            field07C = 1;
            ClearMotionFields();
        }
        if (animationStage == 1) {
            if (color[0] > 5)
                color[0] -= 5;
            else
                color[0] = 0;
        }
        if (animationStage > 0 && RecordedRange(0, 100) < 50) {
            SpawnBattleEffect(0x388, ((x) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)),
                    ((y) + g_ContactProjectionAt00657888) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x316);
            field3CF = 1;
            facing = 1;
            return;
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 3 && animationFrame == 0) {
            facing = 1;
            velocityX = (g_SuikaOffsetAt00657884 - x) / g_SuikaOffsetAt00658264;
            velocityY = 3.0f;
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
