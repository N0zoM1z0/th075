// F1065/F1066: independent native actions 0x333, 0x334, and 0x336.
// Initial signed float at the real motion call is +30.0 for 333/334,
// -30.0 for 336; all three keep the authentic native game calls.
// F1065: independent native actions 0x333 and 0x334, physical original
// 0050D929..0050DDCF and 0050DDCF..0050E274, 249 x86 each.
// Shared C++ gameplay grammar, distinct native switch entries, never two
// original independent callable functions (ONE nonexact 81KB parent).
case F1065_ACTION: {
    if (owner->action>0x45 &&
        owner->action<0x96 &&
        animationStage<0x17) {
        ClearFrameInfo();
        for (int shot=0;shot<8;++shot) {
            owner->SpawnBattleEffect(
                0x3E4, x, y, 1, 1);
        }
        if (owner->fieldEFA>25) {
            owner->fieldEFA=0;
            owner->SpawnBattleEffect(
                0x3E3, x, y, 1, 1);
        }
        return;
    }
    if (field07C==5) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0,0);
        scaleX=0.1f;
        scaleY=0.1f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=0;
        field0DA=0;
        field0DC=0xAA;
        field080=0;
        field07C=0;
    }
    SetPolarVelocity(F1066_INITIAL_ANGLE,
        float(field0DC)*g_F1057_SpeedScaleAt006590B4);
    field0DC=short(field0DC-6);
    if (field0DC<20)
        field0DC=20;
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
            field080=10;
        }
    }
    if ((field07C==6 || field07C==4) &&
        field080>0)
        field07C=0;
    if (field07C!=0)
        ++field0D8;
    x=float(facing)*velocityX + x;
    y=y-velocityY;
    if (field080==0 &&
        animationStage<0x17 && field0D8>0) {
        ResetSecondaryCounter(0x17);
        return;
    }
    if (AdvanceNestedFrame()==field070) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0x17 && animationFrame==0 &&
        field0DA<0) {
        ResetSecondaryCounter(1);
        ++field0DA;
    }
    return;
}
