// F983 authentic Japanese TH075 fighter 004AC040 actions1F8/1F9.
 // Native original 1F8=1168B/339 x86 and 1F9=1167B/339 x86,
 // 28 true original PE external fields each. Typed borrowed float
 // world X at +0x44 yields genuine original IMUL/FILD/FSUBR
 // (six chains per action). Twelve original source FISUB/mnemonic
 // chains are eliminated without fake locals or byte grafting.
 // Original one CMP ECX/EAX,0xEB 6B/5B width per case still
 // differs (case-local ordinal64), with native GPR-role debts;
 // entire 82KB whole callable remains NONEXACT, not case exact.
// F983 natural source probe for real original 004AC040 1F8
case 0x1F8: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)==6 || S16(0x62)==7) {
        if (U8(0x11)>30)
            U8(0x11)=U8(0x11)-30;
        else
            U8(0x11)=0;
        SetAuxActionAt40FB40(8);
        POS=60.0f;
        POS54=10.0f;
        POS5C=0.4f;
        break;
    }
    if (S16(0x62)==9 || S16(0x62)==10) {
        POS54=POS54-POS5C;
        if (U8(0x11)<235)
            U8(0x11)=U8(0x11)+20;
        else
            U8(0x11)=255;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            U8(0x11)=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xB);
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
        SetMotionStateAt40FBB0(0,0.0f,0);
        U8(0x11)=255;
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF02)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF02);
        break;
    }
    if (S16(0x62)==11 && S16(0x64)==0)
        SetAuxActionAt40FB40(9);
    break;
}
// F983 natural source probe for real original 004AC040 1F9
case 0x1F9: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)==6 || S16(0x62)==7) {
        if (U8(0x11)>30)
            U8(0x11)=U8(0x11)-30;
        else
            U8(0x11)=0;
        SetAuxActionAt40FB40(8);
        POS=-60.0f;
        POS54=10.0f;
        POS5C=0.4f;
        break;
    }
    if (S16(0x62)==9 || S16(0x62)==10) {
        POS54=POS54-POS5C;
        if (U8(0x11)<235)
            U8(0x11)=U8(0x11)+20;
        else
            U8(0x11)=255;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            U8(0x11)=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(0xB);
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
        SetMotionStateAt40FBB0(0,0.0f,0);
        U8(0x11)=255;
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF02)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF02);
        break;
    }
    if (S16(0x62)==11 && S16(0x64)==0)
        SetAuxActionAt40FB40(9);
    break;
}
