// Original Reimu 0045DD70 second-table recovery states 59..63.
// Native boundaries and actor-specific policies are checked in the whole parent.
case 0x59: {
    if ((animationStage)==3) {
        rotationZ=(rotationZ)+GeometryConstants::Forty;
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<=FloatConstants::Zero) {
            scriptCounterF00=(velocityX)*GeometryConstants::Hundred;
            scriptCounterF02=(*(&velocityY))*GeometryConstants::Hundred;
            ClearMotionFields(); y=0.0f; ResetPrimaryCounters(0x61);
            rotationZ=0.0f;
            SetCameraShake(2.0f); ClearTransformFlag(); PlaySharedSound(0x16);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) ResetSecondaryCounter(3);
    else if ((animationStage)==3 && (animationFrame)==0) {
        velocityX=float(int(scriptCounterF00))*FloatConstants::OneFourHundredth;
        velocityY=float(-int(scriptCounterF02))*FloatConstants::OneHundredth;
        verticalAcceleration=0.7f;
        ResetTransform(-7.0f,75.0f,0.0f);
    } else if (animationStage == 3 && animationFrame != 0) {
        // Keep the rebound motion on later frames.
    }
    break;
}
#define F617_CASE 0x5D
#define F617_THRESHOLD 11
#define F617_BEGIN_STAGE 3
#define F617_START_SPEED 4.5f
#define F617_START_POS 12.5f
#define F617_FRICTION 0.35f
#define F617_FINISH_STATE 7
#include "FighterAirTransitionCaseF617.inc"
#undef F617_CASE
#undef F617_THRESHOLD
#undef F617_BEGIN_STAGE
#undef F617_START_SPEED
#undef F617_START_POS
#undef F617_FRICTION
#undef F617_FINISH_STATE
#define F617_CASE 0x5E
#define F617_THRESHOLD 11
#define F617_BEGIN_STAGE 3
#define F617_START_SPEED 4.5f
#define F617_START_POS -12.5f
#define F617_FRICTION 0.35f
#define F617_FINISH_STATE 7
#include "FighterAirTransitionCaseF617.inc"
#undef F617_CASE
#undef F617_THRESHOLD
#undef F617_BEGIN_STAGE
#undef F617_START_SPEED
#undef F617_START_POS
#undef F617_FRICTION
#undef F617_FINISH_STATE
#define F620_FIRST_ACTION 0
#define F620_SECOND_ACTION 1
#include "FighterFacing5FF620.inc"
#undef F620_FIRST_ACTION
#undef F620_SECOND_ACTION
case 0x61: {
    if ((facing)*inputX>0) {
        if (static_cast<unsigned int>(inputA)>0 ||
            static_cast<unsigned int>(inputB)>0 ||
            static_cast<unsigned int>(inputC)>0 ||
            static_cast<unsigned int>(inputD)>0) scriptCounterF00=1;
    }
    if ((facing)*inputX<0) {
        if (static_cast<unsigned int>(inputA)>0 ||
            static_cast<unsigned int>(inputB)>0 ||
            static_cast<unsigned int>(inputC)>0 ||
            static_cast<unsigned int>(inputD)>0) scriptCounterF00=2;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        for (int shot=0;shot<10;++shot)
            SpawnBattleEffect(0x3E4,x,y,1,1);
        if ((fieldEFA)>25) {
            fieldEFA=0;
            SpawnBattleEffect(0x3E3,x,y,1,1);
        }
    }
    if ((animationStage)==3 || (animationStage)==4) {
        velocityY=velocityY-verticalAcceleration;
        if (velocityY+y<FloatConstants::Zero) {
            y=0.0f; ClearMotionFields(); ResetSecondaryCounter(5);
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetPrimaryCounters(0x62);
        if (field3CF==0) ResetPrimaryCounters(0x63);
    } else {
        // Original 00460409 jumps over BOTH stage-specific updates.
        if ((animationStage)==3 && (animationFrame)==0) {
            velocityX=float(int(scriptCounterF00))*FloatConstants::OneTwoHundredth;
            velocityY=float(-int(scriptCounterF02))*FloatConstants::OneTwoHundredth;
            verticalAcceleration=2.0f;
        }
        if (animationStage == 4 && animationFrame == 0)
            ResetSecondaryCounter(3);
        else if (animationStage == 4 && animationFrame != 0) {
            // Continue the rebound animation.
        }
    }
    break;
}
#define F622_COUNTER 0xF00
#define F622_CHECK_DIRECTION 1
#include "FighterCounterDispatch62F622.inc"
#undef F622_COUNTER
#undef F622_CHECK_DIRECTION
#include "FighterMode63PriorityF627.inc"
