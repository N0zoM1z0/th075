// F829 actual native B4/B5 215B/60x86/8 physical PE fields, void-source direct original parent epilogue exits. Interior only.
// F645 genuine original native B4/B5 motion restart and ground
// threshold transition. This is inside a giant fighter Advance()
// whole source TU that remains NONEXACT, not a callable leaf.
case F645_CASE: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        ResetAt453E20();
        POS=F645_START_POS;
        POS54=12.5f;
        POS5C=0.75f;
        I32(0x30)=0;
        ResetMotionAt40FC50();
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(0xA);
            POS48=0.0f;
            ResetAt453E20();
            return;
        }
    }
    if (GetNativeActionAt40FA30()==I16(0x70)) {
        SetAuxActionAt40FB40(F645_AUX_ACTION);
        return;
    }
    return;
}
