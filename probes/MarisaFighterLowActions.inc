// Marisa Advance low-action dispatch (0x00..0x0A).
        case 0x0:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            break;
        case 0x1:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(2);
            break;
        case 0x2:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            break;
        case 0x3:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            break;
        case 0x4:
            velocityX = 6.0f;
            goto advanceNestedAndReturn;
        case 0x5:
            velocityX = -6.0f;
            goto advanceNestedAndReturn;
        case 0x6:
            if (animationStage == 0 && animationFrame == 0 &&
                    (aiCommand == 3 || field3AC > 0)) {
                ResetPrimaryCounters(0xCC);
                return;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY = velocityY - field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame >= animationFrameCount) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 4) {
                    velocityX = 0.0f;
                    velocityY = 16.0f;
                    field05C = 0.75f;
                    field3AC = 0;
                }
                if (animationStage >= animationStageCount)
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x7:
            if (animationStage == 0 && animationFrame == 0 &&
                    (aiCommand == 5 || field3AC > 0)) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY = velocityY - field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame >= animationFrameCount) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 4) {
                    velocityX = 5.0f;
                    velocityY = 16.0f;
                    field05C = 0.75f;
                    field3AC = 0;
                }
                if (animationStage >= animationStageCount)
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x8:
            if (animationStage == 0 && animationFrame == 0 &&
                    (aiCommand == 4 || field3AC > 0)) {
                ResetPrimaryCounters(0xCE);
                return;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY = velocityY - field05C;
                if (y + velocityY < g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if (animationFrame >= animationFrameCount) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 4) {
                    velocityX = -4.0f;
                    field3AC = 0;
                    velocityY = 16.0f;
                    field05C = 0.75f;
                }
                if (animationStage >= animationStageCount)
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x9:
        if (field05C == g_ThresholdAt0065782C)
            field05C = 0.6f;
        velocityY = velocityY - field05C;
        if (y + velocityY < g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;
        case 0xA:
            if (animationStage == 0 && animationFrame == 0)
                PlaySharedSound(30);
            ClearMotionFields();
            if (AdvanceNestedFrame() == animationStageCount) {
                if (inputY == 0)
                    ResetPrimaryCounters(3);
                else
                    ResetPrimaryCounters(2);
            }
            break;
