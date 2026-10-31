// F1003 pinned original Japanese 004AC040 fighter 2C2 and 2C3.
 // Original 2C2 515B/138x86/14 genuine typed PE targets,
 // original 2C3 522B/141x86/14 PE fields. Native source
 // recovers getter==frame unconditional sprite0x332 in branch
 // with short F12=1 and genuine BREAK/jump to shared tail.
 // 2C3 stage>5 F0C=300, true stage5 order 453E80(0x28)
 // then Prepare453D60(0x17), then Prepare453D40(0xA).
 // Both all mnemonic/width/GPR roles align under normal full
 // partial 82KB VC7.1 father source; whole giant NONEXACT.
// F1002 original Japanese 004AC040 action 2C0
case 0x2C2: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0xF12)=1;
        SpawnSevenRawXFloatYAt453B50(0x332,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,
            1,1,0,1);
        break;
    }
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
        SpawnAt453C80(0x74,
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
case 0x2C3: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0;
        S16(0xF02)=0;
        I32(0x7C)=0;
        ResetAt453E20();
        S16(0x80)=99;
    }
    if (S16(0x62)>5)
        S16(0xF0C)=300;
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
        PrepareActionAt453D60(0x17);
        PrepareActionAt453D40(0xA);
        F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
        SpawnAt453C80(0x74,
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
