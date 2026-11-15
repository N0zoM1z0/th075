// F858 native actual 0x192: 217B/64-x86/6 original PE field references.
// Original transition2, stage4 sprite320 and +0x314 3f, stage5 state flag.
// Complete game switch interior; independent original whole giant still nonexact.
case 0x192: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field314=3.0f;
        SpawnDirectedAt453A70(0x320,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
           (facing),1);
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D40(0);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=1;
    return;
}
