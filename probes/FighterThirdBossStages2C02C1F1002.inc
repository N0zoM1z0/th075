// F1002 pinned Japanese TH075 original 004AC040 2C0 and 2C1.
 // Real original 2C0=498B/135x86/14 external PE fields;
 // 2C1=522B/141x86/14 PE fields. True 453B50 mixed raw-X
 // float-Y argument ABI and later fixed 640/320 screen effect.
 // Real 2C1 stage>=5 sets F0C=180; distinct F02<4,
 // initial0x32F, fixed0x32E; original 2C0 F02<1,
 // initial0x332, fixed0x330; native ordered 453E80,
 // 453D40, 453D60 calls are different in each.
 // Both entire source cases compile with 0 wrong original
 // mnemonic/width AND GPR roles, but whole 82KB NONEXACT.
// F1002 original Japanese 004AC040 action 2C0
case 0x2C0: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    SpawnSevenRawXFloatYAt453B50(0x332,I32(0x44),
        (*(&POS48))+g_ContactProjectionAt00657888,
        1,1,0,1);
    if (S16(0x62)==5 && S16(0x64)==0) {
        if (S16(0xF02)<1) {
            ++S16(0xF02);
            SetAuxActionAt40FB40(3);
            break;
        }
        ApplyAt453E80(0x64);
        PrepareActionAt453D60(0x17);
        PrepareActionAt453D40(9);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x73,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*18),
            (*(&POS48))+g_F972_YAt00659284,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnSevenFloatAt453B50(0x330,640.0f,320.0f,1,2,0,1);
        S16(0xF10)=S16(0x3B0);
        S16(0xF12)=1;
    }
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<4) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(9);
    }
    break;
}
// F1002 original Japanese 004AC040 action 2C1
case 0x2C1: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (S16(0x62)>=5)
        S16(0xF0C)=180;
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    SpawnSevenRawXFloatYAt453B50(0x32F,I32(0x44),
        (*(&POS48))+g_ContactProjectionAt00657888,
        1,1,0,1);
    if (S16(0x62)==5 && S16(0x64)==0) {
        if (S16(0xF02)<4) {
            ++S16(0xF02);
            SetAuxActionAt40FB40(3);
            break;
        }
        ApplyAt453E80(0x28);
        PrepareActionAt453D40(0xA);
        PrepareActionAt453D60(0x17);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x73,
            reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
                - float((*reinterpret_cast<signed char*>(RAW+0x66))*18),
            (*(&POS48))+g_F972_YAt00659284,
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        SpawnSevenFloatAt453B50(0x32E,640.0f,320.0f,1,2,0,1);
        S16(0xF0C)=S16(0x3B0);
        S16(0xF0E)=0;
    }
    if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<4) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(9);
    }
    break;
}
