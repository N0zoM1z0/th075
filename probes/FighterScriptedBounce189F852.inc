// F852 selected game original 189, 381 B/107 x86/11 physically typed PE fields.
// Genuine x87 FUCOMPP equality and y+velocityY ground test, state7
// reflected velocity, stage3 POS15, speed8.5/0.85. Source GPR phase
// still has genuine nonrelocation mismatches; no standalone exact credit.
case 0x189: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
        velocityX=12.5f;
        field05C=0.0f;
    }
    if (*(&y)==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_AnimationDeltaAt0065747C;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (y>g_ThresholdAt0065782C && (animationStage)<7) {
        velocityY=velocityY-field05C;
        if (y+velocityY<g_ThresholdAt0065782C) {
            y=0.0f;
            velocityX=(velocityX)*g_F852GroundBounceMultiplierAt00657478;
            SetAuxActionAt40FB40(7);
            return;
        }
    }
    if (AdvanceNestedFrame()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=15.0f;
        velocityY=8.5f;
        field05C=0.85f;
        PlaySharedSound(0x1D);
    }
    return;
}
