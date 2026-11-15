// F869 actual native game 1F7: 307B/90x86/11 physical original PE fields.
// Real stage4..6 U8+511 guard =>1F8 effect455B30; stage3 sprite337 Prepare3.
// True original function is whole fighter parent; no case exact CODE credit.
case 0x1F7: {
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
    if ((reinterpret_cast<signed short&>(animationStage))>3 && (reinterpret_cast<signed short&>(animationStage))<7 && (aiCommand)==0x14) {
        SetNativeActionAt40FAC0(0x1F8);
        ResetAt453E20();
        NativeGameEffectAt455B30();
        return;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnDirectedAt453A70(0x337,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PrepareActionAt453D40(3);
    }
    return;
}
