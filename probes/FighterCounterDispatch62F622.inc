// F622 actual original packed action 0x62: collision counter capture and
// dispatch to three action states, in one entire incomplete fighter
// Advance() C++ TU. No whole function or subrange credit.
case 0x62: {
#if F622_CHECK_DIRECTION
    if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
        // The original PE has JA *into* the store for each of the
        // first three uint fields and JBE *around* it on the fourth.
        // This is a four-way OR, not three-zero AND one-positive.
        if (*reinterpret_cast<unsigned int*>(RAW+0x4E8)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4EC)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F0)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F4)>0)
            I16(F622_COUNTER)=1;
    }
    if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)<0) {
        // The original PE has JA *into* the store for each of the
        // first three uint fields and JBE *around* it on the fourth.
        // This is a four-way OR, not three-zero AND one-positive.
        if (*reinterpret_cast<unsigned int*>(RAW+0x4E8)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4EC)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F0)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F4)>0)
            I16(F622_COUNTER)=2;
    }
#endif
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        SetNativeActionAt40FAC0(0x5F);
        if (I16(F622_COUNTER)==1)
            SetNativeActionAt40FAC0(0x5D);
        if (I16(F622_COUNTER)==2)
            SetNativeActionAt40FAC0(0x5E);
    }
    break;
}
