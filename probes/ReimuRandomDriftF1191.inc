case R1191_ACTION: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1; S16(0xF00)=0; S16(0xF02)=0;
        ResetAt453E20();
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(10);
            POS48=0.0f;
            ResetAt453E20();
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(R1191_AUX);
    if (S16(0x62)==2 && S16(0x64)==0) {
#if R1191_REVERSE_X
        POS=g_ReimuReverseDriftAt0065907C-float(SelectRangeAt455580(0,3));
#else
        POS=float(SelectRangeAt455580(0,3))+g_ApproachLowerAt00658290;
#endif
        POS54=float(SelectRangeAt455580(0,R1191_LIFT_RANGE))+g_ReimuRandomLiftAt00657850;
        POS5C=0.3f;
    }
    break;
}
