#include "FighterProjectileXViewF917.hpp"
// F539 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
class FighterSwitchF598_Boss00543210 { public: void SpawnDirectedAt453A70(int,int,int,char,int); void SpawnWithFloatAt453A70(int,int,float,char,int); void SpawnFloatXRawYAt453A70(int,float,int,char,int); void SpawnFloatXYAt453A70(int,float,float,char,int); void SpawnRawXYAt453C80(int,int,int,char,int); void SpawnMixedAt453C80(int,int,float,char,int); void SpawnSevenAt453B50(int,int,int,char,int,int,int); void PrepareActionAt453D40(int); void SetMotionStateAt40FBB0(int,float,int); void MotionAt40FB70(float,float); void ResetMotionAt40FC50(); void InitTrajectoryAt453E60(float); int RandomBoundaryAt455580(int,int); void InitTrajectoryAt453E80(int); virtual void NativeVirtualFrameAdvance(); void Advance(); void ResetAt453E20(); void PrepareActionAt453D60(int); void SubactionAt454A70(int); void ConfigureStormAt454BC0(int,int,int); void SubactionAt452B30(); void StartAnimationAt46D000(int); void SpawnAt453C80(int,float,float,char,int); short GetNativeActionAt40FA30(); void SetNativeActionAt40FAC0(int); signed char ContactAt454EE0(); void SetAuxActionAt40FB40(int); };
extern unsigned int g_FighterProbeMarker;
extern signed char g_ModeAt006714B4;
extern float g_ThresholdAt0065782C;
extern float g_F759_C8DecelAt006593E8;
extern float g_F759_C9DecelAt00658290;
extern float g_F701_VolleyYAt00658268;
extern float g_F699_SideOffsetAt00657874;
extern float g_F699_SideEdgeAt00657884;
extern float g_F699_DistanceAt0065787C;
extern "C" float __cdecl F699AbsAt00412D90(float);
extern float g_AnimationDeltaAt0065747C;
extern float g_AnimationMaximumAt006583B4;
extern float g_JumpGroundCorrectionAt00658058;
extern float g_FallingLateDragAt00659240;
extern float g_NewDragAt006581E0;
extern float g_SlowPositiveDragAt006578C0;
extern float g_ShotPositiveDragAt00659A10;
extern float g_SpeedClampAt00657CF8;
extern float g_RisingGravityAt0065747C;
extern float g_RisingDragAt006581E0;
extern float g_BounceScaleAt006583FC;
extern float g_FloatMulAt00657874;
extern float g_FloatAddAt00657CBC;
extern float g_F734_RoundY0At00659A30;
extern float g_F734_RoundY1At00659A2C;
extern float g_F734_RoundY2At00659A28;
extern float g_F737_RoundY0At00659A24;
extern float g_F737_RoundY1At00659A20;
extern float g_F740_ShotY0At00659A1C;
extern float g_F740_ShotY1At0065928C;
extern float g_F740_ShotY2At00659A18;
extern float g_F743_Y19CAt00659A14;
extern float g_F743_Y1A0At00659288;
extern float g_YPlusAt0065929C;
extern float g_YPlusAt00658400;
extern float g_BarrageY1At006591EC;
extern float g_BarrageY2At006581DC;
extern float g_BarrageY3At0065908C;
extern float g_EightShotY0At006591F8;
extern float g_EightShotY1At00658264;
extern float g_EightShotY2At00658268;
extern float g_OneShotYAt0065928C;
extern double g_JumpReflectionAt006583E8;
extern float g_ApproachLowerAt00658290;
extern float g_ApproachUpperAt006592A4;
extern float g_F711_ReverseRandomAt00659A0C;
extern float g_F714_ShotYAt00657868;
extern float g_F714_DecelerationAt0065747C;
extern float g_F715_DecisionHeightAt006593D0;
extern float g_F718_FallingDragAt00659090;
extern float g_F718_BounceMinAt00657CF8;
extern float g_F722_BurstYAt0065826C;
extern float g_F722_LowYAt00659A10;
extern float g_F724_ShotYAt00659488;
extern float g_F728_RandomOffsetXAt00657878;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_F728_PositiveDragAt006583FC;
extern float g_F731_AimOffsetAt00657CBC;
extern float g_F728_PositiveDrag2At00658058;
extern float g_StopThresholdAt00657480;
extern float g_TrajectoryUpperAt006590C4;
extern float g_ContactProjectionAt00657888;
extern float g_F747_BounceXAt006590BC;
extern float g_F747_BounceYAt00658044;
extern float g_F748_SpeedScaleAt006590B8;
extern float g_FallDecelerationAt00659888;
extern float g_CloudGravityAt0065785C;
extern float g_CloudShotYAt006591E4;
extern float g_StormAngleShotYAt00659A18;
extern float g_StormMotionAt00658348;
extern float g_StormAngleDenominatorAt00657828;
extern "C" float __cdecl CalculateAngleAt483300(float,float);
extern float g_StormYAt0065948C;
extern float g_BurstXAt00659238;
extern float g_BurstXAt00658400;
extern float g_BurstXAt00659420;
extern float g_BurstXAt00658370;
extern float g_BurstXAt006590A8;
extern signed char g_CloudOpponentAt006714D0;
extern float g_ProjectileFallAt006590B4;
extern float g_BounceThresholdAt006590C0;
extern float g_BounceScaleAt00657F74;
extern float g_AngleShiftAt00657878;
extern float g_ApproachAt00658058;
extern double g_ContactScaleAt006583E8;
extern float g_ExtraThresholdAt00657D14;
extern float g_SubtractAt00657478;
extern double g_RiseAt00658050;
#define RAW reinterpret_cast<char*>(this)
#define I32(off) *reinterpret_cast<int*>(RAW+(off))
#define I16(off) *reinterpret_cast<signed short*>(RAW+(off))
#define POS (*reinterpret_cast<float*>(RAW+0x50))
#define POS48 *reinterpret_cast<float*>(RAW+0x48)
#define F32(off) (*reinterpret_cast<float*>(RAW+(off)))
#define POS54 *reinterpret_cast<float*>(RAW+0x54)
#define POS5C *reinterpret_cast<float*>(RAW+0x5C)
#define S16(off) (*reinterpret_cast<signed short*>(RAW+(off)))
#define U8(off) (*reinterpret_cast<unsigned char*>(RAW+(off)))
#define FLAG (*reinterpret_cast<signed char*>(RAW+0x3AC))
#define OWNER (*reinterpret_cast<char**>(RAW+0x2E8))
#include "FighterBorrowedXYViewF771.hpp"
void FighterSwitchF598_Boss00543210::Advance() {
    if (I16(0x82) != 0 || *reinterpret_cast<signed short*>(OWNER+0x3BA) != 0)
        return;
    switch (I16(0x60)) {
        case 0x0:
            if (FLAG == 0) {
                ResetAt453E20();
            } else {
                if (POS > g_ThresholdAt0065782C) {
                    POS -= g_SubtractAt00657478;
                    if (POS < g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
                if (POS < g_ThresholdAt0065782C) {
                    POS += g_RiseAt00658050;
                    if (POS > g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
            }
            goto native_shared_getter;
        case 0x1:
            if (FLAG == 0) {
                ResetAt453E20();
            } else {
                if (POS > g_ThresholdAt0065782C) {
                    POS -= g_SubtractAt00657478;
                    if (POS < g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
                if (POS < g_ThresholdAt0065782C) {
                    POS += g_RiseAt00658050;
                    if (POS > g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
            }
            if (GetNativeActionAt40FA30() == I16(0x70))
                SetNativeActionAt40FAC0(2);
            break;
        case 0x2:
            if (FLAG == 0) {
                ResetAt453E20();
            } else {
                if (POS > g_ThresholdAt0065782C) {
                    POS -= g_SubtractAt00657478;
                    if (POS < g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
                if (POS < g_ThresholdAt0065782C) {
                    POS += g_RiseAt00658050;
                    if (POS > g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
            }
            goto native_shared_getter;
        case 0x3:
            if (FLAG == 0) {
                ResetAt453E20();
            } else {
                if (POS > g_ThresholdAt0065782C) {
                    POS -= g_SubtractAt00657478;
                    if (POS < g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
                if (POS < g_ThresholdAt0065782C) {
                    POS += g_RiseAt00658050;
                    if (POS > g_ThresholdAt0065782C) {
                        ResetAt453E20();
                        FLAG = 0;
                    }
                }
            }
            if (GetNativeActionAt40FA30() == I16(0x70))
                SetNativeActionAt40FAC0(0);
            break;
        case 0x4: POS = 6.5f; goto native_shared_getter;
        case 0x5: POS = -6.5f; goto native_shared_getter;
        case 0x6:
            if (S16(0x62) == 0 && S16(0x64) == 0 &&
                    (U8(0x511) == 3 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCC);
                return;
            }
            if (S16(0x62) == 0 && FLAG == 0)
                ResetAt453E20();
            if (POS48 > g_ThresholdAt0065782C) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            if (S16(0x62) == 3 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(4);
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == 3) {
                    POS = 0.0f;
                    POS54 = 19.0f;
                    POS5C = 0.95f;
                }
                if (S16(0x62) >= S16(0x70))
                    S16(0x62) -= 2;
                NativeVirtualFrameAdvance();
            }
            break;
        case 0x7:
            if (S16(0x62) == 0 && S16(0x64) == 0 &&
                    (U8(0x511) == 5 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCD);
                return;
            }
            if (S16(0x62) == 0 && FLAG == 0)
                ResetAt453E20();
            if (POS48 > g_ThresholdAt0065782C) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == 3) {
                    POS = 7.0f;
                    POS54 = 18.0f;
                    POS5C = 0.95f;
                }
                if (S16(0x62) >= S16(0x70))
                    S16(0x62) -= 2;
                NativeVirtualFrameAdvance();
            }
            break;
        case 0x8:
            if (S16(0x62) == 0 && S16(0x64) == 0 &&
                    (U8(0x511) == 4 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCE);
                return;
            }
            if (S16(0x62) == 0 && FLAG == 0)
                ResetAt453E20();
            if (S16(0x62) == 3 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(4);
            if (POS48 > g_ThresholdAt0065782C) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == 3) {
                    POS = -7.0f;
                    FLAG = 0;
                    POS54 = 18.0f;
                    POS5C = 0.95f;
                }
                if (S16(0x62) >= S16(0x70))
                    S16(0x62) -= 2;
                NativeVirtualFrameAdvance();
            }
            break;
        case 0x9:
        if (POS5C == g_ThresholdAt0065782C)
            POS5C = 0.6f;
        POS54 = POS54 - POS5C;
        if (POS48 + POS54 <= g_ThresholdAt0065782C) {
            SetNativeActionAt40FAC0(10);
            POS48 = 0.0f;
            ResetAt453E20();
            return;
        }
        if (GetNativeActionAt40FA30() == I16(0x70)) {
            SetAuxActionAt40FB40(1);
        }
        break;
        case 0xA:
            if (I16(0x62) == 0 && I16(0x64) == 0)
                PrepareActionAt453D60(30);
            ResetAt453E20();
            if (GetNativeActionAt40FA30() == I16(0x70)) {
                if (I32(0x4E0) == 0)
                    SetNativeActionAt40FAC0(3);
                else
                    SetNativeActionAt40FAC0(2);
            }
            break;
        #include "FighterSingletonContactF598.inc"
#define CONTACT_STAGE_OFFSET 0xF00
#include "FighterAdditionalContactF600.inc"
#undef CONTACT_STAGE_OFFSET
#define TRAJECTORY_LOWER_THRESHOLD g_ApproachLowerAt00658290
#define TRAJECTORY_UPPER_THRESHOLD g_ApproachUpperAt006592A4
#define TRAJECTORY_MINIMUM_SPEED 6.0f
#define TRAJECTORY_MAXIMUM_SPEED 25.0f
#define TRAJECTORY_STAGE_THRESHOLD 1
#define TRAJECTORY_EARLY_STATE 2
#define TRAJECTORY_LATE_STATE 7
#define CONTACT_STAGE_OFFSET 0xF00
#include "FighterTrajectoryContact46F602.inc"
#undef TRAJECTORY_LOWER_THRESHOLD
#undef TRAJECTORY_UPPER_THRESHOLD
#undef TRAJECTORY_MINIMUM_SPEED
#undef TRAJECTORY_MAXIMUM_SPEED
#undef TRAJECTORY_STAGE_THRESHOLD
#undef TRAJECTORY_EARLY_STATE
#undef TRAJECTORY_LATE_STATE
#undef CONTACT_STAGE_OFFSET

#define F605_STAGE47 1
#define F605_EARLY47 2
#define F605_LATE47 7
#define F605_STAGE48 1
#define F605_EARLY48 2
#define F605_LATE48 7
#define F605_COUNTER 0xF00
#include "FighterTrajectoryFollowupsF605.inc"
#undef F605_COUNTER
#undef F605_STAGE47
#undef F605_EARLY47
#undef F605_LATE47
#undef F605_STAGE48
#undef F605_EARLY48
#undef F605_LATE48
#define F607_COUNTER 0xF00
#include "FighterTrajectoryLanding49F607.inc"
#undef F607_COUNTER
#define F610_STAGE 1
#define F610_EARLY 2
#define F610_LATE 7
#define F610_COUNTER 0xF00
#define F610_PREPARE_BEFORE 1
#include "FighterTrajectoryBounce4AF610.inc"
#undef F610_STAGE
#undef F610_EARLY
#undef F610_LATE
#undef F610_COUNTER
#undef F610_PREPARE_BEFORE
#define F613_COUNTER 0xF00
#include "FighterTrajectoryRecovery4CF613.inc"
#undef F613_COUNTER
#define F614_COUNTER 0xF00
#define F614_STAGE1_SPAWN 0
#define F614_PROJECTILE 0x3E7
#define F614_SIDE 0
#include "FighterTrajectoryBurst58F614.inc"
#undef F614_COUNTER
#undef F614_STAGE1_SPAWN
#undef F614_PROJECTILE
#undef F614_SIDE
#include "FighterEarlyBounceTypedF752.inc"


#include "FighterFacing05FF762.inc"
#include "FighterResourceTenVolleyF748.inc"

#include "FighterResourceSelectorF749.inc"
#include "FighterMode63BasicF626.inc"
#define F628_CASE 0x8C
#define F628_COUNTER 0xF00
#define F628_START_POS -11.0f
#define F628_LIMIT 5
#include "FighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x8F
#define F628_COUNTER 0xF00
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "FighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x90
#define F628_COUNTER 0xF00
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "FighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F629_STAGE 1
#define F629_EARLY 2
#define F629_LATE 7
#define F629_COUNTER 0xF00
#include "FighterArcTrajectory91F629.inc"
#undef F629_STAGE
#undef F629_EARLY
#undef F629_LATE
#undef F629_COUNTER
#define F631_COUNTER 0xF00
#define F631_EXTRA_FLAG 1
#define F631_EXTRA_BEFORE 0
#include "FighterLandingTimer96F631.inc"
#undef F631_COUNTER
#undef F631_EXTRA_FLAG
#undef F631_EXTRA_BEFORE
#define F633_CASE 0x97
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 1
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x98
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -13.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 1
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x9A
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 1
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x9B
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 1
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x9C
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -13.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 1
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F637_EXTRA_FLAG 1
#define F637_EXTRA_BEFORE 0
#define F637_STRICT_ABOVE 0
#include "FighterGroundBoost9EF637.inc"
#undef F637_EXTRA_FLAG
#undef F637_EXTRA_BEFORE
#undef F637_STRICT_ABOVE
#define F633_CASE 0x9F
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0xA0
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0xA1
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -13.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F641_CASE 0xA3
#define F641_START_HEIGHT -9.0f
#define F641_NEXT_ACTION 2
#include "FighterLandingNoCounterF641.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F641_CASE 0xA4
#define F641_START_HEIGHT -10.0f
#define F641_NEXT_ACTION 2
#include "FighterLandingNoCounterF641.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F641_CASE 0xA5
#define F641_START_HEIGHT -13.0f
#define F641_NEXT_ACTION 2
#include "FighterLandingNoCounterF641.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F642_CASE 0xA7
#define F642_COUNTER 0xF00
#define F642_NEXT_ACTION 0
#include "FighterProjectileLaunchF642.inc"
#undef F642_CASE
#undef F642_COUNTER
#undef F642_NEXT_ACTION
#define F642_CASE 0xA8
#define F642_COUNTER 0xF00
#define F642_NEXT_ACTION 2
#include "FighterProjectileLaunchF642.inc"
#undef F642_CASE
#undef F642_COUNTER
#undef F642_NEXT_ACTION
#define F645_CASE 0xB4
#define F645_START_POS 8.0f
#define F645_AUX_ACTION 6
#include "FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#define F645_CASE 0xB5
#define F645_START_POS -8.0f
#define F645_AUX_ACTION 6
#include "FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#include "FighterFourDirectionalC8F759.inc"



#include "FighterComplexStageCC_CE_F760.inc"


#include "FighterFallStateCFF647.inc"
#include "FighterReflectLandingD0F646.inc"
#define F651_DECAY 3
#define F651_SPRITE 0x3E6
#include "FighterResourceShotD1F651.inc"
#undef F651_DECAY
#undef F651_SPRITE
#define F652_DECAY 3
#define F652_SPRITE 0x3E6
#define F652_SCALE_BEFORE 0
#include "FighterResourceShotD2F652.inc"
#undef F652_DECAY
#undef F652_SPRITE
#undef F652_SCALE_BEFORE
#define F653_ACTION 0x12C
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 2
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
#define F653_PREPARE_FRAME 4
#define F653_PREPARE_ANIM 0x1D
#define F653_CLEAR_F00 1
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#define F653_ACTION 0x12E
#define F653_NEXT_ACTION 2
#define F653_PREPARE_FRAME 2
#define F653_PREPARE_ANIM 0x1D
#define F653_CLEAR_F00 0
#include "FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#include "FighterFallingFinishF654.inc"

#include "FighterLateGroundF656.inc"
#include "FighterLateShotsF656.inc"



#include "FighterMotionContinuationF657.inc"



#include "FighterMotionShotsF661.inc"

#include "FighterEightRoundF734.inc"


#include "FighterEightGroundF737.inc"

#include "FighterRepeatShotF740.inc"


#include "FighterDoubleRepeatF744.inc"

#include "FighterLaterEarlyF743.inc"



#include "FighterRandomArcsF728.inc"

#define F729_CASE 0x1F6
#define F729_STAGE14_X 40.0f
#define F729_STAGE14_Y -20.0f
#define F729_STAGE15_SHOT 0x336
#include "FighterBoundaryReturnTypedF762.inc"
#undef F729_CASE
#undef F729_STAGE14_X
#undef F729_STAGE14_Y
#undef F729_STAGE15_SHOT
#define F729_CASE 0x1F7
#define F729_STAGE14_X 30.0f
#define F729_STAGE14_Y -30.0f
#define F729_STAGE15_SHOT 0x337
#include "FighterBoundaryReturnTypedF762.inc"
#undef F729_CASE
#undef F729_STAGE14_X
#undef F729_STAGE14_Y
#undef F729_STAGE15_SHOT
#include "FighterAimReturnTypedF762.inc"
#include "FighterFollowingNativeF732.inc"



#include "FighterSpecialStageF664.inc"

#include "FighterCounterSpecialF668.inc"


#include "FighterPostCounterF669.inc"


#include "FighterFourShotBarrageF671.inc"
#include "FighterEightShotAndFollowF672.inc"




#include "FighterGroundWaveF673.inc"
        case 0x2BF: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                PrepareActionAt453D40(9);
                SpawnAt453C80(0x73,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*20),
                    (*(&POS48))+g_BurstXAt00659238,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnSevenAt453B50(0x334,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==12 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x328,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x33C,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(10);
            }
            break;
        }

// F722: complete physical fighter action 0x2C0 and 0x2C1 in original giant.
// 2C0 original 0054D64D..0054D93E = 753 B/218 real x86.
// 2C1 original 0054D93E..0054DC0E = 720 B/214 real x86.
// 2C0 native IMUL +46/FSUBR is algebraically reproduced with -46/FADD
// to align the native FILD-before-X x87 order. Actual opcode/constant differ.
// Entire 00543210 original function still NONEXACT, no case credit.
        case 0x2C0: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=99;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<25 && POS48>g_ThresholdAt0065782C && S16(0x62)>15) {
                POS=POS-g_F718_FallingDragAt00659090;
                POS54=POS54-POS5C;
                if (POS<g_F718_BounceMinAt00657CF8)
                    POS=3.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(25);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==1 && S16(0x64)==0) {
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                SpawnAt453C80(0x73,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*46),
                    (*(&POS48))+g_F722_BurstYAt0065826C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==7 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(11);
                POS54=9.0f;
                POS=20.0f;
                StartAnimationAt46D000(500);
                POS5C=0.8f;
            }
            if (S16(0x62)>6 && S16(0x62)<15) {
                SpawnFloatXYAt453A70(0x329,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==15 && S16(0x64)==0 && S16(0xF00)<3) {
                SetAuxActionAt40FB40(11);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==25 && S16(0x64)==0)
                SetAuxActionAt40FB40(23);
            break;
        }
        case 0x2C1: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                SpawnMixedAt453C80(0x74,I32(0x44),
                    (*(&POS48))+g_ContactProjectionAt00657888,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
            }
            if (S16(0x62)>3 && S16(0x62)<11) {
                POS54=POS54-g_F722_LowYAt00659A10;
                if (POS54<g_ThresholdAt0065782C)
                    POS54=0.0f;
            }
            if (S16(0x62)>10 && S16(0x62)<14) {
                POS54=POS54-POS5C;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(14);
                    break;
                }
            }
            if (S16(0x62)==5 && S16(0x64)==0)
                InitTrajectoryAt453E60(5.0f);
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==4 && S16(0x64)==0) {
                POS54=15.0f;
                POS5C=0.85f;
            }
            if (S16(0x62)==5 && S16(0x64)==0) {
                SpawnFloatXYAt453A70(0x32A,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*40)+F32(0x44),
                    10.0f,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnDirectedAt453A70(0x340,I32(0x44),0,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(12);
            }
            if (S16(0x62)==8 && S16(0x64)==0 && S16(0xF00)<12) {
                SetAuxActionAt40FB40(5);
                ++S16(0xF00);
            }
            if (S16(0x62)==11 && S16(0x64)==0 && S16(0xF00)<14) {
                SetAuxActionAt40FB40(8);
                ++S16(0xF00);
            }
            if (S16(0x62)==14 && S16(0x64)==0)
                SetAuxActionAt40FB40(12);
            break;
        }

        case 0x2C4: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                S16(0xF00)=0;
                I32(0x7C)=1;
                ResetAt453E20();
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                PrepareActionAt453D40(13);
                SpawnAt453C80(0x74,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*20),
                    (*(&POS48))+g_BurstXAt00659238,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnSevenAt453B50(0x334,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1,0,1);
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x62)==12 && S16(0x64)==0) {
                StartAnimationAt46D000(750);
                SpawnFloatXYAt453A70(0x32B,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x33D,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*65)+F32(0x44),
                    (*(&POS48))+g_BarrageY1At006591EC,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                PrepareActionAt453D40(14);
            }
            break;
        }




// F724: complete original fighter 00543210 action0x2C5 native
// 0054DDD2..0054E111: 831 CODE B/239 x86, not a new whole function.
// Original camera/motion reset, floor/drag/landing, native stage1
// 74 attack and trajectory, stage7 3C and 344 shots, stage15 loop.
// All exactness claims require original full giant; this is NONEXACT.
        case 0x2C5: {
            if (S16(0x62)==0 && S16(0x64)==0) {
                ResetAt453E20();
                S16(0x80)=99;
                I32(0x7C)=0;
                U8(0x3AC)=0;
                S16(0xF00)=0;
            }
            if (S16(0x62)<25 && POS48>g_ThresholdAt0065782C && S16(0x62)>15) {
                POS=POS-g_F718_FallingDragAt00659090;
                POS54=POS54-POS5C;
                if (POS<g_F718_BounceMinAt00657CF8)
                    POS=3.0f;
                if (POS48+POS54<=g_ThresholdAt0065782C) {
                    SetAuxActionAt40FB40(25);
                    POS48=0.0f;
                    ResetAt453E20();
                    break;
                }
            }
            if (GetNativeActionAt40FA30()==S16(0x70))
                SetNativeActionAt40FAC0(0);
            if (S16(0x64)==0)
                I32(0x7C)=0;
            if (S16(0x62)==1 && S16(0x64)==0) {
                InitTrajectoryAt453E80(40);
                PrepareActionAt453D60(23);
                SpawnAt453C80(0x74,
                    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44-float(*reinterpret_cast<signed char*>(RAW+0x66)*46),
                    (*(&POS48))+g_F722_BurstYAt0065826C,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                F32(0x36C)=F32(0x36C)-g_ContactProjectionAt00657888;
            }
            if (S16(0x62)==7 && S16(0x64)==0) {
                SpawnRawXYAt453C80(0x3C,I32(0x44),I32(0x48),
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                SpawnFloatXYAt453A70(0x344,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*55)+F32(0x44),
                    (*(&POS48))+g_F724_ShotYAt00659488,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
                StartAnimationAt46D000(500);
                PrepareActionAt453D40(15);
                POS54=10.5f;
                POS=25.0f;
                POS5C=0.8f;
            }
            if (S16(0x62)>6 && S16(0x62)<15) {
                SpawnFloatXYAt453A70(0x32E,
                    float(*reinterpret_cast<signed char*>(RAW+0x66)*62)+F32(0x44),
                    (*(&POS48))+g_F714_ShotYAt00657868,
                    *reinterpret_cast<signed char*>(RAW+0x66),1);
            }
            if (S16(0x62)==15 && S16(0x64)==0 && S16(0xF00)<5) {
                SetAuxActionAt40FB40(11);
                ++S16(0xF00);
                break;
            }
            if (S16(0x62)==25 && S16(0x64)==0)
                SetAuxActionAt40FB40(23);
            break;
        }

#include "FighterFallingRadialsF711.inc"

#include "FighterApproachNativeF763.inc"
#include "FighterBossMovementF714.inc"
#include "FighterDoubleVolleyF718.inc"

#include "FighterLateStormF720.inc"
#include "FighterRandomVolleyF721.inc"
#include "FighterCloudRainF674.inc"
#include "FighterCloudBurstF676.inc"

#include "FighterStormVolleyTypedF768.inc"
#include "FighterAngleStormTypedF767.inc"
#include "FighterApproachVolleyNativeF764.inc"
#include "FighterGroundedVolleyTypedF771.inc"
#include "FighterFourTierVolleyF701.inc"
#include "FighterTerminalShotF681.inc"
#include "FighterTerminalCounterF674.inc"
#include "FighterNativeDefaultF778.inc"
    }
#include "FighterEarlySharedGetterTailF781.inc"
}
#undef OWNER
#undef I16
#undef RAW
