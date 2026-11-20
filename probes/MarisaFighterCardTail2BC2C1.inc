// Original PE handler order: 0x2BC, 0x2BD, 0x2C1, 0x2BF, 0x2C0.
        case 0x2BC: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 2 && animationFrame == 10) {
                field36C -= g_ContactProjectionAt00657888;
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73,
                    x - static_cast<float>(facing * 18),
                    y + g_MarisaResourceYAt00659284, facing, 1);
            }
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x334,
                    static_cast<float>(facing * 32) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                SpawnBattleEffect(0x329,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 6 && animationFrame == 0) {
                ResetPrimaryCounters(0x2BD);
                SpawnBattleEffect(0x34F,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaResourceYAt0065908C, facing, 0);
                PlaySound(0);
            }
            return;
        }
        case 0x2BD: {
            if (animationStage == 0 && animationFrame == 0) {
                SpawnBattleEffect(0x32A,
                    static_cast<float>(static_cast<int>(facing) << 6) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            UpdateGaugeTimer(10);
            if (spirit < 1)
                ++scriptCounterF00;
            if (scriptCounterF00 > 20) {
                scriptCounterF00 = 0;
                ResetPrimaryCounters(700);
                ResetSecondaryCounter(6);
                return;
            }
            if (AdvanceNestedFrame() != field070)
                return;
            ResetSecondaryCounter(0);
            return;
        }
        case 0x2C1: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 0;
                field080 = 6;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                field36C -= g_ContactProjectionAt00657888;
                SpawnAuxEffect(0x73, x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
            }
            if (animationStage == 6 && animationFrame == 0) {
                SpawnBattleEffect(0x342, x, y, facing, 1);
                UpdateGaugeTimer(500);
                fieldF14 = 4;
                fieldF16 = 4;
                fieldF18 = 0x1A4;
                PlaySound(0x0D);
            }
            return;
        }
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
            if (AdvanceNestedFrame() == field070)
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
        case 0x2C0: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 0;
                field080 = 6;
                ClearMotionFields();
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    y = 0.0f;
                    ResetSecondaryCounter(7);
                    return;
                }
            }
            if (animationStage == 3) {
                ++scriptCounterF00;
                if (scriptCounterF00 > 60) {
                    scriptCounterF00 = 0;
                    ResetSecondaryCounter(4);
                    PlaySound(0x0C);
                    UpdateGaugeTimer(500);
                    SpawnBattleEffect(0x339,
                        x - static_cast<float>(facing * 200), 0.0f, facing, 1);
                    SpawnBattleEffect(0x33A,
                        x - static_cast<float>(facing * 200), 0.0f, facing, 1);
                    return;
                }
            }
            if (animationStage == 4 && scriptCounterF02 == 1) {
                ResetSecondaryCounter(5);
                ClearMotionFields();
                field05C = 0.5f;
                y = 400.0f;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 2 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                field36C -= g_ContactProjectionAt00657888;
                SpawnAuxEffect(0x74, x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
            }
            if (animationStage == 3 && animationFrame == 0) {
                Fighter::SpawnTrackedEffect(0x338, x, y, facing, 1, 0, 1);
                velocityX = -30.0f;
            }
            if (animationStage == 4 && animationFrame == 0)
                ResetSecondaryCounter(3);
            if (animationStage == 5 && animationFrame == 0)
                ResetSecondaryCounter(4);
            if (animationStage == 7 && animationFrame == 0)
                ResetSecondaryCounter(5);
            return;
        }
