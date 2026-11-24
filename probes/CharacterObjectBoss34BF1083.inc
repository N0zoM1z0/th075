// F1083: real Japanese original 00512BA7..00512D43, 412 CODE B/85 x86.
// Actual 0x34B animation/ground physics inside the ONE nonexact 81KB Boss.
case 0x34B: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=99;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
        velocityX=0.0f;
        velocityY=0.0f;
    }
    scaleY=(scaleY)+FloatConstants::OneTenth;
    if (y>g_F1083_YBoundAt00658E80) {
        ClearFrameInfo();
        return;
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==15 && animationFrame==0)
        velocityY=-40.0f;
    return;
}
