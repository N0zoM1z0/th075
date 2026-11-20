// Range-local split of MarisaFighterCardLate2BF2DB.inc.
        case 0x2BF: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 0;
                field080 = 6;
                ClearMotionFields();
                scriptCounterF02 = 0;
                fieldF04 = 0;
            }
            if (field07C == 1 && scriptCounterF02 == 0) {
                ++scriptCounterF02;
                PlaySound(0x0B);
            }
            if (((CheckHorizontalLimits() && field07C != 1 &&
                  ((facing == 1 && x > g_MarisaOpponentBoundaryAt00657884) ||
                   (facing == -1 && x < g_MarisaOpponentBoundaryAt00657884))) ||
                 (field080 == 0 && field07C == 2)) && animationStage < 23) {
                ResetSecondaryCounter(0x17);
                velocityX = -2.5f;
                velocityY = 15.0f;
                field05C = 0.5f;
                return;
            }
            if (animationStage > 14 && animationStage < 23) {
                SpawnBattleEffect(0x34C,
                    x - static_cast<float>(facing * 90),
                    y + g_MarisaResourceYAt00659280, -facing, 1);
            }
            if (y > g_ThresholdAt0065782C && animationStage > 22 &&
                animationStage < 35) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    y = 0.0f;
                    ResetSecondaryCounter(0x23);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 2 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                field36C -= g_ContactProjectionAt00657888;
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73, x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
            }
            if (animationStage == 15 && animationFrame == 0) {
                field080 = 20;
                velocityX = 25.0f;
                PlaySound(10);
                UpdateGaugeTimer(500);
                SpawnBattleEffect(0x33B, x, y, facing, 1);
                SpawnBattleEffect(0x34E,
                    x - static_cast<float>(facing * 110),
                    y + g_MarisaResourceYAt00659280, facing, 1);
                if (y == g_ThresholdAt0065782C)
                    SpawnAuxEffect(0x7F, x, 0.0f, facing, 1);
            }
            if (animationStage > 14 && animationStage < 23 && animationFrame == 0) {
                if (y == g_ThresholdAt0065782C) {
                    SpawnAuxEffect(0x80,
                        x - static_cast<float>(facing * 200), y, facing, 1);
                }
                if (field07C == 0) {
                    field07C = 0;
                    velocityX = 25.0f;
                } else {
                    field07C = 0;
                    velocityX = 10.0f;
                }
            }
            if (animationStage == 23 && animationFrame == 0)
                ResetSecondaryCounter(15);
            if (animationStage == 35 && animationFrame == 0)
                ResetSecondaryCounter(0x21);
            return;
        }
