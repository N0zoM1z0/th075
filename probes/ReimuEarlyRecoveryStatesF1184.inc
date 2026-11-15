// Original Reimu 0045DD70 second-table recovery states 59..63.
// Native boundaries and actor-specific policies are checked in the whole parent.
case 0x59: {
    if ((reinterpret_cast<signed short&>(animationStage))==3) {
        rotationZ=(rotationZ)+g_ReimuRotationStepAt00657858;
        velocityY=velocityY-field05C;
        if (velocityY+y<=g_ThresholdAt0065782C) {
            reinterpret_cast<signed short&>(scriptCounterF00)=static_cast<short>((velocityX)*g_ContactProjectionAt00657888);
            reinterpret_cast<signed short&>(scriptCounterF02)=static_cast<short>((*(&velocityY))*g_ContactProjectionAt00657888);
            ResetAt453E20(); y=0.0f; SetNativeActionAt40FAC0(0x61);
            rotationZ=0.0f;
            InitTrajectoryAt453E60(2.0f); ResetMotionAt40FC50(); PrepareActionAt453D60(0x16);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) SetAuxActionAt40FB40(3);
    else if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        velocityX=float(int(reinterpret_cast<signed short&>(scriptCounterF00)))*g_ReimuBounceXAt006590BC;
        velocityY=float(-int(reinterpret_cast<signed short&>(scriptCounterF02)))*g_ReimuBounceYAt00658044;
        field05C=0.7f;
        SetMotionFloatAt40FBB0(-7.0f,75.0f,0.0f);
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
        if (reinterpret_cast<unsigned int&>(inputA)>0 ||
            reinterpret_cast<unsigned int&>(inputB)>0 ||
            reinterpret_cast<unsigned int&>(inputC)>0 ||
            reinterpret_cast<unsigned int&>(inputD)>0) reinterpret_cast<signed short&>(scriptCounterF00)=1;
    }
    if ((facing)*inputX<0) {
        if (reinterpret_cast<unsigned int&>(inputA)>0 ||
            reinterpret_cast<unsigned int&>(inputB)>0 ||
            reinterpret_cast<unsigned int&>(inputC)>0 ||
            reinterpret_cast<unsigned int&>(inputD)>0) reinterpret_cast<signed short&>(scriptCounterF00)=2;
    }
    if ((reinterpret_cast<signed short&>(animationStage))==0 && (reinterpret_cast<signed short&>(animationFrame))==0) {
        for (int shot=0;shot<10;++shot)
            SpawnDirectedAt453A70(0x3E4,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        if ((reinterpret_cast<signed short&>(fieldEFA))>25) {
            reinterpret_cast<signed short&>(fieldEFA)=0;
            SpawnDirectedAt453A70(0x3E3,reinterpret_cast<int&>(x),reinterpret_cast<int&>(y),1,1);
        }
    }
    if ((reinterpret_cast<signed short&>(animationStage))==3 || (reinterpret_cast<signed short&>(animationStage))==4) {
        velocityY=velocityY-field05C;
        if (velocityY+y<g_ThresholdAt0065782C) {
            y=0.0f; ResetAt453E20(); SetAuxActionAt40FB40(5);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==(reinterpret_cast<signed short&>(field070))) {
        SetNativeActionAt40FAC0(0x62);
        if (*reinterpret_cast<unsigned char*>(RAW+0x3CF)==0) SetNativeActionAt40FAC0(0x63);
    } else {
        // Original 00460409 jumps over BOTH stage-specific updates.
        if ((reinterpret_cast<signed short&>(animationStage))==3 && (reinterpret_cast<signed short&>(animationFrame))==0) {
            velocityX=float(int(reinterpret_cast<signed short&>(scriptCounterF00)))*g_ReimuRecoveryScaleAt006590B8;
            velocityY=float(-int(reinterpret_cast<signed short&>(scriptCounterF02)))*g_ReimuRecoveryScaleAt006590B8;
            field05C=2.0f;
        }
        if ((reinterpret_cast<signed short&>(animationStage))==4 && (reinterpret_cast<signed short&>(animationFrame))==0) SetAuxActionAt40FB40(3);
    }
    break;
}
#define F622_COUNTER 0xF00
#define F622_CHECK_DIRECTION 1
#include "FighterCounterDispatch62F622.inc"
#undef F622_COUNTER
#undef F622_CHECK_DIRECTION
#include "FighterMode63PriorityF627.inc"
