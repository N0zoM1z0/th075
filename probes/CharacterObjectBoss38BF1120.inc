// F1120: original Japanese 0x38B, PE 0051C3ED..0051C82D:
// 1,088 original CODE B /226 native x86 in ONE NONEXACT 81KB Boss.
case 0x38B: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0x80;
        F1037_MOTION(this).xMotion=20.0f;
        field0D8=0;
        field0DA=0;
        field0DC=0;
        field080=0;
        field07C=0;
    }
    if (field0DC==0) {
        F1037_MOTION(this).xMotion=F1037_MOTION(this).xMotion-g_F1120_XBrakingAt00659090;
        if (F1037_MOTION(this).xMotion<g_F1051_ScaleCeilingAt0065747C) {
            F1037_MOTION(this).xMotion=1.0f;
            field0DC=1;
        }
    }
    if (field0DC>0 && field0DC<30)
        ++field0DC;
    if (field0DC>29)
        F1037_MOTION(this).xMotion=(*(&F1037_MOTION(this).xMotion))+g_F1059_ScaleRatioAt00657478;
    if (field0D8==0) {
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
            color[0]=unsigned char(color[0]+25);
        } else {
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
        }
        if (color[0]==0xFF && field0D8==0) {
            ++field0D8;
            field080=1;
        }
    }
    if (field07C==6) {
        field07C=0;
        ++field080;
    }
    if (field07C!=0) {
        ++field0D8;
        if (field0D8>5) {
            field0D8=0;
            field07C=0;
        }
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (field080==0 && F1024_PHASE(this).stageAt62<0x17 && field0D8>0) {
        SetAuxActionAt0040FB40(0x17);
        return;
    }
    if (GetNativeActionAt0040FA30()==field070) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0x17 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
