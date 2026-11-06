case 0x303: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        S16(0xF00)=0; I32(0x7C)=1;
        ResetAt453E20();
    }
    I32(0x490)=0;
    *reinterpret_cast<int*>(OWNER+0x490)=0;
    if (S16(0x62)<15 && POS48>g_ThresholdAt0065782C) POS54=POS54-POS5C;
    if (S16(0x62)>14) S16(0xF26)=S16(0xF26)+5;
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        if (S16(0xF00)<8) {
            ++S16(0xF00);
            SetAuxActionAt40FB40(15);
            *reinterpret_cast<char*>(RAW+0x3CF)=1;
            break;
        }
        SetNativeActionAt40FAC0(0x304);
        break;
    }
    if (S16(0x62)==3 && S16(0x64)==0) {
        POS=(g_ReimuArenaCenterAt00657884-*reinterpret_cast<float*>(RAW+0x44))/g_AngleShiftAt00657878*
            (*reinterpret_cast<signed char*>(RAW+0x66));
        POS54=12.0f; POS5C=0.5f;
        I32(0x490)=0;
        *reinterpret_cast<int*>(OWNER+0x490)=0;
    }
    if (S16(0x62)==13 && S16(0x64)==0) ResetAt453E20();
    if (S16(0x62)==15 && S16(0x64)==0) {
        BeginFadeParametersAt454A70(0);
        SelectResourceParametersAt452B30();
        PrepareActionAt453D60(0x17);
        S16(0x516)=0;
        F32(0x318)=0.0f;
        SpawnWithFloatAt453A70(0x3A4,I32(0x44),(*(&POS48))+g_ContactProjectionAt00657888,1,1);
        if (g_ReimuRepeatSettingAt006714D0==0) {
#define R1192_INDEX shotEasy
#define R1192_COUNT 6
#define R1192_STEP 60
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
        }
        if (g_ReimuRepeatSettingAt006714D0==1) {
#define R1192_INDEX shotNormal
#define R1192_COUNT 6
#define R1192_STEP 60
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
        }
        if (g_ReimuRepeatSettingAt006714D0==2) {
#define R1192_INDEX shotHard
#define R1192_COUNT 8
#define R1192_STEP 45
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
        }
        if (g_ReimuRepeatSettingAt006714D0==3) {
#define R1192_INDEX shotLunatic
#define R1192_COUNT 8
#define R1192_STEP 45
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
        }
    }
    break;
}
case 0x304: {
    if (S16(0x62)==0 && S16(0x64)==0) {
        I32(0x7C)=1; ResetAt453E20(); S16(0xF00)=0;
    }
    if (*reinterpret_cast<short*>(OWNER+0x324)>0 && *reinterpret_cast<short*>(OWNER+0x62)==2 &&
        *reinterpret_cast<signed char*>(OWNER+0x39D)>0 && *reinterpret_cast<short*>(OWNER+0x60)==0x63) {
        reinterpret_cast<FighterSwitchF598_Boss0045DD70*>(OWNER)->SetNativeActionAt40FAC0(0x5F);
        *reinterpret_cast<char*>(OWNER+0x3CF)=1;
        break;
    }
    ++S16(0xF00);
    if (S16(0xF00)>300-(10000-S16(0x324)*2)/100-g_ReimuRepeatSettingAt006714D0*30) {
        for (int burstOuter=0; burstOuter<30; ++burstOuter) {
            F32(0x314)=float(burstOuter*12);
            F32(0x318)=60.0f;
            SpawnWithFloatAt453A70(0x3A1,I32(0x44),(*(&POS48))+g_ContactProjectionAt00657888,1,1);
        }
        if (g_ReimuRepeatSettingAt006714D0>1) {
            for (int burstInner=0; burstInner<30; ++burstInner) {
                F32(0x314)=float(burstInner*12);
                F32(0x318)=100.0f;
                SpawnWithFloatAt453A70(0x3A2,I32(0x44),(*(&POS48))+g_ContactProjectionAt00657888,1,1);
            }
        }
        S16(0xF00)=0;
    }
    I32(0x490)=0;
    *reinterpret_cast<int*>(OWNER+0x490)=0;
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(1);
    break;
}
