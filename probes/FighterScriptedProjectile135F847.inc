// F847 selected Japanese original 0x135: 278B/82-x86, 7 native PE fields.
// Actual signed facing byte, original kind/stage and natural C++ source.
// Interior only, not independent original exact callable CODE.
case 0x135: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ResetAt453E20();
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
    if (GetNativeActionAt40FA30()==(field070)) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if ((animationStage)==7 && (animationFrame)==0)
        SpawnDirectedAt453A70(0x339,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),
            (facing),1);
    if ((animationStage)==7 && (animationFrame)==0)
        PrepareActionAt453D60(0x1D);
    return;
}
