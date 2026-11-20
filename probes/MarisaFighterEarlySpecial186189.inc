// Marisa's native early special states 0x186-0x189.
// 0x186 is the original pre-switch 305-byte branch; 0x187-0x189 are
// adjacent sparse-switch handlers with independently distinct stage exits.
        case 0x186: {
            if (animationStage == 0 && animationFrame == 0) {
                field080 = 1;
                field07C = 0;
                field3AC = 0;
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

        case 0x187: {
            if (animationStage == 0 && animationFrame == 0) {
                field3AC = 0;
                field080 = 1;
                field07C = 0;
                velocityX = 12.5f;
            }
            if (animationStage > 0) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_ThresholdAt0065782C)
                    velocityX = 0.0f;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 4 && animationFrame == 0)
                PlaySharedSound(0x1D);
            return;
        }

        case 0x188: {
            if (animationStage == 0 && animationFrame == 0) {
                field080 = 1;
                field07C = 0;
                field3AC = 0;
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
            if (animationStage == 5 && animationFrame == 0)
                PlaySharedSound(0x1D);
            return;
        }

        case 0x189: {
            if (animationStage == 0 && animationFrame == 0) {
                field3AC = 0;
                field080 = 1;
                field07C = 0;
                field05C = 0.0f;
                velocityY = 0.0f;
                velocityX = 12.5f;
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
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 7 && animationFrame == 0) {
                velocityX = 13.5f;
                velocityY = 9.0f;
                field05C = 0.9f;
            }
            if (animationStage != 9 || y <= g_ThresholdAt0065782C)
                return;
            ResetSecondaryCounter(animationStage - 2);
            return;
        }
