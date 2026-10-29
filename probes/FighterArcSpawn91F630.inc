// F630 actual native 105-instruction action0x91 in two special giant
// fighter C++ sources. This 27-instruction stage-one projectile path
// is absent from original regular 78-instruction F629 actors.
// A full parent Advance() remains NONEXACT; this is not a new function.
case 0x91: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS=-10.0f;
        POS54=14.0f;
        POS5C=0.5f;
        I32(0x7C)=0;
    }
    if (I16(0x62)==1 && I16(0x64)==0 && I16(0xF0C)==0) {
        I16(0xF0C)=1;
        SpawnDirectedAt453A70(F630_PROJECTILE, I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),F630_SIDE);
    }
    if (I16(0x62)==F630_STAGE && POS54<g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F630_EARLY);
        break;
    }
    POS54=POS54-POS5C;
    if (POS54+POS48<=g_ThresholdAt0065782C) {
        I16(F630_COUNTER)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        I16(F630_COUNTER+2)=static_cast<short>((POS54)*g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(F630_LATE);
    break;
}
