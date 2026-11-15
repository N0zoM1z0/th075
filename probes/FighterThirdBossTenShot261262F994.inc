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
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
    }
    if ((animationStage)>4)
        velocityY=velocityY-field05C;
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=-3.0f;
        velocityY=9.0f;
        field05C=0.7f;
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            field314=float(30-shot*6);
            field318=15.0f;
            SpawnWithFloatAt453A70(0x346,reinterpret_cast<int&>(x),
                (*(&y))+g_F970_YAt006590AC,facing,1);
        }
    }
    break;
}
// F994 original Japanese 004AC040 action0x262 ten real sprite calls
case 0x262: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        velocityX=(velocityX)*g_F972_GravityAt00657F74;
        velocityY=(velocityY)*g_F972_GravityAt00657F74;
    }
    if ((animationStage)>4)
        velocityY=velocityY-field05C;
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==4 && (animationFrame)==0) {
        velocityX=-3.0f;
        velocityY=9.0f;
        field05C=0.7f;
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            field314=float(30-shot*6);
            field318=15.0f;
            SpawnWithFloatAt453A70(0x347,reinterpret_cast<int&>(x),
                (*(&y))+g_F970_YAt006590AC,facing,1);
        }
    }
    break;
}
