// F1001 native original Japanese TH075 004AC040 actual 2BC/2BD.
 // 2BC 755B/199x86, 2BD 742B/196x86, 15 genuine PE fields
 // each. Correct stage3 original sprite0x73/0x74, real
 // 00453E80(0x28), action0x17, FILD/FSUBR signed facing
 // and actual initial Y PE global00659284, later pair Y0065836C. Stage4..10 2x 0x323/0x32B shots
 // with limit36/72; native 2BD writes short F14=1 while
 // 2BC updates F04. Native stage5 prep5/6; stage11 aux9.
 // Entire PARTIAL father produces all original mnemonics,
 // 2BC widths fully align, 2BD one original ADD width at
 // local ordinal133 remains nonnative, GPR roles differ.
// F1001 original SHA-pinned Japanese 004AC040 action 0x2BC
case 0x2BC: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF06)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        ApplyAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x73,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*18),
            (*(&POS48))+g_F972_YAt00659284,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0xF04)>0)
        --S16(0xF04);
    if (S16(0x62)>4 && S16(0x62)<11 && S16(0xF04)==0 && S16(0xF02)<36) {
        StartAnimationAt46D000(0xA);
        F32(0x314)=float(S16(0xF02)*5);
        SpawnFloatXYAt453A70(0x323,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
            (*(&POS48))+g_F972_YAt0065836C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*5+180);
        SpawnFloatXYAt453A70(0x323,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
            (*(&POS48))+g_F972_YAt0065836C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        ++S16(0xF02);
        ++S16(0xF04);
    }
    if (S16(0x62)==5 && S16(0x64)==0)
        PrepareActionAt453D40(5);
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF06)<5) {
        SetAuxActionAt40FB40(9);
        ++S16(0xF06);
    }
    break;
}
// F1001 original SHA-pinned Japanese 004AC040 action 0x2BD
case 0x2BD: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        I32(0x7C)=1;
        ResetAt453E20();
        S16(0xF00)=0;
        S16(0xF02)=0;
        S16(0xF04)=0;
        S16(0xF06)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==3 && S16(0x64)==0) {
        ApplyAt453E80(0x28);
        PrepareActionAt453D60(0x17);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x74,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*18),
            (*(&POS48))+g_F972_YAt00659284,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
    }
    if (S16(0xF04)>0)
        --S16(0xF04);
    if (S16(0x62)>4 && S16(0x62)<11 && S16(0xF04)==0 && S16(0xF02)<72) {
        S16(0xF14)=1;
        StartAnimationAt46D000(0xA);
        F32(0x314)=float(S16(0xF02)*5);
        SpawnFloatXYAt453A70(0x32B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
            (*(&POS48))+g_F972_YAt0065836C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        F32(0x314)=float(S16(0xF02)*5+180);
        SpawnFloatXYAt453A70(0x32B,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*16),
            (*(&POS48))+g_F972_YAt0065836C,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        ++S16(0xF02);
    }
    if (S16(0x62)==5 && S16(0x64)==0)
        PrepareActionAt453D40(6);
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF06)<5) {
        SetAuxActionAt40FB40(9);
        ++S16(0xF06);
    }
    break;
}
