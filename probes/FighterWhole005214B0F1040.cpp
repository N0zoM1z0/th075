#include "FighterAnimationPhaseBorrowedF1024.hpp"
extern float g_F898ShotYAt0065839C;
extern signed char g_CloudOpponentAt006714D0;
extern float g_F895AbsThresholdAt006591F4;
extern float g_F894VerticalStageAt00659090;
extern float g_F894RandomHeightAt006592A0;
extern float g_F893FloatFallAt00657478;
extern float g_F893VerticalStageAt006598B0;
extern float g_F892DistAt0065787C;
extern float F892AbsAt00412D90(float);
extern float g_F890GravityAt006581E0;
extern float g_F890Phase0YAt0065835C;
extern float g_F890Phase0AltYAt006591E4;
extern float g_F890Phase1LowYAt0065788C;
extern float g_F890Phase4HiYAt00659420;
extern float g_F890Phase4OtherYAt006598B4;
extern float g_F890Phase5YAt0065786C;
extern double g_F884DoubleDropAt00657D00;
extern float g_F884PhaseYAt006598B8;
extern float g_F884Stage5YAt00659470;
extern float g_F873GroundDropAt00658350;
extern float g_F872Volley1F9YAt006598BC;
extern float g_F872Volley1FAYAt00659310;
extern float g_F866DropAt006583FC;
extern float g_F865SustainScaleAt00658348;
extern float g_F861ShotYAt00659460;
extern float g_F860ShotYAt006581DC;
extern float g_F857ShotYAt00659298;
extern float g_F855ShotYAt00658400;
extern float g_F853OffsetYAt0065929C;
extern float g_F852GroundBounceMultiplierAt00657478;
extern float g_AdditionalGravityAt00659090;
extern float g_F834_UpperAt00657CBC;
extern float g_F834_LowerAt006590B0;
struct FighterBorrowedXViewF833 { unsigned char observedUnknown[0x44]; float xAt44; };
extern float g_F701_VolleyYAt00658268;
extern float g_AnimationDeltaAt0065747C;
extern float g_AnimationMaximumAt006583B4;
extern float g_JumpGroundCorrectionAt00658058;
extern double g_JumpReflectionAt006583E8;
extern float g_F748_SpeedScaleAt006590B8;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_F747_BounceXAt006590BC;
extern float g_F747_BounceYAt00658044;
// F874: only the real native caller methods of actor+0x2E8 are borrowed.
class FighterBorrowedOwnerF874 {
public:
    void SetNativeActionAt40FAC0(int action);
    void ResetAt453E20();
};
// F539 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
class FighterSwitchF598_Boss005214B0 { public: void SpawnDirectedAt453A70(int,int,int,char,int); void SpawnFloatXRawYAt453A70(int,float,int,char,int); void SpawnFloatXYAt453A70(int,float,float,char,int); void SpawnWithFloatAt453A70(int,int,float,char,int); void SetMotionStateAt40FBB0(int,float,int); int RandomBoundaryAt455580(int,int); void SetFloatMotionAt40FBB0(float,float,int); void AnimatePushAt453E80(int); void SpawnExtraAt453B50(int,int,float,char,int,int,int); void SpawnExtraRawYAt453B50(int,int,int,char,int,int,int); void ResetMotionAt40FC50(); void ApplyStateAt454A70(int); void EmitStateAt452B30(); void InitTrajectoryAt453E60(float); void Advance(); void ResetAt453E20(); void PrepareActionAt453D60(int); void SetupCollisionAt454BC0(int,int,int); void SpawnRawAt453C80(int,int,int,char,int); void SpawnFloatXRawYAt453C80(int,float,int,char,int); void NativeGameEffectAt455B30(); virtual void NativeVirtualFrameAdvance(); void PrepareActionAt453D40(int); void ConfigureStormAt454BC0(int,int,int); void SpawnMixedAt453C80(int,int,float,char,int); void StartAnimationAt46D000(int); void SpawnAt453C80(int,float,float,char,int); short GetNativeActionAt40FA30(); void SetNativeActionAt40FAC0(int); signed char ContactAt454EE0(); void SetAuxActionAt40FB40(int); };
extern unsigned int g_FighterProbeMarker;
extern signed char g_ModeAt006714B4;
extern float g_ThresholdAt0065782C;
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
void FighterSwitchF598_Boss005214B0::Advance() {
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
            goto native_script_shared_getter;
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
            goto native_script_shared_getter;
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
        case 0x4: POS = 3.0f; goto native_script_shared_getter;
        case 0x5: POS = -3.0f; goto native_script_shared_getter;
        case 0x6:
            if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0 &&
                    (U8(0x511) == 3 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCC);
                return;
            }
            if (F1024_PHASE(this).stageAt62 == 0 && FLAG == 0)
                ResetAt453E20();
            if (F1024_PHASE(this).stageAt62 > 2) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            if (F1024_PHASE(this).stageAt62 == 4 && POS54 < g_ExtraThresholdAt00657D14)
                SetAuxActionAt40FB40(5);
            if (GetNativeActionAt40FA30() == I16(0x70))
                SetAuxActionAt40FB40(11);
            if (F1024_PHASE(this).stageAt62 == 3 && F1024_PHASE(this).frameAt64 == 0) {
                POS = 0.0f;
                POS54 = 16.0f;
                POS5C = 0.8f;
                FLAG = 0;
            }
            break;
        case 0x7:
            if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0 &&
                    (U8(0x511) == 5 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCD);
                return;
            }
            if (F1024_PHASE(this).stageAt62 == 0 && FLAG == 0)
                ResetAt453E20();
            if (F1024_PHASE(this).stageAt62 > 2) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            if (GetNativeActionAt40FA30() == I16(0x70))
                SetNativeActionAt40FAC0(9);
            if (F1024_PHASE(this).stageAt62 == 3 && F1024_PHASE(this).frameAt64 == 0) {
                POS = 5.5f;
                POS54 = 16.0f;
                POS5C = 0.8f;
                FLAG = 0;
            }
            break;
        case 0x8:
            if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0 &&
                    (U8(0x511) == 4 || FLAG > 0)) {
                SetNativeActionAt40FAC0(0xCE);
                return;
            }
            if (F1024_PHASE(this).stageAt62 == 0 && FLAG == 0)
                ResetAt453E20();
            if (F1024_PHASE(this).stageAt62 > 2) {
                POS54 = POS54 - POS5C;
                if (POS48 + POS54 <= g_ThresholdAt0065782C) {
                    SetNativeActionAt40FAC0(10);
                    POS48 = 0.0f;
                    ResetAt453E20();
                    return;
                }
            }
            if (GetNativeActionAt40FA30() == I16(0x70))
                SetAuxActionAt40FB40(13);
            if (F1024_PHASE(this).stageAt62 == 3 && F1024_PHASE(this).frameAt64 == 0) {
                POS = -5.5f;
                POS54 = 16.0f;
                POS5C = 0.8f;
                FLAG = 0;
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

#define F605_STAGE47 3
#define F605_EARLY47 4
#define F605_LATE47 7
#define F605_STAGE48 3
#define F605_EARLY48 4
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
#define F610_STAGE 3
#define F610_EARLY 4
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
#include "FighterScriptedBounce59F813.inc"
#define F617_CASE 0x5D
#define F617_THRESHOLD 19
#define F617_BEGIN_STAGE 6
#define F617_FINISH_STATE 18
#define F617_START_SPEED 8.0f
#define F617_START_POS 13.5f
#define F617_FRICTION 0.6000000238418579f
#include "FighterAirTransitionCaseF617.inc"
#undef F617_CASE
#undef F617_THRESHOLD
#undef F617_BEGIN_STAGE
#undef F617_FINISH_STATE
#undef F617_START_SPEED
#undef F617_START_POS
#undef F617_FRICTION
#define F617_CASE 0x5E
#define F617_THRESHOLD 18
#define F617_BEGIN_STAGE 6
#define F617_FINISH_STATE 16
#define F617_START_SPEED 8.0f
#define F617_START_POS -13.5f
#define F617_FRICTION 0.6000000238418579f
#include "FighterAirTransitionCaseF617.inc"
#undef F617_CASE
#undef F617_THRESHOLD
#undef F617_BEGIN_STAGE
#undef F617_FINISH_STATE
#undef F617_START_SPEED
#undef F617_START_POS
#undef F617_FRICTION
#define F620_FIRST_ACTION 0
#define F620_SECOND_ACTION 1
#include "FighterScriptedFacingF816.inc"
#undef F620_FIRST_ACTION
#undef F620_SECOND_ACTION
#include "FighterScriptedResourceVolleysF816.inc"

#include "FighterScriptedResourceSelectorF817.inc"
#include "FighterMode63BasicF626.inc"
#define F628_CASE 0x8C
#define F628_COUNTER 0xF00
#define F628_START_POS -11.0f
#define F628_LIMIT 5
#include "FighterScriptedJumpLandingF820.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x8F
#define F628_COUNTER 0xF00
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "FighterScriptedJumpLandingF820.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x90
#define F628_COUNTER 0xF00
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "FighterScriptedJumpLandingF820.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F629_STAGE 3
#define F629_EARLY 4
#define F629_LATE 7
#define F629_COUNTER 0xF00
#include "FighterScriptedArc91F821.inc"
#undef F629_STAGE
#undef F629_EARLY
#undef F629_LATE
#undef F629_COUNTER
#define F631_COUNTER 0xF00
#define F631_EXTRA_FLAG 0
#define F631_EXTRA_BEFORE 0
#include "FighterScriptedLanding96F822.inc"
#undef F631_COUNTER
#undef F631_EXTRA_FLAG
#undef F631_EXTRA_BEFORE
#define F633_CASE 0x97
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "FighterScriptedLandingSiblingsF822.inc"
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
#include "FighterScriptedLandingSiblingsF822.inc"
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
#include "FighterScriptedLandingSiblingsF822.inc"
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
#include "FighterScriptedLandingPairF823.inc"
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
#include "FighterScriptedLandingPairF823.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F637_EXTRA_FLAG 0
#define F637_EXTRA_BEFORE 0
#define F637_STRICT_ABOVE 0
#include "FighterScriptedGroundBoostF824.inc"
#undef F637_EXTRA_FLAG
#undef F637_EXTRA_BEFORE
#undef F637_STRICT_ABOVE
#define F633_CASE 0x9F
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "FighterScriptedLandingSiblingsF822.inc"
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
#include "FighterScriptedLandingSiblingsF822.inc"
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
#include "FighterScriptedLandingSiblingsF822.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F641_CASE 0xA3
#define F641_START_HEIGHT -9.0f
#define F641_NEXT_ACTION 2
#include "FighterScriptedNoCounterF826.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F641_CASE 0xA4
#define F641_START_HEIGHT -10.0f
#define F641_NEXT_ACTION 2
#include "FighterScriptedNoCounterF826.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F641_CASE 0xA5
#define F641_START_HEIGHT -13.0f
#define F641_NEXT_ACTION 2
#include "FighterScriptedNoCounterF826.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F642_CASE 0xA7
#define F642_COUNTER 0xF00
#define F642_NEXT_ACTION 0
#include "FighterScriptedProjectileLaunchF827.inc"
#undef F642_CASE
#undef F642_COUNTER
#undef F642_NEXT_ACTION
#define F642_CASE 0xA8
#define F642_COUNTER 0xF00
#define F642_NEXT_ACTION 2
#include "FighterScriptedProjectileLaunchF827.inc"
#undef F642_CASE
#undef F642_COUNTER
#undef F642_NEXT_ACTION
#define F645_CASE 0xB4
#define F645_START_POS 8.0f
#define F645_AUX_ACTION 8
#include "FighterScriptedMotionRestartF829.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#define F645_CASE 0xB5
#define F645_START_POS -8.0f
#define F645_AUX_ACTION 10
#include "FighterScriptedMotionRestartF829.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#include "FighterScriptedFourWayC8F834.inc"
#include "FighterScriptedFourWayC9F833.inc"
#include "FighterScriptedFourWayCAF836.inc"
#include "FighterScriptedFourWayCBF837.inc"
#include "FighterScriptedComplexCCF839.inc"
#include "FighterScriptedComplexCDF840.inc"
#include "FighterScriptedComplexCEF841.inc"
#include "FighterScriptedFallStateCFF831.inc"
#include "FighterScriptedReflectD0F830.inc"
#define F651_DECAY 6
#define F651_SPRITE 0x3E6
#include "FighterScriptedResourceShotD1F832.inc"
#undef F651_DECAY
#undef F651_SPRITE
#define F652_DECAY 6
#define F652_SPRITE 0x3E6
#define F652_SCALE_BEFORE 1
#include "FighterScriptedResourceShotD2F832.inc"
#undef F652_DECAY
#undef F652_SPRITE
#undef F652_SCALE_BEFORE
#define F653_ACTION 0x12C
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 1
#define F653_PREPARE_ANIM 0x1B
#define F653_CLEAR_F00 0
#include "FighterScriptedFallingRecoveryF842.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#define F653_ACTION 0x12D
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 3
#define F653_PREPARE_ANIM 0x1C
#define F653_CLEAR_F00 1
#include "FighterScriptedFallingRecoveryF842.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#define F653_ACTION 0x12E
#define F653_NEXT_ACTION 2
#define F653_PREPARE_FRAME 2
#define F653_PREPARE_ANIM 0x1C
#define F653_CLEAR_F00 0
#include "FighterScriptedFallingRecoveryF842.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#define F653_ACTION 0x12F
#define F653_NEXT_ACTION 2
#define F653_PREPARE_FRAME 1
#define F653_PREPARE_ANIM 0x1B
#define F653_CLEAR_F00 0
#include "FighterScriptedFallingRecoveryF842.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#include "FighterScriptedGrounded130F844.inc"
#include "FighterScriptedGrounded131F845.inc"
#include "FighterScriptedSideStep133F846.inc"
#include "FighterScriptedProjectile134F847.inc"
#include "FighterScriptedProjectile135F847.inc"
#include "FighterScriptedGroundPhysics136F849.inc"
#include "FighterScriptedGround186F850.inc"
#include "FighterScriptedGround187F850.inc"
#include "FighterScriptedGround188F851.inc"
#include "FighterScriptedBounce189F852.inc"
#include "FighterScriptedFloatShot18AF853.inc"
#include "FighterScriptedVolley18BF855.inc"
#include "FighterScriptedStage190F856.inc"
#include "FighterScriptedFloatShot191F857.inc"
#include "FighterScriptedStage192F858.inc"
#include "FighterScriptedGround194F859.inc"
#include "FighterScriptedStage196F860.inc"
#include "FighterScriptedStage198F861.inc"
#include "FighterScriptedStage19AF862.inc"
#include "FighterScriptedShort19CF863.inc"
#include "FighterScriptedShort19EF863.inc"
#include "FighterScriptedSustain1A0F865.inc"
#include "FighterScriptedDoubleProjectile1F4F866.inc"
#include "FighterScriptedStaged1F5F867.inc"
#include "FighterScriptedConditional1F6F868.inc"
#include "FighterScriptedConditional1F7F869.inc"
#include "FighterScriptedGroundBounce1F8F870.inc"
#include "FighterScriptedVolley1F9F872.inc"
#include "FighterScriptedVolley1FAF872.inc"
#include "FighterScriptedRecovery1FBF873.inc"
#include "FighterScriptedRecovery1FCF873.inc"
#include "FighterScriptedBorrowedOwner1FDF874.inc"
#include "FighterScriptedBorrowedOwner1FEF874.inc"
#include "FighterScriptedOwnerStages1FFF875.inc"
#include "FighterScriptedOwnerWave200F877.inc"
#include "FighterScriptedStage201F878.inc"
#include "FighterScriptedStage252F879.inc"
#include "FighterScriptedStage253F879.inc"
#include "FighterScriptedStage254F879.inc"
#include "FighterScriptedStage255F880.inc"
#include "FighterScriptedStage256F880.inc"
#include "FighterScriptedStage257F880.inc"
#include "FighterScriptedFloatX258F881.inc"
#include "FighterScriptedFloatX259F883.inc"
#include "FighterScriptedStage2BCF884.inc"
#include "FighterScriptedStage2BDF885.inc"
#include "FighterScriptedStage2BEF886.inc"
#include "FighterScriptedStage2BFF887.inc"
#include "FighterScriptedStage2C0F888.inc"
#include "FighterScriptedStage2C1F888.inc"
#include "FighterScriptedFull2C2F890.inc"
#include "FighterScriptedTransition2C3F891.inc"
#include "FighterScriptedStage2DBF892.inc"
#include "FighterScriptedStage2DCF893.inc"
#include "FighterScriptedStage2DDF894.inc"
#include "FighterScriptedStage2E4F895.inc"
#include "FighterScriptedRandomPair2E5F896.inc"
#include "FighterScriptedRandomPair2E6F896.inc"
#define F897_CASE 0x2E7
#define F897_SECOND_SPRITE 0x38B
#include "FighterScriptedFourShots2E7F897.inc"
#undef F897_CASE
#undef F897_SECOND_SPRITE
#define F897_CASE 0x2E8
#define F897_SECOND_SPRITE 0x38B
#include "FighterScriptedFourShots2E7F897.inc"
#undef F897_CASE
#undef F897_SECOND_SPRITE
#define F897_CASE 0x2E9
#define F897_SECOND_SPRITE 0x38C
#include "FighterScriptedFourShots2E7F897.inc"
#undef F897_CASE
#undef F897_SECOND_SPRITE
#define F897_CASE 0x2EA
#define F897_SECOND_SPRITE 0x38C
#include "FighterScriptedFourShots2E7F897.inc"
#undef F897_CASE
#undef F897_SECOND_SPRITE
#include "FighterScriptedStage2F0F898.inc"
#include "FighterScriptedStage2F8F899.inc"
#include "FighterScriptedTail31BF901.inc"
#include "FighterScriptedTail31CF901.inc"
#include "FighterScriptedNativeDefaultF806.inc"
    }
#include "FighterScriptedSharedGetterF806.inc"
}
#undef OWNER
#undef I16
#undef RAW
