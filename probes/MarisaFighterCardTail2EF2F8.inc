// Marisa's native 0x2EF, 0x2F0 and 0x2F8 late card states.
        case 0x2EF: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (animationStage == 2 && animationFrame < 45) {
                ++scriptCounterF02;
                if (scriptCounterF02 > 4) {
                    SpawnAuxEffect(0x3E,
                        x - static_cast<float>(facing * 23),
                        y + g_MarisaResourceYAt006581DC, facing, 1);
                    scriptCounterF02 = 0;
                }
            }
            if (animationStage > 5 && animationStage < 12)
                SetCameraShake(5.0f);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x329,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0);
                aiCardTimer = static_cast<short>(RecordedRange(0x78, 0xB4) -
                    g_MarisaDifficultyAt006714D0 * 20);
            }
            if (animationStage == 6 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73, x,
                    y + g_MarisaResourceYAt00659280, facing, 1);
            }
            if (animationStage == 12 && animationFrame == 0) {
                field314 = 0.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 80) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(200);
            }
            return;
        }

        case 0x2F0: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (animationStage == 2 && animationFrame < 45) {
                ++scriptCounterF02;
                if (scriptCounterF02 > 4) {
                    SpawnAuxEffect(0x3E,
                        x - static_cast<float>(facing * 23),
                        y + g_MarisaResourceYAt006581DC, facing, 1);
                    scriptCounterF02 = 0;
                }
            }
            if (animationStage > 5 && animationStage < 12)
                SetCameraShake(5.0f);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x329,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0);
                aiCardTimer = static_cast<short>(RecordedRange(0x78, 0xB4) -
                    g_MarisaDifficultyAt006714D0 * 20);
            }
            if (animationStage == 6 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73, x,
                    y + g_MarisaResourceYAt00659280, facing, 1);
            }
            if (animationStage == 12 && animationFrame == 0) {
                field314 = 0.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 80) + x,
                    y + g_MarisaResourceYAt00659290, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(200);
            }
            return;
        }

        case 0x2F8: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (animationStage > 6 && animationStage < 11 &&
                y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY <= g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    ResetSecondaryCounter(0x15);
                    y = 0.0f;
                    return;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x329,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (animationStage == 6 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73, x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
            }
            if (animationStage == 11 && animationFrame == 0) {
                field314 = 0.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 80) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(200);
            }
            return;
        }
