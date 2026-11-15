// F1113: genuine original TH075 Japanese action 0x384 inside ONE still
// NONEXACT CharacterObject Advance. PE 0051AAFD..0051AFF0: 1267B/277 x86.
case 0x384: {
    if (owner->field3A0<=0) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    if (F1024_PHASE(this).stageAt62<6) {
        scaleX=(scaleX)+g_F1051_ScaleStepAt00658348;
        scaleY=(scaleY)+g_F1051_ScaleStepAt00658348;
        if (scaleX>g_F1057_NudgeAt00657480)
            scaleX=2.0f;
        if (scaleY>g_F1057_NudgeAt00657480)
            scaleY=2.0f;
    }
    if (F1024_PHASE(this).stageAt62>5) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            F1037_POSITION(this).yPosition=0.0f;
            F1037_MOTION(this).yMotion=0.0f;
            F1037_MOTION(this).xMotion=0.0f;
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(11);
            SetNativeActionAt0040FAC0(0x385);
            if (g_F1113_DifficultyAt006714D0>0) {
                owner->field314=3.0f;
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x38E,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x38E,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),-1,1);
            }
            if (g_F1113_DifficultyAt006714D0>1) {
                    owner->field314=6.0f;
                    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                        0x38E,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
                    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                        0x38E,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),-1,1);
            }
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x347,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
                for (int shot=0;shot<15;++shot)
                    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                        0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
            return;
        }
    }
    if (owner->animationStage==9 && F1024_PHASE(this).stageAt62<6) {
        SetAuxActionAt0040FB40(F1024_PHASE(this).stageAt62+5);
        F1037_MOTION(this).xMotion=float(facing) *
            (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition)/g_F1113_DivisorAt0065988C;
        if (F1037_MOTION(this).xMotion<g_F1051_TrajectoryLowerAt00658290)
            F1037_MOTION(this).xMotion=6.0f;
        F1037_MOTION(this).yMotion=-12.0f;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==field070) {
        SetAuxActionAt0040FB40(6);
        return;
    }
    if (F1024_PHASE(this).stageAt62==6 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    return;
}
