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
            if (S16(0x62)<12 && POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(12);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                if (I32(0x4E0)>0)
                    SetNativeActionAt40FAC0(1);
            }
            if (S16(0x62)==S16(0x70)-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44>reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44<reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    *reinterpret_cast<signed char*>(RAW+0x66)=1;
            }
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=8.0f;
                POS=12.5f;
                POS5C=0.7f;
            }
            if (S16(0x62)==12 && S16(0x64)==0)
                SetAuxActionAt40FB40(10);
            break;
        }
        case 0x5E: {
            if (S16(0x62)<9 && POS48>g_ThresholdAt0065782C) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    POS48=0.0f;
                    ResetAt453E20();
                    SetAuxActionAt40FB40(9);
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                SetNativeActionAt40FAC0(0);
                if (I32(0x4E0)>0)
                    SetNativeActionAt40FAC0(1);
            }
            if (S16(0x62)==S16(0x70)-1) {
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44>reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44<reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    *reinterpret_cast<signed char*>(RAW+0x66)=1;
            }
            if (S16(0x62)==6 && S16(0x64)==0) {
                POS54=8.0f;
                POS=-12.5f;
                POS5C=0.7f;
            }
            if (S16(0x62)==9 && S16(0x64)==0)
                SetAuxActionAt40FB40(8);
            break;
        }
