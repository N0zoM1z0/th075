// F1126 genuine Japanese 0x391 at original PE 0051CF28..0051D413:
// 1,259 native CODE B /277 x86 in one incomplete 81KB Boss.
case 0x391: {
    if (owner->field3A0<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=3.0f;
        F1037_MOTION(this).yMotion=g_F1095_UpperYAt00659890-float(RandomBoundaryAt00455580(0,9));
        field0D8=0;
        field0DA=0;
        field0DC=0;
        field080=0;
        field07C=0;
    }
    if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
    } else {
        scaleX=1.0f;
        scaleY=1.0f;
    }
    if (field0DC==0) {
        F1037_MOTION(this).yMotion=F1037_MOTION(this).yMotion-g_F1062_ScaleStepAt006583F8;
        if (F1037_MOTION(this).yMotion<g_F1095_LowerYAt00659894)
            field0DC=1;
    }
    if (field0DC==1) {
        F1037_MOTION(this).yMotion=(*(&F1037_MOTION(this).yMotion))+g_F1062_ScaleStepAt006583F8;
        if (F1037_MOTION(this).yMotion>g_F1095_UpperYAt00659890)
            field0DC=0;
    }
    if (F1094_TRANSFORM(this).scaleXAt1C==g_F1051_ScaleCeilingAt0065747C &&
        g_F1113_DifficultyAt006714D0>1) {
        if (F1037_MOTION(this).xMotion>g_F1044_GroundAt0065782C &&
            F1037_POSITION(this).xPosition>g_F1083_YBoundAt00658E80) {
            F1037_MOTION(this).xMotion=-F1037_MOTION(this).xMotion;
        }
        if (F1037_MOTION(this).xMotion<g_F1044_GroundAt0065782C &&
            F1037_POSITION(this).xPosition<g_F1044_GroundAt0065782C)
            F1037_MOTION(this).xMotion=-F1037_MOTION(this).xMotion;
    }
    if (field0DA==0 &&
        F1094_TRANSFORM(this).scaleXAt1C==g_F1051_ScaleCeilingAt0065747C) {
        if (F1037_POSITION(PARENT_GRANDPARENT).yPosition<F1037_POSITION(this).yPosition &&
            F1115_AbsFloatAt00412D90(F1037_POSITION(this).xPosition-
                F1037_POSITION(PARENT_GRANDPARENT).xPosition)<g_F1126_XDistanceAt00657850) {
            field0DA=1;
            F1037_MOTION(this).xMotion=0.0f;
            F1037_MOTION(this).yMotion=-30.0f;
            scaleX=0.1f;
            scaleY=1.0f;
        }
    }
    if (field0DA==1) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            NativeParentExpiredAt0045B830();
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x392,reinterpret_cast<unsigned int&>(x),0,
                facing,1);
            return;
        }
    }
    if (F1037_POSITION(this).xPosition>g_F1126_RightAt00659884 ||
        F1037_POSITION(this).xPosition<g_F1126_LeftAt006595E4) {
        NativeParentExpiredAt0045B830();
        return;
    }
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    if (GetNativeActionAt0040FA30()==field070)
        NativeParentExpiredAt0045B830();
    if (F1024_PHASE(this).stageAt62==0x1F && F1024_PHASE(this).frameAt64==0) {
        SetAuxActionAt0040FB40(1);
        return;
    }
    return;
}
