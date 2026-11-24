// F711: real native 00543210 action2D0/2D1, each 416 B /120 x86.
// Different actual storm config, fall duration and random horizontal
// velocity; two native 7D/7E projectiles are retained in each case.
// Entire original fighter still NONEXACT; no independent function credit.
        case 0x2D0: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=0.0f;
                scriptCounterF00=0;
            }
            if (y>FloatConstants::Zero && (animationStage)<7) {
                velocityY=velocityY-GeometryConstants::Six;
                if (y+velocityY<=FloatConstants::Zero) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(7);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                break;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityX=float(RecordedRange(0,15))+GeometryConstants::TwentyFive;
                velocityY=40.0f;
                field05C=6.0f;
                SpawnAuxEffect(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+GeometryConstants::Eighty,
                    facing,1);
                SpawnAuxEffect(0x7E,x,
                    (*(&y))+GeometryConstants::Eighty,
                    facing,1);
                PlaySharedSound(31);
            }
            break;
        }
        case 0x2D1: {
            SetCommandSelection(3,4,0xFF);
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=0.0f;
                scriptCounterF00=0;
            }
            if (y>FloatConstants::Zero && (animationStage)<6) {
                velocityY=velocityY-GeometryConstants::Six;
                if (y+velocityY<=FloatConstants::Zero) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(6);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                ResetPrimaryCounters(0);
                break;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=g_F711_ReverseRandomAt00659A0C-float(RecordedRange(0,15));
                velocityY=40.0f;
                field05C=6.0f;
                SpawnAuxEffect(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+GeometryConstants::Eighty,
                    facing,1);
                SpawnAuxEffect(0x7E,x,
                    (*(&y))+GeometryConstants::Eighty,
                    facing,1);
                PlaySharedSound(31);
            }
            break;
        }
