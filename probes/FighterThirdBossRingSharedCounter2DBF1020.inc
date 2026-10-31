// F1020 independently checked original Japanese fighter004AC040
 // REAL 2DB double 36-shot storm counter ownership correction.
 // Original two genuinely separate 0x385 rings use ONE native
 // EBP−0x40 int shot counter, each reset to zero, NOT two
 // separate source C++ for-loop declarations. Both have the
 // actual original 1894B/548 x86 and 38 true PE targets.
 // Hoisting the genuine shared int into its original
 // stage11/frame0 scope removes one unnecessary compiler
 // four-byte slot, restores original entire 82796B/22721
 // x86 count, stack0x720 and this EBP−0x64. Entire
 // whole callable still NONEXACT due 12 real widths and
 // 6958 positional GPR roles; no independent case credit.
// F1016 actual SHA-pinned Japanese 004AC040 original 2DB.
 // Original 004BC8B1..004BD017 1894 CODE B/548x86,
 // 38 actual original PE call/global target fields.
 // Native stage6 six distinct 0x338..0x33D, random
 // 0x33E; stage11 TWO real full 36x0x385 loops,
 // step10, speed5 then10, Y native global00659460,
 // signed-facing*8 FILD/FSUBR world X.
 // Real stage8 actor/opponent facing FCOMP and signed
 // opacity/fall/land/aux. Complete original-shaped
 // PARTIAL father naturally emits all 548 original
 // mnemonic, width and GPR roles; whole 82KB NONEXACT.
// F1016 original Japanese fighter 004AC040 action 2DB genuine gameplay.
case 0x2DB: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF06)=0;
        POS5C=0.2f;
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
        POS54=float(RandAt455580(0,30)-15);
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
    if (S16(0x62)==15 || S16(0x62)==16) {
        if (S16(0xF00)<2) {
            if (U8(0x11)>40)
                U8(0x11)=U8(0x11)-40;
            else {
                U8(0x11)=0;
                if (S16(0xF00)<3) {
                    SetAuxActionAt40FB40(8);
                    break;
                }
            }
        }
    }
    if (S16(0x62)==18 || S16(0x62)==19) {
        POS54=POS54-POS5C;
        if (U8(0x11)<235)
            U8(0x11)=U8(0x11)+20;
        else {
            U8(0x11)=255;
            SetAuxActionAt40FB40(20);
        }
    }
    if (S16(0x62)==20 || S16(0x62)==21) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            U8(0x11)=255;
            ResetAt453E20();
            SetAuxActionAt40FB40(22);
            POS48=0.0f;
            break;
        }
    }
    if (S16(0x62)<8 && S16(0x62)>1)
        SpawnSevenFloatAt453B50(0x33E,
            float(RandAt455580(0,120))+F32(0x44)-g_F983_XOffsetAt00658264,
            ((*(&POS48))-g_F983_YOffsetAt00657CBC)+float(RandAt455580(0,90)),
            1,1,0,1);
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
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
    if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF02)<4) {
        SetAuxActionAt40FB40(6);
        ++S16(0xF02);
        break;
    }
    if (S16(0x62)==9 && S16(0x64)==0) {
        POS=0.0f;
        POS54=0.0f;
    }
    if (S16(0x62)==11 && S16(0x64)==0) {
        ++S16(0xF00);
        S16(0xF06)=0;
        int shot;
        for (shot=0;shot<360;shot+=10) {
            F32(0x314)=float(shot);
            F32(0x318)=5.0f;
            SpawnFloatXYAt453A70(0x385,
                reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                    float((*reinterpret_cast<signed char*>(RAW+0x66))*8),
                (*(&POS48))+g_F1016_RingYAt00659460,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
        }
        for (shot=0;shot<360;shot+=10) {
            F32(0x314)=float(shot);
            F32(0x318)=10.0f;
            SpawnFloatXYAt453A70(0x385,
                reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                    float((*reinterpret_cast<signed char*>(RAW+0x66))*8),
                (*(&POS48))+g_F1016_RingYAt00659460,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
        }
    }
    if (S16(0x62)==17 && S16(0x64)==0 && S16(0xF06)<6) {
        SetAuxActionAt40FB40(15);
        ++S16(0xF06);
    }
    if (S16(0x62)==20 && S16(0x64)==0)
        SetAuxActionAt40FB40(18);
    if (S16(0x62)==22 && S16(0x64)==0)
        SetAuxActionAt40FB40(20);
    break;
}
