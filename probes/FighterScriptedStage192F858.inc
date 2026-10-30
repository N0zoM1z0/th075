// F858 native actual 0x192: 217B/64-x86/6 original PE field references.
// Original transition2, stage4 sprite320 and +0x314 3f, stage5 state flag.
// Complete game switch interior; independent original whole giant still nonexact.
case 0x192: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==4 && S16(0x64)==0) {
        F32(0x314)=3.0f;
        SpawnDirectedAt453A70(0x320,I32(0x44),I32(0x48),
           (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D40(0);
    }
    if (S16(0x62)==5 && S16(0x64)==0)
        I32(0x7C)=1;
    return;
}
