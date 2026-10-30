// F844 original selected 005214B0 native stage0x130 202B/58 x86.
// Native x87 position/grounded drag and two entire-parent returns.
// Physical PE shows prepare stage3, animation1C, action9.
// Not independently callable whole original game CODE.
case 0x130: {
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        POS48=0.0f;
        POS5C=0.0f;
        POS54=0.0f;
        return;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==3 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    return;
}
