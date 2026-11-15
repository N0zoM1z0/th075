// F1074: Two physically different original game-state owners with the
// same verified normal x86 opcode geometry: 0x329 (0050BF41..0050C602)
// and 0x32A (0050C602..0050CCC3). Each 1,729 original CODE B/413 x86.
// Parameter F1074_X_SPEED is authentic 20.0f versus 10.0f.
// Both belong to ONE NONEXACT original 81KB CharacterObject Advance.
case F1074_CASE: {
    if (reinterpret_cast<signed short&>(owner->action)>0x31 &&
        reinterpret_cast<signed short&>(owner->action)<0x96) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<10;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        if (reinterpret_cast<signed short&>(owner->fieldEFA)>25) {
            reinterpret_cast<signed short&>(owner->fieldEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        return;
    }
    if (F1037_POSITION(this).xPosition>g_F1057_RightBoundAt0065925C ||
        F1037_POSITION(this).xPosition<g_F1057_LeftBoundAt00659258 ||
        F1037_POSITION(this).yPosition>g_F1057_UpperBoundAt006583B4 ||
        F1037_POSITION(this).yPosition<g_F1057_LowerBoundAt00658374) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (F1024_PHASE(this).stageAt62==0 && F1024_PHASE(this).frameAt64==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        F1037_MOTION(this).xMotion=F1074_X_SPEED;
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if (field07C==6) {
        field07C=0;
        ++reinterpret_cast<signed short&>(field080);
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    // The real random-position spawn precedes the status-dependent
    // fourteen-register 16-shot unroll. The second nested random
    // argument is evaluated first under original MSVC7.1 /Od.
    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
        0x32B,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).xPosition-g_F1068_ActionSpeedAt00657878,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).yPosition-g_F1068_ActionSpeedAt00657878,
        facing,0);
    if (reinterpret_cast<signed short&>(field080)==0) {
        NativeParentExpiredAt0045B830();
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(1);
#define F1074_SPAWN_33A() \
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70( \
            0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y), \
            facing,1)
        // Actual original has one 0x339 plus fifteen 0x33A direct CALLs,
        // not a loop with a synthetic local counter.
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x339,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
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
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        SetAuxActionAt0040FB40(1);
    return;
}
