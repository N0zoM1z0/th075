// F994 pinned original Japanese 004AC040 true 261/262 actions.
 // Original each 361B/98 x86, eight actual typed PE fields.
 // These ten-shot loops have real signed stage4 motion, native
 // 0x657F74 float velocity scale at stage0 (without ResetAt453E20),
 // shot0x346 or 0x347, raw X integer plus float Y global006590AC.
 // Full PARTIAL normal VC7.1 giant emits identical native 196
 // positional mnemonics, widths, GPR operand roles. Original 82KB
 // whole saved receiver/frame and original PE locations still differ;
 // never claim complete original CODE exactness from internal cases.
// F994 original Japanese 004AC040 action0x261 ten real sprite calls
case 0x261: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
    }
    if (S16(0x62)>4)
        POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=-3.0f;
        POS54=9.0f;
        POS5C=0.7f;
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            F32(0x314)=float(30-shot*6);
            F32(0x318)=15.0f;
            SpawnWithFloatAt453A70(0x346,I32(0x44),
                (*(&POS48))+g_F970_YAt006590AC,*reinterpret_cast<signed char*>(RAW+0x66),1);
        }
    }
    break;
}
// F994 original Japanese 004AC040 action0x262 ten real sprite calls
case 0x262: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1;
        S16(0xF00)=0;
        S16(0xF02)=0;
        POS=POS*g_F972_GravityAt00657F74;
        F32(0x54)=F32(0x54)*g_F972_GravityAt00657F74;
    }
    if (S16(0x62)>4)
        POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=-3.0f;
        POS54=9.0f;
        POS5C=0.7f;
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            F32(0x314)=float(30-shot*6);
            F32(0x318)=15.0f;
            SpawnWithFloatAt453A70(0x347,I32(0x44),
                (*(&POS48))+g_F970_YAt006590AC,*reinterpret_cast<signed char*>(RAW+0x66),1);
        }
    }
    break;
}
