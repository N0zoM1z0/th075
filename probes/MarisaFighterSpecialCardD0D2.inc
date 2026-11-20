// Marisa's native D0-D2 special-card follow-up states.
// D1/D2 consume the same signed spirit field used by the normal guard system.
        case 0xD0: {
            if (animationStage == 0 && animationFrame == 0) {
                facing = static_cast<signed char>(-facing);
                velocityX = -velocityX;
            }
            if (field05C == g_ThresholdAt0065782C)
                field05C = 0.6f;
            velocityY -= field05C;
            if (velocityY + y <= g_ThresholdAt0065782C) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
            if (AdvanceNestedFrame() != field070)
                return;
            ResetSecondaryCounter(5);
            return;
        }

        case 0xD1: {
            if (spirit < 2) {
                ResetPrimaryCounters(0);
                return;
            }
            spirit = static_cast<short>(spirit - 3);
            if (animationStage == 0 && animationFrame == 0) {
                ClearMotionFields();
                PlaySharedSound(0x2C);
                SpawnBattleEffect(0x3E6, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
            }
            if (AdvanceNestedFrame() != field070)
                return;
            if (inputD != 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(0);
            return;
        }

        case 0xD2: {
            if (spirit < 2) {
                ResetPrimaryCounters(9);
                return;
            }
            spirit = static_cast<short>(spirit - 3);
            if (animationStage == 0 && animationFrame == 0) {
                SpawnBattleEffect(0x3E6, x,
                    y + g_ContactProjectionAt00657888, facing, 1);
                velocityX *= 0.25f;
                velocityY *= 0.25f;
                PlaySharedSound(0x2C);
            }
            velocityY -= field05C * 0.25f;
            if (AdvanceNestedFrame() != field070)
                return;
            if (inputD != 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
            return;
        }
