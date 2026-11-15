// F1125 original Japanese action 0x390 at 0051CB4A..0051CF28:
// 990 native CODE B /212 x86 inside ONE still-NONEXACT 81KB boss.
case 0x390: {
    if (owner->field3A0<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+g_F1085_LastYAt006592A4);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
    }
    ++field0D8;
    if (F1024_PHASE(this).stageAt62<2) {
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+g_F1085_LastYAt006592A4);
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (field07C!=0 && F1024_PHASE(this).stageAt62==1) {
        SetAuxActionAt0040FB40(2);
        scaleX=4.0f;
        scaleY=4.0f;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        return;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1125_YUpperAt00657884 ||
        F1037_POSITION(this).yPosition<g_F1101_LeftAt0065924C) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>=25) {
            color[0]-=25;
            color[1]-=25;
            color[2]-=25;
            scaleX=(scaleX)*g_F1070_FadeScaleAt00659454;
            scaleY=(scaleY)*g_F1070_FadeScaleAt00659454;
        } else {
            color[0]=0;
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    return;
}
