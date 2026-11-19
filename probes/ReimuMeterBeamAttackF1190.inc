case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if ((animationStage)==6 && (animationFrame)==0) {
        SetNonnegativeWord(40);
        PlaySharedSound(0x17);
        SpawnAuxEffect(R1190_AUX_EFFECT,float(facing*7)+(x),
            (*(&y))+g_ReimuMeterNearYAt00659088,reinterpret_cast<char&>(facing),1);
        field36C=(field36C)-g_ContactProjectionAt00657888;
    }
    if ((animationStage)==10 || (animationStage)==11) UpdateGaugeTimer(5);
    if (AdvanceNestedFrame()==(field070)) ResetPrimaryCounters(0);
    if ((animationStage)==8 && (animationFrame)==0) {
        Fighter::SpawnBattleEffect(R1190_EFFECT,(*(&x))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            y,facing,1);
        PlaySound(R1190_SOUND);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<10) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        ResetSecondaryCounter(10);
    }
    if ((animationStage)==14 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<5) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        ResetSecondaryCounter(12);
    }
    break;
}
