case 0x31B: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0; field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        BeginFadeParametersAt454A70(0);
        SelectResourceParametersAt452B30();
        PlaySharedSound(0x17);
        SpawnWithFloatAt453A70(0x3E5,reinterpret_cast<int&>(x),(*(&y))+g_ContactProjectionAt00657888,
            reinterpret_cast<char&>(facing),1);
    }
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(7);
    }
    break;
}
case 0x31C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0; field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(field070)) {
        SetNativeActionAt40FAC0(0);
        if (*reinterpret_cast<signed char*>(RAW+field39D+0x370)==4) {
            fieldF26=0; aiCardTimer=0; field318=0.0f;
            SpawnWithFloatAt453A70(0x3A3,reinterpret_cast<int&>(x),(*(&y))+g_ContactProjectionAt00657888,1,1);
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
    if ((animationStage)==20 && (animationFrame)==0) {
        BeginFadeParametersAt454A70(0);
        SelectResourceParametersAt452B30();
        PlaySharedSound(0x17);
    }
    if ((animationStage)==24 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<8) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(22);
        reinterpret_cast<char&>(field3CF)=1;
    }
    break;
}
