case 0x31B: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0; I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetNativeActionAt40FAC0(0);
    if (S16(0x62)==5 && S16(0x64)==0) {
        BeginFadeParametersAt454A70(0);
        SelectResourceParametersAt452B30();
        PrepareActionAt453D60(0x17);
        SpawnWithFloatAt453A70(0x3E5,I32(0x44),(*(&POS48))+g_ContactProjectionAt00657888,
            *reinterpret_cast<char*>(RAW+0x66),1);
    }
    if (S16(0x62)==9 && S16(0x64)==0 && S16(0xF00)<8) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(7);
    }
    break;
}
case 0x31C: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0; I32(0x7C)=1;
        ResetAt453E20();
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0);
        if (*reinterpret_cast<signed char*>(RAW+*reinterpret_cast<signed char*>(RAW+0x39D)+0x370)==4) {
            S16(0xF26)=0; S16(0x516)=0; F32(0x318)=0.0f;
            SpawnWithFloatAt453A70(0x3A3,I32(0x44),(*(&POS48))+g_ContactProjectionAt00657888,1,1);
            if (g_ReimuRepeatSettingAt006714D0==0) {
#define R1192_INDEX echoEasy
#define R1192_COUNT 6
#define R1192_STEP 60
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
            if (g_ReimuRepeatSettingAt006714D0==1) {
#define R1192_INDEX echoNormal
#define R1192_COUNT 6
#define R1192_STEP 60
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
            if (g_ReimuRepeatSettingAt006714D0==2) {
#define R1192_INDEX echoHard
#define R1192_COUNT 8
#define R1192_STEP 45
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
            if (g_ReimuRepeatSettingAt006714D0==3) {
#define R1192_INDEX echoLunatic
#define R1192_COUNT 8
#define R1192_STEP 45
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
        }
    }
    if (S16(0x62)==20 && S16(0x64)==0) {
        BeginFadeParametersAt454A70(0);
        SelectResourceParametersAt452B30();
        PrepareActionAt453D60(0x17);
    }
    if (S16(0x62)==24 && S16(0x64)==0 && S16(0xF00)<8) {
        ++S16(0xF00);
        SetAuxActionAt40FB40(22);
        *reinterpret_cast<char*>(RAW+0x3CF)=1;
    }
    break;
}
