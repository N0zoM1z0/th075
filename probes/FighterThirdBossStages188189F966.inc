// F966 original Japanese TH075 004AC040 actions 188/189.
// 188 physical 004B1F1D..004B2091 372B/106x86/11 PE external fields;
// 189 physical 004B2091..004B2167 214B/61x86/6 PE fields.
// Ordinary C++ emits native mnemonic/widths exactly in whole partial
// fighter; 63/38 GPR-role errors remain. 188 has genuine FUCOMPP
// float equality and real stage6->stage4 nested control-flow test;
// do NOT silently optimize away an original native branch.
// The entire original 82KB fighter function remains NONEXACT.
// Real original Japanese TH075 004AC040 0x188 372B/106-x86 source.
case 0x188: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
        POS=10.0f;
    }
    if (POS48==g_ThresholdAt0065782C) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            POS48=0.0f;
            SetAuxActionAt40FB40(0xC);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        // Actual original PE retains this inner stage 4 conditional,
        // despite the outer stage 6 test. Do not delete original branch.
        if (S16(0x62)==4 && S16(0x64)==0)
            PrepareActionAt453D60(0x1C);
        POS=10.0f;
        POS54=12.5f;
        POS5C=1.0f;
    }
    break;
}
// Real original Japanese TH075 004AC040 0x189 214B/61-x86 source.
case 0x189: {
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
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    break;
}
