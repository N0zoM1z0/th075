// Original Reimu 0045DD70 second-table recovery states 59..63.
// Native boundaries and actor-specific policies are checked in the whole parent.
case 0x59: {
    if (S16(0x62)==3) {
        F32(0x30)=F32(0x30)+g_ReimuRotationStepAt00657858;
        POS54=POS54-POS5C;
        if (POS54+POS48<=g_ThresholdAt0065782C) {
            S16(0xF00)=static_cast<short>(POS*g_ContactProjectionAt00657888);
            S16(0xF02)=static_cast<short>((*(&POS54))*g_ContactProjectionAt00657888);
            ResetAt453E20(); POS48=0.0f; SetNativeActionAt40FAC0(0x61);
            F32(0x30)=0.0f;
            InitTrajectoryAt453E60(2.0f); ResetMotionAt40FC50(); PrepareActionAt453D60(0x16);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) SetAuxActionAt40FB40(3);
    else if (S16(0x62)==3 && S16(0x64)==0) {
        POS=float(int(S16(0xF00)))*g_ReimuBounceXAt006590BC;
        POS54=float(-int(S16(0xF02)))*g_ReimuBounceYAt00658044;
        POS5C=0.7f;
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
    if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)>0) {
        if (*reinterpret_cast<unsigned int*>(RAW+0x4E8)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4EC)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F0)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F4)>0) S16(0xF00)=1;
    }
    if ((*reinterpret_cast<signed char*>(RAW+0x66))*I32(0x4DC)<0) {
        if (*reinterpret_cast<unsigned int*>(RAW+0x4E8)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4EC)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F0)>0 ||
            *reinterpret_cast<unsigned int*>(RAW+0x4F4)>0) S16(0xF00)=2;
    }
    if (S16(0x62)==0 && S16(0x64)==0) {
        for (int shot=0;shot<10;++shot)
            SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
        if (S16(0xEFA)>25) {
            S16(0xEFA)=0;
            SpawnDirectedAt453A70(0x3E3,I32(0x44),I32(0x48),1,1);
        }
    }
    if (S16(0x62)==3 || S16(0x62)==4) {
        POS54=POS54-POS5C;
        if (POS54+POS48<g_ThresholdAt0065782C) {
            POS48=0.0f; ResetAt453E20(); SetAuxActionAt40FB40(5);
            break;
        }
    }
    if (GetNativeActionAt40FA30()==S16(0x70)) {
        SetNativeActionAt40FAC0(0x62);
        if (*reinterpret_cast<unsigned char*>(RAW+0x3CF)==0) SetNativeActionAt40FAC0(0x63);
    } else {
        // Original 00460409 jumps over BOTH stage-specific updates.
        if (S16(0x62)==3 && S16(0x64)==0) {
            POS=float(int(S16(0xF00)))*g_ReimuRecoveryScaleAt006590B8;
            POS54=float(-int(S16(0xF02)))*g_ReimuRecoveryScaleAt006590B8;
            POS5C=2.0f;
        }
        if (S16(0x62)==4 && S16(0x64)==0) SetAuxActionAt40FB40(3);
    }
    break;
}
#define F622_COUNTER 0xF00
#define F622_CHECK_DIRECTION 1
#include "FighterCounterDispatch62F622.inc"
#undef F622_COUNTER
#undef F622_CHECK_DIRECTION
#include "FighterMode63PriorityF627.inc"
