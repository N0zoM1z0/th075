// F856 selected actor original 190: 217B/64 x86/six native PE fields.
// Stage3 actual sprite320, animationFA, prepare0; stage4 state bit.
// Normal C++ whole original game interior, source GPR not exact.
case 0x190: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field314=1.0f;
        SpawnDirectedAt453A70(0x320,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
           (facing),1);
        StartAnimationAt46D000(0xFA);
        PrepareActionAt453D40(0);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
        field07C=1;
    return;
}
