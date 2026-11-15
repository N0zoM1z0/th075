// F939: original 004AC040 two native 337B/101 x86 adjacent stage actions, actor-specific stage/camera/aux thresholds, whole father NONEXACT.
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
        case 0x5D: {
            if ((animationStage)<12 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(12);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0);
                if (inputY>0)
                    SetNativeActionAt40FAC0(1);
            }
            if ((animationStage)==(field070)-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44>reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44<reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=1;
            }
            if ((animationStage)==4 && (animationFrame)==0) {
                velocityY=8.0f;
                velocityX=12.5f;
                field05C=0.7f;
            }
            if ((animationStage)==12 && (animationFrame)==0)
                SetAuxActionAt40FB40(10);
            break;
        }
        case 0x5E: {
            if ((animationStage)<9 && y>g_ThresholdAt0065782C) {
                velocityY=velocityY-field05C;
                if (y+velocityY<=g_ThresholdAt0065782C) {
                    y=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(9);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==(field070)) {
                SetNativeActionAt40FAC0(0);
                if (inputY>0)
                    SetNativeActionAt40FAC0(1);
            }
            if ((animationStage)==(field070)-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44>reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44<reinterpret_cast<const FighterBorrowedXViewF752*>(opponent)->xAt44)
                    facing=1;
            }
            if ((animationStage)==6 && (animationFrame)==0) {
                velocityY=8.0f;
                velocityX=-12.5f;
                field05C=0.7f;
            }
            if ((animationStage)==9 && (animationFrame)==0)
                SetAuxActionAt40FB40(8);
            break;
        }
