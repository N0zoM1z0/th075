// F981 native Japanese original fighter 004AC040 states 1F4 and 1F5.
// Both original game case interiors exactly 830B/232 x86 with
// 23 real typed PE/COFF external targets each. Original 1F5 stage7
// ordering sets drag AFTER raw 0x7F projectile, 1F4 sets it BEFORE.
// Four actual 0x32A/0x329 sprite shots at stage8; real x87 motion,
// 1F4 auxiliary stage10 F00<1 vs 1F5 F00<3. Natural VC7.1 source
// matches native x86 mnemonic/width geometry but 135 GPR roles each
// remain wrong in incomplete 82KB parent. No independent case exact.
// F981 true Japanese original 004AC040 action 0x1F4
case 0x1F4: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=99;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xC);
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
    if (S16(0x62)==7 && S16(0x64)==0) {
        POS=2.0f;
        POS54=6.5f;
        POS5C=0.4f;
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        PrepareActionAt453D40(3);
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
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
    }
    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<1) {
        SetAuxActionAt40FB40(8);
        ++S16(0xF00);
    }
    if (S16(0x62)==12 && S16(0x64)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
// F981 true Japanese original 004AC040 action 0x1F5
case 0x1F5: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=99;
        I32(0x7C)=0;
        FLAG=0;
        S16(0xF00)=0;
        S16(0xF02)=0;
    }
    if (POS48>g_ThresholdAt0065782C) {
        POS54=POS54-POS5C;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            ResetAt453E20();
            SetAuxActionAt40FB40(0xC);
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
    if (S16(0x62)==7 && S16(0x64)==0) {
        POS=8.0f;
        POS54=13.5f;
        SpawnRawAt453C80(0x7F,I32(0x44),I32(0x48),
            *reinterpret_cast<signed char*>(RAW+0x66),1);
        POS5C=0.5f;
        PrepareActionAt453D40(3);
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
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
    }
    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<3) {
        SetAuxActionAt40FB40(8);
        ++S16(0xF00);
    }
    if (S16(0x62)==12 && S16(0x64)==0)
        SetAuxActionAt40FB40(0xB);
    break;
}
