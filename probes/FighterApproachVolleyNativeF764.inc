// F764: original 2FA full inner action C++ grammar in 00543210.
// Six genuine native predicate/borrowed-float corrections restore original
// 971-B/279-x86 geometry. Remaining 156 register operand bytes NONEXACT.
// F699: reconstruct entire original 00543210 action 0x2FA into normal C++.
// Native physical case 005509CC..00550D97, 279 x86 /971 CODE bytes.
// This is an internal case in a NONEXACT 58KB parent, not a standalone function.
        case 0x2FA: {
            if ((animationStage)==0 && (animationFrame)==0) {
                ResetAt453E20();
                field080=1;
                field07C=0;
                reinterpret_cast<unsigned char&>(field3AC)=0;
                reinterpret_cast<signed short&>(scriptCounterF00)=0;
            }
            if ((animationStage)<10 && y>g_ThresholdAt0065782C && (animationStage)>2) {
                velocityX=-30.0f;
                velocityY=velocityY-g_JumpGroundCorrectionAt00658058;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
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
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                if ((reinterpret_cast<signed short&>(scriptCounterF00))<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++reinterpret_cast<signed short&>(scriptCounterF00);
                    SetAuxActionAt40FB40(12);
                    break;
                }
                SetNativeActionAt40FAC0(0x2FB);
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
                PrepareActionAt453D40(5);
                SpawnAt453C80(0x7D,
                    float(facing*80)+(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
                SpawnMixedAt453C80(0x7E,reinterpret_cast<int&>(x),
                    (*(&y))+g_ContactProjectionAt00657888,
                    facing,1);
                velocityX=-20.0f;
                velocityY=17.5f;
                if (RandomBoundaryAt455580(0,100)<50)
                    velocityY=15.0f;
                field05C=0.8f;
            }
            if ((animationStage)==10 && (animationFrame)==0)
                SetAuxActionAt40FB40(8);
            break;
        }
