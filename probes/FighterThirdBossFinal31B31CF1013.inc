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
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        BeginStateAt454A70(0);
        RefreshStateAt452B30();
        PrepareActionAt453D60(0x17);
        SpawnWithFloatAt453A70(0x3E5,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<8) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(9);
    }
    break;
}
// F1013 original Japanese final fighter state 0x31C.
case 0x31C: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==16 && S16(0x64)==0) {
        BeginStateAt454A70(0);
        RefreshStateAt452B30();
        PrepareActionAt453D60(0x17);
    }
    if (S16(0x62)==21 && S16(0x64)==0 && S16(0xF00)<8) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(19);
        U8(0x3CF)=1;
    }
    break;
}
