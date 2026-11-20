// Marisa's native 0x60/0x61 ten-shot resource volleys.
// The original handlers are 0x004888D0..0x00488D0A (541 bytes each).
        case 0x60: {
            if (static_cast<int>(facing) * inputX > 0
                && (static_cast<unsigned int>(inputA) > 0
                 || static_cast<unsigned int>(inputB) > 0
                 || static_cast<unsigned int>(inputC) > 0
                 || static_cast<unsigned int>(inputD) > 0))
                scriptCounterF00 = 1;
            if (static_cast<int>(facing) * inputX < 0
                && (static_cast<unsigned int>(inputA) > 0
                 || static_cast<unsigned int>(inputB) > 0
                 || static_cast<unsigned int>(inputC) > 0
                 || static_cast<unsigned int>(inputD) > 0))
                scriptCounterF00 = 2;
            if (animationStage == 0 && animationFrame == 0) {
                for (int shot = 0; shot < 10; ++shot)
                    SpawnBattleEffect(0x3E4, x, y, 1, 1);
                if (fieldEFA > 25) {
                    fieldEFA = 0;
                    SpawnBattleEffect(0x3E3, x, y, 1, 1);
                }
            }
            if (animationStage == 3) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(4);
                    break;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0x62);
                if (field3CF == 0)
                    ResetPrimaryCounters(99);
            } else if (animationStage == 3 && animationFrame == 0) {
                velocityX = static_cast<float>(scriptCounterF00) * g_F748_SpeedScaleAt006590B8;
                velocityY = static_cast<float>(-scriptCounterF02) * g_F748_SpeedScaleAt006590B8;
                field05C = 2.0f;
            }
            break;
        }
        case 0x61: {
            if (static_cast<int>(facing) * inputX > 0
                && (static_cast<unsigned int>(inputA) > 0
                 || static_cast<unsigned int>(inputB) > 0
                 || static_cast<unsigned int>(inputC) > 0
                 || static_cast<unsigned int>(inputD) > 0))
                scriptCounterF00 = 1;
            if (static_cast<int>(facing) * inputX < 0
                && (static_cast<unsigned int>(inputA) > 0
                 || static_cast<unsigned int>(inputB) > 0
                 || static_cast<unsigned int>(inputC) > 0
                 || static_cast<unsigned int>(inputD) > 0))
                scriptCounterF00 = 2;
            if (animationStage == 0 && animationFrame == 0) {
                for (int shot = 0; shot < 10; ++shot)
                    SpawnBattleEffect(0x3E4, x, y, 1, 1);
                if (fieldEFA > 25) {
                    fieldEFA = 0;
                    SpawnBattleEffect(0x3E3, x, y, 1, 1);
                }
            }
            if (animationStage == 3) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(4);
                    break;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0x62);
                if (field3CF == 0)
                    ResetPrimaryCounters(99);
            } else if (animationStage == 3 && animationFrame == 0) {
                velocityX = static_cast<float>(scriptCounterF00) * g_F748_SpeedScaleAt006590B8;
                velocityY = static_cast<float>(-scriptCounterF02) * g_F748_SpeedScaleAt006590B8;
                field05C = 2.0f;
            }
            break;
        }
