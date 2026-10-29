// F620: complete native 44-instruction action0x5F in normal fighter
// giant Advance(), real per-owner action transitions and independent
// x87 direction tests. Case body is NOT a separately accepted function.
case 0x5F: {
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        SetNativeActionAt40FAC0(F620_FIRST_ACTION);
        if (I32(0x4E0)>0)
            SetNativeActionAt40FAC0(F620_SECOND_ACTION);
    }
    if (I16(0x62)==I16(0x70)-1) {
        if (*(&F32(0x44))>*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=-1;
        if (*(&F32(0x44))<*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=1;
    }
    break;
}
