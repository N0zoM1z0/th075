#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "engine/GameSharedState.hpp"
// Reconstruction of ReimuObject::Advance at 00476A40.
#include "characters/CharacterObject.hpp"
#include "characters/reimu/ReimuFighter.hpp"

extern float __cdecl AngleAt00483300(float y, float x);

// Read-only data shared by the projectile and effect actions.
extern const float g_ReimuObjectOwnerYOffsetAt00659080;

void ReimuObject::Advance()
{
    if (owner->opponent->opponentFreezeSnapshot != 0)
        return;
    if (owner->opponentFreezeSnapshot != 0 && field08A == 0)
        return;
    if (hitstopFrames != 0) {
        --hitstopFrames;
        return;
    }
    switch (action) {
    // 0x320 homes after stage 1. 0xDA holds the target heading, 0xDC steers toward it.
    case 800:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty) {
            ClearFrameInfo();
            return;
        }
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 10;
            field0DA = 0;
            field0DE = 0;
            field0DC = static_cast<short>(field0C8);
        }
        if (animationStage > 1) {
            field0DA = static_cast<short>(AngleAt00483300(
                (owner->opponent->y - y) + GeometryConstants::Hundred,
                (owner->opponent->x - x) * facing) /
                GeometryConstants::RadiansPerDegree);
            if (field0DA > field0DC + 10) {
                field0DC = field0DC + 2;
            }
            if (field0DA < field0DC - 10) {
                field0DC = field0DC - 2;
            }
            if (field0DC > 0x5A) {
                field0DC = 0x5A;
            }
            if (field0DC < -0x5A) {
                field0DC = -0x5A;
            }
        }
        SetPolarVelocity(static_cast<float>(field0DC),
            static_cast<float>(field0D8) * FloatConstants::OneTenth +
            GeometryConstants::Six);
        field0DE = field0DE + 0x1E;
        field0D8 = field0D8 + 2;
        if (animationStage > 0 && field0DA < 0x3C) {
            if ((owner->opponent->y) + GeometryConstants::Hundred < y) {
                field0C8 = (field0C8) + FloatConstants::Two;
            }
            if (y < (owner->opponent->y) + GeometryConstants::Hundred) {
                field0C8 = field0C8 - FloatConstants::Two;
            }
            ++field0DA;
        }
        x = facing * velocityX + x;
        y = y - velocityY;
        rotationZ = (rotationZ) + GeometryConstants::Eight;
        if (collisionResult != 0 && collisionResult != 6) {
            ResetSecondaryCounter(3);
        }
        if (animationStage > 2) {
            if (color[0] >= 0x19) {
                color[0] -= 0x19;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;


    // 0x321 and 0x322 track the opponent early and can spawn the 0x325 aftereffect.
    case 801:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred) {
            ClearFrameInfo();
            return;
        }
        else if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                if (field0C8 == FloatConstants::Zero) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = 5.0f;
                    velocityX = 11.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::One) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = 6.0f;
                    velocityX = 8.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::Two) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = -5.0f;
                    velocityX = 11.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::Three) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = -6.0f;
                    velocityX = 8.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
            }
            x = facing * velocityX + x;
            y = y + velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 1 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                if (field0C8 == FloatConstants::Zero) {
                    owner->SpawnBattleEffect(
                        0x325, x - facing * 30, field0CC, facing, 1);
                }
            }
        }
        break;

    case 802:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred) {
            ClearFrameInfo();
            return;
        }
        else if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                if (field0C8 == FloatConstants::Zero) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = 5.0f;
                    velocityX = 25.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::One) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = 6.0f;
                    velocityX = 22.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::Two) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = -5.0f;
                    velocityX = 25.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::Three) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = -6.0f;
                    velocityX = 22.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
            }
            x = facing * velocityX + x;
            y = y + velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 1 && animationFrame == 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                if (field0C8 == FloatConstants::Zero) {
                    owner->SpawnBattleEffect(
                        0x325, x - facing * 30, field0CC, facing, 1);
                }
            }
        }
        break;

    case 804:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 0;
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.5f;
                scaleY = 1.5f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                remainingHits = 1;
                collisionResult = 0;
            }
            if (collisionResult == 4 && field0D8 < 6) {
                remainingHits = 1;
                ++field0D8;
                collisionResult = 0;
            }
            if (remainingHits == 0 && animationStage == 1) {
                ResetSecondaryCounter(2);
                return;
            }
            else {
                if (animationStage > 1 && color[0] > 10) {
                    color[0] = color[0] - 10;
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
            }
        }
        break;

    case 805:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        scaleX = (scaleX) + FloatConstants::OneFifth;
        scaleY = (scaleY) + FloatConstants::OneFifth;
        if (color[0] > 20 && animationStage > 0) {
            color[0] = color[0] - 20;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 1 && animationFrame == 0) {
            owner->SpawnBattleEffect(0x324, x, y, facing, 1);
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 8.0f;
            scaleY = 8.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationY = 60.0f;
        }
        break;

    // 0x327 starts with a speed of 0x5DC hundredths in 0xDA and uses 0xC8 as an eight-way selector.
    case 807:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = 0x5DC;
                if (field0C8 == FloatConstants::Zero) {
                    field0DC = 0;
                }
                if (field0C8 == FloatConstants::One) {
                    field0DC = 0x2D;
                }
                if (field0C8 == FloatConstants::Two) {
                    field0DC = 0x5A;
                }
                if (field0C8 == FloatConstants::Three) {
                    field0DC = 0x87;
                }
                if (field0C8 == FloatConstants::Four) {
                    field0DC = 0xB4;
                }
                if (field0C8 == FloatConstants::Five) {
                    field0DC = 0xE1;
                }
                if (field0C8 == GeometryConstants::Six) {
                    field0DC = 0x10E;
                }
                if (field0C8 == GeometryConstants::Seven) {
                    field0DC = 0x13B;
                }
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
                // Convert to the projectile angle unit before narrowing.
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree);
            }
            if (animationStage == 1) {
                owner->SpawnBattleEffect(0x335,
                    ((x) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)),
                    ((y) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)), facing, 1);
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x3C;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 100;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 808:
        facing = owner->facing;
        if (owner->action == 0x131 && owner->animationStage < 4 &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x91);
            y = (owner->y) + GeometryConstants::SixtySix;
        }
        else if (animationStage != 1) {
            ResetSecondaryCounter(1);
        }
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationY = facing * 0x46;
            rotationX = 15.0f;
            field0D8 = 1;
        }
        rotationZ = (rotationZ) + FloatConstants::Five;
        if (animationStage > 0) {
            if (color[0] > 0x1E) {
                color[0] -= 0x1E;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    // 0x329 and 0x32A repeat the 0x327 startup with their own child effects.
    case 809:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = 0x5DC;
                if (field0C8 == FloatConstants::Zero) {
                    field0DC = 0;
                }
                if (field0C8 == FloatConstants::One) {
                    field0DC = 0x2D;
                }
                if (field0C8 == FloatConstants::Two) {
                    field0DC = 0x5A;
                }
                if (field0C8 == FloatConstants::Three) {
                    field0DC = 0x87;
                }
                if (field0C8 == FloatConstants::Four) {
                    field0DC = 0xB4;
                }
                if (field0C8 == FloatConstants::Five) {
                    field0DC = 0xE1;
                }
                if (field0C8 == GeometryConstants::Six) {
                    field0DC = 0x10E;
                }
                if (field0C8 == GeometryConstants::Seven) {
                    field0DC = 0x13B;
                }
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
                // Convert to the projectile angle unit before narrowing.
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree);
            }
            if (animationStage == 1) {
                owner->SpawnBattleEffect(0x336,
                    ((x) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)),
                    ((y) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)), facing, 1);
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x3C;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 100;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 810:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = 0x5DC;
                if (field0C8 == FloatConstants::Zero) {
                    field0DC = 0;
                }
                if (field0C8 == FloatConstants::One) {
                    field0DC = 0x2D;
                }
                if (field0C8 == FloatConstants::Two) {
                    field0DC = 0x5A;
                }
                if (field0C8 == FloatConstants::Three) {
                    field0DC = 0x87;
                }
                if (field0C8 == FloatConstants::Four) {
                    field0DC = 0xB4;
                }
                if (field0C8 == FloatConstants::Five) {
                    field0DC = 0xE1;
                }
                if (field0C8 == GeometryConstants::Six) {
                    field0DC = 0x10E;
                }
                if (field0C8 == GeometryConstants::Seven) {
                    field0DC = 0x13B;
                }
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
                // Convert to the projectile angle unit before narrowing.
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree);
            }
            if (animationStage == 1) {
                owner->SpawnBattleEffect(0x337,
                    ((x) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)),
                    ((y) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)), facing, 1);
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x3C;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 100;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 811:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
        }
        ++field0D8;
        SetPolarVelocity(field0C8,
            static_cast<float>(field0D8) * FloatConstants::OneTenth + field0CC);
        if (collisionResult != 0 && animationStage == 1) {
            ResetSecondaryCounter(2);
            return;
        }
        x = facing * velocityX + x;
        y = y - velocityY;
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::SixHundredForty ||
            y < GeometryConstants::NegativeHundredTwenty) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage > 1) {
                if (color[0] >= 0x19) {
                    color[0] = color[0] - 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 812:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 4;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
            }
            SetPolarVelocity(field0C8,
                static_cast<float>(field0DA) * FloatConstants::OneTenth +
                FloatConstants::Ten);
            field0DE = field0DE + 0x1E;
            ++field0DA;
            if (animationStage > 0 && field0DC < 0x5A) {
                if ((owner->opponent->y) + GeometryConstants::Hundred < y) {
                    field0C8 = (field0C8) + FloatConstants::One;
                }
                if (y < (owner->opponent->y) + GeometryConstants::Hundred) {
                    field0C8 = field0C8 - FloatConstants::One;
                }
                ++field0DC;
            }
            x = facing * velocityX + x;
            y = y + velocityY;
            rotationZ = (rotationZ) + GeometryConstants::Twelve;
            if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4) && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] = color[0] - 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 3 && animationFrame == 0 &&
                field0D8 < 0xC && remainingHits > 0) {
                ResetSecondaryCounter(2);
                ++field0D8;
                collisionResult = 0;
            }
        }
        break;

    case 813:
        if (owner->action == 0x1FA || owner->action == 0x1FB) {
            x = owner->x;
            y = owner->y;
        }
        if ((owner->action != 0x1FA || owner->hitstopFrames <= 0) &&
            AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 814:
        if (owner->action == 0x2C0) {
            x = owner->x + static_cast<float>(facing * 0xE4);
            y = (owner->y) + g_ReimuObjectOwnerYOffsetAt00659080;
        }
        if (animationStage < 0x39 &&
            ((owner->action == 0x2C0 && owner->animationStage > 0x0C) ||
             owner->action != 0x2C0)) {
            scaleX = 3.0f;
            scaleY = 3.0f;
            owner->SpawnBattleEffect(0x32F, x, y, facing, 1);
            ResetSecondaryCounter(0x39);
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 99;
                collisionResult = 0;
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                field0DE = 0;
            }
            rotationZ = rotationZ - FloatConstants::Two;
            if (collisionResult != 0) {
                ++field0D8;
                if (field0D8 > 5) {
                    field0D8 = 0;
                    collisionResult = 0;
                }
            }
            if (animationStage > 0x38) {
                scaleX = (scaleX) * FloatConstants::FourFifths;
                scaleY = (scaleY) * FloatConstants::FourFifths;
            }
            if (animationStage == 0x3A) {
                if (color[0] >= 0x0F) {
                    color[0] = color[0] - 0x0F;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 0x39 && animationFrame == 0 &&
                owner->action == 0x2C0 && owner->animationStage < 0x0D) {
                ResetSecondaryCounter(0x1B);
            }
        }
        break;

    case 815:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        scaleX = (scaleX) + FloatConstants::ThreeTenths;
        scaleY = (scaleY) + FloatConstants::ThreeTenths;
        if (animationStage > 0) {
            if (color[0] >= 0x0F) {
                color[0] = color[0] - 0x0F;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 816:
        if (owner->action == 0x2BE) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage < 6 && owner->action != 0x2BE) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 4.0f;
                scaleY = 4.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                field0DE = 0;
            }
            if (animationStage == 6) {
                if (color[0] >= 7) {
                    color[0] = color[0] - 7;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 6 && animationFrame == 0) {
                owner->SpawnBattleEffect(0x331, x, y, facing, 1);
            }
        }
        break;

    case 817:
        if (animationStage == 0 && animationFrame == 0 && field0DC == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 99;
            collisionResult = 0;
            scaleX = 4.0f;
            scaleY = 4.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 1;
        }
        if (owner->action == 0x2BE) {
            x = owner->x;
            y = owner->y;
        }
        if (((owner->animationStage > 0x0B && owner->action == 0x2BE) ||
            owner->action != 0x2BE) && animationStage < 10) {
            ResetSecondaryCounter(animationStage + 10);
            return;
        }
        if (collisionResult != 0) {
            ++field0D8;
            if (field0D8 > 2) {
                field0D8 = 0;
                collisionResult = 0;
            }
        }
        if (animationStage > 9) {
            if (color[0] >= 5) {
                color[0] -= 5;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(10);
            return;
        }
        else if (animationStage == 10 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    // 0x332 drains the owner spirit gauge after stage 0x13.
    case 818:
        static_cast<ReimuFighter*>(owner)->spiritDrainObjectActive = 1;
        if (owner->action == 0x2C1 && animationStage < 0x13) {
            x = owner->x + static_cast<float>(facing * 0xE4);
            y = (owner->y) + g_ReimuObjectOwnerYOffsetAt00659080;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 999;
            collisionResult = 0;
            scaleX = 6.0f;
            scaleY = 6.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            field0DE = 0;
            field0E0 = 0;
            velocityX = 0.0f;
            velocityY = 0.0f;
        }
        if (animationStage > 0x13) {
            rotationZ = rotationZ - FloatConstants::Four;
            velocityX = (velocityX) + FloatConstants::OneFifth;
            if (owner->spirit > 5) {
                owner->UpdateGaugeTimer(4);
            } else {
                field0E0 = 1;
                owner->UpdateGaugeTimer(owner->spirit - 1);
            }
            if (field0E0 == 1) {
                remainingHits = 0;
                if (color[0] > 10) {
                    color[0] -= 10;
                } else {
                    ClearFrameInfo();
                    static_cast<ReimuFighter*>(owner)->spiritDrainObjectActive = 0;
                    return;
                }
            }
        }
        if (collisionResult != 0) {
            field0DA = 10;
            ++field0D8;
            if ((collisionResult == 6 || collisionResult == 4) && field0D8 < 2) {
                field0D8 = 2;
            }
            if (field0D8 >= 3) {
                field0D8 = 0;
                collisionResult = 0;
            }
        }
        if (field0DA > 0) {
            --field0DA;
            velocityX = 2.0f;
            if (field0DA == 0) {
                velocityX = 2.0f;
            }
        }
        x = facing * velocityX + x;
        y = y + velocityY;
        if (x < GeometryConstants::NegativeThreeHundredTwenty ||
            x > GeometryConstants::SixteenHundred) {
            ClearFrameInfo();
            static_cast<ReimuFighter*>(owner)->spiritDrainObjectActive = 0;
            return;
        }
        else {
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(0x28);
            }
            if (animationStage == 0x13 && animationFrame == 0) {
                velocityX = 2.0f;
                velocityY = 0.0f;
            }
        }
        break;

    case 819:
        if (owner->action == 0x2BF) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage < 6 && owner->action != 0x2BF) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 6.0f;
                scaleY = 6.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                field0DE = 0;
            }
            if (animationStage == 6) {
                if (color[0] >= 7) {
                    color[0] = color[0] - 7;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 6 && animationFrame == 0) {
                owner->SpawnBattleEffect(0x334, x, y, facing, 1);
            }
        }
        break;

    case 820:
        if (animationStage == 0 && animationFrame == 0 && field0DC == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 99;
            collisionResult = 0;
            scaleX = 6.0f;
            scaleY = 6.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 1;
        }
        if (owner->action == 0x2BF) {
            x = owner->x;
            y = owner->y;
        }
        if (((owner->animationStage > 0x0B && owner->action == 0x2BF) ||
            owner->action != 0x2BF) && animationStage < 22) {
            ResetSecondaryCounter(animationStage + 22);
            return;
        }
        if (collisionResult != 0) {
            ++field0D8;
            if (field0D8 > 2) {
                field0D8 = 0;
                collisionResult = 0;
            }
        }
        if (animationStage > 21) {
            if (color[0] >= 5) {
                color[0] -= 5;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(0x16);
            return;
        }
        else if (animationStage == 0x16 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;

    case 821:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if (animationStage == 0) {
            scaleX = scaleX - FloatConstants::OneTenth;
            scaleY = scaleY - FloatConstants::OneTenth;
        }
        if (animationStage == 1) {
            scaleX = scaleX - FloatConstants::OneTenth;
            scaleY = scaleY - FloatConstants::OneTenth;
            color[0] = color[0] - 0x32;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 822:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if (animationStage == 0) {
            scaleX = scaleX - FloatConstants::OneTenth;
            scaleY = scaleY - FloatConstants::OneTenth;
        }
        if (animationStage == 1) {
            scaleX = scaleX - FloatConstants::OneTenth;
            scaleY = scaleY - FloatConstants::OneTenth;
            color[0] = color[0] - 0x32;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 823:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if (animationStage == 0) {
            scaleX = scaleX - FloatConstants::OneTenth;
            scaleY = scaleY - FloatConstants::OneTenth;
        }
        if (animationStage == 1) {
            scaleX = scaleX - FloatConstants::OneTenth;
            scaleY = scaleY - FloatConstants::OneTenth;
            color[0] = color[0] - 0x32;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 824:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationX = 75.0f;
            velocityX = 20.0f;
            remainingHits = 3;
            field0D8 = 0;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
        }
        if (remainingHits == 0 && animationStage == 2) {
            ResetSecondaryCounter(3);
            return;
        }
        else {
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (rotationZ > GeometryConstants::DegreesPerTurn) {
                rotationX = rotationX - GeometryConstants::DegreesPerTurn;
            }
            if (animationStage < 3) {
                velocityX = velocityX - FloatConstants::One;
                if (velocityX < FloatConstants::Half) {
                    velocityX = 0.5f;
                }
            }
            if (animationStage == 3) {
                color[0] = color[0] - 10;
                if (color[0] <= 0) {
                    color[0] = 0;
                    ClearFrameInfo();
                    break;
                }
            }
            x = facing * velocityX + x;
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 3 && animationFrame == 0 &&
                field0D8 < 6) {
                ++field0D8;
                ResetSecondaryCounter(2);
                collisionResult = 0;
            }
        }
        break;

    case 825:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationX = 75.0f;
            velocityX = 40.0f;
            remainingHits = 3;
            field0D8 = 0;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
        }
        if (remainingHits == 0 && animationStage == 2) {
            ResetSecondaryCounter(3);
            return;
        }
        else {
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (rotationZ > GeometryConstants::DegreesPerTurn) {
                rotationX = rotationX - GeometryConstants::DegreesPerTurn;
            }
            if (animationStage < 3) {
                velocityX = velocityX - FloatConstants::Two;
                if (velocityX < FloatConstants::Half) {
                    velocityX = 0.5f;
                }
            }
            if (animationStage == 3) {
                color[0] = color[0] - 10;
                if (color[0] <= 0) {
                    color[0] = 0;
                    ClearFrameInfo();
                    break;
                }
            }
            x = facing * velocityX + x;
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 3 && animationFrame == 0 &&
                field0D8 < 6) {
                ++field0D8;
                ResetSecondaryCounter(2);
                collisionResult = 0;
            }
        }
        break;

    case 826:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 2.0f;
            scaleY = 2.0f;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationX = 75.0f;
            velocityX = 60.0f;
            remainingHits = 3;
            field0D8 = 0;
        }
        if (collisionResult == 4) {
            collisionResult = 0;
        }
        if (remainingHits == 0 && animationStage == 2) {
            ResetSecondaryCounter(3);
            return;
        }
        else {
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (rotationZ > GeometryConstants::DegreesPerTurn) {
                rotationX = rotationX - GeometryConstants::DegreesPerTurn;
            }
            if (animationStage < 3) {
                velocityX = velocityX - FloatConstants::Three;
                if (velocityX < FloatConstants::Half) {
                    velocityX = 0.5f;
                }
            }
            if (animationStage == 3) {
                color[0] = color[0] - 10;
                if (color[0] <= 0) {
                    color[0] = 0;
                    ClearFrameInfo();
                    break;
                }
            }
            x = facing * velocityX + x;
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 3 && animationFrame == 0 &&
                field0D8 < 6) {
                ++field0D8;
                ResetSecondaryCounter(2);
                collisionResult = 0;
            }
        }
        break;

    case 827:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            SetPolarVelocity(field0C8, field0CC);
            field0D8 = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
        }
        ++field0D8;
        if (animationStage < 3) {
            SetPolarVelocity(field0C8, field0CC);
        }
        if (collisionResult == 1 || collisionResult == 2 || collisionResult == 4) {
            if (animationStage == 1 && collisionResult == 1) {
                ResetSecondaryCounter(2);
                return;
            }
            if (animationStage == 1) {
                ResetSecondaryCounter(3);
                velocityX = -8.0f;
                velocityY = -10.0f;
                return;
            }
        }
        x = facing * velocityX + x;
        y = y - velocityY;
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::SixHundredForty ||
            y < GeometryConstants::NegativeHundredTwenty) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                    ClearFrameInfo();
                    return;
                }
            }
            if (animationStage == 3) {
                rotationZ = (rotationZ) + GeometryConstants::Thirty;
                velocityY = (velocityY) + FloatConstants::HalfDouble;
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 828:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = 2000;
                if (field0C8 == FloatConstants::Zero) {
                    field0DC = 0;
                }
                if (field0C8 == FloatConstants::One) {
                    field0DC = 0x2D;
                }
                if (field0C8 == FloatConstants::Two) {
                    field0DC = 0x5A;
                }
                if (field0C8 == FloatConstants::Three) {
                    field0DC = 0x87;
                }
                if (field0C8 == FloatConstants::Four) {
                    field0DC = 0xB4;
                }
                if (field0C8 == FloatConstants::Five) {
                    field0DC = 0xE1;
                }
                if (field0C8 == GeometryConstants::Six) {
                    field0DC = 0x10E;
                }
                if (field0C8 == GeometryConstants::Seven) {
                    field0DC = 0x13B;
                }
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1) {
                owner->SpawnBattleEffect(0x335,
                    ((x) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)),
                    ((y) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)), facing, 1);
            }
            if (collisionResult != 0 && animationStage == 1 && remainingHits == 0) {
                owner->SetCameraShake(5.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 3.5f;
                scaleY = 3.5f;
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneFifth;
                scaleY = (scaleY) + FloatConstants::OneFifth;
                if (scaleX > FloatConstants::OneAndHalf) {
                    scaleX = 1.5f;
                    scaleY = 1.5f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 100;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::ThreeTenths;
                scaleY = scaleY - FloatConstants::ThreeTenths;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            if (animationStage < 2) {
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            }
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                if (animationStage == 1 && animationFrame == 0) {
                    remainingHits = 3;
                    collisionResult = 0;
                    field0DC = static_cast<short>(AngleAt00483300(
                        ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                        (owner->opponent->x - x) * facing) /
                        GeometryConstants::RadiansPerDegree);
                }
                if (animationStage == 2 && animationFrame == 0) {
                    ResetSecondaryCounter(1);
                    collisionResult = 0;
                }
            }
        }
        break;

    case 829:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = 2000;
                if (field0C8 == FloatConstants::Zero) {
                    field0DC = 0;
                }
                if (field0C8 == FloatConstants::One) {
                    field0DC = 0x2D;
                }
                if (field0C8 == FloatConstants::Two) {
                    field0DC = 0x5A;
                }
                if (field0C8 == FloatConstants::Three) {
                    field0DC = 0x87;
                }
                if (field0C8 == FloatConstants::Four) {
                    field0DC = 0xB4;
                }
                if (field0C8 == FloatConstants::Five) {
                    field0DC = 0xE1;
                }
                if (field0C8 == GeometryConstants::Six) {
                    field0DC = 0x10E;
                }
                if (field0C8 == GeometryConstants::Seven) {
                    field0DC = 0x13B;
                }
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1) {
                owner->SpawnBattleEffect(0x336,
                    ((x) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)),
                    ((y) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)), facing, 1);
            }
            if (collisionResult != 0 && animationStage == 1 && remainingHits == 0) {
                owner->SetCameraShake(5.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 3.5f;
                scaleY = 3.5f;
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneFifth;
                scaleY = (scaleY) + FloatConstants::OneFifth;
                if (scaleX > FloatConstants::OneAndHalf) {
                    scaleX = 1.5f;
                    scaleY = 1.5f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 100;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::ThreeTenths;
                scaleY = scaleY - FloatConstants::ThreeTenths;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            if (animationStage < 2) {
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            }
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                if (animationStage == 1 && animationFrame == 0) {
                    remainingHits = 3;
                    collisionResult = 0;
                    field0DC = static_cast<short>(AngleAt00483300(
                        ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                        (owner->opponent->x - x) * facing) /
                        GeometryConstants::RadiansPerDegree);
                }
                if (animationStage == 2 && animationFrame == 0) {
                    ResetSecondaryCounter(1);
                    collisionResult = 0;
                }
            }
        }
        break;

    case 830:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (collisionResult == 6) {
                collisionResult = 0;
                remainingHits = 1;
            }
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = 2000;
                if (field0C8 == FloatConstants::Zero) {
                    field0DC = 0;
                }
                if (field0C8 == FloatConstants::One) {
                    field0DC = 0x2D;
                }
                if (field0C8 == FloatConstants::Two) {
                    field0DC = 0x5A;
                }
                if (field0C8 == FloatConstants::Three) {
                    field0DC = 0x87;
                }
                if (field0C8 == FloatConstants::Four) {
                    field0DC = 0xB4;
                }
                if (field0C8 == FloatConstants::Five) {
                    field0DC = 0xE1;
                }
                if (field0C8 == GeometryConstants::Six) {
                    field0DC = 0x10E;
                }
                if (field0C8 == GeometryConstants::Seven) {
                    field0DC = 0x13B;
                }
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1) {
                owner->SpawnBattleEffect(0x337,
                    ((x) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)),
                    ((y) + GeometryConstants::Fifteen) - static_cast<float>(RecordedRange(0, 0x1E)), facing, 1);
            }
            if (collisionResult != 0 && animationStage == 1 && remainingHits == 0) {
                owner->SetCameraShake(5.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 3.5f;
                scaleY = 3.5f;
                velocityX = 0.0f;
                velocityY = 0.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneFifth;
                scaleY = (scaleY) + FloatConstants::OneFifth;
                if (scaleX > FloatConstants::OneAndHalf) {
                    scaleX = 1.5f;
                    scaleY = 1.5f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 100;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::ThreeTenths;
                scaleY = scaleY - FloatConstants::ThreeTenths;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            if (animationStage < 2) {
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            }
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                if (animationStage == 1 && animationFrame == 0) {
                    remainingHits = 3;
                    collisionResult = 0;
                    field0DC = static_cast<short>(AngleAt00483300(
                        ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                        (owner->opponent->x - x) * facing) /
                        GeometryConstants::RadiansPerDegree);
                }
                if (animationStage == 2 && animationFrame == 0) {
                    ResetSecondaryCounter(1);
                    collisionResult = 0;
                }
            }
        }
        break;

    case 831:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                if (field0C8 == FloatConstants::Zero) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = 3.0f;
                    velocityX = 11.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::One) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = 6.0f;
                    velocityX = 8.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::Two) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = -3.0f;
                    velocityX = 11.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
                if (field0C8 == FloatConstants::Three) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    velocityY = -6.0f;
                    velocityX = 8.0f;
                    rotationZ = -AngleAt00483300(velocityY, velocityX) /
                        GeometryConstants::RadiansPerDegree;
                }
            }
            x = facing * velocityX + x;
            y = y + velocityY;
            if (AdvanceNestedFrame() == animationStageCount) {
                owner->SpawnBattleEffect(0x340, x, y, facing, 1);
                ClearFrameInfo();
            }
        }
        break;

    case 832:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 4) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            velocityX = 1.0f;
            velocityY = 0.0f;
            remainingHits = 2;
            collisionResult = 0;
        }
        if ((owner->opponent->y) + GeometryConstants::Hundred < y) {
            velocityY = velocityY - FloatConstants::TwoHundredths;
        }
        if (y <= (owner->opponent->y) + GeometryConstants::Hundred) {
            velocityY = (velocityY) + FloatConstants::TwoHundredths;
        }
        if (velocityY > FloatConstants::Two) {
            velocityY = 2.0f;
        }
        if (velocityY < GeometryConstants::NegativeTwo) {
            velocityY = -2.0f;
        }
        velocityX = (velocityX) + FloatConstants::OneTwentieth;
        if (field0D8 <= 0) {
            collisionResult = 0;
            field0D8 = 10;
        }
        --field0D8;
        x = facing * velocityX + x;
        y = y + velocityY;
        if (animationFrame == 0) {
            owner->SpawnBattleEffect(0x341,
                ((x) - FloatConstants::Ten) + static_cast<float>(RecordedRange(0, 0x14)),
                ((y) - FloatConstants::Ten) + static_cast<float>(RecordedRange(0, 0x14)), facing, 1);
        }
        if (animationFrame == 0) {
            field0DA = static_cast<short>(RecordedRange(0, 0x14));
            scaleX = static_cast<float>(field0DA) * FloatConstants::OneHundredth +
                FloatConstants::NineTenths;
            scaleY = static_cast<float>(field0DA) * FloatConstants::OneHundredth +
                FloatConstants::NineTenths;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            if (field0DC < 0x3C && remainingHits > 0) {
                ResetSecondaryCounter(1);
                ++field0DC;
            }
            else {
                ClearFrameInfo();
            }
        }
        break;

    case 833:
        facing = owner->facing;
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.8f;
            scaleY = 0.8f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 1;
            velocityY = 4.0f;
            velocityX = 0.0f;
        }
        velocityY = velocityY - FloatConstants::OneTenth;
        x = facing * velocityX + x;
        y = y + velocityY;
        if (color[0] > 0x0D) {
            color[0] -= 0x0D;
        } else {
            color[0] = 0;
        }
        scaleX = (scaleX) * FloatConstants::NinetyFourHundredths;
        scaleY = (scaleY) * FloatConstants::NinetyFourHundredths;
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 834:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty) {
            ClearFrameInfo();
            return;
        }
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        if (owner->action > 0x31 && owner->action < 0x96 && animationStage < 2) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
            if (owner->fieldEFA > 0x19) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
            }
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 10;
            field0DA = 0;
            field0DE = 0;
            field0DC = static_cast<short>(field0C8);
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth +
                FloatConstants::Ten);
        }
        if (animationStage > 0) {
            field0DA = static_cast<short>(AngleAt00483300(
                (owner->opponent->y - y) + GeometryConstants::Hundred,
                (owner->opponent->x - x) * facing) /
                GeometryConstants::RadiansPerDegree);
            if (field0DA > field0DC + 10) {
                field0DC = field0DC + 1;
            }
            if (field0DA < field0DC - 10) {
                field0DC = field0DC - 1;
            }
            if (field0DC > 0x5A) {
                field0DC = 0x5A;
            }
            if (field0DC < -0x5A) {
                field0DC = -0x5A;
            }
        }
        SetPolarVelocity(static_cast<float>(field0DC),
            static_cast<float>(field0D8) * FloatConstants::OneTenth +
            FloatConstants::Ten);
        rotationZ = AngleAt00483300(velocityY, velocityX) /
            GeometryConstants::RadiansPerDegree;
        field0DE = field0DE + 0x1E;
        field0D8 = field0D8 + 2;
        x = facing * velocityX + x;
        y = y - velocityY;
        if (collisionResult != 0 && collisionResult != 6) {
            ResetSecondaryCounter(2);
        }
        if (animationStage > 1) {
            if (color[0] >= 0x19) {
                color[0] -= 0x19;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 900:
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = static_cast<short>(RecordedRange(0, 500) + 0x5DC);
                field0DC = static_cast<short>(field0C8);
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree);
            } else if (animationStage == 1) {
                // Keep the aim on later frames of the stage.
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x3C;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 0x32;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 901:
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = static_cast<short>(RecordedRange(0, 500) + 0x5DC);
                field0DC = static_cast<short>(field0C8);
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree);
            } else if (animationStage == 1) {
                // Keep the aim on later frames of the stage.
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x3C;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 0x32;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 902:
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = static_cast<short>(RecordedRange(0, 500) + 0x5DC);
                field0DC = static_cast<short>(field0C8);
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
                field0DC = static_cast<short>(AngleAt00483300(
                    ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree);
            } else if (animationStage == 1) {
                // Keep the aim on later frames of the stage.
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage == 0) {
                field0DA = field0DA - 0x3C;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 0x32;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 903:
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = static_cast<short>(RecordedRange(0, 400) + 300);
                field0DC = static_cast<short>(field0C8);
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
            } else if (animationStage == 1) {
                // Preserve the contact flags between updates.
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage < 2) {
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 0x32;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 904:
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = static_cast<short>(RecordedRange(0, 400) + 300);
                field0DC = static_cast<short>(field0C8);
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
            } else if (animationStage == 1) {
                // Preserve the contact flags between updates.
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage < 2) {
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 0x32;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 905:
        if (collisionResult == 6) {
            collisionResult = 0;
            remainingHits = 1;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                field0D8 = 1;
                field0DA = static_cast<short>(RecordedRange(0, 400) + 300);
                field0DC = static_cast<short>(field0C8);
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                rotationZ = 0.0f;
            }
            if (animationStage == 1 && animationFrame == 0) {
                remainingHits = 1;
                collisionResult = 0;
            } else if (animationStage == 1) {
                // Preserve the contact flags between updates.
            }
            if (collisionResult != 0 && animationStage == 1) {
                owner->SetCameraShake(2.0f);
                ResetSecondaryCounter(2);
                rotationX = 0.0f;
                rotationY = 0.0f;
                rotationZ = 0.0f;
                scaleX = 4.0f;
                scaleY = 4.0f;
                return;
            }
            if (animationStage < 2) {
                scaleX = (scaleX) + FloatConstants::OneTenth;
                scaleY = (scaleY) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }
            }
            if (animationStage == 1) {
                field0DA = field0DA + 0x32;
            }
            if (animationStage == 2) {
                field0DA = field0DA - 0x50;
                if (field0DA < 0) {
                    field0DA = 0;
                }
                scaleX = scaleX - FloatConstants::OneFifth;
                scaleY = scaleY - FloatConstants::OneFifth;
                color[0] = color[0] - 10;
                if (scaleX < FloatConstants::Zero) {
                    scaleX = 0.0f;
                    scaleY = 0.0f;
                }
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0DA) * FloatConstants::OneHundredth);
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Ten;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                y > GeometryConstants::TwelveHundredEighty ||
                y < GeometryConstants::NegativeThreeHundredTwenty ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 910:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 4.0f;
            scaleY = 4.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            field0DE = 0;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 6) {
                if (color[0] >= 7) {
                    color[0] -= 7;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
            if (animationStage == 6 && animationFrame == 0) {
                owner->SpawnBattleEffect(0x38F, x, y, facing, 1);
            }
        }
        break;

    case 911:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 0;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        if (color[0] >= 0x0F) {
            color[0] -= 0x0F;
        } else {
            ClearFrameInfo();
            return;
        }
        if (animationStage == 1 && animationFrame == 0) {
            owner->SpawnBattleEffect(0x390, x, y, 1, 1);
            owner->SpawnBattleEffect(0x390, x, y, -1, 1);
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;

    case 912:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 99;
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            velocityX = 1.5f;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            x = facing * velocityX + x;
            if (x > GeometryConstants::FourteenHundredEighty ||
                x < GeometryConstants::NegativeTwoHundred ||
                owner->spellTimer == 0) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(0);
            }
        }
        break;

    case 913:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0x50;
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0D8) * FloatConstants::OneTenth);
            }
            if (animationStage == 1) {
                if (field0D8 > 1) {
                    field0D8 = field0D8 - 4;
                }
                if (field0D8 < 1) {
                    field0D8 = 1;
                }
            }
            if (animationStage == 2) {
                field0D8 = field0D8 + 3;
            } else if (animationStage == 3) {
                // Hold the projectile speed during the fade.
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth);
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
            x = facing * velocityX + x;
            y = y - velocityY;
            if (animationStage < 3 && remainingHits != 0) {
                // Keep the current stage while contact is active.
            }
            if (animationStage < 3 && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 916:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                velocityX = (field0C8) + FloatConstants::Zero;
                velocityY = 3.0f;
            }
            if (animationStage == 1) {
                scaleX = (scaleX) + FloatConstants::OneTenth;
                if (scaleX > FloatConstants::One) {
                    scaleX = 1.0f;
                }
                scaleY = scaleX;
            }
            rotationZ = (rotationZ) + FloatConstants::Ten;
            x = facing * velocityX + x;
            y = y + velocityY;
            velocityY = velocityY - FloatConstants::Half;
            if (y + velocityY < FloatConstants::Zero) {
                y = 0.0f;
                velocityY = -velocityY;
                collisionResult = 0;
                remainingHits = 1;
            }
            if (collisionResult == 6) {
                remainingHits = 1;
                collisionResult = 0;
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 917:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 99;
                collisionResult = 0;
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                field0DE = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage > 0x13) {
                rotationZ = rotationZ - FloatConstants::Four;
                velocityX = (velocityX) + FloatConstants::OneTwentieth;
            }
            x = facing * velocityX + x;
            y = y + velocityY;
            if (collisionResult != 0) {
                ++field0D8;
                if (collisionResult == 6 || collisionResult == 4) {
                    field0D8 = 6;
                }
                if (field0D8 > 5) {
                    field0D8 = 0;
                    collisionResult = 0;
                }
            }
            if (x < GeometryConstants::NegativeThreeHundredTwenty ||
                x > GeometryConstants::SixteenHundred) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(0x1B);
            }
        }
        break;

    case 918:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 99;
                collisionResult = 0;
                scaleX = 6.0f;
                scaleY = 6.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = 0;
                field0DA = 0;
                field0DC = 0;
                field0DE = 0;
                velocityX = 0.0f;
                velocityY = 0.0f;
            }
            if (animationStage > 0x13) {
                rotationZ = rotationZ - FloatConstants::Four;
                velocityX = (velocityX) + FloatConstants::TwoHundredths;
            }
            if (collisionResult != 0) {
                ++field0D8;
                if (collisionResult == 6 || collisionResult == 4) {
                    field0D8 = 3;
                }
                if (field0D8 >= 3) {
                    field0D8 = 0;
                    collisionResult = 0;
                }
            }
            x = facing * velocityX + x;
            y = y + velocityY;
            if (x < GeometryConstants::NegativeThreeHundredTwenty ||
                x > GeometryConstants::SixteenHundred) {
                ClearFrameInfo();
                return;
            }
            else if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(0x28);
            }
        }
        break;

    case 919: {
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            break;
        }
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            field0DE = 0;
            field0E0 = 0;
        }
        --field0E0;
        --field0DE;
        rotationZ = (rotationZ) + GeometryConstants::Six;
        SetPolarVelocity(static_cast<float>(static_cast<ReimuFighter*>(owner)->fieldF24) + field0C8,
            static_cast<float>(static_cast<ReimuFighter*>(owner)->fieldF26));
        x = owner->x + velocityX;
        y = owner->y + velocityY + GeometryConstants::Hundred;
        if (static_cast<ReimuFighter*>(owner)->fieldF28 == 0 && owner->action == 0x303) {
            field0E0 = 0;
        }
        if (static_cast<ReimuFighter*>(owner)->fieldF28 == 1 && field0E0 <= 0) {
            owner->PlaySound(0);
            owner->field314 = 0.0f;
            owner->field318 = 60.0f;
            owner->SpawnBattleEffect(0x39F, x, y, owner->facing, 1);
            field0E0 = static_cast<short>(5 - g_OptionsModeAt006714D0);
        }
        if (static_cast<ReimuFighter*>(owner)->fieldF28 == 2 && field0E0 <= 0) {
            owner->PlaySound(0);
            owner->field314 = -(static_cast<float>(static_cast<ReimuFighter*>(owner)->fieldF24) + field0C8) *
                static_cast<float>(facing);
            owner->field318 = 60.0f;
            owner->SpawnBattleEffect(0x39F, x, y, 1, 1);
            field0E0 = static_cast<short>(5 - g_OptionsModeAt006714D0);
        }
        if (static_cast<ReimuFighter*>(owner)->fieldF28 == 3 && field0DE <= 0) {
            owner->PlaySound(0x0D);
            owner->field314 = -(static_cast<float>(static_cast<ReimuFighter*>(owner)->fieldF24) + field0C8 +
                FloatConstants::Zero) * static_cast<float>(facing);
            owner->field318 = 100.0f;
            owner->SpawnBattleEffect(0x3A0, x, y, 1, 1);
            field0DE = 10;
        }
        if (static_cast<ReimuFighter*>(owner)->fieldF28 == 4 && field0DE <= 0) {
            owner->PlaySound(0x0D);
            owner->field314 = -(static_cast<float>(static_cast<ReimuFighter*>(owner)->fieldF24) + field0C8 +
                GeometryConstants::HundredEighty) * static_cast<float>(facing);
            owner->field318 = 40.0f;
            owner->SpawnBattleEffect(0x3A1, x, y, 1, 1);
            field0DE = 10;
        }
        if (owner->action == 0x304 && field0E0 <= 0) {
            owner->PlaySound(0);
            owner->field314 = -(static_cast<float>(static_cast<ReimuFighter*>(owner)->fieldF24) + field0C8) *
                static_cast<float>(facing);
            owner->field318 = 250.0f;
            owner->SpawnBattleEffect(0x3AC, x, y, 1, 1);
            field0E0 = 3;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;
    }

    case 927: {
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = static_cast<short>(field0CC);
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0D8) * FloatConstants::OneTenth);
            }
            if (animationStage == 1) {
                if (field0D8 > 1) {
                    field0D8 = field0D8 - 2;
                }
                if (field0D8 < 1) {
                    field0D8 = 1;
                }
            }
            if (animationStage == 2) {
                field0D8 = field0D8 + 3;
            } else if (animationStage == 3) {
                // Hold the projectile speed during the fade.
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth);
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
            x = facing * velocityX + x;
            y = y - velocityY;
            if (animationStage < 3 && remainingHits != 0) {
                // Keep the current stage while contact is active.
            }
            if (animationStage < 3 && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;
    }

    case 928: {
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = static_cast<short>(field0CC);
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0D8) * FloatConstants::OneTwentieth);
            }
            if (animationStage == 1) {
                if (field0D8 > 1) {
                    field0D8 = field0D8 - 2;
                }
                if (field0D8 < 1) {
                    field0D8 = 1;
                }
            }
            if (animationStage == 2) {
                field0D8 = field0D8 - 2;
            } else if (animationStage == 3) {
                // Hold the projectile speed during the fade.
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth);
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
            x = facing * velocityX + x;
            y = y - velocityY;
            if (animationStage < 3 && remainingHits != 0) {
                // Keep the current stage while contact is active.
            }
            if (animationStage < 3 && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;
    }

    case 929: {
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = static_cast<short>(field0CC);
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0D8) * FloatConstants::OneTenth);
            }
            if (animationStage == 1) {
                if (field0D8 > 1) {
                    field0D8 = field0D8 - 2;
                }
                if (field0D8 < 1) {
                    field0D8 = 1;
                }
            }
            if (animationStage == 2) {
                field0D8 = field0D8 + 3;
            } else if (animationStage == 3) {
                // Hold the projectile speed during the fade.
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth);
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
            x = facing * velocityX + x;
            y = y - velocityY;
            if (animationStage < 3 && remainingHits != 0) {
                // Keep the current stage while contact is active.
            }
            if (animationStage < 3 && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;
    }

    case 930: {
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = static_cast<short>(field0CC);
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0D8) * FloatConstants::OneTenth);
            }
            if (animationStage == 1) {
                if (field0D8 > 1) {
                    field0D8 = field0D8 - 2;
                }
                if (field0D8 < 1) {
                    field0D8 = 1;
                }
            }
            if (animationStage == 2) {
                field0D8 = field0D8 - 3;
            } else if (animationStage == 3) {
                // Hold the projectile speed during the fade.
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth);
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
            x = facing * velocityX + x;
            y = y - velocityY;
            if (animationStage < 3 && remainingHits != 0) {
                // Keep the current stage while contact is active.
            }
            if (animationStage < 3 && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;
    }

    case 931: {
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            static_cast<ReimuFighter*>(owner)->fieldF24 = 0;
            static_cast<ReimuFighter*>(owner)->fieldF26 = 0;
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 0;
                field0DA = 1;
                field0DC = 0;
                field0DE = 0;
                field0E0 = 0;
                owner->aiCardTimer = 0x3C;
            }
            if (field0DA == 1) {
                field0CC = (field0CC) + FloatConstants::OneTenth;
                if (field0CC >= FloatConstants::Ten) {
                    field0DA = -1;
                }
            }
            if (field0DA == -1) {
                field0CC = field0CC - FloatConstants::OneTenth;
                if (field0CC <= GeometryConstants::NegativeTen) {
                    field0DA = 1;
                }
            }
            if (owner->opponentFreezeTimer == 0) {
                static_cast<ReimuFighter*>(owner)->fieldF24 += field0CC;
            }
            if (static_cast<ReimuFighter*>(owner)->fieldF24 > 0xB4) {
                static_cast<ReimuFighter*>(owner)->fieldF24 = static_cast<ReimuFighter*>(owner)->fieldF24 - 0x168;
            }
            if (static_cast<ReimuFighter*>(owner)->fieldF24 < -0xB4) {
                static_cast<ReimuFighter*>(owner)->fieldF24 = static_cast<ReimuFighter*>(owner)->fieldF24 + 0x168;
            }
            facing = 1;
            --owner->aiCardTimer;
            --field0DC;
            if (owner->aiCardTimer <= 0) {
                if (RecordedRange(0, 100) < 0x32) {
                    owner->aiCardTimer =
                        300 - g_OptionsModeAt006714D0 * 0x14;
                    static_cast<ReimuFighter*>(owner)->fieldF28 = 1;
                    field0DC = g_OptionsModeAt006714D0 * 5 + 0x14;
                    return;
                }
                else {
                    owner->aiCardTimer =
                        300 - g_OptionsModeAt006714D0 * 0x14;
                    static_cast<ReimuFighter*>(owner)->fieldF28 = 2;
                    field0DC = g_OptionsModeAt006714D0 * 5 + 0x14;
                    return;
                }
            }
            else {
                if (field0DC <= 0) {
                    static_cast<ReimuFighter*>(owner)->fieldF28 = 0;
                }
                if (static_cast<ReimuFighter*>(owner)->fieldF26 < 0x78) {
                    static_cast<ReimuFighter*>(owner)->fieldF26 = static_cast<ReimuFighter*>(owner)->fieldF26 + 2;
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ResetSecondaryCounter(1);
                }
            }
        }
        break;
    }

    case 932: {
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            static_cast<ReimuFighter*>(owner)->fieldF24 = 0;
            static_cast<ReimuFighter*>(owner)->fieldF26 = 0;
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 0;
                field0DA = 1;
                field0DC = 0;
                field0DE = 0;
                field0E0 = 0;
                owner->aiCardTimer = 0x3C;
            }
            field0CC = (field0CC) + FloatConstants::OneTenth;
            if (field0CC >= FloatConstants::Five) {
                field0CC = 5.0f;
            }
            if (owner->opponentFreezeTimer == 0) {
                static_cast<ReimuFighter*>(owner)->fieldF24 += FloatConstants::One;
            }
            if (static_cast<ReimuFighter*>(owner)->fieldF24 > 0xB4) {
                static_cast<ReimuFighter*>(owner)->fieldF24 = static_cast<ReimuFighter*>(owner)->fieldF24 - 0x168;
            }
            if (static_cast<ReimuFighter*>(owner)->fieldF24 < -0xB4) {
                static_cast<ReimuFighter*>(owner)->fieldF24 = static_cast<ReimuFighter*>(owner)->fieldF24 + 0x168;
            }
            if (owner->action == 0x304) {
                ++field0E0;
                if (field0E0 > 7) {
                    --static_cast<ReimuFighter*>(owner)->fieldF26;
                    field0E0 = 0;
                }
                if (static_cast<ReimuFighter*>(owner)->fieldF26 < 0x78) {
                    static_cast<ReimuFighter*>(owner)->fieldF26 = static_cast<ReimuFighter*>(owner)->fieldF26 + 2;
                }
            }
            if (owner->aiCardTimer <= 0) {
                owner->aiCardTimer =
                    300 - g_OptionsModeAt006714D0 * 0x1E;
                static_cast<ReimuFighter*>(owner)->fieldF28 = 3;
                field0DC = 1;
                return;
            }
            else {
                if (field0DC <= 0) {
                    static_cast<ReimuFighter*>(owner)->fieldF28 = 0;
                }
                facing = 1;
                --owner->aiCardTimer;
                --field0DC;
                if (static_cast<ReimuFighter*>(owner)->fieldF26 < 0x78) {
                    static_cast<ReimuFighter*>(owner)->fieldF26 = static_cast<ReimuFighter*>(owner)->fieldF26 + 2;
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ResetSecondaryCounter(1);
                }
            }
        }
        break;
    }

    case 933:
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                field0E0 = 0;
                SetPolarVelocity(AngleAt00483300(
                    (owner->opponent->y - y) + GeometryConstants::Hundred,
                    (owner->opponent->x - x) * facing) /
                    GeometryConstants::RadiansPerDegree, 2.0f);
            } else if (animationStage == 0 && animationFrame != 0) {
                // Keep the launch velocity on later frames.
            }
            x = facing * velocityX + x;
            y = y - velocityY;
            rotationZ = (rotationZ) + FloatConstants::Four;
            if (collisionResult == 6) {
                remainingHits = 1;
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(1);
                collisionResult = 0;
                if (field0E0 > 0x14) {
                    ClearFrameInfo();
                }
            }
        }
        break;

    case 934:
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
            }
            if (animationStage == 1) {
                scaleX = (scaleX) + FloatConstants::OneFifth;
                scaleY = (scaleY) + FloatConstants::OneFifth;
                if (color[0] > 0x14) {
                    color[0] -= 0x14;
                } else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;

    case 940: {
        if (x > GeometryConstants::ThirteenHundredEighty ||
            x < GeometryConstants::NegativeHundred ||
            y > GeometryConstants::Thousand ||
            y < GeometryConstants::NegativeTwoHundredForty ||
            owner->spellTimer == 0) {
            ClearFrameInfo();
            return;
        }
        else if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
                field0D8 = static_cast<short>(field0CC);
                field0DA = 0;
                field0DE = 0;
                field0DC = static_cast<short>(field0C8);
                SetPolarVelocity(static_cast<float>(field0DC),
                    static_cast<float>(field0D8) * FloatConstants::OneTenth);
            }
            if (animationStage == 1) {
                if (field0D8 > 1) {
                    field0D8 = field0D8 - 2;
                }
                if (field0D8 < 1) {
                    field0D8 = 1;
                }
            }
            if (animationStage == 2) {
                field0D8 = field0D8 + 3;
            } else if (animationStage == 3) {
                // Hold the projectile speed during the fade.
            }
            SetPolarVelocity(static_cast<float>(field0DC),
                static_cast<float>(field0D8) * FloatConstants::OneTenth);
            rotationZ = AngleAt00483300(velocityY, velocityX) /
                GeometryConstants::RadiansPerDegree;
            x = facing * velocityX + x;
            y = y - velocityY;
            if (animationStage < 3 && remainingHits != 0) {
                // Keep the current stage while contact is active.
            }
            if (animationStage < 3 && remainingHits == 0) {
                ResetSecondaryCounter(3);
            }
            if (animationStage > 2) {
                if (color[0] >= 0x19) {
                    color[0] -= 0x19;
                } else {
                    color[0] = 0;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
            }
        }
        break;
    }

    case 990: {
        if (static_cast<ReimuFighter*>(owner)->longRangeFrames == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = (owner->y) + GeometryConstants::Hundred;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
            }
            rotationZ = (rotationZ) + FloatConstants::One;
            if (animationStage == 0) {
                if (color[0] < 0xB4) {
                    color[0] = static_cast<unsigned char>(color[0] + 0x19);
                }
                else {
                    color[0] = 0xB4;
                }
                if (static_cast<ReimuFighter*>(owner)->longRangeFrames >= 0x78) {
                    ResetSecondaryCounter(1);
                    color[0] = 0xB4;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 0x1E) {
                    color[0] -= 0x1E;
                } else {
                    color[0] = 0;
                }
                if (color[0] == 0) {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                return;
            }
        }
        break;
    }

    case 991: {
        if (static_cast<ReimuFighter*>(owner)->longRangeFrames == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = (owner->y) + GeometryConstants::Hundred;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 0;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
            }
            scaleX = static_cast<float>(static_cast<ReimuFighter*>(owner)->longRangeFrames) /
                GeometryConstants::FortyFive;
            scaleY = scaleX;
            if (animationStage == 0) {
                if (color[0] < 0xE6) {
                    color[0] = static_cast<unsigned char>(color[0] + 0x19);
                }
                else {
                    color[0] = 0xFF;
                }
                if (static_cast<ReimuFighter*>(owner)->longRangeFrames >= 0x78) {
                    ResetSecondaryCounter(1);
                    color[0] = 0xFF;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 0x0A) {
                    color[0] -= 0x0A;
                } else {
                    color[0] = 0;
                }
                if (color[0] == 0) {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) {
                ClearFrameInfo();
                return;
            }
        }
        break;
    }

    case 994:
        x = owner->x;
        y = 1.0f;
        field08A = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            spriteOffsetZ = 0x4E2;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            rotationX = -80.0f;
            field0D8 = owner->spellTimer;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            scaleX = (static_cast<float>(owner->spellTimer) /
                static_cast<float>(field0D8)) * 2.0f + FloatConstants::One;
            scaleY = (static_cast<float>(owner->spellTimer) /
                static_cast<float>(field0D8)) * 2.0f + FloatConstants::One;
            rotationZ = rotationZ - FloatConstants::One;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(1);
                return;
            }
        }
        break;

    case 950:
        if (owner->action != 700 && owner->action != 0x2BD &&
            owner->action != 0x2C2 && owner->action != 0x2C3) {
            ClearFrameInfo();
            return;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            collisionResult = 0;
            remainingHits = 1;
            velocityY = 15.0f;
        }
        rotationZ = rotationZ - GeometryConstants::ThirtyFive;
        y = y + velocityY;
        if (y > GeometryConstants::Thousand) {
            ClearFrameInfo();
            return;
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        break;


    case 951: {
        if (animationStage < 1) {
            y = owner->y;
        }
        x = owner->x;
        owner->fieldF0C = 1;
        if (owner->animationStage == 0 &&
            (((owner->action >= 0x46 && owner->action <= 0x58) &&
              owner->action != 0x4C) ||
             owner->action == 0xB5 || owner->action == 0xB4 ||
             owner->action == 0x91)) {
            ClearFrameInfo();
            owner->fieldF0C = 0;
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(-45.0f, 45.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
                color[3] = 0xFF;
            }
            if (animationStage == 0 &&
                (owner->action == 0x60 || owner->action == 0x61) &&
                owner->animationStage == 5) {
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                return;
            }
            else if (animationStage == 5 &&
                (owner->action == 0x5F || owner->action == 0x5E ||
                 owner->action == 0x5D || owner->action == 0x31C ||
                 owner->action == 0x303) &&
                owner->animationStage == 3) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (animationStage == 7 &&
                (owner->action == 0x5F || owner->action == 0x5E ||
                 owner->action == 0x5D || owner->action == 0x31C) &&
                owner->animationStage == 0x0B) {
                ClearFrameInfo();
                owner->fieldF0C = 0;
                return;
            }
            else {
                if (animationStage == 7 && animationFrame == 0 &&
                    owner->action != 0x303 && owner->action != 0x304) {
                    velocityY = 15.0f;
                    verticalAcceleration = -1.0f;
                }
                if (animationStage == 7 &&
                    owner->action != 0x304 && owner->action != 0x303) {
                    velocityY = velocityY + verticalAcceleration;
                    y = y + velocityY;
                }
                if (animationStage == 7 &&
                    (owner->action == 0x304 || owner->action == 0x303)) {
                    x = owner->x + static_cast<float>(facing * 0x78);
                    y = (owner->y) + GeometryConstants::Hundred;
                }
                if (animationStage == 0 || animationStage == 7) {
                    rotationZ = rotationZ - GeometryConstants::ThirtyFive;
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
            }
        }
        break;
    }

    case 995:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = static_cast<short>(RecordedRange(0, 360) - 0xB4);
            field0DA = 0x0F;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) {
                field0DA = 3;
            }
            SetPolarVelocity(static_cast<float>(field0D8),
                static_cast<float>(field0DA) * FloatConstants::FourFifths);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                owner->opponent->x - x) / GeometryConstants::RadiansPerDegree);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < GeometryConstants::Twenty &&
                x - owner->opponent->x > GeometryConstants::NegativeTwenty &&
                y - owner->opponent->y < GeometryConstants::HundredTwenty &&
                y - owner->opponent->y > GeometryConstants::Eighty) {
                ClearFrameInfo();
                if (owner->opponent->bombCount < 2) {
                    ++owner->opponent->bombCount;
                }
                else {
                    owner->opponent->score = owner->opponent->score + 0x4E20;
                }
                PlaySharedSound(0x2E);
                return;
            }
        }
        x = x + velocityX;
        y = y - velocityY;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 996:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = static_cast<short>(RecordedRange(0, 360) - 0xB4);
            field0DA = 0x0F;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) {
                field0DA = 3;
            }
            SetPolarVelocity(static_cast<float>(field0D8),
                static_cast<float>(field0DA) * FloatConstants::FourFifths);
        }
        if (animationStage == 1) {
            field0D8 = static_cast<short>(AngleAt00483300(
                ((owner->opponent->y) + GeometryConstants::Hundred) - y,
                owner->opponent->x - x) / GeometryConstants::RadiansPerDegree);
            SetPolarVelocity(static_cast<float>(field0D8), 20.0f);
            if (x - owner->opponent->x < GeometryConstants::Twenty &&
                x - owner->opponent->x > GeometryConstants::NegativeTwenty &&
                y - owner->opponent->y < GeometryConstants::HundredTwenty &&
                y - owner->opponent->y > GeometryConstants::Eighty) {
                ++owner->fieldEFA;
                PlaySharedSound(0x2E);
                ClearFrameInfo();
                if (owner->opponent->spiritCooldown > 0) {
                    if (owner->opponent->spiritCooldown > 5) {
                        owner->opponent->spiritCooldown =
                            owner->opponent->spiritCooldown - 5;
                    }
                    else {
                        owner->opponent->spiritCooldown = 0;
                        owner->opponent->spirit = 1000;
                    }
                    return;
                }
                if (owner->opponent->spirit < 0x3DE) {
                    owner->opponent->spirit = owner->opponent->spirit + 10;
                }
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->spellDeclarationExpired == 0) {
                        if (owner->opponent->spellPower < FloatConstants::NineHundredNinetyEightAndNineTenths) {
                            owner->opponent->spellPower = (owner->opponent->spellPower) +
                                FloatConstants::Half;
                        }
                        else {
                            owner->opponent->spellPower = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x = x + velocityX;
        y = y - velocityY;
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;

    case 997:
        x = owner->x;
        y = 0.0f;
        field08A = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            spriteOffsetZ = 0x4E2;
            rotationY = 0.0f;
            rotationZ = 0.0f;
            rotationX = -80.0f;
            field0D8 = owner->spellTimer;
        }
        if (owner->spellTimer <= 0) {
            ClearFrameInfo();
            return;
        }
        else {
            scaleX = (static_cast<float>(owner->spellTimer) /
                static_cast<float>(field0D8)) * 2.0f;
            scaleY = (static_cast<float>(owner->spellTimer) /
                static_cast<float>(field0D8)) * 2.0f;
            rotationZ = (rotationZ) + FloatConstants::One;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(10);
                return;
            } else if (animationStage < animationStageCount) {
                // Let the animation run to completion.
            }
        }
        break;

    case 998:
        facing = owner->facing;
        if (owner->action > 0x95 && owner->action < 0x9A &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + GeometryConstants::NinetyFour;
        }
        if (owner->action > 0x99 && owner->action < 0x9E &&
            animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + GeometryConstants::Sixty;
        }
        if (owner->action == 0x9E && animationStage == 0) {
            x = owner->x + static_cast<float>(facing * 0x39);
            y = (owner->y) + GeometryConstants::Hundred;
        }
        if ((owner->action < 0x96 || owner->action > 0x9E) &&
            animationStage == 0) {
            ResetSecondaryCounter(1);
            owner->fieldF0A = 0;
        }
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 0.75f;
            scaleY = 0.75f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            rotationY = 50.0f;
            field0D8 = 1;
        }
        rotationZ = (rotationZ) + FloatConstants::Two;
        if (animationStage > 0) {
            if (color[0] > 0x1E) {
                color[0] -= 0x1E;
            } else {
                color[0] = 0;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ClearFrameInfo();
        }
        if (animationStage == 1 && animationFrame == 0) {
            ResetSecondaryCounter(0);
        }
        break;
    default:
        AdvanceNestedFrame();
        break;
    }
}
