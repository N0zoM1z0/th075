#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/yuyuko/YuyukoFighter.hpp"

extern float g_BarrageYAt00659298;
extern float g_RadialPatternYOffsetAt00659274;
extern float g_CardGaugeStepAt0065747C;


void YuyukoFighter::Advance() {
    if (hitstopFrames != 0 || opponent->opponentFreezeSnapshot != 0)
        return;

    switch (action) {
    case 0x0:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if ((velocityX) > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX = (velocityX) + FloatConstants::HalfDouble;
                if ((velocityX) > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        goto advanceFrame;

    case 0x1:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if ((velocityX) > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX = (velocityX) + FloatConstants::HalfDouble;
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
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if ((velocityX) > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX = (velocityX) + FloatConstants::HalfDouble;
                if ((velocityX) > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        goto advanceFrame;

    case 0x3:
        if (field3AC == 0) {
            ClearMotionFields();
        } else {
            if ((velocityX) > FloatConstants::Zero) {
                velocityX -= FloatConstants::Half;
                if (velocityX < FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
            if (velocityX < FloatConstants::Zero) {
                velocityX = (velocityX) + FloatConstants::HalfDouble;
                if ((velocityX) > FloatConstants::Zero) {
                    ClearMotionFields();
                    field3AC = 0;
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;

    case 0x4:
        velocityX = 4.0f;
        goto advanceFrame;

    case 0x5:
        velocityX = -4.0f;
        goto advanceFrame;

    case 0x6:
        if (animationStage == 0 && animationFrame == 0 &&
                (aiCommand == 3 || field3AC > 0)) {
            ResetPrimaryCounters(0xCC);
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
        if (animationStage == 2 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 0.0f;
                velocityY = 12.0f;
                field05C = 0.4f;
            }
            if (animationStage >= animationStageCount)
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
        if (y > FloatConstants::Zero &&
            ((velocityY = velocityY - field05C), y + velocityY <= FloatConstants::Zero)) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (animationStage == 2 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 4.0f;
                velocityY = 12.0f;
                field05C = 0.4f;
            }
            if (animationStage >= animationStageCount)
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
            if (animationStage == 2) {
                velocityX = -4.0f;
                velocityY = 12.0f;
                field05C = 0.4f;
            }
            if (animationStage >= animationStageCount)
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
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount) {
            if (inputY == 0) {
                ResetPrimaryCounters(0);
            } else {
                ResetPrimaryCounters(1);
            }
        }
        break;

    case 0x32: {
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
        break;
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
        break;
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
        break;
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
            break;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        break;
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
        break;
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
        break;
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
        break;
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
            break;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        break;
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
        break;
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
        break;
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
        break;
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
            break;
        }
        if (animationStage == 7 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        break;
    }

    case 0x46:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -hitReactionVelocityX;
            velocityY += hitReactionVelocityY;
            if (velocityY < GeometryConstants::Six)
                velocityY = 6.0f;
            field05C = 0.8f;
            if ((velocityY) > GeometryConstants::TwentyFive)
                velocityY = 25.0f;
            collisionResult = 0;
        }
        if (animationStage == 1 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
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
        break;

    case 0x47:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -hitReactionVelocityX;
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 1 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
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
        break;

    case 0x48:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -hitReactionVelocityX;
            velocityY = hitReactionVelocityY;
            field05C = 1.3f;
            collisionResult = 0;
        }
        if (animationStage == 1 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
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
        break;

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
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(animationStage-1);
        if (animationStage == 1 && animationFrame == 0 && velocityY != FloatConstants::Zero) {

            if (velocityX == (FloatConstants::Zero)) {
                ResetSecondaryCounter(3);
                break;
            } else {
                ResetSecondaryCounter(2);
                break;
            }
        }
        break;
    }

    case 0x4A:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -hitReactionVelocityX;
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 1 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(2);
            return;
        }
        if (CheckHorizontalLimits() && velocityX <= GeometryConstants::NegativeFifteen) {
            ResetPrimaryCounters(0x4C);
            velocityX = -velocityX * FloatConstants::Quarter;
            velocityY = 15.0f;
            field05C = 0.5f;
            SetCameraShake(2.0f);
            PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY -= field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            PlaySharedSound(0x16);
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
        break;

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f,95.0f,0.0f);
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
            break;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(0);
        break;
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

        }
        break;
    }

    case 0x59: {
        if (animationStage == 3) {
            rotationZ = (rotationZ) + GeometryConstants::Forty;
            velocityY = velocityY - field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
                scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
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

        }
        break;
    }

    case 0x5D:
        if (animationStage < 7 && y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
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
            velocityY = 8.0f;
            velocityX = 13.5f;
            field05C = 0.6f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 7 && animationFrame != 0) {
            // The landing animation continues.
        }
        break;

    case 0x5E:
        if (animationStage < 7 && y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(7);
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
            velocityY = 8.0f;
            velocityX = -11.5f;
            field05C = 0.5f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetSecondaryCounter(5);
        } else if (animationStage == 7 && animationFrame != 0) {
            // The landing animation continues.
        }
        break;

    case 0x5F:
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(3);
            if (inputY > 0)
                ResetPrimaryCounters(2);
        }
        if (animationStage == animationStageCount - 1) {
            if (x > opponent->x)
                facing = -1;
            if (x < opponent->x)
                facing = 1;
        }
        break;

    case 0x60:
        if (0 < facing * inputX &&
                (static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0 || static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0))
            scriptCounterF00 = 1;
        if (facing * inputX < 0 &&
                ((static_cast<unsigned int>(inputA) > 0 || static_cast<unsigned int>(inputB) > 0) || (static_cast<unsigned int>(inputC) > 0 || static_cast<unsigned int>(inputD) > 0)))
            scriptCounterF00 = 2;
        if (animationStage == 0 && animationFrame == 0) {
            for (int effectIndex60 = 0; effectIndex60 < 10; ++effectIndex60)
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
        } else if (animationStage == 2 && animationFrame == 0) {
            velocityX = scriptCounterF00 * FloatConstants::OneTwoHundredth;
            velocityY = -scriptCounterF02 * FloatConstants::OneTwoHundredth;
            field05C = 2.0f;
        }
        break;

    case 0x61:
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
        } else if (animationStage == 2 && animationFrame == 0) {
            velocityX = scriptCounterF00 * FloatConstants::OneTwoHundredth;
            velocityY = -scriptCounterF02 * FloatConstants::OneTwoHundredth;
            field05C = 2.0f;
        } else if (animationStage == 2 && animationFrame != 0) {
            // The launch velocity is applied only on the first frame.
        }
        break;

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
            if ((scriptCounterF00) == 1)
                ResetPrimaryCounters(0x5D);
            if ((scriptCounterF00) == 2)
                ResetPrimaryCounters(0x5E);
        }
        return;
    }

    case 0x63:
        if (g_CombatMode != CombatMode::Story || cpuControlled == 0) {
            if (animationStage == 2 && roundsRemaining > 0 && opponent->action < 150) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        } else {
            if (animationStage > 1 && roundsRemaining > 0 && opponent->action < 150 &&
                    static_cast<signed char>(roundKind[roundsRemaining]) == 2) {
                ResetPrimaryCounters(0x31C);
                if (roundSpellVariants[roundsRemaining] == 4) {
                    ResetPrimaryCounters(0x302);
                }
                return;
            }
            if (animationStage > 0 && roundsRemaining > 0 && opponent->action < 150 &&
                    static_cast<signed char>(roundKind[roundsRemaining]) == 1) {
                ResetPrimaryCounters(0x31C);
                return;
            }
            if (animationStage > 1 && roundsRemaining > 0 && opponent->action < 150 &&
                    static_cast<signed char>(roundKind[roundsRemaining]) == 0) {
                ResetPrimaryCounters(0x5F);
                field3CF = 1;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetSecondaryCounter(2);
        break;

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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
        if (AdvanceNestedFrame()==animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
    }

    case 0x91:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            field05C = 0.5f;
            collisionResult = 0;
        }
        if (animationStage == 1 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(2);
            return;
        }
        velocityY -= field05C;
        if (velocityY + y <= FloatConstants::Zero) {
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            ClearMotionFields();
            y = 0.0f;
            ResetPrimaryCounters(0x61);
            SetCameraShake(2.0f);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(6);
        }
        break;

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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field05C = 0.75f;

        }

        if (y >= FloatConstants::Zero) {

            velocityY = velocityY-field05C;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            field490 = (velocityX)*FloatConstants::ThreeQuartersDouble;
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
            PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing)*30)+(x),

                (y) + GeometryConstants::Hundred,
                facing,1);
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        field490 = (-scriptCounterF00)*FloatConstants::OneTenth;
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
            PlaySharedSound(0x2C);
            scriptCounterF00 = 0xB4;
            SpawnAuxEffect(0x38,
                static_cast<float>(static_cast<int>(facing)*30)+(x),

                (y) + GeometryConstants::Hundred,
                facing,1);
        }
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = (velocityX)+FloatConstants::ThreeFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        field490 = (-scriptCounterF00)*FloatConstants::OneTenth;
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
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if (y > FloatConstants::Zero) {
            velocityY = velocityY-field05C;
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

    case 0xB5:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            velocityX = -8.0f;
            velocityY = 12.5f;
            field05C = 0.75f;
            rotationZ = 0.0f;
            ClearTransformFlag();
        }
        if ((y) > FloatConstants::Zero) {
            velocityY -= field05C;
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

    case 0xC8:
        field3AC = 1;
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            scriptCounterF00 = 0;
        }
        if ((velocityX) > FloatConstants::Five) {
            velocityX -= FloatConstants::Half;
            if (velocityX < GeometryConstants::Six)
                velocityX = 6.0f;
        }
        if (inputY < 0) {
            if (facing * inputX > 0) {
                ResetPrimaryCounters(0xCD);
                return;
            }
            ResetPrimaryCounters(0xCC);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (facing * inputX > 0 && scriptCounterF00 < 5) {
                ResetSecondaryCounter(2);
                ++scriptCounterF00;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = 15.0f;
        }
        break;

    case 0xC9:
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0)
            velocityX = 0.0f;
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 2.0f;
            field05C = 0.2f;
        }
        if ((y) > FloatConstants::Zero && animationStage > 0 && animationStage < 5) {
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
        if (animationStage == 5 && animationFrame == 0) {
            ResetSecondaryCounter(animationStage - 2);
        }
        break;

    case 0xCA:
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if ((y) > FloatConstants::Zero && animationStage > 1) {
            velocityY -= field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 7.5f;
            velocityY = 3.5f;
            field05C = 0.45f;
        }
        break;

    case 0xCB:
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if ((y) > FloatConstants::Zero && animationStage > 0) {
            velocityY -= field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetPrimaryCounters(10);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -7.5f;
            velocityY = 3.5f;
            field05C = 0.45f;
        }
        if (animationStage == 5 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(3);
        }
        break;

    case 0xCC:
        if (y == FloatConstants::Zero || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if ((y) > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
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
                velocityY = 18.5f;
                field05C = 0.55f;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;

    case 0xCD:
        if (y == FloatConstants::Zero || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if ((y) > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 2 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = 10.0f;
                velocityY = 13.5f;
                field05C = 0.5f;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;

    case 0xCE:
        if (y == FloatConstants::Zero || velocityY > FloatConstants::Zero) {
            SetCommandSelection(3, 4, 0xFF);
            grazeFrames = 2;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if ((y) > FloatConstants::Zero) {
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
                velocityX = -10.0f;
                velocityY = 13.5f;
                field05C = 0.5f;
                SpawnAuxEffect(0x3C, x, y, 1, 1);
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;

    case 0xCF: {
        field3AC = 1;
        velocityX = (velocityX)-FloatConstants::Half;
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame()==animationStageCount) {
            ResetPrimaryCounters(0);
            field3AC = 0;
        }
        return;
    }

    case 0xD0: {
        if (animationStage == 0 && animationFrame == 0) {
            facing =
                -facing;
            velocityX = -(velocityX);
        }
        if (field05C == (FloatConstants::Zero))
            field05C = 0.6f;
        velocityY = velocityY-field05C;
        if (y+velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(0xA);
            y = 0.0f;
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame()==animationStageCount)
            ResetSecondaryCounter(5);
        return;
    }

    case 0x12C:
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
        if (animationStage == 2 && animationFrame == 0)
            SpawnBattleEffect(0x34C, x, y, facing, 1);
        if (animationStage == 3 && animationFrame == 0) {
            PlaySharedSound(0x1C);
        }
        break;

    case 0x12D:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (animationStage > 3 && animationStage < 15) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(15);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 5.0f;
            velocityY = 10.0f;
            field05C = 0.8f;
            PlaySound(0x0C);
            SpawnBattleEffect(0x32F, x, (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(14);
        }
        break;

    case 0x12E:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 2;
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
        if (animationStage == 1 && animationFrame == 0)
            PlaySharedSound(0x1B);
        if (animationStage == 1 && animationFrame == 0) {
            SpawnBattleEffect(0x34D, x, y, facing, 1);
        }
        break;

    case 0x12F:
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
            PlaySharedSound(0x1D);
        if (animationStage == 2 && animationFrame == 0) {
            SpawnBattleEffect(0x34F, x, y, facing, 1);
        }
        break;

    case 0x130:
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
        if (animationStage == 2 && animationFrame == 0) {
            SpawnBattleEffect(0x327, static_cast<float>(static_cast<int>(facing) * 3) + x,
                (y) + GeometryConstants::HundredTen, facing, 1);
            PlaySound(0x0C);
        }
        break;

    case 0x131:
        velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            ResetPrimaryCounters(10);
            y = 0.0f;
            field05C = 0.0f;
            velocityY = 0.0f;
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 4;
            collisionResult = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationFrame == 0 && animationStage < 9)
            collisionResult = 0;
        if (animationStage == 4 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x34E, x, y, facing, 1);
        }
        break;

    case 0x133:
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            remainingHits = 1;
            collisionResult = 0;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 0.0f;
            PlaySound(0x0C);
            SpawnBattleEffect(0x32E, static_cast<float>(static_cast<int>(facing) * 0x14) + x, 125.0f, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 5 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 20.0f;
        }
        break;

    case 0x134:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0 && animationStage < 2) {
            velocityX -= FloatConstants::ThreeTenths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -15.0f;
        if (velocityX < FloatConstants::Zero && animationStage > 1) {
            velocityX = (velocityX) + FloatConstants::FourFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -50.0f;
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        break;

    case 0x135:
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
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x349, static_cast<float>(static_cast<int>(facing) * 0x14) + x,
                (y) + GeometryConstants::Forty, facing, 1);
            PlaySound(0x0C);
        }
        break;

    case 0x136:
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
        if (animationStage == 6 && animationFrame == 0)
            velocityX = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x335, static_cast<float>(static_cast<int>(facing) * 0x14) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(0x0C);
        }
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = 27.0f;
        }
        break;

    case 0x186:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 3;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationFrame == 0 && animationStage < 7)
            collisionResult = 0;
        if (animationStage == 4 && animationFrame == 0)
            SpawnBattleEffect(0x334, static_cast<float>(static_cast<int>(facing) * 0x92) + x,
                (y) + GeometryConstants::Eighty, facing, 1);
        break;

    case 0x187:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0 && y == FloatConstants::Zero) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage > 3 && animationStage < 15) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(15);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationFrame == 0 && animationStage < 10)
            collisionResult = 0;
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 10.0f;
            field05C = 0.8f;
            SpawnBattleEffect(0x32F, x, (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(0x0C);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(14);
        }
        break;

    case 0x188:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
        }
        if (animationStage > 0) {
            velocityX -= FloatConstants::ThreeFifths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x335, static_cast<float>(static_cast<int>(facing) * 0x14) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(0x0C);
        }
        break;

    case 0x189:
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            field05C = 0.0f;
            velocityY = 0.0f;
            velocityX = 10.0f;
        }
        if ((velocityX) > FloatConstants::Zero)
            velocityX -= FloatConstants::ThreeTenths;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if (animationStage == 3 && animationFrame == 0)
            PlaySharedSound(0x1D);
        if (animationStage == 2 && animationFrame == 0) {
            SpawnBattleEffect(0x34F, x, y, facing, 1);
        }
        break;

    case 0x18A: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 15.0f;
            scriptCounterF00 = 0;
        }
        velocityX = (velocityX)-FloatConstants::ThreeFifths;
        if ((velocityX) < FloatConstants::Zero) {
            velocityX = 0.0f;
            field3AC = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if ((animationStage) == 5 && (animationFrame) == 0) {
            SpawnBattleEffect(0x327,
                float(facing*151)+(x),
                (y)+GeometryConstants::HundredFour,
                facing,1);
        }
        break;
    }

    case 0x18B: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            remainingHits = 1;
            collisionResult = 0;
            velocityX = 10.0f;
            scriptCounterF00 = 0;
        }
        if ((animationStage) > 6) {
            velocityX = (velocityX)-FloatConstants::ThreeFifths;
            if ((velocityX) < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        if ((animationStage) == 7 && (animationFrame) == 0 && (scriptCounterF00) < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
            remainingHits = 1;
            collisionResult = 0;
        }
        if ((animationStage) == 6 && (animationFrame) == 0) {
            SpawnBattleEffect(0x328,
                float(facing*128)+(x),
                (y)+GeometryConstants::Seventy,
                facing,1);
        }
        break;
    }

    case 0x190:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage > 7 && scriptCounterF00 <= 0 && scriptCounterF02 < 3) {
            UpdateGaugeTimer(100);
            PlaySound(0);
            scriptCounterF00 = 15;
            ++scriptCounterF02;
            for (int burstIndex400 = 0; burstIndex400 < 5; ++burstIndex400) {
                field318 = 1.0f;
                field314 = static_cast<float>(40 - burstIndex400 * 20);
                SpawnBattleEffect(800, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                    (y) + GeometryConstants::HundredForty, facing, 1);
            }
        }
        break;

    case 0x191:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            PlaySound(0);
            for (int burstIndex191 = 0; burstIndex191 < 8; ++burstIndex191) {
                field318 = static_cast<float>(burstIndex191 * 2 + 2);
                SpawnBattleEffect(0x33E, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                    (y) + GeometryConstants::HundredForty, facing, 1);
            }
        }
        break;

    case 0x192:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 3 && animationStage < 15) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(15);
                return;
            }
        }
        if (animationStage > 3 && animationStage < 11) {
            --scriptCounterF02;
            if (scriptCounterF02 <= 0) {
                field318 = 1.0f;
                field314 = 0.0f;
                PlaySound(0);
                UpdateGaugeTimer(40);
                SpawnBattleEffect(800, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                    (y) + GeometryConstants::HundredTen, facing, 1);
                scriptCounterF02 = 4;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 10.0f;
            field05C = 0.3f;
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(5);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(14);
        }
        break;

    case 0x194:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::QuarterDouble;
            velocityY = (velocityY) * FloatConstants::QuarterDouble;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 16)
            velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage > 7 && scriptCounterF00 <= 0 && scriptCounterF02 < 3) {
            PlaySound(0);
            scriptCounterF00 = 15;
            ++scriptCounterF02;
            UpdateGaugeTimer(100);
            for (int burstIndex194 = 0; burstIndex194 < 5; ++burstIndex194) {
                field318 = 1.0f;
                field314 = static_cast<float>(40 - burstIndex194 * 20);
                SpawnBattleEffect(0x322, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                    (y) + GeometryConstants::HundredForty, facing, 1);
            }
        }
        break;

    case 0x196:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(10);
        if (animationStage > 5 && scriptCounterF00 <= 0 && scriptCounterF02 < 5) {
            field314 = static_cast<float>(10 - scriptCounterF02 * 10);
            field318 = 10.0f;
            SpawnBattleEffect(0x342, static_cast<float>(static_cast<int>(facing) * 0x69) + x,
                (y) + GeometryConstants::HundredFortyFive, facing, 1);
            UpdateGaugeTimer(30);
            scriptCounterF00 = 5;
            ++scriptCounterF02;
        }
        break;

    case 0x197:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(10);
        if (animationStage > 5 && scriptCounterF00 <= 0 && scriptCounterF02 < 5) {
            field314 = static_cast<float>(scriptCounterF02 * 10 + 10);
            field318 = 10.0f;
            SpawnBattleEffect(0x342, static_cast<float>(static_cast<int>(facing) * 0x41) + x,
                (y) + GeometryConstants::HundredSeventy, facing, 1);
            UpdateGaugeTimer(30);
            scriptCounterF00 = 5;
            ++scriptCounterF02;
        }
        break;

    case 0x198:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(10);
        if (animationStage > 5 && scriptCounterF00 <= 0 && scriptCounterF02 < 5) {
            field314 = static_cast<float>(scriptCounterF02 * 10 + 30);
            field318 = 10.0f;
            SpawnBattleEffect(0x342, static_cast<float>(static_cast<int>(facing) * 0x41) + x,
                (y) + GeometryConstants::HundredSeventy, facing, 1);
            UpdateGaugeTimer(30);
            scriptCounterF00 = 5;
            ++scriptCounterF02;
        }
        break;

    case 0x19A:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            fieldF06 = 0;
        }
        if (animationStage > 7) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(10);
            scriptCounterF00 = static_cast<short>((velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>((velocityY) * GeometryConstants::Hundred);
            UpdateGaugeTimer(150);
            for (int burstIndex19A = 0; burstIndex19A < 7; ++burstIndex19A) {
                field314 = static_cast<float>(30 - burstIndex19A * 10);
                field318 = 10.0f;
                SetPolarVelocity(field314, 80.0f);
                SpawnBattleEffect(0x342,
                    (FloatConstants::Five + velocityX) * facing + x,
                    ((y) + GeometryConstants::HundredFourteen) - velocityY, facing, 1);
            }
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneHundredth;
            velocityY = static_cast<float>(scriptCounterF02) * FloatConstants::OneHundredth;
        }
        break;

    case 0x19C:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        --scriptCounterF00;
        if (animationStage > 7 && scriptCounterF00 <= 0 && scriptCounterF02 < 5) {
            SpawnBattleEffect(0x347, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
            ++scriptCounterF02;
            scriptCounterF00 = 10;
            UpdateGaugeTimer(30);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            PlaySound(10);
        }
        break;

    case 0x19E:
        if (animationStage == 0 && animationFrame == 0) {
            if (field3AC == 0)
                ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
        }
        if (field3AC > 0 && animationStage < 2) {
            velocityX -= FloatConstants::ThreeTenths;
            if (velocityX < FloatConstants::Zero) {
                velocityX = 0.0f;
                field3AC = 0;
            }
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -15.0f;
        if (velocityX < FloatConstants::Zero && animationStage > 1) {
            velocityX = (velocityX) + FloatConstants::FourFifths;
            if ((velocityX) > FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            scriptCounterF00 = 0;
        }
        if (animationStage == 2 && animationFrame == 0)
            velocityX = -50.0f;
        if (animationStage == 3 && animationFrame == 0) {
            PlaySound(0);
            scriptCounterF00 = static_cast<short>(
                (velocityX) * GeometryConstants::Hundred);
            scriptCounterF02 = static_cast<short>(
                (velocityY) * GeometryConstants::Hundred);
            UpdateGaugeTimer(300);
            for (int burstIndex19E = 0; burstIndex19E < 5; ++burstIndex19E) {
                field314 = static_cast<float>(burstIndex19E * 15 + 10);
                field318 = 2.0f;
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x320,
                    (GeometryConstants::NegativeSixty + velocityX) *
                        static_cast<float>(facing) + x,
                    y - velocityY, facing, 1);

                field314 = static_cast<float>(burstIndex19E * 15 + 10);
                field318 = 6.0f;
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x321,
                    (GeometryConstants::NegativeSixty + velocityX) *
                        static_cast<float>(facing) + x,
                    y - velocityY, facing, 1);

                field314 = static_cast<float>(burstIndex19E * 15 + 10);
                field318 = 10.0f;
                SetPolarVelocity(field314, 200.0f);
                SpawnBattleEffect(0x322,
                    (GeometryConstants::NegativeSixty + velocityX) *
                        static_cast<float>(facing) + x,
                    y - velocityY, facing, 1);
            }
            velocityX = static_cast<float>(scriptCounterF00) *
                FloatConstants::OneHundredth;
            velocityY = static_cast<float>(scriptCounterF02) *
                FloatConstants::OneHundredth;
        }
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 0.0f;
        }
        break;

    case 0x1A0:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::QuarterDouble;
            velocityY = (velocityY) * FloatConstants::QuarterDouble;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage > 16)
            velocityY -= field05C;
        if (y + velocityY <= FloatConstants::Zero) {
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
        }
        --scriptCounterF00;
        if (animationStage > 7 && scriptCounterF00 <= 0 && scriptCounterF02 < 5) {
            SpawnBattleEffect(0x347, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                (y) + GeometryConstants::HundredForty, facing, 1);
            ++scriptCounterF02;
            scriptCounterF00 = 10;
            UpdateGaugeTimer(30);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 8 && animationFrame == 0) {
            PlaySound(10);
        }
        break;

    case 0x1F4:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            fieldF04 = 0;
        }
        if ((velocityX) > FloatConstants::Zero && animationStage > 5) {
            velocityX -= FloatConstants::FiftyFiveHundredths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (animationStage > 5 && animationStage < 10) {
            --fieldF04;
            if (fieldF04 <= 0) {
                fieldF04 = 3;
                SpawnBattleEffect(0x343, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                    (y) + g_BarrageYAt00659298, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            velocityX = 8.0f;
            PlaySound(0x0B);
        }
        if (animationStage == 6 && animationFrame == 0)
            PlaySound(0);
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 0) {
            ResetSecondaryCounter(6);
            ++scriptCounterF00;
        }
        break;

    case 0x1F5:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if ((velocityX) > FloatConstants::Zero && animationStage > 5) {
            velocityX -= FloatConstants::FortyFiveHundredths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (animationStage > 5 && animationStage < 10) {
            --fieldF04;
            if (fieldF04 <= 0) {
                fieldF04 = 3;
                SpawnBattleEffect(0x343, static_cast<float>(static_cast<int>(facing) * 0x32) + x,
                    (y) + g_BarrageYAt00659298, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 1 && animationFrame == 0) {
            SpawnAuxEffect(0x7F, x, y, facing, 1);
            velocityX = 12.0f;
            PlaySound(11);
        }
        if (animationStage == 4 && animationFrame == 0 && scriptCounterF02 < 2) {
            ++scriptCounterF02;
            ResetSecondaryCounter(2);
        }
        if (animationStage == 6 && animationFrame == 0)
            PlaySound(0);
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 1) {
            ResetSecondaryCounter(6);
            ++scriptCounterF00;
        }
        break;

    case 0x252: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            --bombCount;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if ((spiritCooldown) == 0 && collisionResult == 1) spirit=1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if ((animationStage) == 4 && (animationFrame) == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
            PlaySharedSound(0x21);
            opponent->fieldEFA=0;
        }
        break;
    }

    case 0x253: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            --bombCount;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if ((spiritCooldown) == 0 && collisionResult == 1) spirit=1000;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if ((animationStage) == 4 && (animationFrame) == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
            PlaySharedSound(0x21);
            opponent->fieldEFA=0;
        }
        break;
    }

    case 0x254: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            --bombCount;
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }

        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if ((animationStage) == 5 && (animationFrame) == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                (facing),1);
            PlaySharedSound(0x21);
            opponent->fieldEFA=0;
        }
        return;
    }

    case 0x255: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if ((animationStage) == 5 && (animationFrame) == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
        }
        if ((animationStage) == 8 && (animationFrame) == 0 && (scriptCounterF00) < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x256: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if ((animationStage) == 5 && (animationFrame) == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
        }

        break;
    }

    case 0x257: {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if ((animationStage) == 5 && (animationFrame) == 0) {
            SpawnAuxEffect(0x37,x,
                (y) + GeometryConstants::Hundred,
                facing,1);
        }
        if ((animationStage) == 8 && (animationFrame) == 0 && (scriptCounterF00) < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        break;
    }

    case 0x258:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(1);
            UpdateGaugeTimer(250);
            for (int burstIndex600 = 0; burstIndex600 < 5; ++burstIndex600) {
                field314 = static_cast<float>(burstIndex600 * 20);
                field318 = 5.0f;
                SpawnBattleEffect(0x32C, static_cast<float>(static_cast<int>(facing) * 0x2B) + x,
                    (y) + GeometryConstants::HundredSeventy, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;

    case 0x259:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            PlaySound(1);
            for (int burstIndex259 = 0; burstIndex259 < 5; ++burstIndex259) {
                field314 = static_cast<float>(burstIndex259 * 20 + 50);
                field318 = 5.0f;
                SpawnBattleEffect(0x330, static_cast<float>(static_cast<int>(facing) * 0x2B) + x,
                    (y) + GeometryConstants::HundredSeventy, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;

    case 0x25A:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(1);
            UpdateGaugeTimer(250);
            for (int burstIndex25A = 0; burstIndex25A < 5; ++burstIndex25A) {
                field314 = static_cast<float>(burstIndex25A * 20 + 110);
                field318 = 5.0f;
                SpawnBattleEffect(0x331, static_cast<float>(static_cast<int>(facing) * 0x2B) + x,
                    (y) + GeometryConstants::HundredSeventy, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;

    case 0x25F:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x336, static_cast<float>(static_cast<int>(facing) * 0x69) + x,
                (y) + GeometryConstants::HundredFortyFive, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;

    case 0x260:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x339, static_cast<float>(static_cast<int>(facing) * 0x69) + x,
                (y) + GeometryConstants::HundredFortyFive, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;

    case 0x261:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
        }
        if (animationStage > 15)
            velocityY -= field05C;
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            SpawnBattleEffect(0x336, static_cast<float>(static_cast<int>(facing) * 0x55) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        break;

    case 0x262:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneFifth;
            velocityY = (velocityY) * FloatConstants::OneFifth;
        }
        if (animationStage > 15)
            velocityY -= field05C;
        if (animationStage == 6 && animationFrame == 0) {
            UpdateGaugeTimer(250);
            SpawnBattleEffect(0x339, static_cast<float>(static_cast<int>(facing) * 0x55) + x,
                (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            PlaySound(2);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        break;

    case 0x263:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            remainingHits = 8;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            for (int radialIndex263 = 0; radialIndex263 < 6; ++radialIndex263) {
                field318 = static_cast<float>(static_cast<int>(facing) * 0x43) + x;
                field31C = (y) + g_RadialPatternYOffsetAt00659274;
                field314 = static_cast<float>(radialIndex263 * 60);
                SpawnBattleEffect(0x33F, static_cast<float>(static_cast<int>(facing) * 0x43) + x,
                    (y) + g_RadialPatternYOffsetAt00659274, facing, 1);
            }
            PlaySound(3);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 3) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            collisionResult = 1;
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        if (animationFrame == 0 && animationStage < 9) {
            collisionResult = 0;
        }
        break;

    case 0x264:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            remainingHits = 10;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            for (int radialIndex264 = 0; radialIndex264 < 8; ++radialIndex264) {
                field318 = static_cast<float>(static_cast<int>(facing) * 0x43) + x;
                field31C = (y) + g_RadialPatternYOffsetAt00659274;
                field314 = static_cast<float>(radialIndex264 * 45);
                SpawnBattleEffect(0x346, static_cast<float>(static_cast<int>(facing) * 0x43) + x,
                    (y) + g_RadialPatternYOffsetAt00659274, facing, 1);
            }
            PlaySound(3);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 5) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            collisionResult = 1;
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 4) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        if (animationFrame == 0 && animationStage < 9) {
            collisionResult = 0;
        }
        break;

    case 0x265:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            remainingHits = 10;
            remainingHits = 0;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(200);
            for (int radialIndex265 = 0; radialIndex265 < 8; ++radialIndex265) {
                field314 = static_cast<float>(radialIndex265 * 45);
                field318 = static_cast<float>(static_cast<int>(facing) * 0x43) + x;
                field31C = (y) + g_RadialPatternYOffsetAt00659274;
                SpawnBattleEffect(0x346, static_cast<float>(static_cast<int>(facing) * 0x43) + x,
                    (y) + g_RadialPatternYOffsetAt00659274, facing, 1);
            }
            PlaySound(3);
        }
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < 1) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            collisionResult = 1;
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 7) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        break;

    case 0x2BC:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x73, x, (y) + GeometryConstants::HundredTwentyFive,
                facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(4);
            for (int burstIndex700 = 0; burstIndex700 < 12; ++burstIndex700) {
                field314 = static_cast<float>(burstIndex700 * 30);
                field318 = 8.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);

                field314 = static_cast<float>(-burstIndex700 * 30);
                field318 = 8.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);

                field314 = static_cast<float>(burstIndex700 * 30);
                field318 = 7.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);

                field314 = static_cast<float>(-burstIndex700 * 30);
                field318 = 7.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF02 < 2) {
            ++scriptCounterF02;
            ResetSecondaryCounter(10);
        }
        break;

    case 0x2BD:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x73, x, (y) + GeometryConstants::HundredTwentyFive,
                facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            for (int burstIndex2BD = 0; burstIndex2BD < 12; ++burstIndex2BD) {
                field314 = static_cast<float>(burstIndex2BD * 30);
                field318 = 8.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-burstIndex2BD * 30);
                field318 = 8.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(burstIndex2BD * 30);
                field318 = 7.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-burstIndex2BD * 30);
                field318 = 7.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x323, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF02 < 2) {
            ++scriptCounterF02;
            ResetSecondaryCounter(10);
        }
        break;

    case 0x2BE:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x73, x, (y) + GeometryConstants::HundredForty, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(6);
            SpawnBattleEffect(0x326, x, y, facing, 1);
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 6) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        break;

    case 0x2BF:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x73, static_cast<float>(static_cast<int>(facing) * 0x2A) + x,
                (y) + GeometryConstants::HundredTwentyEight, facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0) {
            PlaySound(8);
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x328, static_cast<float>(static_cast<int>(facing) * 0x53) + x,
                (y) + GeometryConstants::HundredThirtySeven, facing, 1);
        }
        break;

    case 0x2C0:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x74, x, (y) + GeometryConstants::HundredTwentyFive,
                facing, 1);
        }
        if (animationStage == 4 && animationFrame == 0) {
            UpdateGaugeTimer(300);
            PlaySound(5);
            for (int burstIndex2C0 = 0; burstIndex2C0 < 12; ++burstIndex2C0) {
                field314 = static_cast<float>(burstIndex2C0 * 30);
                field318 = 9.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x340, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-burstIndex2C0 * 30);
                field318 = 9.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x340, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(burstIndex2C0 * 30);
                field318 = 8.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x340, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-burstIndex2C0 * 30);
                field318 = 8.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x340, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 7 && animationFrame == 0) {
            UpdateGaugeTimer(300);
            PlaySound(5);
            for (int burstIndex2C0B = 0; burstIndex2C0B < 12; ++burstIndex2C0B) {
                field314 = static_cast<float>(burstIndex2C0B * 30);
                field318 = 7.0f;
                field31C = 30.0f;
                SpawnBattleEffect(0x341, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-burstIndex2C0B * 30);
                field318 = 7.0f;
                field31C = -30.0f;
                SpawnBattleEffect(0x341, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(burstIndex2C0B * 30);
                field318 = 6.0f;
                field31C = 35.0f;
                SpawnBattleEffect(0x341, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-burstIndex2C0B * 30);
                field318 = 6.0f;
                field31C = -35.0f;
                SpawnBattleEffect(0x341, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF02 < 2) {
            ++scriptCounterF02;
            ResetSecondaryCounter(10);
        }
        break;

    case 0x2C2:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x74, x, (y) + GeometryConstants::HundredForty, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 8 && animationFrame == 0) {
            UpdateGaugeTimer(500);
            PlaySound(6);
            SpawnBattleEffect(0x344, opponent->x, y, facing, 1);
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 6) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        break;

    case 0x2C3:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x74, static_cast<float>(static_cast<int>(facing) * 0x2A) + x,
                (y) + GeometryConstants::HundredTwentyEight, facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0) {
            PlaySound(13);
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x34B, static_cast<float>(static_cast<int>(facing) * 0x53) + x,
                (y) + GeometryConstants::HundredThirtySeven, facing, 1);
        }
        break;

    case 0x2DA:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame < 30) {
            ++fieldF04;
            if (fieldF04 > 4) {
                SpawnAuxEffect(0x3E, x, (y) + GeometryConstants::HundredThirty, 1, 1);
                fieldF04 = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > 0.0f)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(
                180 - g_OptionsModeAt006714D0 * 40);
        }
        if (animationStage == 4 && animationFrame == 0) {
            PlaySound(4);
            for (int fanIndex2DA4 = 0; fanIndex2DA4 < 9; ++fanIndex2DA4) {
                field314 = static_cast<float>(fanIndex2DA4 * 40);
                field318 = 8.0f;
                field31C = 1.0f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-fanIndex2DA4 * 40 + 20);
                field318 = 8.0f;
                field31C = -1.0f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 6 && animationFrame == 0) {
            PlaySound(4);
            for (int fanIndex2DA6 = 0; fanIndex2DA6 < 9; ++fanIndex2DA6) {
                field314 = static_cast<float>(fanIndex2DA6 * 40);
                field318 = 10.0f;
                field31C = 0.8f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-fanIndex2DA6 * 40 + 20);
                field318 = 10.0f;
                field31C = -0.8f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 8 && animationFrame == 0 &&
                g_OptionsModeAt006714D0 > 1) {
            PlaySound(4);
            for (int fanIndex2DA8 = 0; fanIndex2DA8 < 9; ++fanIndex2DA8) {
                field314 = static_cast<float>(fanIndex2DA8 * 40);
                field318 = 12.0f;
                field31C = 0.6f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-fanIndex2DA8 * 40 + 20);
                field318 = 12.0f;
                field31C = -0.6f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 10 && animationFrame == 0 &&
                g_OptionsModeAt006714D0 > 2) {
            PlaySound(4);
            for (int fanIndex2DA10 = 0; fanIndex2DA10 < 9; ++fanIndex2DA10) {
                field314 = static_cast<float>(fanIndex2DA10 * 40);
                field318 = 14.0f;
                field31C = 0.6f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
                field314 = static_cast<float>(-fanIndex2DA10 * 40 + 20);
                field318 = 14.0f;
                field31C = -0.6f;
                SpawnBattleEffect(900, x,
                    (y) + GeometryConstants::HundredTwentyFive, facing, 1);
            }
        }
        if (animationStage == 12 && animationFrame == 0 && scriptCounterF00 < 2) {
            ++scriptCounterF00;
            ResetSecondaryCounter(10);
        }
        if (animationStage == 14 && animationFrame == 0 && scriptCounterF02 < 6) {
            ++scriptCounterF02;
            ResetSecondaryCounter(12);
        }
        break;

    case 0x2DB:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            ResetTransform(0.0f, 0.0f, 0.0f);
        }
        if (color[0] > 0x80) {
            color[0] -= 6;
        } else {
            color[0] = 0x80;
        }
        if (animationStage == 0 && field3AC == 0)
            ClearMotionFields();
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                ResetPrimaryCounters(0x2DA);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (animationStage == 2 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(3);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 2) {
                velocityX = static_cast<float>(facing) * (opponent->x - x) / GeometryConstants::Fifty;
                velocityY = 10.0f;
                field05C = 0.4f;
            }
            if (animationStage >= animationStageCount)
                animationStage -= 2;
            BindAnimation();
        }
        break;

    case 0x2E4:
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            remainingHits = 8;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 7 && animationFrame == 0)
            SpawnBattleEffect(0x388, static_cast<float>(static_cast<int>(facing) * 0x43) + x,
                (y) + g_RadialPatternYOffsetAt00659274, facing, 1);
        if (animationStage == 8 && animationFrame == 0)
            SpawnBattleEffect(0x388, static_cast<float>(static_cast<int>(facing) * 0x43) + x,
                (y) + g_RadialPatternYOffsetAt00659274, facing, 1);
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            SpawnBattleEffect(0x397, x,
                (y) + GeometryConstants::Thousand, facing, 1);
        }
        if (animationStage == 7 && animationFrame == 0)
            PlaySound(3);
        if (animationStage == 9 && animationFrame == 0) {
            if (scriptCounterF00 < g_OptionsModeAt006714D0 * 4 + 5) {
                ++scriptCounterF00;
                ResetSecondaryCounter(7);
                return;
            }
            collisionResult = 1;
        }
        if (animationStage == 11 && animationFrame == 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        break;

    case 0x2EE:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 9 || animationStage == 10) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 20) {
                SpawnBattleEffect(0x386, opponent->x, y, facing, 1);
                PlaySound(6);
                scriptCounterF02 = 0;
                ++scriptCounterF00;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > 0.0f)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(
                240 - g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 11 && animationFrame == 0 &&
                scriptCounterF00 < g_OptionsModeAt006714D0 * 2 + 4) {
            ResetSecondaryCounter(9);
        }
        if (animationStage == 13 && animationFrame == 0 && fieldF04 < 2) {
            ++fieldF04;
            ResetSecondaryCounter(11);
        }
        break;

    case 0x2EF:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            if (y > 0.0f)
                ResetPrimaryCounters(9);
            aiCardTimer = static_cast<short>(
                240 - g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 4 && animationFrame == 0) {
            SpawnBattleEffect(0x389, opponent->x, y, facing, 1);
        }
        break;

    case 0x2F8:
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (animationStage < 3 && scriptCounterF00 < 3 && animationFrame < 70) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 4) {
                SpawnAuxEffect(0x40, x, (y) + GeometryConstants::HundredThirty, 1, 1);
                scriptCounterF02 = 0;
            }
        }
        velocityY -= field05C;
        if (velocityY < FloatConstants::Zero)
            velocityY = 0.0f;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x2F9);
            fieldF04 = 0;
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityY = 10.0f;
            field05C = 0.3f;
        }
        if (animationStage == 3 && animationFrame == 0) {
            SpawnBattleEffect(0x38A, x, y, 1, 0);
            PlaySound(13);
        }
        if (animationStage == 8 && animationFrame == 0 && fieldF04 == 0) {
            ResetSecondaryCounter(6);
            return;
        }
        break;

    case 0x2F9:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 120;
            scriptCounterF02 = 0;
            fieldF04 = 0;
            fieldF06 = 0;
            fieldF08 = 60;
        }
        if (opponent->health > 0 && opponent->animationStage == 2 &&
                opponent->roundsRemaining > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        --scriptCounterF00;
        --fieldF06;
        --fieldF08;
        if (opponent->health > 0) {
            if (scriptCounterF00 <= 0) {
                scriptCounterF00 = 180;
                scriptCounterF02 = static_cast<short>(RecordedRange(0, 20) + 30);
                if (RecordedRange(0, 100) < 50) {
                    if (y < GeometryConstants::TwoHundredForty) {
                        if ((x) < GeometryConstants::FourHundredEighty) {
                            fieldF04 = -5;
                        } else {
                            fieldF04 = -175;
                        }
                    }
                } else if ((y) > GeometryConstants::HundredEighty) {
                    if ((x) > GeometryConstants::EightHundred) {
                        fieldF04 = 175;
                    } else {
                        fieldF04 = 5;
                    }
                }
            }
            if (scriptCounterF02 > 0)
                --scriptCounterF02;
            SetPolarVelocity(static_cast<float>(fieldF04),
                static_cast<float>(scriptCounterF02) * FloatConstants::OneTenth);

            if (fieldF06 <= 0) {
                PlaySound(13);
                fieldF06 = 180;
                if (g_OptionsModeAt006714D0 == 0) {
                    for (int radialIndex2F9A = 0; radialIndex2F9A < 6; ++radialIndex2F9A) {
                        field314 = static_cast<float>(radialIndex2F9A * 60);
                        SpawnBattleEffect(0x38C, x,
                            (y) + GeometryConstants::Hundred, facing, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 == 1) {
                    for (int radialIndex2F9B = 0; radialIndex2F9B < 9; ++radialIndex2F9B) {
                        field314 = static_cast<float>(radialIndex2F9B * 40);
                        SpawnBattleEffect(0x38C, x,
                            (y) + GeometryConstants::Hundred, facing, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 == 2) {
                    for (int radialIndex2F9C = 0; radialIndex2F9C < 12; ++radialIndex2F9C) {
                        field314 = static_cast<float>(radialIndex2F9C * 30);
                        SpawnBattleEffect(0x38C, x,
                            (y) + GeometryConstants::Hundred, facing, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 == 3) {
                    for (int radialIndex2F9D = 0; radialIndex2F9D < 18; ++radialIndex2F9D) {
                        field314 = static_cast<float>(radialIndex2F9D * 20);
                        SpawnBattleEffect(0x38C, x,
                            (y) + GeometryConstants::Hundred, facing, 1);
                    }
                }
            }

            if (fieldF08 <= 0) {
                if (fieldF08 == 0) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9A = 0; burstIndex2F9A < 6; ++burstIndex2F9A) {
                        field314 = static_cast<float>(burstIndex2F9A * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - GeometryConstants::ThreeHundred,
                            y + field31C, facing, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 > 0 && fieldF08 == -20) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9B = 0; burstIndex2F9B < 6; ++burstIndex2F9B) {
                        field314 = static_cast<float>(burstIndex2F9B * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - GeometryConstants::ThreeHundred,
                            y + field31C, facing, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 > 1 && fieldF08 == -40) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9C = 0; burstIndex2F9C < 6; ++burstIndex2F9C) {
                        field314 = static_cast<float>(burstIndex2F9C * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - GeometryConstants::ThreeHundred,
                            y + field31C, facing, 1);
                    }
                }
                if (g_OptionsModeAt006714D0 > 2 && fieldF08 == -60) {
                    field318 = static_cast<float>(RecordedRange(0, 600));
                    field31C = static_cast<float>(RecordedRange(0, 300));
                    PlaySound(0);
                    for (int burstIndex2F9D = 0; burstIndex2F9D < 6; ++burstIndex2F9D) {
                        field314 = static_cast<float>(burstIndex2F9D * 60);
                        SpawnBattleEffect(0x38D,
                            x + field318 - GeometryConstants::ThreeHundred,
                            y + field31C, facing, 1);
                    }
                }
                if (fieldF08 <= -60)
                    fieldF08 = static_cast<short>(120 - g_OptionsModeAt006714D0 * 10);
            }

        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
            return;
        }
        break;

    case 0x302:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 1) {
            if (color[0] > 5) {
                color[0] -= 5;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x303);
            field3CF = 1;
            x = 640.0f;
            y = 200.0f;
            facing = 1;
            return;
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        break;

    case 0x303: {
        facing = 1;
        field010 = 0x82;
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 120;
            scriptCounterF02 = -90;
            fieldF04 = 90;
            fieldF06 = 0;
            fieldF08 = 0;
            ClearMotionFields();
        }
        if (opponent->health > 0 && opponent->animationStage == 2 &&
                opponent->roundsRemaining > 0 && opponent->action == 99) {
            opponent->ResetPrimaryCounters(0x5F);
            opponent->field3CF = 1;
            return;
        }
        if (color[0] < 255) {
            if (color[0] < 250)
                color[0] = static_cast<unsigned char>(color[0] + 5);
            else
                color[0] = 255;
        }
        facing = 1;
        x = 640.0f;
        y = 200.0f;
        if (opponent->health > 0) {
            if ((color[0] = 255) != 0) {
                --scriptCounterF00;
                ++fieldF06;
            }
            opponent->field490 = 0.0f;
            if (fieldF06 > 300 && animationStage == 1 && animationFrame == 0) {
                scriptCounterF02 = static_cast<short>(scriptCounterF02 + 10);
                if (scriptCounterF02 == 180)
                    scriptCounterF02 = -180;
                fieldF04 = static_cast<short>(fieldF04 - 10);
                if (fieldF04 == -180)
                    fieldF04 = 180;
                PlaySound(0x0E);
                field318 = static_cast<float>(scriptCounterF02);
                SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                if (g_OptionsModeAt006714D0 > 0) {
                    field318 = static_cast<float>(fieldF04);
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                }
                if (g_OptionsModeAt006714D0 == 2) {
                    field318 = static_cast<float>(fieldF04 + 180);
                    if ((field318) >= GeometryConstants::HundredEighty)
                        field318 -= GeometryConstants::DegreesPerTurn;
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(scriptCounterF02 - 180);
                    if (field318 <= GeometryConstants::NegativeHundredEighty)
                        field318 = (field318) + GeometryConstants::DegreesPerTurn;
                    SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                }
                if (g_OptionsModeAt006714D0 == 3) {
                    field318 = static_cast<float>(fieldF04 + 120);
                    if ((field318) >= GeometryConstants::HundredEighty)
                        field318 -= GeometryConstants::DegreesPerTurn;
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(scriptCounterF02 - 120);
                    if (field318 <= GeometryConstants::NegativeHundredEighty)
                        field318 = (field318) + GeometryConstants::DegreesPerTurn;
                    SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(fieldF04 + 240);
                    if ((field318) >= GeometryConstants::HundredEighty)
                        field318 -= GeometryConstants::DegreesPerTurn;
                    SpawnBattleEffect(0x391, 640.0f, 340.0f, 1, 0);
                    field318 = static_cast<float>(scriptCounterF02 - 240);
                    if (field318 <= GeometryConstants::NegativeHundredEighty)
                        field318 = (field318) + GeometryConstants::DegreesPerTurn;
                    SpawnBattleEffect(0x38E, 640.0f, 340.0f, 1, 0);
                }
            }
            if (scriptCounterF00 <= 0) {
                if (scriptCounterF00 == 0) {
                    PlaySound(0);
                    int fanIndex303A;
                    for (fanIndex303A = 0; fanIndex303A < 20; ++fanIndex303A) {
                        field314 = static_cast<float>(fanIndex303A * 18);
                        field318 = 1.0f;
                        field31C = 1.0f;
                        SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        if (g_OptionsModeAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303A * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        }
                    }
                    for (fanIndex303A = 0; fanIndex303A < 20; ++fanIndex303A) {
                        field314 = static_cast<float>(fanIndex303A * -18);
                        field318 = 1.0f;
                        field31C = -1.0f;
                        SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        if (g_OptionsModeAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303A * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x394, 640.0f, 340.0f, 1, 1);
                        }
                    }
                }
                if (scriptCounterF00 == -30) {
                    PlaySound(0);
                    int fanIndex303C;
                    for (fanIndex303C = 0; fanIndex303C < 20; ++fanIndex303C) {
                        field314 = static_cast<float>(fanIndex303C * 18);
                        field318 = 1.0f;
                        field31C = 1.0f;
                        SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        if (g_OptionsModeAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303C * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        }
                    }
                    for (fanIndex303C = 0; fanIndex303C < 20; ++fanIndex303C) {
                        field314 = static_cast<float>(fanIndex303C * -18);
                        field318 = 1.0f;
                        field31C = -1.0f;
                        SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        if (g_OptionsModeAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303C * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x395, 640.0f, 340.0f, 1, 1);
                        }
                    }
                }
                if (g_OptionsModeAt006714D0 > 1 && scriptCounterF00 == -60) {
                    PlaySound(0);
                    int fanIndex303E;
                    for (fanIndex303E = 0; fanIndex303E < 20; ++fanIndex303E) {
                        field314 = static_cast<float>(fanIndex303E * 18);
                        field318 = 1.0f;
                        field31C = 1.0f;
                        SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        if (g_OptionsModeAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303E * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        }
                    }
                    for (fanIndex303E = 0; fanIndex303E < 20; ++fanIndex303E) {
                        field314 = static_cast<float>(fanIndex303E * -18);
                        field318 = 1.0f;
                        field31C = -1.0f;
                        SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        if (g_OptionsModeAt006714D0 == 3) {
                            field314 = static_cast<float>(fanIndex303E * 18 + 9);
                            field318 = 3.0f;
                            SpawnBattleEffect(0x396, 640.0f, 340.0f, 1, 1);
                        }
                    }
                }
                if (scriptCounterF00 == -60) {
                    scriptCounterF00 = static_cast<short>(
                        180 - g_OptionsModeAt006714D0 * 10);
                }
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
            return;
        }
        if (animationStage == 7 && animationFrame == 0) {
            ResetSecondaryCounter(1);
        }
        break;
    }

    case 0x31B:
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
        }
        break;

    case 0x31C:
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (roundSpellVariants[roundsRemaining] == 1) {
                ResetPrimaryCounters(0x2E4);
                return;
            }
            ResetPrimaryCounters(0);
        }
        if (animationStage == 0x0B && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            PlaySharedSound(0x17);
        }
        if (animationStage == 14 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(0x0C);
            field3CF = 1;
        }
        break;

    default:
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        break;

    advanceFrame:
        AdvanceNestedFrame();
    }
}
