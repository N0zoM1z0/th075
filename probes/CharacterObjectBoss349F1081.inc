// F1081: original Japanese game 00512815..005129C1, 428 original
// CODE bytes /94 x86 within ONE still nonexact CharacterObject boss.
case 0x349: {
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
    }
    reinterpret_cast<unsigned int&>(x)=reinterpret_cast<unsigned int&>(owner->x);
    y=(*(&owner->y))+g_F1081_ParentYOffsetAt00658268;
    rotationZ=(rotationZ)-g_F1081_AngleStepAt00657874;
    if (animationStage==1) {
        if (owner->action!=0x2BE ||
            (owner->action==0x2BE &&
             owner->animationStage>8))
            ResetSecondaryCounter(2);
    }
    if (animationStage>1) {
        if (color[0]>25)
            color[0]-=25;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    return;
}
