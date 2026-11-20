// F1071: original Japanese PE 0050B150..0050B654; 1,284 original CODE
// B /278 x86. True stage-specific gameplay inside ONE nonexact 81KB Boss.
case 0x324: {
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<2) {
        ClearFrameInfo();
        for (int shot=0;shot<3;++shot) {
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
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        field080=1;
        field07C=0;
        field0D8=0;
        SetPolarVelocity(field0C8,15.0f);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ=F1057_FloatAtan2At00483300(
            velocityY,velocityX)/g_F1057_AngleDivAt00657828;
    }
    ++field0D8;
    if (animationStage<2) {
        SetPolarVelocity(field0C8,
            float(field0D8)*g_F1057_SpeedScaleAt006590B4+
            g_F1068_ActionSpeedAt00657878);
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
        }
    }
    if (field07C!=0 && animationStage==1) {
        ResetSecondaryCounter(2);
        scaleX=4.0f;
        scaleY=4.0f;
        velocityX=0.0f;
        velocityY=0.0f;
        return;
    }
    if (y-velocityY<=g_F1044_GroundAt0065782C) {
        ResetPrimaryCounters(0x325);
        y=0.0f;
        velocityX=0.0f;
        velocityY=0.0f;
        return;
    }
    x=float(facing)*velocityX+x;
    y=y-velocityY;
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1059_UpperBoundAt00657884 ||
        y<g_F1059_LowerBoundAt0065924C) {
        ClearFrameInfo();
        return;
    }
    if (animationStage>1) {
        if (color[0]>=25) {
            color[0]-=25;
            color[1]-=25;
            color[2]-=25;
            scaleX=(scaleX)*g_F1070_FadeScaleAt00659454;
            scaleY=(scaleY)*g_F1070_FadeScaleAt00659454;
        } else {
            color[0]=0;
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ClearFrameInfo();
    return;
}
