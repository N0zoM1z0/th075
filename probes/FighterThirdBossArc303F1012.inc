// F1012 pinned Japanese TH075 original 004AC040 action303.
 // Original 004BFDAB..004C01A1: 1014 CODE B/267 x86
 // with 29 actual external PE fields. Genuine C++ cast
 // short(POS/global), native borrowed opponent-X FIMUL,
 // signed-short F04+=F06 recovers all original 267
 // mnemonic and GPR roles and all widths except final
 // shared-parent tail JMP original 5B vs source2B.
 // Correct original decl-only math call 00483300
 // returns x87 ST0; original 40FB70 gets two float args.
 // Natural 303 source repairs preceding 302 final JMP width.
 // Whole original 82KB callable remains NONEXACT.
// F1012 original Japanese game fighter 004AC040 state303.
case 0x303: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        if (RandAt455580(0,100)>50)
            S16(0xF06)=5;
        else
            S16(0xF06)=-5;
    }
    if (S16(0x62)<9 && POS48>=g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS54<=g_AnimationDeltaAt0065747C)
            POS54=1.0f;
    }
    if (S16(0x62)>8 && POS48>=g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(11);
        }
    }
    if (S16(0x62)==7 || S16(0x62)==8) {
        if (S16(0x64)==0) {
            ++S16(0xF00);
            if (S16(0xF00)<g_F1004_ModeAt006714D0*5+10) {
                PrepareActionAt453D40(0);
                S16(0xF02)=static_cast<short>(POS*g_ContactProjectionAt00657888);
                S16(0xF08)=static_cast<short>(F32(0x54)*g_ContactProjectionAt00657888);
                F32(0x314)=float(S16(0xF04));
                F32(0x318)=10.0f;
                SetAngleAt40FB70(float(S16(0xF04)),100.0f);
                SpawnFloatXYAt453A70(0x388,
                    float(*reinterpret_cast<signed char*>(RAW+0x66))*POS+F32(0x44),
                    (*(&POS48))+g_F1012_ArcYAt006591EC-POS54,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                POS=float(S16(0xF02))*g_F747_BounceYAt00658044;
                POS54=float(S16(0xF08))*g_F747_BounceYAt00658044;
                S16(0xF04)+=S16(0xF06);
            }
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=static_cast<short>(
            RandAt455580(60,120)-g_F1004_ModeAt006714D0*20);
    }
    if (S16(0x62)==6 && S16(0x64)==0) {
        POS=0.0f;
        POS54=6.5f;
        POS5C=0.25f;
    }
    if (S16(0x62)==7 && S16(0x64)==0) {
        S16(0xF04)=static_cast<short>(
            F1012_AngleAt00483300(
                -((*reinterpret_cast<float*>(OWNER+0x48))+
                    g_ContactProjectionAt00657888-POS48+
                    g_F1012_ArcYAt006591EC),
                (reinterpret_cast<const FighterBorrowedXViewF752*>(OWNER)->xAt44 -
                    reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44) *
                    (*reinterpret_cast<signed char*>(RAW+0x66)))/
                g_F1012_AngleDivisorAt00657828);
    }
    if (S16(0x62)==9 && S16(0x64)==0 && S16(0xF00)<25)
        SetAuxActionAt40FB40(7);
    break;
}
