// F1119: real original TH075 game action 0x38A at PE
// 0051BFE2..0051C3ED, 1035 native CODE B/226 x86. Whole 81KB NONEXACT.
case 0x38A: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
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
        if (scaleX>g_F1051_ScaleCeilingAt0065747C)
            scaleX=2.0f;
        if (scaleY>g_F1051_ScaleCeilingAt0065747C)
            scaleY=2.0f;
    }
    if (F1024_PHASE(this).stageAt62>5) {
        if (F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
            F1037_POSITION(this).yPosition=0.0f;
            F1037_MOTION(this).yMotion=0.0f;
            F1037_MOTION(this).xMotion=0.0f;
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(11);
            ResetPrimaryCounters(0x385);
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x347,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            int shot;
            for (shot=0;shot<15;++shot)
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            for (shot=0;shot<15;++shot)
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x389,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),facing,1);
            reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
            return;
        }
    }
    if (owner->animationStage==9 && F1024_PHASE(this).stageAt62<6) {
        ResetSecondaryCounter(F1024_PHASE(this).stageAt62+5);
        F1037_MOTION(this).xMotion=float(RandomBoundaryAt00455580(0,30)+10);
        F1037_MOTION(this).yMotion=-20.0f;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (AdvanceNestedFrame()==field070) {
        ResetSecondaryCounter(6);
        return;
    }
    if (F1024_PHASE(this).stageAt62==6 && F1024_PHASE(this).frameAt64==0)
        ResetSecondaryCounter(1);
    return;
}
