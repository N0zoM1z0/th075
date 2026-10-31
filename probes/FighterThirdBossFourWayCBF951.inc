// F951: genuine original Japanese TH075 004AC040 native action0xCB
// (004B0680..004B0852): 466 CODE B/131 original x86, 11 genuine PE fields.
// Natural C++ emits all 131 native mnemonic positions, but 79 GPR roles
// still differ. Two original signed-to-x87 scratch locals live at native
// EBP−0x9C/−0xA0; partial father emits EBP−0x48/−0x4C,
// giving 4 honest width errors and a 12-byte CODE deficit.
// The 82KB original fighter parent is still structurally incomplete
// and NONEXACT. No source-only case credit.
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
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=-11.0f;
        POS54=5.0f;
        POS5C=0.6f;
        SpawnAt453C80(0x7D,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*68)+F32(0x44),
            (*(&POS48))+g_F950_CAVolleyYAt00658400,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnAt453C80(0x7E,
            float((*reinterpret_cast<signed char*>(RAW+0x66))*68)+F32(0x44),
            (*(&POS48))+g_F950_CAVolleyYAt00658400,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    break;
}
