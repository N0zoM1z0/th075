// F837 selected 005214B0 actor original interior CB: 496 B, 141 x86,
// 12 genuine original PE fields. Natural +F00 prefix signed-short ++
// and actual native source order recover all non-parent-JMP bytes.
// This is NOT an independently callable original game function.
case 0xCB: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        POS=0.0f;
        POS54=0.0f;
        POS5C=0.0f;
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>0) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f;
            POS54=0.0f;
            POS5C=0.0f;
            POS48=0.0f;
            S16(0x64)=0;
            SetNativeActionAt40FAC0(0xA);
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==1 && S16(0x64)==0) {
        POS=-10.0f;
        POS54=5.0f;
        POS5C=0.6f;
        SpawnAt453C80(0x7D,
            reinterpret_cast<FighterBorrowedXViewF833*>(this)->xAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*80),
            (*(&POS48))+g_ContactProjectionAt00657888,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    if (S16(0x62)==3 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(1);
    }
    return;
}
