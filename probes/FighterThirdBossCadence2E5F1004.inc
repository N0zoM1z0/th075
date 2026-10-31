// F1004 original Japanese TH075 004AC040 native state2E5.
 // Complete original 004BD017..004BD314 765B/199x86, 14
 // actual typed PE targets. Mode signed BYTE 006714D0,
 // F02*5 two real 0x387 shots with native FILD/FSUBR X,
 // different Y global 0065836C, signed F06 cadence, F08
 // mode budget, randomized native 516 and late phase13 retry.
 // All 199 original mnemonic/width/GPR roles naturally match
 // in incomplete 82KB parent. Parent original EBP/frame
 // still not native: entire callable NONEXACT.
// F1004 original Japanese 004AC040 2E5 native dual projectile cadence
case 0x2E5: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF06)=0;
        S16(0xF08)=g_F1004_ModeAt006714D0+2;
    }
    if (S16(0x62)>4 && S16(0x62)<11 && S16(0xF08)>0) {
        --S16(0xF06);
        if (S16(0xF06)>3-g_F1004_ModeAt006714D0) {
            F32(0x314)=float(S16(0xF02)*5);
            SpawnFloatXYAt453A70(0x387,
                reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                    float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                (*(&POS48))+g_F972_YAt0065836C,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
            F32(0x314)=float(S16(0xF02)*5+180);
            SpawnFloatXYAt453A70(0x387,
                reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                    float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
                (*(&POS48))+g_F972_YAt0065836C,
                *reinterpret_cast<signed char*>(RAW+0x66),1);
            ++S16(0xF02);
        }
        if (S16(0xF06)<=0 && S16(0xF06)<-30) {
            S16(0xF06)=10;
            --S16(0xF08);
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    S16(0x516)=static_cast<short>(
        RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    if (S16(0x62)==4 && S16(0x64)==0)
        S16(0xF06)=10;
    if (S16(0x62)==5 && S16(0x64)==0)
        PrepareActionAt453D40(5);
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF08)>0)
        SetAuxActionAt40FB40(9);
    if (S16(0x62)==13 && S16(0x64)==0) {
        ++S16(0xF04);
        if (S16(0xF04)<13)
            SetAuxActionAt40FB40(11);
    }
    break;
}
