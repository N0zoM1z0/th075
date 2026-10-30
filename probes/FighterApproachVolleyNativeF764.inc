// F764: original 2FA full inner action C++ grammar in 00543210.
// Six genuine native predicate/borrowed-float corrections restore original
// 971-B/279-x86 geometry. Remaining 156 register operand bytes NONEXACT.
// F699: reconstruct entire original 00543210 action 0x2FA into normal C++.
// Native physical case 005509CC..00550D97, 279 x86 /971 CODE bytes.
// This is an internal case in a NONEXACT 58KB parent, not a standalone function.
        case 0x2FA: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=1;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<10 && POS48>g_ThresholdAt0065782C && S16(0x62)>2) {
                POS=-30.0f;
                POS54=POS54-g_JumpGroundCorrectionAt00658058;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    ResetAt453E20();
                    SetNativeActionAt40FAC0(10);
                    POS48=0.0f;
                    break;
                }
            }
            if (S16(0x62)>9 && S16(0x62)<13 && !ContactAt454EE0()) {
                if (*reinterpret_cast<signed char*>(RAW+0x66)==1)
                    F32(0x44)=F32(0x2D8)+g_F699_SideOffsetAt00657874;
                if (*reinterpret_cast<signed char*>(RAW+0x66)==-1)
                    F32(0x44)=F32(0x2DC)-g_F699_SideOffsetAt00657874;
            }
            if (S16(0x62)>7 && S16(0x62)<10 && POS48>g_ThresholdAt0065782C) {
                if ((ContactAt454EE0() && ((F32(0x44)<g_F699_SideEdgeAt00657884
                     && *reinterpret_cast<signed char*>(RAW+0x66)==1)
                    || (F32(0x44)>g_F699_SideEdgeAt00657884
                        && *reinterpret_cast<signed char*>(RAW+0x66)==-1)))
                    || ((F32(0x2D8)+g_F699_SideOffsetAt00657874)>=reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && *reinterpret_cast<signed char*>(RAW+0x66)==1)
                    || ((F32(0x2DC)-g_F699_SideOffsetAt00657874)<reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44
                        && *reinterpret_cast<signed char*>(RAW+0x66)==-1)) {
                    SetAuxActionAt40FB40(10);
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70)) {
                if (S16(0xF00)<3-static_cast<int>(g_CloudOpponentAt006714D0)) {
                    ++S16(0xF00);
                    SetAuxActionAt40FB40(12);
                    break;
                }
                SetNativeActionAt40FAC0(0x2FB);
                break;
            }
            if (S16(0x62)==3 && S16(0x64)==0) {
                if (F699AbsAt00412D90(reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
                    <g_F699_DistanceAt0065787C) {
                    if (RandomBoundaryAt455580(0,100)<50)
                        *reinterpret_cast<signed char*>(RAW+0x66)=1;
                    else
                        *reinterpret_cast<signed char*>(RAW+0x66)=-1;
                }
                PrepareActionAt453D40(5);
                SpawnAt453C80(0x7D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnMixedAt453C80(0x7E,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                POS=-20.0f;
                POS54=17.5f;
                if (RandomBoundaryAt455580(0,100)<50)
                    POS54=15.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)==10 && S16(0x64)==0)
                SetAuxActionAt40FB40(8);
            break;
        }
