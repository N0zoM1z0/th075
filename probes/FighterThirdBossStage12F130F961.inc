// F961 real original Japanese 004AC040 stages 12F/130.
 // 12F: 004B12F1..004B13C0, 207 CODE B /59 x86 /6 original PE fields.
 // 130: 004B13C0..004B14C9, 265 CODE B /81 x86 /6 original PE fields.
 // Both are native GPR/mnemonic/width-complete INTERNAL cases,
 // not separate whole game functions; parent 82KB remains NONEXACT.
// Genuine original 004AC040 12F: native 207B/59x86.
case 0x12F: {
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
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(2);
    if (S16(0x62)==4 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    break;
}
// Genuine original 004AC040 130: native 265B/81 x86, original sprite334.
case 0x130: {
    POS54=POS54-POS5C;
    if (POS48+POS54<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(0xA);
        POS48=0.0f;
        POS5C=0.0f;
        POS54=0.0f;
        break;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(9);
    if (S16(0x62)==3 && S16(0x64)==0)
        PrepareActionAt453D60(0x1C);
    if (S16(0x62)==3 && S16(0x64)==0) {
        SpawnSevenAt453B50(0x334,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    }
    break;
}
