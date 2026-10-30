// F873 original game 1FC: full 253B/70x86 native case, physics before stage0.
// Real height global658350, stage6 owner counters & POS15, independent game entry.
// Enclosing whole giant remains nonexact; no split-case exact CODE.
case 0x1FC: {
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_F873GroundDropAt00658350;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (S16(0x62)==6 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0)
        POS=15.0f;
    return;
}
