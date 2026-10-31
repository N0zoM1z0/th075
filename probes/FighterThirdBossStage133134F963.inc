// F963: original pinned Japanese TH075 004AC040 action 133 & 134.
 // 133 physically 004B1593..004B16AD 282 B/84 x86/7 typed PE fields;
 // 134 physically 004B16AD..004B18B1 516 B/152 x86/12 PE fields.
 // Natural C++ preserves all original mnemonic and width ordinals.
 // 53/98 GPR roles differ in still PARTIAL/nonexact 82KB father.
// F963 original 004AC040 stage133 native evidence, partial giant.
case 0x133: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0)
            ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_ApproachAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0xF00)=0;
    }
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    if (S16(0x62)==3 && S16(0x64)==0)
        SpawnSevenAt453B50(0x324,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    break;
}
// F963 original 004AC040 stage134 native evidence, partial giant.
case 0x134: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        POS54=0.0f;
        POS5C=0.0f;
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (POS>g_ThresholdAt0065782C) {
        POS=POS-g_SubtractAt00657478;
        if (POS<g_StopThresholdAt00657480 &&
            POS48>g_ThresholdAt0065782C)
            POS=2.0f;
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<14) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f;
            POS54=0.0f;
            POS5C=0.0f;
            POS48=0.0f;
            SetAuxActionAt40FB40(0xE);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        POS=12.5f;
        POS54=8.5f;
        POS5C=0.65f;
    }
    if (S16(0x62)==7 && S16(0x64)==0)
        SpawnSevenAt453B50(0x336,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    if (S16(0x62)==7 && S16(0x64)==0)
        PrepareActionAt453D60(0x1D);
    if (S16(0x62)==14 && S16(0x64)==0)
        SetAuxActionAt40FB40(S16(0x62)-2);
    break;
}
