// F1083: real Japanese original 00512BA7..00512D43, 412 CODE B/85 x86.
// Actual 0x34B animation/ground physics inside the ONE nonexact 81KB Boss.
case 0x34B: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
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
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
    if (F1037_POSITION(this).yPosition>g_F1083_YBoundAt00658E80) {
        ClearFrameInfo();
        return;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (F1024_PHASE(this).stageAt62==15 && F1024_PHASE(this).frameAt64==0)
        F1037_MOTION(this).yMotion=-40.0f;
    return;
}
