// F985 original Japanese game fighter 004AC040 1FB/1FC/1FD.
 // Physical native 1193/1192/1193 CODE B, 346 x86 each, 28
 // genuine typed original PE/COFF external fields EACH.
 // Stage6/7 opacity only (no false break), stage9..12 ground,
 // genuine six 0x338..0x33D signed-FSUBR bursts, real 0xC8
 // animation, stage8 counter/launch with X 60/-60/120 and stage13.
 // All 1038 original ordered mnemonics; one CMP opacity register
 // width wrong in 1FB and 1FC, zero wrong widths in 1FD.
 // Whole 82KB original remains NONEXACT, many GPR/EBP differences.
case 0x1FB: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=1;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)==6 || S16(0x62)==7) {
        if (U8(0x11)>20)
            U8(0x11)=U8(0x11)-20;
        else
            U8(0x11)=0;

    }
    if (S16(0x62)>8 && S16(0x62)<13) {
        POS54=POS54-POS5C;
        if (U8(0x11)<235)
            U8(0x11)=U8(0x11)+20;
        else
            U8(0x11)=255;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            U8(0x11)=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            POS48=0.0f;
            break;
        }
    }
    if (S16(0x62)<8 && S16(0x62)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+F32(0x44)-g_F983_XOffsetAt00658264,
            ((*(&POS48))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if (S16(0x62)==9 && S16(0x64)==0 && S16(0xF00)==0) {
        POS=0.0f;
        POS54=0.0f;
        ++S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        U8(0x11)=255;
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF02)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF02);
        break;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        POS=60.0f;
        POS54=3.0f;
        POS5C=0.5f;
    }
    if (S16(0x62)==13 && S16(0x64)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1FC: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=1;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)==6 || S16(0x62)==7) {
        if (U8(0x11)>20)
            U8(0x11)=U8(0x11)-20;
        else
            U8(0x11)=0;

    }
    if (S16(0x62)>8 && S16(0x62)<13) {
        POS54=POS54-POS5C;
        if (U8(0x11)<235)
            U8(0x11)=U8(0x11)+20;
        else
            U8(0x11)=255;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            U8(0x11)=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            POS48=0.0f;
            break;
        }
    }
    if (S16(0x62)<8 && S16(0x62)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+F32(0x44)-g_F983_XOffsetAt00658264,
            ((*(&POS48))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if (S16(0x62)==9 && S16(0x64)==0 && S16(0xF00)==0) {
        POS=0.0f;
        POS54=0.0f;
        ++S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        U8(0x11)=255;
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF02)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF02);
        break;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        POS=-60.0f;
        POS54=3.0f;
        POS5C=0.5f;
    }
    if (S16(0x62)==13 && S16(0x64)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1FD: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=1;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)==6 || S16(0x62)==7) {
        if (U8(0x11)>20)
            U8(0x11)=U8(0x11)-20;
        else
            U8(0x11)=0;

    }
    if (S16(0x62)>8 && S16(0x62)<13) {
        POS54=POS54-POS5C;
        if (U8(0x11)<235)
            U8(0x11)=U8(0x11)+20;
        else
            U8(0x11)=255;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            U8(0x11)=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xD);
            POS48=0.0f;
            break;
        }
    }
    if (S16(0x62)<8 && S16(0x62)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+F32(0x44)-g_F983_XOffsetAt00658264,
            ((*(&POS48))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if (S16(0x62)==9 && S16(0x64)==0 && S16(0xF00)==0) {
        POS=0.0f;
        POS54=0.0f;
        ++S16(0xF00);
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        StartAnimationAt46D000(0xC8);
        SetMotionStateAt40FBB0(0,0.0f,0);
        U8(0x11)=255;
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF02)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF02);
        break;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        POS=120.0f;
        POS54=3.0f;
        POS5C=0.5f;
    }
    if (S16(0x62)==13 && S16(0x64)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
