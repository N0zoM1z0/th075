// F863 actual original 0x19E: 122 native B/35 x86/three PE calls.
// Full original fighter switch interior, NOT independent exact CODE.
case 0x19E: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0)
        I32(0x7C)=1;
    return;
}
