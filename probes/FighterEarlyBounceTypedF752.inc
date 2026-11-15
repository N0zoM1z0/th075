// F752: actual original 05D/05E borrowed actor and opponent X at +0x44.
// The type is ONLY an observed borrowed memory view: never instantiated.
// Both typed floating members restore native VC7.1 direct FCOMP memory
// instead of the two nonoriginal FLD/FCOMPP sequences from raw casts.
struct FighterBorrowedXViewF752 {
    unsigned int observedRealOwnerWordsBeforeX[17];
    float xAt44;
};
typedef char FighterBorrowedXViewSizeF752[(sizeof(FighterBorrowedXViewF752)==0x48)?1:-1];
// F747: true complete original 059/05D/05E normal C++ action interiors
// in ONE 58KB fighter 00543210 giant parent. No independent CODE credit.
// Native original 059 00545109..0054526D 356 B /95 x86;
// 05D 0054526D..005453BE 337 B/101 x86;
// 05E 005453BE..0054550F 337 B/101 x86.
        case 0x59: {
            if ((reinterpret_cast<signed short&>(animationStage))>1) {
                rotationZ=(rotationZ)+g_F728_RandomOffsetYAt00657858;
                velocityY=velocityY-field05C;
                if (velocityY+y<=g_ThresholdAt0065782C) {
                    reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
                    reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((*(&velocityY))*g_ContactProjectionAt00657888);
                    ResetAt453E20();
                    y=0.0f;
                    SetNativeActionAt40FAC0(0x61);
                    rotationZ=0.0f;
                    InitTrajectoryAt453E60(2.0f);
                    ResetMotionAt40FC50();
                    PrepareActionAt453D60(0x16);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
                SetAuxActionAt40FB40(2);
            else if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityX=static_cast<float>(static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF00)))*g_F747_BounceXAt006590BC;
                velocityY=static_cast<float>(-static_cast<int>(reinterpret_cast<signed short&>(scriptCounterF02)))*g_F747_BounceYAt00658044;
                field05C=0.7f;
                SetMotionStateAt40FBB0(0,95.0f,0);
            }
            break;
        }
        case 0x5D: {
            if ((reinterpret_cast<signed short&>(animationStage))<8 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(8);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                if (inputY>0)
                    SetNativeActionAt40FAC0(1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==(reinterpret_cast<signed short&>(field070))-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44>reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44<reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=1;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=8.0f;
                velocityX=15.5f;
                field05C=0.75f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0)
                SetAuxActionAt40FB40(6);
            break;
        }
        case 0x5E: {
            if ((reinterpret_cast<signed short&>(animationStage))<8 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(8);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
                SetNativeActionAt40FAC0(0);
                if (inputY>0)
                    SetNativeActionAt40FAC0(1);
            }
            if ((reinterpret_cast<signed short&>(animationStage))==(reinterpret_cast<signed short&>(field070))-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44>reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44<reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=1;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
                velocityY=8.0f;
                velocityX=-15.5f;
                field05C=0.75f;
            }
            if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0)
                SetAuxActionAt40FB40(6);
            break;
        }
