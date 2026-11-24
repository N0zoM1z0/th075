// F763: entire original 2DB authored state inside full native 00543210.
// Genuine strict side-edge and abs-distance predicates, and typed actor
// /opponent X positions. Not independently callable CODE or parent-exact.
// F715: original entire physical 00543210 action0x2DB,
// real 0054E451..0054E851: 1024 native CODE B /290 real x86.
// Complete original state, ground/contact and wall predicates, owner
// distance, signed-direction random choice, 7D/7E shots and 2DF/2DC
// transitions. Source is NONEXACT until entire original boss matches.
        case 0x2DB: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ClearMotionFields();
                field080=1;
                field07C=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if ((animationStage)<10 && y>FloatConstants::Zero && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-FloatConstants::ThreeFifths;
                if (y+velocityY<=FloatConstants::Zero) {
                    ClearMotionFields();
                    ResetPrimaryCounters(10);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>9 && (animationStage)<13 && !CheckHorizontalLimits()) {
                if (facing==1)
                    x=(field2D8)+FloatConstants::Five;
                if (facing==-1)
                    x=(field2DC)-FloatConstants::Five;
            }
            if ((animationStage)>7 && (animationStage)<10 && y>FloatConstants::Zero) {
                if ((CheckHorizontalLimits() && (((x)<g_F699_SideEdgeAt00657884
                     && facing==1)
                    || ((x)>g_F699_SideEdgeAt00657884
                        && facing==-1)))
                    || (((field2D8)+FloatConstants::Five)>=x
                        && facing==1)
                    || (((field2DC)-FloatConstants::Five)<=x
                        && facing==-1)) {
                    ResetSecondaryCounter(10);
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount)) {
                if ((scriptCounterF00)<3-static_cast<int>(g_OptionsModeAt006714D0)) {
                    ++scriptCounterF00;
                    ResetSecondaryCounter(12);
                    break;
                }
                scriptCounterF00=0;
                if (g_OptionsModeAt006714D0==3) {
                    ResetPrimaryCounters(0x2DF);
                    break;
                }
                if (y>g_F715_DecisionHeightAt006593D0)
                    ResetPrimaryCounters(0x2DC);
                else
                    ResetPrimaryCounters(0x2DC);
                break;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                if (AbsFloatAt00412D90(x-opponent->x)
                    <g_F699_DistanceAt0065787C) {
                    if (RecordedRange(0,100)<50)
                        facing=1;
                    else
                        facing=-1;
                }
                PlaySound(5);
                SpawnAuxEffect(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
                SpawnAuxEffect(0x7E,x,
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
                velocityX=-20.0f;
                velocityY=20.0f;
                field05C=0.8f;
            }
            if ((animationStage)==10 && (animationFrame)==0)
                ResetSecondaryCounter(8);
            break;
        }
