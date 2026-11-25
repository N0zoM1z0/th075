// F1074: Two physically different original game-state owners with the
// same verified normal x86 opcode geometry: 0x329 (0050BF41..0050C602)
// and 0x32A (0050C602..0050CCC3). Each 1,729 original CODE B/413 x86.
// Parameter F1074_X_SPEED is authentic 20.0f versus 10.0f.
// Both belong to ONE NONEXACT original 81KB CharacterObject Advance.
case F1074_CASE: {
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
    if (x>GeometryConstants::ThirteenHundredEighty ||
        x<GeometryConstants::NegativeHundred ||
        y>GeometryConstants::Thousand ||
        y<GeometryConstants::NegativeTwoHundredForty) {
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
        velocityX=F1074_X_SPEED;
        field0D8=0;
        remainingHits=1;
        collisionResult=0;
    }
    if (collisionResult==6) {
        collisionResult=0;
        ++remainingHits;
    }
    x=float(facing)*velocityX+x;
    // The real random-position spawn precedes the status-dependent
    // fourteen-register 16-shot unroll. The second nested random
    // argument is evaluated first under original MSVC7.1 /Od.
    owner->SpawnBattleEffect(
        0x32B,
        float(RecordedRange(0,60))+x-GeometryConstants::Thirty,
        float(RecordedRange(0,60))+y-GeometryConstants::Thirty,
        facing,0);
    if (remainingHits==0) {
        ClearFrameInfo();
        owner->SetCameraShake(5.0f);
        owner->PlaySound(1);
#define F1074_SPAWN_33A() \
        owner->SpawnBattleEffect( \
            0x33A,x,y, \
            facing,1)
        // Actual original has one 0x339 plus fifteen 0x33A direct CALLs,
        // not a loop with a synthetic local counter.
        owner->SpawnBattleEffect(
            0x339,x,y,
            facing,1); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
        F1074_SPAWN_33A(); F1074_SPAWN_33A();
#undef F1074_SPAWN_33A
        return;
    }
    if (AdvanceNestedFrame()==animationStageCount)
        ResetSecondaryCounter(1);
    return;
}
