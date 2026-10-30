// F852 selected game original 189, 381 B/107 x86/11 physically typed PE fields.
// Genuine x87 FUCOMPP equality and POS48+POS54 ground test, state7
// reflected velocity, stage3 POS15, speed8.5/0.85. Source GPR phase
// still has genuine nonrelocation mismatches; no standalone exact credit.
case 0x189: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=12.5f;
        POS5C=0.0f;
    }
    if (*(&POS48)==g_ThresholdAt0065782C) {
        POS=POS-g_AnimationDeltaAt0065747C;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<7) {
        POS54=POS54-POS5C;
        if (POS48+POS54<g_ThresholdAt0065782C) {
            POS48=0.0f;
            POS=POS*g_F852GroundBounceMultiplierAt00657478;
            SetAuxActionAt40FB40(7);
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=15.0f;
        POS54=8.5f;
        POS5C=0.85f;
        PrepareActionAt453D60(0x1D);
    }
    return;
}
