// F1064: actual Japanese PE 0050E274..0050E518 action 0x335,
// 676 native CODE B /149 x86 of ONE nonexact 81KB CharacterObject.
case 0x335: {
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<7) {
        ClearFrameInfo();
        for (int shot=0;shot<4;++shot) {
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
        }
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3,x,y,1,1);
        }
        return;
    }
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        field080=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=10.0f;
        velocityY=5.0f;
    }
    x=float(facing)*velocityX + x;
    y=y-velocityY;
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
