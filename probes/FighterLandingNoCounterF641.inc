// F641: genuine original 71-instruction A3/A4/A5 timed landing
// actions with NO trajectory counter reset, unlike the earlier F633
// 73/75-x86 family. This is an inner case of a nonexact giant.
case F641_CASE: {
    field368=(field368)+g_AnimationDeltaAt0065747C;
    if ((field368)>g_AnimationMaximumAt006583B4)
        field368=1000.0f;
    if (animationStage==0 && animationFrame==0) {
        velocityX=F641_START_HEIGHT;
        velocityY=0.0f;
        field07C=0;
    }
    if ((velocityX)<g_ThresholdAt0065782C) {
        velocityX=(velocityX)+g_JumpGroundCorrectionAt00658058;
        if ((velocityX)>g_ThresholdAt0065782C)
            velocityX=0.0f;
    }
    if (ContactAt454EE0() && field3BE)
        field490=(velocityX)*g_JumpReflectionAt006583E8;
    if (GetNativeActionAt40FA30()==field070)
        SetNativeActionAt40FAC0(F641_NEXT_ACTION);
    break;
}
