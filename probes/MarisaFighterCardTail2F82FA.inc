// Original handler order 0x2F8, 0x2F9, 0x2FA.
        case 0x2F8: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
            }
            if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
                actionSnapshot = RecordedRange(0, 0x8C);
SpawnBattleEffect(0x330,
    x + g_MarisaRandomEffectXAt00657878 - static_cast<float>(RecordedRange(0, 0x3C)),
    y + g_MarisaRandomEffectYAt00657858 + static_cast<float>(actionSnapshot), facing, 1);
            }
            if (animationStage == 7 && y > g_MarisaHighBoundaryAt0065926C) {
                y = 870.0f;
                ResetPrimaryCounters(0x2F9);
                ClearMotionFields();
                return;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0)
                PlaySound(2);
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 15.0f;
                SpawnAuxEffect(0x7F, x, y, facing, 1);
            }
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
        case 0x2FA: {
            if (animationStage == 0 && animationFrame == 0) {
                facing = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                velocityX = 0.0f;
            }
            --scriptCounterF00;
            if (animationStage < 2) {
                velocityY -= g_MarisaCardFallAt00659264;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(2);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 2 && animationFrame == 0)
                ResetSecondaryCounter(0);
            return;
        }
