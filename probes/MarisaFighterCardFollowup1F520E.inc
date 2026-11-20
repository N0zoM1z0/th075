// Marisa's native random card follow-up and four directional 0x20A-0x20D
// branches, plus their shared 0x20E airborne continuation.
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
                actionSnapshot = RecordedRange(0, 140);
SpawnBattleEffect(0x330,
    x + g_MarisaRandomEffectXAt00657878 - static_cast<float>(RecordedRange(0, 60)),
    y + g_MarisaRandomEffectYAt00657858 + static_cast<float>(actionSnapshot), facing, 1);
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(12);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0)
                PlaySound(2);
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = 18.0f;
                velocityY = 16.0f;
                field05C = 0.8f;
                SpawnAuxEffect(0x7F, x, y, facing, 1);
            }
            if (animationStage == 12 && animationFrame == 0)
                ResetSecondaryCounter(10);
            return;
        }

        case 0x208: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                ClearMotionFields();
                field080 = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage > 6) {
                velocityX -= g_MarisaHorizontalSlowdownAt00659094;
                if (velocityX < g_ThresholdAt0065782C)
                    velocityX = 0.0f;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 2 && animationFrame == 0)
                velocityX = 12.5f;
            if (animationStage == 6 && animationFrame == 0 && scriptCounterF00 < 0) {
                ++scriptCounterF00;
                ResetSecondaryCounter(4);
            }
            if (animationStage == 9 && animationFrame == 0)
                PlaySound(3);
            return;
        }

        case 0x20A: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                ClearMotionFields();
                field080 = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage > 8 && animationStage < 15 &&
                (field07C != 0 ||
                 (CheckHorizontalLimits() &&
                  ((x > g_MarisaOpponentBoundaryAt00657884 && facing == 1) ||
                   (x < g_MarisaOpponentBoundaryAt00657884 && facing == -1))))) {
                ResetSecondaryCounter(0x0F);
                velocityX = -3.0f;
                velocityY = 14.0f;
                field05C = 0.9f;
                return;
            }
            if (animationStage > 14 && animationStage < 27 &&
                y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(0x1B);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 9 && animationFrame == 0) {
                velocityX = 14.0f;
                PlaySound(10);
            }
            if (animationStage == 15 && animationFrame == 0) {
                ResetSecondaryCounter(9);
                ++scriptCounterF00;
                if (scriptCounterF00 > 0) {
                    ResetPrimaryCounters(0x20E);
                    return;
                }
            }
            if (animationStage == 0x1B && animationFrame == 0)
                ResetSecondaryCounter(0x19);
            return;
        }

        case 0x20B: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                ClearMotionFields();
                field080 = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage > 8 && animationStage < 15 &&
                (field07C != 0 ||
                 (CheckHorizontalLimits() &&
                  ((x > g_MarisaOpponentBoundaryAt00657884 && facing == 1) ||
                   (x < g_MarisaOpponentBoundaryAt00657884 && facing == -1))))) {
                ResetSecondaryCounter(0x0F);
                velocityX = -3.0f;
                velocityY = 15.0f;
                field05C = 0.9f;
                return;
            }
            if (animationStage > 14 && animationStage < 27 &&
                y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(0x1B);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 9 && animationFrame == 0) {
                velocityX = 18.25f;
                PlaySound(10);
            }
            if (animationStage == 15 && animationFrame == 0) {
                ResetSecondaryCounter(9);
                ++scriptCounterF00;
                if (scriptCounterF00 > 1) {
                    ResetPrimaryCounters(0x20E);
                    return;
                }
            }
            if (animationStage == 0x1B && animationFrame == 0)
                ResetSecondaryCounter(0x19);
            return;
        }

        case 0x20C: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                ClearMotionFields();
                field080 = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage > 8 && animationStage < 15 &&
                (field07C != 0 ||
                 (CheckHorizontalLimits() &&
                  ((x > g_MarisaOpponentBoundaryAt00657884 && facing == 1) ||
                   (x < g_MarisaOpponentBoundaryAt00657884 && facing == -1))))) {
                ResetSecondaryCounter(0x0F);
                velocityX = -3.0f;
                velocityY = 14.0f;
                field05C = 0.9f;
                return;
            }
            if (animationStage > 14 && animationStage < 27 &&
                y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(0x1B);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 9 && animationFrame == 0) {
                velocityX = 14.0f;
                PlaySound(10);
                SpawnAuxEffect(0x80,
                    static_cast<float>(facing * 150) + x, y, facing, 1);
            }
            if (animationStage == 15 && animationFrame == 0) {
                ResetSecondaryCounter(9);
                ++scriptCounterF00;
                if (scriptCounterF00 > 0) {
                    ResetPrimaryCounters(0x20E);
                    return;
                }
            }
            if (animationStage == 0x1B && animationFrame == 0)
                ResetSecondaryCounter(0x19);
            return;
        }

        case 0x20D: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                ClearMotionFields();
                field080 = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage > 8 && animationStage < 15 &&
                (field07C != 0 ||
                 (CheckHorizontalLimits() &&
                  ((x > g_MarisaOpponentBoundaryAt00657884 && facing == 1) ||
                   (x < g_MarisaOpponentBoundaryAt00657884 && facing == -1))))) {
                ResetSecondaryCounter(0x0F);
                velocityX = -3.0f;
                velocityY = 15.0f;
                field05C = 0.9f;
                return;
            }
            if (animationStage > 14 && animationStage < 27 &&
                y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(0x1B);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 9 && animationFrame == 0) {
                velocityX = 18.25f;
                PlaySound(10);
                SpawnAuxEffect(0x80,
                    static_cast<float>(facing * 150) + x, y, facing, 1);
            }
            if (animationStage == 15 && animationFrame == 0) {
                ResetSecondaryCounter(9);
                ++scriptCounterF00;
                if (scriptCounterF00 > 1) {
                    ResetPrimaryCounters(0x20E);
                    return;
                }
            }
            if (animationStage == 0x1B && animationFrame == 0)
                ResetSecondaryCounter(0x19);
            return;
        }

        case 0x20E: {
            if (animationStage == 0 && animationFrame == 0) {
                if (y == g_ThresholdAt0065782C)
                    field07C = 1;
                ClearMotionFields();
                velocityX = 10.0f;
                velocityY = 7.0f;
                field05C = 0.5f;
            }
            if (animationStage < 10) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(10);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 10 && animationFrame == 0)
                ResetSecondaryCounter(8);
            return;
        }
