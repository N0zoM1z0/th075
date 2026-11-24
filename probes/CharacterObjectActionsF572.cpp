#include "../src/GeometryConstants.hpp"
#include "../src/FloatConstants.hpp"
#include "GameSharedState.hpp"
#include "AliceFighter.hpp"
#include "CharacterObject.hpp"
// F572/F573/F574/F575/F576/F577/F578/F579/F580/F581/F582/F583/F585/F586/F587/F588/F590/F591/F592/F593/F596: selected natural VC7.1 source, original PE 004EBDA0.
// Original entire 33,293-byte CODE + 438 post-RET DATA now have the
// exact physical native layout and all 8,789 original x86 instruction
// offsets/lengths; all 8,789 mnemonic ordinals now match. 137 original
// non-COFF bytes in three GPR contexts still differ: NONEXACT.
// All real native action cases and the original 0040FA30 default are
// present as normal C++; three case bodies still have wrong GPR roles.
// No target ASM, injected filler, machine-byte graft or independent
// split-case CODE/DATA acceptance is claimed.
// F539 natural switch *probe*, not original fighter source or CODE credit.
// This file is regenerable from the original PE under ignored .analysis.
extern float MagnitudeAt00428D20(float value);
extern float AngleAt00483300(float first, float second);
extern float AbsFloatAt00412D90(float value);

void AliceObject::Advance() {
    if (owner->opponent->field3BA != 0)
        return;
    if (owner->field3BA != 0 && field08A == 0)
        return;
    if (field082 != 0) {
        --field082;
        return;
    }
    switch (action) {
        case 0x320: AdvanceProjectileBehavior(); break;
        case 0x321: AdvanceProjectileBehavior(); break;
        case 0x322: AdvanceProjectileBehavior(); break;
        case 0x323: AdvanceProjectileBehavior(); break;
        case 0x324: AdvanceProjectileBehavior(); break;
        case 0x325: AdvanceProjectileBehavior(); break;
        case 0x326: AdvanceProjectileBehavior(); break;
        case 0x327: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 5) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 0x19) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            field0D8 = -30;
            field0DA = 150;
            field0DC = 0;
            ResetTransform(0.0f,0.0f,0.0f);
            field080 = 4;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            owner->SpawnBattleEffect(0x371, x,
                                  (y) + FloatConstants::Ten,
                                  facing, 1);
            owner->PlaySound(2);
        }
        if ((animationStage) == 0) {
            SetPolarVelocity(field0D8,
                            field0DA*FloatConstants::OneTenth);
            field0DA -= 5;
            field0D8 += 3;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            if ((field0DA) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += facing * (velocityX);
        y = y - velocityY;
        if ((animationStage) < 5 && (field080) == 0) {
            ResetSecondaryCounter((animationStage) + 4);
            break;
        }
        if ((animationStage) > 4) {
            scaleX = (scaleX)*FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ResetSecondaryCounter(5);
            break;
        }
        if ((animationFrame) == 0)
            field07C = 0;
        if ((animationStage) == 5 && (animationFrame) == 0 && (field0DC) < 10) {
            ResetSecondaryCounter(1);
            ++field0DC;
        }
    }
    break;
}
        case 0x328: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 5) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 0x19) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            field0D8 = 70;
            field0DA = 150;
            field0DC = 0;
            ResetTransform(0.0f,0.0f,0.0f);
            field080 = 4;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            owner->SpawnBattleEffect(0x371, x,
                                  (y) + FloatConstants::Ten,
                                  facing, 1);
            owner->PlaySound(2);
        }
        if ((animationStage) == 0) {
            SetPolarVelocity(field0D8,
                            field0DA*FloatConstants::OneTenth);
            field0DA -= 5;
            field0D8 -= 2;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            if ((field0DA) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += facing * (velocityX);
        y = y - velocityY;
        if ((animationStage) < 5 && (field080) == 0) {
            ResetSecondaryCounter((animationStage) + 4);
            break;
        }
        if ((animationStage) > 4) {
            scaleX = (scaleX)*FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ResetSecondaryCounter(5);
            break;
        }
        if ((animationFrame) == 0)
            field07C = 0;
        if ((animationStage) == 5 && (animationFrame) == 0 && (field0DC) < 10) {
            ResetSecondaryCounter(1);
            ++field0DC;
        }
    }
    break;
}
        case 0x329: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 5) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 0x19) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            field0D8 = -30;
            field0DA = 200;
            field0DC = 0;
            ResetTransform(0.0f,0.0f,0.0f);
            field080 = 4;
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            owner->SpawnBattleEffect(0x371, x,
                                  (y) + FloatConstants::Ten,
                                  facing, 1);
            owner->PlaySound(2);
        }
        if ((animationStage) == 0) {
            SetPolarVelocity(field0D8,
                            field0DA*FloatConstants::OneTenth);
            field0DA -= 5;
            field0D8 += 4;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            if ((field0DA) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += facing * (velocityX);
        y = y - velocityY;
        if ((animationStage) < 5 && (field080) == 0) {
            ResetSecondaryCounter((animationStage) + 4);
            break;
        }
        if ((animationStage) > 4) {
            scaleX = (scaleX)*FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ResetSecondaryCounter(5);
            break;
        }
        if ((animationFrame) == 0)
            field07C = 0;
        if ((animationStage) == 5 && (animationFrame) == 0 && (field0DC) < 10) {
            ResetSecondaryCounter(1);
            ++field0DC;
        }
    }
    break;
}
        case 0x32A: {
    if ((owner->action) > 0x31 && (owner->action) < 0x96) {
        ClearFrameInfo();
        for (int iteration=0; iteration<5; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 0x19) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field080 = 1;
            field07C = 0;
            if (field0C8 == FloatConstants::Zero) {
                velocityX = 5.0f;
                velocityY = 6.0f;
            }
            if (field0C8 == FloatConstants::One) {
                velocityX = 3.0f;
                velocityY = 8.0f;
            }
            if (field0C8 == FloatConstants::Two) {
                velocityX = 1.0f;
                velocityY = 10.0f;
            }
            if (field0C8 == FloatConstants::Three) {
                velocityX = -5.0f;
                velocityY = 6.0f;
            }
            if (field0C8 == FloatConstants::Four) {
                velocityX = -3.0f;
                velocityY = 8.0f;
            }
            if (field0C8 == FloatConstants::Five) {
                velocityX = -1.0f;
                velocityY = 10.0f;
            }
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        velocityY = (velocityY) - FloatConstants::ThreeFifths;
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) < 2) {
            rotationZ = (rotationZ) + GeometryConstants::Sixteen;
            if (y + velocityY <= FloatConstants::Zero) {
                owner->SpawnBattleEffect(0x32B, x, y, facing, 1);
                owner->SpawnBattleEffect(0x32D, x, y, facing, 1);
                owner->PlaySound(4);
                ResetPrimaryCounters(0x33B);
                y = 0.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
                rotationZ = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount))
            ResetSecondaryCounter(1);
    }
    break;
}
        case 0x32B: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        owner->SetCameraShake(5.0f);
    }
    scaleX = (float)(5 - (animationFrame)) * FloatConstants::ThreeHundredths * ((animationFrame) < 5) + FloatConstants::OneHundredth + (scaleX);
    scaleY = (float)(5 - (animationFrame)) * FloatConstants::ThreeHundredths * ((animationFrame) < 5) + FloatConstants::OneHundredth + (scaleY);
    if ((animationStage) > 1) {
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x32C: {
    if ((owner->action) > 0x31 && (owner->action) < 0x96) {
        ClearFrameInfo();
        for (int iteration=0; iteration<5; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field080 = 1;
            field07C = 0;
            SetPolarVelocity(field0C8,15.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
        }
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) < 2) {
            rotationZ = (rotationZ) + GeometryConstants::Sixteen;
            if (y + velocityY <= FloatConstants::Zero) {
                owner->PlaySound(4);
                owner->SpawnBattleEffect(0x32B, x, y, facing, 1);
                owner->SpawnBattleEffect(0x32D, x, y, facing, 1);
                ResetPrimaryCounters(0x33B);
                y = 0.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
                rotationZ = 0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount))
            ResetSecondaryCounter(1);
    }
    break;
}
        case 0x32D: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 0.4f;
        scaleY = 0.4f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field01A = 0x4E2;
        rotationX = -75.0f;
    }
    scaleX = (scaleX) + FloatConstants::FifteenHundredths;
    scaleY = (scaleY) + FloatConstants::FifteenHundredths;
    if ((animationStage) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x32E: {
    if ((animationStage) == 0 && (animationFrame) == 0 && (field0D8) == 1) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 0.5f;
        scaleY = 0.5f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
    }
    scaleX = (scaleX) + FloatConstants::SevenHundredths;
    scaleY = (scaleY) + FloatConstants::SevenHundredths;
    color[0] -= 10;
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x330: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 11) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = -4.0f;
            velocityY = 6.0f;
        }
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            velocityY = (velocityY) - FloatConstants::ThreeTenths;
        }
        if ((animationStage) == 11) {
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ClearFrameInfo();
            break;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((animationStage) == 6 && (animationFrame) == 0 && (field0DC) < 0) {
            ResetSecondaryCounter(2);
            ++field0DC;
        }
        if ((animationStage) == 10 && (animationFrame) == 0 && (field0DA) < 6) {
            ++field0DA;
            ResetSecondaryCounter(9);
        }
        if ((animationStage) == 9 && (animationFrame) == 0) {
            (owner->field314) = 1200.0f;
            (owner->field318) = RecordedRange(0,10) - 5;
            owner->SpawnBattleEffect(0x320,
                   (facing) * 10 + (x),
                   y, facing, 1);
            owner->PlaySound(6);
        }
    }
    break;
}
        case 0x331: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 11) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 3.0f;
            velocityY = 16.0f;
        }
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            velocityY = (velocityY) - FloatConstants::FourFifths;
        }
        if ((animationStage) == 11) {
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ClearFrameInfo();
            break;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((animationStage) == 6 && (animationFrame) == 0 && (field0DC) < 0) {
            ResetSecondaryCounter(2);
            ++field0DC;
        }
        if ((animationStage) == 10 && (animationFrame) == 0 && (field0DA) < 6) {
            ++field0DA;
            ResetSecondaryCounter(9);
        }
        if ((animationStage) == 9 && (animationFrame) == 0) {
            (owner->field314) = 1200.0f;
            (owner->field318) = RecordedRange(0,15) - 45;
            owner->SpawnBattleEffect(0x321,
                   (facing) * 10 + (x),
                   y, facing, 1);
            owner->PlaySound(6);
        }
    }
    break;
}
        case 0x332: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 11) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 6.0f;
            velocityY = 4.5f;
        }
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            velocityY = (velocityY) - FloatConstants::ThreeTenths;
        }
        if ((animationStage) == 11) {
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ClearFrameInfo();
            break;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
            facing = -(facing);
        }
        if ((animationStage) == 6 && (animationFrame) == 0 && (field0DC) < 0) {
            ResetSecondaryCounter(2);
            ++field0DC;
        }
        if ((animationStage) == 10 && (animationFrame) == 0 && (field0DA) < 6) {
            ++field0DA;
            ResetSecondaryCounter(9);
        }
        if ((animationStage) == 9 && (animationFrame) == 0) {
            (owner->field314) = 1200.0f;
            (owner->field318) = RecordedRange(0,10) - 5;
            owner->SpawnBattleEffect(0x322,
                   (facing) * 10 + (x),
                   y, facing, 1);
            owner->PlaySound(6);
        }
    }
    break;
}
        case 0x335: {
    if ((field07C) == 6) {
        field07C = 0;
        field080 = 99;
    }
    if ((owner->action) > 0x45 && (owner->action) < 0x96 &&
            (field080) > 0 && (animationStage) < 11) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((animationStage) == 0 && (animationFrame) == 0) {
            field0D8 = 0;
            field0DA = 0;
            field0DC = 0;
            field07C = 0;
            field080 = 99;
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            SetPolarVelocity(field0C8,14.0f);
        }
        if ((animationStage) == 0) {
            rotationZ = (rotationZ) + GeometryConstants::Fifteen;
            velocityY = (velocityY) + FloatConstants::Half;
        }
        x += facing * (velocityX);
        y = y - velocityY;
        if ((animationStage) == 10 && y - velocityY <= GeometryConstants::Hundred) {
            velocityX = 2.0f;
            velocityY = 2.0f;
            ResetSecondaryCounter(11);
        }
        if ((animationStage) > 10 && (field0D8) > 2) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ResetSecondaryCounter(10);
            ++field0D8;
            break;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((animationStage) == 6 && (animationFrame) == 0 &&
                field0DC < FloatConstants::Zero + field0CC) {
            ResetSecondaryCounter(2);
            ++field0DC;
        }
        if ((animationStage) == 10 && (animationFrame) == 0) {
            owner->PlaySound(16);
            velocityX = 18.0f;
            velocityY = 18.0f;
        }
    }
    break;
}
        case 0x338: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        owner->SetCameraShake(10.0f);
        owner->SpawnBattleEffect(0x33A, x, y, facing, 1);
    }
    if ((field07C) == 6) {
        field07C = 0;
        ++field080;
    }
    scaleX = (scaleX) + FloatConstants::SevenHundredths;
    scaleY = (scaleY) + FloatConstants::SevenHundredths;
    if ((animationStage) > 1) {
        if ((color[0]) >= 20)
            color[0] -= 20;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    if ((animationStage) == 2 && (animationFrame) == 0)
        owner->SpawnBattleEffect(0x339, x, y, facing, 1);
    break;
}
        case 0x339: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.3f;
        scaleY = 1.3f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
    }
    scaleX = (scaleX) + FloatConstants::SevenHundredths;
    scaleY = (scaleY) + FloatConstants::SevenHundredths;
    if ((animationStage) > 1) {
        if ((color[0]) >= 40)
            color[0] -= 40;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x33A: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field01A = 0x4E2;
        rotationX = -75.0f;
    }
    scaleX = (scaleX) + FloatConstants::ThreeTenths;
    scaleY = (scaleY) + FloatConstants::ThreeTenths;
    if ((animationStage) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x33B: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        SetPolarVelocity(-(RecordedRange(0,45)
                - FloatConstants::TwentyTwoAndHalf + GeometryConstants::Ninety),18.0f);
    }
    x += facing * (velocityX);
    y = y + velocityY;
    velocityY = (velocityY) - FloatConstants::EightyFiveHundredths;
    rotationZ = (rotationZ) + GeometryConstants::Fifteen;
    if ((y) < GeometryConstants::NegativeFourHundredEighty) {
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x33C: {
    if ((owner->action) == 0x2BE) {
        x = owner->x + (facing) * 65;
        y = (owner->y) + GeometryConstants::HundredTen;
    }
    if ((owner->action) != 0x2BE ||
            ((owner->animationStage) > 9 && (owner->action) == 0x2BE)) {
        if ((field0D8) == 0) {
            field0D8 = 1;
            break;
        }
    }
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field07C = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if ((field0D8) == 0) {
        if ((color[0]) <= 0xE1)
            color[0] += 30;
        else
            color[0] = 0xFF;
    }
    if ((field0D8) == 1) {
        scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
        scaleY = (scaleY) + FloatConstants::ThreeTenths;
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount)) {
        ResetSecondaryCounter(1);
        break;
    }
    break;
}
        case 0x33D: {
    if ((owner->action) == 0x2C1) {
        x = owner->x + (facing) * 65;
        y = (owner->y) + GeometryConstants::HundredTen;
    }
    if ((owner->action) != 0x2C1 ||
            ((owner->animationStage) > 9 && (owner->action) == 0x2BE)) {
        if ((field0D8) == 0) {
            field0D8 = 1;
            break;
        }
    }
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field07C = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    if ((field0D8) == 0) {
        if ((color[0]) <= 0xE1)
            color[0] += 30;
        else
            color[0] = 0xFF;
    }
    if ((field0D8) == 1) {
        scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
        scaleY = (scaleY) + FloatConstants::ThreeTenths;
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount)) {
        ResetSecondaryCounter(1);
        break;
    }
    break;
}
        case 0x33E: {
    if ((owner->action) == 0x2BE) {
        x = owner->x + (facing) * 140;
        y = (owner->y) + GeometryConstants::HundredTen;
    }
    if ((owner->action) != 0x2BE && (animationStage) < 7) {
        ResetSecondaryCounter(7);
        break;
    }
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field080 = 1;
        field07C = 0;
        if ((field0D8) != 1) {
            ResetTransform(0.0f,0.0f,0.0f);
            scaleX = 1.5f;
            scaleY = 1.5f;
            field0D8 = 0;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field080 = 10;
        }
    }
    if ((animationStage) == 6)
        scaleY = static_cast<float>(RecordedRange(0,4) - 2)
                  * FloatConstants::OneTwentieth + FloatConstants::OneAndHalf;
    if ((animationStage) == 7)
        scaleY = (scaleY) * FloatConstants::SevenTenths;
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    if ((animationStage) == 7 && (animationFrame) == 0 && (field0D8) < 10) {
        ResetSecondaryCounter(6);
        field07C = 0;
        ++field0D8;
    }
    break;
}
        case 0x33F: {
    if ((owner->action) == 0x2C1) {
        x = owner->x + (facing) * 180;
        y = (owner->y) + GeometryConstants::HundredTen;
    }
    if ((owner->action) != 0x2C1 && (animationStage) < 17) {
        ResetSecondaryCounter(17);
        break;
    }
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field07C = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 2.0f;
        scaleY = 1.5f;
        field0D8 = 0;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field080 = 25;
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    if ((animationFrame) == 0)
        field07C = 0;
    if ((animationStage) == 13 && (animationFrame) == 0 && (field0D8) < 2) {
        ResetSecondaryCounter(6);
        ++field0D8;
    }
    break;
}
        case 0x340: {
    if ((field07C) == 6) {
        field07C = 0;
        field080 = 1;
    }
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityX = AbsFloatAt00412D90(
            owner->x + (owner->facing) * 90 - (owner->opponent->x)
        ) * FloatConstants::FourHundredths;
        if ((velocityX) < FloatConstants::Four)
            velocityX = 4.0f;
        velocityY = 20.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    velocityY = (velocityY) - FloatConstants::Two;
    x += facing * (velocityX);
    y = y + velocityY;
    if ((animationStage) < 2) {
        rotationZ = (rotationZ) + GeometryConstants::Sixteen;
        if (y + velocityY <= FloatConstants::Zero) {
            owner->SpawnBattleEffect(0x338, x, y, facing, 1);
            owner->SpawnBattleEffect(0x33A, x, y, facing, 1);
            owner->PlaySound(8);
            ResetPrimaryCounters(0x33B);
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
            rotationZ = 0.0f;
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ResetSecondaryCounter(1);
    break;
}
        case 0x341: {
    if ((field07C) == 6) {
        field07C = 0;
        field080 = 1;
    }
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityX = AbsFloatAt00412D90(
            owner->x + (owner->facing) * 90 - (owner->opponent->x)
        ) * FloatConstants::FourHundredths;
        if ((velocityX) < FloatConstants::Four)
            velocityX = 4.0f;
        velocityY = 20.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    velocityY = (velocityY) - FloatConstants::Two;
    x += facing * (velocityX);
    y = y + velocityY;
    if ((animationStage) < 2) {
        rotationZ = (rotationZ) + GeometryConstants::Sixteen;
        if (y + velocityY <= FloatConstants::Zero) {
            owner->SpawnBattleEffect(0x342, x, y, facing, 1);
            owner->SpawnBattleEffect(0x344, x, y, facing, 1);
            owner->PlaySound(10);
            ResetPrimaryCounters(0x33B);
            y = 0.0f;
            velocityY = 0.0f;
            velocityX = 0.0f;
            rotationZ = 0.0f;
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ResetSecondaryCounter(1);
    break;
}
        case 0x342: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        owner->SetCameraShake(10.0f);
    }
    if ((field07C) == 6) {
        field07C = 0;
        ++field080;
    }
    if ((animationStage) == 3 && (animationFrame) == 0)
        owner->SpawnBattleEffect(0x343, x, y, facing, 1);
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x343: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        field0D8 = 0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080 = 1;
        field07C = 0;
        velocityY = 0.0f;
        velocityX = 0.0f;
        scaleX = 1.7f;
        scaleY = 1.7f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
    }
    scaleX = (scaleX) + FloatConstants::EightHundredths;
    scaleY = (scaleY) + FloatConstants::EightHundredths;
    if ((animationStage) > -1) {
        if ((color[0]) >= 20)
            color[0] -= 20;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x344: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field01A = 0x4E2;
        rotationX = -75.0f;
    }
    scaleX = (scaleX) + FloatConstants::ThreeTenths;
    scaleY = (scaleY) + FloatConstants::ThreeTenths;
    if ((animationStage) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x345: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field0D8 = 0;
        field0DA = 0;
    }
    if ((animationStage) > 5) {
        x += facing * (velocityX);
        y = y + velocityY;
        if ((x) > GeometryConstants::SixteenHundred ||
            (x) < GeometryConstants::NegativeFourHundred ||
            (y) < GeometryConstants::NegativeFourHundred ||
            (y) > GeometryConstants::TwelveHundredEighty) {
            ClearFrameInfo();
            break;
        }
        if (AdvanceNestedFrame() == (animationStageCount))
            ResetSecondaryCounter(6);
        break;
    }
    if ((animationStage) == 1) {
        rotationZ = (rotationZ) + GeometryConstants::Fifteen;
        if ((static_cast<AliceFighter*>(owner)->fieldF12) == 1 && (animationStage) == 1 && (static_cast<AliceFighter*>(owner)->fieldF12) == 1) {
            ResetSecondaryCounter(2);
            field080 = 99;
            rotationZ = 0.0f;
            field07C = 0;
            break;
        }
    }
    if ((static_cast<AliceFighter*>(owner)->fieldF12) == 2) {
        if ((animationStage) < 6)
            animationStage += 4;
        field0DA = 25;
        SetPolarVelocity(field0D8,
                       field0DA);
    }
    if ((animationStage) < 6 && (static_cast<AliceFighter*>(owner)->fieldF12) < 2) {
        field0D8 = (static_cast<AliceFighter*>(owner)->fieldF10) - 180 + (field0C8);
        if ((field0D8) > 180) field0D8 -= 360;
        if ((field0D8) < -180) field0D8 += 360;
        SetPolarVelocity(field0D8,
                       field0DA);
        x = static_cast<int>(
            (owner->fieldF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            (owner->fieldF0E) + (velocityY));
        if ((field0DA) < 140) field0DA += 7;
        if ((field0DA) > 140) field0DA = 140;
    }
    if (AdvanceNestedFrame() == (animationStageCount)) ResetSecondaryCounter(6);
    if ((animationStage) == 2 && (animationFrame) == 0) ResetSecondaryCounter(1);
    if ((animationStage) == 6 && (animationFrame) == 0 && (static_cast<AliceFighter*>(owner)->fieldF12) == 1) {
        ResetSecondaryCounter(2);
        field07C = 0;
    }
    break;
}
        case 0x346: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        (static_cast<AliceFighter*>(owner)->fieldF10) = 0;
        velocityX = 25.0f;
    }
    if ((animationStage) < 2) {
        (static_cast<AliceFighter*>(owner)->fieldF10) -= 3;
        (owner->fieldF0C) = x;
        (owner->fieldF0E) = y;
        velocityX = (velocityX) - FloatConstants::One;
        if ((velocityX) < FloatConstants::Zero)
            velocityX = 0.0f;
    }
    x += facing * (velocityX);
    if (AdvanceNestedFrame() == (animationStageCount)) {
        ClearFrameInfo();
        (static_cast<AliceFighter*>(owner)->fieldF12) = 0;
    }
    if ((animationStage) == 1 && (animationFrame) == 0)
        (static_cast<AliceFighter*>(owner)->fieldF12) = 1;
    if ((animationStage) == 2 && (animationFrame) == 0)
        (static_cast<AliceFighter*>(owner)->fieldF12) = 2;
    break;
}
        case 0x347: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field0D8 = 0;
        field0DA = 0;
    }
    if ((animationStage) > 5) {
        x += facing * (velocityX);
        y = y + velocityY;
        if ((x) > GeometryConstants::SixteenHundred ||
            (x) < GeometryConstants::NegativeFourHundred ||
            (y) < GeometryConstants::NegativeFourHundred ||
            (y) > GeometryConstants::TwelveHundredEighty) {
            ClearFrameInfo();
            break;
        }
        if (AdvanceNestedFrame() == (animationStageCount))
            ResetSecondaryCounter(6);
        break;
    }
    if ((animationStage) == 1) {
        rotationZ = (rotationZ) + GeometryConstants::Fifteen;
        if ((static_cast<AliceFighter*>(owner)->fieldF12) == 1 && (animationStage) == 1 && (static_cast<AliceFighter*>(owner)->fieldF12) == 1) {
            ResetSecondaryCounter(2);
            field080 = 99;
            rotationZ = 0.0f;
            field07C = 0;
            break;
        }
    }
    if ((static_cast<AliceFighter*>(owner)->fieldF12) == 2) {
        if ((animationStage) < 6)
            animationStage += 4;
        field0DA = 25;
        SetPolarVelocity(field0D8,
                       field0DA);
    }
    if ((animationStage) < 6 && (static_cast<AliceFighter*>(owner)->fieldF12) < 2) {
        field0D8 = (static_cast<AliceFighter*>(owner)->fieldF10) - 180 + (field0C8);
        if ((field0D8) > 180) field0D8 -= 360;
        if ((field0D8) < -180) field0D8 += 360;
        SetPolarVelocity(field0D8,
                       field0DA);
        x = static_cast<int>(
            (owner->fieldF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            (owner->fieldF0E) + (velocityY));
        if ((field0DA) < 120) field0DA += 6;
        if ((field0DA) > 120) field0DA = 120;
    }
    if (AdvanceNestedFrame() == (animationStageCount)) ResetSecondaryCounter(6);
    if ((animationStage) == 2 && (animationFrame) == 0) ResetSecondaryCounter(1);
    if ((animationStage) == 6 && (animationFrame) == 0 && (static_cast<AliceFighter*>(owner)->fieldF12) == 1) {
        ResetSecondaryCounter(2);
        field07C = 0;
    }
    break;
}
        case 0x348: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        field0D8 = 0;
        field0DA = 0;
    }
    if ((animationStage) > 5) {
        x += facing * (velocityX);
        y = y + velocityY;
        if ((x) > GeometryConstants::SixteenHundred ||
            (x) < GeometryConstants::NegativeFourHundred ||
            (y) < GeometryConstants::NegativeFourHundred ||
            (y) > GeometryConstants::TwelveHundredEighty) {
            ClearFrameInfo();
            break;
        }
        if (AdvanceNestedFrame() == (animationStageCount))
            ResetSecondaryCounter(6);
        break;
    }
    if ((animationStage) == 1) {
        rotationZ = (rotationZ) + GeometryConstants::Fifteen;
        if ((static_cast<AliceFighter*>(owner)->fieldF12) == 1 && (animationStage) == 1 && (static_cast<AliceFighter*>(owner)->fieldF12) == 1) {
            ResetSecondaryCounter(2);
            field080 = 99;
            rotationZ = 0.0f;
            field07C = 0;
            break;
        }
    }
    if ((static_cast<AliceFighter*>(owner)->fieldF12) == 2) {
        if ((animationStage) < 6)
            animationStage += 4;
        field0DA = 25;
        SetPolarVelocity(-(field0D8) + 180,
                       field0DA);
    }
    if ((animationStage) < 6 && (static_cast<AliceFighter*>(owner)->fieldF12) < 2) {
        field0D8 = (static_cast<AliceFighter*>(owner)->fieldF10) - 180 + (field0C8);
        if ((field0D8) > 180) field0D8 -= 360;
        if ((field0D8) < -180) field0D8 += 360;
        SetPolarVelocity(-(field0D8),
                       field0DA);
        x = static_cast<int>(
            (owner->fieldF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            (owner->fieldF0E) + (velocityY));
        if ((field0DA) < 200) field0DA += 10;
        if ((field0DA) > 200) field0DA = 200;
    }
    if (AdvanceNestedFrame() == (animationStageCount)) ResetSecondaryCounter(6);
    if ((animationStage) == 2 && (animationFrame) == 0) ResetSecondaryCounter(1);
    if ((animationStage) == 6 && (animationFrame) == 0 && (static_cast<AliceFighter*>(owner)->fieldF12) == 1) {
        ResetSecondaryCounter(2);
        field07C = 0;
    }
    break;
}
        case 0x349: {
    if ((animationStage) == 0 && (animationFrame) == 0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
        (static_cast<AliceFighter*>(owner)->fieldF10) = 0;
        velocityX = 25.0f;
    }
    if ((animationStage) < 2) {
        (static_cast<AliceFighter*>(owner)->fieldF10) -= 3;
        (owner->fieldF0C) = x;
        (owner->fieldF0E) = y;
        velocityX = (velocityX) - FloatConstants::One;
        if ((velocityX) < FloatConstants::Zero)
            velocityX = 0.0f;
    }
    x += facing * (velocityX);
    if (AdvanceNestedFrame() == (animationStageCount)) {
        ClearFrameInfo();
        (static_cast<AliceFighter*>(owner)->fieldF12) = 0;
    }
    if ((animationStage) == 1 && (animationFrame) == 0)
        (static_cast<AliceFighter*>(owner)->fieldF12) = 1;
    if ((animationStage) == 2 && (animationFrame) == 0)
        (static_cast<AliceFighter*>(owner)->fieldF12) = 2;
    break;
}
        case 0x34A: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 11) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            velocityX = 3.0f;
            velocityY = -3.0f;
        }
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            velocityY = (velocityY) - FloatConstants::ThreeTenths;
            if (y + velocityY <= GeometryConstants::Twenty) {
                y = 20.0f;
                velocityY = 0.0f;
                velocityX = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                color[0] = 0xFF;
                break;
            }
        }
        if ((animationStage) == 11) {
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ClearFrameInfo();
            break;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((animationStage) == 6 && (animationFrame) == 0 && (field0DC) < 1) {
            ResetSecondaryCounter(2);
            ++field0DC;
        }
        if ((animationStage) == 10 && (animationFrame) == 0 && (field0DA) < 6) {
            ++field0DA;
            ResetSecondaryCounter(9);
        }
        if ((animationStage) == 9 && (animationFrame) == 0) {
            (owner->field314) = 1200.0f;
            (owner->field318) = RecordedRange(0,60);
            owner->SpawnBattleEffect(0x323,
                   (facing) * 10 + (x),
                   y, facing, 1);
            owner->PlaySound(6);
        }
    }
    break;
}
        case 0x34B: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 11) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
        }
        break;
    } else {
        if ((field07C) == 6) {
            field07C = 0;
            field080 = 1;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            SetPolarVelocity(field0CC,field0C8);
        }
        x += facing * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + GeometryConstants::Eighteen;
            velocityY = (velocityY) - FloatConstants::Half;
        }
        if ((animationStage) == 11) {
            scaleX = (scaleX) * FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ClearFrameInfo();
            break;
        }
        if ((animationStage) == 1 && (animationFrame) == 0) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            rotationZ = 0.0f;
        }
        if ((animationStage) == 6 && (animationFrame) == 0 && (field0DC) < 0) {
            ResetSecondaryCounter(2);
            ++field0DC;
        }
        if ((animationStage) == 10 && (animationFrame) == 0 && (field0DA) < 6) {
            ++field0DA;
            ResetSecondaryCounter(9);
        }
        if ((animationStage) == 9 && (animationFrame) == 0) {
            (owner->field314) = 1200.0f;
            (owner->field318) = RecordedRange(0,15) - 60;
            owner->SpawnBattleEffect(0x324,
                   (facing) * 10 + (x),
                   y, facing, 1);
            owner->PlaySound(6);
        }
    }
    break;
}
        case 0x34C: {
    if ((owner->action) > 0x45 && (owner->action) < 0x96 && (animationStage) < 5) {
        ClearFrameInfo();
        for (int iteration=0; iteration<8; ++iteration)
            owner->SpawnBattleEffect(0x3E4,x,y,1,1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA) = 0;
            owner->SpawnBattleEffect(0x3E3,x,y,1,1);
        }
        break;
    } else {
        if (((owner->action) == 0x198 && (owner->animationStage) < 7) ||
            ((owner->action) == 0x19C && (owner->animationStage) < 5) ||
            ((owner->action) == 0x19A && (owner->animationStage) < 7) ||
            ((owner->action) == 0x19D && (owner->animationStage) < 5)) {
            x = owner->x + (facing) * 60;
            y = (owner->y) + GeometryConstants::HundredTwenty;
            if ((owner->action) == 0x19A)
                y = (owner->y) + GeometryConstants::Sixty;
        } else if ((animationStage) < 5) {
            ResetSecondaryCounter(5);
            break;
        }
        if ((animationStage) == 0 && (animationFrame) == 0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field07C = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            color[3] = 0xFF;
            field0DA = 0;
        }
        if ((animationStage) == 5) {
            scaleX = (scaleX)*FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY) + FloatConstants::ThreeTenths;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (animationStageCount)) {
            ClearFrameInfo();
            break;
        }
        if ((animationStage) == 4 && (animationFrame) == 0 && (field0DA) < 8) {
            ++field0DA;
            ResetSecondaryCounter(3);
        }
        if ((animationStage) == 3 && (animationFrame) == 0) {
            if ((owner->action) == 0x198) {
                (owner->field314) = 1000.0f;
                (owner->field318) = RecordedRange(0,10) - 5;
                owner->SpawnBattleEffect(0x322,
                    (facing) * 10 + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
            if ((owner->action) == 0x19A) {
                (owner->field314) = 1000.0f;
                (owner->field318) = RecordedRange(0,10) + 30;
                owner->SpawnBattleEffect(0x323,
                    (facing) * 10 + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
            if ((owner->action) == 0x19C) {
                (owner->field314) = 1000.0f;
                (owner->field318) = RecordedRange(0,10) - 5;
                owner->SpawnBattleEffect(0x324,
                    (facing) * 10 + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
            if ((owner->action) == 0x19D) {
                (owner->field314) = 1000.0f;
                (owner->field318) = -RecordedRange(0,10) - 30;
                owner->SpawnBattleEffect(0x325,
                    (facing) * 10 + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
        }
    }
    break;
}
        case 0x34D: {
    if ((owner->action) > 0x31 && (owner->action) < 0x96) {
        ClearFrameInfo();
        for (int iteration=0; iteration<5; ++iteration)
            owner->SpawnBattleEffect(0x3E4,x,y,1,1);
        if ((owner->fieldEFA) > 25) {
            (owner->fieldEFA)=0;
            owner->SpawnBattleEffect(0x3E3,x,y,1,1);
        }
        break;
    } else {
        if ((field07C)==6) {
            field07C=0;
            field080=1;
        }
        if ((animationStage)==0 && (animationFrame)==0) {
            ResetTransform(0.0f,0.0f,0.0f);
            field080=1;
            field07C=0;
            velocityX=field0C8;
            velocityY=field0CC;
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
            color[1]=0xFF;
            color[2]=0xFF;
            color[3]=0xFF;
        }
        velocityY = (velocityY) - FloatConstants::FourFifths;
        x += facing*(velocityX);
        y = y + velocityY;
        if ((animationStage)<2) {
            rotationZ = (rotationZ)+GeometryConstants::Sixteen;
            if (y + velocityY <= FloatConstants::Zero) {
                owner->PlaySound(4);
                owner->SpawnBattleEffect(0x32B,x,y,facing,1);
                owner->SpawnBattleEffect(0x32D,x,y,facing,1);
                ResetPrimaryCounters(0x33B);
                y=0.0f;
                velocityY=0.0f;
                velocityX=0.0f;
                rotationZ=0.0f;
                break;
            }
        }
        if (AdvanceNestedFrame()==(animationStageCount))
            ResetSecondaryCounter(1);
    }
    break;
}
        case 0x34E: {
    if ((owner->action)>0x31 && (owner->action)<0x96) {
        ClearFrameInfo();
        for (int iteration=0;iteration<4;++iteration)
            owner->SpawnBattleEffect(0x3E4,x,y,1,1);
        if ((owner->fieldEFA)>25) {
            (owner->fieldEFA)=0;
            owner->SpawnBattleEffect(0x3E3,x,y,1,1);
        }
        break;
    } else {
        if ((field07C)==6) {
            field07C=0;
            field080=1;
        }
        if ((field0D8)>2) {
            scaleX = (scaleX)*FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY)+FloatConstants::ThreeTenths;
            if ((color[0])>=10)
                color[0]-=10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if ((animationStage)==0 && (animationFrame)==0) {
            ResetTransform(0.0f,0.0f,0.0f);

            velocityX=20.0f;
            velocityY=0.0f;
            field0D8=0;
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
            color[1]=0xFF;
            color[2]=0xFF;
            color[3]=0xFF;
        }
        velocityX = (velocityX)-FloatConstants::One;
        if ((velocityX)<FloatConstants::Two)
            velocityX=2.0f;
        x += facing*(velocityX);
        y = y+velocityY;
        if (AdvanceNestedFrame()==(animationStageCount)) {
            ResetSecondaryCounter(1);
            ++field0D8;
        }
    }
    break;
}
        case 0x34F: {
    if ((owner->action)>0x31 && (owner->action)<0x96) {
        ClearFrameInfo();
        for (int iteration=0;iteration<4;++iteration)
            owner->SpawnBattleEffect(0x3E4,x,y,1,1);
        if ((owner->fieldEFA)>25) {
            (owner->fieldEFA)=0;
            owner->SpawnBattleEffect(0x3E3,x,y,1,1);
        }
        break;
    } else {
        if ((field07C)==6) {
            field07C=0;
            field080=1;
        }
        if ((field0D8)>1) {
            scaleX = (scaleX)*FloatConstants::EightyFiveHundredthsDouble;
            scaleY = (scaleY)+FloatConstants::ThreeTenths;
            if ((color[0])>=10)
                color[0]-=10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if ((animationStage)==0 && (animationFrame)==0) {
            ResetTransform(0.0f,0.0f,0.0f);

            velocityX=20.0f;
            velocityY=0.0f;
            field0D8=0;
            field07C=0;
            field080=1;
            scaleX=1.0f;
            scaleY=1.0f;
            color[0]=0xFF;
            color[1]=0xFF;
            color[2]=0xFF;
            color[3]=0xFF;
        }
        velocityX = (velocityX)-FloatConstants::One;
        if ((velocityX)<FloatConstants::Two)
            velocityX=2.0f;
        x += facing*(velocityX);
        y = y+velocityY;
        if (AdvanceNestedFrame()==(animationStageCount)) {
            ClearFrameInfo();
        }
    }
    break;
}
        case 0x370: {
    if ((owner->action)==0x133) {
        x = owner->x + (facing) * 260;
        y = (owner->y) + GeometryConstants::NinetySix;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    scaleX = (scaleX) + FloatConstants::ThreeTenths;
    scaleY = (scaleY) * FloatConstants::FourFifths;
    if ((color[0])>20)
        color[0]-=20;
    else {
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x371: {
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=0.85f;
        scaleY=0.85f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field01A=0x4E2;
        rotationX=-65.0f;
    }
    rotationZ = (rotationZ)-FloatConstants::TwentyTwoAndHalf;
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x384: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX = (field0C8)*FloatConstants::OneTenth;
        velocityY = (field0CC)*FloatConstants::OneTenth;
    }
    velocityY = (velocityY)-FloatConstants::ThreeFifths;
    x += facing*(velocityX);
    y = y + velocityY;
    if ((animationStage)<2) {
        rotationZ = (rotationZ)+GeometryConstants::Sixteen;
        if (y + velocityY <= FloatConstants::Zero) {
            owner->SpawnBattleEffect(0x388,x,y,facing,0);
            owner->PlaySound(8);
            ResetPrimaryCounters(0x385);
            if (g_OptionsModeAt006714D0>1)
                ResetPrimaryCounters(0x38E);
            y=0.0f;
            velocityY=0.0f;
            velocityX=0.0f;
            rotationZ=0.0f;
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetSecondaryCounter(1);
    break;
}
        case 0x385: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field0D8=0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.75f;
        scaleY=0.75f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        owner->SetCameraShake(5.0f);
        owner->SpawnBattleEffect(0x387,x,y,facing,1);
    }
    if ((field07C)==6) {
        field07C=0;
        ++field080;
    }
    scaleX = (scaleX)+FloatConstants::FourHundredths;
    scaleY = (scaleY)+FloatConstants::FourHundredths;
    if ((animationStage)>1) {
        if ((color[0])>=40)
            color[0]-=40;
        else {
            color[0]=0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    if ((animationStage)==2 && (animationFrame)==0)
        owner->SpawnBattleEffect(0x386,x,y,facing,1);
    break;
}
        case 0x386: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field0D8=0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.75f;
        scaleY=0.75f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
    }
    scaleX = (scaleX)+FloatConstants::FourHundredths;
    scaleY = (scaleY)+FloatConstants::FourHundredths;
    if ((color[0])>=20)
        color[0]-=20;
    else {
        color[0]=0;
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x387: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=0.75f;
        scaleY=0.75f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field01A=0x4E2;
        rotationX=-75.0f;
    }
    scaleX = (scaleX)+FloatConstants::FifteenHundredths;
    scaleY = (scaleY)+FloatConstants::FifteenHundredths;
    if ((animationStage)>1) {
        if ((color[0])>20)
            color[0]-=20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x388: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        SetPolarVelocity(-(RecordedRange(0,45)
             - FloatConstants::TwentyTwoAndHalf + GeometryConstants::Ninety),18.0f);
    }
    x += facing*(velocityX);
    y = y+velocityY;
    velocityY = (velocityY)-FloatConstants::EightyFiveHundredths;
    rotationZ = (rotationZ)+GeometryConstants::Fifteen;
    if ((y)<GeometryConstants::NegativeFourHundredEighty) {
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x389: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((field07C)==6) {
        field07C=0;
        field080=1;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field0D8=-30;
        field0DA=150;
        field0DC=0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
    }
    if ((animationStage)==4 && (animationFrame)==0) {
        owner->SpawnBattleEffect(0x371,x,
                    (y)+FloatConstants::Ten,facing,1);
        owner->PlaySound(2);
    }
    if ((animationStage)==0) {
        if ((color[0])<225)
            color[0]+=30;
        else
            color[0]=0xFF;
    }
    if ((animationStage)<8 && (field080)==0) {
        ResetSecondaryCounter((animationStage)+4);
        break;
    }
    if ((animationStage)>7) {
        scaleX=(scaleX)*FloatConstants::EightyFiveHundredthsDouble;
        scaleY=(scaleY)+FloatConstants::ThreeTenths;
        if ((color[0])>=10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetSecondaryCounter(8);
        break;
    }
    if ((animationFrame)==0)
        field07C=0;
    if ((animationStage)==8 && (animationFrame)==0 && (field0DC)<5) {
        ResetSecondaryCounter(4);
        ++field0DC;
    }
    break;
}
        case 0x38A: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        field080=1;
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field0D8=10;
        field0DA=0;
        field0DE=0;
        field0DC=0;
    }
    if ((animationStage)==1 && (animationFrame)==0) {
        owner->SpawnBattleEffect(0x389,x,y,facing,1);
    }
    if ((animationStage)>0) {
        field0DA = AngleAt00483300(
            owner->opponent->y - y + GeometryConstants::Hundred,
            (owner->opponent->x - x) * (facing)) / GeometryConstants::RadiansPerDegree;
        if ((field0DC)>(field0DA)) {
            if ((field0DC)-(field0DA)<=180) {
                field0DC-=2;
                if ((field0DC)<-180) field0DC+=360;
            } else {
                field0DC+=2;
                if ((field0DC)>180) field0DC-=360;
            }
        }
        if ((field0DC)<=(field0DA)) {
            if ((field0DC)-(field0DA)>=-180) {
                field0DC+=2;
                if ((field0DC)>180) field0DC-=360;
            } else {
                field0DC-=2;
                if ((field0DC)<-180) field0DC+=360;
            }
        }
    }
    SetPolarVelocity(field0DC,4.0f);
    x += facing*(velocityX);
    y = y - velocityY;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        if ((field0D8)<g_OptionsModeAt006714D0*5+10) {
            ++field0D8;
            ResetSecondaryCounter(1);
            break;
        }
        ClearFrameInfo();
        break;
    }
    break;
}
        case 0x38B: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        field07C=0;
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=(field0C8)*FloatConstants::OneTenth;
        velocityY=(field0CC)*FloatConstants::OneTenth;
        field0D8=RecordedRange(-480,960);
    }
    x += facing*(velocityX);
    y = y+velocityY;
    if ((animationStage)==0) {
        if ((color[0])<=235)
            color[0]+=20;
        else
            color[0]=0xFF;
        rotationZ=(rotationZ)+GeometryConstants::Eighteen;
        velocityY=(velocityY)-FloatConstants::ThreeFifths;
    }
    if ((animationStage)==12) {
        scaleX=(scaleX)*FloatConstants::EightyFiveHundredthsDouble;
        scaleY=(scaleY)+FloatConstants::ThreeTenths;
        if ((color[0])>=10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==1 && (animationFrame)==0) {
        velocityX=0.0f;
        velocityY=0.0f;
        rotationZ=0.0f;
    }
    if ((animationStage)==6 && (animationFrame)==0 && (field0DC)<0) {
        ResetSecondaryCounter(2);
        ++field0DC;
    }
    if ((animationStage)==8 && (animationFrame)==0) {
        (owner->field314)=field0D8;
        owner->field318=x;
        owner->field31C=y;
        owner->SpawnBattleEffect(0x38C,x,y,facing,1);
        owner->PlaySound(15);
    }
    if ((animationStage)==10 && (animationFrame)==0 && (field0DA)<6) {
        ++field0DA;
        ResetSecondaryCounter(9);
    }
    if ((animationStage)==11 && (animationFrame)==0) {
        owner->SpawnBattleEffect(0x38D,
            (field0D8) * (facing) + (x),
            0.0f,facing,1);
        owner->PlaySound(8);
    }
    break;
}
        case 0x38C: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX = MagnitudeAt00428D20(
            field0C8* field0C8 + field0D0* field0D0)
            / GeometryConstants::TwoHundredFiftySix * FloatConstants::OneAndOneTenth;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ = AngleAt00483300(field0D0,field0C8) / GeometryConstants::RadiansPerDegree;
    }
    scaleY=(scaleY)*FloatConstants::EightyFiveHundredthsDouble;
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x38D: {
    if ((animationStage)==0 && (animationFrame)==0) {
        field0D8=0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.25f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        owner->SetCameraShake(10.0f);
    }
    if ((field07C)==6) {
        field07C=0;
        ++field080;
    }
    if ((animationStage)==3 && (animationFrame)==0)
        owner->SpawnBattleEffect(0x343,x,y,facing,1);
    if ((animationStage)<3) {
        scaleX=(scaleX)+FloatConstants::SevenHundredths;
        scaleY=(scaleY)+FloatConstants::SevenHundredths;
    } else if ((animationStage)==3) {
        // Stage 3 deliberately leaves the scale unchanged.
    }
    if ((animationStage)==4) {
        scaleX=(scaleX)*FloatConstants::FourFifths;
        if ((color[0])>=20) {
            color[0]-=20;
            color[1]-=20;
            color[2]-=20;
        } else {
            color[0]=0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    if ((animationStage)==4 && (animationFrame)==0 && (field0D8)<5) {
        ++field0D8;
        ResetSecondaryCounter(3);
    }
    break;
}
        case 0x38E: {
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    if ((animationStage)==0 && (animationFrame)==0) {
        field0D8=0;
        ResetTransform(0.0f,0.0f,0.0f);
        field080=1;
        field07C=0;
        velocityY=0.0f;
        velocityX=0.0f;
        scaleX=0.75f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        owner->SetCameraShake(5.0f);
        owner->SpawnBattleEffect(0x387,x,y,facing,1);
    }
    if ((field07C)==6) {
        field07C=0;
        ++field080;
    }
    if (AdvanceNestedFrame()==(animationStageCount))
        ClearFrameInfo();
    break;
}
        case 0x3E3: {
    facing=1;
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=-1.0f;
        field0D8=RecordedRange(0,360)-180;
        field0DA=15;
    }
    if ((animationStage)==0) {
        --field0DA;
        if ((field0DA)<3) field0DA=3;
        SetPolarVelocity(field0D8,
                       field0DA*FloatConstants::FourFifths);
    }
    if ((animationStage)==1) {
        field0D8=AngleAt00483300(
            (owner->opponent->y) + GeometryConstants::Hundred - (y),
            owner->opponent->x-x) / GeometryConstants::RadiansPerDegree;
        SetPolarVelocity(field0D8,20.0f);
        if ((x - owner->opponent->x < GeometryConstants::Twenty) &&
            (x - owner->opponent->x > GeometryConstants::NegativeTwenty) &&
            (y - owner->opponent->y < GeometryConstants::HundredTwenty) &&
            (y - owner->opponent->y > GeometryConstants::Eighty)) {
            ClearFrameInfo();
            if ((owner->opponent->field366)<2)
                ++owner->opponent->field366;
            else
                (owner->opponent->score)+=20000;
            PlaySharedSound(0x2E);
            break;
        }
    }
    x=x+velocityX;
    y=y-velocityY;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetSecondaryCounter(1);
    break;
}
        case 0x3E4: {
    facing=1;
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=1.0f;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        velocityX=0.0f;
        velocityY=-1.0f;
        field0D8=RecordedRange(0,360)-180;
        field0DA=15;
    }
    if ((animationStage)==0) {
        --field0DA;
        if ((field0DA)<3) field0DA=3;
        SetPolarVelocity(field0D8,
                       field0DA*FloatConstants::FourFifths);
    }
    if ((animationStage)==1) {
        field0D8=AngleAt00483300(
            (owner->opponent->y) + GeometryConstants::Hundred - (y),
            owner->opponent->x-x) / GeometryConstants::RadiansPerDegree;
        SetPolarVelocity(field0D8,20.0f);
        if ((x - owner->opponent->x < GeometryConstants::Twenty) &&
            (x - owner->opponent->x > GeometryConstants::NegativeTwenty) &&
            (y - owner->opponent->y < GeometryConstants::HundredTwenty) &&
            (y - owner->opponent->y > GeometryConstants::Eighty)) {
            ++(owner->fieldEFA);
            PlaySharedSound(0x2E);
            ClearFrameInfo();
            if ((owner->opponent->spiritCooldown)>0) {
                if ((owner->opponent->spiritCooldown)>5)
                    (owner->opponent->spiritCooldown)-=5;
                else {
                    (owner->opponent->spiritCooldown)=0;
                    (owner->opponent->spirit)=1000;
                }
                break;
            }
            if ((owner->opponent->spirit)<990)
                (owner->opponent->spirit)+=10;
            else {
                (owner->opponent->spirit)=1000;
                if ((owner->opponent->field39C)==0) {
                    if ((owner->opponent->field36C)<FloatConstants::NineHundredNinetyEightAndNineTenths)
                        (owner->opponent->field36C)=(owner->opponent->field36C)+FloatConstants::Half;
                    else
                        (owner->opponent->field36C)=900.0f;
                }
            }
            break;
        }
    }
    x=x+velocityX;
    y=y-velocityY;
    if (AdvanceNestedFrame()==(animationStageCount))
        ResetSecondaryCounter(1);
    break;
}
        case 0x3E5: {
    x=owner->x;
    y=0.0f;
    field08A=1;
    if ((animationStage)==0 && (animationFrame)==0) {
        ResetTransform(0.0f,0.0f,0.0f);
        scaleX=3.0f;
        scaleY=3.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        field01A=0x4E2;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        rotationX=-80.0f;
        field0D8=(owner->field3A0);
    }
    if ((owner->field3A0)<=0) {
        ClearFrameInfo();
        break;
    }
    scaleX=static_cast<float>((owner->field3A0))/(field0D8)*2.0f;
    scaleY=static_cast<float>((owner->field3A0))/(field0D8)*2.0f;
    rotationZ=(rotationZ)+FloatConstants::One;
    if (AdvanceNestedFrame()==(animationStageCount)) {
        ResetSecondaryCounter(9);
        break;
    }
    break;
}
        default: AdvanceNestedFrame();
    }
}
