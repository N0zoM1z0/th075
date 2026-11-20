// Marisa's native 0x19C-0x19E card-resource actions.
        case 0x19C: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage != 6 || animationFrame != 0)
                return;
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 96) + x,
                y + g_MarisaResourceYAt00659298, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
            return;
        }

        case 0x19D: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage != 6 || animationFrame != 0)
                return;
            field314 = 20.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 90) + x,
                y + g_MarisaCommandYAt00658268, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
            return;
        }

        case 0x19E: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (animationStage == 6 && animationFrame == 0) {
                field314 = 0.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 92) + x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
                PlaySound(1);
                UpdateGaugeTimer(200);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 7 && animationFrame == 0 &&
                inputC != 0 && scriptCounterF00 < 5) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            return;
        }
