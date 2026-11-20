// Marisa's native 0x2EF, 0x2F0 and 0x2F8 late card states.
        case 0x2EF: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 2 && animationFrame < 45) {
                ++scriptCounterF02;
                if (scriptCounterF02 > 4) {
                    SpawnAuxEffect(0x3E,
                        x - static_cast<float>(facing * 23),
                        y + g_MarisaResourceYAt006581DC, 1, 1);
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
                SpawnBattleEffect(0x399,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaResourceYAt0065908C, facing, 0);
                SpawnBattleEffect(0x329,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaResourceYAt0065908C, facing, 0);
                SpawnBattleEffect(0x32A,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                SpawnBattleEffect(0x353,
                    x - static_cast<float>(facing * 82),
                    y + g_MarisaResourceYAt00659270, facing, 1);
                PlaySound(0);
            }
            if (animationStage == 12 && animationFrame == 0 &&
                scriptCounterF00 < g_MarisaDifficultyAt006714D0 * 2 + 4) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
                SpawnBattleEffect(0x32A,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            return;
        }

        case 0x2F0: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 2 && animationFrame < 45) {
                ++scriptCounterF02;
                if (scriptCounterF02 > 4) {
                    SpawnAuxEffect(0x3E,
                        x - static_cast<float>(facing * 23),
                        y + g_MarisaResourceYAt006581DC, 1, 1);
                    scriptCounterF02 = 0;
                }
            }
            if (animationStage > 5 && animationStage < 12)
                SetCameraShake(10.0f);
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
                SpawnBattleEffect(0x39A,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaResourceYAt0065908C, facing, 0);
                SpawnBattleEffect(0x329,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaResourceYAt0065908C, facing, 0);
                SpawnBattleEffect(0x32A,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                SpawnBattleEffect(0x353,
                    x - static_cast<float>(facing * 82),
                    y + g_MarisaResourceYAt00659270, facing, 1);
                PlaySound(0);
            }
            if (animationStage == 12 && animationFrame == 0 &&
                scriptCounterF00 < g_MarisaDifficultyAt006714D0 * 2 + 4) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
                SpawnBattleEffect(0x32A,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            return;
        }

        case 0x2F8: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
            }
            if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
                const float effectY = y + g_MarisaRandomEffectYAt00657858;
                const float spawnY = static_cast<float>(RecordedRange(0, 0x8C)) + effectY;
                const float effectX = x + g_MarisaRandomEffectXAt00657878;
                const float spawnX = effectX - static_cast<float>(RecordedRange(0, 0x3C));
                SpawnBattleEffect(0x330, spawnX, spawnY, facing, 1);
            }
            if (animationStage == 7 && y > g_MarisaHighBoundaryAt0065926C) {
                y = 870.0f;
                ResetPrimaryCounters(0x2F9);
                ClearMotionFields();
                return;
            }
            if (AdvanceNestedFrame() == field070)
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
