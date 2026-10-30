// F868 actual original 1F6: 372B/111-x86/12 real typed PE fields.
// Special U8 this+511 equals20, stage 8..10 triggers native 455B30 and exits.
// Stage5 float X/bitwise Y sprite80 and second sprite336, Prepare2.
// Full original enclosing fighter NONEXACT; no split-case CODE credit.
case 0x1F6: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_SubtractAt00657478;
        if (POS<g_ThresholdAt0065782C)
            POS=0.0f;
    }
    if (S16(0x62)>7 && S16(0x62)<0xB && U8(0x511)==0x14) {
        SetNativeActionAt40FAC0(0x1F7);
        ResetAt453E20();
        NativeGameEffectAt455B30();
        return;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=14.0f;
        SpawnFloatXRawYAt453C80(0x80,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*100)+F32(0x44),
            I32(0x48),(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnDirectedAt453A70(0x336,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D40(2);
    }
    return;
}
