// F958: consecutive real native Japanese 004AC040 stages 12C/12D.
 // 12C physically 004B1039..004B1108 (207B/59x86/6 PE fields);
 // 12D physically 004B1108..004B11E3 (219B/61x86/6 PE fields).
 // True 12C is contiguous after D2 but has NO standalone afterRET
 // DIR32 table entry: source must be verified through the real D2
 // terminal and mapped 12D successor, not a fabricated jump label.
 // Only inner source in a NONEXACT 82KB original fighter father.
// Natural native 004AC040 12C original game state, source probe.
case 0x12C: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0)
        PrepareActionAt453D60(0x1B);
    break;
}
// Natural native 004AC040 12D original game state, source probe.
case 0x12D: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    S16(0xF00)=0;
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    break;
}
