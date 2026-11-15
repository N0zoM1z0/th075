// F1069: native Japanese original action 0x331 at
// 0050D53A..0050D88E, 852 original CODE B /185 actual x86 instructions.
// Genuine gameplay inside ONE still nonexact 81KB original CharacterObject.
case 0x331: {
    reinterpret_cast<unsigned char&>(facing)=reinterpret_cast<unsigned char&>(owner->facing);
    if (owner->action>0x95 &&
        owner->action<0x9A &&
        F1024_PHASE(this).stageAt62==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(facing*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1069_ParentYFirstAt00659138;
    }
    if (owner->action>0x99 &&
        owner->action<0x9E &&
        F1024_PHASE(this).stageAt62==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(facing*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1069_ParentYSecondAt00658264;
    }
    if (owner->action==0x9E &&
        F1024_PHASE(this).stageAt62==0) {
        F1037_POSITION(this).xPosition=F1037_POSITION(PARENT).xPosition+
            float(facing*57);
        F1037_POSITION(this).yPosition=(*(&F1037_POSITION(PARENT).yPosition))+
            g_F1057_YOffsetAt00657888;
    }
    if ((owner->action<0x96 ||
         owner->action>0x9E) &&
        F1024_PHASE(this).stageAt62==0) {
        ResetSecondaryCounter(1);
        owner->fieldF0A=0;
    }
    if (F1024_PHASE(this).stageAt62==0 &&
        F1024_PHASE(this).frameAt64==0 &&
        field0D8==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationY=50.0f;
        field0D8=1;
    }
    rotationZ=(rotationZ)+g_F1057_NudgeAt00657480;
    if (F1024_PHASE(this).stageAt62>0) {
        if (color[0]>30)
            color[0]-=30;
        else
            color[0]=0;
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (F1024_PHASE(this).stageAt62==1 && F1024_PHASE(this).frameAt64==0)
        ResetSecondaryCounter(0);
    return;
}
