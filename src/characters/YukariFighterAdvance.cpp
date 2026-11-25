#include "battle/CombatMode.hpp"
#include "engine/MathFloatHelpers.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/YukariFighter.hpp"

extern float g_YukariOffsetAt00659A14;
extern float g_YukariOffsetAt00659CA4;
extern float g_YukariOffsetAt00659CAC;

void YukariFighter::Advance() {
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
        velocityX = 4.5f; goto advanceFrame;
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
            if (animationStage == 4) {
                velocityX = 0.0f;
                velocityY = 12.5f;
                field05C = 0.55f;
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
            if (animationStage == 4) {
                velocityX = 4.0f;
                velocityY = 12.5f;
                field05C = 0.55f;
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
        if (y > FloatConstants::Zero &&
            ((velocityY = velocityY - field05C), y + velocityY <= FloatConstants::Zero)) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = -4.0f;
                velocityY = 12.5f;
                field05C = 0.55f;
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

        if (animationStage == 1 && animationFrame == 0 && fieldF0C == 0) {
            fieldF0C = 1;
            SpawnBattleEffect(999, x, y,
                facing, 0);
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            break;
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
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
        break;
    }

    case 0x47: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 1 && animationFrame == 0 && fieldF0C == 0) {
            fieldF0C = 1;
            SpawnBattleEffect(999, x, y,
                facing, 0);
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            break;
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
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
        break;
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
        if (animationStage == 1 && animationFrame == 0) {
            if (fieldF0C == 0) {
                fieldF0C = 1;
                SpawnBattleEffect(999, x, y, facing, 0);
            }
        }
        velocityY = velocityY - field05C;
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
            ResetSecondaryCounter(5);
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
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(animationStage - 1);
        if (animationStage == 1 && animationFrame == 0) {
            if (fieldF0C == 0) {
                fieldF0C = 1;
                SpawnBattleEffect(999, x, y,
                    facing, 0);
            }
            if (velocityY != FloatConstants::Zero) {
            if (velocityX == (FloatConstants::Zero)) {
                ResetSecondaryCounter(3);
                break;
            } else {
                ResetSecondaryCounter(2);
                break;
            }
            }
        }
        break;
    }

    case 0x4A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 1 && animationFrame == 0 && fieldF0C == 0) {
            fieldF0C = 1;
            SpawnBattleEffect(999, x, y,
                facing, 0);
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            break;
        }
        if (CheckHorizontalLimits() && (velocityX) <= GeometryConstants::NegativeFifteen) {
            if (fieldF0C == 0) {
                fieldF0C = 1;
                SpawnBattleEffect(999, x, y,
                    facing, 0);
            }
            ResetPrimaryCounters(0x4C);
            velocityX = -(velocityX) * FloatConstants::Quarter;
            velocityY = 15.0f;
            field05C = 0.5f;
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            break;
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

            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(5);
        break;
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f, 95.0f, 0.0f);
        }

        rotationZ = (rotationZ) + GeometryConstants::Thirty;
        velocityY = velocityY - field05C;
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
                SpawnBattleEffect(999, x, y, facing, 0);
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
            // Continue the impact animation.
        }
        break;
    }

    case 0x59: {
        if (animationStage == 3) {
            rotationZ = (rotationZ) + GeometryConstants::Forty;
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                scriptCounterF00 = (velocityX) * GeometryConstants::Hundred;
                scriptCounterF02 = (velocityY) * GeometryConstants::Hundred;
                ClearMotionFields(); y = 0.0f; ResetPrimaryCounters(0x61);
                rotationZ = 0.0f;
                SetCameraShake(2.0f); ClearTransformFlag(); PlaySharedSound(0x16);
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
        }
        break;
    }

    case 0x5D: {
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x3DD, x, y, facing, 0);
        }
        if (animationStage == 10 && animationFrame == 0) {
            SpawnBattleEffect(0x3DC, x, y, facing, 0);
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
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 90.0f;
        }
        if (animationStage == 10 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        return;
    }

    case 0x5E: {
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x3DD, x, y, facing, 0);
        }
        if (animationStage == 10 && animationFrame == 0) {
            SpawnBattleEffect(0x3DC, x, y, facing, 0);
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
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = -90.0f;
        }
        if (animationStage == 10 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        return;
    }

    case 0x5F: {
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x3DD, x, y, facing, 0);
        }
        if (animationStage == 10 && animationFrame == 0) {
            SpawnBattleEffect(0x3DC, x, y, facing, 0);
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
        return;
    }

    case 0x61: {
        if (facing * inputX > 0) {
            if (static_cast<unsigned int>(inputA) > 0 ||
                static_cast<unsigned int>(inputB) > 0 ||
                static_cast<unsigned int>(inputC) > 0 ||
                static_cast<unsigned int>(inputD) > 0) scriptCounterF00 = 1;
        }
        if (facing * inputX < 0) {
            if (static_cast<unsigned int>(inputA) > 0 ||
                static_cast<unsigned int>(inputB) > 0 ||
                static_cast<unsigned int>(inputC) > 0 ||
                static_cast<unsigned int>(inputD) > 0) scriptCounterF00 = 2;
        }
        if (animationStage == 0 && animationFrame == 0) {
            for (int shot = 0; shot < 10; ++shot)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if ((fieldEFA) > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage == 3 || animationStage == 4) {
            velocityY = velocityY - field05C;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f; ClearMotionFields(); ResetSecondaryCounter(5);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0)
                ResetPrimaryCounters(0x63);
        } else {
            if (animationStage == 2 && animationFrame == 0) {
                velocityX = float(int(scriptCounterF00)) * FloatConstants::OneTwoHundredth;
                velocityY = float(-int(scriptCounterF02)) * FloatConstants::OneTwoHundredth;
                field05C = 2.0f;
            }
            if (animationStage == 5 && animationFrame == 0)
                ResetSecondaryCounter(4);
            else if (animationStage == 5 && animationFrame != 0) {
            // Continue the launch animation.
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

    case 0x89: {
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        return;
    }

    case 0x8A: {
        if (field05C == FloatConstants::Zero)
            field05C = 0.6f;
        velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(0x8B);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        return;
    }

    case 0x8B: {
        if (animationStage == 0 && animationFrame == 0) {
            PlaySharedSound(0x1E);
        }
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0x89);
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
        if (animationStage == 1 && animationFrame == 0 && fieldF0C == 0) {
            fieldF0C = 1;
            SpawnBattleEffect(999, x, y,
                facing, 1);
        }
        if (animationStage == 2 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(3);
            break;
        }
        velocityY = velocityY - field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(7);
        break;
    }

    case 0x96: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

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
        break;
    }

    case 0x97: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

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
        break;
    }

    case 0x98: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

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
        break;
    }

    case 0x9A: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

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
        break;
    }

    case 0x9B: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

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
        break;
    }

    case 0x9C: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

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
        break;
    }

    case 0x9E: {
        pendingSpellCharge = (pendingSpellCharge) + FloatConstants::One;
        if ((pendingSpellCharge) > GeometryConstants::Thousand)
            pendingSpellCharge = 1000.0f;
        if (animationStage == 0 && animationFrame == 0) {
            fieldF0A = 0;

            velocityX = -6.0f;
            velocityY = 8.0f;
            field05C = 0.75f;
        }

        if (y >= FloatConstants::Zero) {

            velocityY = velocityY - field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(0xA);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        break;
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
            ResetSecondaryCounter(5);
            break;
        }
        break;
    }

    case 0xC8: {
        field3AC = 1;
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { velocityX = 0.0f; scriptCounterF00 = 0; }
        if ((velocityX) > GeometryConstants::Eight) {
            velocityX = (velocityX) - FloatConstants::Half;
            if ((velocityX) < GeometryConstants::Nine) velocityX = 9.0f;
        }
        if (inputY < 0) {
            if (facing * inputX > 0) {
                ResetPrimaryCounters(0xCD);
                break;
            }
            ResetPrimaryCounters(0xCC);
            break;
        }
        if (scriptCounterF00 > 0 && facing * inputX <= 0) {
            ResetPrimaryCounters(0xCF);
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (facing * inputX > 0 && scriptCounterF00 < 3) {
                ResetSecondaryCounter(4);
                ++scriptCounterF00;
                break;
            }
            ResetPrimaryCounters(0xCF);
            break;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 11.0f;
            SpawnAuxEffect(0x7D, float(facing * 80) + (x),
                (y) + GeometryConstants::Eighty, facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::Eighty,
                facing, 1);
            PlaySharedSound(31);
        }
        break;
    }

    case 0xC9: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
        }
        if (y > FloatConstants::Zero && animationStage > 1 && animationStage < 4) {
            velocityY -= field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(4);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 5.0f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D, x,
                (y) + GeometryConstants::Eighty, -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::Eighty, -facing, 1);
            PlaySharedSound(0x1F);
        }
        if (animationStage == 4 && animationFrame == 0) {
            ResetSecondaryCounter(animationStage - 2);
        }
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 9.0f; velocityY = 5.0f; field05C = 0.45f;
            SpawnAuxEffect(0x7D, float(facing * 80) + (x),
                (y) + GeometryConstants::HundredTen, facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::HundredTen,
                facing, 1);
            PlaySharedSound(31);
        }
        if (y > FloatConstants::Zero && animationStage > 1) {
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; y = 0.0f; animationFrame = 0;
                ResetPrimaryCounters(10);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        break;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) { scriptCounterF00 = 0; velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; }
        if (y > FloatConstants::Zero && animationStage > 0) {
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f; velocityY = 0.0f; field05C = 0.0f; y = 0.0f; animationFrame = 0;
                ResetPrimaryCounters(10);
                break;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -9.0f; velocityY = 5.0f; field05C = 0.45f;
            SpawnAuxEffect(0x7D, x, (y) + GeometryConstants::HundredTwenty,
                -facing, 1);
            SpawnAuxEffect(0x7E, x, (y) + GeometryConstants::HundredTwenty,
                -facing, 1);
            PlaySharedSound(31);
        }
        break;
    }

    case 0xCC: {
        if ((y == (FloatConstants::Zero)) || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY = velocityY - field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 0.0f;
                velocityY = 20.0f;
                field05C = 0.65f;
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
            velocityY = velocityY - field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                break;
            }
        }

        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);

        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 9.0f;
                velocityY = 15.0f;
                field05C = 0.65f;
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
            velocityY = velocityY - field05C;
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
            if (animationStage == 4) {
                velocityX = -9.0f;
                velocityY = 15.0f;
                field05C = 0.65f;
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
            return;
        }
        spirit = static_cast<short>(spirit - 3);
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            Fighter::PlaySharedSound(0x2C);
            SpawnBattleEffect(0x3DD, x,
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

            SpawnBattleEffect(0x3DD, x,
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
        if (animationStage == 2 && animationFrame == 0)
            PlaySharedSound(0x1B);
        break;
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
            SpawnBattleEffect(0x338, x, y, facing, 1);
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1C);
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
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x34C, x, y, facing, 1);
        }
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1D);
        }
        return;
    }

    case 0x130: {
        velocityY = velocityY - field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1C);
        return;
    }

    case 0x131: {
        velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
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
            SpawnBattleEffect(0x33A, x, (y) + GeometryConstants::Sixty, facing, 1);
        }
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1D);
        }
        return;
    }

    case 0x133: {
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            PlaySound(0x16);
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
        if (animationStage == 4 && animationFrame == 0)
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
            return;
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x349, static_cast<float>(facing * 155) + x, y, facing, 0);
            SpawnBattleEffect(0x34A, static_cast<float>(facing * 155) + x, y, facing, 0);
            SpawnBattleEffect(0x34B, static_cast<float>(facing * 155) + x, y, facing, 0);
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
        if (animationStage > 2 && velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::One;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            SpawnBattleEffect(0x346, x - static_cast<float>(facing * 35),
                (y) + g_YukariOffsetAt00659A14, facing, 1);
            SpawnBattleEffect(0x347, x - static_cast<float>(facing * 35),
                (y) + g_YukariOffsetAt00659A14, facing, 1);
            SpawnBattleEffect(0x348, x - static_cast<float>(facing * 35),
                (y) + g_YukariOffsetAt00659A14, facing, 1);
        }
        return;
    }

    case 0x137: {
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
        return;
    }

    case 0x140: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8) {
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
            if (y + velocityY <= FloatConstants::Zero) {
                field3AD = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 7.0f;
            velocityY = -7.0f;
            PlaySound(1);
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
        }
        if (animationStage == 9 && animationFrame == 0) {
            ResetSecondaryCounter(8);
            return;
        }
        break;
    }

    case 0x141: {
        velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
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
            SpawnBattleEffect(0x339, x, y, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySharedSound(0x1D);
        }
        return;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        return;
    }

    case 0x187: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX = (velocityX) - FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            SpawnBattleEffect(0x338, x, y, facing, 1);
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1C);
        return;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 15.0f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1D);
        return;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
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
        if (animationStage == 2 && animationFrame == 0)
            PlaySharedSound(0x1D);
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
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(0);
            field314 = 0.0f;
            field318 = 0.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 180) + x,
                (y) + GeometryConstants::EightyFive, facing, 1);
            field314 = 90.0f;
            field318 = 4.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 180) + x,
                (y) + GeometryConstants::EightyFive, facing, 1);
            field314 = -90.0f;
            field318 = 4.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 180) + x,
                (y) + GeometryConstants::EightyFive, facing, 1);
            field314 = 90.0f;
            field318 = 8.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 180) + x,
                (y) + GeometryConstants::EightyFive, facing, 1);
            field314 = -90.0f;
            field318 = 8.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 180) + x,
                (y) + GeometryConstants::EightyFive, facing, 1);
            PlaySound(0);
            UpdateGaugeTimer(200);
        }
        return;
    }

    case 0x191: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(0);
            field314 = 60.0f;
            field318 = 4.0f;
            field31C = -30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 135) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            field314 = 60.0f;
            field318 = 8.0f;
            field31C = -30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 135) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            field314 = 0.0f;
            field318 = 0.0f;
            field31C = -30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 135) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            field314 = -120.0f;
            field318 = 4.0f;
            field31C = -30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 135) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            field314 = -120.0f;
            field318 = 8.0f;
            field31C = -30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 135) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            UpdateGaugeTimer(200);
        }
        return;
    }

    case 0x192: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(0);
            field314 = 0.0f;
            field318 = 10.0f;
            field31C = -90.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + g_YukariOffsetAt00659CAC, facing, 1);
            field314 = 0.0f;
            field318 = 15.0f;
            field31C = -90.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + g_YukariOffsetAt00659CAC, facing, 1);
            field314 = 0.0f;
            field318 = 20.0f;
            field31C = -90.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + g_YukariOffsetAt00659CAC, facing, 1);
            field314 = 0.0f;
            field318 = 25.0f;
            field31C = -90.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + g_YukariOffsetAt00659CAC, facing, 1);
            field314 = 0.0f;
            field318 = 30.0f;
            field31C = -90.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + g_YukariOffsetAt00659CAC, facing, 1);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
        }
        velocityY -= field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            y = 0.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            if (animationStage > 7) {
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(0);
            velocityX = -3.0f;
            velocityY = 8.0f;
            field05C = 0.55f;
            field314 = -90.0f;
            field318 = 4.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -90.0f;
            field318 = 8.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 0.0f;
            field318 = 0.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 90.0f;
            field318 = 4.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 90.0f;
            field318 = 8.0f;
            field31C = 0.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x195: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
        }
        velocityY -= field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            y = 0.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            if (animationStage > 7) {
                ClearMotionFields();
                y = 0.0f;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(0);
            velocityX = -3.0f;
            velocityY = 8.0f;
            field05C = 0.55f;
            field314 = -60.0f;
            field318 = 4.0f;
            field31C = 30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = -60.0f;
            field318 = 8.0f;
            field31C = 30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 0.0f;
            field318 = 0.0f;
            field31C = 30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 120.0f;
            field318 = 4.0f;
            field31C = 30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 120.0f;
            field318 = 8.0f;
            field31C = 30.0f;
            SpawnBattleEffect(0x326, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x196: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (animationStage == 3 && animationFrame == 0) {
            PlaySound(0x15);
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            if (fieldF04 == 0)
                UpdateGaugeTimer(100);
            else
                UpdateGaugeTimer(25);
            for (int shot = 0; shot < 5; ++shot) {
                field314 = static_cast<float>(20 - shot * 10);
                field318 = 10.0f;
                SetPolarVelocity(field314, 40.0f);
                SpawnBattleEffect(800, (GeometryConstants::EightySix + velocityX) * facing + x,
                    ((y) + GeometryConstants::HundredThirtyFive) - velocityY, facing, 1);
            }
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneHundredth;
            velocityY = static_cast<float>(scriptCounterF02) * FloatConstants::OneHundredth;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0 &&
                static_cast<unsigned int>(inputA) > 0 && spirit > 0 && fieldF04 < 2) {
            ++fieldF04;
            ResetSecondaryCounter(3);
        }
        return;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(0x15);
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            if (fieldF04 == 0)
                UpdateGaugeTimer(100);
            else
                UpdateGaugeTimer(25);
            for (int shot = 0; shot < 5; ++shot) {
                field314 = static_cast<float>(20 - shot * 10);
                field318 = 10.0f;
                SetPolarVelocity(field314, 40.0f);
                SpawnBattleEffect(800, (g_EffectOffsetNinetyTwo + velocityX) * facing + x,
                    ((y) + GeometryConstants::Seventy) - velocityY, facing, 1);
            }
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneHundredth;
            velocityY = static_cast<float>(scriptCounterF02) * FloatConstants::OneHundredth;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 5 && animationFrame == 0 &&
                static_cast<unsigned int>(inputA) > 0 && spirit > 0 && fieldF04 < 2) {
            ++fieldF04;
            ResetSecondaryCounter(4);
        }
        return;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
        }
        if (velocityY + y <= FloatConstants::Zero) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
        }
        if (animationStage > 5 && y > FloatConstants::Zero)
            velocityY -= field05C;
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(0x15);
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            if (fieldF04 == 0)
                UpdateGaugeTimer(100);
            else
                UpdateGaugeTimer(25);
            for (int shot = 0; shot < 5; ++shot) {
                field314 = static_cast<float>(20 - shot * 10);
                field318 = 10.0f;
                SetPolarVelocity(field314, 40.0f);
                SpawnBattleEffect(800, (g_EffectOffsetNinetyTwo + velocityX) * facing + x,
                    ((y) + GeometryConstants::HundredFive) - velocityY, facing, 1);
            }
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneHundredth;
            velocityY = static_cast<float>(scriptCounterF02) * FloatConstants::OneHundredth;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0 &&
                static_cast<unsigned int>(inputA) > 0 && spirit > 0 && fieldF04 < 2) {
            ++fieldF04;
            ResetSecondaryCounter(4);
        }
        return;
    }

    case 0x19B: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33F, x - static_cast<float>(facing * 640),
                (y) + GeometryConstants::EightyFive, facing, 1);
            SpawnBattleEffect(0x33F, x - static_cast<float>(facing * 640),
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            SpawnBattleEffect(0x33F, x - static_cast<float>(facing * 640),
                (y) + GeometryConstants::FortyFive, facing, 1);
            PlaySound(0x17);
            UpdateGaugeTimer(250);
        }
        return;
    }

    case 0x19D: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            SpawnBattleEffect(0x340, (opponent->x) + GeometryConstants::Forty,
                y - GeometryConstants::SixHundredForty, facing, 1);
            SpawnBattleEffect(0x340, opponent->x, y - GeometryConstants::SixHundredForty, facing, 1);
            SpawnBattleEffect(0x340, opponent->x - GeometryConstants::Forty,
                y - GeometryConstants::SixHundredForty, facing, 1);
            PlaySound(0x17);
            UpdateGaugeTimer(250);
        }
        return;
    }

    case 0x19F: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
        }
        if (velocityY + y <= FloatConstants::Zero) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            y = 0.0f;
        }
        if (animationStage > 5 && y > FloatConstants::Zero) {
            // Continue the airborne animation.
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x33F, x - static_cast<float>(facing * 640),
                (y) + GeometryConstants::EightyFive, facing, 1);
            SpawnBattleEffect(0x33F, x - static_cast<float>(facing * 640),
                (y) + GeometryConstants::FortyFive, facing, 1);
            SpawnBattleEffect(0x33F, x - static_cast<float>(facing * 640),
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            PlaySound(0x17);
            UpdateGaugeTimer(250);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x1F4: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 3;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8)
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
        if (velocityX > FloatConstants::Zero && animationStage > 8) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 10.0f;
            PlaySound(1);
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
            SpawnBattleEffect(0x33B, static_cast<float>(facing * 8) + x,
                (y) + GeometryConstants::HundredThirtyFive, 1, 1);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 4) {
                ++scriptCounterF00;
                collisionResult = 0;
                ResetSecondaryCounter(8);
                return;
            }
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x1F5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 3;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8)
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
        if (y > FloatConstants::Zero && animationStage > 7) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(16);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityY = 12.0f;
            field05C = 0.5f;
            SpawnBattleEffect(0x33B, static_cast<float>(facing * 8) + x,
                (y) + GeometryConstants::HundredThirtyFive, 1, 1);
            PlaySound(1);
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 2) {
                ++scriptCounterF00;
                collisionResult = 0;
                ResetSecondaryCounter(8);
                return;
            }
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (animationStage == 16 && animationFrame == 0) {
            ResetSecondaryCounter(14);
        }
        return;
    }

    case 0x1F7: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
            SpawnBattleEffect(0x33C, x, y, facing, 0);
        }
        if (animationStage == 6) {
            scaleX -= FloatConstants::OneTenth;
            if (scaleX < FloatConstants::Zero)
                scaleX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33D, x, y, facing, 0);
            PlaySound(0x13);
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x14);
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            velocityX = 36.0f;
        }
        return;
    }

    case 0x1F8: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
            SpawnBattleEffect(0x33C, x, y, facing, 0);
        }
        if (animationStage == 6) {
            scaleX -= FloatConstants::OneTenth;
            if (scaleX < FloatConstants::Zero)
                scaleX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33D, x, y, facing, 0);
            PlaySound(0x13);
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x14);
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            velocityX = -36.0f;
        }
        return;
    }

    case 0x1F9: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            SpawnBattleEffect(0x33C, x, y, facing, 0);
        }
        if (animationStage == 6) {
            scaleX -= FloatConstants::OneTenth;
            if (scaleX < FloatConstants::Zero)
                scaleX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
            field3AD = 2;
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33D, x, y, facing, 0);
            PlaySound(0x13);
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x14);
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            velocityX = 36.0f;
            velocityY = 20.0f;
            field05C = 0.6f;
        }
        return;
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
        if (animationStage == 5 && animationFrame == 0) {
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
        if (animationStage == 5 && animationFrame == 0) {
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
        if (animationStage == 5 && animationFrame == 0) {
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
            SpawnBattleEffect(0x328, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
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
            SpawnBattleEffect(0x329, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
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
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 160) + x,
                (y) + GeometryConstants::ThreeHundredEighty, facing, 1);
            PlaySound(4);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 320) + x,
                (y) + GeometryConstants::ThreeHundredEighty, facing, 1);
            PlaySound(4);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 3 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x32A, static_cast<float>(facing * 480) + x,
                (y) + GeometryConstants::ThreeHundredEighty, facing, 1);
            PlaySound(4);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25D: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x328, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25E: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x329, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25F: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x328, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x260: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x329, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x261: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 7 && animationFrame == 0) {
            SpawnBattleEffect(0x341, static_cast<float>(facing * 54) + x,
                (y) + g_YukariOffsetAt00659CA4, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x262: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x342, opponent->x,
                (opponent->y) + GeometryConstants::ThreeHundred, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x263: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x344, opponent->x, 0.0f, facing, 1);
            UpdateGaugeTimer(200);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x2BC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - static_cast<float>(facing * 18),
                (y) + g_EffectOffsetNinetyTwo, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(6);
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x324, static_cast<float>(facing * 126) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
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
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 32) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            Fighter::SpawnTrackedEffect(0x32D, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 0, 0, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x2BE: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, static_cast<float>(facing * 65) + x,
                (y) + GeometryConstants::HundredFive, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x333, static_cast<float>(facing * 100) + x, y, facing, 0);
            PlaySound(11);
        }
        return;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - static_cast<float>(facing * 18),
                (y) + g_EffectOffsetNinetyTwo, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(14);
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x330, static_cast<float>(facing * 126) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
            SpawnBattleEffect(0x331, static_cast<float>(facing * 127) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
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
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 32) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            Fighter::SpawnTrackedEffect(0x32E, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 0, 0, 1);
            PlaySound(7);
        }
        return;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 32) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            Fighter::SpawnTrackedEffect(0x32F, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 0, 0, 1);
            PlaySound(12);
        }
        return;
    }

    case 0x2C2: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(40);
            PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, static_cast<float>(facing * 65) + x,
                (y) + GeometryConstants::HundredFive, facing, 1);
            spellPower -= GeometryConstants::Hundred;
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x337, static_cast<float>(facing * 100) + x, y, facing, 0);
            SpawnBattleEffect(0x337, static_cast<float>(facing * 100) + x, y, -facing, 0);
            PlaySound(11);
        }
        return;
    }

    case 0x2DB: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }

        if (animationStage == 8 || animationStage == 9)
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
        if (animationStage == 8) {
            velocityX -= FloatConstants::ThirtyFiveHundredths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (y > FloatConstants::Zero && animationStage > 8 && animationStage < 16) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(16);
                ClearMotionFields();
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        } else if (animationStage < animationStageCount) {
            // Continue the current animation.
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
            if (g_OptionsModeAt006714D0 < 2) {
                SpawnBattleEffect(0x38F, static_cast<float>(facing * 8) + x,
                    (y) + GeometryConstants::HundredThirtyFive, 1, 1);
            }
            if (g_OptionsModeAt006714D0 == 2) {
                SpawnBattleEffect(0x39C, static_cast<float>(facing * 8) + x,
                    (y) + GeometryConstants::HundredThirtyFive, 1, 1);
            }
            if (g_OptionsModeAt006714D0 == 3) {
                SpawnBattleEffect(0x39D, static_cast<float>(facing * 8) + x,
                    (y) + GeometryConstants::HundredThirtyFive, 1, 1);
            }
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 == 6) {
                PlaySound(1);
                velocityX = 25.0f;
                remainingHits = 1;
                collisionResult = 0;
            }
            if (scriptCounterF00 < 10) {
                ++scriptCounterF00;
                ResetSecondaryCounter(8);
                return;
            }
            if (scriptCounterF02 > 0) {
                PlaySound(1);
                velocityX = 18.0f;
                --scriptCounterF02;
                scriptCounterF00 = 0;
                remainingHits = 1;
                collisionResult = 0;
                ResetSecondaryCounter(8);
                if (x > opponent->x)
                    facing = -1;
                else
                    facing = 1;
                return;
            }
            if (scriptCounterF02 == 0) {
                velocityX = static_cast<float>(RecordedRange(0, 5) + 10);
                if (RecordedRange(0, 100) < 50)
                    velocityX = -velocityY;
                velocityY = 11.0f;
                field05C = 0.15f;
                scriptCounterF00 = 0;
                if (x > opponent->x)
                    facing = -1;
                else
                    facing = 1;
                return;
            }
        }
        if (animationStage == 10 && animationFrame == 0) {
            if (scriptCounterF00 < 4) {
                ++scriptCounterF00;
                collisionResult = 0;
                ++remainingHits;
                ResetSecondaryCounter(9);
                return;
            }
            ResetTransform(0.0f, 0.0f, 0.0f);
            if (g_OptionsModeAt006714D0 > 0)
                ResetPrimaryCounters(0x2DC);
            return;
        }
        if (animationStage == 14 && animationFrame == 0) {
            ResetSecondaryCounter(12);
        } else if (animationStage == 14 && animationFrame != 0) {
            // Continue the recovery animation.
        }
        return;
    }

    case 0x2DC: {
        if (y > FloatConstants::Zero && animationStage < 14) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(14);
                ClearMotionFields();
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            PlaySound(0x11);
        }
        if (animationStage == 14 && animationFrame == 0) {
            ResetSecondaryCounter(12);
        }
        return;
    }

    case 0x2DD: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 5;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8)
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
        if (velocityX > FloatConstants::Zero && animationStage > 8) {
            velocityX -= FloatConstants::Half;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 8.0f;
            PlaySound(1);
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
            SpawnBattleEffect(0x390, static_cast<float>(facing * 8) + x,
                (y) + GeometryConstants::HundredThirtyFive, 1, 1);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 6) {
                ++scriptCounterF00;
                collisionResult = 0;
                ResetSecondaryCounter(8);
                return;
            }
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x2DE: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 3;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (animationStage == 8) {
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
            if (fieldF04 > 4 && scriptCounterF02 < 20) {
                PlaySound(0x12);
                for (int shot = 0; shot < 4; ++shot) {
                    field314 = static_cast<float>(scriptCounterF02 * 8 + shot * 90);
                    field318 = 6.0f;
                    SetPolarVelocity(field314, 160.0f);
                    SpawnBattleEffect(0x386, (GeometryConstants::Eight + velocityX) * facing + x,
                        ((y) + GeometryConstants::HundredThirtyFive) - velocityY, facing, 1);
                }
                fieldF04 = 0;
                ++scriptCounterF02;
            }
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        ++fieldF04;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
            SpawnBattleEffect(0x390, static_cast<float>(facing * 8) + x,
                (y) + GeometryConstants::HundredThirtyFive, 1, 1);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 15) {
                ++scriptCounterF00;
                collisionResult = 0;
                ResetSecondaryCounter(8);
                return;
            }
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        return;
    }

    case 0x2E5: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (y > FloatConstants::Zero && animationStage > 3 && animationStage != 10 && animationStage != 11) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(14);
                return;
            }
        }
        if (animationStage == 10 || animationStage == 11) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 60 && fieldF04 < 30) {
                SpawnBattleEffect(0x38C, x, (y) + GeometryConstants::Hundred, facing, 1);
                scriptCounterF02 = 15;
                ++fieldF04;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(120 - g_OptionsModeAt006714D0 * 20);
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 11.0f;
            field05C = 0.5f;
        }
        if (animationStage == 10 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            PlaySound(16);
            SpawnBattleEffect(0x389, x, (y) + GeometryConstants::Hundred, facing, 1);
            SpawnBattleEffect(0x38A, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 0.0f;
            SpawnBattleEffect(0x38D, x, (y) + GeometryConstants::Hundred, facing, 1);
            field314 = 45.0f;
            SpawnBattleEffect(0x38D, x, (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (animationStage == 12 && animationFrame == 0) {
            if (scriptCounterF00 < 60) {
                ++scriptCounterF00;
                collisionResult = 0;
                ResetSecondaryCounter(10);
                return;
            }
            field05C = 0.15f;
        }
        if (animationStage == 14 && animationFrame == 0) {
            ResetSecondaryCounter(12);
        }
        return;
    }

    case 0x2EF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(900, static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::HundredTwenty, facing, 0);
            if (g_OptionsModeAt006714D0 > 1)
                SpawnBattleEffect(0x388, static_cast<float>(facing * 100) + x,
                    (y) + GeometryConstants::HundredTwenty, facing, 0);
            PlaySound(7);
        }
        return;
    }

    case 0x2F0: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 3;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (animationStage == 8)
            rotationZ = (rotationZ) + GeometryConstants::FortyFive;
        if (y > FloatConstants::Zero && animationStage > 7) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(16);
                ResetTransform(0.0f, 0.0f, 0.0f);
                return;
            }
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(8.0f, 135.0f, 0.0f);
            PlaySound(0x12);
            if (fieldF04 > 8) {
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            if (fieldF04 > 10) {
                for (int shot = 0; shot < 4; ++shot) {
                    field314 = static_cast<float>(fieldF04 * 5 + shot * 90);
                    field318 = 6.0f;
                    SetPolarVelocity(field314, 160.0f);
                    SpawnBattleEffect(0x386, (GeometryConstants::Eight + velocityX) * facing + x,
                        ((y) + GeometryConstants::HundredThirtyFive) - velocityY, facing, 1);
                }
            }
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneHundredth;
            velocityY = static_cast<float>(scriptCounterF02) * FloatConstants::OneHundredth;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityY = 10.5f;
            field05C = 0.25f;
            velocityX = static_cast<float>(RecordedRange(0, 16) - 8);
            PlaySound(1);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (fieldF04 < 25) {
                ++fieldF04;
                collisionResult = 0;
                ResetSecondaryCounter(8);
                return;
            }
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (animationStage == 16 && animationFrame == 0) {
            ResetSecondaryCounter(14);
        }
        return;
    }

    case 0x2F1: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            collisionResult = 1;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (y > FloatConstants::Zero && animationStage > 3) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetPrimaryCounters(10);
                ResetTransform(0.0f, 0.0f, 0.0f);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(10);
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 8.5f;
            field05C = 0.2f;
            velocityX = static_cast<float>(RecordedRange(0, 20) - 10);
        }
        return;
    }

    case 0x2F8: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
            fieldF04 = static_cast<short>(RecordedRange(0, 5));
            fieldF06 = static_cast<short>(RecordedRange(0, 4));
            if (fieldF04 <= fieldF06)
                ++fieldF04;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(180 - g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(0xF);
            if (g_OptionsModeAt006714D0 == 0) {
                SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                    static_cast<float>(RecordedRange(0, 5) * 100 + 50), facing, 1);
            }
            if (g_OptionsModeAt006714D0 == 1) {
                SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                    static_cast<float>(RecordedRange(0, 5) * 100 + 50), facing, 1);
            }
            if (g_OptionsModeAt006714D0 == 2) {
                if (fieldF04 == 0 || fieldF06 == 0) {
                    SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                        50.0f, facing, 1);
                }
                if (fieldF04 == 1 || fieldF06 == 1) {
                    SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                        200.0f, facing, 1);
                }
                if (fieldF04 == 2 || fieldF06 == 2) {
                    SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                        350.0f, facing, 1);
                }
            }
            if (g_OptionsModeAt006714D0 == 3) {
                if (fieldF04 == 0 || fieldF06 == 0) {
                    SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                        50.0f, facing, 1);
                }
                if (fieldF04 == 1 || fieldF06 == 1) {
                    SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                        200.0f, facing, 1);
                }
                if (fieldF04 == 2 || fieldF06 == 2) {
                    SpawnBattleEffect(0x392, static_cast<float>((facing == -1) * 1280),
                        350.0f, facing, 1);
                }
            }
        }
        return;
    }

    case 0x302: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(300 - g_OptionsModeAt006714D0 * 40);
        }
        return;
    }

    case 0x303: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(300 - g_OptionsModeAt006714D0 * 40);
        }
        return;
    }

    case 0x304: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (animationStage == 8 && animationFrame == 0) {
            velocityX = 0.0f;
            SpawnBattleEffect(0x33C, x, y, facing, 0);
        }
        if (animationStage == 6) {
            scaleX -= FloatConstants::OneTenth;
            if (scaleX < FloatConstants::Zero)
                scaleX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x33D, x, y, facing, 0);
            PlaySound(0x13);
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            PlaySound(0x14);
        }
        if (animationStage == 8 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            velocityX = static_cast<float>(RecordedRange(0, 480) - 360);
            if (x < GeometryConstants::ThreeHundredTwenty) {
                if (facing == 1)
                    velocityX = static_cast<float>(RecordedRange(0, 240) + 240);
                else
                    velocityX = static_cast<float>(-360 - RecordedRange(0, 240));
            }
            if (x > GeometryConstants::NineHundredSixty) {
                if (facing == 1)
                    velocityX = static_cast<float>(-240 - RecordedRange(0, 240));
                else
                    velocityX = static_cast<float>(RecordedRange(0, 240) + 360);
            }
        }
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
        if (animationStage == 3 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x, y, facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        break;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x3DD, x, y, facing, 0);
        }
        if (animationStage == 9 && animationFrame == 0) {
            SpawnBattleEffect(0x3DC, x, y, facing, 0);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (roundSpellVariants[roundsRemaining] == 2) {
                ResetPrimaryCounters(0x2EF);
                return;
            }
            if (roundSpellVariants[roundsRemaining] == 3)
                SpawnBattleEffect(0x395, x, y, 1, 0);
            if (roundSpellVariants[roundsRemaining] == 4) {
                fieldF14 = 440;
                SpawnBattleEffect(0x398, opponent->x,
                    (opponent->y) + GeometryConstants::Hundred, 1, 1);
                if (g_OptionsModeAt006714D0 < 2) {
                    for (int shot = 0; shot < 4; ++shot) {
                        field314 = static_cast<float>(shot * 90);
                        SpawnBattleEffect(0x396, opponent->x,
                            (opponent->y) + GeometryConstants::Hundred, 1, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 == 2) {
                    for (int shot = 0; shot < 6; ++shot) {
                        field314 = static_cast<float>(shot * 60);
                        SpawnBattleEffect(0x396, opponent->x,
                            (opponent->y) + GeometryConstants::Hundred, 1, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 == 3) {
                    for (int shot = 0; shot < 8; ++shot) {
                        field314 = static_cast<float>(shot * 45);
                        SpawnBattleEffect(0x396, opponent->x,
                            (opponent->y) + GeometryConstants::Hundred, 1, 1);
                    }
                }
            }
            ResetPrimaryCounters(0);
            return;
        }
        if (animationStage == 24 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }

        if (animationStage == 28 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(26);
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
