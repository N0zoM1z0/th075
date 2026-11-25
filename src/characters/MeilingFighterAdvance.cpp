#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/MeilingFighter.hpp"

extern float g_MeilingDoubleShotYAt00659F3C;

void MeilingFighter::Advance() {
    if (hitstopFrames != 0 || opponent->opponentFreezeSnapshot != 0)
        return;

    switch (action) {
    case 0: {
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
        velocityX = -4.5f; goto advanceFrame;
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
            velocityY = velocityY - field05C;
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
                velocityY = 14.0f;
                field05C = 0.7f;
                field3AC = 0;
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
            velocityY = velocityY - field05C;
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
                velocityX = 6.0f;
                velocityY = 14.0f;
                field05C = 0.7f;
                field3AC = 0;
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
            velocityY = velocityY - field05C;
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
                velocityY = 14.0f;
                field05C = 0.7f;
                field3AC = 0;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;
    }

    case 0x9: {
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
    }

    case 0xA: {
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
    }

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
            field490 = static_cast<float>((velocityX) * FloatConstants::ThreeQuartersDouble);
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            field490 =
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
            if (velocityY < FloatConstants::Two)
                velocityY = 2.0f;
            field05C = 0.8f;
            if (velocityY > GeometryConstants::Twelve)
                velocityY = 12.0f;
            collisionResult = 0;
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
        return;
    }

    case 0x47: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;
    }

    case 0x48: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            field05C = 1.3f;
            collisionResult = 0;
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;
    }

    case 0x49: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
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
            field05C = 0.8f;
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
            field05C = 0.5f;
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(6);
        return;
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }

        rotationZ = (rotationZ) + GeometryConstants::Thirty;
        velocityY = velocityY - field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            PlaySharedSound(0x16);
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
        if (animationStage == 3) {
            rotationZ = (rotationZ) + GeometryConstants::Forty;
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                scriptCounterF00 = (velocityX) * GeometryConstants::Hundred;
                scriptCounterF02 = (velocityY) * GeometryConstants::Hundred;
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(0x61);
                rotationZ = 0.0f;
                SetCameraShake(2.0f);
                ClearTransformFlag(); PlaySharedSound(0x16);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(3);
        else if (animationStage == 3 && animationFrame == 0) {
            velocityX = float(int(scriptCounterF00)) * FloatConstants::OneFourHundredth;
            velocityY = float(-int(scriptCounterF02)) * FloatConstants::OneHundredth;
            field05C = 0.7f;
            ResetTransform(-7.0f, 75.0f, 0.0f);
        } else if (animationStage == 3 && animationFrame != 0) {
            // Continue the spinning animation.
        }
        break;
    }

    case 0x5D: {
        if (animationStage < 6 && y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(6);
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
        if (animationStage == 3 && animationFrame == 0) {
            velocityY = 4.5f;
            velocityX = 20.0f;
            field05C = 0.5f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 6 && animationFrame != 0) {
            // Continue the landing animation.
        }
        break;
    }

    case 0x5E: {
        if (animationStage < 6 && y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(6);
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
        if (animationStage == 3 && animationFrame == 0) {
            velocityY = 4.5f;
            velocityX = -20.0f;
            field05C = 0.5f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 6 && animationFrame != 0) {
            // Continue the landing animation.
        }
        break;
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

    case 0x61: {
        if (0 < facing * inputX &&
                ((static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0) || (static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0)))
            scriptCounterF00 = 1;
        if (facing * inputX < 0 &&
                (((static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0) || static_cast<unsigned int>(inputC) > 0) || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int effectIndex61 = 0; effectIndex61 < 10; ++effectIndex61)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage == 2 || animationStage == 3 || animationStage == 4) {
            velocityY -= field05C;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0) {
                ResetPrimaryCounters(99);
            }
        } else {
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = scriptCounterF00 * FloatConstants::OneTwoHundredth;
                velocityY = -scriptCounterF02 * FloatConstants::OneTwoHundredth;
                field05C = 2.0f;
            }
            if (animationStage == 5 && animationFrame == 0) {
                ResetSecondaryCounter(4);
            } else if (animationStage == 5 && animationFrame != 0) {
                // Continue the landing animation.
            }
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
                break;
            }
        } else {
            if (animationStage > 1 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                roundSpellVariants[roundsRemaining] == 5 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 2) {
                ResetPrimaryCounters(0x303);
                break;
            }
            if (animationStage > 1 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 2) {
                ResetPrimaryCounters(0x31C);

                break;
            }
            if (animationStage > 0 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 1) {
                ResetPrimaryCounters(0x31C);
                break;
            }
            if (animationStage > 1 &&
                roundsRemaining > 0 &&
                opponent->action < 150 &&
                static_cast<signed char>(roundKind[roundsRemaining]) == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(2);
        break;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field05C = 0.5f;
            collisionResult = 0;
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            return;
        }
        velocityY = velocityY - field05C;
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
            ResetSecondaryCounter(6);
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field05C = 0.75f;
        }

        if (y > FloatConstants::Zero) {

            velocityY = velocityY - field05C;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX) * FloatConstants::ThreeQuartersDouble;
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
            PlaySharedSound(0x2C);
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
        field490 = (-scriptCounterF00) * FloatConstants::OneTenth;
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
            PlaySharedSound(0x2C);
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
        field490 = (-scriptCounterF00) * FloatConstants::OneTenth;
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
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
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
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(6);
            break;
        }
        break;
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
            if (static_cast<int>(facing) * inputX > 0 && scriptCounterF00 < 3) {
                ResetSecondaryCounter(2);
                ++scriptCounterF00;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 13.0f;
            SpawnAuxEffect(0x7D,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::Eighty, facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Eighty, facing, 1);
            PlaySharedSound(0x1F);
        }
        return;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (y > FloatConstants::Zero && animationStage > 2 && animationStage < 5) {
            velocityY -= field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(5);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = -12.0f;
            velocityY = 7.0f;
            field05C = 0.7f;
            SpawnAuxEffect(0x7D, x,
                (y) + GeometryConstants::Eighty, -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::Eighty, -facing, 1);
            PlaySharedSound(0x1F);
        }
        if (animationStage == 5 && animationFrame == 0) {
            ResetSecondaryCounter(animationStage - 2);
        }
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 11.0f;
            velocityY = 5.0f;
            field05C = 0.45f;
            SpawnAuxEffect(0x7D, float(facing * 80) + (x),
                (y) + GeometryConstants::HundredTen, facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::HundredTen,
                facing, 1);
            PlaySharedSound(31);
        }
        if (y > FloatConstants::Zero && animationStage > 1) {
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f; y = 0.0f; animationFrame = 0;
                ResetPrimaryCounters(10);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(10);
        break;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { scriptCounterF00 = 0; velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; }
        if (y > FloatConstants::Zero && animationStage > 0) {
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f; y = 0.0f; animationFrame = 0;
                ResetPrimaryCounters(10);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(10);
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 5.0f;
            field05C = 0.45f;
            SpawnAuxEffect(0x7D, x, (y) + GeometryConstants::HundredTwenty,
                -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::HundredTwenty,
                -facing, 1);
            PlaySharedSound(31);
        }
        break;
    }

    case 0xCC: {
        if (y == FloatConstants::Zero || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
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
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 21.0f;
                field05C = 0.75f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
    }

    case 0xCD: {
        if ((y == (FloatConstants::Zero)) ||
            velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 3 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(4);

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 11.0f;
                velocityY = 16.0f;
                field05C = 0.7f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage = animationStage - 2;
            BindAnimation();
        }
        break;
    }

    case 0xCE: {
        if (y == FloatConstants::Zero || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
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
                velocityX = -8.0f;
                velocityY = 16.0f;
                field05C = 0.7f;
                field3AC = 0;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        return;
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
            facing = -facing;
            velocityX = -(velocityX);
        }
        if (field05C == (FloatConstants::Zero)) field05C = 0.6f;
        velocityY = velocityY - field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(4);
        break;
    }

    case 0xD1: {
        if (spirit < 2) {
            ResetPrimaryCounters(0);
            break;
        }
        spirit = spirit - 3;
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            PlaySharedSound(0x2C);
            SpawnBattleEffect(0x3e5, x,
                    (y) + GeometryConstants::Hundred,
                    facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(0);
        }
        break;
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

            SpawnBattleEffect(0x3e5, x,
                    (y) + GeometryConstants::Hundred,
                    facing, 1);
        }

        velocityY = velocityY - (field05C) * FloatConstants::Quarter;
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
        }
        break;
    }

    case 0x12C: {
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
        }
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1B);
        return;
    }

    case 0x12D: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) - GeometryConstants::TwentyFive;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) - GeometryConstants::ThirtySix;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) + GeometryConstants::TwentyFive;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) + GeometryConstants::ThirtySix;
        }
        break;
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
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1B);
        return;
    }

    case 0x130: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x131: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage == 8 && animationFrame == 0) {
            scriptCounterF00 = 0;
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnBattleEffect(0x34E, x, y, facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(9);
        }
        if (animationStage == 8 && animationFrame == 0) {
            PlaySound(9);
        }
        break;
    }

    case 0x132: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) { remainingHits = 1; collisionResult = 0; }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 2 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x133: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0 || animationStage > 2) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x134: {
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
        }
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x135: {
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
        }
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1C);
        break;
    }

    case 0x136: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage < 5 && velocityX > FloatConstants::Zero) {
            velocityX = (velocityX) - FloatConstants::FourFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (animationStage > 4 && velocityX > FloatConstants::Zero) {
            velocityX = (velocityX) - FloatConstants::OneAndSevenTenths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = 12.5f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 25.0f;
            PlaySharedSound(0x1D);
        } else if (animationStage == 5 && animationFrame != 0) {
            // Continue the recovery animation.
        }
        break;
    }

    case 0x140: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        break;
    }

    case 0x141: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) - GeometryConstants::TwentyFive;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) - GeometryConstants::ThirtySix;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (field3AC > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) + GeometryConstants::TwentyFive;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) + GeometryConstants::ThirtySix;
        }
        break;
    }

    case 0x142: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::One;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            PlaySharedSound(0x1C);
            velocityX = 12.0f;
        }
        break;
    }

    case 0x143: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0 || animationStage > 2) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 8.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x144: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x145: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1C);
            velocityX = 30.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 10.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 10.0f;
        }
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 10.0f;
        }
        break;
    }

    case 0x146: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 11.0f;
        }
        if (animationStage == 0) {
            velocityX = (velocityX) - FloatConstants::Half;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 0) {
            velocityX = (velocityX) - FloatConstants::Half;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage > 1) {
            velocityX = (velocityX) - FloatConstants::Four;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 1 && animationFrame == 0) {
            PlaySharedSound(0x1D);
            velocityX = 20.0f;
        } else if (animationStage == 1 && animationFrame != 0) {
            // Continue the follow-through.
        }
        break;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 12.0f;
        }
        velocityX = (velocityX) - FloatConstants::SixtyFiveHundredths;
        if (velocityX < FloatConstants::Zero) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) - GeometryConstants::TwentyFive;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) - GeometryConstants::ThirtySix;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = (velocityX) + GeometryConstants::TwentyFive;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = (velocityX) + GeometryConstants::ThirtySix;
        }
        break;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 2 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 12.0f;
        }
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
        }
        velocityX = (velocityX) - FloatConstants::SixtyFiveHundredths;
        if (velocityX < FloatConstants::Zero) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySharedSound(0x1B);
        }
        break;
    }

    case 0x190: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(800,
                static_cast<float>(facing * 90) + x,
                (y) + GeometryConstants::NinetyFive, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(250);
        }
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33F, static_cast<float>(facing * 120) + x, (y) + FloatConstants::Zero, facing, 1);
            PlaySound(7);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        velocityY -= field05C;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 8.0f;
            field05C = 0.55f;
            SpawnBattleEffect(0x320, static_cast<float>(facing * 125) + x, (y) + GeometryConstants::HundredFifteen, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x195: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        velocityY = velocityY - field05C;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 8.0f;
            field05C = 0.55f;

            field314 = -30.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -40.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -50.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -60.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -70.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);

            PlaySound(0);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 6 && animationFrame == 0 && scriptCounterF00 < 2 &&
            static_cast<unsigned int>(inputC) > 0) {

            field314 = -30.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -40.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -50.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -60.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);
            field314 = -70.0f;
            field318 = 10.0f;
            SpawnBattleEffect(0x32B, float(facing * 67) + (x),
                (y) + GeometryConstants::SeventyFive, facing, 1);

            PlaySound(0);
            UpdateGaugeTimer(25);
            ++scriptCounterF00;
            ResetSecondaryCounter(4);
        }
        break;
    }

    case 0x196: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(36 - shot * 12);
                SpawnBattleEffect(shot + 0x32B, (x) + FloatConstants::Zero,
                    (y) + GeometryConstants::Hundred, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(15 - shot * 5);
                SpawnBattleEffect(shot + 0x32B, (x) + FloatConstants::Zero,
                    (y) + GeometryConstants::Hundred, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x323, static_cast<float>(facing * 134) + x, (y) + g_MeilingDoubleShotYAt00659F3C, facing, 1);
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x324, static_cast<float>(facing * 134) + x, (y) + g_MeilingDoubleShotYAt00659F3C, facing, 1);
            PlaySound(8);
        }
        break;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6)
            velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(36 - shot * 12);
                SpawnBattleEffect(shot + 0x32B, static_cast<float>(facing * 10) + x,
                    (y) + GeometryConstants::HundredThirty, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x19B: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6)
            velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(150);
            for (int shot = 0; shot < 7; ++shot) {
                field318 = 13.0f;
                field314 = static_cast<float>(15 - shot * 5);
                SpawnBattleEffect(shot + 0x32B, static_cast<float>(facing * 10) + x,
                    (y) + GeometryConstants::HundredThirty, facing, 1);
                PlaySound(5);
            }
        }
        break;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x339, static_cast<float>(facing * 100) + x, y, facing, 1);
            PlaySound(6);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage < 10 && animationStage > 1) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(10);
                ClearMotionFields();
                y = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 4.0f;
            velocityY = 8.0f;
            field05C = 0.4f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33B, static_cast<float>(facing * 50) + x, (y) + GeometryConstants::Forty, facing, 1);
            PlaySound(6);
            UpdateGaugeTimer(250);
        }
        if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(8);
        }
        break;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 4)
            velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x33A, static_cast<float>(facing * 100) + x, y, facing, 1);
            PlaySound(6);
            UpdateGaugeTimer(250);
        }
        break;
    }

    case 0x1A1: {
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            break;
        }
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0) {
            field314 = 30.0f;
            field318 = 8.0f;
            SpawnBattleEffect(0x32C, float(facing * 12) + (x),
                (y) + GeometryConstants::HundredTwenty, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        break;
    }

    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (animationStage == 12 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage > 7 && animationStage < 11 && RecordedRange(0, 100) < 80) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, static_cast<float>((RecordedRange(0, 75) + 90) * facing) + x,
                ((y) + GeometryConstants::EightyFive) + static_cast<float>(RecordedRange(0, 70)), facing, 1);
            SpawnBattleEffect(0x352, static_cast<float>(facing * 130) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (y > FloatConstants::Zero && animationStage < 11) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(11);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 16.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 54.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 11.0f;
            velocityY = 3.0f;
            field05C = 0.3f;
            SpawnBattleEffect(0x34F, static_cast<float>(facing * 110) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            PlaySound(0);
        }
        if (animationStage == 11 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        break;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (animationStage == 12 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage > 7 && animationStage < 11 && RecordedRange(0, 100) < 80) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, static_cast<float>((RecordedRange(0, 75) + 90) * facing) + x,
                ((y) + GeometryConstants::EightyFive) + static_cast<float>(RecordedRange(0, 70)), facing, 1);
            SpawnBattleEffect(0x352, static_cast<float>(facing * 130) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (y > FloatConstants::Zero && animationStage < 11) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(11);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 16.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 54.0f;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 13.0f;
            velocityY = 3.0f;
            field05C = 0.2f;
            SpawnBattleEffect(0x34F, static_cast<float>(facing * 110) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            PlaySound(0);
        }
        if (animationStage == 11 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        }
        break;
    }

    case 0x1FA: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x33C, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x33D, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x33E, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
            SetCameraShake(5.0f);
            PlaySound(2);
            UpdateGaugeTimer(200);
        }
        break;
    }

    case 0x1FB: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x33C, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x33D, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x33E, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
            SetCameraShake(5.0f);
            PlaySound(2);
            UpdateGaugeTimer(200);
        }
        break;
    }

    case 0x1FC: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (y > FloatConstants::Zero && animationStage < 12) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(12);
                break;
            }
        }
        if (animationStage > 2 && animationStage < 12 && RecordedRange(0, 100) < 60) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, ((x) + GeometryConstants::Hundred) - static_cast<float>(RecordedRange(0, 200)),
                ((y) + GeometryConstants::TwoHundred) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 3.0f;
            velocityY = 13.0f;
            field05C = 0.9f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x34D, x, y, facing, 1);
        }
        if (animationStage == 9 && animationFrame == 0) {
            PlaySound(1);
        }
        if (animationStage == 12 && animationFrame == 0) {
            ResetSecondaryCounter(11);
        }
        break;
    }

    case 0x1FD: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            velocityX = 0.0f;
        }
        if (y > FloatConstants::Zero && animationStage < 16) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(16);
                break;
            }
        }
        if (animationStage > 5 && animationStage < 16 && RecordedRange(0, 100) < 80) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, ((x) + GeometryConstants::Hundred) - static_cast<float>(RecordedRange(0, 200)),
                ((y) + GeometryConstants::TwoHundred) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 16.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 54.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 44.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 8.5f;
            velocityY = 15.0f;
            field05C = 0.95f;
        }
        if (animationStage == 11 && animationFrame == 0) {
            SpawnBattleEffect(0x34D, x, y, facing, 1);
        }
        if (animationStage == 12 && animationFrame == 0) {
            PlaySound(1);
        }
        if (animationStage == 16 && animationFrame == 0) {
            ResetSecondaryCounter(15);
        }
        break;
    }

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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySharedSound(0x21);
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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySharedSound(0x21);
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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnAuxEffect(0x37, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySharedSound(0x21);
            opponent->fieldEFA = 0;
        }
        return;
    }

    case 0x258: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            SpawnBattleEffect(0x323, static_cast<float>(facing * 80) + x, (y) + GeometryConstants::HundredTen, facing, 1);
            UpdateGaugeTimer(0);
        }
        if (animationStage == 8 && animationFrame == 0) {
            field314 = 1.0f;
            if (scriptCounterF00 > 3)
                field314 = 2.0f;
            if (scriptCounterF00 > 6)
                field314 = 3.0f;
            if (scriptCounterF00 > 10)
                field314 = 5.0f;
            SpawnBattleEffect(0x324, static_cast<float>(facing * 120) + x, (y) + GeometryConstants::HundredTen, facing, 1);
        }
        break;
    }

    case 0x259: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 8 && animationFrame == 0) {
            field314 = 0.0f;
            field318 = (y) + GeometryConstants::NinetySix;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + GeometryConstants::NinetySix, facing, 1);
            field314 = 1.0f;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + GeometryConstants::NinetySix, facing, 1);
            field314 = 2.0f;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + GeometryConstants::NinetySix, facing, 1);
            field314 = 3.0f;
            SpawnBattleEffect(0x322, x + static_cast<float>(facing * 0x72),
                (y) + GeometryConstants::NinetySix, facing, 1);
            UpdateGaugeTimer(300);
            PlaySound(4);
        }
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetCameraShake(5.0f);
            SpawnBattleEffect(0x343, static_cast<float>(facing * 70) + x, y, facing, 0);
            SpawnAuxEffect(0x3, static_cast<float>(facing * 70) + x, y, facing, 1);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 100) + x, y, -facing, 1);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 40) + x, y, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(3);
        }
        break;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SetCameraShake(10.0f);
            SpawnBattleEffect(0x344, static_cast<float>(facing * 70) + x, y, facing, 0);
            SpawnAuxEffect(0x3, static_cast<float>(facing * 70) + x, y, facing, 1);
            SpawnAuxEffect(0x7F, static_cast<float>(facing * 100) + x, y, -facing, 1);
            SpawnAuxEffect(0x7F, static_cast<float>(facing * 40) + x, y, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(3);
        }
        break;
    }

    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 0;
            remainingHits = 99;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x326, x, (y) + GeometryConstants::Hundred, -facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x326, x, (y) + GeometryConstants::Hundred, -facing, 1);
        }
        if (animationStage > 10 && animationStage < 18) {
            velocityY = (velocityY) - FloatConstants::Half;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(18);
                ClearMotionFields();
                y = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationFrame == 0)
            collisionResult = 0;
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 18), (y) + GeometryConstants::Fifty, facing, 1);
            spellPower = (spellPower) - GeometryConstants::Hundred;
            UpdateGaugeTimer(500);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityY = 3.0f;
            PlaySound(10);
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        }
        if (animationStage == 18 && animationFrame == 0) {
            ResetSecondaryCounter(16);
        }
        break;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 0;
            remainingHits = 99;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, -facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x348, x, (y) + GeometryConstants::Hundred, -facing, 1);
        }
        if (animationStage > 6 && animationStage < 11 && RecordedRange(0, 100) < 75) {
            SpawnBattleEffect(RecordedRange(0, 7) + 0x332, ((x) + GeometryConstants::TwoHundred) - static_cast<float>(RecordedRange(0, 401)),
                ((y) + GeometryConstants::Hundred) - static_cast<float>(RecordedRange(0, 200)), facing, 1);
        }
        if (animationStage > 10 && animationStage < 18) {
            velocityY = (velocityY) - FloatConstants::Half;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(18);
                ClearMotionFields();
                y = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationFrame == 0)
            collisionResult = 0;
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 18), (y) + GeometryConstants::Fifty, facing, 1);
            spellPower = (spellPower) - GeometryConstants::Hundred;
            UpdateGaugeTimer(500);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityY = 2.5f;
            PlaySound(11);
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 14) {
            ++scriptCounterF00;
            ResetSecondaryCounter(7);
        }
        if (animationStage == 18 && animationFrame == 0) {
            ResetSecondaryCounter(16);
        }
        break;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1);
            spellPower = (spellPower) - GeometryConstants::Hundred;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x327, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1, 0, 1);
            PlaySound(12);
        }
        if (animationStage == 3 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x328, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1, 0, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x329, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1, 0, 1);
        }
        if (animationStage == 15 && animationFrame == 0) {
            PlaySound(13);
            UpdateGaugeTimer(500);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        break;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1);
            spellPower = (spellPower) - GeometryConstants::Hundred;
        }
        if (animationStage > 11 && animationStage < 27 && inputD <= 0) {
            ResetSecondaryCounter(27);
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 2 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x349, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1, 0, 1);
            PlaySound(14);
        }
        if (animationStage == 3 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x34A, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1, 0, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x34B, static_cast<float>(facing * 100) + x, (y) + GeometryConstants::HundredTen, facing, 1, 0, 1);
        }
        if (animationStage == 29 && animationFrame == 0) {
            PlaySound(15);
            UpdateGaugeTimer(500);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        break;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 20) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
            spellPower = (spellPower) - GeometryConstants::Hundred;
            remainingHits = 1;
            UpdateGaugeTimer(500);
            collisionResult = 0;
        }
        if (animationStage == 15 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
            if (collisionResult == 1) {
                SetCameraShake(10.0f);
                PlaySound(16);
                PlaySound(17);
                SpawnBattleEffect(0x345, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
                SpawnBattleEffect(0x346, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
                SpawnBattleEffect(0x347, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 0;
            remainingHits = 1;
            ClearMotionFields();
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX = (velocityX) - FloatConstants::ThreeQuarters;
        } else {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SetCameraShake(10.0f);
            PlaySound(16);
            PlaySound(17);
            SpawnBattleEffect(0x345, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x346, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x347, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
        }
        break;
    }

    case 0x2C2: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 20) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
            spellPower = (spellPower) - GeometryConstants::Hundred;
            remainingHits = 1;
            UpdateGaugeTimer(500);
            collisionResult = 0;
        }
        if (animationStage == 14 && collisionResult == 1) {
            PlaySound(18);
            ResetPrimaryCounters(0x2C3);
            SpawnBattleEffect(0x350, static_cast<float>(facing * 94) + x, (y) + GeometryConstants::Hundred, facing, 1);
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 13 && animationFrame == 0) {
            SpawnAuxEffect(0x81, static_cast<float>(facing * 100) + x, y, -facing, 1);
            SpawnAuxEffect(0x81, static_cast<float>(facing * 40) + x, y, facing, 1);
        }
        break;
    }

    case 0x2C3: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 0;
            remainingHits = 2;
            ClearMotionFields();
        }
        if (animationStage == 7 && collisionResult == 1) {
            PlaySound(19);
            SpawnBattleEffect(0x351, static_cast<float>(facing * 45) + x, (y) + GeometryConstants::HundredTwenty, facing, 1);
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX = (velocityX) - FloatConstants::ThreeQuarters;
        } else {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        if (animationStage == 16 && animationFrame == 0) {
            SetCameraShake(10.0f);
            collisionResult = 0;
            PlaySound(20);
            PlaySound(21);
            SpawnBattleEffect(0x345, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x346, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnBattleEffect(0x347, static_cast<float>(facing * 76) + x, (y) + GeometryConstants::HundredSixtyEight, facing, 1);
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            SpawnAuxEffect(0x81, x, y, -facing, 1);
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 12.0f;
        }
        break;
    }

    case 0x31B: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x,
                (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(4);
        }
        return;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (roundSpellVariants[roundsRemaining] == 4) {
                fieldF26 = 0;
                aiCardTimer = 0;
                field318 = 0.0f;
                SpawnBattleEffect(0x3A3, x, (y) + GeometryConstants::Hundred, 1, 1);
                if (g_OptionsModeAt006714D0 == 0) {

            for (int echoEasy = 0; echoEasy < 6; ++echoEasy) {
                field314 = float(echoEasy * 60);
                SpawnBattleEffect(0x397, x, (y) + GeometryConstants::Hundred, 1, 1);
            }
                }
                if (g_OptionsModeAt006714D0 == 1) {

            for (int echoNormal = 0; echoNormal < 6; ++echoNormal) {
                field314 = float(echoNormal * 60);
                SpawnBattleEffect(0x397, x, (y) + GeometryConstants::Hundred, 1, 1);
            }
                }
                if (g_OptionsModeAt006714D0 == 2) {

            for (int echoHard = 0; echoHard < 8; ++echoHard) {
                field314 = float(echoHard * 45);
                SpawnBattleEffect(0x397, x, (y) + GeometryConstants::Hundred, 1, 1);
            }
                }
                if (g_OptionsModeAt006714D0 == 3) {

            for (int echoLunatic = 0; echoLunatic < 8; ++echoLunatic) {
                field314 = float(echoLunatic * 45);
                SpawnBattleEffect(0x397, x, (y) + GeometryConstants::Hundred, 1, 1);
            }
                }
            }
        }
        if (animationStage == 20 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 24 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(22);
            field3CF = 1;
        }
        break;
    }

    default:
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;

    advanceFrame:
        AdvanceNestedFrame();
    }
}
