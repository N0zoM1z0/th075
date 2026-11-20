// Marisa's native 0x252-0x25D and 0x270-0x271 card/resource actions.
        case 0x252: {
            if (animationStage == 0 && animationFrame == 0) {
                --field366;
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                scriptCounterF00 = 0;
            }
            if (spiritCooldown == 0 && field07C == 1)
                spirit = 1000;
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnAuxEffect(0x37, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x21);
                opponent->fieldEFA = 0;
            }
            return;
        }

        case 0x253: {
            if (animationStage == 0 && animationFrame == 0) {
                --field366;
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                scriptCounterF00 = 0;
            }
            if (spiritCooldown == 0 && field07C == 1)
                spirit = 1000;
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnAuxEffect(0x37, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x21);
                opponent->fieldEFA = 0;
            }
            return;
        }

        case 0x254: {
            if (animationStage == 0 && animationFrame == 0) {
                --field366;
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnAuxEffect(0x37, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x21);
                opponent->fieldEFA = 0;
            }
            return;
        }

        case 0x255: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnAuxEffect(0x37, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x21);
            }
            if (animationStage == 8 && animationFrame == 0) {
                if (scriptCounterF00 > 0)
                    return;
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            return;
        }

        case 0x256: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnAuxEffect(0x37, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x21);
            }
            return;
        }

        case 0x257: {
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                field080 = 1;
                field07C = 0;
                field3AC = 0;
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnAuxEffect(0x37, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x21);
            }
            if (animationStage == 8 && animationFrame == 0) {
                if (scriptCounterF00 > 0)
                    return;
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            return;
        }

        case 0x258: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (animationStage == 6 && animationFrame == 0) {
                field314 = 0.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 100) + x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySound(4);
                UpdateGaugeTimer(200);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x259: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (animationStage == 6 && animationFrame == 0) {
                field314 = 30.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 90) + x,
                    y + g_MarisaResourceYAt00659298, facing, 1);
                PlaySound(4);
                UpdateGaugeTimer(200);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x25A: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX *= g_BounceScaleAt00657F74;
                velocityY *= g_BounceScaleAt00657F74;
                field07C = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage == 6 && animationFrame == 0) {
                field314 = 0.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(facing * 74) + x,
                    y + g_MarisaResourceYAt00659288, facing, 1);
                PlaySound(4);
                UpdateGaugeTimer(200);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            return;
        }

        case 0x25B: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX *= g_BounceScaleAt00657F74;
                velocityY *= g_BounceScaleAt00657F74;
                field07C = 1;
                scriptCounterF00 = 0;
            }
            if (animationStage == 6 && animationFrame == 0) {
                field314 = -30.0f;
                SpawnBattleEffect(0x32C,
                    static_cast<float>(static_cast<int>(facing) << 6) + x,
                    y + g_MarisaResourceYAt00659284, facing, 1);
                PlaySound(4);
                UpdateGaugeTimer(200);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            return;
        }

        case 0x25C: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                PlaySound(5);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x25D: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x333,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                PlaySound(5);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x270: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                UpdateGaugeTimer(0xFA);
                field314 = 20.0f;
                field318 = 150.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                PlaySound(5);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x271: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                UpdateGaugeTimer(0xFA);
                field314 = 60.0f;
                field318 = 150.0f;
                SpawnBattleEffect(0x332,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt0065928C, facing, 1);
                PlaySound(5);
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            return;
        }
