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
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        S16(0x516)=240-g_ReimuRepeatSettingAt006714D0*30;
    }
    if (S16(0x62)==8 && S16(0x64)==0) {
        SpawnFloatXAt453A70(0x38E,(*(&F32(0x44)))+g_ThresholdAt0065782C+g_ThresholdAt0065782C,
            I32(0x48),*reinterpret_cast<char*>(RAW+0x66),1);
        PlaySoundAt453D40(7);
        S16(0x516)=180;
    }
    if (S16(0x62)==12 && S16(0x64)==0 && S16(0xF00)<1) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(10);
    }
    if (S16(0x62)==14 && S16(0x64)==0 && S16(0xF02)<1) {
        ++S16(0xF02);
        SetAuxActionAt40FB40(12);
    }
    break;
}
