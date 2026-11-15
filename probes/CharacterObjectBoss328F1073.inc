// F1073: pinned Japanese original 0050B821..0050BF41: 1824 native
// CODE bytes /435 x86. One genuine, not separately callable 81KB state.
case 0x328: {
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
        SetNativeAngleBitsAt0040FB70(reinterpret_cast<unsigned int&>(field0C8),13.0f);
        reinterpret_cast<unsigned int&>(rotationZ)=reinterpret_cast<unsigned int&>(field0C8);
        reinterpret_cast<signed short&>(field0D8)=0;
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if (field07C==6) {
        field07C=0;
        ++reinterpret_cast<signed short&>(field080);
    }
    F1037_POSITION(this).xPosition=float(facing)*F1037_MOTION(this).xMotion+F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion;
    // The native projectile is spawned UNCONDITIONALLY before its
    // subsequent native state/ground branch (original ordinal 147..176).
    reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
        0x32B,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).xPosition-g_F1068_ActionSpeedAt00657878,
        float(RandomBoundaryAt00455580(0,60))+F1037_POSITION(this).yPosition-g_F1068_ActionSpeedAt00657878,
        facing,0);
    if (reinterpret_cast<signed short&>(field080)==0 ||
        F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion<=g_F1044_GroundAt0065782C) {
        NativeParentExpiredAt0045B830();
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(5.0f);
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(1);
        // Real PE has 16 separate CALLs: one 0x339 then 15 0x33A; not a loop.
#define F1073_SPAWN_33A() \
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70( \
            0x33A,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y), \
            facing,1)
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x339,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),
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
    if (GetNativeActionAt0040FA30()==reinterpret_cast<signed short&>(field070))
        SetAuxActionAt0040FB40(1);
    return;
}
