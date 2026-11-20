// Marisa's native 0x12D-0x136 state family. These original actions share
// the signed +0x3AC horizontal return flag but keep distinct frame exits.
        case 0x12D: {
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
                PlaySharedSound(0x1C);
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
            if (animationStage == 3 && animationFrame == 0)
                PlaySharedSound(0x1B);
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
                PlaySharedSound(0x1C);
            return;
        }

        case 0x130: {
            velocityY -= field05C;
            if (y + velocityY < g_ThresholdAt0065782C) {
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
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(9);
                return;
            }
            if (animationStage != 5 || animationFrame != 0)
                return;
            SpawnBattleEffect(0x323,
                static_cast<float>(facing * 38) + x,
                y + g_MarisaProjectilePairYAt00657CF8, facing, 1);
            SpawnBattleEffect(0x324,
                static_cast<float>(facing * 38) + x,
                y + g_MarisaProjectilePairYAt00657CF8, facing, 1);
            PlaySharedSound(0x1C);
            return;
        }

        case 0x131: {
            velocityY -= field05C;
            if (y + velocityY < g_ThresholdAt0065782C) {
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
            if (animationStage == 2 && animationFrame == 0)
                PlaySharedSound(0x1C);
            return;
        }

        case 0x133: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                field080 = 1;
                field07C = 0;
            }
            if (velocityX > g_ThresholdAt0065782C)
                velocityX -= g_MarisaSpecialDriftAt006578C0;
            if (y > g_ThresholdAt0065782C &&
                animationStage > 6 && animationStage < 9) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    field05C = 0.0f;
                    y = 0.0f;
                    animationFrame = 0;
                    ResetSecondaryCounter(9);
                    PlaySound(0x13);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 7 && animationFrame == 0) {
                velocityX = 15.0f;
                velocityY = 7.0f;
                field05C = 0.9f;
                PlaySound(0x12);
            }
            if (animationStage != 9 || y <= g_ThresholdAt0065782C)
                return;
            ResetSecondaryCounter(animationStage - 2);
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
            if (animationStage == 4 && animationFrame == 0)
                PlaySharedSound(0x1C);
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
            if (animationStage == 5 && animationFrame == 0)
                PlaySharedSound(0x1D);
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
            if (animationStage > 2 && velocityX > g_ThresholdAt0065782C) {
                velocityX -= g_AnimationDeltaAt0065747C;
                if (velocityX < g_ThresholdAt0065782C)
                    velocityX = 0.0f;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0)
                velocityX = 12.0f;
            if (animationStage == 4 && animationFrame == 0)
                PlaySharedSound(0x1D);
            if (animationStage == 5 && animationFrame == 0) {
                SetCameraShake(2.0f);
                SpawnBattleEffect(0x325,
                    static_cast<float>(facing * 170) + x,
                    y - g_MarisaSpecialYCorrectionAt00658290, facing, 0);
            }
            return;
        }
