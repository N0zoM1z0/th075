// F846 selected actor original 0x133, 270B/78 x86/6 genuine PE fields.
// Native stage8 direction*70 integer-to-float conversion precedes ADD
// to observed xAt44; this original GPR/x87 order naturally matches.
// This is a whole giant function interior, not independent callable CODE.
case 0x133: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0) ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D60(0x1D);
    if ((reinterpret_cast<signed short&>(animationStage))==8 && (reinterpret_cast<signed short&>(animationFrame))==0)
        x=float((facing)*70)+(x);
    return;
}
