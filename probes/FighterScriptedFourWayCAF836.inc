// F836: actual Japanese TH075 005214B0 native interior CA.
// Native 418 B/121 x86/11 physical PE fields; direct enclosing-giant exits.
// Unlike another fighter, resets native motion slots, with stage2 sprite.
// Not independently callable original CODE.
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        POS54=0.0f;
        POS5C=0.0f;
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
            return;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS=10.0f;
        POS54=5.0f;
        POS5C=0.6f;
        SpawnAt453C80(0x7D,float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            (*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    return;
}
