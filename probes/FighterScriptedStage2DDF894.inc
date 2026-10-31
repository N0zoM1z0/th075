// F894 original 2DD physical native complete 535B/153x86, next physical handler 2E4.
// Stage3 truly used random0..6 FILD EBP-0x10C, stage18 sprite335 and stage26 aux24.
// This is an inner case, whole 46755B fighter NONEXACT and uncredited.
case 0x2DD: {
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
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<26) {
        POS54=POS54-g_F894VerticalStageAt00659090;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetAuxActionAt40FB40(26);
            POS=0.0f;
            POS54=0.0f;
            POS48=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=RandomBoundaryAt455580(0,60);
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        POS=float(RandomBoundaryAt455580(0,6))+g_F894RandomHeightAt006592A0;
        POS54=16.0f;
        I32(0x7C)=0;
        S16(0x80)=1;
    }
    if (S16(0x62)==18 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x335,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(4);
    }
    if (S16(0x62)==26 && S16(0x64)==0)
        SetAuxActionAt40FB40(24);
    return;
}
