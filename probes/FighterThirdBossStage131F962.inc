// F962: real original Japanese TH075 004AC040 game action 0x131.
 // Native original 004B14C9..004B1593 202 B/58 x86/5 original PE fields.
 // Natural C++ reproduces 202B/58 ordinal mnemonic and width geometry,
 // but 36 genuine GPR roles (first ordinal 0) remain incorrect.
 // This case is INTERNAL to a still NONEXACT 82KB original fighter.
// Genuine original 004AC040 131: 202B/58x86, stage5 Prepare0x1D.
case 0x131: {
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
    if (S16(0x62)==5 && S16(0x64)==0)
        PrepareActionAt453D60(0x1D);
    break;
}
