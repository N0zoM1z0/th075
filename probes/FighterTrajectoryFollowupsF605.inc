// F605: native second packed-switch actions 0x47 and 0x48 in large
// original fighter Advance() functions. These are NOT independent
// function credits; owner-specific spawn variants differ.
case 0x47: {
    // Original copying +0x98 to +0x54 is MOV dword, not FLD/FSTP.
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 0.8f;
        I32(0x7C) = 0;
    }
    if (I16(0x62)==F605_STAGE47 && POS54 < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F605_EARLY47);
        break;
    }
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F605_COUNTER) = static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F605_COUNTER+2) = static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48 = 0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetAuxActionAt40FB40(F605_LATE47);
    break;
}
case 0x48: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 1.3f;
        I32(0x7C) = 0;
    }
    if (I16(0x62)==F605_STAGE48 && POS54 < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F605_EARLY48);
        break;
    }
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F605_COUNTER) = static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F605_COUNTER+2) = static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48 = 0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetAuxActionAt40FB40(F605_LATE48);
    break;
}
