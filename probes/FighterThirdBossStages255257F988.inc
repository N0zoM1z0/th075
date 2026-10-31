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
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(0x21);
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(6);
    }
    break;
}
// F988 real Japanese original 004AC040 action 0x256
case 0x256: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    break;
}
// F988 real Japanese original 004AC040 action 0x257
case 0x257: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==5 && S16(0x64)==0) {
        SpawnMixedAt453C80(0x37,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(6);
    }
    break;
}
