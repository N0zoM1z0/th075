// F893 original game action2DC 660B/188-x86: true ground contact and stage phases.
// Native stage2 sprite33B, stage13 sprite338 and once-only auxiliary2.
// Stage15 12.5/15.0 motion, stage24 aux22, true random0..30 on getter match.
// Entire original 46,755B fighter still NONEXACT, not a callable inner case.
case 0x2DC: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        I32(0x7C)=0;
        S16(0x80)=1;
        POS=10.0f;
        POS54=0.0f;
        SpawnDirectedAt453A70(0x33B,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(1);
    }
    if (S16(0x62)==13 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x338,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(1);
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_F893FloatFallAt00657478;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<24) {
        POS54=POS54-g_F893VerticalStageAt006598B0;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(24);
            POS=0.0f;
            POS54=0.0f;
            POS48=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(0,30);
    }
    if (S16(0x62)==13 && S16(0x64)==0 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(2);
    }
    if (S16(0x62)==15 && S16(0x64)==0) {
        POS=12.5f;
        POS54=15.0f;
        I32(0x7C)=0;
        S16(0x80)=1;
    }
    if (S16(0x62)==24 && S16(0x64)==0)
        SetAuxActionAt40FB40(22);
    return;
}
