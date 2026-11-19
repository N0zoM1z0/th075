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
extern float gFloatAt00657850;
extern float gMulAt006590B4;
extern float gAddAt00659738;
extern double gMulDoubleAt00659730;
extern float gAddAt006583FC;
extern float gSubAt00659090;
extern float gSubtractAt00659728;
extern float gOffsetAt006581DC;
extern float gVelocityDragAt00659454;
extern float gMaxPositionAt0065912C;
extern float gStageOffsetAt006590AC;
extern float gScatterRateAt006578C0;
extern float gScatterBaseAt006581E0;
extern float gShrinkAt00659094;
extern float gGrowAt00657CBC;
extern float gGrowAt00657478;
extern float gCollisionAt00657888;
extern float gAngleUnitAt00657828;
extern float gTouchMaxAt00659230;
extern float gVerticalTouchMaxAt00658268;
extern double gDoubleTouchAt00659228;
extern float gNextBonusAt00657478;
extern float gLengthDivisorAt006583A0;
extern float gLengthFactorAt00659720;
extern float MagnitudeAt00428D20(float value);
extern float AngleAt00483300(float first, float second);
extern float gCompareAt0065782C;
extern float gCompareAt0065747C;
extern float gCompareAt00657480;
extern float gCompareAt00657CF8;
extern float gCompareAt00657D14;
extern float gCompareAt00657874;
extern float gDropAt00658058;
extern float gLiftAt00657CC0;
extern float gCurveAt0065972C;
extern float gStepAt00658044;
extern float gFadeAt006583F8;
extern float gFadeAt00659428;
extern float gAbsScaleAt00659724;
extern float gStageContactAt0065786C;
extern float gParentYAt006590A8;
extern float gParentYAt006590A0;
extern signed char gGlobalActorCountAt006714D0;
extern float gParentYExtraAt00658264;
extern float gBoundRightAt00659248;
extern float gBoundLowerAt0065930C;
extern float gBoundUpperAt00658E80;
extern float gFadeAt0065825C;
extern float gMotionDecelAt00657480;
extern float gInitialClampAt00657D14;
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
                                  (y) + gFloatAt00657850,
                                  facing, 1);
            owner->PlaySound(2);
        }
        if ((animationStage) == 0) {
            SetPolarVelocity(static_cast<float>(field0D8),
                            static_cast<float>(field0DA)*gMulAt006590B4);
            field0DA -= 5;
            field0D8 += 3;
            rotationZ = (rotationZ) + gAddAt00659738;
            if ((field0DA) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += static_cast<float>(facing) * (velocityX);
        y = y - velocityY;
        if ((animationStage) < 5 && (field080) == 0) {
            ResetSecondaryCounter((animationStage) + 4);
            break;
        }
        if ((animationStage) > 4) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
                                  (y) + gFloatAt00657850,
                                  facing, 1);
            owner->PlaySound(2);
        }
        if ((animationStage) == 0) {
            SetPolarVelocity(static_cast<float>(field0D8),
                            static_cast<float>(field0DA)*gMulAt006590B4);
            field0DA -= 5;
            field0D8 -= 2;
            rotationZ = (rotationZ) + gAddAt00659738;
            if ((field0DA) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += static_cast<float>(facing) * (velocityX);
        y = y - velocityY;
        if ((animationStage) < 5 && (field080) == 0) {
            ResetSecondaryCounter((animationStage) + 4);
            break;
        }
        if ((animationStage) > 4) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
                                  (y) + gFloatAt00657850,
                                  facing, 1);
            owner->PlaySound(2);
        }
        if ((animationStage) == 0) {
            SetPolarVelocity(static_cast<float>(field0D8),
                            static_cast<float>(field0DA)*gMulAt006590B4);
            field0DA -= 5;
            field0D8 += 4;
            rotationZ = (rotationZ) + gAddAt00659738;
            if ((field0DA) <= 0) {
                velocityX = 0.0f;
                velocityY = 0.0f;
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                break;
            }
        }
        x += static_cast<float>(facing) * (velocityX);
        y = y - velocityY;
        if ((animationStage) < 5 && (field080) == 0) {
            ResetSecondaryCounter((animationStage) + 4);
            break;
        }
        if ((animationStage) > 4) {
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
            if (field0C8 == gCompareAt0065782C) {
                velocityX = 5.0f;
                velocityY = 6.0f;
            }
            if (field0C8 == gCompareAt0065747C) {
                velocityX = 3.0f;
                velocityY = 8.0f;
            }
            if (field0C8 == gCompareAt00657480) {
                velocityX = 1.0f;
                velocityY = 10.0f;
            }
            if (field0C8 == gCompareAt00657CF8) {
                velocityX = -5.0f;
                velocityY = 6.0f;
            }
            if (field0C8 == gCompareAt00657D14) {
                velocityX = -3.0f;
                velocityY = 8.0f;
            }
            if (field0C8 == gCompareAt00657874) {
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
        velocityY = (velocityY) - gDropAt00658058;
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) < 2) {
            rotationZ = (rotationZ) + gLiftAt00657CC0;
            if (y + velocityY <= gCompareAt0065782C) {
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
        if (AdvanceNestedFrame() == (field070))
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
    scaleX = (float)(5 - (animationFrame)) * gCurveAt0065972C * ((animationFrame) < 5) + gStepAt00658044 + (scaleX);
    scaleY = (float)(5 - (animationFrame)) * gCurveAt0065972C * ((animationFrame) < 5) + gStepAt00658044 + (scaleY);
    if ((animationStage) > 1) {
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) < 2) {
            rotationZ = (rotationZ) + gLiftAt00657CC0;
            if (y + velocityY <= gCompareAt0065782C) {
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
        if (AdvanceNestedFrame() == (field070))
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
    scaleX = (scaleX) + gFadeAt006583F8;
    scaleY = (scaleY) + gFadeAt006583F8;
    if ((animationStage) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
    scaleX = (scaleX) + gFadeAt00659428;
    scaleY = (scaleY) + gFadeAt00659428;
    color[0] -= 10;
    if (AdvanceNestedFrame() == (field070))
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gAddAt006583FC;
        }
        if ((animationStage) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
            (owner->field318) = static_cast<float>(RecordedRange(0,10) - 5);
            owner->SpawnBattleEffect(0x320,
                   static_cast<float>((facing) * 10) + (x),
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gSubAt00659090;
        }
        if ((animationStage) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
            (owner->field318) = static_cast<float>(RecordedRange(0,15) - 45);
            owner->SpawnBattleEffect(0x321,
                   static_cast<float>((facing) * 10) + (x),
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gAddAt006583FC;
        }
        if ((animationStage) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
            (owner->field318) = static_cast<float>(RecordedRange(0,10) - 5);
            owner->SpawnBattleEffect(0x322,
                   static_cast<float>((facing) * 10) + (x),
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
            rotationZ = (rotationZ) + gGrowAt00657CBC;
            velocityY = (velocityY) + gGrowAt00657478;
        }
        x += static_cast<float>(facing) * (velocityX);
        y = y - velocityY;
        if ((animationStage) == 10 && y - velocityY <= gCollisionAt00657888) {
            velocityX = 2.0f;
            velocityY = 2.0f;
            ResetSecondaryCounter(11);
        }
        if ((animationStage) > 10 && (field0D8) > 2) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
                static_cast<float>(field0DC) < gCompareAt0065782C + field0CC) {
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
    scaleX = (scaleX) + gFadeAt00659428;
    scaleY = (scaleY) + gFadeAt00659428;
    if ((animationStage) > 1) {
        if ((color[0]) >= 20)
            color[0] -= 20;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
    scaleX = (scaleX) + gFadeAt00659428;
    scaleY = (scaleY) + gFadeAt00659428;
    if ((animationStage) > 1) {
        if ((color[0]) >= 40)
            color[0] -= 40;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
    scaleX = (scaleX) + gAddAt006583FC;
    scaleY = (scaleY) + gAddAt006583FC;
    if ((animationStage) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
        SetPolarVelocity(-(static_cast<float>(RecordedRange(0,45))
                - gSubtractAt00659728 + gOffsetAt006581DC),18.0f);
    }
    x += static_cast<float>(facing) * (velocityX);
    y = y + velocityY;
    velocityY = (velocityY) - gVelocityDragAt00659454;
    rotationZ = (rotationZ) + gGrowAt00657CBC;
    if ((y) < gMaxPositionAt0065912C) {
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame() == (field070))
        ClearFrameInfo();
    break;
}
        case 0x33C: {
    if ((owner->action) == 0x2BE) {
        x = owner->x + static_cast<float>((facing) * 65);
        y = (owner->y) + gStageOffsetAt006590AC;
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
        scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
        scaleY = (scaleY) + gAddAt006583FC;
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070)) {
        ResetSecondaryCounter(1);
        break;
    }
    break;
}
        case 0x33D: {
    if ((owner->action) == 0x2C1) {
        x = owner->x + static_cast<float>((facing) * 65);
        y = (owner->y) + gStageOffsetAt006590AC;
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
        scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
        scaleY = (scaleY) + gAddAt006583FC;
        if ((color[0]) >= 10)
            color[0] -= 10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070)) {
        ResetSecondaryCounter(1);
        break;
    }
    break;
}
        case 0x33E: {
    if ((owner->action) == 0x2BE) {
        x = owner->x + static_cast<float>((facing) * 140);
        y = (owner->y) + gStageOffsetAt006590AC;
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
                  * gScatterRateAt006578C0 + gScatterBaseAt006581E0;
    if ((animationStage) == 7)
        scaleY = (scaleY) * gShrinkAt00659094;
    if (AdvanceNestedFrame() == (field070))
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
        x = owner->x + static_cast<float>((facing) * 180);
        y = (owner->y) + gStageOffsetAt006590AC;
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
    if (AdvanceNestedFrame() == (field070))
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
            owner->x + static_cast<float>((owner->facing)*90) - (owner->opponent->x)
        ) * gAbsScaleAt00659724;
        if ((velocityX) < gInitialClampAt00657D14)
            velocityX = 4.0f;
        velocityY = 20.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    velocityY = (velocityY) - gMotionDecelAt00657480;
    x += static_cast<float>(facing) * (velocityX);
    y = y + velocityY;
    if ((animationStage) < 2) {
        rotationZ = (rotationZ) + gLiftAt00657CC0;
        if (y + velocityY <= gCompareAt0065782C) {
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
    if (AdvanceNestedFrame() == (field070))
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
            owner->x + static_cast<float>((owner->facing)*90) - (owner->opponent->x)
        ) * gAbsScaleAt00659724;
        if ((velocityX) < gInitialClampAt00657D14)
            velocityX = 4.0f;
        velocityY = 20.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0xFF;
        color[1] = 0xFF;
        color[2] = 0xFF;
        color[3] = 0xFF;
    }
    velocityY = (velocityY) - gMotionDecelAt00657480;
    x += static_cast<float>(facing) * (velocityX);
    y = y + velocityY;
    if ((animationStage) < 2) {
        rotationZ = (rotationZ) + gLiftAt00657CC0;
        if (y + velocityY <= gCompareAt0065782C) {
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
    if (AdvanceNestedFrame() == (field070))
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
    if (AdvanceNestedFrame() == (field070))
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
    scaleX = (scaleX) + gFadeAt0065825C;
    scaleY = (scaleY) + gFadeAt0065825C;
    if ((animationStage) > -1) {
        if ((color[0]) >= 20)
            color[0] -= 20;
        else {
            color[0] = 0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
    scaleX = (scaleX) + gAddAt006583FC;
    scaleY = (scaleY) + gAddAt006583FC;
    if ((animationStage) > 1) {
        if ((color[0]) > 20)
            color[0] -= 20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame() == (field070))
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((x) > gBoundRightAt00659248 ||
            (x) < gBoundLowerAt0065930C ||
            (y) < gBoundLowerAt0065930C ||
            (y) > gBoundUpperAt00658E80) {
            ClearFrameInfo();
            break;
        }
        if (AdvanceNestedFrame() == (field070))
            ResetSecondaryCounter(6);
        break;
    }
    if ((animationStage) == 1) {
        rotationZ = (rotationZ) + gGrowAt00657CBC;
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
        SetPolarVelocity(static_cast<float>(field0D8),
                       static_cast<float>(field0DA));
    }
    if ((animationStage) < 6 && (static_cast<AliceFighter*>(owner)->fieldF12) < 2) {
        field0D8 = static_cast<short>(
            static_cast<float>((static_cast<AliceFighter*>(owner)->fieldF10)-180) + (field0C8));
        if ((field0D8) > 180) field0D8 -= 360;
        if ((field0D8) < -180) field0D8 += 360;
        SetPolarVelocity(static_cast<float>(field0D8),
                       static_cast<float>(field0DA));
        x = static_cast<int>(
            (owner->fieldF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            (owner->fieldF0E) + (velocityY));
        if ((field0DA) < 140) field0DA += 7;
        if ((field0DA) > 140) field0DA = 140;
    }
    if (AdvanceNestedFrame() == (field070)) ResetSecondaryCounter(6);
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
        (owner->fieldF0C) = static_cast<short>(x);
        (owner->fieldF0E) = static_cast<short>(y);
        velocityX = (velocityX) - gCompareAt0065747C;
        if ((velocityX) < gCompareAt0065782C)
            velocityX = 0.0f;
    }
    x += static_cast<float>(facing) * (velocityX);
    if (AdvanceNestedFrame() == (field070)) {
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((x) > gBoundRightAt00659248 ||
            (x) < gBoundLowerAt0065930C ||
            (y) < gBoundLowerAt0065930C ||
            (y) > gBoundUpperAt00658E80) {
            ClearFrameInfo();
            break;
        }
        if (AdvanceNestedFrame() == (field070))
            ResetSecondaryCounter(6);
        break;
    }
    if ((animationStage) == 1) {
        rotationZ = (rotationZ) + gGrowAt00657CBC;
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
        SetPolarVelocity(static_cast<float>(field0D8),
                       static_cast<float>(field0DA));
    }
    if ((animationStage) < 6 && (static_cast<AliceFighter*>(owner)->fieldF12) < 2) {
        field0D8 = static_cast<short>(
            static_cast<float>((static_cast<AliceFighter*>(owner)->fieldF10)-180) + (field0C8));
        if ((field0D8) > 180) field0D8 -= 360;
        if ((field0D8) < -180) field0D8 += 360;
        SetPolarVelocity(static_cast<float>(field0D8),
                       static_cast<float>(field0DA));
        x = static_cast<int>(
            (owner->fieldF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            (owner->fieldF0E) + (velocityY));
        if ((field0DA) < 120) field0DA += 6;
        if ((field0DA) > 120) field0DA = 120;
    }
    if (AdvanceNestedFrame() == (field070)) ResetSecondaryCounter(6);
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((x) > gBoundRightAt00659248 ||
            (x) < gBoundLowerAt0065930C ||
            (y) < gBoundLowerAt0065930C ||
            (y) > gBoundUpperAt00658E80) {
            ClearFrameInfo();
            break;
        }
        if (AdvanceNestedFrame() == (field070))
            ResetSecondaryCounter(6);
        break;
    }
    if ((animationStage) == 1) {
        rotationZ = (rotationZ) + gGrowAt00657CBC;
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
        SetPolarVelocity(static_cast<float>(-(field0D8) + 180),
                       static_cast<float>(field0DA));
    }
    if ((animationStage) < 6 && (static_cast<AliceFighter*>(owner)->fieldF12) < 2) {
        field0D8 = static_cast<short>(
            static_cast<float>((static_cast<AliceFighter*>(owner)->fieldF10)-180) + (field0C8));
        if ((field0D8) > 180) field0D8 -= 360;
        if ((field0D8) < -180) field0D8 += 360;
        SetPolarVelocity(static_cast<float>(-(field0D8)),
                       static_cast<float>(field0DA));
        x = static_cast<int>(
            (owner->fieldF0C) + (facing)*(velocityX));
        y = static_cast<int>(
            (owner->fieldF0E) + (velocityY));
        if ((field0DA) < 200) field0DA += 10;
        if ((field0DA) > 200) field0DA = 200;
    }
    if (AdvanceNestedFrame() == (field070)) ResetSecondaryCounter(6);
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
        (owner->fieldF0C) = static_cast<short>(x);
        (owner->fieldF0E) = static_cast<short>(y);
        velocityX = (velocityX) - gCompareAt0065747C;
        if ((velocityX) < gCompareAt0065782C)
            velocityX = 0.0f;
    }
    x += static_cast<float>(facing) * (velocityX);
    if (AdvanceNestedFrame() == (field070)) {
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gAddAt006583FC;
            if (y + velocityY <= gStageContactAt0065786C) {
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
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
            (owner->field318) = static_cast<float>(RecordedRange(0,60));
            owner->SpawnBattleEffect(0x323,
                   static_cast<float>((facing) * 10) + (x),
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
        x += static_cast<float>(facing) * (velocityX);
        y = y + velocityY;
        if ((animationStage) == 0) {
            if ((color[0]) <= 0xEB)
                color[0] += 20;
            else
                color[0] = 0xFF;
            rotationZ = (rotationZ) + gAddAt00659738;
            velocityY = (velocityY) - gGrowAt00657478;
        }
        if ((animationStage) == 11) {
            scaleX = static_cast<float>((scaleX) * gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
            (owner->field318) = static_cast<float>(RecordedRange(0,15) - 60);
            owner->SpawnBattleEffect(0x324,
                   static_cast<float>((facing) * 10) + (x),
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
            x = owner->x + static_cast<float>((facing)*60);
            y = (owner->y) + gParentYAt006590A8;
            if ((owner->action) == 0x19A)
                y = (owner->y) + gParentYExtraAt00658264;
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
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY) + gAddAt006583FC;
            if ((color[0]) >= 10)
                color[0] -= 10;
            else {
                ClearFrameInfo();
                break;
            }
        }
        if (AdvanceNestedFrame() == (field070)) {
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
                (owner->field318) = static_cast<float>(RecordedRange(0,10) - 5);
                owner->SpawnBattleEffect(0x322,
                    static_cast<float>((facing)*10) + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
            if ((owner->action) == 0x19A) {
                (owner->field314) = 1000.0f;
                (owner->field318) = static_cast<float>(RecordedRange(0,10) + 30);
                owner->SpawnBattleEffect(0x323,
                    static_cast<float>((facing)*10) + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
            if ((owner->action) == 0x19C) {
                (owner->field314) = 1000.0f;
                (owner->field318) = static_cast<float>(RecordedRange(0,10) - 5);
                owner->SpawnBattleEffect(0x324,
                    static_cast<float>((facing)*10) + (x),
                    y, facing,1);
                owner->PlaySound(6);
            }
            if ((owner->action) == 0x19D) {
                (owner->field314) = 1000.0f;
                (owner->field318) = static_cast<float>(-RecordedRange(0,10) - 30);
                owner->SpawnBattleEffect(0x325,
                    static_cast<float>((facing)*10) + (x),
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
        velocityY = (velocityY) - gSubAt00659090;
        x += static_cast<float>(facing)*(velocityX);
        y = y + velocityY;
        if ((animationStage)<2) {
            rotationZ = (rotationZ)+gLiftAt00657CC0;
            if (y + velocityY <= gCompareAt0065782C) {
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
        if (AdvanceNestedFrame()==(field070))
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
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY)+gAddAt006583FC;
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
        velocityX = (velocityX)-gCompareAt0065747C;
        if ((velocityX)<gMotionDecelAt00657480)
            velocityX=2.0f;
        x += static_cast<float>(facing)*(velocityX);
        y = y+velocityY;
        if (AdvanceNestedFrame()==(field070)) {
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
            scaleX = static_cast<float>((scaleX)*gMulDoubleAt00659730);
            scaleY = (scaleY)+gAddAt006583FC;
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
        velocityX = (velocityX)-gCompareAt0065747C;
        if ((velocityX)<gMotionDecelAt00657480)
            velocityX=2.0f;
        x += static_cast<float>(facing)*(velocityX);
        y = y+velocityY;
        if (AdvanceNestedFrame()==(field070)) {
            ClearFrameInfo();
        }
    }
    break;
}
        case 0x370: {
    if ((owner->action)==0x133) {
        x = owner->x + static_cast<float>((facing)*260);
        y = (owner->y) + gParentYAt006590A0;
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
    scaleX = (scaleX) + gAddAt006583FC;
    scaleY = (scaleY) * gSubAt00659090;
    if ((color[0])>20)
        color[0]-=20;
    else {
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame()==(field070))
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
    rotationZ = (rotationZ)-gSubtractAt00659728;
    if (AdvanceNestedFrame()==(field070))
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
        velocityX = (field0C8)*gMulAt006590B4;
        velocityY = (field0CC)*gMulAt006590B4;
    }
    velocityY = (velocityY)-gDropAt00658058;
    x += static_cast<float>(facing)*(velocityX);
    y = y + velocityY;
    if ((animationStage)<2) {
        rotationZ = (rotationZ)+gLiftAt00657CC0;
        if (y + velocityY <= gCompareAt0065782C) {
            owner->SpawnBattleEffect(0x388,x,y,facing,0);
            owner->PlaySound(8);
            ResetPrimaryCounters(0x385);
            if (gGlobalActorCountAt006714D0>1)
                ResetPrimaryCounters(0x38E);
            y=0.0f;
            velocityY=0.0f;
            velocityX=0.0f;
            rotationZ=0.0f;
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070))
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
    scaleX = (scaleX)+gAbsScaleAt00659724;
    scaleY = (scaleY)+gAbsScaleAt00659724;
    if ((animationStage)>1) {
        if ((color[0])>=40)
            color[0]-=40;
        else {
            color[0]=0;
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070))
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
    scaleX = (scaleX)+gAbsScaleAt00659724;
    scaleY = (scaleY)+gAbsScaleAt00659724;
    if ((color[0])>=20)
        color[0]-=20;
    else {
        color[0]=0;
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame()==(field070))
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
    scaleX = (scaleX)+gFadeAt006583F8;
    scaleY = (scaleY)+gFadeAt006583F8;
    if ((animationStage)>1) {
        if ((color[0])>20)
            color[0]-=20;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070))
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
        SetPolarVelocity(-(static_cast<float>(RecordedRange(0,45))
             - gSubtractAt00659728 + gOffsetAt006581DC),18.0f);
    }
    x += static_cast<float>(facing)*(velocityX);
    y = y+velocityY;
    velocityY = (velocityY)-gVelocityDragAt00659454;
    rotationZ = (rotationZ)+gGrowAt00657CBC;
    if ((y)<gMaxPositionAt0065912C) {
        ClearFrameInfo();
        break;
    }
    if (AdvanceNestedFrame()==(field070))
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
                    (y)+gFloatAt00657850,facing,1);
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
        scaleX=static_cast<float>((scaleX)*gMulDoubleAt00659730);
        scaleY=(scaleY)+gAddAt006583FC;
        if ((color[0])>=10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
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
        field0DA = static_cast<short>(AngleAt00483300(
            owner->opponent->y - y + gCollisionAt00657888,
            (owner->opponent->x - x) * (facing)) / gAngleUnitAt00657828);
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
    SetPolarVelocity(static_cast<float>(field0DC),4.0f);
    x += static_cast<float>(facing)*(velocityX);
    y = y - velocityY;
    if (AdvanceNestedFrame()==(field070)) {
        if ((field0D8)<gGlobalActorCountAt006714D0*5+10) {
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
        velocityX=(field0C8)*gMulAt006590B4;
        velocityY=(field0CC)*gMulAt006590B4;
        field0D8=static_cast<short>(RecordedRange(-480,960));
    }
    x += static_cast<float>(facing)*(velocityX);
    y = y+velocityY;
    if ((animationStage)==0) {
        if ((color[0])<=235)
            color[0]+=20;
        else
            color[0]=0xFF;
        rotationZ=(rotationZ)+gAddAt00659738;
        velocityY=(velocityY)-gDropAt00658058;
    }
    if ((animationStage)==12) {
        scaleX=static_cast<float>((scaleX)*gMulDoubleAt00659730);
        scaleY=(scaleY)+gAddAt006583FC;
        if ((color[0])>=10)
            color[0]-=10;
        else {
            ClearFrameInfo();
            break;
        }
    }
    if (AdvanceNestedFrame()==(field070)) {
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
        (owner->field314)=static_cast<float>(field0D8);
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
            static_cast<float>((field0D8)*(facing)) + (x),
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
            / gLengthDivisorAt006583A0 * gLengthFactorAt00659720;
        scaleY=1.0f;
        color[0]=0xFF;
        color[1]=0xFF;
        color[2]=0xFF;
        color[3]=0xFF;
        rotationZ = AngleAt00483300(field0D0,field0C8) / gAngleUnitAt00657828;
    }
    scaleY=static_cast<float>((scaleY)*gMulDoubleAt00659730);
    if (AdvanceNestedFrame()==(field070))
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
        scaleX=(scaleX)+gFadeAt00659428;
        scaleY=(scaleY)+gFadeAt00659428;
    }
    if ((animationStage)==4) {
        scaleX=(scaleX)*gSubAt00659090;
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
    if (AdvanceNestedFrame()==(field070))
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
    if (AdvanceNestedFrame()==(field070))
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
        field0D8=static_cast<short>(RecordedRange(0,360)-180);
        field0DA=15;
    }
    if ((animationStage)==0) {
        --field0DA;
        if ((field0DA)<3) field0DA=3;
        SetPolarVelocity(static_cast<float>(field0D8),
                       static_cast<float>(field0DA)*gSubAt00659090);
    }
    if ((animationStage)==1) {
        field0D8=static_cast<short>(AngleAt00483300(
            (owner->opponent->y) + gCollisionAt00657888 - (y),
            owner->opponent->x-x) / gAngleUnitAt00657828);
        SetPolarVelocity(static_cast<float>(field0D8),20.0f);
        if ((x - owner->opponent->x < gStageContactAt0065786C) &&
            (x - owner->opponent->x > gTouchMaxAt00659230) &&
            (y - owner->opponent->y < gParentYAt006590A8) &&
            (y - owner->opponent->y > gVerticalTouchMaxAt00658268)) {
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
    if (AdvanceNestedFrame()==(field070))
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
        field0D8=static_cast<short>(RecordedRange(0,360)-180);
        field0DA=15;
    }
    if ((animationStage)==0) {
        --field0DA;
        if ((field0DA)<3) field0DA=3;
        SetPolarVelocity(static_cast<float>(field0D8),
                       static_cast<float>(field0DA)*gSubAt00659090);
    }
    if ((animationStage)==1) {
        field0D8=static_cast<short>(AngleAt00483300(
            (owner->opponent->y) + gCollisionAt00657888 - (y),
            owner->opponent->x-x) / gAngleUnitAt00657828);
        SetPolarVelocity(static_cast<float>(field0D8),20.0f);
        if ((x - owner->opponent->x < gStageContactAt0065786C) &&
            (x - owner->opponent->x > gTouchMaxAt00659230) &&
            (y - owner->opponent->y < gParentYAt006590A8) &&
            (y - owner->opponent->y > gVerticalTouchMaxAt00658268)) {
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
                    if ((owner->opponent->field36C)<gDoubleTouchAt00659228)
                        (owner->opponent->field36C)=(owner->opponent->field36C)+gNextBonusAt00657478;
                    else
                        (owner->opponent->field36C)=900.0f;
                }
            }
            break;
        }
    }
    x=x+velocityX;
    y=y-velocityY;
    if (AdvanceNestedFrame()==(field070))
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
    rotationZ=(rotationZ)+gCompareAt0065747C;
    if (AdvanceNestedFrame()==(field070)) {
        ResetSecondaryCounter(9);
        break;
    }
    break;
}
        default: AdvanceNestedFrame();
    }
}
