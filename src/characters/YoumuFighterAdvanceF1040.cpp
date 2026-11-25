#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/MathFloatHelpers.hpp"
#include "engine/GameSharedState.hpp"
// Natural-C++ reconstruction of YoumuFighter::Advance at 005214B0.
#include "characters/YoumuFighter.hpp"
#include "battle/FighterAnimationPhaseBorrowedF1024.hpp"
extern float g_F890Phase4OtherYAt006598B4;
extern float g_F872Volley1F9YAt006598BC;
extern float g_F857ShotYAt00659298;
// Owner motion clearing now invokes the inherited Fighter method.
// F1197 complete original-shaped 005214B0 parent, continued from F901/F1040.
// Native stack, CFG and non-GPR operands agree; 2736 GPR positions and
// five instruction widths remain NONEXACT. No whole CODE credit.

void YoumuFighter::Advance() {
    if (field082 != 0 || opponent->field3BA != 0)
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
            goto native_script_shared_getter;
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
            goto native_script_shared_getter;
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
        case 0x4: velocityX = 3.0f; goto native_script_shared_getter;
        case 0x5: velocityX = -3.0f; goto native_script_shared_getter;
        case 0x6:
            if (animationStage == 0 && animationFrame == 0 &&
                    ((aiCommand) == 3 || (field3AC) > 0)) {
                ResetPrimaryCounters(0xCC);
                return;
            }
            if (animationStage == 0 && (field3AC) == 0)
                ClearMotionFields();
            if (animationStage > 2) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (animationStage == 4 && velocityY < FloatConstants::Four)
                ResetSecondaryCounter(5);
            if (AdvanceNestedFrame() == animationStageCount)
                ResetSecondaryCounter(11);
            if (animationStage == 3 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 16.0f;
                field05C = 0.8f;
                field3AC = 0;
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
            if (animationStage > 2) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetPrimaryCounters(9);
            if (animationStage == 3 && animationFrame == 0) {
                velocityX = 5.5f;
                velocityY = 16.0f;
                field05C = 0.8f;
                field3AC = 0;
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
            if (animationStage > 2) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    ResetPrimaryCounters(10);
                    y = 0.0f;
                    ClearMotionFields();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetSecondaryCounter(13);
            if (animationStage == 3 && animationFrame == 0) {
                velocityX = -5.5f;
                velocityY = 16.0f;
                field05C = 0.8f;
                field3AC = 0;
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
            ClearMotionFields();
            if (AdvanceNestedFrame() == animationStageCount) {
                if (inputY == 0)
                    ResetPrimaryCounters(0);
                else
                    ResetPrimaryCounters(1);
            }
            break;
        #include "FighterSingletonContactF598.inc"
#define CONTACT_STAGE_OFFSET 0xF00
#include "FighterAdditionalContactF600.inc"
#undef CONTACT_STAGE_OFFSET
#define TRAJECTORY_LOWER_THRESHOLD GeometryConstants::Six
#define TRAJECTORY_UPPER_THRESHOLD GeometryConstants::TwentyFive
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
        case 0x58: {
            if (animationStage == 0 && animationFrame == 0) {
                velocityX = -field094;
                velocityY = field098;
                field05C = 0.8f;
                field07C = 0;
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
        case 0x59: {
            if (animationStage == 3) {
                rotationZ = (rotationZ) + GeometryConstants::Forty;
                velocityY = velocityY - field05C;
                if (velocityY + y <= FloatConstants::Zero) {
                    scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
                    scriptCounterF02 = static_cast<short>((*(&velocityY)) * GeometryConstants::Hundred);
                    ClearMotionFields();
                    y = 0.0f;
                    ResetPrimaryCounters(0x61);
                    rotationZ = 0.0f;
                    SetCameraShake(2.0f);
                    ClearTransformFlag();
                    PlaySharedSound(0x16);
                    break;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount)
                ResetSecondaryCounter(3);
            else if (animationStage == 3 && animationFrame == 0) {
                velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneFourHundredth;
                velocityY = static_cast<float>(-scriptCounterF02) * FloatConstants::OneHundredth;
                field05C = 0.7f;
                ResetTransform(0.0f, 95.0f, 0.0f);
            } else if (animationStage == 3 && animationFrame != 0) {
                // Keep the rebound motion on later frames.
            }
            break;
        }
        case 0x5D: {
            if (animationStage < 19 && y > FloatConstants::Zero) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(19);
                    break;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0);
                if (inputY > 0)
                    ResetPrimaryCounters(1);
            }
            if (animationStage == animationStageCount - 1) {
                // Keep the two independent comparisons in their x87 operand order.
                if (*(&x) > opponent->x)
                    facing = -1;
                if (*(&x) < opponent->x)
                    facing = 1;
            }
            if (animationStage == 6 && animationFrame == 0) {
                velocityY = 8.0f;
                velocityX = 13.5f;
                field05C = 0.6f;
            }
            if (animationStage == 19 && animationFrame == 0)
                ResetSecondaryCounter(18);
            else if (animationStage == 19 && animationFrame != 0) {
                // Continue the landing animation.
            }
            break;
        }
        case 0x5E: {
            if (animationStage < 18 && y > FloatConstants::Zero) {
                velocityY = velocityY - field05C;
                if (y + velocityY <= FloatConstants::Zero) {
                    y = 0.0f;
                    ClearMotionFields();
                    ResetSecondaryCounter(18);
                    break;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetPrimaryCounters(0);
                if (inputY > 0)
                    ResetPrimaryCounters(1);
            }
            if (animationStage == animationStageCount - 1) {
                if (*(&x) > opponent->x)
                    facing = -1;
                if (*(&x) < opponent->x)
                    facing = 1;
            }
            if (animationStage == 6 && animationFrame == 0) {
                velocityY = 8.0f;
                velocityX = -13.5f;
                field05C = 0.6f;
            }
            if (animationStage == 18 && animationFrame == 0)
                ResetSecondaryCounter(16);
            else if (animationStage == 18 && animationFrame != 0) {
                // Continue the landing animation.
            }
            break;
        }
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
#include "FighterScriptedSharedGetter005214B0F1197.inc"
    }
}
#undef opponent
