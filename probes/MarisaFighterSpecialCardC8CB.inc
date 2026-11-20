// Marisa special-card command selection and its three attack directions.
// Native handler extents: C8 0x48A650..0x48A860, C9 0x48A861..0x48AA2E,
// CA 0x48AA2F..0x48ABD0, CB 0x48ABD1..0x48ADC0.
        case 0xC8: {
            field3AC = 1;
            SetCommandSelection(3, 4, 0xFF);
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = 0.0f;
                scriptCounterF00 = 0;
            }
            if (velocityX > g_MarisaCommandSpeedUpperAt006592A0) {
                velocityX -= g_SubtractAt00657478;
                if (velocityX < g_MarisaCommandSpeedLowerAt00657850)
                    velocityX = g_MarisaCommandSpeedLowerAt00657850;
            }
            if (inputY < 0) {
                if (static_cast<int>(facing) * inputX > 0)
                    ResetPrimaryCounters(0xCD);
                else
                    ResetPrimaryCounters(0xCC);
                return;
            }
            if (scriptCounterF00 > 0 && static_cast<int>(facing) * inputX < 1) {
                ResetPrimaryCounters(0xCF);
                return;
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                if (static_cast<int>(facing) * inputX > 0 && scriptCounterF00 < 2) {
                    ResetSecondaryCounter(4);
                    ++scriptCounterF00;
                    return;
                }
                ResetPrimaryCounters(0xCF);
                return;
            }
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = 15.0f;
                SpawnAuxEffect(0x7D,
                    static_cast<float>(facing * 80) + x,
                    y + g_MarisaCommandYAt00658268, facing, 1);
                SpawnAuxEffect(0x7E, x,
                    y + g_MarisaCommandYAt00658268, facing, 1);
                PlaySharedSound(0x1F);
            }
            return;
        }

        case 0xC9: {
            SetCommandSelection(3, 4, 0xFF);
            if (animationStage == 0 && animationFrame == 0)
                velocityX = 0.0f;
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = -11.0f;
                velocityY = 5.0f;
                field05C = 0.6f;
                SpawnAuxEffect(0x7D,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaCommandYAt00658268, -facing, 1);
                SpawnAuxEffect(0x7E, x,
                    y + g_MarisaCommandYAt00658268, -facing, 1);
                PlaySharedSound(0x1F);
            }
            if (animationStage > 1 && animationStage < 5 && y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    field05C = 0.0f;
                    y = 0.0f;
                    animationFrame = 0;
                    ResetSecondaryCounter(5);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            if (animationStage != 5 || animationFrame != 0)
                return;
            ResetSecondaryCounter(animationStage - 2);
            return;
        }

        case 0xCA: {
            SetCommandSelection(3, 4, 0xFF);
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
            }
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = 10.5f;
                velocityY = 5.0f;
                field05C = 0.6f;
                SpawnAuxEffect(0x7D,
                    static_cast<float>(facing * 80) + x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                SpawnAuxEffect(0x7E, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                PlaySharedSound(0x1F);
            }
            if (animationStage > 1 && y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    field05C = 0.0f;
                    y = 0.0f;
                    animationFrame = 0;
                    ResetPrimaryCounters(10);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(9);
                return;
            }
            return;
        }

        case 0xCB: {
            SetCommandSelection(3, 4, 0xFF);
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
            }
            if (animationStage > 0 && y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    field05C = 0.0f;
                    y = 0.0f;
                    animationFrame = 0;
                    ResetPrimaryCounters(10);
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            if (animationStage == 1 && animationFrame == 0) {
                velocityX = -10.5f;
                velocityY = 5.0f;
                field05C = 0.6f;
                SpawnAuxEffect(0x7D,
                    x - static_cast<float>(facing * 80),
                    y + g_ContactProjectionAt00657888, -facing, 1);
                SpawnAuxEffect(0x7E, x,
                    y + g_ContactProjectionAt00657888, -facing, 1);
                PlaySharedSound(0x1F);
            }
            if (animationStage == 3 && scriptCounterF00 <= 0) {
                ++scriptCounterF00;
                ResetSecondaryCounter(1);
            }
            return;
        }
