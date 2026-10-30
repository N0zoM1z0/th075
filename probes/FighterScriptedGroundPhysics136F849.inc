// F849 genuine original 0x136 ground/extra-fall and sprite0x33A.
// Full 321B/95 x86/10 native typed PE fields. Current parent has
// 15 real stage5 GPR operand negatives and two entire-parent JMP bytes.
// Not byte exact or independently callable original CODE.
case 0x136: {
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
    if (S16(0x62)>2 && POS>g_ThresholdAt0065782C) {
        POS=POS-g_AnimationDeltaAt0065747C;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x33A,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(0x1D);
    }
    return;
}
