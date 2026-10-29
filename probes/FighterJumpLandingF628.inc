// F628 original complete indexed actions 0x8C/0x8F/0x90: native
// fighter landing with true x87 ground boundary, 0x490 reflection,
// and stage3 animation counter. These are inner CASE bodies only;
// the original enclosing giant fighter Advance() remains NONEXACT.
case F628_CASE: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS=F628_START_POS;
        POS54=0.0f;
        I32(0x7C)=0;
        I16(F628_COUNTER)=0;
    }
    if (POS<g_ThresholdAt0065782C) {
        POS=POS+g_JumpGroundCorrectionAt00658058;
        if (POS>g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (ContactAt454EE0() && *reinterpret_cast<signed char*>(RAW+0x3BE))
        F32(0x490)=POS*g_JumpReflectionAt006583E8;
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetNativeActionAt40FAC0(0);
    if (I16(0x62)==3 && I16(0x64)==0 && I16(F628_COUNTER)<F628_LIMIT) {
        ++I16(F628_COUNTER);
        SetAuxActionAt40FB40(1);
    }
    break;
}
