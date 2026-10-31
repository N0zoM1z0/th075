// F949: independent native 004AC040 original C9
// 004B02B9..004B04CC 531 complete internal original CODE B/158 x86.
// Natural source preserves all original positional mnemonic, width
// and GPR roles in the whole incomplete 82KB game-fighter source.
// All 13 original PE call/global targets must be verified separately;
// original saved-this EBP-0x64 is still wrong in this partial parent.
// No independent callable function or whole-fighter exactness claim.
case 0xC9: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0)
        ResetAt453E20();
    if (S16(0x62)==2 && S16(0x64)==0)
        POS=0.0f;
    if (S16(0x62)==4 && S16(0x64)==0)
        POS=-10.0f;
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>3 && S16(0x62)<6) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f;
            POS54=0.0f;
            POS5C=0.0f;
            POS48=0.0f;
            S16(0x64)=0;
            SetAuxActionAt40FB40(6);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0)
        POS=-50.0f;
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS54=4.0f;
        POS5C=0.6f;
        POS=-30.0f;
        SpawnMixedAt453C80(0x7D,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            -(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    if (S16(0x62)==6 && S16(0x64)==0)
        SetAuxActionAt40FB40(5);
    break;
}
