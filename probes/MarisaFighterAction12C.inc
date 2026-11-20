// Native Marisa action 0x12C: horizontal drift with the ordinary frame exit.
        case 0x12C: {
            if (animationStage == 0 && animationFrame == 0) {
                if (field3AC == 0)
                    ClearMotionFields();
                field080 = 1;
                field07C = 0;
            }
            if (field3AC > 0) {
                velocityX -= g_JumpGroundCorrectionAt00658058;
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX = 0.0f;
                    field3AC = 0;
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            if (animationStage == 3 && animationFrame == 0)
                PlaySharedSound(0x1B);
            return;
        }
