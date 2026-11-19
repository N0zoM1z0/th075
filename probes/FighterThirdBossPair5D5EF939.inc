// F939: original 004AC040 two native 337B/101 x86 adjacent stage actions, actor-specific stage/camera/aux thresholds, whole father NONEXACT.
// F752: actual original 05D/05E borrowed actor and opponent X at +0x44.
// The type is ONLY an observed borrowed memory view: never instantiated.
// Both typed floating members restore native VC7.1 direct FCOMP memory
// instead of the two nonoriginal FLD/FCOMPP sequences from raw casts.
// F747: true complete original 059/05D/05E normal C++ action interiors
// in ONE 58KB fighter 00543210 giant parent. No independent CODE credit.
// Native original 059 00545109..0054526D 356 B /95 x86;
// 05D 0054526D..005453BE 337 B/101 x86;
// 05E 005453BE..0054550F 337 B/101 x86.
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
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(field070)-1) {
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
            if ((animationStage)==12 && (animationFrame)==0)
                ResetSecondaryCounter(10);
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
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                if (inputY>0)
                    ResetPrimaryCounters(1);
            }
            if ((animationStage)==(field070)-1) {
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
            if ((animationStage)==9 && (animationFrame)==0)
                ResetSecondaryCounter(8);
            break;
        }
