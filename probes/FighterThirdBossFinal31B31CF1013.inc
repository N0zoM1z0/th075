// F1013 original Japanese 004AC040 true final 31B/31C states.
 // Native original 31B: 257B/76 x86/9 actual PE targets;
 // native 31C: 219B/63 x86/7 actual PE targets.
 // Correct stage5/11 vs16/21, stage5 0x3E5 raw X+float Y
 // shot, stage21 signed state count and native +0x3CF BYTE.
 // Normal entire original-shaped PARTIAL 82KB source emits
 // all 139 original mnemonic, width and GPR roles naturally.
 // New real cases make preceding 303 final shared JMP use
 // native 5-byte near. Whole 82KB fighter still NONEXACT.
// F1013 original Japanese final fighter state 0x31B.
case 0x31B: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        BeginStateAt454A70(0);
        RefreshStateAt452B30();
        PrepareActionAt453D60(0x17);
        SpawnWithFloatAt453A70(0x3E5,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            facing,1);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(9);
    }
    break;
}
// F1013 original Japanese final fighter state 0x31C.
case 0x31C: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070)))
        SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==16 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        BeginStateAt454A70(0);
        RefreshStateAt452B30();
        PrepareActionAt453D60(0x17);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==21 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(19);
        reinterpret_cast<unsigned char&>(field3CF)=1;
    }
    break;
}
