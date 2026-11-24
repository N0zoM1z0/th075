// F1113: genuine original TH075 Japanese action 0x384 inside ONE still
// NONEXACT CharacterObject Advance. PE 0051AAFD..0051AFF0: 1267B/277 x86.
case 0x384: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
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
        velocityX=0.0f;
        velocityY=0.0f;
    }
    if (animationStage<6) {
        scaleX=(scaleX)+g_F1051_ScaleStepAt00658348;
        scaleY=(scaleY)+g_F1051_ScaleStepAt00658348;
        if (scaleX>g_F1057_NudgeAt00657480)
            scaleX=2.0f;
        if (scaleY>g_F1057_NudgeAt00657480)
            scaleY=2.0f;
    }
    if (animationStage>5) {
        if (y+velocityY<=g_F1044_GroundAt0065782C) {
            y=0.0f;
            velocityY=0.0f;
            velocityX=0.0f;
            owner->PlaySound(11);
            ResetPrimaryCounters(0x385);
            if (g_OptionsModeAt006714D0>0) {
                owner->field314=3.0f;
                owner->SpawnBattleEffect(
                    0x38E,x,y,1,1);
                owner->SpawnBattleEffect(
                    0x38E,x,y,-1,1);
            }
            if (g_OptionsModeAt006714D0>1) {
                    owner->field314=6.0f;
                    owner->SpawnBattleEffect(
                        0x38E,x,y,1,1);
                    owner->SpawnBattleEffect(
                        0x38E,x,y,-1,1);
            }
                owner->SpawnBattleEffect(
                    0x347,x,y,facing,1);
                for (int shot=0;shot<15;++shot)
                    owner->SpawnBattleEffect(
                        0x33A,x,y,facing,1);
            owner->SetCameraShake(5.0f);
            return;
        }
    }
    if (owner->animationStage==9 && animationStage<6) {
        ResetSecondaryCounter(animationStage+5);
        velocityX=float(facing) *
            (owner->opponent->x-x)/g_F1113_DivisorAt0065988C;
        if (velocityX<g_F1051_TrajectoryLowerAt00658290)
            velocityX=6.0f;
        velocityY=-12.0f;
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    if (AdvanceNestedFrame()==animationStageCount) {
        ResetSecondaryCounter(6);
        return;
    }
    if (animationStage==6 && animationFrame==0)
        ResetSecondaryCounter(1);
    return;
}
