// Marisa's three remaining native random-card states. The 0x2E5/0x2E6
// variants create difficulty-scaled particle rows; 0x2F9 tracks the opponent.
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

        case 0x2F9: {
            if (animationStage == 0 && animationFrame == 0) {
                facing = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                fieldF04 = 0;
            }
            --scriptCounterF00;
            if (animationStage == 1 && animationFrame == 0) {
                if (fieldF04 == 0 && g_MarisaDifficultyAt006714D0 < 2) {
                    SpawnBattleEffect(
                        static_cast<short>(g_MarisaDifficultyAt006714D0 + 0x39F),
                        x, 0.0f, 1, 1);
                }
                if (fieldF04 == 4 && g_MarisaDifficultyAt006714D0 > 1) {
                    SpawnBattleEffect(
                        static_cast<short>(g_MarisaDifficultyAt006714D0 + 0x39F),
                        opponent->x, 0.0f, 1, 1);
                }
            }
            velocityX = 0.0f;
            if (x < opponent->x - g_MarisaPhaseDivisorBAt0065788C)
                velocityX = static_cast<float>(g_MarisaDifficultyAt006714D0) *
                    g_SubtractAt00657478 + g_AnimationDeltaAt0065747C;
            if (opponent->x + g_MarisaPhaseDivisorBAt0065788C < x)
                velocityX = g_MarisaNegativeCardDriftAt00659268 -
                    static_cast<float>(g_MarisaDifficultyAt006714D0) *
                    g_SubtractAt00657478;
            if (animationStage == 1 && y > g_MarisaHighBoundaryAt0065926C) {
                y = 870.0f;
                ResetPrimaryCounters(0x2F9);
                return;
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                if (scriptCounterF02 > 0 && g_MarisaDifficultyAt006714D0 < 2) {
                    ResetPrimaryCounters(0x2FA);
                    return;
                }
                if (scriptCounterF02 > 1 && g_MarisaDifficultyAt006714D0 > 1) {
                    ResetPrimaryCounters(0x2FA);
                    return;
                }
                ResetSecondaryCounter(1);
                ++fieldF04;
                return;
            }
            if (animationStage == 1 && animationFrame == 0) {
                SpawnBattleEffect(
                    static_cast<short>(g_MarisaDifficultyAt006714D0 + 0x39F),
                    x, 0.0f, 1, 1);
            }
            return;
        }
