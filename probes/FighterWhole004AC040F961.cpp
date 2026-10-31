// F961 selected GROWING natural C++ original-shaped whole-parent fighter.
 // 82KB original GAME is NONEXACT: real cases restored from F938-F958
 // with their true C++ native game calls, still many original markers;
 // original full 0x720 stack frame and EBP this have not been restored.
 // Original whole callable exact CODE credit is ZERO.
 // F938 original full-function source PROBE,
// deliberately NONEXACT. The 0x59 game case is now real native-observed
// C++ rather than the historical placeholder in F652. Numerous other
// cases remain explicit markers. Never credit the parent as whole exact.
// Its original includes / stage variants are retained for independent
// full-VC7.1 recompilation and original-PE case verification.
// F539 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
class FighterSwitchF598_Boss004AC040 { public: void SpawnDirectedAt453A70(int,int,int,char,int); void SpawnWithFloatAt453A70(int,int,float,char,int); void SetMotionStateAt40FBB0(int,float,int); void ResetMotionAt40FC50(); void InitTrajectoryAt453E60(float); virtual void NativeVirtualFrameAdvance(); void Advance(); void ResetAt453E20(); void PrepareActionAt453D60(int); void StartAnimationAt46D000(int); void SpawnAt453C80(int,float,float,char,int); void SpawnMixedAt453C80(int,int,float,char,int); void ConfigureStormAt454BC0(int,int,int); void SpawnRawAt453C80(int,int,int,char,int); void SpawnSevenAt453B50(int,int,int,char,int,int,int); short GetNativeActionAt40FA30(); void SetNativeActionAt40FAC0(int); signed char ContactAt454EE0(); void SetAuxActionAt40FB40(int); };
extern unsigned int g_FighterProbeMarker;
extern signed char g_ModeAt006714B4;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_F747_BounceXAt006590BC;
extern float g_F747_BounceYAt00658044;
extern float g_F748_SpeedScaleAt006590B8;
extern float g_F948_C8UpperAt00657854;
extern float g_F948_C8DragAt00658350;
extern float g_F948_C8VolleyYAt00658268;
extern float g_F950_CAVolleyYAt00658400;
extern float g_ThresholdAt0065782C;
extern float g_AnimationDeltaAt0065747C;
extern float g_AnimationMaximumAt006583B4;
extern float g_JumpGroundCorrectionAt00658058;
extern double g_JumpReflectionAt006583E8;
extern float g_ApproachLowerAt00658290;
extern float g_ApproachUpperAt006592A4;
extern float g_StopThresholdAt00657480;
extern float g_TrajectoryUpperAt006590C4;
extern float g_ContactProjectionAt00657888;
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
void FighterSwitchF598_Boss004AC040::Advance() {
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
            break;
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
            break;
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
        case 0x4: POS = 6.0f; break;
        case 0x5: POS = -6.0f; break;
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
            if (S16(0x62) == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == 2) {
                    POS = 0.0f;
                    POS54 = 15.0f;
                    POS5C = 0.7f;
                    FLAG = 0;
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
                if (S16(0x62) == 2) {
                    FLAG = 0;
                    POS = 5.0f;
                    POS54 = 15.0f;
                    POS5C = 0.7f;
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
                if (S16(0x62) == 2) {
                    FLAG = 0;
                    POS = -4.0f;
                    POS54 = 15.0f;
                    POS5C = 0.7f;
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
            SetAuxActionAt40FB40(0);
        }
        break;
        case 0xA:
            if (I16(0x62) == 0 && I16(0x64) == 0)
                PrepareActionAt453D60(30);
            ResetAt453E20();
            if (GetNativeActionAt40FA30() == I16(0x70)) {
                if (I32(0x4E0) == 0)
                    SetNativeActionAt40FAC0(0);
                else
                    SetNativeActionAt40FAC0(1);
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
#define TRAJECTORY_STAGE_THRESHOLD 3
#define TRAJECTORY_EARLY_STATE 4
#define TRAJECTORY_LATE_STATE 5
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
#define F605_LATE47 5
#define F605_STAGE48 1
#define F605_EARLY48 2
#define F605_LATE48 5
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
#define F610_LATE 5
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
#include "FighterScriptedBounce59F813.inc"

#include "FighterThirdBossPair5D5EF939.inc"

#include "FighterThirdBossFacing5FF941.inc"
#include "FighterThirdBossVolley6061F942.inc"

#include "FighterThirdBossSelector62F943.inc"
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
#define F629_LATE 5
#define F629_COUNTER 0xF00
#include "FighterArcTrajectory91F629.inc"
#undef F629_STAGE
#undef F629_EARLY
#undef F629_LATE
#undef F629_COUNTER
#define F631_COUNTER 0xF00
#define F631_EXTRA_FLAG 0
#define F631_EXTRA_BEFORE 0
#include "FighterLandingTimer96F631.inc"
#undef F631_COUNTER
#undef F631_EXTRA_FLAG
#undef F631_EXTRA_BEFORE
#define F633_CASE 0x97
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
#define F633_CASE 0x98
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
#define F633_CASE 0x9A
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 0
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
#define F633_EXTRA_FLAG 0
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
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F637_EXTRA_FLAG 0
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
#define F645_AUX_ACTION 8
#include "FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#define F645_CASE 0xB5
#define F645_START_POS -8.0f
#define F645_AUX_ACTION 10
#include "FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#include "FighterThirdBossFourWayC8F948.inc"
#include "FighterThirdBossFourWayC9F949.inc"
#include "FighterThirdBossFourWayCAF950.inc"
#include "FighterThirdBossFourWayCBF951.inc"
#include "FighterThirdBossCCF953.inc"
#include "FighterThirdBossCDF953.inc"
#include "FighterThirdBossCEF955.inc"
#include "FighterFallStateCFF647.inc"
#include "FighterReflectLandingD0F646.inc"
#define F651_DECAY 3
#define F651_SPRITE 0x3e6
#include "FighterResourceShotD1F651.inc"
#undef F651_DECAY
#undef F651_SPRITE
#define F652_DECAY 3
#define F652_SPRITE 0x3e6
#define F652_SCALE_BEFORE 1
#include "FighterResourceShotD2F652.inc"
#undef F652_DECAY
#undef F652_SPRITE
#undef F652_SCALE_BEFORE
#include "FighterThirdBossStage12C12DF958.inc"

#include "FighterThirdBossStage12EF959.inc"
#include "FighterThirdBossStage12F130F961.inc"

        case 0x131: g_FighterProbeMarker = 306; break;
        case 0x133: g_FighterProbeMarker = 308; break;
        case 0x134: g_FighterProbeMarker = 309; break;
        case 0x135: g_FighterProbeMarker = 310; break;
        case 0x136: g_FighterProbeMarker = 311; break;
        case 0x186: g_FighterProbeMarker = 391; break;
        case 0x187: g_FighterProbeMarker = 392; break;
        case 0x188: g_FighterProbeMarker = 393; break;
        case 0x189: g_FighterProbeMarker = 394; break;
        case 0x190: g_FighterProbeMarker = 401; break;
        case 0x191: g_FighterProbeMarker = 402; break;
        case 0x192: g_FighterProbeMarker = 403; break;
        case 0x194: g_FighterProbeMarker = 405; break;
        case 0x195: g_FighterProbeMarker = 406; break;
        case 0x196: g_FighterProbeMarker = 407; break;
        case 0x197: g_FighterProbeMarker = 408; break;
        case 0x198: g_FighterProbeMarker = 409; break;
        case 0x199: g_FighterProbeMarker = 410; break;
        case 0x19A: g_FighterProbeMarker = 411; break;
        case 0x19B: g_FighterProbeMarker = 412; break;
        case 0x19C: g_FighterProbeMarker = 413; break;
        case 0x19D: g_FighterProbeMarker = 414; break;
        case 0x19E: g_FighterProbeMarker = 415; break;
        case 0x19F: g_FighterProbeMarker = 416; break;
        case 0x1A0: g_FighterProbeMarker = 417; break;
        case 0x1A1: g_FighterProbeMarker = 418; break;
        case 0x1A2: g_FighterProbeMarker = 419; break;
        case 0x1A3: g_FighterProbeMarker = 420; break;
        case 0x1A4: g_FighterProbeMarker = 421; break;
        case 0x1F4: g_FighterProbeMarker = 501; break;
        case 0x1F5: g_FighterProbeMarker = 502; break;
        case 0x1F6: g_FighterProbeMarker = 503; break;
        case 0x1F7: g_FighterProbeMarker = 504; break;
        case 0x1F8: g_FighterProbeMarker = 505; break;
        case 0x1F9: g_FighterProbeMarker = 506; break;
        case 0x1FA: g_FighterProbeMarker = 507; break;
        case 0x1FB: g_FighterProbeMarker = 508; break;
        case 0x1FC: g_FighterProbeMarker = 509; break;
        case 0x1FD: g_FighterProbeMarker = 510; break;
        case 0x252: g_FighterProbeMarker = 595; break;
        case 0x253: g_FighterProbeMarker = 596; break;
        case 0x254: g_FighterProbeMarker = 597; break;
        case 0x255: g_FighterProbeMarker = 598; break;
        case 0x256: g_FighterProbeMarker = 599; break;
        case 0x257: g_FighterProbeMarker = 600; break;
        case 0x258: g_FighterProbeMarker = 601; break;
        case 0x259: g_FighterProbeMarker = 602; break;
        case 0x25A: g_FighterProbeMarker = 603; break;
        case 0x25B: g_FighterProbeMarker = 604; break;
        case 0x25C: g_FighterProbeMarker = 605; break;
        case 0x25D: g_FighterProbeMarker = 606; break;
        case 0x25E: g_FighterProbeMarker = 607; break;
        case 0x25F: g_FighterProbeMarker = 608; break;
        case 0x260: g_FighterProbeMarker = 609; break;
        case 0x261: g_FighterProbeMarker = 610; break;
        case 0x262: g_FighterProbeMarker = 611; break;
        case 0x2BC: g_FighterProbeMarker = 701; break;
        case 0x2BD: g_FighterProbeMarker = 702; break;
        case 0x2BE: g_FighterProbeMarker = 703; break;
        case 0x2BF: g_FighterProbeMarker = 704; break;
        case 0x2C0: g_FighterProbeMarker = 705; break;
        case 0x2C1: g_FighterProbeMarker = 706; break;
        case 0x2C2: g_FighterProbeMarker = 707; break;
        case 0x2C3: g_FighterProbeMarker = 708; break;
        case 0x2DB: g_FighterProbeMarker = 732; break;
        case 0x2E5: g_FighterProbeMarker = 742; break;
        case 0x2E6: g_FighterProbeMarker = 743; break;
        case 0x2EF: g_FighterProbeMarker = 752; break;
        case 0x2F0: g_FighterProbeMarker = 753; break;
        case 0x2F9: g_FighterProbeMarker = 762; break;
        case 0x2FA: g_FighterProbeMarker = 763; break;
        case 0x2FB: g_FighterProbeMarker = 764; break;
        case 0x302: g_FighterProbeMarker = 771; break;
        case 0x303: g_FighterProbeMarker = 772; break;
        case 0x31B: g_FighterProbeMarker = 796; break;
        case 0x31C: g_FighterProbeMarker = 797; break;
        default: g_FighterProbeMarker = 0;
    }
}
#undef OWNER
#undef I16
#undef RAW
