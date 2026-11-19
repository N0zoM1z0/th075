// F1095: independent Japanese original game action 0x355,
// 00514FE8..005154ED = 1285 original CODE B /270 native x86.
// One authentic state inside the still-NONEXACT 81KB CharacterObject.
case 0x355: {
    if (owner->action>0x45 &&
        owner->action<0x96) {
        ClearFrameInfo();
        for (int shot=0;shot<10;++shot) {
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
        }
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            owner->SpawnBattleEffect(
                0x3E3,x,y,1,1);
        }
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.0f;
        scaleY=0.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=10.0f;
        velocityY=6.0f;
        field0D8=0;
        field0DA=0;
        field0DC=0;
        field080=0;
        field07C=0;
    }
    if (scaleX<g_F1095_ScaleCeilingAt00659898) {
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
    } else if (field0D8==0) {
        field080=10;
        ++field0D8;
    }
    if (velocityX>g_F1059_ScaleRatioAt00657478) {
        velocityX=velocityX-g_F1059_ScaleRatioAt00657478;
        if (velocityX<g_F1059_ScaleRatioAt00657478)
            velocityX=0.5f;
    }
    if (field0DC==0) {
        velocityY=velocityY-g_F1062_ScaleStepAt006583F8;
        if (velocityY<g_F1095_LowerYAt00659894)
            field0DC=1;
    }
    if (field0DC==1) {
        velocityY=(*(&velocityY))+g_F1062_ScaleStepAt006583F8;
        if (velocityY>g_F1095_UpperYAt00659890)
            field0DC=0;
    }
    if (field07C==4 && field080>0)
        field07C=0;
    if (field07C!=0 && animationStage<0x1F) {
        ResetSecondaryCounter(0x1F);
        velocityX=0.0f;
        velocityY=0.0f;
        field0DC=2;
    }
    if (animationStage==0x1F) {
        scaleX=(scaleX)+g_F1051_ScaleStepAt00658348;
        scaleY=(scaleY)+g_F1051_ScaleStepAt00658348;
        color[0]=unsigned char(color[0]-25);
    }
    y=y+velocityY;
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (animationStage==0x1F && animationFrame==0) {
        if (field0DA<6) {
            ++field0DA;
            ResetSecondaryCounter(1);
            return;
        }
        velocityX=0.0f;
        velocityY=0.0f;
        field0DC=2;
    }
    return;
}
