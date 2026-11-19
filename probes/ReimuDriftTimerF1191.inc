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
    if (AdvanceNestedFrame()==(field070)) {
        SetNativeActionAt40FAC0(0);
        aiCardTimer=240-g_ReimuRepeatSettingAt006714D0*30;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        SpawnFloatXAt453A70(0x38E,(*(&x))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            reinterpret_cast<int&>(y),reinterpret_cast<char&>(facing),1);
        PlaySound(7);
        aiCardTimer=180;
    }
    if ((animationStage)==12 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(10);
    }
    if ((animationStage)==14 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF02))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF02);
        SetAuxActionAt40FB40(12);
    }
    break;
}
