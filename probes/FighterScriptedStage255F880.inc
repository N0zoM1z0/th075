// F880 real original action 0x255, complete native interior.
// Native action9, float Y sprite37, Prepare21; stage8 aux6 only 255/257.
// Entire original fighter remains nonexact; this is no independent leaf.
case 0x255: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetAt453E20();
        field080=1;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(9);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            (facing),1);
        PrepareActionAt453D60(0x21);
    }
    if ((animationStage)==8 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(6);
    }
    return;
}
