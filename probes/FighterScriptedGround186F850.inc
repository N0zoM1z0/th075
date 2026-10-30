// F850 current original native actor 0x186 natural falling/animation source.
// Entire original game case, not an independent callable function.
case 0x186: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=12.5f;
    }
    if (S16(0x62)>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        PrepareActionAt453D60(0x1D);
        SpawnDirectedAt453A70(0x341,I32(0x44),I32(0x48),(*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    return;
}
