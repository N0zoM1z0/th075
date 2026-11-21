// Partial natural-C++ reconstruction of ReimuObject::Advance at 00476A40.
// The original parent is 50,915 bytes. This file currently models only the
// two fully transcribed directional-movement actions 0x321 and 0x322; other
// original actions are intentionally not represented and this is not a
// complete replacement or an exactness claim.
#include "CharacterObject.hpp"

extern float __cdecl AngleAt00483300(float y, float x);

// Address-anchored constants used by these two original movement handlers.
// Their values are read-only game data; names remain local to this partial
// reconstruction until their shared semantic identity is established.
extern const float g_ReimuObjectRightBoundAt0065925C;
extern const float g_ReimuObjectLeftBoundAt00659258;
extern const float g_ReimuObjectAngleUnitAt00657828;
extern const float g_ReimuObjectDirectionMarker0At0065782C;
extern const float g_ReimuObjectDirectionMarker1At0065747C;
extern const float g_ReimuObjectDirectionMarker2At00657480;
extern const float g_ReimuObjectDirectionMarker3At00657CF8;
extern const float g_ReimuObjectScaleStepAt00658348;

void ReimuObject::Advance()
{
    if (owner->opponent->field3BA == 0 &&
        (owner->field3BA == 0 || field08A != 0)) {
        if (field082 == 0) {
            switch (action) {
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
                        if (field0C8 == g_ReimuObjectDirectionMarker2At00657480) {
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
                        if (field0C8 == g_ReimuObjectDirectionMarker2At00657480) {
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
            }
        }
    }
}
