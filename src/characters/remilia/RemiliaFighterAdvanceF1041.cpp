#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/MathFloatHelpers.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/remilia/RemiliaFighter.hpp"
// Natural-C++ reconstruction of RemiliaFighter::Advance at 00543210.

extern float g_F734_RoundY1At00659A2C;
extern float g_F734_RoundY2At00659A28;
extern float g_F737_RoundY0At00659A24;
extern float g_F737_RoundY1At00659A20;
extern float g_F740_ShotY1At0065928C;
extern float g_F743_Y19CAt00659A14;
extern float g_OneShotYAt0065928C;
extern float g_StormYAt0065948C;
void RemiliaFighter::Advance() {
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
        case 0x4: velocityX = 6.5f; goto native_shared_getter;
        case 0x5: velocityX = -6.5f; goto native_shared_getter;
        case 0x6:
            if (animationStage == 0 && animationFrame == 0 &&
                    ((aiCommand) == 3 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCC);
                return;
            }
            if (animationStage == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (y > FloatConstants::Zero) {
                velocityY = velocityY - verticalAcceleration;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 3 && velocityY < FloatConstants::Four)
                ResetSecondaryCounter(4);
            ++animationFrame;
            if (animationFrame >= (animationFrameCount)) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 3) {
                    velocityX = 0.0f;
                    velocityY = 19.0f;
                    verticalAcceleration = 0.95f;
                }
                if (animationStage >= (animationStageCount))
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x7:
            if (animationStage == 0 && animationFrame == 0 &&
                    ((aiCommand) == 5 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            if (animationStage == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (y > FloatConstants::Zero) {
                velocityY = velocityY - verticalAcceleration;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < FloatConstants::Four)
                ResetSecondaryCounter(5);
            ++animationFrame;
            if (animationFrame >= (animationFrameCount)) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 3) {
                    velocityX = 7.0f;
                    velocityY = 18.0f;
                    verticalAcceleration = 0.95f;
                }
                if (animationStage >= (animationStageCount))
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x8:
            if (animationStage == 0 && animationFrame == 0 &&
                    ((aiCommand) == 4 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCE);
                return;
            }
            if (animationStage == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (animationStage == 3 && velocityY < FloatConstants::Four)
                ResetSecondaryCounter(4);
            if (y > FloatConstants::Zero) {
                velocityY = velocityY - verticalAcceleration;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            ++animationFrame;
            if (animationFrame >= (animationFrameCount)) {
                animationFrame = 0;
                ++animationStage;
                if (animationStage == 3) {
                    velocityX = -7.0f;
                    field3AC = 0;
                    velocityY = 18.0f;
                    verticalAcceleration = 0.95f;
                }
                if (animationStage >= (animationStageCount))
                    animationStage -= 2;
                BindAnimation();
            }
            break;
        case 0x9:
        if (verticalAcceleration == FloatConstants::Zero)
            verticalAcceleration = 0.6f;
        velocityY = velocityY - verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;
        case 0xA:
            if (animationStage == 0 && animationFrame == 0)
                PlaySharedSound(30);
            ClearMotionFields();
            if (AdvanceNestedFrame() == animationStageCount) {
                if (inputY == 0)
                    ResetPrimaryCounters(3);
                else
                    ResetPrimaryCounters(2);
            }
            break;
        #include "characters/shared/actions/FighterSingletonContactF598.inc"
#define CONTACT_STAGE_OFFSET 0xF00
#include "characters/shared/actions/FighterAdditionalContactF600.inc"
#undef CONTACT_STAGE_OFFSET
#define TRAJECTORY_LOWER_THRESHOLD GeometryConstants::Six
#define TRAJECTORY_UPPER_THRESHOLD GeometryConstants::TwentyFive
#define TRAJECTORY_MINIMUM_SPEED 6.0f
#define TRAJECTORY_MAXIMUM_SPEED 25.0f
#define TRAJECTORY_STAGE_THRESHOLD 1
#define TRAJECTORY_EARLY_STATE 2
#define TRAJECTORY_LATE_STATE 7
#define CONTACT_STAGE_OFFSET 0xF00
#include "characters/shared/actions/FighterTrajectoryContact46F602.inc"
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
#include "characters/shared/actions/FighterTrajectoryFollowupsF605.inc"
#undef F605_COUNTER
#undef F605_STAGE47
#undef F605_EARLY47
#undef F605_LATE47
#undef F605_STAGE48
#undef F605_EARLY48
#undef F605_LATE48
#define F607_COUNTER 0xF00
#include "characters/shared/actions/FighterTrajectoryLanding49F607.inc"
#undef F607_COUNTER
#define F610_STAGE 1
#define F610_EARLY 2
#define F610_LATE 7
#define F610_COUNTER 0xF00
#define F610_PREPARE_BEFORE 1
#include "characters/shared/actions/FighterTrajectoryBounce4AF610.inc"
#undef F610_STAGE
#undef F610_EARLY
#undef F610_LATE
#undef F610_COUNTER
#undef F610_PREPARE_BEFORE
#define F613_COUNTER 0xF00
#include "characters/shared/actions/FighterTrajectoryRecovery4CF613.inc"
#undef F613_COUNTER
        case 0x58: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = -hitReactionVelocityX;
                velocityY = hitReactionVelocityY;
                verticalAcceleration = 0.8f;
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
#include "actions/FighterEarlyBounceTypedF752.inc"


#include "actions/FighterFacing05FF762.inc"
#include "actions/FighterResourceTenVolleyF748.inc"

#include "actions/FighterResourceSelectorF749.inc"
#include "characters/shared/actions/FighterMode63BasicF626.inc"
#define F628_CASE 0x8C
#define F628_COUNTER 0xF00
#define F628_START_POS -11.0f
#define F628_LIMIT 5
#include "characters/shared/actions/FighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x8F
#define F628_COUNTER 0xF00
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "characters/shared/actions/FighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F628_CASE 0x90
#define F628_COUNTER 0xF00
#define F628_START_POS -12.0f
#define F628_LIMIT 7
#include "characters/shared/actions/FighterJumpLandingF628.inc"
#undef F628_CASE
#undef F628_COUNTER
#undef F628_START_POS
#undef F628_LIMIT
#define F629_STAGE 1
#define F629_EARLY 2
#define F629_LATE 7
#define F629_COUNTER 0xF00
#include "characters/shared/actions/FighterArcTrajectory91F629.inc"
#undef F629_STAGE
#undef F629_EARLY
#undef F629_LATE
#undef F629_COUNTER
#define F631_COUNTER 0xF00
#define F631_EXTRA_FLAG 1
#define F631_EXTRA_BEFORE 0
#include "characters/shared/actions/FighterLandingTimer96F631.inc"
#undef F631_COUNTER
#undef F631_EXTRA_FLAG
#undef F631_EXTRA_BEFORE
#define F633_CASE 0x97
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -10.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 1
#define F633_EXTRA_BEFORE 0
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
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
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
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
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
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
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
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
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F637_EXTRA_FLAG 1
#define F637_EXTRA_BEFORE 0
#define F637_STRICT_ABOVE 0
#include "characters/shared/actions/FighterGroundBoost9EF637.inc"
#undef F637_EXTRA_FLAG
#undef F637_EXTRA_BEFORE
#undef F637_STRICT_ABOVE
#define F633_CASE 0x9F
#define F633_COUNTER 0xF00
#define F633_START_HEIGHT -9.0f
#define F633_NEXT_ACTION 0
#define F633_EXTRA_FLAG 0
#define F633_EXTRA_BEFORE 0
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
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
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
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
#include "characters/shared/actions/FighterLandingTimerSiblingsF633.inc"
#undef F633_CASE
#undef F633_COUNTER
#undef F633_START_HEIGHT
#undef F633_NEXT_ACTION
#undef F633_EXTRA_FLAG
#undef F633_EXTRA_BEFORE
#define F641_CASE 0xA3
#define F641_START_HEIGHT -9.0f
#define F641_NEXT_ACTION 2
#include "characters/shared/actions/FighterLandingNoCounterF641.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F641_CASE 0xA4
#define F641_START_HEIGHT -10.0f
#define F641_NEXT_ACTION 2
#include "characters/shared/actions/FighterLandingNoCounterF641.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F641_CASE 0xA5
#define F641_START_HEIGHT -13.0f
#define F641_NEXT_ACTION 2
#include "characters/shared/actions/FighterLandingNoCounterF641.inc"
#undef F641_CASE
#undef F641_START_HEIGHT
#undef F641_NEXT_ACTION
#define F642_CASE 0xA7
#define F642_COUNTER 0xF00
#define F642_NEXT_ACTION 0
#include "characters/shared/actions/FighterProjectileLaunchF642.inc"
#undef F642_CASE
#undef F642_COUNTER
#undef F642_NEXT_ACTION
#define F642_CASE 0xA8
#define F642_COUNTER 0xF00
#define F642_NEXT_ACTION 2
#include "characters/shared/actions/FighterProjectileLaunchF642.inc"
#undef F642_CASE
#undef F642_COUNTER
#undef F642_NEXT_ACTION
#define F645_CASE 0xB4
#define F645_START_POS 8.0f
#define F645_AUX_ACTION 6
#include "characters/shared/actions/FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#define F645_CASE 0xB5
#define F645_START_POS -8.0f
#define F645_AUX_ACTION 6
#include "characters/shared/actions/FighterMotionRestartB4F645.inc"
#undef F645_CASE
#undef F645_START_POS
#undef F645_AUX_ACTION
#include "actions/FighterFourDirectionalC8F759.inc"



#include "actions/FighterComplexStageCC_CE_F760.inc"


#include "characters/shared/actions/FighterFallStateCFF647.inc"
#include "characters/shared/actions/FighterReflectLandingD0F646.inc"
#define F651_DECAY 3
#define F651_SPRITE 0x3E6
#include "characters/shared/actions/FighterResourceShotD1F651.inc"
#undef F651_DECAY
#undef F651_SPRITE
#define F652_DECAY 3
#define F652_SPRITE 0x3E6
#define F652_SCALE_BEFORE 0
#include "characters/shared/actions/FighterResourceShotD2F652.inc"
#undef F652_DECAY
#undef F652_SPRITE
#undef F652_SCALE_BEFORE
#define F653_ACTION 0x12C
#define F653_NEXT_ACTION 0
#define F653_PREPARE_FRAME 2
#define F653_PREPARE_ANIM 0x1B
#define F653_CLEAR_F00 0
#include "characters/shared/actions/FighterFallingRecoveryF653.inc"
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
#include "characters/shared/actions/FighterFallingRecoveryF653.inc"
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
#include "characters/shared/actions/FighterFallingRecoveryF653.inc"
#undef F653_ACTION
#undef F653_NEXT_ACTION
#undef F653_PREPARE_FRAME
#undef F653_PREPARE_ANIM
#undef F653_CLEAR_F00
#include "actions/FighterFallingFinishF654.inc"

#include "actions/FighterLateGroundF656.inc"
#include "actions/FighterLateShotsF656.inc"



#include "actions/FighterMotionContinuationF657.inc"



#include "actions/FighterMotionShotsF661.inc"

#include "actions/FighterEightRoundF734.inc"


#include "actions/FighterEightGroundF737.inc"

#include "actions/FighterRepeatShotF740.inc"


#include "actions/FighterDoubleRepeatF744.inc"

#include "actions/FighterLaterEarlyF743.inc"



#include "actions/FighterRandomArcsF728.inc"

#define F729_CASE 0x1F6
#define F729_STAGE14_X 40.0f
#define F729_STAGE14_Y -20.0f
#define F729_STAGE15_SHOT 0x336
#include "actions/FighterBoundaryReturnTypedF762.inc"
#undef F729_CASE
#undef F729_STAGE14_X
#undef F729_STAGE14_Y
#undef F729_STAGE15_SHOT
#define F729_CASE 0x1F7
#define F729_STAGE14_X 30.0f
#define F729_STAGE14_Y -30.0f
#define F729_STAGE15_SHOT 0x337
#include "actions/FighterBoundaryReturnTypedF762.inc"
#undef F729_CASE
#undef F729_STAGE14_X
#undef F729_STAGE14_Y
#undef F729_STAGE15_SHOT
#include "actions/FighterAimReturnTypedF762.inc"
#include "actions/FighterFollowingNativeF732.inc"



#include "actions/FighterSpecialStageF664.inc"

#include "actions/FighterCounterSpecialF668.inc"


#include "actions/FighterPostCounterF669.inc"


#include "actions/FighterFourShotBarrageF671.inc"
#include "actions/FighterEightShotAndFollowF672.inc"




#include "actions/FighterGroundWaveF673.inc"
        case 0x2BF: {
            if (animationStage==0 && animationFrame==0) {
                scriptCounterF00=0;
                collisionResult=1;
                ClearMotionFields();
                spellPower=(spellPower)-GeometryConstants::Hundred;
                SetNonnegativeWord(40);
                PlaySharedSound(23);
                PlaySound(9);
                SpawnAuxEffect(0x73,
                    x-float(facing*20),
                    (*(&y))+GeometryConstants::HundredEighty,
                    facing,1);
                Fighter::SpawnTrackedEffect(0x334,x,y,
                    facing,1,0,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if (animationStage==12 && animationFrame==0) {
                SpawnBattleEffect(0x328,
                    float(facing*65)+(x),
                    (*(&y))+GeometryConstants::HundredForty,
                    facing,1);
                SpawnBattleEffect(0x33C,
                    float(facing*65)+(x),
                    (*(&y))+GeometryConstants::HundredForty,
                    facing,1);
                UpdateGaugeTimer(500);
                PlaySound(10);
            }
            break;
        }

        case 0x2C0: {
            if (animationStage==0 && animationFrame==0) {
                ClearMotionFields();
                remainingHits=99;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if (animationStage<25 && y>FloatConstants::Zero && animationStage>15) {
                velocityX=(velocityX)-FloatConstants::FourFifths;
                velocityY=velocityY-verticalAcceleration;
                if ((velocityX)<FloatConstants::Three)
                    velocityX=3.0f;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(25);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if (animationFrame==0)
                collisionResult=0;
            if (animationStage==1 && animationFrame==0) {
                spellPower=(spellPower)-GeometryConstants::Hundred;
                SetNonnegativeWord(40);
                PlaySharedSound(23);
                SpawnAuxEffect(0x73,
                    x-float(facing*46),
                    (*(&y))+GeometryConstants::SeventyFive,
                    facing,1);
            }
            if (animationStage==7 && animationFrame==0) {
                SpawnAuxEffect(0x3C,x,y,
                    facing,1);
                PlaySound(11);
                velocityY=9.0f;
                velocityX=20.0f;
                UpdateGaugeTimer(500);
                verticalAcceleration=0.8f;
            }
            if (animationStage>6 && animationStage<15) {
                SpawnBattleEffect(0x329,
                    float(facing*62)+(x),
                    (*(&y))+GeometryConstants::EightyThree,
                    facing,1);
            }
            if (animationStage==15 && animationFrame==0 && (scriptCounterF00)<3) {
                ResetSecondaryCounter(11);
                ++scriptCounterF00;
                break;
            }
            if (animationStage==25 && animationFrame==0)
                ResetSecondaryCounter(23);
            break;
        }
        case 0x2C1: {
            if (animationStage==0 && animationFrame==0) {
                scriptCounterF00=0;
                collisionResult=1;
                ClearMotionFields();
                SetNonnegativeWord(40);
                PlaySharedSound(23);
                SpawnAuxEffect(0x74,x,
                    (*(&y))+GeometryConstants::Hundred,
                    facing,1);
                spellPower=(spellPower)-GeometryConstants::Hundred;
            }
            if (animationStage>3 && animationStage<11) {
                velocityY=velocityY-FloatConstants::ThirtyFiveHundredths;
                if (velocityY<FloatConstants::Zero)
                    velocityY=0.0f;
            }
            if (animationStage>10 && animationStage<14) {
                velocityY=velocityY-verticalAcceleration;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(14);
                    break;
                }
            }
            if (animationStage==5 && animationFrame==0)
                SetCameraShake(5.0f);
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if (animationStage==4 && animationFrame==0) {
                velocityY=15.0f;
                verticalAcceleration=0.85f;
            }
            if (animationStage==5 && animationFrame==0) {
                SpawnBattleEffect(0x32A,
                    float(facing*40)+(x),
                    10.0f,
                    facing,1);
                SpawnBattleEffect(0x340,x,0.0f,
                    facing,1);
                UpdateGaugeTimer(500);
                PlaySound(12);
            }
            if (animationStage==8 && animationFrame==0 && (scriptCounterF00)<12) {
                ResetSecondaryCounter(5);
                ++scriptCounterF00;
            }
            if (animationStage==11 && animationFrame==0 && (scriptCounterF00)<14) {
                ResetSecondaryCounter(8);
                ++scriptCounterF00;
            }
            if (animationStage==14 && animationFrame==0)
                ResetSecondaryCounter(12);
            break;
        }

        case 0x2C4: {
            if (animationStage==0 && animationFrame==0) {
                scriptCounterF00=0;
                collisionResult=1;
                ClearMotionFields();
                spellPower=(spellPower)-GeometryConstants::Hundred;
                SetNonnegativeWord(40);
                PlaySharedSound(23);
                PlaySound(13);
                SpawnAuxEffect(0x74,
                    x-float(facing*20),
                    (*(&y))+GeometryConstants::HundredEighty,
                    facing,1);
                Fighter::SpawnTrackedEffect(0x334,x,y,
                    facing,1,0,1);
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if (animationStage==12 && animationFrame==0) {
                UpdateGaugeTimer(750);
                SpawnBattleEffect(0x32B,
                    float(facing*65)+(x),
                    (*(&y))+GeometryConstants::HundredForty,
                    facing,1);
                SpawnBattleEffect(0x33D,
                    float(facing*65)+(x),
                    (*(&y))+GeometryConstants::HundredForty,
                    facing,1);
                PlaySound(14);
            }
            break;
        }




        case 0x2C5: {
            if (animationStage==0 && animationFrame==0) {
                ClearMotionFields();
                remainingHits=99;
                collisionResult=0;
                field3AC=0;
                scriptCounterF00=0;
            }
            if (animationStage<25 && y>FloatConstants::Zero && animationStage>15) {
                velocityX=(velocityX)-FloatConstants::FourFifths;
                velocityY=velocityY-verticalAcceleration;
                if ((velocityX)<FloatConstants::Three)
                    velocityX=3.0f;
                if (y+velocityY<=FloatConstants::Zero) {
                    ResetSecondaryCounter(25);
                    y=0.0f;
                    ClearMotionFields();
                    break;
                }
            }
            if (AdvanceNestedFrame()==(animationStageCount))
                ResetPrimaryCounters(0);
            if (animationFrame==0)
                collisionResult=0;
            if (animationStage==1 && animationFrame==0) {
                SetNonnegativeWord(40);
                PlaySharedSound(23);
                SpawnAuxEffect(0x74,
                    x-float(facing*46),
                    (*(&y))+GeometryConstants::SeventyFive,
                    facing,1);
                spellPower=(spellPower)-GeometryConstants::Hundred;
            }
            if (animationStage==7 && animationFrame==0) {
                SpawnAuxEffect(0x3C,x,y,
                    facing,1);
                SpawnBattleEffect(0x344,
                    float(facing*55)+(x),
                    (*(&y))+GeometryConstants::EightySix,
                    facing,1);
                UpdateGaugeTimer(500);
                PlaySound(15);
                velocityY=10.5f;
                velocityX=25.0f;
                verticalAcceleration=0.8f;
            }
            if (animationStage>6 && animationStage<15) {
                SpawnBattleEffect(0x32E,
                    float(facing*62)+(x),
                    (*(&y))+GeometryConstants::EightyThree,
                    facing,1);
            }
            if (animationStage==15 && animationFrame==0 && (scriptCounterF00)<5) {
                ResetSecondaryCounter(11);
                ++scriptCounterF00;
                break;
            }
            if (animationStage==25 && animationFrame==0)
                ResetSecondaryCounter(23);
            break;
        }

#include "actions/FighterFallingRadialsF711.inc"

#include "actions/FighterApproachNativeF763.inc"
#include "actions/FighterBossMovementF714.inc"
#include "actions/FighterDoubleVolleyF718.inc"

#include "actions/FighterLateStormF720.inc"
#include "actions/FighterRandomVolleyF721.inc"
#include "actions/FighterCloudRainF674.inc"
#include "actions/FighterCloudBurstF676.inc"

#include "actions/FighterStormVolleyTypedF768.inc"
#include "actions/FighterAngleStormTypedF767.inc"
#include "actions/FighterApproachVolleyNativeF764.inc"
#include "actions/FighterGroundedVolleyTypedF771.inc"
#include "actions/FighterFourTierVolleyF701.inc"
#include "actions/FighterTerminalShotF681.inc"
#include "actions/FighterTerminalCounterF674.inc"
#include "actions/FighterNativeDefaultF778.inc"
#include "actions/FighterSharedGetterTail00543210F1196.inc"
    }
}
#undef opponent
