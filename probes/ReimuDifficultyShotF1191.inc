case 0x2F9: {
#include "ReimuMeterInitF1190.inc"
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=240-g_ReimuRepeatSettingAt006714D0*20;
    }
    if (S16(0x62)==7 && S16(0x64)==0) {
        if (g_ReimuRepeatSettingAt006714D0<2) {
            SpawnFloatXYAt453A70(0x395,float(*reinterpret_cast<signed char*>(RAW+0x66)*228)+F32(0x44),
                (*(&POS48))+g_ReimuMeterShotYAt00659080,*reinterpret_cast<char*>(RAW+0x66),1);
        } else {
            SpawnFloatXYAt453A70(0x396,float(*reinterpret_cast<signed char*>(RAW+0x66)*228)+F32(0x44),
                (*(&POS48))+g_ReimuMeterShotYAt00659080,*reinterpret_cast<char*>(RAW+0x66),1);
        }
        PlaySoundAt453D40(8);
    }
    break;
}
