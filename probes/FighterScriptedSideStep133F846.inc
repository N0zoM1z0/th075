// F846 selected actor original 0x133, 270B/78 x86/6 genuine PE fields.
// Native stage8 direction*70 integer-to-float conversion precedes ADD
// to observed xAt44; this original GPR/x87 order naturally matches.
// This is a whole giant function interior, not independent callable CODE.
case 0x133: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        if (FLAG==0) ResetAt453E20();
        S16(0x80)=1;
        I32(0x7C)=0;
    }
    if (FLAG>0) {
        POS=POS-g_JumpGroundCorrectionAt00658058;
        if (POS<g_ThresholdAt0065782C) {
            POS=0.0f;
            FLAG=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0xF00)=0;
    }
    if (S16(0x62)==5 && S16(0x64)==0)
        PrepareActionAt453D60(0x1D);
    if (S16(0x62)==8 && S16(0x64)==0)
        F32(0x44)=float((*reinterpret_cast<signed char*>(RAW+0x66))*70)+F32(0x44);
    return;
}
