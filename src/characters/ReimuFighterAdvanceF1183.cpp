#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/ReimuFighter.hpp"
// Natural-C++ reconstruction of ReimuFighter::Advance at 0045DD70.

extern float g_ReimuMeterNearYAt00659088;
extern float g_ReimuMeterShotYAt00659080;
extern float g_ReimuAirVolleyYAt00659098;
extern float g_ReimuHighVolleyYAt0065909C;
extern float g_ReimuStormPairYBaseAt00657CBC;
extern float g_ReimuStormPairXBaseAt00658264;
extern float g_ReimuStormRingYOffsetAt0065836C;
extern float g_ReimuStormBurstYOffsetAt00659490;
extern float g_ReimuFallingGravityAt00658354;
extern float g_ReimuFallingSpawnYOffsetAt0065908C;
extern float g_ReimuStormLeftBoundaryAt0065787C;
extern float g_ReimuStormRightBoundaryAt0065920C;
extern float g_ReimuApproachRightBoundAt0065945C;

void ReimuFighter::Advance() {
    if (hitstopFrames != 0 || opponent->opponentFreezeSnapshot != 0)
        return;
    switch (action) {
        case 0x0:
            if ((field3AC) == 0) {
                ClearMotionFields();
            } else {
                if ((velocityX) > FloatConstants::Zero) {
                    velocityX -= FloatConstants::Half;
                    if ((velocityX) < FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if ((velocityX) < FloatConstants::Zero) {
                    velocityX += FloatConstants::HalfDouble;
                    if ((velocityX) > FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            goto native_shared_getter;
        case 0x1:
            if ((field3AC) == 0) {
                ClearMotionFields();
            } else {
                if ((velocityX) > FloatConstants::Zero) {
                    velocityX -= FloatConstants::Half;
                    if ((velocityX) < FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if ((velocityX) < FloatConstants::Zero) {
                    velocityX += FloatConstants::HalfDouble;
                    if ((velocityX) > FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(2);
            break;
        case 0x2:
            if ((field3AC) == 0) {
                ClearMotionFields();
            } else {
                if ((velocityX) > FloatConstants::Zero) {
                    velocityX -= FloatConstants::Half;
                    if ((velocityX) < FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if ((velocityX) < FloatConstants::Zero) {
                    velocityX += FloatConstants::HalfDouble;
                    if ((velocityX) > FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            goto native_shared_getter;
        case 0x3:
            if ((field3AC) == 0) {
                ClearMotionFields();
            } else {
                if ((velocityX) > FloatConstants::Zero) {
                    velocityX -= FloatConstants::Half;
                    if ((velocityX) < FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
                if ((velocityX) < FloatConstants::Zero) {
                    velocityX += FloatConstants::HalfDouble;
                    if ((velocityX) > FloatConstants::Zero) {
                        ClearMotionFields();
                        field3AC = 0;
                    }
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(0);
            break;
        case 0x4: velocityX = 4.5f; goto native_shared_getter;
        case 0x5: velocityX = -4.5f; goto native_shared_getter;
        case 0x6:
            if ((animationStage) == 0 && (animationFrame) == 0 &&
                    ((aiCommand) == 3 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCC);
                return;
            }
            if ((animationStage) == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (y > FloatConstants::Zero) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if ((animationFrame) >= (animationFrameCount)) {
                animationFrame = 0;
                ++animationStage;
                if ((animationStage) == 2) {
                    velocityX = 0.0f;
                    velocityY = 12.5f;
                    field05C = 0.55f;
                    field3AC = 0;
                }
                if ((animationStage) >= (animationStageCount))
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x7:
            if ((animationStage) == 0 && (animationFrame) == 0 &&
                    ((aiCommand) == 5 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            if ((animationStage) == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (y > FloatConstants::Zero) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if ((animationFrame) >= (animationFrameCount)) {
                animationFrame = 0;
                ++animationStage;
                if ((animationStage) == 2) {
                    velocityX = 4.0f;
                    velocityY = 12.5f;
                    field05C = 0.55f;
                    field3AC = 0;
                }
                if ((animationStage) >= (animationStageCount))
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x8:
            if ((animationStage) == 0 && (animationFrame) == 0 &&
                    ((aiCommand) == 4 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCE);
                return;
            }
            if ((animationStage) == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (y > FloatConstants::Zero) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if ((animationFrame) >= (animationFrameCount)) {
                animationFrame = 0;
                ++animationStage;
                if ((animationStage) == 2) {
                    velocityX = -4.0f;
                    velocityY = 12.5f;
                    field05C = 0.55f;
                    field3AC = 0;
                }
                if ((animationStage) >= (animationStageCount))
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x9:
        if (field05C == FloatConstants::Zero)
            field05C = 0.6f;
        velocityY = velocityY - field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        break;
        case 0xA:
            if (animationStage == 0 && animationFrame == 0)
                PlaySharedSound(30);
            ClearMotionFields();
            if (AdvanceNestedFrame() == animationStageCount) {
                if (inputY == 0)
                    ResetPrimaryCounters(0);
                else
                    ResetPrimaryCounters(2);
            }
            break;
        #include "FighterSingletonContactF598.inc"
#define CONTACT_STAGE_OFFSET 0xF00
#include "FighterAdditionalContactF600.inc"
#undef CONTACT_STAGE_OFFSET
#define TRAJECTORY_LOWER_THRESHOLD FloatConstants::Two
#define TRAJECTORY_UPPER_THRESHOLD GeometryConstants::Twelve
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
case 0x48: {
    if (animationStage==0 && animationFrame==0) {
        velocityX = -hitReactionVelocityX;
        velocityY = hitReactionVelocityY;
        field05C = 1.3f;
        collisionResult = 0;
    }
    if (animationStage==F605_STAGE48 && velocityY < FloatConstants::Two) {
        ResetSecondaryCounter(F605_EARLY48);
        break;
    }
    velocityY = velocityY - field05C;
    if (velocityY + y <= FloatConstants::Zero) {
        scriptCounterF00 = (velocityX) * GeometryConstants::Hundred;
        scriptCounterF02 = (velocityY) * GeometryConstants::Hundred;
        ClearMotionFields();
        y = 0.0f;
        ResetPrimaryCounters(0x61);
        SetCameraShake(2.0f);
        PlaySharedSound(0x16);
        break;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(F605_LATE48);
    break;
}

#undef F605_STAGE48
#undef F605_EARLY48
#undef F605_LATE48
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
        case 0x58: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = -hitReactionVelocityX;
                velocityY = hitReactionVelocityY;
                field05C = 0.8f;
                collisionResult = 0;
            }
            if (velocityY + y <= FloatConstants::Zero) {
                scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
                scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x59);
                SetCameraShake(3.0f);
                PlaySharedSound(0x16);
                for (int burst = 0; burst < 10; ++burst)
                    SpawnBattleEffect(0x3E4, x, y, 1, 1);
                if (fieldEFA > 25) {
                    fieldEFA = 0;
                    SpawnBattleEffect(0x3E3, x, y, 1, 1);
                }
                break;
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetSecondaryCounter(animationStage - 1);
            if (animationStage == 1 && animationFrame == 0) {
                if (fieldF0C == 0) {
                    fieldF0C = 1;
                    SpawnBattleEffect(0x3B7, x, y, facing, 1);
                }
                if (velocityY != FloatConstants::Zero) {
                    if (velocityX == FloatConstants::Zero) {
                        ResetSecondaryCounter(3);
                        break;
                    } else {
                        ResetSecondaryCounter(2);
                        break;
                    }
                }
            } else if (animationStage == 1 && animationFrame != 0) {
                // Continue the current trajectory.
            }
            break;
        }
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
#include "ReimuCommandStatesF1185.inc"








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










#include "ReimuScriptedAttacksF1186.inc"
#include "ReimuScriptedCombosF1187.inc"
#include "ReimuChargedAttacksF1188.inc"
#include "ReimuSpecialAttacksF1189.inc"
#include "ReimuMeterAttacksF1190.inc"
#include "ReimuCounterTailF1191.inc"
#include "ReimuRingStormF1192.inc"
#include "ReimuDriftTimerF1191.inc"
#include "ReimuRandomWarpF1192.inc"
#include "ReimuDifficultyShotF1191.inc"
#include "ReimuResourceLoopsF1192.inc"
#include "ReimuFinalEffectsF1192.inc"
        default:
            if (AdvanceNestedFrame()==(animationStageCount)) ResetPrimaryCounters(0);
            break;
#include "ReimuSharedGetterTailF1192.inc"
    }
}
#undef opponent
