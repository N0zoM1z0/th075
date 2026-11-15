// F1115: genuine original Japanese 0x386 game action at
// PE 0051B21D..0051B5AF, 914 native CODE B /195 ordered x86.
// One true state of ONE still-NONEXACT 81KB CharacterObject::Advance.
case 0x386: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=3.0f;
        F1037_MOTION(this).yMotion=0.0f;
    }
    if (F1024_PHASE(this).stageAt62==1) {
        scaleX=float(RandomBoundaryAt00455580(0,4))*
            g_F1057_SpeedScaleAt006590B4+g_F1115_RandomDoubleAt006583B8;
        reinterpret_cast<unsigned int&>(scaleY)=reinterpret_cast<unsigned int&>(scaleX);
        if (F1115_AbsFloatAt00412D90(F1037_POSITION(this).xPosition-
            F1037_POSITION(PARENT_GRANDPARENT).xPosition)<g_F1115_DistanceAt0065786C) {
            F1037_MOTION(this).xMotion=0.0f;
            scaleX=1.0f;
            scaleY=1.0f;
            reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
            ResetSecondaryCounter(2);
            return;
        }
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    if (AdvanceNestedFrame()==field070) {
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(10.0f);
        for (int shot=0;shot<12;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x387,
                (*(&F1037_POSITION(this).xPosition))+g_F1069_ParentYSecondAt00658264-float(RandomBoundaryAt00455580(0,80)),
                float(RandomBoundaryAt00455580(0,320)),
                facing,1);
        }
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0)
        ResetSecondaryCounter(1);
    return;
}
