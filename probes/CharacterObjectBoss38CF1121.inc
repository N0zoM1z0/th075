// F1121: original Japanese 0x38C, 0051C82D..0051C91E:
// 241 native CODE B/52 x86 inside ONE NONEXACT 81KB parent.
case 0x38C: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=6.0f;
    }
    F1037_MOTION(this).xMotion=(*(&F1037_MOTION(this).xMotion))+g_F1120_XBrakingAt00659090;
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
