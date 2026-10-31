// F1005 original Japanese 004AC040 native state2E6:
 // 2058 original CODE B/590x86, 47 real native PE targets.
 // Four real signed-mode loops emit 12/20/30/40 shots at
 // angle step30/18/12/9, each 0x387 signed facing*16
 // FILD/FSUBR; true random 0x33E and six 0x338..0x33D
 // seven-argument calls. Reused original borrowed F752
 // X views preserve direct native FCOMP memory: all 590
 // mnemonic + GPR roles match; only final shared-tail JMP
 // 5B original vs 2B partial-parent width differs.
 // Whole 82KB fighter and saved-this EBP NONEXACT.
// F1005 pinned Japanese TH075 original 004AC040 2E6.
case 0x2E6: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF06)=30;
        S16(0xF08)=1;
        POS5C=0.15f;
    }
    if (S16(0x62)==6 || S16(0x62)==7) {
        if (U8(0x11)>30)
            U8(0x11)=U8(0x11)-30;
        else {
            U8(0x11)=0;
            SetAuxActionAt40FB40(8);
            break;
        }
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        POS=float(RandAt455580(0,100)-50);
        POS54=float(RandAt455580(0,5)+20);
        if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
                reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
            *reinterpret_cast<signed char*>(RAW+0x66)=-1;
        else
            *reinterpret_cast<signed char*>(RAW+0x66)=1;
    }
    if (S16(0x62)==9) {
        if (U8(0x11)<225)
            U8(0x11)=U8(0x11)+30;
        else
            U8(0x11)=255;
    }
    if (S16(0x62)>13 && S16(0x62)<19) {
        if (POS48>=g_ThresholdAt0065782C) {
            POS54=POS54-POS5C;
            if (POS48+POS54<=g_ThresholdAt0065782C) {
                U8(0x11)=255;
                ResetAt453E20();
                SetAuxActionAt40FB40(19);
                POS48=0.0f;
                break;
            }
        }
    }
    if (S16(0x62)<8 && S16(0x62)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+F32(0x44)-g_F983_XOffsetAt00658264,
            ((*(&POS48))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if (S16(0x62)>10 && S16(0x62)<17 && S16(0xF02)==0) {
        ++S16(0xF02);
        if (g_F1004_ModeAt006714D0==0) {
            for (int shot=0;shot<12;++shot) {
                F32(0x314)=float(shot*30);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
        if (g_F1004_ModeAt006714D0==1) {
            for (int shot=0;shot<20;++shot) {
                F32(0x314)=float(shot*18);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
        if (g_F1004_ModeAt006714D0==2) {
            for (int shot=0;shot<30;++shot) {
                F32(0x314)=float(shot*12);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
        if (g_F1004_ModeAt006714D0==3) {
            for (int shot=0;shot<40;++shot) {
                F32(0x314)=float(shot*9);
                SpawnFloatXYAt453A70(0x387,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                        float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                    (*(&POS48))+g_F972_YAt0065836C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if (S16(0x62)==6 && S16(0x64)==0) {
        PrepareActionAt453D40(2);
        SpawnSevenFloatAt453B50(0x338,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x339,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33A,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33C,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SpawnSevenFloatAt453B50(0x33D,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                float((*reinterpret_cast<signed char*>(RAW+0x66))*7),
            (*(&POS48))+g_F983_BurstYAt00659490,
            1,1,0,1);
        SetMotionStateAt40FBB0(0,0.0f,0);
        U8(0x11)=255;
    }
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF00);
        break;
    }
    if (S16(0x62)==9 && S16(0x64)==0) {
        POS=0.0f;
        POS54=0.0f;
    }
    if (S16(0x62)==11 && S16(0x64)==0)
        PrepareActionAt453D40(5);
    if (S16(0x62)==17 && S16(0x64)==0 && S16(0xF00)<10) {
        SetAuxActionAt40FB40(15);
        ++S16(0xF00);
    }
    if (S16(0x62)==19 && S16(0x64)==0)
        SetAuxActionAt40FB40(17);
    break;
}
