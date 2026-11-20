// Partial native-source reconstruction of MarisaFighter::Advance at 0x00486550.
// It contains only the recovered game states listed below; unimplemented
// states deliberately fall through the genuine native default action.
#include "MarisaFighter.hpp"
class MarisaFighterAdvanceProbe : public MarisaFighter {
public:
    virtual void Advance();
};
extern signed char g_ModeAt006714B4;
extern float g_ThresholdAt0065782C;
extern float g_F748_SpeedScaleAt006590B8;
extern float g_MarisaCommandSpeedUpperAt006592A0;
extern float g_MarisaCommandSpeedLowerAt00657850;
extern float g_MarisaCommandYAt00658268;
extern float g_MarisaSpecialYCorrectionAt00658290;
extern float g_MarisaSpecialDriftAt006578C0;
extern float g_MarisaSpecialProjectileYAt0065929C;
extern float g_MarisaSpecialProjectileYAt00658400;
extern float g_MarisaProjectilePairYAt00657CF8;
extern float g_MarisaHorizontalSlowdownAt00659094;
extern float g_MarisaOpponentBoundaryAt00657884;
extern float g_MarisaRandomEffectYAt00657858;
extern float g_MarisaRandomEffectXAt00657878;
extern float g_MarisaResourceYAt00659298;
extern float g_MarisaResourceYAt006590A4;
extern float g_MarisaResourceYAt00659294;
extern float g_MarisaResourceYAt006581DC;
extern float g_MarisaResourceYAt00659290;
extern float g_MarisaResourceYAt00659270;
extern float g_MarisaResourceYAt0065928C;
extern float g_MarisaResourceYAt00659288;
extern float g_MarisaResourceYAt00659284;
extern float g_MarisaResourceYAt0065927C;
extern float g_MarisaResourceYAt0065908C;
extern float g_MarisaRandomVelocityYBaseAt00657D70;
extern float g_MarisaCardFallAt00659264;
extern float g_MarisaResourceYAt00659280;
extern float g_MarisaResourceYAt00659290;
extern float g_MarisaResourceYAt006590AC;
extern float g_MarisaMinimumDriftAt00659278;
extern float g_MarisaHighBoundaryAt0065926C;
extern float g_MarisaResourceYAt00659274;
extern float g_MarisaNegativeCardDriftAt00659268;
extern signed char g_MarisaDifficultyAt006714D0;
extern float g_MarisaCardVelocityScaleAt006590B4;
extern float g_F728_RandomOffsetYAt00657858;
extern float g_F747_BounceXAt006590BC;
extern float g_F747_BounceYAt00658044;
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
void MarisaFighterAdvanceProbe::Advance() {
    if (field082 != 0 || opponent->field3BA != 0)
        return;
    if (action == 0x32) {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            field07C = 0;
        }
        if (velocityX < g_ThresholdAt0065782C) {
            velocityX += g_JumpGroundCorrectionAt00658058;
            if (velocityX > g_ThresholdAt0065782C)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE != 0)
            field490 = velocityX * static_cast<float>(g_JumpReflectionAt006583E8);
        if (AdvanceNestedFrame() == field070)
            ResetPrimaryCounters(0);
        return;
    }
    switch (action) {
        case 0x0:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            break;
        case 0x1:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(2);
            break;
        case 0x2:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            break;
        case 0x3:
            if (field3AC == 0) {
                ClearMotionFields();
            } else {
                if (velocityX > g_ThresholdAt0065782C) {
                    velocityX -= g_SubtractAt00657478;
                    if (velocityX < g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if (velocityX < g_ThresholdAt0065782C) {
                    velocityX += g_RiseAt00658050;
                    if (velocityX > g_ThresholdAt0065782C) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            break;
        case 0x4:
            velocityX = 6.0f;
            AdvanceNestedFrame();
            return;
        case 0x5:
            velocityX = -6.0f;
            AdvanceNestedFrame();
            return;
        case 0x6:
            if (animationStage == 0 && animationFrame == 0 &&
                    (aiCommand == 3 || field3AC > 0)) {
                ResetPrimaryCounters(0xCC);
                return;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame >= field072) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 4) {
                    velocityX = 0.0f;
                    velocityY = 16.0f;
                    field05C = 0.75f;
                    field3AC = 0;
                }
                if (animationStage >= field070)
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x7:
            if (animationStage == 0 && animationFrame == 0 &&
                    (aiCommand == 5 || field3AC > 0)) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < g_ExtraThresholdAt00657D14)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame >= field072) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 4) {
                    velocityX = 5.0f;
                    velocityY = 16.0f;
                    field05C = 0.75f;
                    field3AC = 0;
                }
                if (animationStage >= field070)
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x8:
            if (animationStage == 0 && animationFrame == 0 &&
                    (aiCommand == 4 || field3AC > 0)) {
                ResetPrimaryCounters(0xCE);
                return;
            }
            if (animationStage == 0 && field3AC == 0)
                ClearMotionFields();
            if (y > g_ThresholdAt0065782C) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= g_ThresholdAt0065782C) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if (animationFrame >= field072) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 4) {
                    velocityX = -4.0f;
                    field3AC = 0;
                    velocityY = 16.0f;
                    field05C = 0.75f;
                }
                if (animationStage >= field070)
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x9:
        if (field05C == g_ThresholdAt0065782C)
            field05C = 0.6f;
        velocityY = velocityY - field05C;
        if (y + velocityY <= g_ThresholdAt0065782C) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == field070) {
            ResetSecondaryCounter(0);
        }
        break;
        case 0xA:
            if (animationStage == 0 && animationFrame == 0)
                PlaySharedSound(30);
            ClearMotionFields();
            if (AdvanceNestedFrame() == field070) {
                if (inputY == 0)
                    ResetPrimaryCounters(3);
                else
                    ResetPrimaryCounters(2);
            }
            break;
        #include "FighterSingletonContactF598.inc"
#include "MarisaFighterAdditionalContactF600.inc"
#define TRAJECTORY_LOWER_THRESHOLD g_ApproachLowerAt00658290
#define TRAJECTORY_UPPER_THRESHOLD g_ApproachUpperAt006592A4
#define TRAJECTORY_MINIMUM_SPEED 6.0f
#define TRAJECTORY_MAXIMUM_SPEED 25.0f
#define TRAJECTORY_STAGE_THRESHOLD 3
#define TRAJECTORY_EARLY_STATE 4
#define TRAJECTORY_LATE_STATE 7
#include "MarisaFighterTrajectoryContact46F602.inc"
#undef TRAJECTORY_LOWER_THRESHOLD
#undef TRAJECTORY_UPPER_THRESHOLD
#undef TRAJECTORY_MINIMUM_SPEED
#undef TRAJECTORY_MAXIMUM_SPEED
#undef TRAJECTORY_STAGE_THRESHOLD
#undef TRAJECTORY_EARLY_STATE
#undef TRAJECTORY_LATE_STATE
#define F605_STAGE47 3
#define F605_EARLY47 4
#define F605_LATE47 7
#define F605_STAGE48 3
#define F605_EARLY48 4
#define F605_LATE48 7
#include "MarisaFighterTrajectoryFollowupsF605.inc"
#undef F605_STAGE47
#undef F605_EARLY47
#undef F605_LATE47
#undef F605_STAGE48
#undef F605_EARLY48
#undef F605_LATE48
#include "MarisaFighterTrajectoryLanding49F607.inc"
#define F610_STAGE 3
#define F610_EARLY 4
#define F610_LATE 7
#define F610_PREPARE_BEFORE 1
#include "MarisaFighterTrajectoryBounce4AF610.inc"
#undef F610_STAGE
#undef F610_EARLY
#undef F610_LATE
#include "MarisaFighterTrajectoryRecovery4CF613.inc"
#define F614_STAGE1_SPAWN 0
#define F614_PROJECTILE 0x3E7
#define F614_SIDE 0
#include "MarisaFighterTrajectoryBurst58F614.inc"
#include "MarisaFighterScriptedBounce59.inc"
#include "MarisaFighterEarlyBounce5D5E5F.inc"
#include "MarisaFighterResourceVolleys6061.inc"
#include "MarisaFighterResourceSelector62.inc"
#undef F614_STAGE1_SPAWN
#undef F614_PROJECTILE
#undef F614_SIDE
#include "MarisaFighterMode63BasicF626.inc"
#define F628_CASE 0x8C
#define F628_START_POS -11.0f
#define F628_LIMIT 5
#include "MarisaFighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x8F
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "MarisaFighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x90
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "MarisaFighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_START_POS
#undef F628_LIMIT
#define F629_STAGE 3
#define F629_EARLY 4
#define F629_LATE 7
#include "MarisaFighterArcTrajectory91F629.inc"
#undef F629_STAGE
#undef F629_EARLY
#undef F629_LATE
#define F631_EXTRA_FLAG 0
#define F631_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimer96F631.inc"
#undef F631_EXTRA_FLAG
#undef F631_EXTRA_BEFORE
#define F633_CASE 0x97
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x98
#define F633_START_HEIGHT -13.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x9A
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x9B
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0x9C
#define F633_START_HEIGHT -13.0f
#define F633_NEXT_ACTION 2
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
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
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0xA0
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F633_CASE 0xA1
#define F633_START_HEIGHT -13.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "MarisaFighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_NEXT_ACTION
#undef F633_START_HEIGHT
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
#define F642_NEXT_ACTION 0
#include "MarisaFighterProjectileLaunchF642.inc"
#undef F642_CASE
#undef F642_NEXT_ACTION
#define F642_CASE 0xA8
#define F642_NEXT_ACTION 2
#include "MarisaFighterProjectileLaunchF642.inc"
#undef F642_CASE
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
#include "MarisaFighterSpecialCardC8CB.inc"
#include "MarisaFighterSpecialCardCCCE.inc"
#include "MarisaFighterSpecialCardCF.inc"
#include "MarisaFighterSpecialCardD0D2.inc"
#include "MarisaFighterEarlySpecial186189.inc"
#include "MarisaFighterProjectileSpecial18A18B.inc"
#include "MarisaFighterCardResource191194.inc"
#include "MarisaFighterCardResource19C19E.inc"
#include "MarisaFighterCardResource19F1A3.inc"
#include "MarisaFighterCardVolleys19619B.inc"
#include "MarisaFighterAction12C.inc"
#include "MarisaFighterStage12D136.inc"
#include "MarisaFighterAction1F4.inc"
#include "MarisaFighterCardFollowup1F520E.inc"
#include "MarisaFighterCardResource252271.inc"
#include "MarisaFighterAction2C2.inc"
#include "MarisaFighterLateCard2C3D1.inc"
#include "MarisaFighterCardTail2BD31C.inc"
#include "MarisaFighterCardLate2BC2C0.inc"
#include "MarisaFighterCardLate2BF2DB.inc"
#include "MarisaFighterCardTail2EF2F8.inc"
#include "MarisaFighterRandomCard2E52F9.inc"
        default:
            if (AdvanceNestedFrame() == field070)
                ResetPrimaryCounters(0);
            return;
    }
}
