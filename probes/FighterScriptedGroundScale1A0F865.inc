// F865 authentic game original 1A0: 235B/67x86/5 physical PE fields.
// Both native multiplier x87 groups must FLD field before FMUL global658348.
// Current whole giant GPR and original final JMP remain NONEXACT.
case 0x1A0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    POS=POS*g_F865PhysicsMultiplierAt00658348;
    POS54=(*(&POS54))*g_F865PhysicsMultiplierAt00658348;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        POS=0.0f;
        POS54=0.0f;
        POS48=0.0f;
    }
    if (S16(0x62)>3)
        POS54=POS54-POS5C;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0)
        I32(0x7C)=1;
    return;
}
