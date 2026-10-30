// F859 current Japanese original 194 full interior 297B/86x86/7 physical fields.
// IMPORTANT: no stage0 ResetAt453E20 call, unlike sibling source 192.
// Actual ground motion/early stateA, stage5 2f sprite320, stage6 state flag.
// Current whole giant remains register/JMP NONEXACT.
case 0x194: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        POS48=0.0f;
        POS5C=0.0f;
        POS54=0.0f;
        return;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        F32(0x314)=2.0f;
        SpawnDirectedAt453A70(0x320,I32(0x44),I32(0x48),
           (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D40(0);
    }
    if (S16(0x62)==6 && S16(0x64)==0)
        I32(0x7C)=1;
    return;
}
