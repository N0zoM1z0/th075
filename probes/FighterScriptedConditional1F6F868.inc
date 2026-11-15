// F868 actual original 1F6: 372B/111-x86/12 real typed PE fields.
// Special U8 this+511 equals20, stage 8..10 triggers native 455B30 and exits.
// Stage5 float X/bitwise Y sprite80 and second sprite336, Prepare2.
// Full original enclosing fighter NONEXACT; no split-case CODE credit.
case 0x1F6: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
    }
    if ((velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_SubtractAt00657478;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>7 && (reinterpret_cast<signed short&>(animationStage))<0xB && (aiCommand)==0x14) {
        SetNativeActionAt40FAC0(0x1F7);
        ResetAt453E20();
        NativeGameEffectAt455B30();
        return;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=14.0f;
        SpawnFloatXRawYAt453C80(0x80,
            float((facing)*100)+(x),
            reinterpret_cast<int&>(y),(facing),1);
        SpawnDirectedAt453A70(0x336,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(2);
    }
    return;
}
