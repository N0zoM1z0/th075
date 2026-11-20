// Marisa's native special projectile states 0x18A and 0x18B.
        case 0x18A: {
            if (animationStage == 0 && animationFrame == 0) {
                field080 = 1;
                field07C = 0;
                velocityX = 15.0f;
                scriptCounterF00 = 0;
            }
            velocityX -= g_JumpGroundCorrectionAt00658058;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x327,
                    static_cast<float>(facing * 151) + x,
                    y + g_MarisaSpecialProjectileYAt0065929C, facing, 1);
            }
            return;
        }

        case 0x18B: {
            if (animationStage == 0 && animationFrame == 0) {
                field080 = 1;
                field07C = 0;
                velocityX = 10.0f;
                scriptCounterF00 = 0;
            }
            if (animationStage > 6) {
                velocityX -= g_JumpGroundCorrectionAt00658058;
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    field3AC = 0;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(2);
            if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 2) {
                ++scriptCounterF00;
                ResetSecondaryCounter(6);
                field080 = 1;
                field07C = 0;
            }
            if (animationStage == 6 && animationFrame == 0) {
                SpawnBattleEffect(0x328,
                    static_cast<float>(static_cast<int>(facing) << 7) + x,
                    y + g_MarisaSpecialProjectileYAt00658400, facing, 1);
            }
            return;
        }
