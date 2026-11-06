case 0x2DB: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0; S16(0xF02)=0; I32(0x7C)=1;
        if (POS48==g_ThresholdAt0065782C) ResetAt453E20();
        else {
            POS=POS*g_ReimuAirDragAt00658348;
            POS54=(*(&POS54))*g_ReimuAirDragAt00658348;
        }
    }
    if (POS48>g_ThresholdAt0065782C) {
        if (S16(0x62)<12) {
            POS54=POS54-g_ReimuStormFallAt00658044;
            if (POS48+POS54<=g_ThresholdAt0065782C) POS=0.0f;
        } else {
            POS54=POS54-POS5C;
            if (POS48+POS54<=g_ThresholdAt0065782C && S16(0x62)<16) {
                POS48=0.0f;
                ResetAt453E20();
                SetAuxActionAt40FB40(16);
                break;
            }
        }
    }
    if (S16(0x62)==10 && S16(0x64)==0 && S16(0xF00)<g_ReimuRepeatSettingAt006714D0*3+4) {
        PlaySoundAt453D40(6);
        F32(0x314)=float(SelectRangeAt455580(0,359));
        if (S16(0xF02)==0) {
            SpawnFloatXYAt453A70(0x384,float(*reinterpret_cast<signed char*>(RAW+0x66)*18)+F32(0x44),
                (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
            F32(0x314)=float(SelectRangeAt455580(0,359));
        }
        if (S16(0xF02)==1) {
            SpawnFloatXYAt453A70(0x385,float(*reinterpret_cast<signed char*>(RAW+0x66)*18)+F32(0x44),
                (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
            F32(0x314)=float(SelectRangeAt455580(0,359));
        }
        if (S16(0xF02)==2) {
            SpawnFloatXYAt453A70(0x386,float(*reinterpret_cast<signed char*>(RAW+0x66)*18)+F32(0x44),
                (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
            F32(0x314)=float(SelectRangeAt455580(0,359));
        }
        ++S16(0xF02);
        if (S16(0xF02)>2) S16(0xF02)=0;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=300-g_ReimuRepeatSettingAt006714D0*20;
    }
    if (S16(0x62)==4 && S16(0x64)==0) {
        SpawnTrackedAt453B50(0x3B6,(*(&F32(0x44)))+g_ThresholdAt0065782C,
            (*(&POS48))+g_ReimuMeterTrailYAt0065835C,*reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
    }
    if (S16(0x62)==12 && S16(0x64)==0 && S16(0xF00)<30) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(10);
    }
    if (S16(0x62)==15 && S16(0x64)==0 && POS48==g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        break;
    }
    if (S16(0x62)==16 && S16(0x64)==0) SetAuxActionAt40FB40(14);
    break;
}
