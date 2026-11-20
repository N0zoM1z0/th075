// F1121: original Japanese 0x38C, 0051C82D..0051C91E:
// 241 native CODE B/52 x86 inside ONE NONEXACT 81KB parent.
case 0x38C: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=6.0f;
    }
    velocityX=(*(&velocityX))+g_F1120_XBrakingAt00659090;
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
