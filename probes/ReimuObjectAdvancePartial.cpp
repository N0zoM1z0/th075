// Partial natural-C++ reconstruction of ReimuObject::Advance at 00476A40.
// The original parent is 50,915 bytes. This research source covers 180 action
// values: 46 behavior-specific states and 134 frame-only remap states.
// Other original actions remain unrepresented; this is not a complete
// replacement or an exactness claim.
#include "CharacterObject.hpp"
#include "ReimuFighter.hpp"

extern float __cdecl AngleAt00483300(float y, float x);

// Address-anchored constants used by the recovered action handlers. Their
// values are read-only game data; names remain local to this partial parent
// until their shared semantic identity is established.
extern const float g_ReimuObjectRightBoundAt0065925C;
extern const float g_ReimuObjectLeftBoundAt00659258;
extern const float g_ReimuObjectAngleUnitAt00657828;
extern const float g_ReimuObjectDirectionMarker0At0065782C;
extern const float g_ReimuObjectDirectionMarker1At0065747C;
extern const float g_ReimuObjectScalarAt00657480;
extern const float g_ReimuObjectDirectionMarker3At00657CF8;
extern const float g_ReimuObjectScaleStepAt00658348;
extern const float g_ReimuObjectDirectionMarker4At00657D14;
extern const float g_ReimuObjectDirectionMarker5At00657874;
extern const float g_ReimuObjectScalarAt00658290;
extern const float g_ReimuObjectDirectionMarker7At00659254;
extern const float g_ReimuObjectEffectSpreadAt00657CBC;
extern const float g_ReimuObjectScalarAt006590B4;
extern const float g_ReimuObjectSpeedScaleAt00658044;
extern const float g_ReimuObjectScalarAt00657850;
extern const float g_ReimuObjectOwnerOffsetAt006590A4;
extern const float g_ReimuObjectRightBoundAt00659250;
extern const float g_ReimuObjectLeftBoundAt00658344;
extern const float g_ReimuObjectUpperBoundAt00658E80;
extern const float g_ReimuObjectLowerBoundAt00657880;
extern const float g_ReimuObjectUpperBoundAt006583B4;
extern const float g_ReimuObjectLowerBoundAt00658374;
extern const float g_ReimuObjectUpperBoundAt00657884;
extern const float g_ReimuObjectLowerBoundAt0065924C;
extern const float g_ReimuObjectRotationStepAt006590C4;
extern const float g_ReimuObjectOwnerYOffsetAt00659080;
extern const float g_ReimuObjectScaleMultiplierAt00659090;
extern const float g_ReimuObjectScaleIncrementAt006583FC;
extern const float g_ReimuObjectRightBoundAt00659248;
extern const float g_ReimuObjectFullRotationAt00657864;
extern const float g_ReimuObjectHalfAt00657478;
extern const float g_ReimuObjectScaleCeilingAt006581E0;
extern const float g_ReimuObjectVerticalSpringAt00658354;
extern const float g_ReimuObjectHorizontalDriftAt006578C0;
extern const float g_ReimuObjectScaleBaseAt00659240;
extern const float g_ReimuObjectScaleFadeAt0065923C;
extern const float g_ReimuObjectVerticalLowerLimitAt00659244;
extern float g_AngleShiftAt00657878;
extern double g_RiseAt00658050;
extern const float g_ReimuObjectContactProjectionAt00657888;
extern const float g_ReimuObjectRotationStepAt00657D70;

void ReimuObject::Advance()
{
    if (owner->opponent->field3BA == 0 &&
        (owner->field3BA == 0 || field08A != 0)) {
        if (field082 == 0) {
            switch (action) {
            case 800:
                if (g_ReimuObjectRightBoundAt0065925C < x ||
                    x < g_ReimuObjectLeftBoundAt00659258 ||
                    g_ReimuObjectUpperBoundAt006583B4 < y ||
                    y < g_ReimuObjectLowerBoundAt00658374) {
                    ClearFrameInfo();
                }
                else if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
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
                            (owner->opponent->y - y) + g_ReimuObjectContactProjectionAt00657888,
                            (owner->opponent->x - x) * facing) /
                            g_ReimuObjectAngleUnitAt00657828);
                        if (field0DC + 10 < field0DA) {
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
                        static_cast<float>(field0D8) * g_ReimuObjectScalarAt006590B4 +
                        g_ReimuObjectScalarAt00658290);
                    field0DE = field0DE + 0x1E;
                    field0D8 = field0D8 + 2;
                    if (animationStage > 0 && field0DA < 0x3C) {
                        if (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888 < y) {
                            field0C8 = field0C8 + g_ReimuObjectScalarAt00657480;
                        }
                        if (y < owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) {
                            field0C8 = field0C8 - g_ReimuObjectScalarAt00657480;
                        }
                        field0DA = field0DA + 1;
                    }
                    x = facing * velocityX + x;
                    y = y - velocityY;
                    rotationZ = rotationZ + g_ReimuObjectRotationStepAt00657D70;
                    if (field07C != 0 && field07C != 6) {
                        ResetSecondaryCounter(3);
                    }
                    if (animationStage > 2) {
                        if (color[0] < 0x19) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 0x19;
                        }
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                    }
                }
                else {
                    ClearFrameInfo();
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    if (owner->fieldEFA > 0x19) {
                        owner->fieldEFA = 0;
                        owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
                    }
                }
                break;

            case 0x321:
                if (g_ReimuObjectRightBoundAt0065925C < x ||
                    x < g_ReimuObjectLeftBoundAt00659258) {
                    ClearFrameInfo();
                }
                else if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = 5.0f;
                            velocityX = 11.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = 6.0f;
                            velocityX = 8.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00657480) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = -5.0f;
                            velocityX = 11.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = -6.0f;
                            velocityX = 8.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
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
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            owner->SpawnBattleEffect(
                                0x325, x - facing * 30, field0CC, facing, 1);
                        }
                    }
                }
                break;

            case 0x322:
                if (g_ReimuObjectRightBoundAt0065925C < x ||
                    x < g_ReimuObjectLeftBoundAt00659258) {
                    ClearFrameInfo();
                }
                else if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = 5.0f;
                            velocityX = 25.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = 6.0f;
                            velocityX = 22.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00657480) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = -5.0f;
                            velocityX = 25.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            velocityY = -6.0f;
                            velocityX = 22.0f;
                            rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                g_ReimuObjectAngleUnitAt00657828;
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
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            owner->SpawnBattleEffect(
                                0x325, x - facing * 30, field0CC, facing, 1);
                        }
                    }
                }
                break;

            case 0x324:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (field07C == 6) {
                        field07C = 0;
                        field080 = 1;
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
                        field080 = 1;
                        field07C = 0;
                    }
                    if (field07C == 4 && field0D8 < 6) {
                        field080 = 1;
                        ++field0D8;
                        field07C = 0;
                    }
                    if (field080 == 0 && animationStage == 1) {
                        ResetSecondaryCounter(2);
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

            case 0x325:
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 0xFF;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                    color[3] = 0xFF;
                }
                scaleX = scaleX + g_ReimuObjectScaleStepAt00658348;
                scaleY = scaleY + g_ReimuObjectScaleStepAt00658348;
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
                    rotationZ = 60.0f;
                }
                break;

            case 0x327:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (field07C == 6) {
                        field07C = 0;
                        field080 = 1;
                    }
                    if (animationStage == 0 && animationFrame == 0) {
                        field0D8 = 1;
                        field0DA = 0x5DC;
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            field0DC = 0;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                            field0DC = 0x2D;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00657480) {
                            field0DC = 0x5A;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                            field0DC = 0x87;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker4At00657D14) {
                            field0DC = 0xB4;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker5At00657874) {
                            field0DC = 0xE1;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00658290) {
                            field0DC = 0x10E;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker7At00659254) {
                            field0DC = 0x13B;
                        }
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.1f;
                        scaleY = 0.1f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = 0.0f;
                    }
                    if (animationStage == 1 && animationFrame == 0) {
                        field080 = 1;
                        field07C = 0;
                        // Target x87 sequence divides by the angle unit before
                        // the float-to-short conversion (the decompiler omits it).
                        field0DC = static_cast<short>(AngleAt00483300(
                            (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) - y,
                            (owner->opponent->x - x) * facing) /
                            g_ReimuObjectAngleUnitAt00657828);
                    }
                    if (animationStage == 1) {
                        float effectY = y + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectY = effectY - static_cast<float>(RecordedRange(0, 0x1E));
                        float effectX = x + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectX = effectX - static_cast<float>(RecordedRange(0, 0x1E));
                        owner->SpawnBattleEffect(0x335, effectX, effectY, facing, 1);
                    }
                    if (field07C == 0 || animationStage != 1) {
                        if (animationStage == 0) {
                            field0DA = field0DA - 0x3C;
                            if (field0DA < 0) {
                                field0DA = 0;
                            }
                            scaleX = scaleX + g_ReimuObjectScalarAt006590B4;
                            scaleY = scaleY + g_ReimuObjectScalarAt006590B4;
                            if (g_ReimuObjectDirectionMarker1At0065747C < scaleX) {
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
                            scaleX = scaleX - g_ReimuObjectScaleStepAt00658348;
                            scaleY = scaleY - g_ReimuObjectScaleStepAt00658348;
                            color[0] = color[0] - 10;
                            if (scaleX < g_ReimuObjectDirectionMarker0At0065782C) {
                                scaleX = 0.0f;
                                scaleY = 0.0f;
                            }
                        }
                        SetPolarVelocity(static_cast<float>(field0DC),
                            static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044);
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectRightBoundAt00659250 < x ||
                            x < g_ReimuObjectLeftBoundAt00658344 ||
                            g_ReimuObjectUpperBoundAt00658E80 < y ||
                            y < g_ReimuObjectLowerBoundAt00657880) {
                            ClearFrameInfo();
                        }
                        else if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                    }
                    else {
                        owner->SetCameraShake(2.0f);
                        ResetSecondaryCounter(2);
                        rotationX = 0.0f;
                        rotationY = 0.0f;
                        rotationZ = 0.0f;
                        scaleX = 4.0f;
                        scaleY = 4.0f;
                    }
                }
                break;
            case 0x328:
                facing = owner->facing;
                if (owner->action == 0x131 && owner->animationStage < 4 &&
                    animationStage == 0) {
                    x = facing * 0x91 + owner->x;
                    y = owner->y + g_ReimuObjectOwnerOffsetAt006590A4;
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
                    rotationZ = facing * 0x46;
                    field0D8 = 1;
                }
                rotationZ = rotationZ + g_ReimuObjectDirectionMarker5At00657874;
                if (animationStage > 0) {
                    if (color[0] < 0x1F) {
                        color[0] = 0;
                    }
                    else {
                        color[0] = color[0] - 0x1E;
                    }
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                if (animationStage == 1 && animationFrame == 0) {
                    ResetSecondaryCounter(0);
                }
                break;

            case 0x329:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (field07C == 6) {
                        field07C = 0;
                        field080 = 1;
                    }
                    if (animationStage == 0 && animationFrame == 0) {
                        field0D8 = 1;
                        field0DA = 0x5DC;
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            field0DC = 0;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                            field0DC = 0x2D;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00657480) {
                            field0DC = 0x5A;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                            field0DC = 0x87;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker4At00657D14) {
                            field0DC = 0xB4;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker5At00657874) {
                            field0DC = 0xE1;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00658290) {
                            field0DC = 0x10E;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker7At00659254) {
                            field0DC = 0x13B;
                        }
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.1f;
                        scaleY = 0.1f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = 0.0f;
                    }
                    if (animationStage == 1 && animationFrame == 0) {
                        field080 = 1;
                        field07C = 0;
                        // Target x87 sequence divides by the angle unit before
                        // the float-to-short conversion (the decompiler omits it).
                        field0DC = static_cast<short>(AngleAt00483300(
                            (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) - y,
                            (owner->opponent->x - x) * facing) /
                            g_ReimuObjectAngleUnitAt00657828);
                    }
                    if (animationStage == 1) {
                        float effectY = y + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectY = effectY - static_cast<float>(RecordedRange(0, 0x1E));
                        float effectX = x + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectX = effectX - static_cast<float>(RecordedRange(0, 0x1E));
                        owner->SpawnBattleEffect(0x336, effectX, effectY, facing, 1);
                    }
                    if (field07C == 0 || animationStage != 1) {
                        if (animationStage == 0) {
                            field0DA = field0DA - 0x3C;
                            if (field0DA < 0) {
                                field0DA = 0;
                            }
                            scaleX = scaleX + g_ReimuObjectScalarAt006590B4;
                            scaleY = scaleY + g_ReimuObjectScalarAt006590B4;
                            if (g_ReimuObjectDirectionMarker1At0065747C < scaleX) {
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
                            scaleX = scaleX - g_ReimuObjectScaleStepAt00658348;
                            scaleY = scaleY - g_ReimuObjectScaleStepAt00658348;
                            color[0] = color[0] - 10;
                            if (scaleX < g_ReimuObjectDirectionMarker0At0065782C) {
                                scaleX = 0.0f;
                                scaleY = 0.0f;
                            }
                        }
                        SetPolarVelocity(static_cast<float>(field0DC),
                            static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044);
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectRightBoundAt00659250 < x ||
                            x < g_ReimuObjectLeftBoundAt00658344 ||
                            g_ReimuObjectUpperBoundAt00658E80 < y ||
                            y < g_ReimuObjectLowerBoundAt00657880) {
                            ClearFrameInfo();
                        }
                        else if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                    }
                    else {
                        owner->SetCameraShake(2.0f);
                        ResetSecondaryCounter(2);
                        rotationX = 0.0f;
                        rotationY = 0.0f;
                        rotationZ = 0.0f;
                        scaleX = 4.0f;
                        scaleY = 4.0f;
                    }
                }
                break;

            case 0x32A:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (field07C == 6) {
                        field07C = 0;
                        field080 = 1;
                    }
                    if (animationStage == 0 && animationFrame == 0) {
                        field0D8 = 1;
                        field0DA = 0x5DC;
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            field0DC = 0;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                            field0DC = 0x2D;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00657480) {
                            field0DC = 0x5A;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                            field0DC = 0x87;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker4At00657D14) {
                            field0DC = 0xB4;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker5At00657874) {
                            field0DC = 0xE1;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00658290) {
                            field0DC = 0x10E;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker7At00659254) {
                            field0DC = 0x13B;
                        }
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.1f;
                        scaleY = 0.1f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = 0.0f;
                    }
                    if (animationStage == 1 && animationFrame == 0) {
                        field080 = 1;
                        field07C = 0;
                        // Target x87 sequence divides by the angle unit before
                        // the float-to-short conversion (the decompiler omits it).
                        field0DC = static_cast<short>(AngleAt00483300(
                            (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) - y,
                            (owner->opponent->x - x) * facing) /
                            g_ReimuObjectAngleUnitAt00657828);
                    }
                    if (animationStage == 1) {
                        float effectY = y + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectY = effectY - static_cast<float>(RecordedRange(0, 0x1E));
                        float effectX = x + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectX = effectX - static_cast<float>(RecordedRange(0, 0x1E));
                        owner->SpawnBattleEffect(0x337, effectX, effectY, facing, 1);
                    }
                    if (field07C == 0 || animationStage != 1) {
                        if (animationStage == 0) {
                            field0DA = field0DA - 0x3C;
                            if (field0DA < 0) {
                                field0DA = 0;
                            }
                            scaleX = scaleX + g_ReimuObjectScalarAt006590B4;
                            scaleY = scaleY + g_ReimuObjectScalarAt006590B4;
                            if (g_ReimuObjectDirectionMarker1At0065747C < scaleX) {
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
                            scaleX = scaleX - g_ReimuObjectScaleStepAt00658348;
                            scaleY = scaleY - g_ReimuObjectScaleStepAt00658348;
                            color[0] = color[0] - 10;
                            if (scaleX < g_ReimuObjectDirectionMarker0At0065782C) {
                                scaleX = 0.0f;
                                scaleY = 0.0f;
                            }
                        }
                        SetPolarVelocity(static_cast<float>(field0DC),
                            static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044);
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectRightBoundAt00659250 < x ||
                            x < g_ReimuObjectLeftBoundAt00658344 ||
                            g_ReimuObjectUpperBoundAt00658E80 < y ||
                            y < g_ReimuObjectLowerBoundAt00657880) {
                            ClearFrameInfo();
                        }
                        else if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                    }
                    else {
                        owner->SetCameraShake(2.0f);
                        ResetSecondaryCounter(2);
                        rotationX = 0.0f;
                        rotationY = 0.0f;
                        rotationZ = 0.0f;
                        scaleX = 4.0f;
                        scaleY = 4.0f;
                    }
                }
                break;


            case 0x32B:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        SetPolarVelocity(field0C8, field0CC);
                        field0D8 = 0;
                        scaleX = 1.0f;
                        scaleY = 1.0f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = AngleAt00483300(velocityY, velocityX) /
                            g_ReimuObjectAngleUnitAt00657828;
                    }
                    field0D8 = field0D8 + 1;
                    SetPolarVelocity(field0C8,
                        static_cast<float>(field0D8) * g_ReimuObjectScalarAt006590B4 + field0CC);
                    if (field07C == 0 || animationStage != 1) {
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        if (g_ReimuObjectRightBoundAt0065925C < x ||
                            x < g_ReimuObjectLeftBoundAt00659258 ||
                            g_ReimuObjectUpperBoundAt00657884 < y ||
                            y < g_ReimuObjectLowerBoundAt0065924C) {
                            ClearFrameInfo();
                        }
                        else {
                            if (animationStage > 1) {
                                if (color[0] < 0x19) {
                                    color[0] = 0;
                                }
                                else {
                                    color[0] = color[0] - 0x19;
                                }
                            }
                            if (AdvanceNestedFrame() == animationStageCount) {
                                ClearFrameInfo();
                            }
                        }
                    }
                    else {
                        ResetSecondaryCounter(2);
                    }
                }
                else {
                    ClearFrameInfo();
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    if (owner->fieldEFA > 0x19) {
                        owner->fieldEFA = 0;
                        owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
                    }
                }
                break;

            case 0x32C:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (g_ReimuObjectRightBoundAt0065925C < x ||
                        x < g_ReimuObjectLeftBoundAt00659258 ||
                        g_ReimuObjectUpperBoundAt006583B4 < y ||
                        y < g_ReimuObjectLowerBoundAt00658374) {
                        ClearFrameInfo();
                    }
                    else {
                        if (animationStage == 0 && animationFrame == 0) {
                            ResetTransform(0.0f, 0.0f, 0.0f);
                            field080 = 4;
                            field07C = 0;
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
                            static_cast<float>(field0DA) * g_ReimuObjectScalarAt006590B4 +
                            g_ReimuObjectScalarAt00657850);
                        field0DE = field0DE + 0x1E;
                        field0DA = field0DA + 1;
                        if (animationStage > 0 && field0DC < 0x5A) {
                            if (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888 < y) {
                                field0C8 = field0C8 + g_ReimuObjectDirectionMarker1At0065747C;
                            }
                            if (y < owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) {
                                field0C8 = field0C8 - g_ReimuObjectDirectionMarker1At0065747C;
                            }
                            field0DC = field0DC + 1;
                        }
                        x = facing * velocityX + x;
                        y = y + velocityY;
                        rotationZ = rotationZ + g_ReimuObjectRotationStepAt006590C4;
                        if ((field07C == 1 || field07C == 2 || field07C == 4) && field080 == 0) {
                            ResetSecondaryCounter(3);
                        }
                        if (animationStage > 2) {
                            if (color[0] < 0x19) {
                                color[0] = 0;
                            }
                            else {
                                color[0] = color[0] - 0x19;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                        if (animationStage == 3 && animationFrame == 0 &&
                            field0D8 < 0xC && field080 > 0) {
                            ResetSecondaryCounter(2);
                            field0D8 = field0D8 + 1;
                            field07C = 0;
                        }
                    }
                }
                else {
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
                }
                break;
            case 0x32D:
                if (owner->action == 0x1FA || owner->action == 0x1FB) {
                    x = owner->x;
                    y = owner->y;
                }
                if ((owner->action != 0x1FA || owner->field082 < 1) &&
                    AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                break;

            case 0x32E:
                if (owner->action == 0x2C0) {
                    x = facing * 0xE4 + owner->x;
                    y = owner->y + g_ReimuObjectOwnerYOffsetAt00659080;
                }
                if (animationStage < 0x39 &&
                    ((owner->action == 0x2C0 && owner->animationStage > 0x0C) ||
                     owner->action != 0x2C0)) {
                    scaleX = 3.0f;
                    scaleY = 3.0f;
                    owner->SpawnBattleEffect(0x32F, x, y, facing, 1);
                    ResetSecondaryCounter(0x39);
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 99;
                        field07C = 0;
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
                    rotationZ = rotationZ - g_ReimuObjectScalarAt00657480;
                    if (field07C != 0) {
                        field0D8 = field0D8 + 1;
                        if (field0D8 > 5) {
                            field0D8 = 0;
                            field07C = 0;
                        }
                    }
                    if (animationStage > 0x38) {
                        scaleX = scaleX * g_ReimuObjectScaleMultiplierAt00659090;
                        scaleY = scaleY * g_ReimuObjectScaleMultiplierAt00659090;
                    }
                    if (animationStage == 0x3A) {
                        if (color[0] < 0x0F) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 0x0F;
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
            case 0x32F:
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field07C = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 0xFF;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                    color[3] = 0xFF;
                }
                scaleX = scaleX + g_ReimuObjectScaleIncrementAt006583FC;
                scaleY = scaleY + g_ReimuObjectScaleIncrementAt006583FC;
                if (animationStage > 0) {
                    if (color[0] < 0x0F) {
                        color[0] = 0;
                    }
                    else {
                        color[0] = color[0] - 0x0F;
                    }
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                break;

            case 0x330:
                if (owner->action == 0x2BE) {
                    x = owner->x;
                    y = owner->y;
                }
                if (animationStage < 6 && owner->action != 0x2BE) {
                    ClearFrameInfo();
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
                        if (color[0] < 7) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 7;
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
            case 0x331:
                if (animationStage == 0 && animationFrame == 0 && field0DC == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field080 = 99;
                    field07C = 0;
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
                if ((owner->action == 0x2BE && owner->animationStage < 0x0C) ||
                    animationStage > 9) {
                    if (field07C != 0) {
                        field0D8 = field0D8 + 1;
                        if (field0D8 > 2) {
                            field0D8 = 0;
                            field07C = 0;
                        }
                    }
                    if (animationStage > 9) {
                        if (color[0] < 5) {
                            color[0] = 0;
                            ClearFrameInfo();
                            return;
                        }
                        color[0] = color[0] - 5;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ResetSecondaryCounter(10);
                    }
                    else if (animationStage == 10 && animationFrame == 0) {
                        ResetSecondaryCounter(0);
                    }
                }
                else {
                    ResetSecondaryCounter(animationStage + 10);
                }
                break;
            case 0x332:
                static_cast<ReimuFighter*>(owner)->fieldF22 = 1;
                if (owner->action == 0x2C1 && animationStage < 0x13) {
                    x = facing * 0xE4 + owner->x;
                    y = owner->y + g_ReimuObjectOwnerYOffsetAt00659080;
                }
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field080 = 999;
                    field07C = 0;
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
                    rotationZ = rotationZ - g_ReimuObjectDirectionMarker4At00657D14;
                    velocityX = velocityX + g_ReimuObjectScaleStepAt00658348;
                    if (owner->spirit < 6) {
                        field0E0 = 1;
                        owner->UpdateGaugeTimer(owner->spirit - 1);
                    }
                    else {
                        owner->UpdateGaugeTimer(4);
                    }
                    if (field0E0 == 1) {
                        field080 = 0;
                        if (color[0] < 0x0B) {
                            ClearFrameInfo();
                            static_cast<ReimuFighter*>(owner)->fieldF22 = 0;
                            return;
                        }
                        color[0] = color[0] - 10;
                    }
                }
                if (field07C != 0) {
                    field0DA = 10;
                    field0D8 = field0D8 + 1;
                    if ((field07C == 6 || field07C == 4) && field0D8 < 2) {
                        field0D8 = 2;
                    }
                    if (field0D8 > 2) {
                        field0D8 = 0;
                        field07C = 0;
                    }
                }
                if (field0DA > 0) {
                    field0DA = field0DA - 1;
                    velocityX = 2.0f;
                    if (field0DA == 0) {
                        velocityX = 2.0f;
                    }
                }
                x = facing * velocityX + x;
                y = y + velocityY;
                if (x < g_ReimuObjectLowerBoundAt00657880 ||
                    g_ReimuObjectRightBoundAt00659248 < x) {
                    ClearFrameInfo();
                    static_cast<ReimuFighter*>(owner)->fieldF22 = 0;
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
            case 0x333:
                if (owner->action == 0x2BF) {
                    x = owner->x;
                    y = owner->y;
                }
                if (animationStage < 6 && owner->action != 0x2BF) {
                    ClearFrameInfo();
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
                        if (color[0] < 7) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 7;
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

            case 0x334:
                if (animationStage == 0 && animationFrame == 0 && field0DC == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field080 = 99;
                    field07C = 0;
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
                if ((owner->action == 0x2BF && owner->animationStage < 0x0C) ||
                    animationStage > 0x15) {
                    if (field07C != 0) {
                        field0D8 = field0D8 + 1;
                        if (field0D8 > 2) {
                            field0D8 = 0;
                            field07C = 0;
                        }
                    }
                    if (animationStage > 0x15) {
                        if (color[0] < 5) {
                            color[0] = 0;
                            ClearFrameInfo();
                            return;
                        }
                        color[0] = color[0] - 5;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ResetSecondaryCounter(0x16);
                    }
                    else if (animationStage == 0x16 && animationFrame == 0) {
                        ResetSecondaryCounter(0);
                    }
                }
                else {
                    ResetSecondaryCounter(animationStage + 0x16);
                }
                break;

            case 0x335:
            case 0x336:
            case 0x337:
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field080 = 1;
                    field07C = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 0xFF;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                    color[3] = 0xFF;
                }
                if (animationStage == 0) {
                    scaleX = scaleX - g_ReimuObjectScalarAt006590B4;
                    scaleY = scaleY - g_ReimuObjectScalarAt006590B4;
                }
                if (animationStage == 1) {
                    scaleX = scaleX - g_ReimuObjectScalarAt006590B4;
                    scaleY = scaleY - g_ReimuObjectScalarAt006590B4;
                    color[0] = color[0] - 0x32;
                }
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                break;
            case 0x338:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 2.0f;
                        scaleY = 2.0f;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationX = 75.0f;
                        velocityX = 20.0f;
                        field080 = 3;
                        field0D8 = 0;
                    }
                    if (field07C == 4) {
                        field07C = 0;
                    }
                    if (field080 == 0 && animationStage == 2) {
                        ResetSecondaryCounter(3);
                    }
                    else {
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectFullRotationAt00657864 < rotationZ) {
                            rotationX = rotationX - g_ReimuObjectFullRotationAt00657864;
                        }
                        if (animationStage < 3) {
                            velocityX = velocityX - g_ReimuObjectDirectionMarker1At0065747C;
                            if (velocityX < g_ReimuObjectHalfAt00657478) {
                                velocityX = g_ReimuObjectHalfAt00657478;
                            }
                        }
                        if (animationStage == 3) {
                            color[0] = color[0] - 10;
                            if (color[0] == 0) {
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
                            field0D8 = field0D8 + 1;
                            ResetSecondaryCounter(2);
                            field07C = 0;
                        }
                    }
                }
                else {
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
                }
                break;
            case 0x339:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 2.0f;
                        scaleY = 2.0f;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationX = 75.0f;
                        velocityX = 40.0f;
                        field080 = 3;
                        field0D8 = 0;
                    }
                    if (field07C == 4) {
                        field07C = 0;
                    }
                    if (field080 == 0 && animationStage == 2) {
                        ResetSecondaryCounter(3);
                    }
                    else {
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectFullRotationAt00657864 < rotationZ) {
                            rotationX = rotationX - g_ReimuObjectFullRotationAt00657864;
                        }
                        if (animationStage < 3) {
                            velocityX = velocityX - g_ReimuObjectScalarAt00657480;
                            if (velocityX < g_ReimuObjectHalfAt00657478) {
                                velocityX = g_ReimuObjectHalfAt00657478;
                            }
                        }
                        if (animationStage == 3) {
                            color[0] = color[0] - 10;
                            if (color[0] == 0) {
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
                            field0D8 = field0D8 + 1;
                            ResetSecondaryCounter(2);
                            field07C = 0;
                        }
                    }
                }
                else {
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
                }
                break;
            case 0x33A:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 2.0f;
                        scaleY = 2.0f;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationX = 75.0f;
                        velocityX = 60.0f;
                        field080 = 3;
                        field0D8 = 0;
                    }
                    if (field07C == 4) {
                        field07C = 0;
                    }
                    if (field080 == 0 && animationStage == 2) {
                        ResetSecondaryCounter(3);
                    }
                    else {
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectFullRotationAt00657864 < rotationZ) {
                            rotationX = rotationX - g_ReimuObjectFullRotationAt00657864;
                        }
                        if (animationStage < 3) {
                            velocityX = velocityX - g_ReimuObjectDirectionMarker3At00657CF8;
                            if (velocityX < g_ReimuObjectHalfAt00657478) {
                                velocityX = g_ReimuObjectHalfAt00657478;
                            }
                        }
                        if (animationStage == 3) {
                            color[0] = color[0] - 10;
                            if (color[0] == 0) {
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
                            field0D8 = field0D8 + 1;
                            ResetSecondaryCounter(2);
                            field07C = 0;
                        }
                    }
                }
                else {
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
                }
                break;
            case 0x33B:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        SetPolarVelocity(field0C8, field0CC);
                        field0D8 = 0;
                        scaleX = 1.0f;
                        scaleY = 1.0f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = AngleAt00483300(velocityY, velocityX) /
                            g_ReimuObjectAngleUnitAt00657828;
                    }
                    field0D8 = field0D8 + 1;
                    if (animationStage < 3) {
                        SetPolarVelocity(field0C8, field0CC);
                    }
                    if (field07C == 1 || field07C == 2 || field07C == 4) {
                        if (animationStage == 1 && field07C == 1) {
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
                    if (g_ReimuObjectRightBoundAt0065925C < x ||
                        x < g_ReimuObjectLeftBoundAt00659258 ||
                        g_ReimuObjectUpperBoundAt00657884 < y ||
                        y < g_ReimuObjectLowerBoundAt0065924C) {
                        ClearFrameInfo();
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] < 0x19) {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                            color[0] = color[0] - 0x19;
                        }
                        if (animationStage == 3) {
                            rotationZ = rotationZ + g_AngleShiftAt00657878;
                            velocityY = velocityY + static_cast<float>(g_RiseAt00658050);
                        }
                        if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                    }
                }
                else {
                    ClearFrameInfo();
                    if (owner->fieldEFA > 0x19) {
                        owner->fieldEFA = 0;
                        owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
                    }
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                }
                break;
            case 0x33C:
            case 0x33D:
            case 0x33E:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else {
                    if (field07C == 6) {
                        field07C = 0;
                        field080 = 1;
                    }
                    if (animationStage == 0 && animationFrame == 0) {
                        field0D8 = 1;
                        field0DA = 2000;
                        if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                            field0DC = 0;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                            field0DC = 0x2D;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00657480) {
                            field0DC = 0x5A;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                            field0DC = 0x87;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker4At00657D14) {
                            field0DC = 0xB4;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker5At00657874) {
                            field0DC = 0xE1;
                        }
                        if (field0C8 == g_ReimuObjectScalarAt00658290) {
                            field0DC = 0x10E;
                        }
                        if (field0C8 == g_ReimuObjectDirectionMarker7At00659254) {
                            field0DC = 0x13B;
                        }
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.1f;
                        scaleY = 0.1f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = 0.0f;
                    }
                    if (animationStage == 1) {
                        float effectY = y + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectY = effectY - static_cast<float>(RecordedRange(0, 0x1E));
                        float effectX = x + g_ReimuObjectEffectSpreadAt00657CBC;
                        effectX = effectX - static_cast<float>(RecordedRange(0, 0x1E));
                        owner->SpawnBattleEffect(static_cast<short>(action - 7), effectX, effectY, facing, 1);
                    }
                    if (field07C == 0 || animationStage != 1 || field080 != 0) {
                        if (animationStage == 0) {
                            field0DA = field0DA - 0x50;
                            if (field0DA < 0) {
                                field0DA = 0;
                            }
                            scaleX = scaleX + g_ReimuObjectScaleStepAt00658348;
                            scaleY = scaleY + g_ReimuObjectScaleStepAt00658348;
                            if (g_ReimuObjectScaleCeilingAt006581E0 < scaleX) {
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
                            scaleX = scaleX - g_ReimuObjectScaleIncrementAt006583FC;
                            scaleY = scaleY - g_ReimuObjectScaleIncrementAt006583FC;
                            color[0] = color[0] - 10;
                            if (scaleX < g_ReimuObjectDirectionMarker0At0065782C) {
                                scaleX = 0.0f;
                                scaleY = 0.0f;
                            }
                        }
                        if (animationStage < 2) {
                            SetPolarVelocity(static_cast<float>(field0DC),
                                static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044);
                        }
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectRightBoundAt00659250 < x ||
                            x < g_ReimuObjectLeftBoundAt00658344 ||
                            g_ReimuObjectUpperBoundAt00658E80 < y ||
                            y < g_ReimuObjectLowerBoundAt00657880) {
                            ClearFrameInfo();
                        }
                        else {
                            if (AdvanceNestedFrame() == animationStageCount) {
                                ClearFrameInfo();
                            }
                            if (animationStage == 1 && animationFrame == 0) {
                                field080 = 3;
                                field07C = 0;
                                field0DC = static_cast<short>(AngleAt00483300(
                                    (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) - y,
                                    (owner->opponent->x - x) * facing) /
                                    g_ReimuObjectAngleUnitAt00657828);
                            }
                            if (animationStage == 2 && animationFrame == 0) {
                                ResetSecondaryCounter(1);
                                field07C = 0;
                            }
                        }
                    }
                    else {
                        owner->SetCameraShake(5.0f);
                        ResetSecondaryCounter(2);
                        rotationX = 0.0f;
                        rotationY = 0.0f;
                        rotationZ = 0.0f;
                        scaleX = 3.5f;
                        scaleY = 3.5f;
                        velocityX = 0.0f;
                        velocityY = 0.0f;
                    }
                }
                break;
            case 0x33F:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
                    if (g_ReimuObjectRightBoundAt0065925C < x ||
                        x < g_ReimuObjectLeftBoundAt00659258) {
                        ClearFrameInfo();
                    }
                    else {
                        if (animationStage == 0 && animationFrame == 0) {
                            if (field0C8 == g_ReimuObjectDirectionMarker0At0065782C) {
                                ResetTransform(0.0f, 0.0f, 0.0f);
                                velocityY = 3.0f;
                                velocityX = 11.0f;
                                rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                    g_ReimuObjectAngleUnitAt00657828;
                            }
                            if (field0C8 == g_ReimuObjectDirectionMarker1At0065747C) {
                                ResetTransform(0.0f, 0.0f, 0.0f);
                                velocityY = 6.0f;
                                velocityX = 8.0f;
                                rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                    g_ReimuObjectAngleUnitAt00657828;
                            }
                            if (field0C8 == g_ReimuObjectScalarAt00657480) {
                                ResetTransform(0.0f, 0.0f, 0.0f);
                                velocityY = -3.0f;
                                velocityX = 11.0f;
                                rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                    g_ReimuObjectAngleUnitAt00657828;
                            }
                            if (field0C8 == g_ReimuObjectDirectionMarker3At00657CF8) {
                                ResetTransform(0.0f, 0.0f, 0.0f);
                                velocityY = -6.0f;
                                velocityX = 8.0f;
                                rotationZ = -AngleAt00483300(velocityY, velocityX) /
                                    g_ReimuObjectAngleUnitAt00657828;
                            }
                        }
                        x = facing * velocityX + x;
                        y = y + velocityY;
                        if (AdvanceNestedFrame() == animationStageCount) {
                            owner->SpawnBattleEffect(0x340, x, y, facing, 1);
                            ClearFrameInfo();
                        }
                    }
                }
                else {
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
                }
                break;
            case 0x340:
                if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 3) {
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
                        field080 = 2;
                        field07C = 0;
                    }
                    if (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888 < y) {
                        velocityY = velocityY - g_ReimuObjectVerticalSpringAt00658354;
                    }
                    if (y <= owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) {
                        velocityY = velocityY + g_ReimuObjectVerticalSpringAt00658354;
                    }
                    if (g_ReimuObjectScalarAt00657480 < velocityY) {
                        velocityY = 2.0f;
                    }
                    if (velocityY < g_ReimuObjectVerticalLowerLimitAt00659244) {
                        velocityY = -2.0f;
                    }
                    velocityX = velocityX + g_ReimuObjectHorizontalDriftAt006578C0;
                    if (field0D8 < 1) {
                        field07C = 0;
                        field0D8 = 10;
                    }
                    field0D8 = field0D8 - 1;
                    x = facing * velocityX + x;
                    y = y + velocityY;
                    if (animationFrame == 0) {
                        float effectY = y - g_ReimuObjectScalarAt00657850;
                        effectY = static_cast<float>(RecordedRange(0, 0x14)) + effectY;
                        float effectX = x - g_ReimuObjectScalarAt00657850;
                        effectX = static_cast<float>(RecordedRange(0, 0x14)) + effectX;
                        owner->SpawnBattleEffect(0x341, effectX, effectY, facing, 1);
                    }
                    if (animationFrame == 0) {
                        field0DA = static_cast<short>(RecordedRange(0, 0x14));
                        scaleX = static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044 +
                            g_ReimuObjectScaleBaseAt00659240;
                        scaleY = static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044 +
                            g_ReimuObjectScaleBaseAt00659240;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        if (field0DC < 0x3C && field080 > 0) {
                            ResetSecondaryCounter(1);
                            field0DC = field0DC + 1;
                        }
                        else {
                            ClearFrameInfo();
                        }
                    }
                }
                else {
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
                }
                break;

            case 0x341:
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
                velocityY = velocityY - g_ReimuObjectScalarAt006590B4;
                x = facing * velocityX + x;
                y = y + velocityY;
                if (color[0] < 0x0E) {
                    color[0] = 0;
                }
                else {
                    color[0] = color[0] - 0x0D;
                }
                scaleX = scaleX * g_ReimuObjectScaleFadeAt0065923C;
                scaleY = scaleY * g_ReimuObjectScaleFadeAt0065923C;
                if (AdvanceNestedFrame() == animationStageCount) {
                    ClearFrameInfo();
                }
                break;
            case 0x342:
                if (g_ReimuObjectRightBoundAt0065925C < x ||
                    x < g_ReimuObjectLeftBoundAt00659258 ||
                    g_ReimuObjectUpperBoundAt006583B4 < y ||
                    y < g_ReimuObjectLowerBoundAt00658374) {
                    ClearFrameInfo();
                }
                else if (field07C == 5) {
                    ClearFrameInfo();
                }
                else if (owner->action < 0x32 || owner->action > 0x95 ||
                    animationStage > 1) {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
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
                            static_cast<float>(field0D8) * g_ReimuObjectScalarAt006590B4 +
                            g_ReimuObjectScalarAt00657850);
                    }
                    if (animationStage > 0) {
                        field0DA = static_cast<short>(AngleAt00483300(
                            (owner->opponent->y - y) + g_ReimuObjectContactProjectionAt00657888,
                            (owner->opponent->x - x) * facing) /
                            g_ReimuObjectAngleUnitAt00657828);
                        if (field0DC + 10 < field0DA) {
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
                        static_cast<float>(field0D8) * g_ReimuObjectScalarAt006590B4 +
                        g_ReimuObjectScalarAt00657850);
                    rotationZ = AngleAt00483300(velocityY, velocityX) /
                        g_ReimuObjectAngleUnitAt00657828;
                    field0DE = field0DE + 0x1E;
                    field0D8 = field0D8 + 2;
                    x = facing * velocityX + x;
                    y = y - velocityY;
                    if (field07C != 0 && field07C != 6) {
                        ResetSecondaryCounter(2);
                    }
                    if (animationStage > 1) {
                        if (color[0] < 0x19) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 0x19;
                        }
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                    }
                }
                else {
                    ClearFrameInfo();
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    owner->SpawnBattleEffect(0x3E4, x, y, 1, 1);
                    if (owner->fieldEFA > 0x19) {
                        owner->fieldEFA = 0;
                        owner->SpawnBattleEffect(0x3E3, x, y, 1, 1);
                    }
                }
                break;
            case 900:
            case 0x385:
            case 0x386:
                if (field07C == 6) {
                    field07C = 0;
                    field080 = 1;
                }
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        field0D8 = 1;
                        field0DA = static_cast<short>(RecordedRange(0, 500) + 0x5DC);
                        field0DC = static_cast<short>(field0C8);
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.1f;
                        scaleY = 0.1f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = 0.0f;
                    }
                    if (animationStage == 1 && animationFrame == 0) {
                        field080 = 1;
                        field07C = 0;
                        field0DC = static_cast<short>(AngleAt00483300(
                            (owner->opponent->y + g_ReimuObjectContactProjectionAt00657888) - y,
                            (owner->opponent->x - x) * facing) /
                            g_ReimuObjectAngleUnitAt00657828);
                    }
                    if (field07C == 0 || animationStage != 1) {
                        if (animationStage == 0) {
                            field0DA = field0DA - 0x3C;
                            if (field0DA < 0) {
                                field0DA = 0;
                            }
                            scaleX = scaleX + g_ReimuObjectScalarAt006590B4;
                            scaleY = scaleY + g_ReimuObjectScalarAt006590B4;
                            if (g_ReimuObjectDirectionMarker1At0065747C < scaleX) {
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
                            scaleX = scaleX - g_ReimuObjectScaleStepAt00658348;
                            scaleY = scaleY - g_ReimuObjectScaleStepAt00658348;
                            color[0] = color[0] - 10;
                            if (scaleX < g_ReimuObjectDirectionMarker0At0065782C) {
                                scaleX = 0.0f;
                                scaleY = 0.0f;
                            }
                        }
                        SetPolarVelocity(static_cast<float>(field0DC),
                            static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044);
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectRightBoundAt00659250 < x ||
                            x < g_ReimuObjectLeftBoundAt00658344 ||
                            g_ReimuObjectUpperBoundAt00658E80 < y ||
                            y < g_ReimuObjectLowerBoundAt00657880 ||
                            owner->field3A0 == 0) {
                            ClearFrameInfo();
                        }
                        else if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                    }
                    else {
                        owner->SetCameraShake(2.0f);
                        ResetSecondaryCounter(2);
                        rotationX = 0.0f;
                        rotationY = 0.0f;
                        rotationZ = 0.0f;
                        scaleX = 4.0f;
                        scaleY = 4.0f;
                    }
                }
                break;
            case 0x387:
            case 0x388:
            case 0x389:
                if (field07C == 6) {
                    field07C = 0;
                    field080 = 1;
                }
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        field0D8 = 1;
                        field0DA = static_cast<short>(RecordedRange(0, 400) + 300);
                        field0DC = static_cast<short>(field0C8);
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.1f;
                        scaleY = 0.1f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        rotationZ = 0.0f;
                    }
                    if (animationStage == 1 && animationFrame == 0) {
                        field080 = 1;
                        field07C = 0;
                    }
                    if (field07C == 0 || animationStage != 1) {
                        if (animationStage < 2) {
                            if (animationStage == 0) {
                                field0DA = field0DA - 0x3C;
                                if (field0DA < 0) {
                                    field0DA = 0;
                                }
                            }
                            scaleX = scaleX + g_ReimuObjectScalarAt006590B4;
                            scaleY = scaleY + g_ReimuObjectScalarAt006590B4;
                            if (g_ReimuObjectDirectionMarker1At0065747C < scaleX) {
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
                            scaleX = scaleX - g_ReimuObjectScaleStepAt00658348;
                            scaleY = scaleY - g_ReimuObjectScaleStepAt00658348;
                            color[0] = color[0] - 10;
                            if (scaleX < g_ReimuObjectDirectionMarker0At0065782C) {
                                scaleX = 0.0f;
                                scaleY = 0.0f;
                            }
                        }
                        SetPolarVelocity(static_cast<float>(field0DC),
                            static_cast<float>(field0DA) * g_ReimuObjectSpeedScaleAt00658044);
                        x = facing * velocityX + x;
                        y = y - velocityY;
                        rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                        if (g_ReimuObjectRightBoundAt00659250 < x ||
                            x < g_ReimuObjectLeftBoundAt00658344 ||
                            g_ReimuObjectUpperBoundAt00658E80 < y ||
                            y < g_ReimuObjectLowerBoundAt00657880 ||
                            owner->field3A0 == 0) {
                            ClearFrameInfo();
                        }
                        else if (AdvanceNestedFrame() == animationStageCount) {
                            ClearFrameInfo();
                        }
                    }
                    else {
                        owner->SetCameraShake(2.0f);
                        ResetSecondaryCounter(2);
                        rotationX = 0.0f;
                        rotationY = 0.0f;
                        rotationZ = 0.0f;
                        scaleX = 4.0f;
                        scaleY = 4.0f;
                    }
                }
                break;
            case 0x38E:
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
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 6) {
                        if (color[0] < 7) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 7;
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

            case 0x38F:
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field080 = 0;
                    field07C = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 0xFF;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                    color[3] = 0xFF;
                    field0D8 = 0;
                    field0DA = 0;
                }
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else if (color[0] < 0x0F) {
                    ClearFrameInfo();
                }
                else {
                    color[0] = color[0] - 0x0F;
                    if (animationStage == 1 && animationFrame == 0) {
                        owner->SpawnBattleEffect(0x390, x, y, 1, 1);
                        owner->SpawnBattleEffect(0x390, x, y, -1, 1);
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                    }
                }
                break;

            case 0x390:
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    field080 = 99;
                    field07C = 0;
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
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    x = facing * velocityX + x;
                    if (g_ReimuObjectRightBoundAt00659250 < x ||
                        x < g_ReimuObjectLeftBoundAt00658344 ||
                        owner->field3A0 == 0) {
                        ClearFrameInfo();
                    }
                    else if (AdvanceNestedFrame() == animationStageCount) {
                        ResetSecondaryCounter(0);
                    }
                }
                break;

            case 0x391:
                if (g_ReimuObjectRightBoundAt0065925C < x ||
                    x < g_ReimuObjectLeftBoundAt00659258 ||
                    g_ReimuObjectUpperBoundAt006583B4 < y ||
                    y < g_ReimuObjectLowerBoundAt00658374 ||
                    owner->field3A0 == 0) {
                    ClearFrameInfo();
                }
                else if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
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
                            static_cast<float>(field0D8) * g_ReimuObjectScalarAt006590B4);
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
                    }
                    SetPolarVelocity(static_cast<float>(field0DC),
                        static_cast<float>(field0D8) * g_ReimuObjectScalarAt006590B4);
                    rotationZ = AngleAt00483300(velocityY, velocityX) /
                        g_ReimuObjectAngleUnitAt00657828;
                    x = facing * velocityX + x;
                    y = y - velocityY;
                    if (animationStage < 3 && field080 == 0) {
                        ResetSecondaryCounter(3);
                    }
                    if (animationStage > 2) {
                        if (color[0] < 0x19) {
                            color[0] = 0;
                        }
                        else {
                            color[0] = color[0] - 0x19;
                        }
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                    }
                }
                break;

            case 0x394:
                if (g_ReimuObjectRightBoundAt0065925C < x ||
                    x < g_ReimuObjectLeftBoundAt00659258 ||
                    g_ReimuObjectUpperBoundAt006583B4 < y ||
                    y < g_ReimuObjectLowerBoundAt00658374 ||
                    owner->field3A0 == 0) {
                    ClearFrameInfo();
                }
                else if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 1;
                        field07C = 0;
                        scaleX = 0.0f;
                        scaleY = 0.0f;
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        velocityX = field0C8 + g_ReimuObjectDirectionMarker0At0065782C;
                        velocityY = 3.0f;
                    }
                    if (animationStage == 1) {
                        scaleX = scaleX + g_ReimuObjectScalarAt006590B4;
                        if (g_ReimuObjectDirectionMarker1At0065747C < scaleX) {
                            scaleX = 1.0f;
                        }
                        scaleY = scaleX;
                    }
                    rotationZ = rotationZ + g_ReimuObjectScalarAt00657850;
                    x = facing * velocityX + x;
                    y = y + velocityY;
                    velocityY = velocityY - g_ReimuObjectHalfAt00657478;
                    if (y + velocityY < g_ReimuObjectDirectionMarker0At0065782C) {
                        y = 0.0f;
                        velocityY = -velocityY;
                        field07C = 0;
                        field080 = 1;
                    }
                    if (field07C == 6) {
                        field080 = 1;
                        field07C = 0;
                    }
                    if (AdvanceNestedFrame() == animationStageCount) {
                        ClearFrameInfo();
                    }
                }
                break;

            case 0x395:
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 99;
                        field07C = 0;
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
                        rotationZ = rotationZ - g_ReimuObjectDirectionMarker4At00657D14;
                        velocityX = velocityX + g_ReimuObjectHorizontalDriftAt006578C0;
                    }
                    x = facing * velocityX + x;
                    y = y + velocityY;
                    if (field07C != 0) {
                        field0D8 = field0D8 + 1;
                        if (field07C == 6 || field07C == 4) {
                            field0D8 = 6;
                        }
                        if (field0D8 > 5) {
                            field0D8 = 0;
                            field07C = 0;
                        }
                    }
                    if (x < g_ReimuObjectLowerBoundAt00657880 ||
                        g_ReimuObjectRightBoundAt00659248 < x) {
                        ClearFrameInfo();
                    }
                    else if (AdvanceNestedFrame() == animationStageCount) {
                        ResetSecondaryCounter(0x1B);
                    }
                }
                break;

            case 0x396:
                if (owner->field3A0 < 1) {
                    ClearFrameInfo();
                }
                else {
                    if (animationStage == 0 && animationFrame == 0) {
                        ResetTransform(0.0f, 0.0f, 0.0f);
                        field080 = 99;
                        field07C = 0;
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
                        rotationZ = rotationZ - g_ReimuObjectDirectionMarker4At00657D14;
                        velocityX = velocityX + g_ReimuObjectVerticalSpringAt00658354;
                    }
                    if (field07C != 0) {
                        field0D8 = field0D8 + 1;
                        if (field07C == 6 || field07C == 4) {
                            field0D8 = 3;
                        }
                        if (field0D8 > 2) {
                            field0D8 = 0;
                            field07C = 0;
                        }
                    }
                    x = facing * velocityX + x;
                    y = y + velocityY;
                    if (x < g_ReimuObjectLowerBoundAt00657880 ||
                        g_ReimuObjectRightBoundAt00659248 < x) {
                        ClearFrameInfo();
                    }
                    else if (AdvanceNestedFrame() == animationStageCount) {
                        ResetSecondaryCounter(0x28);
                    }
                }
                break;

            case 0x323:
            case 0x326:
            case 0x343:
            case 0x344:
            case 0x345:
            case 0x346:
            case 0x347:
            case 0x348:
            case 0x349:
            case 0x34A:
            case 0x34B:
            case 0x34C:
            case 0x34D:
            case 0x34E:
            case 0x34F:
            case 0x350:
            case 0x351:
            case 0x352:
            case 0x353:
            case 0x354:
            case 0x355:
            case 0x356:
            case 0x357:
            case 0x358:
            case 0x359:
            case 0x35A:
            case 0x35B:
            case 0x35C:
            case 0x35D:
            case 0x35E:
            case 0x35F:
            case 0x360:
            case 0x361:
            case 0x362:
            case 0x363:
            case 0x364:
            case 0x365:
            case 0x366:
            case 0x367:
            case 0x368:
            case 0x369:
            case 0x36A:
            case 0x36B:
            case 0x36C:
            case 0x36D:
            case 0x36E:
            case 0x36F:
            case 0x370:
            case 0x371:
            case 0x372:
            case 0x373:
            case 0x374:
            case 0x375:
            case 0x376:
            case 0x377:
            case 0x378:
            case 0x379:
            case 0x37A:
            case 0x37B:
            case 0x37C:
            case 0x37D:
            case 0x37E:
            case 0x37F:
            case 0x380:
            case 0x381:
            case 0x382:
            case 0x383:
            case 0x38A:
            case 0x38B:
            case 0x38C:
            case 0x38D:
            case 0x392:
            case 0x393:
            case 0x398:
            case 0x399:
            case 0x39A:
            case 0x39B:
            case 0x39C:
            case 0x39D:
            case 0x39E:
            case 0x3A7:
            case 0x3A8:
            case 0x3A9:
            case 0x3AA:
            case 0x3AB:
            case 0x3AD:
            case 0x3AE:
            case 0x3AF:
            case 0x3B0:
            case 0x3B1:
            case 0x3B2:
            case 0x3B3:
            case 0x3B4:
            case 0x3B5:
            case 0x3B8:
            case 0x3B9:
            case 0x3BA:
            case 0x3BB:
            case 0x3BC:
            case 0x3BD:
            case 0x3BE:
            case 0x3BF:
            case 0x3C0:
            case 0x3C1:
            case 0x3C2:
            case 0x3C3:
            case 0x3C4:
            case 0x3C5:
            case 0x3C6:
            case 0x3C7:
            case 0x3C8:
            case 0x3C9:
            case 0x3CA:
            case 0x3CB:
            case 0x3CC:
            case 0x3CD:
            case 0x3CE:
            case 0x3CF:
            case 0x3D0:
            case 0x3D1:
            case 0x3D2:
            case 0x3D3:
            case 0x3D4:
            case 0x3D5:
            case 0x3D6:
            case 0x3D7:
            case 0x3D8:
            case 0x3D9:
            case 0x3DA:
            case 0x3DB:
            case 0x3DC:
            case 0x3DD:
            case 0x3E0:
            case 0x3E1:
                AdvanceNestedFrame();
                break;
            }
        }
    }
}
