// Original Reimu 186..192 attack policies. Interior evidence only;
// the single 0045DD70 owner remains incomplete and NONEXACT.
case 0x186: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0) ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if ((reinterpret_cast<signed short&>(animationStage))>3 && (velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_AnimationDeltaAt0065747C;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=15.0f;
        PrepareActionAt453D60(0x1D);
    }
    break;
}
case 0x187: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) reinterpret_cast<signed short&>(scriptCounterF00)=0;
    if ((reinterpret_cast<signed short&>(animationStage))<5 && y==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ReimuGroundDragAt00658350;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=9.0f; velocityY=0.0f; field05C=0.0f;
        reinterpret_cast<signed short&>(field080)=1; field07C=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f;
            SetAuxActionAt40FB40(0xB);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(0);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=10.0f; velocityY=12.5f; field05C=0.85f;
        PrepareActionAt453D60(0x1C);
    }
    break;
}
case 0x188: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0) ResetAt453E20();
        field07C=0;
        velocityX=8.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))>0) {
        velocityX=(velocityX)-g_ApproachAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=8;
        field07C=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(animationStage))<12) field07C=0;
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1B);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1B);
    if ((reinterpret_cast<signed short&>(animationStage))==7 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1B);
    if ((reinterpret_cast<signed short&>(animationStage))==9 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1B);
    break;
}
case 0x189: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        if ((field3AC)==0) ResetAt453E20();
        reinterpret_cast<signed short&>(field080)=1; field07C=0;
        velocityX=12.0f; field3AC=0;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) reinterpret_cast<signed short&>(scriptCounterF00)=0;
    if ((reinterpret_cast<signed short&>(animationStage))>4 && y==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ReimuGroundDragAt00658350;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationStage))==2 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        reinterpret_cast<signed short&>(field080)=1; field07C=0; velocityX=12.0f;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) PrepareActionAt453D60(0x1D);
    if ((reinterpret_cast<signed short&>(animationStage))==5 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<1) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(3);
    }
    break;
}
#define R1186_ACTION 0x190
#define R1186_ANGLE0 -20.0f
#define R1186_ANGLE1 -10.0f
#define R1186_ANGLE2 0.0f
#define R1186_ANGLE3 10.0f
#define R1186_ANGLE4 20.0f
#define R1186_X_OFFSET 114
#define R1186_Y_OFFSET g_ReimuLowVolleyYAt006590A0
#include "ReimuFiveShotAttackF1186.inc"
#undef R1186_ACTION
#undef R1186_ANGLE0
#undef R1186_ANGLE1
#undef R1186_ANGLE2
#undef R1186_ANGLE3
#undef R1186_ANGLE4
#undef R1186_X_OFFSET
#undef R1186_Y_OFFSET
#define R1186_ACTION 0x191
#define R1186_ANGLE0 60.0f
#define R1186_ANGLE1 50.0f
#define R1186_ANGLE2 40.0f
#define R1186_ANGLE3 30.0f
#define R1186_ANGLE4 20.0f
#define R1186_X_OFFSET 90
#define R1186_Y_OFFSET g_ReimuHighVolleyYAt0065909C
#include "ReimuFiveShotAttackF1186.inc"
#undef R1186_ACTION
#undef R1186_ANGLE0
#undef R1186_ANGLE1
#undef R1186_ANGLE2
#undef R1186_ANGLE3
#undef R1186_ANGLE4
#undef R1186_X_OFFSET
#undef R1186_Y_OFFSET
case 0x192: {
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field07C=1;
        ResetAt453E20();
        reinterpret_cast<signed short&>(scriptCounterF00)=0;
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetNativeActionAt40FAC0(2);
    if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        field314=40.0f; field318=10.0f;
        SpawnFloatXYAt453A70(0x338,(*(&x))+g_ThresholdAt0065782C,
            (*(&y))+g_ThresholdAt0065782C,reinterpret_cast<char&>(facing),0);
        PlaySoundAt453D40(4);
        StartAnimationAt46D000(250);
    }
    if ((reinterpret_cast<signed short&>(animationStage))==6 && (reinterpret_cast<signed short&>(animationFrame))==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(4);
    }
    break;
}
