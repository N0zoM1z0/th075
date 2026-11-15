// F1085: genuine native Japanese action 0x34C, original
// 00512D43..00513235 (1266 original CODE B /273 x86), one nonexact 81KB boss.
case 0x34C: {
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        ResetTransform(0,0.0f,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        if (field0D8!=140)
            field0D8=0;
    }
    SetPolarVelocity(
        float(owner->fieldF0C)+
            g_F1085_ParentMultiplierAt0065989C*static_cast<const float&>(field0C8),
        float(field0D8));
    F1037_POSITION(this).xPosition=F1037_MOTION(this).xMotion+F1037_POSITION(PARENT).xPosition;
    F1037_POSITION(this).yPosition=(*(&F1037_MOTION(this).yMotion))*g_F1085_ParentYMultiplierAt00657F74+
        F1037_POSITION(PARENT).yPosition+g_F1085_YOffsetAt0065835C;
    if (field0D8<140)
        field0D8=short(field0D8+5);
    else
        field0D8=140;
    if ((owner->opponent->health<=0 ||
        owner->health<=0 ||
        owner->field3A0<=0) &&
        F1024_PHASE(this).stageAt62<2)
        ResetSecondaryCounter(2);
    if (owner->action==0x2C1 &&
        owner->animationStage==2 &&
        F1024_PHASE(this).stageAt62<2)
        ResetSecondaryCounter(2);
    if (F1024_PHASE(this).stageAt62==0) {
        if ((owner->action==0x190 && owner->animationStage==4) ||
            (owner->action==0x258 && owner->animationStage==7) ||
            (owner->action==0x259 && owner->animationStage==7) ||
            (owner->action==0x25A && owner->animationStage==3)) {
            for (int shot=0;shot<8;++shot) {
                owner->field314=float(shot*45);
                reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                    0x360,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
                    owner->facing,1);
            }
            ResetSecondaryCounter(2);
            reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(4);
        }
    }
    if (F1024_PHASE(this).stageAt62==1 &&
        owner->action==0x2C1 &&
        owner->animationStage==3) {
        ResetSecondaryCounter(0);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(20);
        return;
    }
    if (F1024_PHASE(this).stageAt62>1) {
        if (color[0]>10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070) {
        ClearFrameInfo();
        return;
    }
    if (F1024_PHASE(this).stageAt62==2 && F1024_PHASE(this).frameAt64==0) {
        ResetSecondaryCounter(0);
        owner->field36C=(owner->field36C)-g_F1085_LastYAt006592A4;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(20);
    }
    return;
}
