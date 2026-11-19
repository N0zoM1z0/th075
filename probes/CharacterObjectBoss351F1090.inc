// F1090: genuine original 0x351 at 00514537..0051497A, 1091 original
// CODE B /246 native x86, inside ONE still-NONEXACT CharacterObject.
case 0x351: {
    x = owner->x+float(owner->facing*20);
    ++field0DA;
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
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
        velocityX=0.0f;
        velocityY=-1.0f;
    }
    if (owner->animationStage>6 && animationStage<6) {
        ResetSecondaryCounter(animationStage+5);
        owner->PlaySound(15);
    }
    if (animationStage>5 && animationStage<11) {
        velocityY=0.0f;
        if (scaleX>=g_F1070_InitSpeedAt00657858) {
            ResetSecondaryCounter(animationStage+5);
            return;
        }
        scaleX=(scaleX)+g_F1057_NudgeAt00657480;
        scaleY=(scaleY)+g_F1057_NudgeAt00657480;
    }
    if (animationStage>10 && animationStage<16) {
        reinterpret_cast<F1051Grandparent*>(owner)->SpawnObjectAt00453A70(
            0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1);
    }
    if (animationStage>15) {
        if (color[0]>5)
            color[0]-=5;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (field0DA==35) {
        reinterpret_cast<F1051Grandparent*>(owner)->SpawnSevenAt00453B50(
            0x352,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
            facing,1,0,1);
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (AdvanceNestedFrame()==field070) {
        ResetSecondaryCounter(16);
        return;
    }
    if (animationFrame==0) field07C=0;
    if (animationStage==6 && animationFrame==0)
        ResetSecondaryCounter(1);
    if (animationStage==11 && animationFrame==0)
        ResetSecondaryCounter(6);
    if (animationStage==16 && animationFrame==0 &&
        owner->action==0x2BF && owner->animationStage>6 && owner->animationStage<9) {
        ResetSecondaryCounter(11);
    }
    return;
}
