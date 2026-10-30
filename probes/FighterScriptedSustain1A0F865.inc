// F865 native original 1A0: 235B/67 x86/five real original PE fields.
// Meaningful float+54 lvalue needed for native FLD member/ FMUL global widths.
// Enclosing giant remains original GPR and full-parent-JMP nonexact.
case 0x1A0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=POS*g_F865SustainScaleAt00658348;
        POS54=(*(&POS54))*g_F865SustainScaleAt00658348;
    }
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
