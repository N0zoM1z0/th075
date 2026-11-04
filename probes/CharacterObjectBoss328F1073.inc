// F1073: pinned Japanese original 0050B821..0050BF41: 1824 native
// CODE bytes /435 x86. One genuine, not separately callable 81KB state.
case 0x328: {
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
        SetNativeAngleBitsAt0040FB70(SELF_FIELD(unsigned int,0xC8),13.0f);
        SELF_FIELD(unsigned int,0x30)=SELF_FIELD(unsigned int,0xC8);
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
    }
    if (SELF_FIELD(int,0x7C)==6) {
        SELF_FIELD(int,0x7C)=0;
        ++SELF_FIELD(signed short,0x80);
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    // The native projectile is spawned UNCONDITIONALLY before its
    // subsequent native state/ground branch (original ordinal 147..176).
    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
        0x32B,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).xPosition-g_F1068_ActionSpeedAt00657878,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).yPosition-g_F1068_ActionSpeedAt00657878,
        SELF_FIELD(signed char,0x66),0);
    if (SELF_FIELD(signed short,0x80)==0 ||
        F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
        NativeParentExpiredAt0045B830();
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(1);
        // Original PE has sixteen separate CALLs, not a compiler loop.
#define F1073_SPAWN_33A() \
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70( \
            0x33A,SELF_FIELD(unsigned int,0x44),SELF_FIELD(unsigned int,0x48), \
            SELF_FIELD(signed char,0x66),1)
        F1073_SPAWN_33A(); F1073_SPAWN_33A();
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
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70))
        SetAuxActionAt0040FB40(1);
    return;
}
