// F1070: original Japanese PE 0050AD46..0050B150, 1034 CODE B /220 x86.
// Genuine gameplay inside ONE nonexact 81KB CharacterObject advance.
case 0x323: {
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0,0);
        field080=1;
        field07C=0;
        field0D8=0;
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+
            g_F1070_InitSpeedAt00657858);
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
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+
            g_F1070_AnimSpeedAt006592A4);
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (field07C==6) {
        field07C=0;
        ++field080;
    }
    if (field07C!=0 && F1024_PHASE(this).stageAt62==1) {
        ResetSecondaryCounter(2);
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
        F1037_POSITION(this).yPosition>g_F1059_UpperBoundAt00657884 ||
        F1037_POSITION(this).yPosition<g_F1059_LowerBoundAt0065924C) {
        ClearFrameInfo();
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
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
