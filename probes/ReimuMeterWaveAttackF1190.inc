case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if ((animationStage)==0 && (animationFrame)==0) {
        SetNonnegativeWord(40);
        PlaySharedSound(0x17);
        SpawnAuxEffect(R1190_AUX_EFFECT,float(facing*24)+(x),
            (*(&y))+GeometryConstants::HundredFortyFour,facing,1);
        field36C=(field36C)-GeometryConstants::Hundred;
#if R1190_HAS_ANIMATION
        UpdateGaugeTimer(500);
#endif
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==7 && (animationFrame)==0) {
        SpawnBattleEffect(R1190_EFFECT,(*(&x))+GeometryConstants::Hundred+
            (facing*128),
            (*(&y))+g_ReimuMeterShotYAt00659080,facing,1);
        PlaySound(R1190_SOUND);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (scriptCounterF00)<R1190_LIMIT) {
        ++scriptCounterF00;
        ResetSecondaryCounter(10);
    }
    break;
}
