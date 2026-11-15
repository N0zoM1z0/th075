// F762: genuine original 1F6 and 1F7 with authentic split Contact guard
// and observed actor +0x44 float member. Whole parent remains NONEXACT.
// F729: one of two complete original physical 00543210 return-bounce
// stages (1F6/1F7), instantiated twice with genuinely used values.
// 1F6: native 0054AB00..0054AF9D, 1181 CODE B /348 x86.
// 1F7: native 0054AF9D..0054B43A, 1181 CODE B /348 x86.
// First side-edge strict `<` recovers original TEST AH,5/JP. Third/
// fourth comparisons currently still naturally compile FLD/FCOMPP
// instead of native FCOMP [this+0x44]; NO byte-exact claim.
// All native stack/branch/physical fields must be proven in whole parent.
        case F729_CASE: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ResetAt453E20();
                field080=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
            }
            if ((animationStage)<11 && y>g_ThresholdAt0065782C && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-g_ApproachAt00658058;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetAuxActionAt40FB40(15);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>10 && (animationStage)<14 && !ContactAt454EE0()) {
                if (facing==1)
                    x=(field2D8)+g_F699_SideOffsetAt00657874;
                if (facing==-1)
                    x=(field2DC)-g_F699_SideOffsetAt00657874;
            }
            if ((animationStage)>8 && (animationStage)<11
                && y>g_ThresholdAt0065782C) {
                if ((ContactAt454EE0() && (((x)<g_F699_SideEdgeAt00657884
                        && facing==1)
                    || ((x)>g_F699_SideEdgeAt00657884
                        && facing==-1)))
                    || (((field2D8)+g_F699_SideOffsetAt00657874)>=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==1)
                    || (((field2DC)-g_F699_SideOffsetAt00657874)<=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && facing==-1)) {
                    SetAuxActionAt40FB40(11);
                    ResetAt453E20();
                    break;
                }
            }
            if ((animationStage)==14 || (animationStage)==15) {
                if (field07C!=0 && field07C!=3 && field07C!=1) {
                    SetNativeActionAt40FAC0(0x1FA);
                    break;
                }
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    velocityY=0.0f;
                    velocityX=(velocityX)*g_F728_PositiveDragAt006583FC;
                    SetAuxActionAt40FB40(16);
                    y=0.0f;
                    break;
                }
            }
            if ((animationStage)>15) {
                velocityX=(velocityX)-g_NewDragAt006581E0;
                if ((velocityX)<g_ThresholdAt0065782C)
                    velocityX=0.0f;
            }
            if (GetNativeActionAt40FA30()==(field070))
                SetNativeActionAt40FAC0(0);
            if ((animationStage)==3 && (animationFrame)==0) {
                PrepareActionAt453D40(5);
                SpawnAt453C80(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    -facing,1);
                SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    -facing,1);
                velocityX=-20.0f;
                velocityY=20.0f;
                if (y>g_ThresholdAt0065782C)
                    velocityY=8.0f;
                field05C=0.8f;
            }
            if ((animationStage)==14 && (animationFrame)==0) {
                PrepareActionAt453D40(6);
                velocityX=F729_STAGE14_X;
                velocityY=F729_STAGE14_Y;
            }
            if ((animationStage)==15 && (animationFrame)==0)
                SpawnDirectedAt453A70(F729_STAGE15_SHOT,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
                    facing,1);
            if ((animationStage)==18 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))==0)
                SetAuxActionAt40FB40(19);
            if ((animationStage)==11 && (animationFrame)==0)
                SetAuxActionAt40FB40(9);
            break;
        }
