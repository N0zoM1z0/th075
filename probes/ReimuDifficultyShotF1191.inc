case 0x2F9: {
#include "ReimuMeterInitF1190.inc"
    if (GetNativeActionAt40FA30()==(field070)) {
        SetNativeActionAt40FAC0(0);
        aiCardTimer=240-g_ReimuRepeatSettingAt006714D0*20;
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        if (g_ReimuRepeatSettingAt006714D0<2) {
            SpawnFloatXYAt453A70(0x395,float(facing*228)+(x),
                (*(&y))+g_ReimuMeterShotYAt00659080,reinterpret_cast<char&>(facing),1);
        } else {
            SpawnFloatXYAt453A70(0x396,float(facing*228)+(x),
                (*(&y))+g_ReimuMeterShotYAt00659080,reinterpret_cast<char&>(facing),1);
        }
        PlaySoundAt453D40(8);
    }
    break;
}
