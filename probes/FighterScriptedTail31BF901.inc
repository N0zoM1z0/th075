// F901 original native 31B whole 248B/74 x86/8 physical PE calls.
// Stage4 actual native 454A70(0), 452B30() and sprite3E5;
// stage8 genuinely used short F00<8 and auxiliary6.
// Inner original game case, not independently callable exact CODE.
case 0x31B: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ApplyStateAt454A70(0);
        EmitStateAt452B30();
        PrepareActionAt453D60(0x17);
        SpawnDirectedAt453A70(0x3E5,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(6);
    }
    return;
}
