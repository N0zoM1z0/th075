// Range-local split of MarisaFighterCardTail2BD31C.inc.
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
            if (AdvanceNestedFrame() != animationStageCount)
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
            if (AdvanceNestedFrame() == animationStageCount)
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
