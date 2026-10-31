// F975 native Japanese TH075 original 004AC040 action19D/E/F.
 // 19D=400B/97x86/7 real PE fields; 19E=475B/128x86/12 PE;
 // 19F=478B/128x86/12 PE. Ordinary normal VC7.1 source reproduces
 // all 353 true native mnemonic and width positions, with 65/84/84
 // original GPR role differences. Original 19D has FIADD integer Y
 // and one native 0x326 shot; original 19E/F scale X/Y motion and
 // use genuine signed-short negative angle grammar (19E 0−4*F02,
 // 19F −45−4*F02), keeping real native x87 word conversions.
 // This is ONLY internal game state source in NONEXACT 82KB father.
// F975 true original Japanese 004AC040 19D stage, 400B/97 native x86.
case 0x19D: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>5 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(S16(0xF02)*4+55);
        F32(0x318)=15.0f;
        SpawnFloatXYAt453A70(0x326,
            float((47-S16(0xF02)*10)*(*reinterpret_cast<signed char*>(RAW+0x66)))+F32(0x44),
            (*(&POS48))+g_F969_RoundY192At00658264+S16(0xF02)*20,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    break;
}
// F975 true original Japanese 004AC040 19E, float-scaled single native shot.
case 0x19E: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(0-S16(0xF02)*4);
        F32(0x318)=15.0f;
        SpawnWithFloatAt453A70(0x326,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        POS48=0.0f;
        ResetAt453E20();
        SetNativeActionAt40FAC0(0xA);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x335,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    break;
}
// F975 true original Japanese 004AC040 19E, float-scaled single native shot.
case 0x19F: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
    }
    if (S16(0x62)>4 && S16(0xF00)<=0 && S16(0xF02)<5) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x28);
        F32(0x314)=float(-45-S16(0xF02)*4);
        F32(0x318)=15.0f;
        SpawnWithFloatAt453A70(0x326,I32(0x44),
            (*(&POS48))+g_F970_YAt006590AC,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        S16(0xF00)=2;
        ++S16(0xF02);
        --S16(0xF00);
    }
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        POS48=0.0f;
        ResetAt453E20();
        SetNativeActionAt40FAC0(0xA);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0)
        SpawnDirectedAt453A70(0x335,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    break;
}
