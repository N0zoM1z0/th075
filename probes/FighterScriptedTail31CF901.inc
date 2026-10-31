// F901 original 31C tail native 219B/63 x86/7 real PE calls.
// Actual stage12 uses state454A70(0)/452B30/Prepare17;
// stage15 short F00<8 and native aux0D, sets char3CF=1.
// Whole original fighter 46755B remains NONEXACT.
case 0x31C: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==12 && S16(0x64)==0) {
        ApplyStateAt454A70(0);
        EmitStateAt452B30();
        PrepareActionAt453D60(0x17);
    }
    if (S16(0x62)==15 && S16(0x64)==0 && S16(0xF00)<8) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(0xD);
        U8(0x3CF)=1;
    }
    return;
}
