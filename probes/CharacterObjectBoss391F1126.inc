// F1126 genuine Japanese 0x391 at original PE 0051CF28..0051D413:
// 1,259 native CODE B /277 x86 in one incomplete 81KB Boss.
case 0x391: {
    if (owner->field3A0<=0) {
        ClearFrameInfo();
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
        velocityX=3.0f;
        velocityY=g_F1095_UpperYAt00659890-float(RecordedRange(0,9));
        field0D8=0;
        field0DA=0;
        field0DC=0;
        field080=0;
        field07C=0;
    }
    if (scaleX<g_F1051_ScaleCeilingAt0065747C) {
        scaleX=(scaleX)+g_F1057_SpeedScaleAt006590B4;
        scaleY=(scaleY)+g_F1057_SpeedScaleAt006590B4;
    } else {
        scaleX=1.0f;
        scaleY=1.0f;
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
    if (scaleX==g_F1051_ScaleCeilingAt0065747C &&
        g_F1113_DifficultyAt006714D0>1) {
        if (velocityX>g_F1044_GroundAt0065782C &&
            x>g_F1083_YBoundAt00658E80) {
            velocityX=-velocityX;
        }
        if (velocityX<g_F1044_GroundAt0065782C &&
            x<g_F1044_GroundAt0065782C)
            velocityX=-velocityX;
    }
    if (field0DA==0 &&
        scaleX==g_F1051_ScaleCeilingAt0065747C) {
        if (owner->opponent->y<y &&
            F1115_AbsFloatAt00412D90(x-
                owner->opponent->x)<g_F1126_XDistanceAt00657850) {
            field0DA=1;
            velocityX=0.0f;
            velocityY=-30.0f;
            scaleX=0.1f;
            scaleY=1.0f;
        }
    }
    if (field0DA==1) {
        if (y+velocityY<=g_F1044_GroundAt0065782C) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(
                0x392,x,0.0f,
                facing,1);
            return;
        }
    }
    if (x>g_F1126_RightAt00659884 ||
        x<g_F1126_LeftAt006595E4) {
        ClearFrameInfo();
        return;
    }
    y=y+velocityY;
    x=float(facing)*velocityX+x;
    if (AdvanceNestedFrame()==field070)
        ClearFrameInfo();
    if (animationStage==0x1F && animationFrame==0) {
        ResetSecondaryCounter(1);
        return;
    }
    return;
}
