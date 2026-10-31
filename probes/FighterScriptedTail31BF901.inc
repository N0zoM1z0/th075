// F901 original native 31B whole 248B/74 x86/8 physical PE calls.
// Stage4 actual native 454A70(0), 452B30() and sprite3E5;
// stage8 genuinely used short F00<8 and auxiliary6.
// Inner original game case, not independently callable exact CODE.
case 0x31B: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0) {
        ApplyStateAt454A70(0);
        EmitStateAt452B30();
        PrepareActionAt453D60(0x17);
        SpawnDirectedAt453A70(0x3E5,I32(0x44),I32(0x48),
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<8) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(6);
    }
    return;
}
