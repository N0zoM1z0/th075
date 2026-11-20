// Marisa's native 0x19F-0x1A3 card-resource siblings.
        case 0x19F: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage != 6 || animationFrame != 0)
                return;
            field314 = 55.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 81) + x,
                y + g_MarisaResourceYAt006581DC, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
            return;
        }

        case 0x1A0: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                velocityX *= g_BounceScaleAt00657F74;
                velocityY *= g_BounceScaleAt00657F74;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage != 6 || animationFrame != 0)
                return;
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 80) + x,
                y + g_MarisaResourceYAt00659290, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
            return;
        }

        case 0x1A1: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                velocityX *= g_BounceScaleAt00657F74;
                velocityY *= g_BounceScaleAt00657F74;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage != 6 || animationFrame != 0)
                return;
            field314 = -20.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(static_cast<int>(facing) << 6) + x,
                y + g_MarisaResourceYAt006581DC, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
            return;
        }

        case 0x1A2: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                UpdateGaugeTimer(0xFA);
                field314 = 5.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                field314 = 6.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                field314 = 7.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                field314 = 8.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                PlaySound(5);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x1A3: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                UpdateGaugeTimer(0xFA);
                field314 = 10.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                field314 = 11.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                field314 = 12.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                field314 = 13.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                PlaySound(5);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            return;
        }
