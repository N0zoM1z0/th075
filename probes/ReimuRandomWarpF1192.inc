case 0x2EF: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ClearMotionFields();
        field080=1; field07C=0; field3AC=0; reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
#define R1188_FADE_STAGE 1
#define R1188_RETURN_STAGE 3
#include "ReimuChargeTransformF1188.inc"
#undef R1188_FADE_STAGE
#undef R1188_RETURN_STAGE
    if (y>g_ThresholdAt0065782C && (animationStage)<14) {
        velocityY=velocityY-g_ReimuAirDragAt00658348;
        if (y+velocityY<g_ThresholdAt0065782C) {
            y=0.0f; velocityX=0.0f; velocityY=0.0f;
            ResetSecondaryCounter(14);
            break;
        }
    }
    if ((reinterpret_cast<signed short&>(scriptCounterF00))<g_ReimuRepeatSettingAt006714D0*2+3 && (animationFrame)==0 &&
        ((animationStage)==7 || (animationStage)==8)) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        PlaySound(12);
        field314=float(reinterpret_cast<signed short&>(scriptCounterF00));
        SpawnFloatXYAt453A70(0x394,float(facing*80)+(x),
            (*(&y))+g_ReimuCommandBackYAt006590A8,reinterpret_cast<char&>(facing),1);
        aiCardTimer=120;
    }
    if (AdvanceNestedFrame()==(field070)) {
        ResetPrimaryCounters(0);
        aiCardTimer=SelectRangeAt455580(0,60)+120-g_ReimuRepeatSettingAt006714D0*40;
    }
    if ((animationStage)==3 && (animationFrame)==0) {
        x=((*(&opponent->x))+g_ReimuWarpSpreadAt006583B4)-float(SelectRangeAt455580(0,2000));
        y=200.0f;
        velocityX=g_ReimuWarpSpeedAt00657CF8-float(SelectRangeAt455580(0,6));
        velocityY=6.0f;
        PlaySound(2);
        if (x>opponent->x)
            facing=-1;
        else facing=1;
    }
    if ((animationStage)==9 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<6) ResetSecondaryCounter(7);
    if ((animationStage)==14 && (animationFrame)==0) ResetSecondaryCounter(12);
    break;
}
