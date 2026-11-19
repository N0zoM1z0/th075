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
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
        SpawnWithFloatAt453A70(0x3E5,reinterpret_cast<int&>(x),
            (*(&y))+g_ContactProjectionAt00657888,
            facing,1);
    }
    if ((animationStage)==11 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(9);
    }
    break;
}
// F1013 original Japanese final fighter state 0x31C.
case 0x31C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070))
        ResetPrimaryCounters(0);
    if ((animationStage)==16 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
    }
    if ((animationStage)==21 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(19);
        reinterpret_cast<unsigned char&>(field3CF)=1;
    }
    break;
}
