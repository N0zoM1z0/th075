// F619: real original 64-instruction native second-switch 0x5D/0x5E
// air transition cases in fighter005AEEC0; entirely different native
// source grammar from 101-instruction F617 owners. These remain inner
// parts of a NONEXACT whole original giant function, not standalone.
case F619_CASE: {
    if (I16(0x62)==2 && I16(0x64)==0)
        POS=F619_START_POS;
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        SetNativeActionAt40FAC0(0);
        if (I32(0x4E0)>0)
            SetNativeActionAt40FAC0(1);
    }
    if (I16(0x62)==I16(0x70)-1) {
        if (*(&F32(0x44))>*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=-1;
        if (*(&F32(0x44))<*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=1;
    }
    if (I16(0x62)==14 && I16(0x64)==0)
        POS=0.0f;
    break;
}
