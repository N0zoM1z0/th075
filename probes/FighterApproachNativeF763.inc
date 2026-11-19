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
                reinterpret_cast<unsigned char&>(field3AC)=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)<10 && y>g_ThresholdAt0065782C && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-g_JumpGroundCorrectionAt00658058;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ClearMotionFields();
                    SetNativeActionAt40FAC0(10);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>9 && (animationStage)<13 && !ContactAt454EE0()) {
                if (facing==1)
                    x=(field2D8)+g_F699_SideOffsetAt00657874;
                if (facing==-1)
                    x=(field2DC)-g_F699_SideOffsetAt00657874;
            }
            if ((animationStage)>7 && (animationStage)<10 && y>g_ThresholdAt0065782C) {
                if ((ContactAt454EE0() && (((x)<g_F699_SideEdgeAt00657884
                     && facing==1)
                    || ((x)>g_F699_SideEdgeAt00657884
                        && facing==-1)))
                    || (((field2D8)+g_F699_SideOffsetAt00657874)>=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==1)
                    || (((field2DC)-g_F699_SideOffsetAt00657874)<=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==-1)) {
                    SetAuxActionAt40FB40(10);
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(field070)) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    SetAuxActionAt40FB40(12);
                    break;
                }
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
                if (g_CloudOpponentAt006714D0==3) {
                    SetNativeActionAt40FAC0(0x2DF);
                    break;
                }
                if (y>g_F715_DecisionHeightAt006593D0)
                    SetNativeActionAt40FAC0(0x2DC);
                else
                    SetNativeActionAt40FAC0(0x2DC);
                break;
            }
            if ((animationStage)==3 && (animationFrame)==0) {
                if (F699AbsAt00412D90(reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    <g_F699_DistanceAt0065787C) {
                    if (RandomBoundaryAt455580(0,100)<50)
                        facing=1;
                    else
                        facing=-1;
                }
                PlaySound(5);
                SpawnAt453C80(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
                SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
                velocityX=-20.0f;
                velocityY=20.0f;
                field05C=0.8f;
            }
            if ((animationStage)==10 && (animationFrame)==0)
                SetAuxActionAt40FB40(8);
            break;
        }
