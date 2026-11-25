#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/alice/AliceFighter.hpp"

extern float g_AliceEffectYAt0065909C;
extern float g_AliceEffectYAt00659478;
extern float g_MarisaResourceYAt00659274;
extern float g_OneShotYAt0065928C;

void AliceFighter::Advance() {
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
        velocityX = 6.0f;
        goto advanceFrame;
    }

    case 0x5: {
        velocityX = -6.0f;
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
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 15.0f;
                verticalAcceleration = 0.65f;
            }
            if (animationStage >= animationStageCount)
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
                velocityX = 5.0f;
                velocityY = 15.0f;
                verticalAcceleration = 0.65f;
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
        if (y > FloatConstants::Zero &&
            ((velocityY = velocityY - verticalAcceleration), y + velocityY <= FloatConstants::Zero)) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -5.0f;
                velocityY = 15.0f;
                verticalAcceleration = 0.65f;
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x47: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            verticalAcceleration = 0.8f;
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x48: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            verticalAcceleration = 1.3f;
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
            Fighter::PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(8);
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
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(animationStage-1);
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
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
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
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f,95.0f,0.0f);
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
            scriptCounterF00 = static_cast<short>((velocityX)*GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY)*GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x59);
            SetCameraShake(3.0f);
            Fighter::PlaySharedSound(0x16);
            for (int burst=0;burst < 10;++burst)
                SpawnBattleEffect(0x3E4,x,y,1,1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3,x,y,1,1);
            }
            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(animationStage-1);
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

        }
        return;
    }

    case 0x59: {
        if (animationStage == 3) {
            rotationZ = (rotationZ)+GeometryConstants::Forty;
            velocityY = velocityY-verticalAcceleration;
            if (velocityY+y <= FloatConstants::Zero) {
                scriptCounterF00 = (velocityX)*GeometryConstants::Hundred;
                scriptCounterF02 = (velocityY)*GeometryConstants::Hundred;
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
            ResetSecondaryCounter(3);
        else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*FloatConstants::OneFourHundredth;
            velocityY = static_cast<float>(-scriptCounterF02)*FloatConstants::OneHundredth;
            verticalAcceleration = 0.7f;
            ResetTransform(0.0f,95.0f,0.0f);
        }
        return;
    }

    case 0x5D: {
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 15.0f;
        if (animationStage < 11 && y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(11);
                return;
            }
        }
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
        if (animationStage == 8 && animationFrame == 0)
            velocityX = 0.0f;
        return;
    }

    case 0x5E: {
        if (animationStage == 0 && animationFrame == 0)
            velocityX = -15.0f;
        if (animationStage < 12 && y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(12);
                return;
            }
        }
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
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
        } else if (animationStage == 8 && animationFrame != 0) {
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
            for (int shot=0;shot < 10;++shot)
                SpawnBattleEffect(0x3E4,x,y,1,1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3,x,y,1,1);
            }
        }
        if (animationStage <= 6 && animationStage > 2) {
            velocityY = velocityY-verticalAcceleration;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                break;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0x62);
            if ((field3CF) == 0)
                ResetPrimaryCounters(0x63);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*FloatConstants::OneTwoHundredth;
            velocityY = static_cast<float>(-scriptCounterF02)*FloatConstants::OneTwoHundredth;
            verticalAcceleration = 2.0f;
        }
        break;
    }

    case 0x61: {
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
            for (int shot=0;shot < 10;++shot)
                SpawnBattleEffect(0x3E4,x,y,1,1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3,x,y,1,1);
            }
        }
        if (animationStage <= 6 && animationStage > 2) {
            velocityY = velocityY-verticalAcceleration;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
                break;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0x62);
            if ((field3CF) == 0)
                ResetPrimaryCounters(0x63);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*FloatConstants::OneTwoHundredth;
            velocityY = static_cast<float>(-scriptCounterF02)*FloatConstants::OneTwoHundredth;
            verticalAcceleration = 2.0f;
        } else if (animationStage == 3 && animationFrame != 0) {

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
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
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
        velocityY = velocityY-verticalAcceleration;
        if (velocityY+y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX)*GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY)*GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(8);
        return;
    }

    case 0x96: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x97: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x98: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x9A: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9B: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9C: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x9E: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            velocityX = -6.0f;
            velocityY = 8.0f;
            verticalAcceleration = 0.75f;

        }

        if (y >= FloatConstants::Zero) {

            velocityY = velocityY-verticalAcceleration;
            if (y+velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x9F: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA0: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA1: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {

            scriptCounterF00 = 0;
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;

        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA3: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -9.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA4: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA5: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -13.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (CheckHorizontalLimits() && field3BE)
            opponentVelocityDeltaX = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0xA7: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            Fighter::PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing)*30)+(x),

                (y)+GeometryConstants::Hundred,
                facing,1);
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        opponentVelocityDeltaX = (-scriptCounterF00)*FloatConstants::OneTenth;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00-10;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0xA8: {
        pendingSpellCharge = (pendingSpellCharge)+FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            Fighter::PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing)*30)+(x),

                (y)+GeometryConstants::Hundred,
                facing,1);
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        opponentVelocityDeltaX = (-scriptCounterF00)*FloatConstants::OneTenth;
        if (scriptCounterF00 > 0)
            scriptCounterF00 = scriptCounterF00-10;
        if (AdvanceNestedFrame()==animationStageCount)
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
            velocityY = velocityY-verticalAcceleration;
            if (y+velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetSecondaryCounter(7);
            break;
        }
        break;
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
        if ((y) > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(7);
            return;
        }
        break;
    }

    case 0xC8: {
        field3AC = 1;
        SetCommandSelection(3,4,0xFF);
        if (animationStage == 0 && animationFrame == 0) { velocityX=0.0f; scriptCounterF00=0; }
        if ((velocityX) > GeometryConstants::Nine) {
            velocityX = (velocityX)-FloatConstants::Half;
            if ((velocityX) < GeometryConstants::Nine) velocityX=9.0f;
        }
        if (inputY < 0) {
            if (facing*inputX > 0) {
                ResetPrimaryCounters(0xCD);
                break;
            }
            ResetPrimaryCounters(0xCC);
            break;
        }
        if (scriptCounterF00 > 0 && facing*inputX <= 0) {
            ResetPrimaryCounters(0xCF);
            break;
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            if (facing*inputX > 0 && scriptCounterF00 < 6) {
                ResetSecondaryCounter(3);
                ++scriptCounterF00;
                break;
            }
            ResetPrimaryCounters(0xCF);
            break;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 10.0f;
            SpawnAuxEffect(0x7D,float(facing*80)+(x),
                (y)+GeometryConstants::Eighty,facing,1);
            SpawnAuxEffect(0x7E,x,(y)+GeometryConstants::Eighty,
                facing,1);
            PlaySharedSound(31);
        }
        break;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 0.0f;
        if (y > FloatConstants::Zero && animationStage > 2 && animationStage < 11) {
            velocityY -= verticalAcceleration;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                verticalAcceleration = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(11);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 4.5f;
            verticalAcceleration = 0.6f;
            SpawnAuxEffect(0x7D, x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::Eighty, -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::Eighty, -facing, 1);
            PlaySharedSound(0x1F);
        }
        if (animationStage == 11 && animationFrame == 0)
            ResetSecondaryCounter(9);
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
            velocityX = 8.5f;
            velocityY = 5.0f;
            verticalAcceleration = 0.6f;
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
            velocityX = -8.5f;
            velocityY = 5.0f;
            verticalAcceleration = 0.6f;
            SpawnAuxEffect(0x7D,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::Hundred, -facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Hundred, -facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (animationStage == 4 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(2);
        }
        return;
    }

    case 0xCC: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3,4,0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0) ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY-verticalAcceleration;
            if (y+velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);

        ++animationFrame;
        if (animationFrame>=animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 19.0f;
                verticalAcceleration = 0.65f;
                field3AC = 0;
                SpawnAuxEffect(0x3C,x,y,1,1);
            }
            if (animationStage>=animationStageCount) animationStage=animationStage-2;
            BindAnimation();
        }
        break;
    }

    case 0xCD: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3,4,0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0) ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY-verticalAcceleration;
            if (y+velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);

        ++animationFrame;
        if (animationFrame>=animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 9.0f;
                velocityY = 15.0f;
                verticalAcceleration = 0.65f;
                field3AC = 0;
                SpawnAuxEffect(0x3C,x,y,1,1);
            }
            if (animationStage>=animationStageCount) animationStage=animationStage-2;
            BindAnimation();
        }
        break;
    }

    case 0xCE: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3,4,0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0) ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY-verticalAcceleration;
            if (y+velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        ++animationFrame;
        if (animationFrame>=animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = -9.0f;
                velocityY = 15.0f;
                verticalAcceleration = 0.65f;
                field3AC = 0;
                SpawnAuxEffect(0x3C,x,y,1,1);
            }
            if (animationStage>=animationStageCount) animationStage=animationStage-2;
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
            return;
        }
        spirit = static_cast<short>(spirit - 3);
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x3E6, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            velocityX *= 0.25f;
            velocityY *= 0.25f;
            Fighter::PlaySharedSound(0x2C);
        }
        velocityY -= verticalAcceleration * 0.25f;
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
        }
        return;
    }

    // Normal attacks with separate ground and air recovery.
    case 0x12C: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 5;
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
            PlaySharedSound(0x1c);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 8 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 10 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage < 11 && animationFrame == 0)
            collisionResult = 0;
        return;
    }

    case 0x12D: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0) ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX)-FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0);

            scriptCounterF00 = 0;

        }
        if (animationStage == 2 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x12E: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 6;
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
            PlaySharedSound(0x1c);
        if (animationStage == 5 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 7 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 9 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage < 11 && animationFrame == 0)
            collisionResult = 0;
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
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
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
            remainingHits = 4;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 8 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage < 8 && animationFrame == 0)
            collisionResult = 0;
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
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x133: {
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
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x370, static_cast<float>(facing * 260) + x,
                (y) + GeometryConstants::NinetySix, facing, 1);
        }
        return;
    }

    case 0x134: {
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
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1d);
        return;
    }

    case 0x135: {
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
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x1D);
            SpawnBattleEffect(0x34F, x, y, facing, 1);
            SpawnBattleEffect(0x34E, (x) + GeometryConstants::Seventy,
                (y) + FloatConstants::Ten, facing, 1);
            SpawnBattleEffect(0x34E, x - GeometryConstants::Seventy,
                (y) + FloatConstants::Ten, facing, 1);
            SpawnBattleEffect(0x34E, x, (y) + GeometryConstants::Thirty, facing, 0);
        }
        return;
    }

    case 0x136: {
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
        if (animationStage > 8 && velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::FourFifths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0)
            velocityX = 8.0f;
        if (animationStage == 10 && animationFrame == 0)
            PlaySharedSound(0x1d);
        return;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 5;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 6 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 8 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 10 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationFrame == 0 && animationStage < 11)
            collisionResult = 0;
        return;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 12.5f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1d);
        return;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 5;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
        if (animationStage == 5 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 7 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationStage == 9 && animationFrame == 0)
            PlaySharedSound(0x1b);
        if (animationFrame == 0 && animationStage < 11)
            collisionResult = 0;
        return;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 12.5f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1c);
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

    case 0x190: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x330, static_cast<float>(facing * 7) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
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
        }
        if (animationStage == 10 && animationFrame == 0)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 10 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            velocityX = 41.0f;
            SpawnBattleEffect(0x331, static_cast<float>(facing * 51) + x,
                (y) + GeometryConstants::HundredNinety, facing, 1);
            PlaySound(0);
        }
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x332, static_cast<float>(facing * 93) + x,
                (y) + GeometryConstants::SixtyFour, facing, 1);
            PlaySound(0);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0)
            collisionResult = 1;
        velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = -6.0f;
            velocityY = 8.0f;
            verticalAcceleration = 0.5f;
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x34A, static_cast<float>(facing * 26) + x,
                (y) + GeometryConstants::SixtySeven, facing, 1);
            PlaySound(0);
        }
        return;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
        }
        if (animationStage > 3)
            velocityY -= verticalAcceleration;
        if (y + velocityY <= FloatConstants::Zero)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            field314 = 10.0f;
            field318 = -40.0f;
            SpawnBattleEffect(0x34B, static_cast<float>(facing * 27) + x,
                (y) + g_AliceEffectYAt0065909C, facing, 1);
            PlaySound(0);
        }
        return;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);

        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 2) {
            ResetSecondaryCounter(4);
            ++scriptCounterF00;
        }

        return;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + GeometryConstants::Sixty, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);

        return;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
            scriptCounterF00 = 0;
        }
        if (y + velocityY <= FloatConstants::Zero) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19D: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
            scriptCounterF00 = 0;
        }
        if (y + velocityY <= FloatConstants::Zero) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(100);
            SpawnBattleEffect(0x34C, static_cast<float>(facing * 60) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 4.0f;
            field318 = 15.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 6.0f;
            field318 = 18.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 8.0f;
            field318 = 21.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x19F: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 8.0f;
            field318 = 17.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 10.0f;
            field318 = 18.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 12.0f;
            field318 = 21.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 2.0f;
            field318 = 22.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 3.0f;
            field318 = 24.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            field314 = 4.0f;
            field318 = 26.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x1A2: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (y > FloatConstants::Zero && animationStage < 9) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 12.0f;
            verticalAcceleration = 0.8f;
            PlaySound(3);
            UpdateGaugeTimer(250);
            field314 = 6.0f;
            field318 = 8.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 8.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 10.0f;
            field318 = 12.0f;
            SpawnBattleEffect(0x34D, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
            SpawnBattleEffect(0x330,
                (x) + GeometryConstants::Thirty - static_cast<float>(RecordedRange(0, 60)),
                (y) + GeometryConstants::Forty + static_cast<float>(RecordedRange(0, 140)),
                facing, 1);
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::ThreeTenths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(12);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 14.0f;
            verticalAcceleration = 0.8f;
        }
        if (animationStage == 12 && animationFrame == 0)
            ResetSecondaryCounter(10);
        return;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
            SpawnBattleEffect(0x330,
                (x) + GeometryConstants::Thirty - static_cast<float>(RecordedRange(0, 60)),
                (y) + GeometryConstants::Forty + static_cast<float>(RecordedRange(0, 140)),
                facing, 1);
        }
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(12);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 18.0f;
            velocityY = 16.0f;
            verticalAcceleration = 0.8f;
        }
        if (animationStage == 12 && animationFrame == 0)
            ResetSecondaryCounter(10);
        return;
    }

    // Spirit Strike and its recovery variants.
    case 0x252: {
        if (animationStage == 0 && animationFrame == 0) {
            bombCount = bombCount - 1;
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
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x21);
            SpawnAuxEffect(0x37, x, (y) + GeometryConstants::Hundred, facing, 1);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x253: {
        if (animationStage == 0 && animationFrame == 0) {
            bombCount = bombCount - 1;
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
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x21);
            SpawnAuxEffect(0x37, x, (y) + GeometryConstants::Hundred, facing, 1);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x254: {
        if (animationStage == 0 && animationFrame == 0) {
            bombCount = bombCount - 1;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x21);
            SpawnAuxEffect(0x37, x, (y) + GeometryConstants::Hundred, facing, 1);
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
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
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
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
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
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
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
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x327, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::NinetyFive, facing, 1);
            PlaySound(1);
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
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x328, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::NinetyFive, facing, 1);
            PlaySound(1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x329, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::NinetyFive, facing, 1);
            PlaySound(1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX)*FloatConstants::Quarter;
            velocityY = (velocityY)*FloatConstants::Quarter;
            collisionResult = 1;
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x32D,
                float(facing*100)+(x),
                (y)+GeometryConstants::Sixty,
                facing,1);
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(9);
        break;
    }

    case 0x25E: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 85.0f;
            field318 = 2.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 75.0f;
            field318 = 3.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 95.0f;
            field318 = 1.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 105.0f;
            field318 = 0.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            PlaySound(5);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x25F: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 90.0f;
            field318 = 0.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 100.0f;
            field318 = 1.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 110.0f;
            field318 = 2.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 120.0f;
            field318 = 3.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            PlaySound(5);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x260: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            field314 = 90.0f;
            field318 = 0.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 80.0f;
            field318 = 1.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 70.0f;
            field318 = 2.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            field314 = 60.0f;
            field318 = 3.0f;
            SpawnBattleEffect(0x335,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            PlaySound(5);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x264: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (y > FloatConstants::Zero && animationStage < 9) {
            velocityX = (velocityX) + FloatConstants::ThreeTenths;
            velocityY = velocityY + verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(3);
            UpdateGaugeTimer(250);
            field314 = 0.0f;
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            velocityX = -8.0f;
            velocityY = 16.0f;
            verticalAcceleration = -1.2f;
            field314 = 1.0f;
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 2.0f;
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x265: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (y > FloatConstants::Zero && animationStage < 9) {
            velocityY = velocityY + verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = -6.0f;
            velocityY = 16.0f;
            verticalAcceleration = -0.8f;
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 4 && spirit > 0) {
            UpdateGaugeTimer(30);
            field314 = static_cast<float>(70 - scriptCounterF00 * 15);
            SpawnBattleEffect(0x32C, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(3);
            ++scriptCounterF00;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x25D: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x333,
                float(facing*70)+(x),
                (y)+g_OneShotYAt0065928C,
                facing,1);
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        break;
    }

    // Spell-card actions. 0x2BC spends stock at stage 1 and creates 0x340 at stage 14.
    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 40),
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (animationStage == 14 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x340, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 40),
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            field314 = 180.0f;
            SpawnBattleEffect(0x345, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 120.0f;
            SpawnBattleEffect(0x345, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x345, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x345, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x345, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -120.0f;
            SpawnBattleEffect(0x345, x, (y) + GeometryConstants::Hundred, facing, 1);
            SpawnBattleEffect(0x346, x, (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(11);
        }
        return;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33c, static_cast<float>(facing * 65) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 61),
                (y) + GeometryConstants::HundredFifty, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(13);
            SpawnBattleEffect(0x33e, static_cast<float>(facing * 140) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 6) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 40),
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (animationStage == 14 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x341, static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659274, facing, 1);
            PlaySound(9);
        }
        return;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 40),
                (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(12);
            UpdateGaugeTimer(500);
            field314 = 180.0f;
            SpawnBattleEffect(0x347, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 120.0f;
            SpawnBattleEffect(0x347, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x347, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x347, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x347, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -120.0f;
            SpawnBattleEffect(0x347, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 180.0f;
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 120.0f;
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 60.0f;
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -60.0f;
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -120.0f;
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, facing, 1);
            SpawnBattleEffect(0x349, x, (y) + GeometryConstants::Hundred, facing, 1);
        }
        return;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33d, static_cast<float>(facing * 65) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 61),
                (y) + GeometryConstants::HundredFifty, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x33f, static_cast<float>(facing * 180) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            PlaySound(14);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 10) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
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
        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                if (RecordedRange(0, 100) < 50)
                    velocityX = 12.0f;
                else
                    velocityX = -12.0f;
                if (facing == 1 && x > GeometryConstants::Thousand)
                    velocityX = -12.0f;
                if (facing == -1 && x < GeometryConstants::TwoHundredEighty)
                    velocityX = -12.0f;
                velocityY = 17.0f;
                verticalAcceleration = 0.65f;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
    }

    case 0x2DB: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (y > FloatConstants::Zero) {
            velocityY -= verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                ClearMotionFields();
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(16);
        if (animationStage == 2 && animationFrame == 0) {
            velocityY = 16.0f;
            velocityX = static_cast<float>(RecordedRange(0, 4) + 10);
            verticalAcceleration = 0.4f;
        }
        if (animationStage == 10 && animationFrame == 0) {
            if (g_OptionsModeAt006714D0 == 0) {
                for (int shot = 0; shot < 3; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 80);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + GeometryConstants::SixtyFive, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 1) {
                for (int shot = 0; shot < 4; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 120);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + GeometryConstants::SixtyFive, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 2) {
                for (int shot = 0; shot < 5; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 160);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + GeometryConstants::SixtyFive, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 3) {
                for (int shot = 0; shot < 6; ++shot) {
                    field314 = static_cast<float>(shot * 80 - 200);
                    field318 = 10.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 27) + x,
                        (y) + GeometryConstants::SixtyFive, facing, 1);
                }
            }
            PlaySound(7);
        }
        return;
    }

    case 0x2DC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 14 && animationFrame == 0) {
            if (g_OptionsModeAt006714D0 == 0) {
                for (int shot = 0; shot < 3; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 1) {
                for (int shot = 0; shot < 4; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 2) {
                for (int shot = 0; shot < 5; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 3) {
                for (int shot = 0; shot < 6; ++shot) {
                    field314 = static_cast<float>(shot * 40 + 20);
                    field318 = 200.0f;
                    SpawnBattleEffect(900, static_cast<float>(facing * 90) + x,
                        (y) + g_MarisaResourceYAt00659274, facing, 1);
                }
            }
            PlaySound(7);
        }
        return;
    }

    // Airborne descent ends at stage 9 on landing.
    case 0x2DD: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (y > FloatConstants::Zero && animationStage < 9) {
            velocityY = velocityY + verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            verticalAcceleration = -0.5f;
        }
        if (animationStage == 8 && animationFrame == 0 &&
                scriptCounterF00 < g_OptionsModeAt006714D0 * 2 + 2) {
            field314 = static_cast<float>(scriptCounterF00 * 20);
            field318 = static_cast<float>(scriptCounterF00 * 30);
            SpawnBattleEffect(900, static_cast<float>(facing * 10) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(3);
            ++scriptCounterF00;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
        return;
    }

    case 0x2E5: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x38A,
                static_cast<float>((16 - RecordedRange(0, 10)) * facing) + x,
                ((y) + g_AliceEffectYAt00659478) + static_cast<float>(RecordedRange(0, 10)),
                facing, 1);
            aiCardTimer = static_cast<short>(360 - g_OptionsModeAt006714D0 * 60);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        return;
    }

    case 0x2EF: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (y > FloatConstants::Zero && animationStage < 9) {
            velocityY = velocityY + verticalAcceleration;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (animationStage == 5 && animationFrame == 0) {
            if ((x > GeometryConstants::Thousand && facing == -1) ||
                    (x < GeometryConstants::TwoHundredEighty && facing == 1)) {
                velocityX = 10.0f;
                velocityY = 15.0f;
                verticalAcceleration = -0.4f;
            } else {
                velocityX = -1.5f;
                velocityY = 8.0f;
                verticalAcceleration = -0.09f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(3);
            for (int shot = 0; shot < g_OptionsModeAt006714D0 * 3 + 6; ++shot) {
                field314 = static_cast<float>(RecordedRange(0, 180) - 90);
                field318 = static_cast<float>(RecordedRange(0, 80) + 150);
                SpawnBattleEffect(0x38B, static_cast<float>(facing * 10) + x,
                    (y) + GeometryConstants::Hundred, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0)
            ResetSecondaryCounter(7);
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
        if (animationStage == 4 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x, y, facing, 1);
        }
        if (animationStage == 9 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        }
        break;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 11 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 15 && animationFrame == 0 && scriptCounterF00 < 4) {
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
