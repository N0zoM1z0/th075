// Sakuya landing actions 0x5D and 0x5E in 0x004AC040.
        case 0x5D: {
            if ((animationStage)<12 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(12);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(animationStageCount)-1) {
                if (x>opponent->x)
                    facing=-1;
                if (x<opponent->x)
                    facing=1;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityY=8.0f;
                velocityX=12.5f;
                field05C=0.7f;
            }
            if (animationStage == 12 && animationFrame == 0)
                ResetSecondaryCounter(10);
            else if (animationStage == 12 && animationFrame != 0) {
                // Continue the landing animation.
            }
            break;
        }
        case 0x5E: {
            if ((animationStage)<9 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(9);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(animationStageCount)-1) {
                if (x>opponent->x)
                    facing=-1;
                if (x<opponent->x)
                    facing=1;
            }
            if ((animationStage)==6 && (animationFrame)==0) {
                velocityY=8.0f;
                velocityX=-12.5f;
                field05C=0.7f;
            }
            if (animationStage == 9 && animationFrame == 0)
                ResetSecondaryCounter(8);
            else if (animationStage == 9 && animationFrame != 0) {
                // Continue the landing animation.
            }
            break;
        }
