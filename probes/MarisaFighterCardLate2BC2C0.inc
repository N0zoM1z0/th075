// Marisa's native 0x2BC and 0x2C0 multi-stage card transitions.
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
                if (y + velocityY <= g_ThresholdAt0065782C) {
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
