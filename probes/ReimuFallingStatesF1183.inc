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
        remainingHits=1;
        collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) {
            velocityX=0.0f;
            field3AC=0;
        }
    }
    if ((animationStage)>2 && (velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::One;
        if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=12.0f;
        if (static_cast<unsigned int>(inputA)>9U) {
            ResetPrimaryCounters(0x136);
            velocityX=0.0f;
        }
        break;
    }
    if ((animationStage)==5 && (animationFrame)==0) {
        SetCameraShake(2.0f);
        SpawnBattleEffect(0x325,
            float(facing*170)+(x),
            y-GeometryConstants::Six,
            facing,0);
    }
    break;
}
case 0x12F: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        remainingHits=6;
        collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) { velocityX=0.0f; field3AC=0; }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(2);
    if ((animationFrame)==0 && (animationStage)<12) collisionResult=0;
    if ((animationStage)==3 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==5 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==7 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==9 && (animationFrame)==0) PlaySharedSound(0x1B);
    break;
}
case 0x130: {
    if ((animationStage)==0 && (animationFrame)==0) {
        if ((field3AC)==0) ClearMotionFields();
        remainingHits=1;
        collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) { velocityX=0.0f; field3AC=0; }
    }
    if (y>FloatConstants::Zero) velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero && (animationStage)<12 && (animationStage)>5) {
        ResetSecondaryCounter(12);
        y=0.0f; field05C=0.0f; velocityY=0.0f; velocityX=0.0f;
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if ((animationStage)==5 && (animationFrame)==0) {
        velocityX=5.0f; velocityY=12.5f; field05C=1.0f; field3AC=0;
        PlaySharedSound(0x1C);
    }
    if ((animationStage)==12 && (animationFrame)==0) ResetSecondaryCounter(11);
    break;
}
case 0x131: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        scriptCounterF00=0; remainingHits=3; collisionResult=0;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==1 && (animationFrame)==0) PlaySharedSound(0x1B);
    if ((animationStage)==2 && (animationFrame)==0)
        SpawnBattleEffect(0x328,
            float(facing*145)+(x),
            (*(&y))+GeometryConstants::SixtySix,facing,1);
    if ((animationStage)==4 && (animationFrame)==0 && (scriptCounterF00)<2) {
        ++scriptCounterF00;
        ResetSecondaryCounter(2);
        collisionResult=0;
    }
    break;
}
case 0x132: {
    velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero) {
        ResetPrimaryCounters(10);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) { remainingHits=1; collisionResult=0; }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(9);
    if ((animationStage)==2 && (animationFrame)==0) PlaySharedSound(0x1C);
    break;
}
case 0x133: {
    if ((animationStage)==0 && (animationFrame)==0) {
        velocityX=0.0f; velocityY=0.0f; field05C=0.0f; remainingHits=1; collisionResult=0;
    }
    if (y>FloatConstants::Zero) {
        velocityY=velocityY-field05C;
        velocityX=(velocityX)-FloatConstants::OneFifth;
        if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
        if (velocityY+y<=FloatConstants::Zero) {
            velocityX=0.0f; velocityY=0.0f; field05C=0.0f; y=0.0f;
            ResetSecondaryCounter(11);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
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
    if ((animationStage)==0 && (animationFrame)==0) { ClearMotionFields(); scriptCounterF00=0; }
    if ((animationStage)>4 && y==FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::ThreeQuarters;
        if ((velocityX)<FloatConstants::Zero) { velocityX=0.0f; field3AC=0; }
    }
    if (y>FloatConstants::Zero) velocityY=velocityY-field05C;
    if (y+velocityY<=FloatConstants::Zero && velocityY<FloatConstants::Zero && (animationStage)==2) {
        ResetSecondaryCounter(3);
        y=0.0f; field05C=0.0f; velocityY=0.0f;
        PlaySharedSound(0x1D);
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(2);
    if ((animationStage)==2 && (animationFrame)==0) {
        remainingHits=1; collisionResult=0; velocityX=12.0f; velocityY=6.0f; field05C=0.8f;
    }
    // Original 004639D2..00463A2C really nests stage 5 under stage 3.
    // Keep both observed guards; simplifying this contradictory path would
    // discard native instructions rather than reconstruct the original.
    if ((animationStage)==3 && (animationFrame)==0) {
        if ((animationStage)==5 && (animationFrame)==0 && (scriptCounterF00)<4) {
            ++scriptCounterF00;
            ResetSecondaryCounter(3);
        }
    }
    break;
}
case 0x136: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field3AC=0; ClearMotionFields(); remainingHits=1; collisionResult=0;
    }
    if ((field3AC)>0) {
        velocityX=(velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX)<FloatConstants::Zero) { velocityX=0.0f; field3AC=0; }
    }
    if ((animationStage)>3 && (velocityX)>FloatConstants::Zero) {
        velocityX=(velocityX)-FloatConstants::OneAndHalf;
        if ((velocityX)<FloatConstants::Zero) velocityX=0.0f;
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
    if (animationStage == 4 && animationFrame == 0) {
        velocityX = 15.0f;
        PlaySharedSound(0x1D);
    } else if (animationStage == 4 && animationFrame != 0) {
        // Continue the launch animation.
    }
    break;
}
