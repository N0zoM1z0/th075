#define R1191_ACTION 0x2DF
#define R1191_AUX 10
#define R1191_REVERSE_X 0
#define R1191_LIFT_RANGE 4
#include "ReimuRandomDriftF1191.inc"
#undef R1191_ACTION
#undef R1191_AUX
#undef R1191_REVERSE_X
#undef R1191_LIFT_RANGE
#define R1191_ACTION 0x2E0
#define R1191_AUX 8
#define R1191_REVERSE_X 1
#define R1191_LIFT_RANGE 3
#include "ReimuRandomDriftF1191.inc"
#undef R1191_ACTION
#undef R1191_AUX
#undef R1191_REVERSE_X
#undef R1191_LIFT_RANGE
case 0x2E5: {
#include "ReimuMeterInitF1190.inc"
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        aiCardTimer=240-g_OptionsModeAt006714D0*30;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        Fighter::SpawnBattleEffect(0x38E,(*(&x))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            y,facing,1);
        PlaySound(7);
        aiCardTimer=180;
    }
    if ((animationStage)==12 && (animationFrame)==0 && (scriptCounterF00)<1) {
        ++scriptCounterF00;
        ResetSecondaryCounter(10);
    }
    if ((animationStage)==14 && (animationFrame)==0 && (scriptCounterF02)<1) {
        ++scriptCounterF02;
        ResetSecondaryCounter(12);
    }
    break;
}
