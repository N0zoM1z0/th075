// F856 selected actor original 190: 217B/64 x86/six native PE fields.
// Stage3 actual sprite320, animationFA, prepare0; stage4 state bit.
// Normal C++ whole original game interior, source GPR not exact.
case 0x190: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        F32(0x314)=1.0f;
        SpawnDirectedAt453A70(0x320,I32(0x44),I32(0x48),
           (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D40(0);
    }
    if (S16(0x62)==4 && S16(0x64)==0)
        I32(0x7C)=1;
    return;
}
