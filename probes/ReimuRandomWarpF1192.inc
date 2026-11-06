case 0x2EF: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        ResetAt453E20();
        S16(0x80)=1; I32(0x7C)=0; FLAG=0; S16(0xF00)=0;
    }
#define R1188_FADE_STAGE 1
#define R1188_RETURN_STAGE 3
#include "ReimuChargeTransformF1188.inc"
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
    if (POS48>g_ThresholdAt0065782C && S16(0x62)<14) {
        POS54=POS54-g_ReimuAirDragAt00658348;
        if (POS48+POS54<g_ThresholdAt0065782C) {
            POS48=0.0f; POS=0.0f; POS54=0.0f;
            SetAuxActionAt40FB40(14);
            break;
        }
    }
    if (S16(0xF00)<g_ReimuRepeatSettingAt006714D0*2+3 && S16(0x64)==0 &&
        (S16(0x62)==7 || S16(0x62)==8)) {
        ++S16(0xF00);
        PlaySoundAt453D40(12);
        F32(0x314)=float(S16(0xF00));
        SpawnFloatXYAt453A70(0x394,float(*reinterpret_cast<signed char*>(RAW+0x66)*80)+F32(0x44),
            (*(&POS48))+g_ReimuCommandBackYAt006590A8,*reinterpret_cast<char*>(RAW+0x66),1);
        S16(0x516)=120;
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=SelectRangeAt455580(0,60)+120-g_ReimuRepeatSettingAt006714D0*40;
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        F32(0x44)=((*(&*reinterpret_cast<float*>(OWNER+0x44)))+g_ReimuWarpSpreadAt006583B4)-float(SelectRangeAt455580(0,2000));
        POS48=200.0f;
        POS=g_ReimuWarpSpeedAt00657CF8-float(SelectRangeAt455580(0,6));
        POS54=6.0f;
        PlaySoundAt453D40(2);
        if (*reinterpret_cast<float*>(RAW+0x44)>*reinterpret_cast<float*>(OWNER+0x44))
            *reinterpret_cast<signed char*>(RAW+0x66)=-1;
        else *reinterpret_cast<signed char*>(RAW+0x66)=1;
    }
    if (S16(0x62)==9 && S16(0x64)==0 && S16(0xF00)<6) SetAuxActionAt40FB40(7);
    if (S16(0x62)==14 && S16(0x64)==0) SetAuxActionAt40FB40(12);
    break;
}
