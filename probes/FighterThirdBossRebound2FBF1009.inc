// F1009 native original Japanese fighter 004AC040 2FB.
 // Original 004BF40E..004BF9A2 1428B/411x86/33 real physical
 // PE call and global fields. Real random0x33E, 6 native seven
 // arg 0x338..0x33D with FILD/FSUBR signed facing*7,
 // opponent facing via verified F752 borrowed native X,
 // world-X bounds 0065787C/0065920C, real stage8
 // randomized rebound and genuine transition to 0x2F9.
 // Source in normal PARTIAL father produces 1425B/411 x86
 // with ALL native mnemonic/GPR roles, one wrong final
 // shared-parent JMP width original 5B vs source2B.
 // Real 2FB restores preceding 2FA's last JMP to native5B;
 // original whole 82KB parent remains NONEXACT.
// F1009 original Japanese TH075 004AC040 2FB
case 0x2FB: {
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
            SetAuxActionAt40FB40(13);
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
        SetNativeActionAt40FAC0(0x2F9);
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
        POS=float(RandAt455580(0,480)-240);
        if (F32(0x44)<g_F1009_LeftAt0065787C)
            POS=float((RandAt455580(0,180)+90) *
                (*reinterpret_cast<signed char*>(RAW+0x66)));
        if (F32(0x44)>=g_F1009_RightAt0065920C)
            POS=float(-(RandAt455580(0,180)+90) *
                (*reinterpret_cast<signed char*>(RAW+0x66)));
        POS54=3.0f;
        POS5C=0.5f;
    }
    if (S16(0x62)==9 && S16(0x64)==0) {
        if (reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44 >
            reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44)
            *reinterpret_cast<signed char*>(RAW+0x66)=-1;
        else
            *reinterpret_cast<signed char*>(RAW+0x66)=1;
    }
    if (S16(0x62)==13 && S16(0x64)==0)
        SetAuxActionAt40FB40(11);
    break;
}
