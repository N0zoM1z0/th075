// F1073: pinned Japanese original 0050B821..0050BF41: 1824 native
// CODE bytes /435 x86. One genuine, not separately callable 81KB state.
case 0x328: {
    if (owner->action>0x31 &&
        owner->action<0x96) {
        ClearFrameInfo();
        for (int shot=0;shot<10;++shot) {
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
    if (x>g_F1057_RightBoundAt0065925C ||
        x<g_F1057_LeftBoundAt00659258 ||
        y>g_F1057_UpperBoundAt006583B4 ||
        y<g_F1057_LowerBoundAt00658374) {
        ClearFrameInfo();
        return;
    }
    if (animationStage==0 && animationFrame==0) {
        ResetTransform(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        SetPolarVelocity(field0C8,13.0f);
        rotationZ=field0C8;
        field0D8=0;
        field080=1;
        field07C=0;
    }
    if (field07C==6) {
        field07C=0;
        ++field080;
    }
    x=float(facing)*velocityX+x;
    y=y+velocityY;
    // The native projectile is spawned UNCONDITIONALLY before its
    // subsequent native state/ground branch (original ordinal 147..176).
    owner->SpawnBattleEffect(
        0x32B,
        float(RecordedRange(0,60))+x-g_F1068_ActionSpeedAt00657878,
        float(RecordedRange(0,60))+y-g_F1068_ActionSpeedAt00657878,
        facing,0);
    if (field080==0 ||
        y+velocityY<=g_F1044_GroundAt0065782C) {
        ClearFrameInfo();
        owner->SetCameraShake(5.0f);
        owner->PlaySound(1);
        // Real PE has 16 separate CALLs: one 0x339 then 15 0x33A; not a loop.
#define F1073_SPAWN_33A() \
        owner->SpawnBattleEffect( \
            0x33A,x,y, \
            facing,1)
        owner->SpawnBattleEffect(
            0x339,x,y,
            facing,1); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
#undef F1073_SPAWN_33A
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(1);
    return;
}
