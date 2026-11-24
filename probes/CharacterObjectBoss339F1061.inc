// F1061: authentic original CharacterObject action 0x339 at
// 0050ED70..0050EF5F, original 495 CODE B /101 ordered x86.
// This is an INNER state inside ONE nonexact original 81KB Boss.
case 0x339: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        scaleX=0.5f;
        scaleY=0.5f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field01A=0x4E2;
        rotationX=-30.0f;
        rotationY=float(int(facing) * -45);
        field0D8=0;
    }
    scaleX =
        (FloatConstants::ThreeTenths -
            float(field0D8)*g_F1061_StepAt0065972C *
            int(field0D8<10)) +
        g_F1061_OffsetAt00658354 + scaleX;
    scaleY =
        (FloatConstants::ThreeTenths -
            float(field0D8)*g_F1061_StepAt0065972C *
            int(field0D8<10)) +
        g_F1061_OffsetAt00658354 + scaleY;
    if (animationStage>1) {
        if (color[0]>20)
            color[0]-=20;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
