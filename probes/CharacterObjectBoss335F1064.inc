// F1064: actual Japanese PE 0050E274..0050E518 action 0x335,
// 676 native CODE B /149 x86 of ONE nonexact 81KB CharacterObject.
case 0x335: {
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        F1024_PHASE(this).stageAt62<7) {
        ClearFrameInfo();
        for (int shot=0;shot<4;++shot) {
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
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0,0);
        field080=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=10.0f;
        F1037_MOTION(this).yMotion=5.0f;
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion + F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition-F1037_MOTION(this).yMotion;
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
