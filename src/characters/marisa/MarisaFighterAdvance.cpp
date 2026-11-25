#include "battle/CombatMode.hpp"
#include "engine/MathFloatHelpers.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/marisa/MarisaFighter.hpp"

extern float g_MarisaResourceYAt00659298;
extern float g_MarisaResourceYAt0065928C;
extern float g_MarisaResourceYAt00659274;
void MarisaFighter::Advance() {
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
        goto advanceNestedAndReturn;
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
        goto advanceNestedAndReturn;
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
        goto advanceNestedAndReturn;
    }

    case 0x5: {
        velocityX = -6.0f;
        goto advanceNestedAndReturn;
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
        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 0.0f;
                velocityY = 16.0f;
                field05C = 0.75f;
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
        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 5.0f;
                velocityY = 16.0f;
                field05C = 0.75f;
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
            if (animationStage == 4) {
                velocityX = -4.0f;
                field3AC = 0;
                velocityY = 16.0f;
                field05C = 0.75f;
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
            Fighter::PlaySharedSound(30);
        ClearMotionFields();
        if (AdvanceNestedFrame() == animationStageCount) {
            if (inputY == 0)
                ResetPrimaryCounters(3);
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
            if (velocityY < GeometryConstants::Six)
                velocityY = 6.0f;
            field05C = 0.8f;
            if (velocityY > GeometryConstants::TwentyFive)
                velocityY = 25.0f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
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
            field05C = 0.8f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
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
            field05C = 1.3f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
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
            field05C = 0.8f;
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
            field05C = 0.5f;
            SetCameraShake(2.0f);
            Fighter::PlaySharedSound(0x16);
            scriptCounterF00 = 0;
            return;
        }
        velocityY = velocityY - field05C;
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
            ResetSecondaryCounter(7);
        return;
    }

    case 0x4C: {
        if (scriptCounterF00 == 0) {
            ++scriptCounterF00;
            ResetTransform(0.0f,95.0f,0.0f);
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
            velocityX = -(hitReactionVelocityX);
            velocityY = hitReactionVelocityY;
            field05C = 0.8f;
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
            // Continue the impact animation.
        }
        return;
    }

    case 0x59: {
        if ((animationStage) == 3) {
            rotationZ = (rotationZ)+GeometryConstants::Forty;
            velocityY = velocityY-field05C;
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
        else if ((animationStage) == 3 && (animationFrame) == 0) {
            velocityX = static_cast<float>(scriptCounterF00)*FloatConstants::OneFourHundredth;
            velocityY = static_cast<float>(-scriptCounterF02)*FloatConstants::OneHundredth;
            field05C = 0.7f;
            ResetTransform(0.0f,95.0f,0.0f);
        } else if (animationStage == 3 && animationFrame != 0) {
            // Continue the bounce animation.
        }
        return;
    }

    case 0x5D: {
        if (animationStage < 11 && y > FloatConstants::Zero) {
            velocityY -= field05C;
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
        if (animationStage == 5 && animationFrame == 0) {
            velocityY = 8.0f;
            velocityX = 13.5f;
            field05C = 0.6f;
        }
        if (animationStage == 11 && animationFrame == 0) {
            ResetSecondaryCounter(9);
        } else if (animationStage == 11 && animationFrame != 0) {
            // Continue the landing animation.
        }
        return;
    }

    case 0x5E: {
        if (animationStage < 12 && y > FloatConstants::Zero) {
            velocityY -= field05C;
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
        if (animationStage == 4 && animationFrame == 0) {
            velocityY = 8.0f;
            velocityX = -13.5f;
            field05C = 0.6f;
        }
        if (animationStage == 12 && animationFrame == 0) {
            ResetSecondaryCounter(10);
        } else if (animationStage == 12 && animationFrame != 0) {
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
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage == 3) {
            velocityY -= field05C;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(4);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0)
                ResetPrimaryCounters(99);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneTwoHundredth;
            velocityY = static_cast<float>(-scriptCounterF02) * FloatConstants::OneTwoHundredth;
            field05C = 2.0f;
        }
        return;
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
            for (int shot = 0; shot < 10; ++shot)
                SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (fieldEFA > 25) {
                fieldEFA = 0;
                SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
        }
        if (animationStage == 3) {
            velocityY -= field05C;
            if (velocityY + y < FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(4);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0x62);
            if (field3CF == 0)
                ResetPrimaryCounters(99);
        } else if (animationStage == 3 && animationFrame == 0) {
            velocityX = static_cast<float>(scriptCounterF00) * FloatConstants::OneTwoHundredth;
            velocityY = static_cast<float>(-scriptCounterF02) * FloatConstants::OneTwoHundredth;
            field05C = 2.0f;
        } else if (animationStage == 3 && animationFrame != 0) {
            // Continue the launch animation.
        }
        return;
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

    case 0x91: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = -10.0f;
            velocityY = 14.0f;
            field05C = 0.5f;
            collisionResult = 0;
        }
        if (animationStage == 3 && velocityY < FloatConstants::Two) {
            ResetSecondaryCounter(4);
            return;
        }
        velocityY = velocityY-field05C;
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
            ResetSecondaryCounter(7);
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
                return;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
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
                return;
            }
        }
        if (AdvanceNestedFrame()==animationStageCount) {
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
        if (velocityX > FloatConstants::TenAndHalf) {
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
            if (static_cast<int>(facing) * inputX > 0 && scriptCounterF00 < 2) {
                ResetSecondaryCounter(4);
                ++scriptCounterF00;
                return;
            }
            ResetPrimaryCounters(0xCF);
            return;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 15.0f;
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
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = -11.0f;
            velocityY = 5.0f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::Eighty, -facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Eighty, -facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (y > FloatConstants::Zero && animationStage > 1 && animationStage < 5) {
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
        return;
    }

    case 0xCA: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if (animationStage == 2 && animationFrame == 0) {
            velocityX = 10.5f;
            velocityY = 5.0f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (y > FloatConstants::Zero && animationStage > 1) {
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
        return;
    }

    case 0xCB: {
        SetCommandSelection(3, 4, 0xFF);
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
        }
        if (y > FloatConstants::Zero && animationStage > 0) {
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
        if (animationStage == 1 && animationFrame == 0) {
            velocityX = -10.5f;
            velocityY = 5.0f;
            field05C = 0.6f;
            SpawnAuxEffect(0x7D,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::Hundred, -facing, 1);
            SpawnAuxEffect(0x7E, x,
                (y) + GeometryConstants::Hundred, -facing, 1);
            Fighter::PlaySharedSound(0x1F);
        }
        if (animationStage == 3 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(1);
        }
        return;
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
        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
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
        if (animationStage == 4 && velocityY < FloatConstants::Four)
            ResetSecondaryCounter(5);
        ++animationFrame;
        if (animationFrame >= animationFrameCount) {
            animationFrame = 0;
            ++animationStage;
            if (animationStage == 4) {
                velocityX = 10.0f;
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
            if (animationStage == 4) {
                velocityX = -10.0f;
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
            facing = static_cast<signed char>(-facing);
            velocityX = -velocityX;
        }
        if (field05C == FloatConstants::Zero)
            field05C = 0.6f;
        velocityY -= field05C;
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
        velocityY -= field05C * 0.25f;
        if (AdvanceNestedFrame() == animationStageCount) {
            if (static_cast<unsigned int>(inputD) > 0)
                ResetSecondaryCounter(2);
            else
                ResetPrimaryCounters(9);
        }
        return;
    }

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
            Fighter::PlaySharedSound(0x1B);
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
            Fighter::PlaySharedSound(0x1C);
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
        if (animationStage == 3 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x130: {
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
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        } else if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x323,
                static_cast<float>(facing * 38) + x,
                (y) + FloatConstants::Three, facing, 1);
            SpawnBattleEffect(0x324,
                static_cast<float>(facing * 38) + x,
                (y) + FloatConstants::Three, facing, 1);
            Fighter::PlaySharedSound(0x1C);
        }
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
        if (animationStage == 2 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1C);
        return;
    }

    case 0x133: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            field05C = 0.0f;
            remainingHits = 1;
            collisionResult = 0;
        }
        if (velocityX > FloatConstants::Zero)
            velocityX -= FloatConstants::OneTwentieth;
        if (y > FloatConstants::Zero &&
            animationStage > 6 && animationStage < 9) {
            velocityY -= field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(9);
                PlaySound(0x13);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 15.0f;
            velocityY = 7.0f;
            field05C = 0.9f;
            PlaySound(0x12);
        }
        if (animationStage == 9 && y > FloatConstants::Zero) {
            ResetSecondaryCounter(animationStage - 2);
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
            Fighter::PlaySharedSound(0x1C);
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
        if (animationStage == 5 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1D);
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
        if (animationStage == 3 && animationFrame == 0)
            velocityX = 12.0f;
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1D);
        if (animationStage == 5 && animationFrame == 0) {
            SetCameraShake(2.0f);
            SpawnBattleEffect(0x325,
                static_cast<float>(facing * 170) + x,
                y - GeometryConstants::Six, facing, 0);
        }
        return;
    }

    case 0x186: {
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
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
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1D);
        if (animationStage == 5 && animationFrame == 0) {
            SetCameraShake(2.0f);
            SpawnBattleEffect(0x325,
                static_cast<float>(facing * 170) + x,
                y - GeometryConstants::Six, facing, 0);
        }
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
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 4 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1D);
        return;
    }

    case 0x188: {
        if (animationStage == 0 && animationFrame == 0) {
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
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
        if (animationStage == 5 && animationFrame == 0)
            Fighter::PlaySharedSound(0x1D);
        return;
    }

    case 0x189: {
        if (animationStage == 0 && animationFrame == 0) {
            field3AC = 0;
            remainingHits = 1;
            collisionResult = 0;
            field05C = 0.0f;
            velocityY = 0.0f;
            velocityX = 12.5f;
        }
        if (velocityX > FloatConstants::Zero)
            velocityX -= FloatConstants::OneTwentieth;
        if (y > FloatConstants::Zero &&
            animationStage > 6 && animationStage < 9) {
            velocityY -= field05C;
            if (velocityY + y <= FloatConstants::Zero) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                field05C = 0.0f;
                y = 0.0f;
                animationFrame = 0;
                ResetSecondaryCounter(9);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0) {
            velocityX = 13.5f;
            velocityY = 9.0f;
            field05C = 0.9f;
        }
        if (animationStage == 9 && y > FloatConstants::Zero) {
            ResetSecondaryCounter(animationStage - 2);
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

    case 0x190: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(800,
                static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            UpdateGaugeTimer(0x96);
            PlaySound(6);
        } else if (animationStage == 5 && animationFrame != 0) {
            // Continue the firing animation.
        }
        return;
    }

    case 0x191: {
        if (animationStage == 0 && animationFrame == 0)
            collisionResult = 1;
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x321,
                static_cast<float>(facing * 100) + x,
                (y) + g_MarisaResourceYAt00659298, facing, 1);
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
            SpawnBattleEffect(0x321,
                static_cast<float>(facing * 99) + x,
                (y) + GeometryConstants::SixtySix, facing, 1);
            UpdateGaugeTimer(0x96);
            PlaySound(6);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(2);
        return;
    }

    case 0x194: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x322,
                static_cast<float>(facing * 70) + x,
                (y) + GeometryConstants::HundredSixteen, facing, 1);
            UpdateGaugeTimer(0x96);
            PlaySound(6);
        } else if (animationStage == 5 && animationFrame != 0) {
            // Continue the firing animation.
        }
        return;
    }

    case 0x196: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = static_cast<float>(scriptCounterF00 * 8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 96) + x,
                (y) + GeometryConstants::HundredFour, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 7 && animationFrame == 0 && static_cast<unsigned int>(inputC) > 0 &&
                scriptCounterF00 < 5 && spirit > 0) {
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * 8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 96) + x,
                (y) + GeometryConstants::HundredFour, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x197: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = static_cast<float>(scriptCounterF00 * 8 + 30);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659298, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 7 && animationFrame == 0 && static_cast<unsigned int>(inputC) > 0 &&
                scriptCounterF00 < 5 && spirit > 0) {
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * 8 + 30);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659298, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x198: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
            UpdateGaugeTimer(100);
        }
        if (animationStage == 6 && animationFrame == 0) {
            field314 = static_cast<float>(scriptCounterF00 * 4);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 92) + x,
                (y) + GeometryConstants::Seventy, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0 &&
            static_cast<unsigned int>(inputC) > 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x199: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = static_cast<float>(45 - scriptCounterF00 * 8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 81) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 7 && animationFrame == 0 && static_cast<unsigned int>(inputC) > 0 &&
                scriptCounterF00 < 5 && spirit > 0) {
            ++scriptCounterF00;
            field314 = static_cast<float>(45 - scriptCounterF00 * 8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 81) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x19A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        velocityY -= field05C;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 8.5f;
            field05C = 0.5f;
            field314 = static_cast<float>((-scriptCounterF00) * 8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::HundredFourteen, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 7 && animationFrame == 0 && static_cast<unsigned int>(inputC) > 0 &&
                scriptCounterF00 < 5 && spirit > 0) {
            ++scriptCounterF00;
            field314 = static_cast<float>((-scriptCounterF00) * 8);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::HundredFourteen, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x19B: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        velocityY -= field05C;
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            velocityX = -3.0f;
            velocityY = 8.5f;
            field05C = 0.5f;
            field314 = static_cast<float>(scriptCounterF00 * 8 - 45);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(100);
        }
        if (animationStage == 7 && animationFrame == 0 && static_cast<unsigned int>(inputC) > 0 &&
                scriptCounterF00 < 5 && spirit > 0) {
            ++scriptCounterF00;
            field314 = static_cast<float>(scriptCounterF00 * 8 - 45);
            SpawnBattleEffect(0x32B,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(20);
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x19C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 96) + x,
                (y) + GeometryConstants::HundredFour, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
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
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 20.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659298, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        return;
    }

    case 0x19E: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 92) + x,
                (y) + GeometryConstants::Seventy, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 7 && animationFrame == 0 &&
            static_cast<unsigned int>(inputC) > 0 && scriptCounterF00 < 5) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x19F: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 55.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 81) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        return;
    }

    case 0x1A0: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 80) + x,
                (y) + GeometryConstants::HundredFourteen, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        return;
    }

    case 0x1A1: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 6 && animationFrame == 0) {
            field314 = -20.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            PlaySound(1);
            UpdateGaugeTimer(200);
        }
        return;
    }

    case 0x1A2: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            field314 = 5.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            field314 = 6.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            field314 = 7.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            field314 = 8.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            PlaySound(5);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x1A3: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            field314 = 10.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            field314 = 11.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            field314 = 12.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            field314 = 13.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            PlaySound(5);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
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
                (x) + GeometryConstants::Thirty - static_cast<float>(RecordedRange(0, 0x3C)),
                (y) + GeometryConstants::Forty + static_cast<float>(RecordedRange(0, 0x8C)), facing, 1);
        }
        if (velocityX > FloatConstants::Zero) {
            velocityX -= FloatConstants::ThreeTenths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        }
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(12);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySound(2);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 8.0f;
            velocityY = 14.0f;
            field05C = 0.8f;
            SpawnAuxEffect(0x7F, x, y, facing, 1);
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
                (y) + GeometryConstants::Forty + static_cast<float>(RecordedRange(0, 140)), facing, 1);
        }
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(12);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySound(2);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 18.0f;
            velocityY = 16.0f;
            field05C = 0.8f;
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        if (animationStage == 12 && animationFrame == 0)
            ResetSecondaryCounter(10);
        return;
    }

    case 0x208: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            ClearMotionFields();
            remainingHits = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 6) {
            velocityX -= FloatConstants::SevenTenths;
            if (velocityX < FloatConstants::Zero)
                velocityX = 0.0f;
        } else if (animationStage == 6 && animationFrame != 0) {
            // Keep the current speed until the drift stage starts.
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0)
            velocityX = 12.5f;
        if (animationStage == 6 && animationFrame == 0 && scriptCounterF00 < 0) {
            ++scriptCounterF00;
            ResetSecondaryCounter(4);
        }
        if (animationStage == 9 && animationFrame == 0)
            PlaySound(3);
        return;
    }

    case 0x20A: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            ClearMotionFields();
            remainingHits = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 8 && animationStage < 15 &&
            (collisionResult != 0 ||
             (CheckHorizontalLimits() &&
              ((x > GeometryConstants::SixHundredForty && facing == 1) ||
               (x < GeometryConstants::SixHundredForty && facing == -1))))) {
            ResetSecondaryCounter(0x0F);
            velocityX = -3.0f;
            velocityY = 14.0f;
            field05C = 0.9f;
            return;
        }
        if (animationStage > 14 && animationStage < 27) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(0x1B);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 14.5f;
            PlaySound(10);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(9);
            ++scriptCounterF00;
            if (scriptCounterF00 > 0) {
                ResetPrimaryCounters(0x20E);
                return;
            }
        }
        if (animationStage == 0x1B && animationFrame == 0)
            ResetSecondaryCounter(0x19);
        return;
    }

    case 0x20B: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            ClearMotionFields();
            remainingHits = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 8 && animationStage < 15 &&
            (collisionResult != 0 ||
             (CheckHorizontalLimits() &&
              ((x > GeometryConstants::SixHundredForty && facing == 1) ||
               (x < GeometryConstants::SixHundredForty && facing == -1))))) {
            ResetSecondaryCounter(0x0F);
            velocityX = -3.0f;
            velocityY = 15.0f;
            field05C = 0.9f;
            return;
        }
        if (animationStage > 14 && animationStage < 27) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(0x1B);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 18.5f;
            PlaySound(10);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(9);
            ++scriptCounterF00;
            if (scriptCounterF00 > 1) {
                ResetPrimaryCounters(0x20E);
                return;
            }
        }
        if (animationStage == 0x1B && animationFrame == 0)
            ResetSecondaryCounter(0x19);
        return;
    }

    case 0x20C: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            ClearMotionFields();
            remainingHits = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 8 && animationStage < 15 &&
            (collisionResult != 0 ||
             (CheckHorizontalLimits() &&
              ((x > GeometryConstants::SixHundredForty && facing == 1) ||
               (x < GeometryConstants::SixHundredForty && facing == -1))))) {
            ResetSecondaryCounter(0x0F);
            velocityX = -3.0f;
            velocityY = 14.0f;
            field05C = 0.9f;
            return;
        }
        if (animationStage > 14 && animationStage < 27) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(0x1B);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 14.5f;
            PlaySound(10);
            SpawnAuxEffect(0x80,
                static_cast<float>(facing * 150) + x, y, facing, 1);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(9);
            ++scriptCounterF00;
            if (scriptCounterF00 > 0) {
                ResetPrimaryCounters(0x20E);
                return;
            }
        }
        if (animationStage == 0x1B && animationFrame == 0)
            ResetSecondaryCounter(0x19);
        return;
    }

    case 0x20D: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            ClearMotionFields();
            remainingHits = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage > 8 && animationStage < 15 &&
            (collisionResult != 0 ||
             (CheckHorizontalLimits() &&
              ((x > GeometryConstants::SixHundredForty && facing == 1) ||
               (x < GeometryConstants::SixHundredForty && facing == -1))))) {
            ResetSecondaryCounter(0x0F);
            velocityX = -3.0f;
            velocityY = 15.0f;
            field05C = 0.9f;
            return;
        }
        if (animationStage > 14 && animationStage < 27) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(0x1B);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 18.5f;
            PlaySound(10);
            SpawnAuxEffect(0x80,
                static_cast<float>(facing * 150) + x, y, facing, 1);
        }
        if (animationStage == 15 && animationFrame == 0) {
            ResetSecondaryCounter(9);
            ++scriptCounterF00;
            if (scriptCounterF00 > 1) {
                ResetPrimaryCounters(0x20E);
                return;
            }
        }
        if (animationStage == 0x1B && animationFrame == 0)
            ResetSecondaryCounter(0x19);
        return;
    }

    case 0x20E: {
        if (animationStage == 0 && animationFrame == 0) {
            if (y == FloatConstants::Zero)
                collisionResult = 1;
            ClearMotionFields();
            velocityX = 10.0f;
            velocityY = 7.0f;
            field05C = 0.5f;
        }
        if (animationStage < 10) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                ResetSecondaryCounter(10);
                y = 0.0f;
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 10 && animationFrame == 0)
            ResetSecondaryCounter(8);
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
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x21);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
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
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x21);
        }
        return;
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
                (y) + GeometryConstants::Hundred, facing, 1);
            Fighter::PlaySharedSound(0x21);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 1) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x258: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 100) + x,
                (y) + GeometryConstants::Hundred, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x259: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 30.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 90) + x,
                (y) + g_MarisaResourceYAt00659298, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x25A: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            field314 = 0.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 74) + x,
                (y) + GeometryConstants::HundredFifteen, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(200);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        return;
    }

    case 0x25B: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::Quarter;
            velocityY = (velocityY) * FloatConstants::Quarter;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (animationStage == 6 && animationFrame == 0) {
            field314 = -30.0f;
            SpawnBattleEffect(0x32C,
                static_cast<float>(facing * 64) + x,
                (y) + g_EffectOffsetNinetyTwo, facing, 1);
            PlaySound(4);
            UpdateGaugeTimer(200);
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
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            PlaySound(5);
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
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x333,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            PlaySound(5);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x270: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            field314 = 20.0f;
            field318 = 150.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            PlaySound(5);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        return;
    }

    case 0x271: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            UpdateGaugeTimer(0xFA);
            field314 = 60.0f;
            field318 = 150.0f;
            SpawnBattleEffect(0x332,
                static_cast<float>(facing * 70) + x,
                (y) + g_MarisaResourceYAt0065928C, facing, 1);
            PlaySound(5);
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
        }
        if (animationStage == 2 && animationFrame == 10) {
            spellPower -= GeometryConstants::Hundred;
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x73,
                x - static_cast<float>(facing * 18),
                (y) + g_EffectOffsetNinetyTwo, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x334,
                static_cast<float>(facing * 32) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            SpawnBattleEffect(0x329,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 6 && animationFrame == 0) {
            ResetPrimaryCounters(0x2BD);
            SpawnBattleEffect(0x34F,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::HundredThirty, facing, 0);
            PlaySound(0);
        }
        return;
    }

    case 0x2BD: {
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x32A,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        UpdateGaugeTimer(10);
        if (spirit <= 0)
            ++scriptCounterF00;
        if (scriptCounterF00 > 20) {
            scriptCounterF00 = 0;
            ResetPrimaryCounters(700);
            ResetSecondaryCounter(6);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        return;
    }

    case 0x2BF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 0;
            remainingHits = 6;
            ClearMotionFields();
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (collisionResult == 1 && scriptCounterF02 == 0) {
            ++scriptCounterF02;
            PlaySound(0x0B);
        }
        if (((CheckHorizontalLimits() && collisionResult != 1 &&
              ((facing == 1 && x > GeometryConstants::SixHundredForty) ||
               (facing == -1 && x < GeometryConstants::SixHundredForty))) ||
             (remainingHits == 0 && collisionResult == 2)) && animationStage < 23) {
            ResetSecondaryCounter(0x17);
            velocityX = -2.5f;
            velocityY = 15.0f;
            field05C = 0.5f;
        }
        if (animationStage > 14 && animationStage < 23) {
            SpawnBattleEffect(0x34C,
                x - static_cast<float>(facing * 90),
                (y) + GeometryConstants::NinetyFive, -facing, 1);
        }
        if (y > FloatConstants::Zero && animationStage > 22 &&
            animationStage < 35) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(0x23);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            spellPower -= GeometryConstants::Hundred;
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - FloatConstants::Zero,
                (y) + GeometryConstants::Seventy, facing, 1);
        }
        if (animationStage == 15 && animationFrame == 0) {
            remainingHits = 20;
            velocityX = 25.0f;
            PlaySound(10);
            UpdateGaugeTimer(500);
            SpawnBattleEffect(0x33B, x - FloatConstants::Zero, y, facing, 1);
            SpawnBattleEffect(0x34E,
                x - static_cast<float>(facing * 110),
                (y) + GeometryConstants::NinetyFive, facing, 1);
            if (y == FloatConstants::Zero)
                SpawnAuxEffect(0x7F, x, 0.0f, facing, 1);
        } else if (animationStage == 15 && animationFrame != 0) {
            // Continue the firing animation.
        }
        if (animationFrame == 0 && animationStage > 14 && animationStage < 23) {
            if (y == FloatConstants::Zero) {
                SpawnAuxEffect(0x80,
                    x - static_cast<float>(facing * 200), y, facing, 1);
            }
            if (collisionResult != 0) {
                collisionResult = 0;
                velocityX = 10.0f;
            } else {
                collisionResult = 0;
                velocityX = 25.0f;
            }
        }
        if (animationStage == 23 && animationFrame == 0)
            ResetSecondaryCounter(15);
        if (animationStage == 35 && animationFrame == 0)
            ResetSecondaryCounter(0x21);
        return;
    }

    case 0x2C0: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 0;
            remainingHits = 6;
            ClearMotionFields();
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
        }
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(7);
                return;
            }
        }
        if (animationStage == 3) {
            ++scriptCounterF00;
            if (scriptCounterF00 > 60) {
                scriptCounterF00 = 0;
                ResetSecondaryCounter(4);
                PlaySound(0x0C);
                UpdateGaugeTimer(500);
                SpawnBattleEffect(0x339,
                    x - static_cast<float>(facing * 200), 0.0f, facing, 1);
                SpawnBattleEffect(0x33A,
                    x - static_cast<float>(facing * 200), 0.0f, facing, 1);
                return;
            }
        }
        if (animationStage == 4 && scriptCounterF02 == 1) {
            ResetSecondaryCounter(5);
            ClearMotionFields();
            field05C = 0.5f;
            y = 1600.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x74, x - FloatConstants::Zero,
                (y) + GeometryConstants::Seventy, facing, 1);
        }
        if (animationStage == 3 && animationFrame == 0) {
            Fighter::SpawnTrackedEffect(0x338, x, y, facing, 1, 0, 1);
            velocityX = -30.0f;
        }
        if (animationStage == 4 && animationFrame == 0)
            ResetSecondaryCounter(3);
        if (animationStage == 5 && animationFrame == 0)
            ResetSecondaryCounter(4);
        if (animationStage == 7 && animationFrame == 0)
            ResetSecondaryCounter(5);
        return;
    }

    case 0x2C1: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 0;
            remainingHits = 6;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x73, x - FloatConstants::Zero,
                (y) + GeometryConstants::Seventy, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x342, x - FloatConstants::Zero, y, facing, 1);
            UpdateGaugeTimer(500);
            fieldF14 = 4;
            fieldF16 = 4;
            fieldF18 = 0x1A4;
            PlaySound(0x0D);
        }
        return;
    }

    case 0x2C2: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 0;
            remainingHits = 6;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            spellPower -= GeometryConstants::Hundred;
            SpawnAuxEffect(0x74, x - FloatConstants::Zero,
                (y) + GeometryConstants::Seventy, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x343, x - FloatConstants::Zero, y, facing, 1);
            UpdateGaugeTimer(0x1F4);
            fieldF14 = 6;
            fieldF16 = 6;
            fieldF18 = 0x1A4;
            PlaySound(0x0D);
        }
        return;
    }

    case 0x2C3: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x73, x - FloatConstants::Zero,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(0x0E);
            UpdateGaugeTimer(500);
        }
        return;
    }

    case 0x2C4: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x73,
                x - static_cast<float>(facing * 20),
                (y) + GeometryConstants::EightyFive, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(0x0F);
            UpdateGaugeTimer(500);
            fieldF18 = 300;
        }
        return;
    }

    case 0x2C5: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(0x10);
        return;
    }

    case 0x2C6: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(0x10);
        return;
    }

    case 0x2C8: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x345,
                static_cast<float>(facing * 32) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            SpawnBattleEffect(0x346,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x74,
                x - static_cast<float>(facing * 18),
                (y) + g_EffectOffsetNinetyTwo, facing, 1);
        }
        if (animationStage == 6 && animationFrame == 0) {
            ResetPrimaryCounters(0x2C9);
            SpawnBattleEffect(0x34F,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::HundredThirty, facing, 0);
            PlaySound(0x11);
        }
        return;
    }

    case 0x2C9: {
        if (animationStage == 0 && animationFrame == 0) {
            SpawnBattleEffect(0x347,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        SetCameraShake(5.0f);
        if ((spellPower) >= FloatConstants::Three || spirit >= 20) {
            spellPower -= FloatConstants::Three;
            UpdateGaugeTimer(20);
        } else {
            spellPower = 0.0f;
            ++scriptCounterF00;
        }
        if (scriptCounterF00 > 50) {
            scriptCounterF00 = 0;
            ResetPrimaryCounters(700);
            ResetSecondaryCounter(6);
            if (opponent->health > 0)
                spellTimer = 1;
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0);
        }
        return;
    }

    case 0x2CA: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x74, x - FloatConstants::Zero,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(0x0E);
            UpdateGaugeTimer(500);
        }
        return;
    }

    case 0x2CB: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0) {
            SetNonnegativeWord(0x28);
            Fighter::PlaySharedSound(0x17);
            SpawnAuxEffect(0x74,
                x - static_cast<float>(facing * 20),
                (y) + GeometryConstants::EightyFive, facing, 1);
        }
        if (animationStage == 5 && animationFrame == 0) {
            PlaySound(6);
            UpdateGaugeTimer(500);
            fieldF18 = 300;
        }
        return;
    }

    case 0x2CC: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(6);
        return;
    }

    case 0x2CD: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(9);
        if (animationStage == 5 && animationFrame == 0)
            PlaySound(6);
        return;
    }

    case 0x2CE: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        return;
    }

    case 0x2CF: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            ClearMotionFields();
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
        }
        return;
    }

    case 0x2D0: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        return;
    }

    case 0x2D1: {
        if (animationStage == 0 && animationFrame == 0) {
            velocityX = (velocityX) * FloatConstants::OneTenth;
            velocityY = (velocityY) * FloatConstants::OneTenth;
            collisionResult = 1;
            scriptCounterF00 = 0;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(9);
        }
        return;
    }

    case 0x2DB: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 0;
            remainingHits = 1;
            ClearMotionFields();
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        if (CheckHorizontalLimits() &&
            ((x > GeometryConstants::SixHundredForty && facing == 1) ||
             (x < GeometryConstants::SixHundredForty && facing == -1)) &&
            animationStage < 17) {
            ResetSecondaryCounter(0x11);
            velocityX = -4.0f;
            velocityY = 17.0f;
            field05C = 0.4f;
        }
        if (animationStage > 8 && animationStage < 17) {
            --scriptCounterF02;
            if (scriptCounterF02 <= 0) {
                SpawnBattleEffect(0x385,
                    x - static_cast<float>(facing * 140),
                    (y) + GeometryConstants::HundredTen, facing, 1);
                scriptCounterF02 = -(g_OptionsModeAt006714D0 - 3);
            }
        }
        if (y > FloatConstants::Zero && animationStage > 16) {
            velocityY -= field05C;
            velocityX = (velocityX) + FloatConstants::Half;
            if (velocityX > GeometryConstants::NegativeFive)
                velocityX = -5.0f;
            if (y + velocityY <= FloatConstants::Zero) {
                ClearMotionFields();
                y = 0.0f;
                ResetSecondaryCounter(26);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(0, 60) + 180 -
                g_OptionsModeAt006714D0 * 30);
        }
        if (animationStage == 9 && animationFrame == 0) {
            velocityX = 25.0f;
            PlaySound(10);
            SpawnBattleEffect(0x33B, x - FloatConstants::Zero, y, facing, 1);
            if (y == FloatConstants::Zero)
                SpawnAuxEffect(0x7F, x, 0.0f, facing, 1);
        }
        if (animationStage == 17 && animationFrame == 0 && scriptCounterF00 < 3) {
            ++scriptCounterF00;
            ResetSecondaryCounter(9);
        }
        if (animationStage == 26 && animationFrame == 0)
            ResetSecondaryCounter(24);
        return;
    }

    case 0x2E5: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
        }
        if (animationStage > 5 && animationStage < 8 && animationFrame == 0) {
            scriptCounterF02 = static_cast<short>(RecordedRange(0, 4));
            field314 = static_cast<float>(RecordedRange(0, 0x167));
            for (int i = 0; i < static_cast<int>(g_OptionsModeAt006714D0) + 1; ++i) {
                PlaySound(0x14);
                field31C = 3.0f;
                field318 = static_cast<float>(i * 7);
                SpawnBattleEffect(
                    static_cast<short>(scriptCounterF02 + 0x38E),
                    x - static_cast<float>(facing * 25),
                    (y) + g_MarisaResourceYAt00659274, facing, 1);
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(60, 120) -
                g_OptionsModeAt006714D0 * 20);
        }
        if (animationStage == 8 && animationFrame == 0 &&
            scriptCounterF00 < g_OptionsModeAt006714D0 * 3 + 10) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        if (animationStage == 10 && animationFrame == 0 && scriptCounterF00 < 6) {
            ++scriptCounterF00;
            ResetSecondaryCounter(8);
        }
        return;
    }

    case 0x2E6: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
        }
        if (animationStage > 17 && animationStage < 22 && animationFrame == 0) {
            scriptCounterF02 = static_cast<short>(RecordedRange(0, 4));
            field314 = static_cast<float>(RecordedRange(0, 0x167));
            for (int i = 0; i < static_cast<int>(g_OptionsModeAt006714D0) + 1; ++i) {
                PlaySound(0x14);
                field318 = static_cast<float>(i * 5);
                field31C = 3.0f;
                SpawnBattleEffect(
                    static_cast<short>(scriptCounterF02 + 0x38E),
                    static_cast<float>(facing * 65) + x,
                    (y) + GeometryConstants::EightyFive, facing, 1);
            }
        }
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(0x1C);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(60, 180) -
                g_OptionsModeAt006714D0 * 20);
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = static_cast<float>(RecordedRange(0, 8)) +
                FloatConstants::Four;
            velocityY = static_cast<float>(RecordedRange(0, 5)) +
                GeometryConstants::Eight;
            field05C = 0.2f;
        }
        if (animationStage == 0x16 && animationFrame == 0 &&
            scriptCounterF00 < g_OptionsModeAt006714D0 * 3 + 10) {
            ++scriptCounterF00;
            ResetSecondaryCounter(0x15);
        }
        if (animationStage == 0x1C && animationFrame == 0)
            ResetSecondaryCounter(0x1A);
        return;
    }

    case 0x2E7: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
        }
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetSecondaryCounter(0x0E);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(3);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = static_cast<float>(RecordedRange(0, 8)) +
                FloatConstants::Four;
            velocityY = static_cast<float>(RecordedRange(0, 5)) +
                GeometryConstants::Eight;
            field05C = 0.2f;
        }
        if (animationStage == 14 && animationFrame == 0)
            ResetSecondaryCounter(12);
        return;
    }

    case 0x2EF: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame < 45) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 4) {
                SpawnAuxEffect(0x3E,
                    x - static_cast<float>(facing * 23),
                    (y) + GeometryConstants::Ninety, 1, 1);
                scriptCounterF02 = 0;
            }
        }
        if (animationStage > 5 && animationStage < 12)
            SetCameraShake(5.0f);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x329,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(0x78, 0xB4) -
                g_OptionsModeAt006714D0 * 20);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x399,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::HundredThirty, facing, 0);
            SpawnBattleEffect(0x329,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::HundredThirty, facing, 0);
            SpawnBattleEffect(0x32A,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            SpawnBattleEffect(0x353,
                x - static_cast<float>(facing * 82),
                (y) + GeometryConstants::HundredThirtyTwo, facing, 1);
            PlaySound(0);
        }
        if (animationStage == 12 && animationFrame == 0 &&
            scriptCounterF00 < g_OptionsModeAt006714D0 * 2 + 4) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
            SpawnBattleEffect(0x32A,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        return;
    }

    case 0x2F0: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (animationStage == 2 && animationFrame < 45) {
            ++scriptCounterF02;
            if (scriptCounterF02 > 4) {
                SpawnAuxEffect(0x3E,
                    x - static_cast<float>(facing * 23),
                    (y) + GeometryConstants::Ninety, 1, 1);
                scriptCounterF02 = 0;
            }
        }
        if (animationStage > 5 && animationStage < 12)
            SetCameraShake(10.0f);
        if (animationStage == 5 && animationFrame == 0) {
            SpawnBattleEffect(0x329,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetPrimaryCounters(0);
            aiCardTimer = static_cast<short>(RecordedRange(0x78, 0xB4) -
                g_OptionsModeAt006714D0 * 20);
        }
        if (animationStage == 6 && animationFrame == 0) {
            SpawnBattleEffect(0x39A,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::HundredThirty, facing, 0);
            SpawnBattleEffect(0x329,
                x - static_cast<float>(facing * 80),
                (y) + GeometryConstants::HundredThirty, facing, 0);
            SpawnBattleEffect(0x32A,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
            SpawnBattleEffect(0x353,
                x - static_cast<float>(facing * 82),
                (y) + GeometryConstants::HundredThirtyTwo, facing, 1);
            PlaySound(0);
        }
        if (animationStage == 12 && animationFrame == 0 &&
            scriptCounterF00 < g_OptionsModeAt006714D0 * 2 + 4) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
            SpawnBattleEffect(0x32A,
                static_cast<float>(facing * 64) + x,
                (y) + GeometryConstants::Ninety, facing, 1);
        }
        return;
    }

    case 0x2F2: {
        if (animationStage == 0 && animationFrame == 0) {
            collisionResult = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            ClearMotionFields();
        }
        if (y > FloatConstants::Zero) {
            velocityY -= field05C;
            if (y + velocityY <= FloatConstants::Zero) {
                ResetPrimaryCounters(10);
                y = 0.0f;
                ClearMotionFields();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(12);
            aiCardTimer = 0;
        }
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = static_cast<float>(RecordedRange(0, 8)) +
                GeometryConstants::Eight;
            velocityY = static_cast<float>(RecordedRange(0, 5)) +
                FloatConstants::Ten;
            field05C = 0.5f;
        }
        return;
    }

    case 0x2F8: {
        if (animationStage == 0 && animationFrame == 0) {
            ClearMotionFields();
            remainingHits = 1;
            collisionResult = 0;
            field3AC = 0;
        }
        if (RecordedRange(0, 100) < 40 && animationStage > 3 && animationStage < 8) {
            SpawnBattleEffect(0x330,
                (x) + GeometryConstants::Thirty - static_cast<float>(RecordedRange(0, 0x3C)),
                (y) + GeometryConstants::Forty + static_cast<float>(RecordedRange(0, 0x8C)), facing, 1);
        }
        if (animationStage == 7 && y > GeometryConstants::NineHundredTwenty) {
            y = 920.0f;
            ResetPrimaryCounters(0x2F9);
            ClearMotionFields();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 3 && animationFrame == 0)
            PlaySound(2);
        if (animationStage == 4 && animationFrame == 0) {
            velocityX = 0.0f;
            velocityY = 15.0f;
            SpawnAuxEffect(0x7F, x, y, facing, 1);
        }
        return;
    }

    case 0x2F9: {
        if (animationStage == 0 && animationFrame == 0) {
            facing = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            fieldF04 = 0;
        }
        --scriptCounterF00;
        if (animationStage == 1 && animationFrame == 0) {
            if (fieldF04 == 0 && g_OptionsModeAt006714D0 < 2) {
                SpawnBattleEffect(
                    static_cast<short>(g_OptionsModeAt006714D0 + 0x39F),
                    x, 0.0f, 1, 1);
            }
            if (fieldF04 == 4 && g_OptionsModeAt006714D0 > 1) {
                SpawnBattleEffect(
                    static_cast<short>(g_OptionsModeAt006714D0 + 0x39F),
                    opponent->x, 0.0f, 1, 1);
            }
        }
        velocityX = 0.0f;
        if (x < opponent->x - GeometryConstants::Fifty)
            velocityX = static_cast<float>(g_OptionsModeAt006714D0) *
                FloatConstants::Half + FloatConstants::One;
        if ((opponent->x) + GeometryConstants::Fifty < x)
            velocityX = GeometryConstants::NegativeOne -
                static_cast<float>(g_OptionsModeAt006714D0) *
                FloatConstants::Half;
        if (animationStage == 1 && y > GeometryConstants::NineHundredTwenty) {
            y = 920.0f;
            ResetPrimaryCounters(0x2F9);
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (scriptCounterF02 > 0 && g_OptionsModeAt006714D0 < 2) {
                ResetPrimaryCounters(0x2FA);
                return;
            }
            if (scriptCounterF02 > 1 && g_OptionsModeAt006714D0 > 1) {
                ResetPrimaryCounters(0x2FA);
                return;
            }
            ResetSecondaryCounter(1);
            ++fieldF04;
            return;
        }
        if (animationStage == 1 && animationFrame == 0) {
            SpawnBattleEffect(
                static_cast<short>(g_OptionsModeAt006714D0 + 0x39F),
                x, 0.0f, 1, 1);
        }
        return;
    }

    case 0x2FA: {
        if (animationStage == 0 && animationFrame == 0) {
            facing = 1;
            scriptCounterF00 = 0;
            scriptCounterF02 = 0;
            velocityX = 0.0f;
        }
        --scriptCounterF00;
        if (animationStage < 2) {
            velocityY -= FloatConstants::FiftyFiveHundredths;
            if (y + velocityY <= FloatConstants::Zero) {
                y = 0.0f;
                ClearMotionFields();
                ResetSecondaryCounter(2);
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 2 && animationFrame == 0)
            ResetSecondaryCounter(0);
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
            Fighter::PlaySharedSound(0x17);
            SpawnBattleEffect(0x3E5, x,
                (y) + GeometryConstants::Hundred, facing, 1);
        }
        if (animationStage == 8 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(6);
        }
        return;
    }

    case 0x31C: {
        if (animationStage == 0 && animationFrame == 0) {
            scriptCounterF00 = 0;
            collisionResult = 1;
            ClearMotionFields();
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        if (animationStage == 16 && animationFrame == 0) {
            BeginFadeParameters(0);
            SelectResourceParameters();
            Fighter::PlaySharedSound(0x17);
        }
        if (animationStage == 20 && animationFrame == 0 && scriptCounterF00 < 8) {
            ++scriptCounterF00;
            ResetSecondaryCounter(0x12);
            field3CF = 1;
        }
        return;
    }

    default:
        if (AdvanceNestedFrame() == animationStageCount)
            ResetPrimaryCounters(0);
        break;

    advanceNestedAndReturn:
        AdvanceNestedFrame();
    }
}
