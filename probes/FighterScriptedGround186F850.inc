// F850 current original native actor 0x186 natural falling/animation source.
// Entire original game case, not an independent callable function.
case 0x186: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
        velocityX=12.5f;
    }
    if ((animationStage)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if (GetNativeActionAt40FA30()==(field070))
        SetNativeActionAt40FAC0(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        PlaySharedSound(0x1D);
        SpawnDirectedAt453A70(0x341,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),(facing),1);
    }
    return;
}
