// Original handler order 0x31B, 0x31C.
        case 0x31B: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 4 && animationFrame == 0) {
                BeginFadeParameters(0);
                SelectResourceParameters();
                PlaySharedSound(0x17);
                SpawnBattleEffect(0x3E5, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
            }
            if (animationStage == 8 && animationFrame == 0) {
                if (scriptCounterF00 > 7)
                    return;
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
            }
            return;
        }
        case 0x31C: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 16 && animationFrame == 0) {
                BeginFadeParameters(0);
                SelectResourceParameters();
                PlaySharedSound(0x17);
            }
            if (animationStage == 20 && animationFrame == 0) {
                if (scriptCounterF00 > 7)
                    return;
                ++scriptCounterF00;
                ResetSecondaryCounter(0x12);
                field3CF = 1;
            }
            return;
        }
