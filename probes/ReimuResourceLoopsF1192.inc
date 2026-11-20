case 0x303: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0; field07C=1;
        ClearMotionFields();
    }
    field490=0.0f;
    opponent->field490=0.0f;
    if ((animationStage)<15 && y>g_ThresholdAt0065782C) velocityY=velocityY-field05C;
    if ((animationStage)>14) fieldF26=(fieldF26)+5;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        if ((scriptCounterF00)<8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(15);
            field3CF=1;
            break;
        }
        ResetPrimaryCounters(0x304);
        break;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=(g_ReimuArenaCenterAt00657884-x)/g_AngleShiftAt00657878*
            (facing);
        velocityY=12.0f; field05C=0.5f;
        field490=0.0f;
        opponent->field490=0.0f;
    }
    if ((animationStage)==13 && (animationFrame)==0) ClearMotionFields();
    if ((animationStage)==15 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
        aiCardTimer=0;
        field318=0.0f;
        SpawnBattleEffect(0x3A4,x,(*(&y))+g_ContactProjectionAt00657888,1,1);
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
        field07C=1; ClearMotionFields(); scriptCounterF00=0;
    }
    if (opponent->health>0 && opponent->animationStage==2 &&
        opponent->field39D>0 && opponent->action==0x63) {
        reinterpret_cast<ReimuFighter*>(opponent)->ResetPrimaryCounters(0x5F);
        opponent->field3CF=1;
        break;
    }
    ++scriptCounterF00;
    if ((scriptCounterF00)>300-(10000-(health)*2)/100-g_ReimuRepeatSettingAt006714D0*30) {
        for (int burstOuter=0; burstOuter<30; ++burstOuter) {
            field314=float(burstOuter*12);
            field318=60.0f;
            SpawnBattleEffect(0x3A1,x,(*(&y))+g_ContactProjectionAt00657888,1,1);
        }
        if (g_ReimuRepeatSettingAt006714D0>1) {
            for (int burstInner=0; burstInner<30; ++burstInner) {
                field314=float(burstInner*12);
                field318=100.0f;
                SpawnBattleEffect(0x3A2,x,(*(&y))+g_ContactProjectionAt00657888,1,1);
            }
        }
        scriptCounterF00=0;
    }
    field490=0.0f;
    opponent->field490=0.0f;
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(1);
    break;
}
