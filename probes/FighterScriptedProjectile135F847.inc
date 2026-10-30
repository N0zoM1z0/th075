// F847 selected Japanese original 0x135: 278B/82-x86, 7 native PE fields.
// Actual signed facing byte, original kind/stage and natural C++ source.
// Interior only, not independent original exact callable CODE.
case 0x135: {
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
        SetNativeActionAt40FAC0(0);
        S16(0xF00)=0;
    }
    if (S16(0x62)==7 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x339,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    if (S16(0x62)==7 && S16(0x64)==0)
        PrepareActionAt453D60(0x1D);
    return;
}
