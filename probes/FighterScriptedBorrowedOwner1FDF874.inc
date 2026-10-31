// F874 selected original owner pointer +0x2E8, two native calls and owner X/float Y.
// Native outer equality/inner range forms ONE real conditional with else zero.
// 1FD has true original 6B CMP ECX,149 not yet normal VC7.1-restored.
// Original whole giant NONEXACT, no inner-case callable exact credit.
case 0x1FD: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=0;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (S16(0x62)==2 && I32(0x7C)==1) {
        SpawnAt453C80(0x50,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_F872Volley1FAYAt00659310,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x66);
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->ResetAt453E20();
        *reinterpret_cast<float*>(OWNER+0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44);
        SetNativeActionAt40FAC0(0x1FF);
        return;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        if (*reinterpret_cast<float*>(OWNER+0x48)==g_ThresholdAt0065782C &&
           (*reinterpret_cast<signed short*>(OWNER+0x60)<0x32 ||
            *reinterpret_cast<signed short*>(OWNER+0x60)>0x95)) {
            S16(0x80)=1;
        } else {
            S16(0x80)=0;
        }
    }
    return;
}
