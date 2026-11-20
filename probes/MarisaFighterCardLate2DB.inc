// Range-local split of MarisaFighterCardLate2BF2DB.inc.
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
