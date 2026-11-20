// Marisa's late card transition/finish states 0x2C3-0x2D1.
        case 0x2C3: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73, x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (animationStage == 5 && animationFrame == 0) {
                PlaySound(0x0E);
                UpdateGaugeTimer(500);
            }
            return;
        }

        case 0x2C4: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x73,
                    x - static_cast<float>(facing * 20),
                    y + g_MarisaResourceYAt0065927C, facing, 1);
            }
            if (animationStage == 5 && animationFrame == 0) {
                PlaySound(0x0F);
                UpdateGaugeTimer(500);
                fieldF18 = 300;
            }
            return;
        }

        case 0x2C5: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0)
                PlaySound(0x10);
            return;
        }

        case 0x2C6: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                velocityX *= g_MarisaCardVelocityScaleAt006590B4;
                velocityY *= g_MarisaCardVelocityScaleAt006590B4;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage == 5 && animationFrame == 0)
                PlaySound(0x10);
            return;
        }

        case 0x2C8: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (animationStage == 5 && animationFrame == 0) {
                SpawnBattleEffect(0x345,
                    static_cast<float>(facing * 32) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
                SpawnBattleEffect(0x346,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 2 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x74,
                    x - static_cast<float>(facing * 18),
                    y + g_MarisaResourceYAt00659284, facing, 1);
            }
            if (animationStage == 6 && animationFrame == 0) {
                ResetPrimaryCounters(0x2C9);
                SpawnBattleEffect(0x34F,
                    x - static_cast<float>(facing * 80),
                    y + g_MarisaResourceYAt0065908C, facing, 0);
                PlaySound(0x11);
            }
            return;
        }

        case 0x2C9: {
            if (animationStage == 0 && animationFrame == 0) {
                SpawnBattleEffect(0x347,
                    static_cast<float>(facing * 64) + x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            SetCameraShake(5.0f);
            if (g_MarisaProjectilePairYAt00657CF8 <= field36C || spirit > 19) {
                field36C -= g_MarisaProjectilePairYAt00657CF8;
                UpdateGaugeTimer(20);
            } else {
                field36C = 0.0f;
                ++scriptCounterF00;
            }
            if (scriptCounterF00 > 50) {
                scriptCounterF00 = 0;
                ResetPrimaryCounters(700);
                ResetSecondaryCounter(6);
                if (opponent->health < 1)
                    return;
                field3A0 = 1;
                return;
            }
            if (AdvanceNestedFrame() != field070)
                return;
            ResetSecondaryCounter(0);
            return;
        }

        case 0x2CA: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x74, x,
                    y + g_MarisaResourceYAt006581DC, facing, 1);
            }
            if (animationStage == 5 && animationFrame == 0) {
                PlaySound(0x0E);
                UpdateGaugeTimer(500);
            }
            return;
        }

        case 0x2CB: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0) {
                SetNonnegativeWord(0x28);
                PlaySharedSound(0x17);
                SpawnAuxEffect(0x74,
                    x - static_cast<float>(facing * 20),
                    y + g_MarisaResourceYAt0065927C, facing, 1);
            }
            if (animationStage == 5 && animationFrame == 0) {
                PlaySound(6);
                UpdateGaugeTimer(500);
                fieldF18 = 300;
            }
            return;
        }

        case 0x2CC: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                ClearMotionFields();
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 5 && animationFrame == 0)
                PlaySound(6);
            return;
        }

        case 0x2CD: {
            if (animationStage == 0 && animationFrame == 0) {
                scriptCounterF00 = 0;
                field07C = 1;
                velocityX *= g_MarisaCardVelocityScaleAt006590B4;
                velocityY *= g_MarisaCardVelocityScaleAt006590B4;
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(9);
            if (animationStage == 5 && animationFrame == 0)
                PlaySound(6);
            return;
        }

        case 0x2CE:
        case 0x2CF: {
            if (animationStage == 0 && animationFrame == 0) {
                field07C = 1;
                ClearMotionFields();
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() != field070)
                return;
            ResetPrimaryCounters(0);
            return;
        }

        case 0x2D0:
        case 0x2D1: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX *= g_MarisaCardVelocityScaleAt006590B4;
                velocityY *= g_MarisaCardVelocityScaleAt006590B4;
                field07C = 1;
                scriptCounterF00 = 0;
            }
            if (AdvanceNestedFrame() != field070)
                return;
            ResetPrimaryCounters(9);
            return;
        }
