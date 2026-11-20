// F1069: native Japanese original action 0x331 at
// 0050D53A..0050D88E, 852 original CODE B /185 actual x86 instructions.
// Genuine gameplay inside ONE still nonexact 81KB original CharacterObject.
case 0x331: {
    facing = owner->facing;
    if (owner->action>0x95 &&
        owner->action<0x9A &&
        animationStage==0) {
        x=owner->x+
            float(facing*57);
        y=(*(&owner->y))+
            g_F1069_ParentYFirstAt00659138;
    }
    if (owner->action>0x99 &&
        owner->action<0x9E &&
        animationStage==0) {
        x=owner->x+
            float(facing*57);
        y=(*(&owner->y))+
            g_F1069_ParentYSecondAt00658264;
    }
    if (owner->action==0x9E &&
        animationStage==0) {
        x=owner->x+
            float(facing*57);
        y=(*(&owner->y))+
            g_F1057_YOffsetAt00657888;
    }
    if ((owner->action<0x96 ||
         owner->action>0x9E) &&
        animationStage==0) {
        ResetSecondaryCounter(1);
        owner->fieldF0A=0;
    }
    if (animationStage==0 &&
        animationFrame==0 &&
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
    if (animationStage>0) {
        if (color[0]>30)
            color[0]-=30;
        else
            color[0]=0;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    if (animationStage==1 && animationFrame==0)
        ResetSecondaryCounter(0);
    return;
}
