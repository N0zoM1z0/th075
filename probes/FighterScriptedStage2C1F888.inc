// F888 real original game 0x2C1 stage1, true real 453B50 sprite345.
// F10=420 guard is stage>10 for 2C0 but ONLY getter match for 2C1.
// Full 46755B giant NONEXACT, do not treat original inner case as callable CODE.
case 0x2C1: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=0;
        reinterpret_cast<signed short&>(field080)=1;
        ResetAt453E20();
    }
    if ((reinterpret_cast<signed short&>(animationStage))==1 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        AnimatePushAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        PrepareActionAt453D40(9);
        field36C=(field36C)-g_ContactProjectionAt00657888;
        SpawnMixedAt453C80(0x74,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
    }

    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        reinterpret_cast<signed short&>(fieldF10)=0x1A4;
        SetNativeActionAt40FAC0(0);
        SpawnExtraAt453B50(0x345,reinterpret_cast<int&>(x),
        (*(&y))+g_ContactProjectionAt00657888,1,1,0,1);
    }
    return;
}
