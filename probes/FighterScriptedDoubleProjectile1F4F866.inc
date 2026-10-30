// F866 actual original 1F4 full 448B/136-x86/14 original PE fields.
// Genuine native narrow fourth argument at 00453C80 makes MOV r8, not MOVSX r32.
// Two physical stage4 projectile conditions; original whole giant still nonexact.
case 0x1F4: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_F866DropAt006583FC;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            POS48=0.0f;
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x338,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    if (S16(0x62)==4 && S16(0x64)==0) {
        PrepareActionAt453D40(1);
        POS=8.0f;
        POS54=9.5f;
        POS5C=0.65f;
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==0xD && S16(0x64)==0)
        SetAuxActionAt40FB40(0xB);
    return;
}
