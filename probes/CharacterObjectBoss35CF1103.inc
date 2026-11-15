// F1103 original Japanese 0x35C, native 005163BA..00516517:
// 349 CODE B /72 x86 in ONE still-NONEXACT 81KB parent.
case 0x35C: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        reinterpret_cast<signed short&>(field080)=99;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        reinterpret_cast<signed short&>(field0D8)=0;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
    scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
    if (F1024_PHASE(this).stageAt62>0) {
        if (color[0]>15)
            color[0]-=10;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        NativeParentExpiredAt0045B830();
    return;
}
