// F711: real native 00543210 action2D0/2D1, each 416 B /120 x86.
// Different actual storm config, fall duration and random horizontal
// velocity; two native 7D/7E projectiles are retained in each case.
// Entire original fighter still NONEXACT; no independent function credit.
        case 0x2D0: {
            SetCommandSelection(3,4,0xFF0000);
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=0.0f;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (y>g_ThresholdAt0065782C && (animationStage)<7) {
                velocityY=velocityY-g_ApproachLowerAt00658290;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(7);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                break;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityX=float(RandomBoundaryAt455580(0,15))+g_ApproachUpperAt006592A4;
                velocityY=40.0f;
                field05C=6.0f;
                SpawnAt453C80(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_EightShotY2At00658268,
                    facing,1);
                SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
                    (*(&y))+g_EightShotY2At00658268,
                    facing,1);
                PlaySharedSound(31);
            }
            break;
        }
        case 0x2D1: {
            SetCommandSelection(3,4,0xFF);
            if ((animationStage)==0 && (animationFrame)==0) {
                velocityX=0.0f;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if (y>g_ThresholdAt0065782C && (animationStage)<6) {
                velocityY=velocityY-g_ApproachLowerAt00658290;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(6);
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                ResetPrimaryCounters(0);
                break;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                velocityX=g_F711_ReverseRandomAt00659A0C-float(RandomBoundaryAt455580(0,15));
                velocityY=40.0f;
                field05C=6.0f;
                SpawnAt453C80(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_EightShotY2At00658268,
                    facing,1);
                SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
                    (*(&y))+g_EightShotY2At00658268,
                    facing,1);
                PlaySharedSound(31);
            }
            break;
        }
