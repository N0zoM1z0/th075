#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/patchouli/PatchouliFighter.hpp"

extern float g_PatchouliEffectYAt00659740;
extern float g_PatchouliEffectYAt00659748;

void PatchouliFighter::Advance() {
    if (hitstopFrames != 0 || opponent->opponentFreezeSnapshot != 0)
        return;

    switch (action) {
    case 0x0: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX += FloatConstants::HalfDouble;
                if (velocityX > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        goto advanceFrame;
    }

    case 0x1: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX += FloatConstants::HalfDouble;
                if (velocityX > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        break;
    }

    case 0x2: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX += FloatConstants::HalfDouble;
                if (velocityX > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        goto advanceFrame;
    }

    case 0x3: {
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if (velocityX > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX += FloatConstants::HalfDouble;
                if (velocityX > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;
    }

    case 0x4: {
        velocityX = 4.0f;
        goto advanceFrame;
    }

    case 0x5: {
        velocityX = -4.0f;
        goto advanceFrame;
    }

    case 0x6: {
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 3 || field3AC > 0)) {
            ResetPrimaryCounters(0xCC);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
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
        if (animationFrame >= (field072)) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 13.0f;
                verticalAcceleration = 0.4f;
                if (field3AC > 0) {
                    velocityX = 2.0f;
                    velocityY = 10.0f;
                    verticalAcceleration = 0.25f;
                }
            }
            if (animationStage >= (field070))
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x7: {
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 5 || field3AC > 0)) {
            ResetPrimaryCounters(0xCD);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
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
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 3.0f;
                velocityY = 13.0f;
                verticalAcceleration = 0.4f;
                if (field3AC > 0) {
                    velocityX = 4.5f;
                    velocityY = 10.0f;
                    verticalAcceleration = 0.25f;
                    field3AC = 0;
                }
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x8: {
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 4 || field3AC > 0)) {
            ResetPrimaryCounters(0xCE);
            return;
        }
        if (animationStage == 0 && field3AC == 0)
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
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -4.0f;
                field3AC = 0;
                velocityY = 13.0f;
                verticalAcceleration = 0.4f;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x9: {
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
            ResetSecondaryCounter(0);
        }
        break;
    }

    case 0xA: {
        if (animationStage == 0 && animationFrame == 0)
            PlaySharedSound(30);
        ClearMotionFields();
        if (AdvanceNestedFrame() == field070) {
            if (inputY == 0)
                ResetPrimaryCounters(0);
            else
                ResetPrimaryCounters(1);
        }
        break;
    }

    // Ground hit reactions and corner displacement.
    case 0x32: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if (velocityX < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if (velocityX > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE != 0)
            opponentVelocityDeltaX = static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x33: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x34: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x35: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x38: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x39: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x3A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x3B: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x3E: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x3F: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x40: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x41: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -15.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() &&
            field3BE) {
            opponentVelocityDeltaX =
                static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
            return;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x46: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY += hitReactionVelocityY;
            if (velocityY < GeometryConstants::Six)
                velocityY = 6.0f;
            verticalAcceleration = 0.8f;
            if (velocityY > GeometryConstants::TwentyFive)
                velocityY = 25.0f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
            return;
        }
        velocityY = velocityY - verticalAcceleration;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x47: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            verticalAcceleration = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
            return;
        }
        velocityY = velocityY - verticalAcceleration;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x48: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            verticalAcceleration = 1.3f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
            return;
        }
        velocityY = velocityY - verticalAcceleration;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x49: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            verticalAcceleration = 0.8f;
            collisionResult = 0;
        }
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage == 1 && animationFrame == 0 && velocityY != FloatConstants::Zero) {
            if (velocityX == (FloatConstants::Zero)) {
                ResetSecondaryCounter(3);
                return;
            } else {
                ResetSecondaryCounter(2);
                return;
            }
        }
        return;
    }

    case 0x4A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            verticalAcceleration = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
            return;
        }
        if (CheckHorizontalLimits() && (velocityX) <= GeometryConstants::NegativeFifteen) {
            ResetPrimaryCounters(0x4C);
            velocityX = -(velocityX) * FloatConstants::Quarter;
            velocityY = 15.0f;
            verticalAcceleration = 0.5f;
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY = velocityY - verticalAcceleration;
        if (velocityY + y <= FloatConstants::Zero) {

            Fighter::PlaySharedSound(0x16);

            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);

            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }

        rotationZ = (rotationZ) + GeometryConstants::Thirty;
        velocityY = velocityY - verticalAcceleration;
        if (velocityY + y <= FloatConstants::Zero) {
            Fighter::PlaySharedSound(0x16);
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            rotationZ = 0.0f;
            SetCameraShake(2.0f);
            ClearTransformFlag();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        return;
    }

    case 0x58: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
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
            Fighter::PlaySharedSound(0x16);
            for (int burst = 0; burst < 10; ++burst)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage == 1 && animationFrame == 0) {
            if (velocityY != FloatConstants::Zero) {
                if (velocityX == (FloatConstants::Zero)) {
                    ResetSecondaryCounter(3);
                    return;
                } else {
                    ResetSecondaryCounter(2);
                    return;
                }
            }
        } else if (animationStage == 1 && animationFrame != 0) {
            // Continue the impact animation.
        }
        return;
    }

    case 0x59: {
        if (animationStage > 2) {
            rotationZ = (rotationZ) + GeometryConstants::Forty;
            velocityY = velocityY - verticalAcceleration;
            if (velocityY + y <= FloatConstants::Zero) {
                scriptCounterF00 = (velocityX) * GeometryConstants::Hundred;
                scriptCounterF02 = (velocityY) * GeometryConstants::Hundred;
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x61);
                rotationZ = 0.0f;
                SetCameraShake(2.0f);
                ClearTransformFlag();
                Fighter::PlaySharedSound(0x16);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(4);
        else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneFourHundredth;
            velocityY = static_cast<float>(-scriptCounterF02) * FloatConstants::OneHundredth;
            verticalAcceleration = 0.7f;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }
        return;
    }

    case 0x5D: {
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 11.0f;
        SpawnBattleEffect(0x353, (x) + GeometryConstants::Seventy - static_cast<float>(RecordedRange(0, 140)),
            y - static_cast<float>(RecordedRange(0, 20)), facing, 1);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        if (animationStage == 6 && animationFrame == 0)
            velocityX = 0.0f;
        return;
    }

    case 0x5E: {
        if (animationStage == 0 && animationFrame == 0)
            velocityX = -11.0f;
        SpawnBattleEffect(0x353, (x) + GeometryConstants::Seventy - static_cast<float>(RecordedRange(0, 140)),
            y - static_cast<float>(RecordedRange(0, 20)), facing, 1);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = 0.0f;
        } else if (animationStage == 6 && animationFrame != 0) {
            // Continue the landing animation.
        }
        return;
    }

    case 0x5F: {
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (inputY > 0)
                ResetPrimaryCounters(1);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        return;
    }

    case 0x60: {
        if (static_cast<int>(facing) * inputX > 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 1;
        if (static_cast<int>(facing) * inputX < 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot = 0; shot < 10; ++shot)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage > 2 && animationStage < 7) {
            velocityY = velocityY - verticalAcceleration;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if ((field3CF) == 0)
                ResetPrimaryCounters(0x63);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneTwoHundredth;
            velocityY = static_cast<float>(-scriptCounterF02) * FloatConstants::OneTwoHundredth;
            verticalAcceleration = 2.0f;
        }
        break;
    }

    case 0x61: {
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot = 0; shot < 10; ++shot)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage > 2 && animationStage < 7) {
            velocityY = velocityY - verticalAcceleration;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if ((field3CF) == 0)
                ResetPrimaryCounters(0x63);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneTwoHundredth;
            velocityY = static_cast<float>(-scriptCounterF02) * FloatConstants::OneTwoHundredth;
            verticalAcceleration = 2.0f;
        } else if (animationStage == 3 && animationFrame != 0) {
            // Continue the launch animation.
        }
        break;
    }

    case 0x62: {
        if (static_cast<int>(facing) * inputX > 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 1;
        if (static_cast<int>(facing) * inputX < 0
            && (static_cast<unsigned int>(inputA) > 0
             || static_cast<unsigned int>(inputB) > 0
             || static_cast<unsigned int>(inputC) > 0
             || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 2;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x5F);
            if (scriptCounterF00 == 1)
                ResetPrimaryCounters(0x5D);
            if (scriptCounterF00 == 2)
                ResetPrimaryCounters(0x5E);
        }
        return;
    }

    case 0x63: {
        if (g_CombatMode != CombatMode::Story ||
            cpuControlled == 0) {
            if (animationStage == 2 &&
                roundsRemaining > 0 &&
                opponent->action < 150) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        } else {
            if (animationStage > 1 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 2) {
                ResetPrimaryCounters(0x31C);

                return;
            }
            if (animationStage > 0 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 1) {
                ResetPrimaryCounters(0x31C);
                return;
            }
            if (animationStage > 1 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(2);
        return;
    }

    case 0x8C: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 0.0f;
            collisionResult = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x8F: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            collisionResult = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x90: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 0.0f;
            collisionResult = 0;
            scriptCounterF00 = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x91: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            verticalAcceleration = 0.5f;
            collisionResult = 0;
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - verticalAcceleration;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x96: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x97: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x98: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x9A: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9B: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9C: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9E: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            velocityX = -6.0f;
            velocityY = 8.0f;
            verticalAcceleration = 0.75f;
        }

        if (y >= FloatConstants::Zero) {

            velocityY = velocityY - verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x9F: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA0: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA1: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA3: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA4: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA5: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX) * FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA7: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            Fighter::PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing) * 30) + (x),

                (y) + GeometryConstants::Hundred,
                facing, 1);
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        opponentVelocityDeltaX = (-scriptCounterF00) * FloatConstants::OneTenth;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00 - 10;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA8: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            Fighter::PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing) * 30) + (x),

                (y) + GeometryConstants::Hundred,
                facing, 1);
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX) + FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        opponentVelocityDeltaX = (-scriptCounterF00) * FloatConstants::OneTenth;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00 - 10;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xB4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = 8.0f;
            velocityY = 12.5f;
            verticalAcceleration = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(8);
            return;
        }
        return;
    }

    case 0xB5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = -8.0f;
            velocityY = 12.5f;
            verticalAcceleration = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(10);
            return;
        }
        return;
    }

    case 0xC8: {
        field3AC = 1;
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            scriptCounterF00 = 0;
        }
        if (velocityX > FloatConstants::Ten) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Ten)
                velocityX = 10.0f;
        }
        if (inputY < 0) {
            if (static_cast<int>(facing) * inputX > 0) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            ResetPrimaryCounters(0xCC);
            return;
        }
        if (scriptCounterF00 > 0 && static_cast<int>(facing) * inputX <= 0) {
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<int>(facing) * inputX > 0 && scriptCounterF00 < 5) {
                ResetSecondaryCounter(2);
                ++scriptCounterF00;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.5f;
            SpawnAuxEffect(0x7D,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::Eighty, facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Eighty, facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        return;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 0.0f;
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 3.0f;
            verticalAcceleration = 0.3f;
            SpawnAuxEffect(0x7D,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::Eighty, -facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Eighty, -facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (y > FloatConstants::Zero && animationStage > 0 && animationStage < 9) {
            velocityY -= verticalAcceleration;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                verticalAcceleration = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            ResetSecondaryCounter(8);
        }
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            verticalAcceleration = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 3.0f;
            verticalAcceleration = 0.4f;
            SpawnAuxEffect(0x7D,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (y > FloatConstants::Zero && animationStage > 1) {
            velocityY -= verticalAcceleration;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                verticalAcceleration = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            verticalAcceleration = 0.0f;
        }
        if (y > FloatConstants::Zero && animationStage > 0) {
            velocityY -= verticalAcceleration;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                verticalAcceleration = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -8.0f;
            velocityY = 3.0f;
            verticalAcceleration = 0.4f;
            SpawnAuxEffect(0x7D,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::Hundred, -facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Hundred, -facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        return;
    }

    case 0xCC: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 2 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(3);

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 19.0f;
                verticalAcceleration = 0.6f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount) animationStage = animationStage - 2;
            BindAnimation();
        }
        break;
    }

    case 0xCD: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 2 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(3);

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 8.5f;
                velocityY = 15.0f;
                verticalAcceleration = 0.6f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount) animationStage = animationStage - 2;
            BindAnimation();
        }
        break;
    }

    case 0xCE: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -8.5f;
                velocityY = 15.0f;
                verticalAcceleration = 0.6f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount) animationStage = animationStage - 2;
            BindAnimation();
        }
        break;
    }

    case 0xCF: {
        field3AC = 1;
        velocityX -= FloatConstants::Half;
        if (velocityX < FloatConstants::Zero) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            field3AC = 0;
        }
        return;
    }

    case 0xD0: {
        if (animationStage == 0 && animationFrame == 0) {
            facing = static_cast<signed char>(-facing);
            velocityX = -velocityX;
        }
        if (verticalAcceleration == FloatConstants::Zero)
            verticalAcceleration = 0.6f;
        velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0xD1: {
        if (spirit < 2) {
            ResetPrimaryCounters(0);
            return;
        }
        spirit = static_cast<short>(spirit - 3);
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            Fighter::PlaySharedSound(0x2C);
            SpawnBattleEffect(0x3E6, x,
                (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(0);
        }
        return;
    }

    case 0xD2: {
        if (spirit < 2) {
            ResetPrimaryCounters(9);
            break;
        }
        spirit = spirit - 3;
        if (animationStage == 0 && animationFrame == 0) {

            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            PlaySharedSound(0x2C);

            SpawnBattleEffect(0x3e6, x,
                    (y) + GeometryConstants::Hundred,
                    facing, 1);
        }

        velocityY = velocityY - (verticalAcceleration) * FloatConstants::Quarter;
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
        }
        break;
    }

    // Normal attacks with separate ground and air recovery.
    case 0x12C: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x12D: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x32D, x, y, facing, 1);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        return;
    }

    case 0x12E: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1B);
        return;
    }

    case 0x12F: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
                        remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1D);
        break;
    }

    case 0x130: {
        velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            verticalAcceleration = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1C);
        if (animationStage == 2 && animationFrame == 0)
            SpawnBattleEffect(0x335, x, y, facing, 1);
        return;
    }

    case 0x131: {
        velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            verticalAcceleration = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0) {
            if (static_cast<unsigned int>(inputB) > 0) {
                ResetSecondaryCounter(5);
                return;
            }
            PlaySharedSound(0x1D);
        }
        if (animationStage == 4 && animationFrame == 0)
            SpawnBattleEffect(0x32E, x, y, facing, 1);
        if (animationStage == 5 && animationFrame == 0)
            ResetSecondaryCounter(8);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage == 7 && animationFrame == 0)
            SpawnBattleEffect(0x32C, x, y, facing, 1);
        return;
    }

    case 0x133: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 0;
            collisionResult = 1;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x32F, x, y, facing, 1);
            SpawnBattleEffect(0x333, static_cast<float>(facing * 60) + x, y, facing, 1);
            PlaySound(6);
        }
        return;
    }

    case 0x134: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 0;
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x334, static_cast<float>(facing * 60) + x, y, facing, 1);
            PlaySound(6);
        }
        return;
    }

    case 0x135: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            field3AC = 0;
            collisionResult = 0;
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::NineTenths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0)
            velocityX = 13.0f;
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1D);
        return;
    }

    case 0x136: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            field3AC = 0;
            collisionResult = 0;
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::NineTenths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0)
            velocityX = 13.0f;
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1D);
        return;
    }

    case 0x137: {
        velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            verticalAcceleration = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x32F, x, y, facing, 1);
            SpawnBattleEffect(0x334, static_cast<float>(facing * 60) + x, y, facing, 1);
            PlaySound(6);
        }
        return;
    }

    case 0x138: {
        velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            verticalAcceleration = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x336, static_cast<float>(facing * 60) + x, y, facing, 1);
            PlaySound(6);
        }
        return;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 8.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::Half;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        return;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::TwoFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x32D, x, y, facing, 1);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        return;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::TwoFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1D);
        }
        return;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 3;
            collisionResult = 0;
            velocityX = 10.0f;
            scriptCounterF00 = 0;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::ThreeTenths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x32F, x, y, facing, 1);
            SpawnBattleEffect(0x357, static_cast<float>(facing * 120) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 1);
            PlaySound(6);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            collisionResult = 0;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x18A: {
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 15.0f;
            scriptCounterF00 = 0;
        }
        velocityX -= FloatConstants::ThreeFifths;
        if (velocityX < FloatConstants::Zero) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x327,
                static_cast<float>(facing * 151) + x,
                (y) + GeometryConstants::HundredFour, facing, 1);
        }
        return;
    }

    case 0x18B: {
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x328,
                static_cast<float>(static_cast<int>(facing) << 7) + x,
                (y) + GeometryConstants::Seventy, facing, 1);
        }
        return;
    }

    // Projectile startup. 0x190 fires four 0x33B objects at the angles in effect parameter 0.
    case 0x190: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            field314 = 5.0f;
            SpawnBattleEffect(0x33b, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -5.0f;
            SpawnBattleEffect(0x33b, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = 20.0f;
            SpawnBattleEffect(0x33b, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -20.0f;
            SpawnBattleEffect(0x33b, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x191: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            field314 = 45.0f;
            SpawnBattleEffect(0x33d, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -25.0f;
            SpawnBattleEffect(0x33d, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = 25.0f;
            SpawnBattleEffect(0x33d, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -45.0f;
            SpawnBattleEffect(0x33d, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            field314 = 55.0f;
            SpawnBattleEffect(0x343, static_cast<float>(facing * 115) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
            field314 = 65.0f;
            SpawnBattleEffect(0x343, static_cast<float>(facing * 115) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
            field314 = 45.0f;
            SpawnBattleEffect(0x343, static_cast<float>(facing * 115) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
            field314 = 75.0f;
            SpawnBattleEffect(0x343, static_cast<float>(facing * 115) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            collisionResult = 1;
        }
        if (y + velocityY <= FloatConstants::Zero) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            field314 = 5.0f;
            SpawnBattleEffect(0x341, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -5.0f;
            SpawnBattleEffect(0x341, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = 20.0f;
            SpawnBattleEffect(0x341, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -20.0f;
            SpawnBattleEffect(0x341, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x195: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            collisionResult = 1;
        }
        if (y + velocityY <= FloatConstants::Zero) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            field314 = 45.0f;
            SpawnBattleEffect(0x33f, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -35.0f;
            SpawnBattleEffect(0x33f, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = 25.0f;
            SpawnBattleEffect(0x33f, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            field314 = -45.0f;
            SpawnBattleEffect(0x33f, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x196: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 0;
            collisionResult = 1;
        }
        if (field3AC > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            for (int shot = 0; shot < 8; ++shot) {
                field314 = static_cast<float>(shot * 45);
                SpawnBattleEffect(0x35E, static_cast<float>(facing * 106) + x,
                    (y) + GeometryConstants::HundredFortyFour, facing, 1);
            }
            PlaySound(2);
        }
        return;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 0;
            collisionResult = 1;
        }
        if (field3AC > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x32F, x, y, facing, 1);
            SpawnBattleEffect(0x354, static_cast<float>(facing * 60) + x, y, facing, 1);
            PlaySound(6);
        }
        return;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x358, static_cast<float>(facing * 115) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
            PlaySound(0x18);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            collisionResult = 1;
        }
        if (animationStage > 8)
            velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            for (int shot = 0; shot < 8; ++shot) {
                field314 = static_cast<float>(shot * 45);
                SpawnBattleEffect(0x35E, static_cast<float>(facing * 78) + x,
                    (y) + GeometryConstants::HundredFive, facing, 1);
            }
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (animationStage > 4 && scriptCounterF00 <= 0 && scriptCounterF02 < 10) {
            UpdateGaugeTimer(10);
            PlaySound(0x16);
            field314 = static_cast<float>(10 - RecordedRange(0, 20));
            SpawnBattleEffect(0x324, static_cast<float>(facing * 65) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            ++scriptCounterF02;
            scriptCounterF00 = 2;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            SpawnBattleEffect(0x355, static_cast<float>(facing * 115) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
            PlaySound(0x18);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            collisionResult = 1;
        }
        if (animationStage > 8)
            velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            SpawnBattleEffect(0x355, static_cast<float>(facing * 77) + x,
                (y) + GeometryConstants::HundredEighteen, facing, 1);
            PlaySound(0x18);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x1A1: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (y + velocityY <= FloatConstants::Zero) {
            velocityY = 0.0f;
            velocityX = 0.0f;
            y = 0.0f;
        }
        --scriptCounterF00;
        if (animationStage > 3 && scriptCounterF00 <= 0 && scriptCounterF02 < 10) {
            UpdateGaugeTimer(10);
            PlaySound(0x16);
            field314 = static_cast<float>(RecordedRange(0, 20) - 10);
            SpawnBattleEffect(0x324, static_cast<float>(facing * 78) + x,
                (y) + GeometryConstants::HundredFive, facing, 1);
            ++scriptCounterF02;
            scriptCounterF00 = 2;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF02 < 10)
            ResetSecondaryCounter(5);
        return;
    }

    // 0x1F4 and 0x1F5 start the timed horizontal pull at stage 6.
    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 0;
            collisionResult = 0;
            field3AC = 0;
        }
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(17);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(9);
            UpdateGaugeTimer(200);
            fieldF10 = 90;
            velocityY = 6.0f;
            verticalAcceleration = 0.6f;
            scriptCounterF00 = 100;
        }
        if (animationFrame == 0)
            collisionResult = 0;
        if (animationStage == 13 && animationFrame == 0 && velocityY > GeometryConstants::Twelve) {
            ResetSecondaryCounter(6);
            collisionResult = 0;
        }
        if (animationStage == 17 && animationFrame == 0)
            ResetSecondaryCounter(15);
        return;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 10;
            collisionResult = 0;
            field3AC = 0;
        }
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(17);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(9);
            fieldF10 = 120;
            UpdateGaugeTimer(250);
            velocityY = 10.0f;
            verticalAcceleration = 0.5f;
        }
        if (animationFrame == 0)
            collisionResult = 0;
        if (animationStage == 13 && animationFrame == 0 && velocityY > FloatConstants::Four) {
            ResetSecondaryCounter(6);
            collisionResult = 0;
        }
        if (animationStage == 17 && animationFrame == 0)
            ResetSecondaryCounter(15);
        return;
    }

    // Spirit Strike and its recovery variants.
    case 0x252: {
        if (animationStage == 0 && animationFrame == 0) {
            --bombCount;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (spiritCooldown == 0 && collisionResult == 1)
            spirit = 1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x253: {
        if (animationStage == 0 && animationFrame == 0) {
            --bombCount;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (spiritCooldown == 0 && collisionResult == 1)
            spirit = 1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x254: {
        if (animationStage == 0 && animationFrame == 0) {
            --bombCount;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x255: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred,
                facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x256: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred,
                facing, 1);
        }

        break;
    }

    case 0x257: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred,
                facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x258: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            SpawnBattleEffect(0x332, x, y, facing, 1);
            SpawnAuxEffect(0x7F, x - static_cast<float>(facing * 60), 0.0f, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x259: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x329, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            SpawnBattleEffect(0x332, x, y, facing, 1);
            SpawnAuxEffect(0x7F, x - static_cast<float>(facing * 60), 0.0f, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            field314 = static_cast<float>(fieldF04);
            SpawnBattleEffect(0x328, static_cast<float>(facing * 40) + x,
                (y) + GeometryConstants::FortyFive, facing, 1);
            PlaySound(2);
            velocityX = -8.0f;
            velocityY = 8.0f;
        }
        if (animationStage > 2) {
            velocityY -= FloatConstants::ThreeFifths;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x25C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x338, opponent->x, 0.0f, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x260: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x35D, static_cast<float>(facing * 100) + x, 0.0f, facing, 1);
        return;
    }

    case 0x261: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x35D, static_cast<float>(facing * 300) + x, 0.0f, facing, 1);
        return;
    }

    case 0x262: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x35D, static_cast<float>(facing * 500) + x, 0.0f, facing, 1);
        return;
    }

    case 0x263: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            collisionResult = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            PlaySound(10);
            field314 = 75.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -75.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = 45.0f;
            field314 = 60.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = 45.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -45.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
        }
        return;
    }

    case 0x264: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            collisionResult = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            PlaySound(10);
            field314 = 105.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = 90.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = 75.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -105.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -90.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -75.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x346, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::SeventySeven, facing, 1);
        }
        return;
    }

    case 0x266: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 13) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = 8.0f;
            SpawnBattleEffect(0x329, x, (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (animationStage == 13 && animationFrame == 0 && scriptCounterF00 < 1) {
            ResetSecondaryCounter(6);
            ++scriptCounterF00;
        }
        return;
    }

    // Spell-card actions. 0x2BC spends stock at stage 3 and creates 0x320/0x321 in stages 4/5.
    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        } else if (animationStage == 0 && animationFrame != 0) {
            // Continue the startup animation.
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 33),
                (y) + GeometryConstants::HundredSeventy, facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(800, static_cast<float>(facing * 66) + x,
                (y) + GeometryConstants::SixtySeven, facing, 1, 0, 1);
            PlaySound(0x15);
        }
        if (animationStage == 5 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x321, x - static_cast<float>(facing * 72),
                (y) + g_PatchouliEffectYAt00659748, facing, 1, 0, 1);
            UpdateGaugeTimer(250);
        }
        return;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 20;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > FloatConstants::Zero)
                ResetPrimaryCounters(9);
        }
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 30) + x,
                (y) + GeometryConstants::HundredSeventySeven, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 7 && animationFrame == 0) {
            if (facing * inputX > 0)
                --scriptCounterF02;
            if (facing * inputX < 0)
                ++scriptCounterF02;
            if (scriptCounterF02 > 40)
                scriptCounterF02 = 40;
            if (scriptCounterF02 < 10)
                scriptCounterF02 = 10;
            field314 = static_cast<float>(RecordedRange(0, scriptCounterF02 * 2) - scriptCounterF02);
            PlaySound(12);
            SpawnBattleEffect(0x323, static_cast<float>(facing * 70) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            UpdateGaugeTimer(10);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 12) {
            ++scriptCounterF00;
            if (facing * inputX > 0)
                --scriptCounterF02;
            if (facing * inputX < 0)
                ++scriptCounterF02;
            if (scriptCounterF02 > 40)
                scriptCounterF02 = 40;
            if (scriptCounterF02 < 10)
                scriptCounterF02 = 10;
            field314 = static_cast<float>(RecordedRange(0, scriptCounterF02 * 2) - scriptCounterF02);
            PlaySound(12);
            SpawnBattleEffect(0x323, static_cast<float>(facing * 70) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            ResetSecondaryCounter(6);
            UpdateGaugeTimer(10);
        }
        return;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
            remainingHits = 99;
        }
        if (animationStage > 6 && animationStage < 9) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 7 && animationFrame == 0)
            PlaySound(13);
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 62),
                (y) + GeometryConstants::HundredSeven, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 2.0f;
            velocityY = 3.5f;
            verticalAcceleration = 0.05f;
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x349, x, (y) + GeometryConstants::Eighty, facing, 0);
            for (int shot = 0; shot < 3; ++shot) {
                field314 = static_cast<float>(shot);
                SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            }
        }
        if (animationStage == 9 && animationFrame == 0) {
            collisionResult = 0;
            ResetSecondaryCounter(7);
        }
        return;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            return;
        }
        if (animationStage > 6 && animationStage < 9) {
            if (animationStage < 9)
                SetCameraShake(10.0f);
            if (spirit > 5)
                UpdateGaugeTimer(5);
            else
                UpdateGaugeTimer(spirit - 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            PlaySound(14);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 20) + x,
                (y) + GeometryConstants::TwoHundredForty, facing, 1);
            Fighter::SpawnTrackedEffect(0x351, static_cast<float>(facing * 20) + x,
                (y) + GeometryConstants::TwoHundredForty, facing, 1, 0, 1);
        }
        if (animationStage == 9 && animationFrame == 0 && spirit > 5)
            ResetSecondaryCounter(7);
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 10) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        return;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            collisionResult = 1;
            ClearMotionFields();
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 12) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::SpawnTrackedEffect(0x34A, x, y, facing, 0, 0, 1);
        }
        --scriptCounterF02;
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x35A, x, y, facing, 0);
        if (animationStage > 2 && animationStage < 7 && scriptCounterF02 <= 0) {
            UpdateGaugeTimer(5);
            SetPolarVelocity(static_cast<float>(fieldF04), 220.0f);
            fieldF04 += 10;
            if (fieldF04 == 180)
                fieldF04 = 0;
            SpawnBattleEffect(0x34B, x + velocityX, (velocityY) * g_PatchouliEffectYAt00659740,
                facing, velocityY < FloatConstants::Zero);
            SpawnBattleEffect(0x35C, x + velocityX, (velocityY) * g_PatchouliEffectYAt00659740,
                facing, velocityY < FloatConstants::Zero);
            SpawnBattleEffect(0x34B, x - velocityX, -(velocityY) * g_PatchouliEffectYAt00659740,
                facing, velocityY < FloatConstants::Zero);
            SpawnBattleEffect(0x35C, x - velocityX, -(velocityY) * g_PatchouliEffectYAt00659740,
                facing, velocityY < FloatConstants::Zero);
            scriptCounterF02 = 2;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            return;
        }
        if (animationStage == 3 && animationFrame == 0)
            PlaySound(0x11);
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(3);
        }
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnAuxEffect(0x74, static_cast<float>(facing * 12) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            PlaySound(0x12);
            field314 = 0.0f;
            Fighter::SpawnTrackedEffect(0x34c, x, y, facing, 1, 0, 1);
            field314 = 1.0f;
            Fighter::SpawnTrackedEffect(0x34d, x, y, facing, 1, 0, 1);
            field314 = 2.0f;
            Fighter::SpawnTrackedEffect(0x34e, x, y, facing, 1, 0, 1);
            field314 = 3.0f;
            Fighter::SpawnTrackedEffect(0x34f, x, y, facing, 1, 0, 1);
            field314 = 4.0f;
            Fighter::SpawnTrackedEffect(0x350, x, y, facing, 1, 0, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            return;
        }
        break;
    }

    case 0x2D0: {
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(10);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = static_cast<float>(RecordedRange(0, 4) + 8);
            velocityY = static_cast<float>(RecordedRange(0, 5) + 9);
            verticalAcceleration = 0.3f;
        }
        if (animationStage == 8 && animationFrame == 0)
            ResetSecondaryCounter(6);
        return;
    }

    case 0x2D1: {
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(10);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = static_cast<float>(-8 - RecordedRange(0, 4));
            velocityY = static_cast<float>(RecordedRange(0, 5) + 9);
            verticalAcceleration = 0.3f;
        }
        if (animationStage == 8 && animationFrame == 0)
            ResetSecondaryCounter(6);
        return;
    }

    case 0x2DB: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = static_cast<short>(RecordedRange(0, 36));
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 180 - g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 4 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(800, static_cast<float>(facing * 66) + x,
                (y) + GeometryConstants::SixtySeven, facing, 1, 0, 1);
            PlaySound(0x15);
        }
        if (animationStage == 5 && animationFrame == 0) {
            field314 = static_cast<float>(scriptCounterF00 + 18);
            field318 = -20.0f;
            Fighter::SpawnTrackedEffect(900, x - static_cast<float>(facing * 72),
                (y) + g_PatchouliEffectYAt00659748, facing, 1, 0, 1);
        }
        return;
    }

    case 0x2E5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            fieldF06 = 0;
        }
        if (y > FloatConstants::Zero && (animationStage < 4 || animationStage > 11)) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(16);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage > 7 && animationStage < 11 &&
                fieldF04 < g_OptionsModeAt006714D0 * 2 + 3) {
            --fieldF06;
            if (fieldF06 <= 0) {
                SpawnBattleEffect(0x391, static_cast<float>(facing * 77) + x,
                    (y) + GeometryConstants::HundredEighteen, facing, 1);
                PlaySound(0x18);
                fieldF06 = 15;
                ++fieldF04;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(60, 90) - g_OptionsModeAt006714D0 * 20);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -4.0f;
            velocityY = 12.0f;
            verticalAcceleration = 0.3f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF02 < 5) {
            ++scriptCounterF02;
            ResetSecondaryCounter(8);
        }
        if (animationStage == 16 && animationFrame == 0)
            ResetSecondaryCounter(14);
        return;
    }

    case 0x2E6: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 20;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage <= 3 && animationFrame < 25) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 3) {
                SpawnAuxEffect(0x3E, x - static_cast<float>(facing * 28),
                    (y) + GeometryConstants::HundredEighty, 1, 1);
                scriptCounterF02 = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > FloatConstants::Zero)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(RecordedRange(60, 90) - g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 7 && animationFrame == 0) {
            field314 = static_cast<float>(RecordedRange(0, 40) - 20);
            PlaySound(12);
            SpawnBattleEffect(0x390, static_cast<float>(facing * 70) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            field314 = static_cast<float>(RecordedRange(0, 20) - 10);
            PlaySound(12);
            SpawnBattleEffect(0x390, static_cast<float>(facing * 70) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x2EF: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 10;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (y > FloatConstants::Zero && animationStage > 19) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(24);
                y = 0.0f;
                return;
            }
        }
        if (animationStage > 5 && animationStage < 20) {
            opponentVelocityDeltaX = static_cast<float>(scriptCounterF00) * FloatConstants::OneTenth *
                static_cast<float>(facing * opponent->facing) *
                static_cast<float>(2 * ((opponent->x - x) * facing > FloatConstants::Zero) - 1);
            scriptCounterF00 -= 2;
            --fieldF04;
            if (scriptCounterF00 < 40)
                scriptCounterF00 = 40;
            if (fieldF04 <= 0) {
                if (facing == 1) {
                    SpawnBattleEffect(0x38B, cameraState.viewLeft - GeometryConstants::Hundred,
                        static_cast<float>(RecordedRange(0, 280)), facing, 1);
                }
                if (facing == -1) {
                    SpawnBattleEffect(0x38B, (viewRight) + GeometryConstants::Hundred,
                        static_cast<float>(RecordedRange(0, 280)), facing, 1);
                }
                fieldF04 = static_cast<short>(35 - g_OptionsModeAt006714D0 * 8);
            }
            if (RecordedRange(0, 100) < 50) {
                SpawnBattleEffect(0x38C, static_cast<float>(RecordedRange(0, 640) * facing) + x,
                    0.0f, facing, 1);
            } else {
                SpawnBattleEffect(0x38C, x - static_cast<float>(RecordedRange(0, 640) * facing),
                    0.0f, -facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(180 - g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 5 && animationFrame == 0)
            scriptCounterF00 = 100;
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(9);
            velocityX = static_cast<float>(RecordedRange(0, 4) - 2);
            velocityY = 1.5f;
            verticalAcceleration = 0.2f;
        }
        if (animationFrame == 0)
            collisionResult = 0;
        if (animationStage == 20 && animationFrame == 0 && scriptCounterF02 < 10) {
            ++scriptCounterF02;
            ResetSecondaryCounter(13);
        }
        if (animationStage == 24 && animationFrame == 0)
            ResetSecondaryCounter(22);
        return;
    }

    case 0x31B: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x, y, facing, 1);
        }
        if (animationStage == 9 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        } else if (animationStage == 9 && animationFrame != 0) {
            // Continue the repeat animation.
        }
        break;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (roundSpellVariants[roundsRemaining] == 1)
                SpawnBattleEffect(0x393, -200.0f, -200.0f, 1, 1);
        }
        if (animationStage == 12 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 15 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(0xD);
            field3CF = 1;
        }
        return;
    }

    default:
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;

    advanceFrame:
        AdvanceNestedFrame();
    }
}
