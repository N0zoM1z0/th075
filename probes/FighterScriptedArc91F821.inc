// F821: selected original native action91, 288B/78 x86 and
// twelve actual PE calls/globals, 005214B0 whole original fighter.
// Void function original case branches exit to native parent epilogue.
// These original source cases are NOT independent exact callable game units.
// F629: genuine complete original native action0x91 arc trajectory,
// inside a huge incomplete fighter Advance(). Game case evidence,
// not an independent original CODE function or accepted match unit.
case 0x91: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS=-10.0f;
        POS54=14.0f;
        POS5C=0.5f;
        I32(0x7C)=0;
    }
    if (I16(0x62)==F629_STAGE && POS54<g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F629_EARLY);
        return;
    }
    POS54=POS54-POS5C;
    if (POS54+POS48<=g_ThresholdAt0065782C) {
        I16(F629_COUNTER)=static_cast<short>(POS*g_ContactProjectionAt00657888);
        I16(F629_COUNTER+2)=static_cast<short>((POS54)*g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48=0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        return;
    }
    if (GetNativeActionAt40FA30()==I16(0x70))
        SetAuxActionAt40FB40(F629_LATE);
    return;
}
