// Original handler order 0x2EF, 0x2F0, 0x2F2.
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
            if (AdvanceNestedFrame() == animationStageCount) {
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
            if (AdvanceNestedFrame() == animationStageCount) {
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
        case 0x2F2: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(12);
                aiCardTimer = 0;
            }
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = static_cast<float>(RecordedRange(0, 8)) +
                    g_MarisaRandomVelocityYBaseAt00657D70;
                velocityY = static_cast<float>(RecordedRange(0, 5)) +
                    g_MarisaCommandSpeedLowerAt00657850;
                field05C = 0.5f;
            }
            return;
        }
