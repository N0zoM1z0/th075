// F993 native Japanese original TH075 004AC040 25F and 260.
 // Both real original handlers 466B/114 x86, nine genuine PE
 // external fields per case. Source ten-iteration int loop
 // with native 30-shot*6 angle, sprite 0x346 vs 0x347,
 // signed facing*49 and float Y global00659294.
 // ENTIRE PARTIAL father source naturally reproduces ALL 228
 // original positional mnemonics, widths AND GPR roles.
 // Original saved-this EBP−0x64 and full 0x720 stack
 // frame still differ; no complete original callable exactness.
// F993 original Japanese fighter 004AC040 action 0x25F 10-shot loop.
case 0x25F: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    --S16(0xF00);
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0 && S16(0xF00)<=0 && S16(0xF02)<1) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            F32(0x314)=float(30-shot*6);
            F32(0x318)=15.0f;
            SpawnFloatXYAt453A70(0x346,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
                (*(&POS48))+g_F968_RoundY190At00659294,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
        }
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        S16(0xF00)=2;
        ++S16(0xF02);
    }
    break;
}
// F993 original Japanese fighter 004AC040 action 0x260 10-shot loop.
case 0x260: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    --S16(0xF00);
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0 && S16(0xF00)<=0 && S16(0xF02)<1) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            F32(0x314)=float(30-shot*6);
            F32(0x318)=15.0f;
            SpawnFloatXYAt453A70(0x347,
                float((*reinterpret_cast<signed char*>(RAW+0x66))*49)+F32(0x44),
                (*(&POS48))+g_F968_RoundY190At00659294,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
        }
        POS=float(S16(0xF00))*g_F747_BounceYAt00658044;
        POS54=float(S16(0xF02))*g_F747_BounceYAt00658044;
        S16(0xF00)=2;
        ++S16(0xF02);
    }
    break;
}
