// F965 original Japanese TH075 fighter 004AC040 native 186/187
// 186 at 004B1C5B..004B1D70, 277B/84x86/7 original PE fields;
// 187 at 004B1D70..004B1F1D, 429B/124x86/11 original PE fields.
// Both source states preserve original mnemonic+width geometry;
// native GPR roles still differ in the partial huge father (53/78).
// 186 has NO actual native afterRET label; original 136 134-x86
// true physical end supplies its source start. Never fabricate label.
// This is only internal C++ of still NONEXACT 82KB original fighter.
// Original Japanese 004AC040 handler 0x186, native 277B/84 x86.
case 0x186: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=10.0f;
    }
    if (S16(0x62)>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    if (S16(0x62)==3 && S16(0x64)==0)
        SpawnSevenAt453B50(0x324,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    break;
}
// Original Japanese 004AC040 handler 0x187, native 429B/124 x86.
case 0x187: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
        S16(0x80)=2;
        I32(0x7C)=0;
        POS=10.0f;
    }
    if (S16(0x62)<2) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xE);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS=15.0f;
        POS54=8.5f;
        POS5C=0.6f;
    }
    if (S16(0x62)==7 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    if (S16(0x62)==8 && S16(0x64)==0)
        I32(0x7C)=0;
    if (S16(0x62)==14 && S16(0x64)==0)
        SetAuxActionAt40FB40(0xC);
    break;
}
