// F1090: genuine original 0x351 at 00514537..0051497A, 1091 original
// CODE B /246 native x86, inside ONE still-NONEXACT CharacterObject.
case 0x351: {
    F1037_POSITION(this).xPosition = F1037_POSITION(PARENT).xPosition+float(owner->facing*20);
    ++field0DA;
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        field080=99;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
        field0DA=0;
        F1037_MOTION(this).xMotion=0.0f;
        F1037_MOTION(this).yMotion=-1.0f;
    }
    if (owner->animationStage>6 && F1024_PHASE(this).stageAt62<6) {
        SetAuxActionAt0040FB40(F1024_PHASE(this).stageAt62+5);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(15);
    }
    if (F1024_PHASE(this).stageAt62>5 && F1024_PHASE(this).stageAt62<11) {
        F1037_MOTION(this).yMotion=0.0f;
        if (scaleX>=g_F1070_InitSpeedAt00657858) {
            SetAuxActionAt0040FB40(F1024_PHASE(this).stageAt62+5);
            return;
        }
        scaleX=(scaleX)+g_F1057_NudgeAt00657480;
        scaleY=(scaleY)+g_F1057_NudgeAt00657480;
    }
    if (F1024_PHASE(this).stageAt62>10 && F1024_PHASE(this).stageAt62<16) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
    }
    if (F1024_PHASE(this).stageAt62>15) {
        if (color[0]>5)
            color[0]-=5;
        else {
            NativeParentExpiredAt0045B830();
            return;
        }
    }
    if (field0DA==35) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnSevenAt00453B50(
            0x352,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1,0,1);
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==field070) {
        SetAuxActionAt0040FB40(16);
        return;
    }
    if (F1024_PHASE(this).frameAt64==0) field07C=0;
    if (F1024_PHASE(this).stageAt62==6 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(1);
    if (F1024_PHASE(this).stageAt62==11 && F1024_PHASE(this).frameAt64==0)
        SetAuxActionAt0040FB40(6);
    if (F1024_PHASE(this).stageAt62==16 && F1024_PHASE(this).frameAt64==0 &&
        owner->action==0x2BF && owner->animationStage>6 && owner->animationStage<9) {
        SetAuxActionAt0040FB40(11);
    }
    return;
}
