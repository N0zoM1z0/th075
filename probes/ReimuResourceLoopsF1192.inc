case 0x303: {
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0; field07C=1;
        ResetAt453E20();
    }
    reinterpret_cast<int&>(field490)=0;
    reinterpret_cast<int&>(opponent->field490)=0;
    if ((animationStage)<15 && y>g_ThresholdAt0065782C) velocityY=velocityY-field05C;
    if ((animationStage)>14) fieldF26=(fieldF26)+5;
    if (GetNativeActionAt40FA30()==(field070)) {
        if ((reinterpret_cast<signed short&>(scriptCounterF00))<8) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            SetAuxActionAt40FB40(15);
            reinterpret_cast<char&>(field3CF)=1;
            break;
        }
        SetNativeActionAt40FAC0(0x304);
        break;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=(g_ReimuArenaCenterAt00657884-x)/g_AngleShiftAt00657878*
            (facing);
        velocityY=12.0f; field05C=0.5f;
        reinterpret_cast<int&>(field490)=0;
        reinterpret_cast<int&>(opponent->field490)=0;
    }
    if ((animationStage)==13 && (animationFrame)==0) ResetAt453E20();
    if ((animationStage)==15 && (animationFrame)==0) {
        BeginFadeParametersAt454A70(0);
        SelectResourceParametersAt452B30();
        PrepareActionAt453D60(0x17);
        aiCardTimer=0;
        field318=0.0f;
        SpawnWithFloatAt453A70(0x3A4,reinterpret_cast<int&>(x),(*(&y))+g_ContactProjectionAt00657888,1,1);
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
    if ((animationStage)==0 && (animationFrame)==0) {
        field07C=1; ResetAt453E20(); reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (opponent->health>0 && opponent->animationStage==2 &&
        opponent->field39D>0 && opponent->action==0x63) {
        reinterpret_cast<ReimuFighter*>(opponent)->SetNativeActionAt40FAC0(0x5F);
        reinterpret_cast<char&>(opponent->field3CF)=1;
        break;
    }
    ++reinterpret_cast<signed short&>(scriptCounterF00);
    if ((reinterpret_cast<signed short&>(scriptCounterF00))>300-(10000-(health)*2)/100-g_ReimuRepeatSettingAt006714D0*30) {
        for (int burstOuter=0; burstOuter<30; ++burstOuter) {
            field314=float(burstOuter*12);
            field318=60.0f;
            SpawnWithFloatAt453A70(0x3A1,reinterpret_cast<int&>(x),(*(&y))+g_ContactProjectionAt00657888,1,1);
        }
        if (g_ReimuRepeatSettingAt006714D0>1) {
            for (int burstInner=0; burstInner<30; ++burstInner) {
                field314=float(burstInner*12);
                field318=100.0f;
                SpawnWithFloatAt453A70(0x3A2,reinterpret_cast<int&>(x),(*(&y))+g_ContactProjectionAt00657888,1,1);
            }
        }
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    reinterpret_cast<int&>(field490)=0;
    reinterpret_cast<int&>(opponent->field490)=0;
    if (GetNativeActionAt40FA30()==(field070)) SetAuxActionAt40FB40(1);
    break;
}
