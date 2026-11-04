// F1051: native original 0050A80F..0050AC27 (1048B/229 x86), ONE case
// inside the nonexact 81KB original CharacterObject::Advance.
// Parent +0xE4, target grandparent +0x2E8 are borrowed, not embedded owners.
case 0x321: {
    if (PARENT_FIELD(signed short,0x60) != 0x2BC) {
        NativeParentExpiredAt0045B830();
        return;
    }
    if (SELF_FIELD(signed short,0x62)==0 && SELF_FIELD(signed short,0x64)==0) {
        SetNativeMotionAt0040FBB0(0,0,0);
        SELF_FIELD(signed short,0x80)=1;
        SELF_FIELD(int,0x7C)=0;
        SELF_FIELD(signed short,0xD8)=0;
        SELF_FIELD(float,0x1C)=0.0f;
        SELF_FIELD(float,0x20)=0.0f;
        SELF_FIELD(unsigned char,0x11)=0xFF;
        SELF_FIELD(unsigned char,0x12)=0xFF;
        SELF_FIELD(unsigned char,0x13)=0xFF;
        SELF_FIELD(unsigned char,0x14)=0xFF;
        SELF_FIELD(float,0x50)=0.0f;
        SELF_FIELD(float,0x54)=0.0f;
    }
    if (SELF_FIELD(signed short,0x62)<6) {
        SELF_FIELD(float,0x1C)=SELF_FIELD(float,0x1C)+g_F1051_ScaleStepAt00658348;
        SELF_FIELD(float,0x20)=SELF_FIELD(float,0x20)+g_F1051_ScaleStepAt00658348;
        if (SELF_FIELD(float,0x1C)>g_F1051_ScaleCeilingAt0065747C)
            SELF_FIELD(float,0x1C)=2.0f;
        if (SELF_FIELD(float,0x20)>g_F1051_ScaleCeilingAt0065747C)
            SELF_FIELD(float,0x20)=2.0f;
    }
    if (SELF_FIELD(signed short,0x62)>5 &&
        F1037_POSITION(this).yPosition+F1037_MOTION(this).yMotion <= g_F1044_GroundAt0065782C) {
        SELF_FIELD(float,0x48)=0.0f;
        SELF_FIELD(float,0x54)=0.0f;
        SELF_FIELD(float,0x50)=0.0f;
        reinterpret_cast<F1051Grandparent*>(PARENT)->NativePrepareAt00453D40(0xB);
        SetNativeActionAt0040FAC0(0x322);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
            0x347, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48),
            SELF_FIELD(signed char,0x66), 1);
        reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnProjectileAt00453C80(
            0x7F, SELF_FIELD(unsigned int,0x44), 0,
            SELF_FIELD(signed char,0x66), 1);
        for (int shot=0; shot<20; ++shot) {
            reinterpret_cast<F1051Grandparent*>(PARENT)->SpawnObjectAt00453A70(
                0x33A, SELF_FIELD(unsigned int,0x44), SELF_FIELD(unsigned int,0x48),
                SELF_FIELD(signed char,0x66), 1);
        }
        reinterpret_cast<F1051Grandparent*>(PARENT)->InitTrajectoryAt00453E60(10.0f);
        return;
    }
    if (PARENT_FIELD(signed short,0x62)==9 && SELF_FIELD(signed short,0x62)<6) {
        SetAuxActionAt0040FB40(SELF_FIELD(signed short,0x62)+5);
        SELF_FIELD(float,0x50)=
            float(SELF_FIELD(signed char,0x66)) *
            (F1037_POSITION(PARENT_GRANDPARENT).xPosition-F1037_POSITION(this).xPosition) /
            g_F1051_TrajectoryUpperAt006590C4;
        if (SELF_FIELD(float,0x50)<g_F1051_TrajectoryLowerAt00658290)
            SELF_FIELD(float,0x50)=6.0f;
        SELF_FIELD(float,0x54)=-24.0f;
    }
    F1037_POSITION(this).xPosition=float(SELF_FIELD(signed char,0x66))*SELF_FIELD(float,0x50)+
        F1037_POSITION(this).xPosition;
    F1037_POSITION(this).yPosition=F1037_POSITION(this).yPosition+
        F1037_MOTION(this).yMotion;
    if (GetNativeActionAt0040FA30()==SELF_FIELD(signed short,0x70)) {
        SetAuxActionAt0040FB40(6);
        return;
    }
    if (SELF_FIELD(signed short,0x62)==6 && SELF_FIELD(signed short,0x64)==0)
        SetAuxActionAt0040FB40(1);
    return;
}
