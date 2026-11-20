// Marisa's six native resource volleys 0x196-0x19B. These are full
// original action bodies inside the 50 KB parent, not independent functions.
        case 0x196: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 6 && animationFrame == 0) {
                field314 = static_cast<float>(static_cast<int>(scriptCounterF00) << 3);
                SpawnBattleEffect(0x32B,
                    static_cast<float>(facing * 96) + x,
                    y + g_MarisaSpecialProjectileYAt0065929C, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(100);
            }
            if (animationStage != 7 || animationFrame != 0 || inputC == 0 ||
                scriptCounterF00 > 4 || spirit < 1)
                return;
            ++scriptCounterF00;
            field314 = static_cast<float>(static_cast<int>(scriptCounterF00) << 3);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 96) + x,
                y + g_MarisaSpecialProjectileYAt0065929C, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
            return;
        }

        case 0x197: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 6 && animationFrame == 0) {
                field314 = static_cast<float>(scriptCounterF00 * 8 + 30);
                SpawnBattleEffect(0x32B,
                    static_cast<float>(facing * 90) + x,
                    y + g_MarisaResourceYAt00659298, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(100);
            }
            if (animationStage != 7 || animationFrame != 0 || inputC == 0 ||
                scriptCounterF00 > 4 || spirit < 1)
                return;
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * 8 + 30);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 90) + x,
                y + g_MarisaResourceYAt00659298, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
            return;
        }

        case 0x198: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
                UpdateGaugeTimer(100);
            }
            if (animationStage == 6 && animationFrame == 0) {
                field314 = static_cast<float>(static_cast<int>(scriptCounterF00) << 2);
                SpawnBattleEffect(0x32B,
                    static_cast<float>(facing * 92) + x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(20);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 7 && animationFrame == 0 &&
                inputC != 0 && scriptCounterF00 <= 4) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            return;
        }

        case 0x199: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            velocityY -= field05C;
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 6 && animationFrame == 0) {
                velocityX = -3.0f;
                velocityY = 8.5f;
                field05C = 0.5f;
                field314 = static_cast<float>(scriptCounterF00 * -8 + 45);
                SpawnBattleEffect(0x32B,
                    static_cast<float>(facing * 81) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(100);
            }
            if (animationStage != 7 || animationFrame != 0 || inputC == 0 ||
                scriptCounterF00 > 4 || spirit < 1)
                return;
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * -8 + 45);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 81) + x,
                y + g_MarisaResourceYAt006581DC, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
            return;
        }

        case 0x19A: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            velocityY -= field05C;
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage == 6 && animationFrame == 0) {
                velocityX = -3.0f;
                velocityY = 8.5f;
                field05C = 0.5f;
                field314 = static_cast<float>(scriptCounterF00 * -8);
                SpawnBattleEffect(0x32B,
                    static_cast<float>(facing * 80) + x,
                    y + g_MarisaResourceYAt00659290, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(100);
            }
            if (animationStage != 7 || animationFrame != 0 || inputC == 0 ||
                scriptCounterF00 > 4 || spirit < 1)
                return;
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * -8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 80) + x,
                y + g_MarisaResourceYAt00659290, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
            return;
        }

        case 0x19B: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            velocityY -= field05C;
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage == 6 && animationFrame == 0) {
                velocityX = -3.0f;
                velocityY = 8.5f;
                field05C = 0.5f;
                field314 = static_cast<float>(scriptCounterF00 * 8 - 45);
                SpawnBattleEffect(0x32B,
                    static_cast<float>(static_cast<int>(facing) << 6) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(100);
            }
            if (animationStage != 7 || animationFrame != 0 || inputC == 0 ||
                scriptCounterF00 > 4 || spirit < 1)
                return;
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * 8 - 45);
            SpawnBattleEffect(0x32B,
                static_cast<float>(static_cast<int>(facing) << 6) + x,
                y + g_MarisaResourceYAt006581DC, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
            return;
        }
