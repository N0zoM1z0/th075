case 0x31B: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0; field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
        SpawnBattleEffect(0x3E5,x,(*(&y))+GeometryConstants::Hundred,
            facing,1);
    }
    if ((animationStage)==9 && (animationFrame)==0 && (scriptCounterF00)<8) {
        ++scriptCounterF00;
        ResetSecondaryCounter(7);
    }
    break;
}
case 0x31C: {
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0; field07C=1;
        ClearMotionFields();
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0);
        if (roundSpellVariants[roundsRemaining]==4) {
            fieldF26=0; aiCardTimer=0; field318=0.0f;
            SpawnBattleEffect(0x3A3,x,(*(&y))+GeometryConstants::Hundred,1,1);
            if (g_OptionsModeAt006714D0==0) {
#define R1192_INDEX echoEasy
#define R1192_COUNT 6
#define R1192_STEP 60
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
            if (g_OptionsModeAt006714D0==1) {
#define R1192_INDEX echoNormal
#define R1192_COUNT 6
#define R1192_STEP 60
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
            if (g_OptionsModeAt006714D0==2) {
#define R1192_INDEX echoHard
#define R1192_COUNT 8
#define R1192_STEP 45
#include "ReimuDifficultyRingF1192.inc"
#undef R1192_INDEX
#undef R1192_COUNT
#undef R1192_STEP
            }
            if (g_OptionsModeAt006714D0==3) {
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
        BeginFadeParameters(0);
        SelectResourceParameters();
        PlaySharedSound(0x17);
    }
    if ((animationStage)==24 && (animationFrame)==0 && (scriptCounterF00)<8) {
        ++scriptCounterF00;
        ResetSecondaryCounter(22);
        field3CF=1;
    }
    break;
}
