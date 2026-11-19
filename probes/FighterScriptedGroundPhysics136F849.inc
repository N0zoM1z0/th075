// F849 genuine original 0x136 ground/extra-fall and sprite0x33A.
// Full 321B/95 x86/10 native typed PE fields. Current parent has
// 15 real stage5 GPR operand negatives and two entire-parent JMP bytes.
// Not byte exact or independently callable original CODE.
case 0x136: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if ((animationStage)>2 && (velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_AnimationDeltaAt0065747C;
        if ((velocityX)<g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        SpawnDirectedAt453A70(0x33A,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
        PlaySharedSound(0x1D);
    }
    return;
}
