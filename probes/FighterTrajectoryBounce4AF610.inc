// F610 original native fighter second-switch action 0x4A inside whole
// incomplete giant Advance() C++ source; not an independent function.
case 0x4A: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 0.8f;
        I32(0x7C) = 0;
    }
    if (I16(0x62)==F610_STAGE && POS54 < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F610_EARLY);
        break;
    }
    if (ContactAt454EE0() && POS <= g_BounceThresholdAt006590C0) {
        SetNativeActionAt40FAC0(0x4C);
        POS = -POS * g_BounceScaleAt00657F74;
        POS54 = 15.0f;
        POS5C = 0.5f;
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        I16(F610_COUNTER) = 0;
        break;
    }
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
#if F610_PREPARE_BEFORE
        PrepareActionAt453D60(0x16);
#endif
        I16(F610_COUNTER)=static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F610_COUNTER+2)=static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
#if !F610_PREPARE_BEFORE
        PrepareActionAt453D60(0x16);
#endif
        break;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(F610_LATE);
    break;
}
