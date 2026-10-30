// F759 real original game action 0xC8..0xCB, all under the same 00543210 giant.
// These are switch-case interiors, not individually accepted callable CODE.
case 0xC8: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        S16(0xF00)=0;
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<7) {
        POS54=POS54-g_F759_C8DecelAt006593E8;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(7);
            break;
        }
    }
    if (S16(0x62)==7 && I32(0x4E0)<0) {
        if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
            SetNativeActionAt40FAC0(0xCD);
            break;
        }
        SetNativeActionAt40FAC0(0xCC);
        break;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        break;
    }
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=15.0f;
        POS54=25.0f;
        POS5C=2.5f;
        SpawnAt453C80(0x7D,float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnRawXYAt453C80(0x81,I32(0x44),0,(*reinterpret_cast<signed char*>(RAW+0x66)),0);
        PrepareActionAt453D60(31);
    }
    break;
}
case 0xC9: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) {
        POS=0.0f;
        S16(0xF00)=0;
    }
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<6) {
        POS54=POS54-g_F759_C9DecelAt00658290;
        if (POS48+POS54<=g_ThresholdAt0065782C) {
            POS48=0.0f;
            ResetAt453E20();
            SetAuxActionAt40FB40(6);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        break;
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=-25.0f;
        POS54=40.0f;
        POS5C=6.0f;
        SpawnAt453C80(0x7D,reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*80),
            (*(&POS48))+g_F701_VolleyYAt00658268,-(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_F701_VolleyYAt00658268,-(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnRawXYAt453C80(0x81,I32(0x44),0,-(*reinterpret_cast<signed char*>(RAW+0x66)),0);
        PrepareActionAt453D60(31);
    }
    break;
}
case 0xCA: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) ResetAt453E20();
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>5) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f;
            POS54=0.0f;
            POS5C=0.0f;
            POS48=0.0f;
            S16(0x64)=0;
            SetNativeActionAt40FAC0(0xA);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==4 && S16(0x64)==0) {
        POS=30.0f;
        POS54=-4.0f;
        POS5C=0.6f;
        SpawnAt453C80(0x7D,float((*reinterpret_cast<signed char*>(RAW+0x66))*80)+F32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    if (S16(0x62)==6 && S16(0x64)==0) {
        POS=10.0f;
        POS54=-4.0f;
    }
    break;
}
case 0xCB: {
    ConfigureStormAt454BC0(3,4,0xFF);
    if (S16(0x62)==0 && S16(0x64)==0) ResetAt453E20();
    if (POS48>g_ThresholdAt0065782C && S16(0x62)>4) {
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            POS=0.0f;
            POS54=0.0f;
            POS5C=0.0f;
            POS48=0.0f;
            S16(0x64)=0;
            SetNativeActionAt40FAC0(0xA);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(9);
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=-30.0f;
        POS54=2.0f;
        POS5C=0.6f;
        SpawnAt453C80(0x7D,reinterpret_cast<FighterBorrowedXViewF752*>(this)->xAt44-float((*reinterpret_cast<signed char*>(RAW+0x66))*80),
            (*(&POS48))+g_ContactProjectionAt00657888,-(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        SpawnMixedAt453C80(0x7E,I32(0x44),
            (*(&POS48))+g_ContactProjectionAt00657888,-(*reinterpret_cast<signed char*>(RAW+0x66)),1);
        PrepareActionAt453D60(31);
    }
    if (S16(0x62)==5 && S16(0x64)==0) {
        POS=-10.0f;
        POS54=2.0f;
    }
    break;
}
