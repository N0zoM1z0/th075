// F1071: original Japanese PE 0050B150..0050B654; 1,284 original CODE
// B /278 x86. True stage-specific gameplay inside ONE nonexact 81KB Boss.
case 0x324: {
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        F1024_PHASE(this).stageAt62<2) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),15.0f);
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
            g_F1068_ActionSpeedAt00657878);
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (field07C!=0 && F1024_PHASE(this).stageAt62==1) {
        ResetSecondaryCounter(2);
        scaleX=4.0f;
        scaleY=4.0f;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
        return;
    }
    if (F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
        ResetPrimaryCounters(0x325);
        F1037_POSITION(this).yPosition=0.0f;
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
