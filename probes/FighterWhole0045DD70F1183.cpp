// F1183 live whole original 0045DD70 parent, continued from the existing
// F652 native D1/D2 source. The complete 60,999B callable is NONEXACT.
// Missing states remain explicit research markers and earn no CODE credit.
// Preserve independently reviewed current bodies and all six table groups.
class FighterSwitchF598_Boss0045DD70 { public: void SetMotionStateAt40FBB0(int,float,int); void SetMotionFloatAt40FBB0(float,float,float); void ResetMotionAt40FC50(); void SpawnDirectedAt453A70(int,int,int,char,int); void SpawnWithFloatAt453A70(int,int,float,char,int); void SpawnFloatXYAt453A70(int,float,float,char,int); void InitTrajectoryAt453E60(float); virtual void NativeVirtualFrameAdvance(); void Advance(); void ResetAt453E20(); void PrepareActionAt453D60(int); void StartAnimationAt46D000(int); void SpawnAt453C80(int,float,float,char,int); short GetNativeActionAt40FA30(); void SetNativeActionAt40FAC0(int); signed char ContactAt454EE0(); void SetAuxActionAt40FB40(int); };
extern unsigned int g_FighterProbeMarker;
extern float g_ThresholdAt0065782C;
extern float g_ReimuShotYAt006590A4;
extern float g_ReimuRotationStepAt00657858;
extern float g_ReimuBounceXAt006590BC;
extern float g_ReimuBounceYAt00658044;
extern float g_ReimuRecoveryScaleAt006590B8;
extern signed char g_ModeAt006714B4;
extern float g_ReimuAirDragAt00658348;
extern float g_ReimuGroundDragAt00658350;
extern float g_ReimuLateDragAt006581E0;
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
void FighterSwitchF598_Boss0045DD70::Advance() {
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
        case 0x4: POS = 4.5f; break;
        case 0x5: POS = -4.5f; break;
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
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == 2) {
                    POS = 0.0f;
                    POS54 = 12.5f;
                    POS5C = 0.55f;
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
            ++S16(0x64);
            if (S16(0x64) >= S16(0x72)) {
                S16(0x64) = 0;
                ++S16(0x62);
                if (S16(0x62) == 2) {
                    POS = 4.0f;
                    POS54 = 12.5f;
                    POS5C = 0.55f;
                    FLAG = 0;
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
                    POS = -4.0f;
                    POS54 = 12.5f;
                    POS5C = 0.55f;
                    FLAG = 0;
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
                    SetNativeActionAt40FAC0(2);
            }
            break;
        #include "FighterSingletonContactF598.inc"
#define CONTACT_STAGE_OFFSET 0xF00
#include "FighterAdditionalContactF600.inc"
#undef CONTACT_STAGE_OFFSET
#define TRAJECTORY_LOWER_THRESHOLD g_StopThresholdAt00657480
#define TRAJECTORY_UPPER_THRESHOLD g_TrajectoryUpperAt006590C4
#define TRAJECTORY_MINIMUM_SPEED 2.0f
#define TRAJECTORY_MAXIMUM_SPEED 12.0f
#define TRAJECTORY_STAGE_THRESHOLD 3
#define TRAJECTORY_EARLY_STATE 4
#define TRAJECTORY_LATE_STATE 5
#define CONTACT_STAGE_OFFSET 0xF00
#define TRAJECTORY_SPAWN_KIND 0x3B7
#define TRAJECTORY_SPAWN_SIDE 1
#include "FighterTrajectorySpawn46F603.inc"
#undef TRAJECTORY_SPAWN_KIND
#undef TRAJECTORY_SPAWN_SIDE
#undef TRAJECTORY_LOWER_THRESHOLD
#undef TRAJECTORY_UPPER_THRESHOLD
#undef TRAJECTORY_MINIMUM_SPEED
#undef TRAJECTORY_MAXIMUM_SPEED
#undef TRAJECTORY_STAGE_THRESHOLD
#undef TRAJECTORY_EARLY_STATE
#undef TRAJECTORY_LATE_STATE
#undef CONTACT_STAGE_OFFSET

#define F606_ACTION 0x47
#define F606_DRAG 0.8f
#define F606_STAGE 1
#define F606_EARLY 2
#define F606_LATE 5
#define F606_PROJECTILE 0x3B7
#define F606_SIDE 1
#define F606_COUNTER 0xF00
#include "FighterTrajectoryFollowupSpawnF606.inc"
#undef F606_ACTION
#undef F606_DRAG
#undef F606_STAGE
#undef F606_EARLY
#undef F606_LATE
#undef F606_PROJECTILE
#undef F606_SIDE
#undef F606_COUNTER
#define F605_STAGE48 1
#define F605_EARLY48 2
#define F605_LATE48 5
#define F605_COUNTER 0xF00
case 0x48: {
    if (I16(0x62)==0 && I16(0x64)==0) {
        POS = -F32(0x94);
        I32(0x54) = I32(0x98);
        POS5C = 1.3f;
        I32(0x7C) = 0;
    }
    if (I16(0x62)==F605_STAGE48 && POS54 < g_StopThresholdAt00657480) {
        SetAuxActionAt40FB40(F605_EARLY48);
        break;
    }
    POS54 = POS54 - POS5C;
    if (POS54 + POS48 <= g_ThresholdAt0065782C) {
        I16(F605_COUNTER) = static_cast<short>(POS * g_ContactProjectionAt00657888);
        I16(F605_COUNTER+2) = static_cast<short>((POS54) * g_ContactProjectionAt00657888);
        ResetAt453E20();
        POS48 = 0.0f;
        SetNativeActionAt40FAC0(0x61);
        InitTrajectoryAt453E60(2.0f);
        PrepareActionAt453D60(0x16);
        break;
    }
    if (GetNativeActionAt40FA30() == I16(0x70))
        SetAuxActionAt40FB40(F605_LATE48);
    break;
}

#undef F605_STAGE48
#undef F605_EARLY48
#undef F605_LATE48
#undef F605_COUNTER
#define F608_PROJECTILE 0x3B7
#define F608_SIDE 1
#define F608_COUNTER 0xF00
#include "FighterTrajectoryLandingSpawnF608.inc"
#undef F608_PROJECTILE
#undef F608_SIDE
#undef F608_COUNTER
#define F611_PROJECTILE 0x3B7
#define F611_SIDE 1
#define F610_STAGE 1
#define F610_EARLY 2
#define F610_LATE 5
#define F610_COUNTER 0xF00
#define F610_PREPARE_BEFORE 0
#include "FighterTrajectoryBounceSpawn4AF611.inc"
#undef F611_PROJECTILE
#undef F611_SIDE
#undef F610_STAGE
#undef F610_EARLY
#undef F610_LATE
#undef F610_COUNTER
#undef F610_PREPARE_BEFORE
#define F613_COUNTER 0xF00
#include "FighterTrajectoryRecovery4CF613.inc"
#undef F613_COUNTER
#define F614_COUNTER 0xF00
#define F614_STAGE1_SPAWN 1
#define F614_PROJECTILE 0x3B7
#define F614_SIDE 1
#include "FighterTrajectoryBurst58F614.inc"
#undef F614_COUNTER
#undef F614_STAGE1_SPAWN
#undef F614_PROJECTILE
#undef F614_SIDE
#include "ReimuEarlyRecoveryStatesF1184.inc"






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
#define F630_STAGE 1
#define F630_EARLY 2
#define F630_LATE 5
#define F630_COUNTER 0xF00
#define F630_PROJECTILE 0x3b7
#define F630_SIDE 1
#include "FighterArcSpawn91F630.inc"
#undef F630_STAGE
#undef F630_EARLY
#undef F630_LATE
#undef F630_COUNTER
#undef F630_PROJECTILE
#undef F630_SIDE
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
#define F645_AUX_ACTION 7
#include "FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#define F645_CASE 0xB5
#define F645_START_POS -8.0f
#define F645_AUX_ACTION 5
#include "FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
        case 0xC8: g_FighterProbeMarker = 201; break;
        case 0xC9: g_FighterProbeMarker = 202; break;
        case 0xCA: g_FighterProbeMarker = 203; break;
        case 0xCB: g_FighterProbeMarker = 204; break;
        case 0xCC: g_FighterProbeMarker = 205; break;
        case 0xCD: g_FighterProbeMarker = 206; break;
        case 0xCE: g_FighterProbeMarker = 207; break;
        case 0xCF: g_FighterProbeMarker = 208; break;
        case 0xD0: g_FighterProbeMarker = 209; break;
#define F651_DECAY 3
#define F651_SPRITE 0x3e5
#include "FighterResourceShotD1F651.inc"
#undef F651_DECAY
#undef F651_SPRITE
#define F652_DECAY 3
#define F652_SPRITE 0x3e5
#define F652_SCALE_BEFORE 1
#include "FighterResourceShotD2F652.inc"
#undef F652_DECAY
#undef F652_SPRITE
#undef F652_SCALE_BEFORE
#include "ReimuFallingStatesF1183.inc"










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
        case 0x19A: g_FighterProbeMarker = 411; break;
        case 0x19B: g_FighterProbeMarker = 412; break;
        case 0x19C: g_FighterProbeMarker = 413; break;
        case 0x19D: g_FighterProbeMarker = 414; break;
        case 0x19E: g_FighterProbeMarker = 415; break;
        case 0x1A0: g_FighterProbeMarker = 417; break;
        case 0x1A1: g_FighterProbeMarker = 418; break;
        case 0x1F4: g_FighterProbeMarker = 501; break;
        case 0x1F5: g_FighterProbeMarker = 502; break;
        case 0x1F6: g_FighterProbeMarker = 503; break;
        case 0x1F7: g_FighterProbeMarker = 504; break;
        case 0x1F8: g_FighterProbeMarker = 505; break;
        case 0x1FA: g_FighterProbeMarker = 507; break;
        case 0x1FB: g_FighterProbeMarker = 508; break;
        case 0x252: g_FighterProbeMarker = 595; break;
        case 0x253: g_FighterProbeMarker = 596; break;
        case 0x254: g_FighterProbeMarker = 597; break;
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
        case 0x263: g_FighterProbeMarker = 612; break;
        case 0x2BC: g_FighterProbeMarker = 701; break;
        case 0x2BD: g_FighterProbeMarker = 702; break;
        case 0x2BE: g_FighterProbeMarker = 703; break;
        case 0x2BF: g_FighterProbeMarker = 704; break;
        case 0x2C0: g_FighterProbeMarker = 705; break;
        case 0x2C1: g_FighterProbeMarker = 706; break;
        case 0x2C2: g_FighterProbeMarker = 707; break;
        case 0x2C3: g_FighterProbeMarker = 708; break;
        case 0x2D0: g_FighterProbeMarker = 721; break;
        case 0x2D1: g_FighterProbeMarker = 722; break;
        case 0x2D2: g_FighterProbeMarker = 723; break;
        case 0x2D3: g_FighterProbeMarker = 724; break;
        case 0x2DB: g_FighterProbeMarker = 732; break;
        case 0x2DF: g_FighterProbeMarker = 736; break;
        case 0x2E0: g_FighterProbeMarker = 737; break;
        case 0x2E5: g_FighterProbeMarker = 742; break;
        case 0x2EF: g_FighterProbeMarker = 752; break;
        case 0x2F9: g_FighterProbeMarker = 762; break;
        case 0x303: g_FighterProbeMarker = 772; break;
        case 0x304: g_FighterProbeMarker = 773; break;
        case 0x31B: g_FighterProbeMarker = 796; break;
        case 0x31C: g_FighterProbeMarker = 797; break;
        default: g_FighterProbeMarker = 0;
    }
}
#undef OWNER
#undef I16
#undef RAW
