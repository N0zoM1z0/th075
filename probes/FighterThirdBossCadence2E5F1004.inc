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
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
        reinterpret_cast<signed short&>(scriptCounterF02)=0;
        reinterpret_cast<signed short&>(fieldF04)=0;
        reinterpret_cast<signed short&>(fieldF06)=0;
        reinterpret_cast<signed short&>(fieldF08)=g_F1004_ModeAt006714D0+2;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>4 && (reinterpret_cast<signed short&>(animationStage))<11 && (reinterpret_cast<signed short&>(fieldF08))>0) {
        --reinterpret_cast<signed short&>(fieldF06);
        if ((reinterpret_cast<signed short&>(fieldF06))>3-g_F1004_ModeAt006714D0) {
            field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*5);
            SpawnFloatXYAt453A70(0x387,
                reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                    float((facing)*16),
                (*(&y))+g_F972_YAt0065836C,
                facing,1);
            field314=float((reinterpret_cast<signed short&>(scriptCounterF02))*5+180);
            SpawnFloatXYAt453A70(0x387,
                reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44 -
                    float((facing)*16),
                (*(&y))+g_F972_YAt0065836C,
                facing,1);
            ++reinterpret_cast<signed short&>(scriptCounterF02);
        }
        if ((reinterpret_cast<signed short&>(fieldF06))<=0 && (reinterpret_cast<signed short&>(fieldF06))<-30) {
            reinterpret_cast<signed short&>(fieldF06)=10;
            --reinterpret_cast<signed short&>(fieldF08);
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0);
        reinterpret_cast<signed short&>(aiCardTimer)=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0)
        reinterpret_cast<signed short&>(fieldF06)=10;
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0)
        PrepareActionAt453D40(5);
    if ((reinterpret_cast<signed short&>(animationStage))==11 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(fieldF08))>0)
        SetAuxActionAt40FB40(9);
    if ((reinterpret_cast<signed short&>(animationStage))==13 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        ++reinterpret_cast<signed short&>(fieldF04);
        if ((reinterpret_cast<signed short&>(fieldF04))<13)
            SetAuxActionAt40FB40(11);
    }
    break;
}
