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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<1) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            field314=float(30-shot*6);
            field318=15.0f;
            SpawnFloatXYAt453A70(0x346,
                float((facing)*49)+(x),
                (*(&y))+g_F968_RoundY190At00659294,
                facing,1);
        }
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    break;
}
// F993 original Japanese fighter 004AC040 action 0x260 10-shot loop.
case 0x260: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
    }
    --reinterpret_cast<signed short&>(scriptCounterF00);
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<=0 && (reinterpret_cast<signed short&>(scriptCounterF02))<1) {
        PrepareActionAt453D40(0);
        StartAnimationAt46D000(0x96);
        for (int shot=0;shot<10;++shot) {
            field314=float(30-shot*6);
            field318=15.0f;
            SpawnFloatXYAt453A70(0x347,
                float((facing)*49)+(x),
                (*(&y))+g_F968_RoundY190At00659294,
                facing,1);
        }
        velocityX=float(reinterpret_cast<signed short&>(scriptCounterF00))*g_F747_BounceYAt00658044;
        velocityY=float(reinterpret_cast<signed short&>(scriptCounterF02))*g_F747_BounceYAt00658044;
        reinterpret_cast<signed short&>(scriptCounterF00)=2;
        ++reinterpret_cast<signed short&>(scriptCounterF02);
    }
    break;
}
