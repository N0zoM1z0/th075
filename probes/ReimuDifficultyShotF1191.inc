case 0x2F9: {
#include "ReimuMeterInitF1190.inc"
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        aiCardTimer=240-g_ReimuRepeatSettingAt006714D0*20;
    }
    if ((animationStage)==7 && (animationFrame)==0) {
        if (g_ReimuRepeatSettingAt006714D0<2) {
            SpawnBattleEffect(0x395,float(facing*228)+(x),
                (*(&y))+g_ReimuMeterShotYAt00659080,facing,1);
        } else {
            SpawnBattleEffect(0x396,float(facing*228)+(x),
                (*(&y))+g_ReimuMeterShotYAt00659080,facing,1);
        }
        PlaySound(8);
    }
    break;
}
