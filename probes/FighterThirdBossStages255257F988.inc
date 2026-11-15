// F988 authentic Japanese fighter 004AC040 actions255/256/257.
 // Original complete internal handlers 258B/75, 176B/52,
 // 248B/72 x86; 7+5+6 native typed PE external target fields.
 // Natural normal VC7.1 source matches all opcode mnemonics/widths
 // but GPR/EBP saved-this owner still differs: 46/32/46 GPR roles.
 // Stage5 rawX/floatY 0x37, original 255 alone prepares action21;
 // original 255/257 alone perform stage8 auxiliary action6.
 // Entire 82KB giant is NONEXACT; do not credit cropped cases.
// F988 real Japanese original 004AC040 action 0x255
case 0x255: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(9);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            facing,1);
        PrepareActionAt453D60(0x21);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(6);
    }
    break;
}
// F988 real Japanese original 004AC040 action 0x256
case 0x256: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(9);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            facing,1);
    }
    break;
}
// F988 real Japanese original 004AC040 action 0x257
case 0x257: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
        field3AC=0;
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(9);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        SpawnMixedAt453C80(0x37,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            facing,1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(6);
    }
    break;
}
