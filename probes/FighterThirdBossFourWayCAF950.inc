// F950: independently reconstructed native Japanese TH075 004AC040
// original action0xCA, 004B04CC..004B0680 436 CODE B /123 x86.
// The ordinary C++ emits 430B/123 original x86 with ALL native
// mnemonic and GPR-role positions equal, but two native wide EBP−0x98
// integer-to-x87 spill instructions are short because the still
// PARTIAL 82KB original father uses only a 0x40 stack frame.
// The original game giant remains NONEXACT; no case-only credit.
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        POS54=0.0f;
        POS5C=0.0f;
        S16(0xF00)=0;
    }
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS=11.0f;
        POS54=5.0f;
        POS5C=0.6f;
        SpawnAt453C80(0x7D,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_F950_CAVolleyYAt00658400,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_F950_CAVolleyYAt00658400,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D60(31);
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>1) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f;
            POS54=0.0f;
            POS5C=0.0f;
            POS48=0.0f;
            S16(0x64)=0;
            SetNativeActionAt40FAC0(0xA);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    break;
}
