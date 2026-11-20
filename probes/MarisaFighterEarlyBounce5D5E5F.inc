// Marisa's native 0x5D/0x5E/0x5F early-bounce and facing states.
// Recovered from the original handlers 0x0048859E..0x004888D0.
        case 0x5D: {
            if (animationStage < 11 && y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY <= g_ThresholdAt0065782C) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(11);
                    break;
                }
            }
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0);
                if (inputY > 0)
                    ResetPrimaryCounters(1);
            }
            if (animationStage == field070 - 1) {
                if (opponent->x < x)
                    facing = -1;
                if (x < opponent->x)
                    facing = 1;
            }
            if (animationStage == 5 && animationFrame == 0) {
                velocityY = 8.0f;
                velocityX = 13.5f;
                field05C = 0.6f;
            }
            if (animationStage == 11 && animationFrame == 0)
                ResetSecondaryCounter(9);
            break;
        }
        case 0x5E: {
            if (animationStage < 12 && y > g_ThresholdAt0065782C) {
                velocityY -= field05C;
                if (y + velocityY <= g_ThresholdAt0065782C) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(12);
                    break;
                }
            }
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0);
                if (inputY > 0)
                    ResetPrimaryCounters(1);
            }
            if (animationStage == field070 - 1) {
                if (opponent->x < x)
                    facing = -1;
                if (x < opponent->x)
                    facing = 1;
            }
            if (animationStage == 4 && animationFrame == 0) {
                velocityY = 8.0f;
                velocityX = -13.5f;
                field05C = 0.6f;
            }
            if (animationStage == 12 && animationFrame == 0)
                ResetSecondaryCounter(10);
            break;
        }
        case 0x5F: {
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0);
                if (inputY > 0)
                    ResetPrimaryCounters(1);
            }
            if (animationStage != field070 - 1)
                break;
            if (opponent->x < x)
                facing = -1;
            if (opponent->x <= x)
                break;
            facing = 1;
            break;
        }
