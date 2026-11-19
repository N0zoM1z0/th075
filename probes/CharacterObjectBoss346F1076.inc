// F1076: genuine Japanese native 00511D25..005123B9 (1684B/365 x86).
// Real 0x346 source inside ONE original 81KB CharacterObject, NONEXACT.
case 0x346: {
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<5) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
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
    if (animationStage==0 && animationFrame==0 &&
        field0D8==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field07C=0;
        field080=1;
        field0D8=15;
        SetPolarVelocity(field0C8,
                                    float(field0D8));
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (animationStage==1) {
        SetPolarVelocity(field0C8,
                                    float(field0D8));
        --field0D8;
        if (field0D8<0)
            field0D8=0;
        rotationZ=(rotationZ)+g_F1076_AngleNudgeAt00658294;
    }
    if (animationStage==2) {
        ++field0D8;
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)*g_F1076_ScaleMulAt00659450;
        SetPolarVelocity(float(field0DC),
                                     float(field0D8));
        rotationZ=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
        owner->field310=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
    }
    if (animationStage==3) {
        ++field0D8;
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)*g_F1076_ScaleMulAt00659450;
        SetPolarVelocity(float(field0DC),
                                     float(field0D8));
        rotationZ=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
        if (color[0]>10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if ((field07C==2 || field07C==4) && animationStage==2) {
        ResetSecondaryCounter(3);
        return;
    }
    if (x>g_F1076_RightAt00659424 ||
        x<g_F1076_LeftAt006595EC ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1076_LeftAt006595EC) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (animationStage==2 && animationFrame==0) {
        field0DC=short(F1057_FloatAtan2At00483300(
          ((*(&owner->opponent->y))+g_F1076_TargetYOffsetAt00658398-y),
          (owner->opponent->x-x)*int(facing)) /
          g_F1057_AngleDivAt00657828);
    }
    if (animationStage==3 && animationFrame==0)
        ClearFrameInfo();
    return;
}
