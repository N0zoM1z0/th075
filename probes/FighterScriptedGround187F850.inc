// F850 current original native actor 0x187 natural falling/animation source.
// Entire original game case, not an independent callable function.
case 0x187: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=12.5f;
    }
    if (S16(0x62)>0) {
        POS=POS-g_AdditionalGravityAt00659090;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        PrepareActionAt453D60(0x1C);

    }
    return;
}
