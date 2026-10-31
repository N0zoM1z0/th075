// F875 native original 1FF complete real stage1..6 associated owner action.
// Five actual native FILD scratch slots; original owner+0x44 x87 updates.
// Enclosing 46755B whole fighter still not exact; no inner exact credit.
case 0x1FF: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=0;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==1 && S16(0x64)==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x64);
        *reinterpret_cast<float*>(OWNER+0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*74)+F32(0x44);
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x64);
        *reinterpret_cast<float*>(OWNER+0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*40)+F32(0x44);
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x64);
        *reinterpret_cast<float*>(OWNER+0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*36)+F32(0x44);
    }
    if (S16(0x62)==4 && S16(0x64)==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x64);
        *reinterpret_cast<float*>(OWNER+0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*33)+F32(0x44);
    }
    if (S16(0x62)==5 && S16(0x64)==0) {
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x64);
        *reinterpret_cast<float*>(OWNER+0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*32)+F32(0x44);
    }
    if (S16(0x62)==6 && S16(0x64)==0)
        reinterpret_cast<FighterBorrowedOwnerF874*>(OWNER)->SetNativeActionAt40FAC0(0x35);
    return;
}
