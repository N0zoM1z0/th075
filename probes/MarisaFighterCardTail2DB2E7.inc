// Original handler order 0x2DB, 0x2E5, 0x2E6, 0x2E7.
        case 0x2DB: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 0;
                field080 = 1;
                ClearMotionFields();
                scriptCounterF02 = 0;
                fieldF04 = 0;
            }
            if (CheckHorizontalLimits() &&
                ((facing == 1 && x > g_MarisaOpponentBoundaryAt00657884) ||
                 (facing == -1 && x < g_MarisaOpponentBoundaryAt00657884)) &&
                animationStage < 17) {
                ResetSecondaryCounter(0x11);
                velocityX = -4.0f;
                velocityY = 17.0f;
                field05C = 0.4f;
                return;
            }
            if (animationStage > 8 && animationStage < 17) {
                --scriptCounterF02;
                if (scriptCounterF02 < 1) {
                    SpawnBattleEffect(0x385,
                        x - static_cast<float>(facing * 140),
                        y + g_MarisaResourceYAt006590AC, facing, 1);
                    scriptCounterF02 = 3 - g_MarisaDifficultyAt006714D0;
                }
            }
            if (y > g_ThresholdAt0065782C && animationStage > 16) {
                velocityY -= field05C;
                velocityX += g_SubtractAt00657478;
                if (velocityX > g_MarisaMinimumDriftAt00659278)
                    velocityX = g_MarisaMinimumDriftAt00659278;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    y = 0.0f;
                    ResetSecondaryCounter(26);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0);
                aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 180 -
                    g_MarisaDifficultyAt006714D0 * 30);
            }
            if (animationStage == 9 && animationFrame == 0) {
                velocityX = 25.0f;
                PlaySound(10);
                SpawnBattleEffect(0x33B, x, y, facing, 1);
                if (y == g_ThresholdAt0065782C)
                    SpawnAuxEffect(0x7F, x, 0.0f, facing, 1);
            }
            if (animationStage == 17 && animationFrame == 0 && scriptCounterF00 < 3) {
                ++scriptCounterF00;
                ResetSecondaryCounter(9);
            }
            if (animationStage == 26 && animationFrame == 0)
                ResetSecondaryCounter(24);
            return;
        }
        case 0x2E5: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (animationStage > 5 && animationStage < 8 && animationFrame == 0) {
                scriptCounterF02 = static_cast<short>(RecordedRange(0, 4));
                field314 = static_cast<float>(RecordedRange(0, 0x167));
                for (int i = 0; i < static_cast<int>(g_MarisaDifficultyAt006714D0) + 1; ++i) {
                    PlaySound(0x14);
                    field31C = 3.0f;
                    field318 = static_cast<float>(i * 7);
                    SpawnBattleEffect(
                        static_cast<short>(scriptCounterF02 + 0x38E),
                        x - static_cast<float>(facing * 25),
                        y + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0);
                aiCardTimer = static_cast<short>(RecordedRange(60, 120) -
                    g_MarisaDifficultyAt006714D0 * 20);
            }
            if (animationStage == 8 && animationFrame == 0 &&
                scriptCounterF00 < g_MarisaDifficultyAt006714D0 * 3 + 10) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 <= 5) {
                ++scriptCounterF00;
                ResetSecondaryCounter(8);
            }
            return;
        }
        case 0x2E6: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (animationStage > 17 && animationStage < 22 && animationFrame == 0) {
                scriptCounterF02 = static_cast<short>(RecordedRange(0, 4));
                field314 = static_cast<float>(RecordedRange(0, 0x167));
                for (int i = 0; i < static_cast<int>(g_MarisaDifficultyAt006714D0) + 1; ++i) {
                    PlaySound(0x14);
                    field318 = static_cast<float>(i * 5);
                    field31C = 3.0f;
                    SpawnBattleEffect(
                        static_cast<short>(scriptCounterF02 + 0x38E),
                        static_cast<float>(facing * 65) + x,
                        y + g_MarisaResourceYAt0065927C, facing, 1);
                }
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetSecondaryCounter(0x1C);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0);
                aiCardTimer = static_cast<short>(RecordedRange(60, 180) -
                    g_MarisaDifficultyAt006714D0 * 20);
            }
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = static_cast<float>(RecordedRange(0, 8)) +
                    g_ExtraThresholdAt00657D14;
                velocityY = static_cast<float>(RecordedRange(0, 5)) +
                    g_MarisaRandomVelocityYBaseAt00657D70;
                field05C = 0.2f;
            }
            if (animationStage == 0x16 && animationFrame == 0 &&
                scriptCounterF00 < g_MarisaDifficultyAt006714D0 * 3 + 10) {
                ++scriptCounterF00;
                ResetSecondaryCounter(0x15);
            }
            if (animationStage == 0x1C && animationFrame == 0)
                ResetSecondaryCounter(0x1A);
            return;
        }
        case 0x2E7: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetSecondaryCounter(0x0E);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(3);
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = static_cast<float>(RecordedRange(0, 8)) +
                    g_ExtraThresholdAt00657D14;
                velocityY = static_cast<float>(RecordedRange(0, 5)) +
                    g_MarisaRandomVelocityYBaseAt00657D70;
                field05C = 0.2f;
            }
            if (animationStage == 14 && animationFrame == 0) {
                if (scriptCounterF00 > 5)
                    return;
                ++scriptCounterF00;
                ResetSecondaryCounter(8);
            }
            return;
        }
