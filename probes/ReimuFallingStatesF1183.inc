// Original 0045DD70 falling/recovery states 12C..136, continued in the
// live whole-function parent. No state is an independent exact callable.
#define F653_ACTION 0x12C
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 3
#define F653_PREPARE_ANIM 0x1B
#define F653_CLEAR_F00 0
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#define F653_ACTION 0x12D
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 2
#define F653_PREPARE_ANIM 0x1C
#define F653_CLEAR_F00 1
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
case 0x12E: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if ((animationStage)>2 && (velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_AnimationDeltaAt0065747C;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=12.0f;
        if (reinterpret_cast<unsigned int&>(inputA)>9U) {
            SetNativeActionAt40FAC0(0x136);
            velocityX=0.0f;
        }
        break;
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        InitTrajectoryAt453E60(2.0f);
        SpawnFloatXYAt453A70(0x325,
            float(facing*170)+(x),
            y-g_ApproachLowerAt00658290,
            reinterpret_cast<char&>(facing),0);
    }
    break;
}
case 0x12F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=6;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(2);
    if ((animationFrame)==0 && (animationStage)<12) field07C=0;
    if ((animationStage)==3 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==5 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==7 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==9 && (animationFrame)==0) PlaySharedSound(0x1B);
    break;
}
case 0x130: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        field080=1;
        field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if (y>g_ThresholdAt0065782C) velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C && (animationStage)<12 && (animationStage)>5) {
        SetAuxActionAt40FB40(12);
        y=0.0f; field05C=0.0f; velocityY=0.0f; velocityX=0.0f;
        break;
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=5.0f; velocityY=12.5f; field05C=1.0f; field3AC=0;
        PlaySharedSound(0x1C);
    }
    if ((animationStage)==12 && (animationFrame)==0) SetAuxActionAt40FB40(11);
    break;
}
case 0x131: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        reinterpret_cast<signed short&>(scriptCounterF00)=0; field080=3; field07C=0;
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(9);
    if ((animationStage)==1 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==2 && (animationFrame)==0)
        SpawnFloatXYAt453A70(0x328,
            float(facing*145)+(x),
            (*(&y))+g_ReimuShotYAt006590A4,reinterpret_cast<char&>(facing),1);
    if ((animationStage)==4 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<2) {
        ++reinterpret_cast<signed short&>(scriptCounterF00);
        SetAuxActionAt40FB40(2);
        field07C=0;
    }
    break;
}
case 0x132: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C) {
        SetNativeActionAt40FAC0(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) { field080=1; field07C=0; }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(9);
    if ((animationStage)==2 && (animationFrame)==0) PlaySharedSound(0x1C);
    break;
}
case 0x133: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f; velocityY=0.0f; field05C=0.0f; field080=1; field07C=0;
    }
    if (y>g_ThresholdAt0065782C) {
        velocityY=velocityY-field05C;
        velocityX=(velocityX)-g_ReimuAirDragAt00658348;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f;
            SetAuxActionAt40FB40(11);
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=10.0f; velocityY=8.0f; field05C=0.8f;
        PlaySharedSound(0x1C);
    }
    break;
}
#define F653_ACTION 0x134
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 4
#define F653_PREPARE_ANIM 0x1C
#define F653_CLEAR_F00 0
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
case 0x135: {
    if ((animationStage)==0 && (animationFrame)==0) { ClearMotionFields(); reinterpret_cast<signed short&>(scriptCounterF00)=0; }
    if ((animationStage)>4 && y==g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ReimuGroundDragAt00658350;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if (y>g_ThresholdAt0065782C) velocityY=velocityY-field05C;
    if (y+velocityY<=g_ThresholdAt0065782C && velocityY<g_ThresholdAt0065782C && (animationStage)==2) {
        SetAuxActionAt40FB40(3);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        PlaySharedSound(0x1D);
        break;
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(2);
    if ((animationStage)==2 && (animationFrame)==0) {
        field080=1; field07C=0; velocityX=12.0f; velocityY=6.0f; field05C=0.8f;
    }
    // Original 004639D2..00463A2C really nests stage 5 under stage 3.
    // Keep both observed guards; simplifying this contradictory path would
    // discard native instructions rather than reconstruct the original.
    if ((animationStage)==3 && (animationFrame)==0) {
        if ((animationStage)==5 && (animationFrame)==0 && (reinterpret_cast<signed short&>(scriptCounterF00))<4) {
            ++reinterpret_cast<signed short&>(scriptCounterF00);
            SetAuxActionAt40FB40(3);
        }
    }
    break;
}
case 0x136: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field3AC=0; ClearMotionFields(); field080=1; field07C=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-g_JumpGroundCorrectionAt00658058;
        if ((velocityX)<g_ThresholdAt0065782C) { velocityX=0.0f; field3AC=0; }
    }
    if ((animationStage)>3 && (velocityX)>g_ThresholdAt0065782C) {
        velocityX=(velocityX)-g_ReimuLateDragAt006581E0;
        if ((velocityX)<g_ThresholdAt0065782C) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(field070)) SetNativeActionAt40FAC0(0);
    if ((animationStage)==4 && (animationFrame)==0) { velocityX=15.0f; PlaySharedSound(0x1D); }
    break;
}
