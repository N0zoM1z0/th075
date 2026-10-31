// F982 original Japanese fighter 004AC040 real 1F6 and 1F7.
// Each physical native handler is 777B/215x86/22 typed PE fields.
// Native initial motion is scaled by true DOUBLE at 006583E0
// (1F6) or 006584C8 (1F7); native stage4 F00<2 vs F00<4.
// Normal VC7.1 partial father C++ matches ordered native mnemonic/
// width geometry; original GPR mismatch count 126 per state.
// Entire 82KB game fighter remains NONEXACT, not inner-case exact.
// F982 original native 004AC040 0x1F6 double-scaled fighter action
case 0x1F6: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=POS*g_F982_Scale1F6At006583E0;
        F32(0x54)=F32(0x54)*g_F982_Scale1F6At006583E0;
        S16(0x80)=99;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>3 && S16(0x62)<6) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(6);
            POS48=0.0f;
            break;
        }
    }
    if (I32(0x7C)!=0) {
        ++S16(0xF02);
        if (S16(0xF02)>6) {
            S16(0xF02)=0;
            I32(0x7C)=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        F32(0x314)=15.0f;
        F32(0x318)=-20.0f;
        F32(0x31C)=-60.0f;
        SpawnSevenFloatAt453B50(0x32A,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        F32(0x314)=10.0f;
        F32(0x318)=-135.0f;
        F32(0x31C)=-30.0f;
        SpawnSevenFloatAt453B50(0x32A,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        PrepareActionAt453D40(3);
    }
    if (S16(0x62)==4 && S16(0x64)==0 && S16(0xF00)<2) {
        SetAuxActionAt40FB40(2);
        ++S16(0xF00);
    }
    if (S16(0x62)==6 && S16(0x64)==0)
        SetAuxActionAt40FB40(5);
    break;
}
// F982 original native 004AC040 0x1F7 double-scaled fighter action
case 0x1F7: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=POS*g_F982_Scale1F7At006584C8;
        F32(0x54)=F32(0x54)*g_F982_Scale1F7At006584C8;
        S16(0x80)=99;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (S16(0x62)>3 && S16(0x62)<6) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(6);
            POS48=0.0f;
            break;
        }
    }
    if (I32(0x7C)!=0) {
        ++S16(0xF02);
        if (S16(0xF02)>6) {
            S16(0xF02)=0;
            I32(0x7C)=0;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    if (S16(0x62)==2 && S16(0x64)==0) {
        F32(0x314)=15.0f;
        F32(0x318)=-20.0f;
        F32(0x31C)=-60.0f;
        SpawnSevenFloatAt453B50(0x32A,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        F32(0x314)=10.0f;
        F32(0x318)=-135.0f;
        F32(0x31C)=-30.0f;
        SpawnSevenFloatAt453B50(0x32A,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        SpawnSevenFloatAt453B50(0x329,
            F32(0x44)+g_ThresholdAt0065782C,
            (*(&POS48))+g_F981_YAt00659270,
            *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
        PrepareActionAt453D40(3);
    }
    if (S16(0x62)==4 && S16(0x64)==0 && S16(0xF00)<4) {
        SetAuxActionAt40FB40(2);
        ++S16(0xF00);
    }
    if (S16(0x62)==6 && S16(0x64)==0)
        SetAuxActionAt40FB40(5);
    break;
}
