// Marisa special-card vertical flight siblings. The original states share
// the exact frame/collision skeleton but have three distinct launch vectors.
        case 0xCC: {
            if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
                SetCommandSelection(3, 4, 0xFF);
                field088 = 2;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame < animationFrameCount)
                return;
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 0.0f;
                velocityY = 21.0f;
                field05C = 0.75f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStageCount <= animationStage)
                animationStage -= 2;
            BindAnimation();
            return;
        }

        case 0xCD: {
            if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
                SetCommandSelection(3, 4, 0xFF);
                field088 = 2;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame < animationFrameCount)
                return;
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 10.0f;
                velocityY = 16.0f;
                field05C = 0.7f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStageCount <= animationStage)
                animationStage -= 2;
            BindAnimation();
            return;
        }

        case 0xCE: {
            if (y == g_ThresholdAt0065782C || velocityY > g_ThresholdAt0065782C) {
                SetCommandSelection(3, 4, 0xFF);
                field088 = 2;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (velocityY + y < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if (animationFrame < animationFrameCount)
                return;
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = -10.0f;
                velocityY = 16.0f;
                field05C = 0.7f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStageCount <= animationStage)
                animationStage -= 2;
            BindAnimation();
            return;
        }
