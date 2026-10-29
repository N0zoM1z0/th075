// F613 real native second indexed-switch recovery action0x4C within giant
// fighter Advance(). Original whole giant is still NONEXACT; case alone
// is not independently callable source CODE and has separate jump DATA.
case 0x4C: {
    if (I16(F613_COUNTER)==0) {
        ++I16(F613_COUNTER);
        SetMotionStateAt40FBB0(0,95.0f,0);
    }
    // Original PE executes this global angle advance on *every* frame,
    // even when the once-only F613_COUNTER initialization is skipped.
    F32(0x30) = F32(0x30) + g_AngleShiftAt00657878;
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        PrepareActionAt453D60(0x16);
        I16(F613_COUNTER) = static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F613_COUNTER+2) = static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48 = 0.0f;
        SetNativeActionAt40FAC0(0x61);
        F32(0x30)=0.0f;
        InitTrajectoryAt453E60(2.0f);
        ResetMotionAt40FC50();
        break;
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetAuxActionAt40FB40(0);
    break;
}
