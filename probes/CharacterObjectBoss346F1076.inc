// F1076: genuine Japanese native 00511D25..005123B9 (1684B/365 x86).
// Real 0x346 source inside ONE original 81KB CharacterObject, NONEXACT.
case 0x346: {
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        F1024_PHASE(this).stageAt62<5) {
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
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0 &&
        field0D8==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field07C=0;
        field080=1;
        field0D8=15;
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
                                    float(field0D8));
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (F1024_PHASE(this).stageAt62==1) {
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),
                                    float(field0D8));
        --field0D8;
        if (field0D8<0)
            field0D8=0;
        rotationZ=(rotationZ)+g_F1076_AngleNudgeAt00658294;
    }
    if (F1024_PHASE(this).stageAt62==2) {
        ++field0D8;
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)*g_F1076_ScaleMulAt00659450;
        SetPolarVelocity(float(field0DC),
                                     float(field0D8));
        rotationZ=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
        owner->field310=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
    }
    if (F1024_PHASE(this).stageAt62==3) {
        ++field0D8;
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)*g_F1076_ScaleMulAt00659450;
        SetPolarVelocity(float(field0DC),
                                     float(field0D8));
        rotationZ=F1057_FloatAtan2At00483300(
            F1037_MOTION(this).yMotion,F1037_MOTION(this).xMotion)/g_F1057_AngleDivAt00657828;
        if (color[0]>10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if ((field07C==2 || field07C==4) && F1024_PHASE(this).stageAt62==2) {
        ResetSecondaryCounter(3);
        return;
    }
    if (F1037_POSITION(this).xPosition>g_F1076_RightAt00659424 ||
        F1037_POSITION(this).xPosition<g_F1076_LeftAt006595EC ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1076_LeftAt006595EC) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0) {
        field0DC=short(F1057_FloatAtan2At00483300(
          ((*(&F1037_POSITION(PARENT_GRANDPARENT).yPosition))+g_F1076_TargetYOffsetAt00658398-F1037_POSITION(this).yPosition),
          (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition)*int(facing)) /
          g_F1057_AngleDivAt00657828);
    }
    if (F1024_PHASE(this).stageAt62==3 && F1024_PHASE(this).frameAt64==0)
        ClearFrameInfo();
    return;
}
