// Marisa's native card-resource finishers 0x191, 0x192 and 0x194.
        case 0x191: {
            if (animationStage == 0 && animationFrame == 0)
                field07C = 1;
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x321,
                    static_cast<float>(facing * 100) + x,
                    y + g_MarisaResourceYAt00659298, facing, 1);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            return;
        }

        case 0x192: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x321,
                    static_cast<float>(facing * 99) + x,
                    y + g_MarisaResourceYAt006590A4, facing, 1);
                UpdateGaugeTimer(0x96);
                PlaySound(6);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(2);
            return;
        }

        case 0x194: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX *= g_MarisaCardVelocityScaleAt006590B4;
                velocityY *= g_MarisaCardVelocityScaleAt006590B4;
                field07C = 1;
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x322,
                    static_cast<float>(facing * 70) + x,
                    y + g_MarisaResourceYAt00659294, facing, 1);
                UpdateGaugeTimer(0x96);
                PlaySound(6);
            }
            return;
        }
