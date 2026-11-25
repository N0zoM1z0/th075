case R1190_ACTION: {
#include "ReimuMeterInitF1190.inc"
    if ((animationStage)==6 && (animationFrame)==0) {
        SetNonnegativeWord(40);
        PlaySharedSound(0x17);
        SpawnAuxEffect(R1190_AUX_EFFECT,float(facing*7)+(x),
            (*(&y))+g_ReimuMeterNearYAt00659088,facing,1);
        spellPower=(spellPower)-GeometryConstants::Hundred;
    }
    if ((animationStage)==10 || (animationStage)==11) UpdateGaugeTimer(5);
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==8 && (animationFrame)==0) {
        Fighter::SpawnBattleEffect(R1190_EFFECT,(*(&x))+FloatConstants::Zero+FloatConstants::Zero,
            y,facing,1);
        PlaySound(R1190_SOUND);
    }
    if ((animationStage)==12 && (animationFrame)==0 && (scriptCounterF00)<10) {
        ++scriptCounterF00;
        ResetSecondaryCounter(10);
    }
    if ((animationStage)==14 && (animationFrame)==0 && (scriptCounterF02)<5) {
        ++scriptCounterF02;
        ResetSecondaryCounter(12);
    }
    break;
}
