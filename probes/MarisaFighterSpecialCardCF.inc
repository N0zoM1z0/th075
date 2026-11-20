// Marisa's native 0xCF horizontal return and state-flag cleanup.
        case 0xCF: {
            field3AC = 1;
            velocityX -= g_SubtractAt00657478;
            if (velocityX < g_ThresholdAt0065782C) {
                velocityX = 0.0f;
                field3AC = 0;
            }
            if (AdvanceNestedFrame() == field070) {
                ResetPrimaryCounters(0);
                field3AC = 0;
            }
            return;
        }
