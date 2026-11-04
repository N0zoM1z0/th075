// F1074: Two physically different original game-state owners with the
// same verified normal x86 opcode geometry: 0x329 (0050BF41..0050C602)
// and 0x32A (0050C602..0050CCC3). Each 1,729 original CODE B/413 x86.
// Parameter F1074_X_SPEED is authentic 20.0f versus 10.0f.
// Both belong to ONE NONEXACT original 81KB CharacterObject Advance.
case F1074_CASE: {
    if (PARENT_FIELD(signed short,0x60)>0x31 &&
        PARENT_FIELD(signed short,0x60)<0x96) {
        NativeParentExpiredAt0045B830();
        for (int shot=0;shot<10;++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E4,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
        }
        if (PARENT_FIELD(signed short,0xEFA)>25) {
            PARENT_FIELD(signed short,0xEFA)=0;
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x3E3,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),1,1);
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
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0.0f,0);
        SELF_FIELD(float,0x1C)=1.0f;
        SELF_FIELD(float,0x20)=1.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        F1037_MOTION(this).xMotion=F1074_X_SPEED;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
    }
    if (SELF_FIELD(int,0x7C)==6) {
        SELF_FIELD(int,0x7C)=0;
        ++SELF_FIELD(signed short,0x80);
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    // The real random-position spawn precedes the status-dependent
    // fourteen-register 16-shot unroll. The second nested random
    // argument is evaluated first under original MSVC7.1 /Od.
    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
        0x32B,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).xPosition-g_F1068_ActionSpeedAt00657878,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).yPosition-g_F1068_ActionSpeedAt00657878,
        SELF_FIELD(signed char,0x66),0);
    if (SELF_FIELD(signed short,0x80)==0) {
        NativeParentExpiredAt0045B830();
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(1);
#define F1074_SPAWN_33A() \
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70( \
            0x33A,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48), \
            SELF_FIELD(signed char,0x66),1)
        // Actual original has one 0x339 plus fifteen 0x33A direct CALLs,
        // not a loop with a synthetic local counter.
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x339,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66),1); F1074_SPAWN_33A();
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
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        SetAuxActionAt0040FB40(1);
    return;
}
