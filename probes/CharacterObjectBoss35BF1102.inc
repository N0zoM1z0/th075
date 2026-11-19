// F1102 original Japanese 0x35B, native 00515F65..005163BA:
// 1109 native CODE B /233 x86 in ONE still-NONEXACT 81KB parent.
case 0x35B: {
    if (owner->action>0x31 &&
        owner->action<0x96 &&
        animationStage<0x17) {
        ClearFrameInfo();
        for (int shot=0;shot<8;++shot)
            owner->SpawnBattleEffect(
                0x3E4,x,y,1,1);
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3,x,y,1,1);
        }
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=22.0f;
        field0D8=0;
        field0DA=0;
        field080=0;
        field07C=0;
    }
    velocityX=velocityX-g_F1093_XStepAt00658048;
    if (velocityX<g_F1051_ScaleCeilingAt0065747C)
        velocityX=1.0f;
    if (field0D8==0) {
        if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
            scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
            scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
            color[0]=unsigned char(color[0]+25);
        } else {
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
        }
        if (color[0]==0xFF && field0D8==0) {
            ++field0D8;
            field080=5;
        }
    }
    if (field07C==6) {
        field07C=0;
        ++field080;
    }
    if (field07C==4 && field080>0)
        field07C=0;
    if (field07C!=0)
        field080=0;
    x=float(facing)*velocityX+x;
    if (field080==0 && animationStage<0x17 &&
        field0D8>0) {
        ResetSecondaryCounter(0x17);
        return;
    }
    if (AdvanceNestedFrame()==field070) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0x17 && animationFrame==0 &&
        field0DA<1) {
        ResetSecondaryCounter(1);
        ++field0DA;
    }
    return;
}
