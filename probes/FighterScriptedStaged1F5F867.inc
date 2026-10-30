// F867 original native 1F5 628B/195x86/17 physically correct PE fields.
// Original stage1/2/13/14/15/24 separate checks, native char fourth parameter.
// Native lower height comparator global 657480, not apparent equivalent 65782C.
// Full enclosing fighter still GPR and final JMP nonexact.
case 0x1F5: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_F866DropAt006583FC;
        if (POS<g_StopThresholdAt00657480)
            POS=2.0f;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0x18);
            POS48=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==1 && S16(0x64)==0) {
        POS=9.5f;
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x33B,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(1);
    }
    if (S16(0x62)==0xD && S16(0x64)==0) {
        SpawnDirectedAt453A70(0x338,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(1);
    }
    if (S16(0x62)==0xE && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (S16(0x62)==0xF && S16(0x64)==0) {
        POS=10.0f;
        POS54=15.0f;
        POS5C=0.65f;
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==0x18 && S16(0x64)==0)
        SetAuxActionAt40FB40(0x16);
    return;
}
