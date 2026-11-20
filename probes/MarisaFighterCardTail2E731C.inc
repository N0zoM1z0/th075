// Range-local split of MarisaFighterCardTail2BD31C.inc.
        case 0x2E7: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                ClearMotionFields();
            }
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetSecondaryCounter(0x0E);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(3);
            if (animationStage == 4 && animationFrame == 0) {
                velocityX = static_cast<float>(RecordedRange(0, 8)) +
                    g_ExtraThresholdAt00657D14;
                velocityY = static_cast<float>(RecordedRange(0, 5)) +
                    g_MarisaRandomVelocityYBaseAt00657D70;
                field05C = 0.2f;
            }
            if (animationStage == 14 && animationFrame == 0) {
                if (scriptCounterF00 > 5)
                    return;
                ++scriptCounterF00;
                ResetSecondaryCounter(8);
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
        case 0x2FA: {
            if (animationStage == 0 && animationFrame == 0) {
                facing = 1;
                scriptCounterF00 = 0;
                scriptCounterF02 = 0;
                velocityX = 0.0f;
            }
            --scriptCounterF00;
            if (animationStage < 2) {
                velocityY -= g_MarisaCardFallAt00659264;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(2);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage == 2 && animationFrame == 0)
                ResetSecondaryCounter(0);
            return;
        }
        case 0x31B: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == animationStageCount)
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
            if (AdvanceNestedFrame() == animationStageCount)
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
