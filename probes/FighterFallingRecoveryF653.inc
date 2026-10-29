// Original fighter 00543210 falling-recovery handlers 0x12C..0x12E.
// This is one native switch case in the still-NONEXACT whole Advance().
// The F653_* parameters reflect the three distinct original action states.
case F653_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(F653_NEXT_ACTION);
#if F653_CLEAR_F00
        S16(0xF00)=0;
#endif
    }
    if (S16(0x62)==F653_PREPARE_FRAME && S16(0x64)==0)
        PrepareActionAt453D60(F653_PREPARE_ANIM);
    break;
}
