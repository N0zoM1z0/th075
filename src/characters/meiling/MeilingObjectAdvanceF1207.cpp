// Natural-C++ reconstruction of MeilingObject::Advance at 005EB520.
// Replays 34,434 code bytes plus 443 bytes of switch data with VC7.1 build 3077.
// Compiler profile and relocation bindings are in config/match-units.toml.
// Uses the shared CharacterObject/Fighter classes and their native helpers.
#include "characters/CharacterObject.hpp"
#include "characters/meiling/MeilingFighter.hpp"

float __cdecl AngleAt00483300(float, float);


// The state labels and names describe observed behavior, not original identity.
void MeilingObject::Advance() {
    if (owner->opponent->opponentFreezeSnapshot != 0) return;
    if (owner->opponentFreezeSnapshot != 0 && field08A == 0) return;
    if (hitstopFrames != 0) {
        --hitstopFrames;
        return;
    }
    switch (action) {
    case 800:
        if (owner->action > 49 && owner->action < 150 && animationStage < 8) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 1;
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                field0D8 = 10;
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 801:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 0.5f;
                scaleY = 0.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationY = facing * 60;
                rotationZ = field0C8;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 15;
                collisionResult = 0;
            }
            rotationZ += field0D8;
            field0D8 = field0D8 - 1;
            if (field0D8 < 1) field0D8 = 1;
            scaleX += 0.02f;
            scaleY += 0.02f;
            if (animationStage == 2) {
                if (color[0] > 5) {
                    color[0] -= 5;
                    color[1] -= 5;
                    color[2] -= 5;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 802:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 0.5f;
                scaleY = 0.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationY = facing * 70;
                rotationZ = RecordedRange(0, 359);
                velocityX = 0.0f;
                velocityY = 0.0f;
                collisionResult = 0;
            }
            scaleX += 0.03f;
            scaleY += 0.03f;
            if (animationStage == 1) {
                if (color[0] > 5) {
                    color[0] -= 5;
                    color[1] -= 5;
                    color[2] -= 5;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 803:
        if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
            ClearFrameInfo();
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            owner->SpawnBattleEffect(996, x, y, 1, 1);
            if (owner->fieldEFA > 25) {
                owner->fieldEFA = 0;
                owner->SpawnBattleEffect(995, x, y, 1, 1);
            }
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                remainingHits = 3;
                collisionResult = 0;
                scaleX = 0.1f;
                scaleY = 0.1f;
                color[0] = 255;
                color[1] = 0;
                color[2] = 0;
                color[3] = 255;
                field0D8 = 0;
                owner->field314 = 0.0f;
                owner->SpawnBattleEffect(801, x, y, facing, 1);
                owner->field314 = 180.0f;
                owner->SpawnBattleEffect(801, x, y, facing, 1);
                owner->SpawnBattleEffect(802, x, y, facing, 1);
            }
            if (animationStage == 1) {
                if (scaleX < 1.0f) {
                    scaleX += 0.1f;
                    scaleY += 0.1f;
                }
                if (color[2] < 230) {
                    color[2] += 25;
                    color[1] += 25;
                }
                else {
                    color[0] = 255;
                    color[2] = 255;
                    color[1] = 255;
                }
            }
            if (animationStage > 2) {
                scaleX += 0.3f;
                scaleY += 0.3f;
                if (color[0] >= 25) {
                    color[0] -= 25;
                    color[2] -= 25;
                    color[1] -= 25;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 3 && animationFrame == 0 && owner->action == 600 && owner->animationStage < 8) {
                ResetSecondaryCounter(2);
                ++field0D8;
                scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
                scaleY = scaleX;
                if (field0D8 > 4) {
                    field0D8 = 0;
                    collisionResult = 0;
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
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 10;
                    collisionResult = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    velocityX = 15.0f;
                    velocityY = 0.0f;
                    field0D8 = 0;
                    field0DA = 0;
                }
                if (collisionResult == 6) {
                    collisionResult = 0;
                    ++remainingHits;
                }
                if (collisionResult == 4) {
                    collisionResult = 0;
                }
                velocityX -= 0.4f;
                if (velocityX <= 2.0f) velocityX = 2.0f;
                if (animationStage > 1) {
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    scaleX += 0.3f;
                    scaleY += 0.3f;
                    if (color[0] >= 25) {
                        color[0] -= 25;
                        color[2] -= 25;
                        color[1] -= 25;
                    }
                    else {
                        ClearFrameInfo();
                        return;
                    }
                }
                x += facing * velocityX;
                y += velocityY;
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 2 && animationFrame == 0 && remainingHits > 0 && field0DA < 20) {
                    ResetSecondaryCounter(1);
                    ++field0D8;
                    ++field0DA;
                    if (field0D8 > 2) {
                        owner->SpawnBattleEffect(805, x, y, facing, 1);
                        field0D8 = 0;
                    }
                    scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
                    scaleY = scaleX;
                    if (collisionResult != 0) {
                        collisionResult = 0;
                        remainingHits -= 3;
                    }
                }
            }
        }
        break;
    case 805:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 0.5f;
                scaleY = 0.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationX = RecordedRange(0, 359);
                rotationY = RecordedRange(0, 359);
                rotationZ = RecordedRange(0, 359);
                velocityX = 0.0f;
                velocityY = 0.0f;
                collisionResult = 0;
            }
            scaleX += 0.085f;
            scaleY += 0.085f;
            if (animationStage == 1) {
                if (color[0] > 15) {
                    color[0] -= 15;
                    color[1] -= 15;
                    color[2] -= 15;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 806:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 2.5f;
            scaleY = 2.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->action == 700 && owner->animationStage < 11) {
            x = owner->x;
            y = owner->y + 100.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 807:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 255;
            rotationY = facing * 50;
            field0D8 = 1;
        }
        rotationZ += 1.0f;
        scaleX -= 0.01f;
        scaleY -= 0.01f;
        if (animationStage == 1) {
            if (color[0] < 248) {
                color[0] += 7;
                color[2] += 7;
                color[1] += 7;
            }
            else {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
        }
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                color[2] -= 10;
                color[1] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 808:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.2f;
            scaleY = 1.2f;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 255;
            rotationY = facing * 50;
            field0D8 = 1;
        }
        scaleX -= 0.018f;
        scaleY -= 0.018f;
        if (animationStage == 1) {
            if (color[0] < 248) {
                color[0] += 7;
                color[2] += 7;
                color[1] += 7;
            }
            else {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
        }
        if (animationStage > 1) {
            if (color[0] > 8) {
                color[0] -= 8;
                color[2] -= 8;
                color[1] -= 8;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 809:
        if (x > 1580.0f || x < -300.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action != 702 && animationStage < 2) {
                ClearFrameInfo();
                return;
            }
            else {
                if (field08A > 0 && owner->opponentFreezeTimer == 0) {
                    field08A = 0;
                }
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    scaleX = 0.1f;
                    scaleY = 0.1f;
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0;
                    color[3] = 255;
                    remainingHits = 20;
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    field0D8 = 0;
                }
                if (collisionResult == 6) {
                    collisionResult = 0;
                    ++remainingHits;
                }
                if (animationStage == 2 && animationFrame == 0) {
                    collisionResult = 0;
                    ++field0D8;
                    scaleX = 1.0f - RecordedRange(0, 20) * 0.01f;
                    scaleY = scaleX;
                    if (field0D8 > 1) {
                        owner->SpawnBattleEffect(810, x, y, facing, 1);
                        field0D8 = 0;
                    }
                }
                if (animationStage == 1) {
                    scaleX += 0.03f;
                    scaleY += 0.03f;
                    if (color[0] < 235) {
                        color[0] += 20;
                        color[2] += 20;
                        color[1] += 20;
                    }
                    else {
                        color[0] = 255;
                        color[1] = 255;
                        color[2] = 255;
                    }
                    if (owner->animationStage == 15) {
                        scaleX = 1.0f - RecordedRange(0, 20) * 0.01f;
                        scaleY = scaleX;
                        ResetSecondaryCounter(2);
                    }
                }
                if (animationStage == 2) {
                    velocityX -= 0.75f;
                    if (velocityX < 10.0f) velocityX = 10.0f;
                }
                if (animationStage > 2) {
                    if (color[0] > 10) {
                        scaleX *= 0.95f;
                        scaleY = scaleX;
                        color[0] -= 10;
                        color[2] -= 10;
                        color[1] -= 10;
                    }
                    else {
                        ClearFrameInfo();
                        return;
                    }
                }
                x += facing * velocityX;
                y += velocityY;
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 2 && animationFrame == 0) {
                    velocityX = 18.5f;
                    scaleX = 0.6f;
                    scaleY = 0.6f;
                }
                if (animationStage == 3 && animationFrame == 0) {
                    ResetSecondaryCounter(2);
                }
            }
        }
        break;
    case 810:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 0.5f;
                scaleY = 0.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationX = RecordedRange(0, 359);
                rotationY = RecordedRange(0, 359);
                rotationZ = RecordedRange(0, 359);
                velocityX = 0.0f;
                velocityY = 0.0f;
                collisionResult = 0;
            }
            scaleX += 0.065f;
            scaleY += 0.065f;
            if (animationStage == 1) {
                if (color[0] > 10) {
                    color[0] -= 10;
                    color[1] -= 10;
                    color[2] -= 10;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 811:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(818, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 812:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(819, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 813:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(820, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 814:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(821, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 815:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(822, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 816:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(823, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 817:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    SetPolarVelocity(field0C8, field0CC);
                    field0D8 = 0;
                    field0DC = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.017453288659453392f;
                }
                if (animationStage < 3 && RecordedRange(0, 100) < 40) {
                    owner->SpawnBattleEffect(824, x + 20.0f - RecordedRange(0, 40), y + 20.0f - RecordedRange(0, 40), facing, 1);
                }
                ++field0D8;
                if (animationStage < 2) {
                    SetPolarVelocity(field0C8, field0CC);
                }
                if ((collisionResult == 1 || collisionResult == 2 || collisionResult == 4 || collisionResult == 6) && animationStage == 1) {
                    ResetSecondaryCounter(2);
                    return;
                }
                else {
                    x += facing * velocityX;
                    y -= velocityY;
                    if (x > 1380.0f || x < -100.0f || y > 640.0f || y < -120.0f) {
                        ClearFrameInfo();
                        return;
                    }
                    else {
                        if (animationStage == 2) {
                            if (color[0] >= 60) {
                                color[0] -= 60;
                            }
                            else {
                                color[0] = 0;
                                ClearFrameInfo();
                                return;
                            }
                        }
                        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    }
                }
            }
        }
        break;
    case 818:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 819:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 820:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 821:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 822:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 823:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 824:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            remainingHits = 1;
            collisionResult = 0;
            scaleX = 1.1f - RecordedRange(0, 20) * 0.01f;
            scaleY = scaleX;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationZ = RecordedRange(0, 359);
            velocityX = 0.0f;
            velocityY = -2.0f;
        }
        y += velocityY;
        rotationZ += 2.0f;
        if (animationStage > 0) {
            if (scaleX > 0.05f) {
                scaleX -= 0.05f;
                scaleY -= 0.05f;
            }
            if (color[0] > 10) {
                color[0] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 825:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 26) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 10;
                    collisionResult = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    field0DA = 2000;
                    SetPolarVelocity(0.0f, field0DA * 0.01f);
                    remainingHits = 5;
                    field0D8 = 0;
                }
                if (collisionResult == 6) {
                    collisionResult = 0;
                    ++remainingHits;
                }
                if (collisionResult != 0) {
                    if (collisionResult == 4) {
                        collisionResult = 0;
                    }
                    else {
                        remainingHits = 0;
                    }
                }
                if (remainingHits == 0 && animationStage < 26) {
                    ResetSecondaryCounter(26);
                    return;
                }
                else {
                    field0DA -= 100;
                    if (field0DA < 300) field0DA = 300;
                    SetPolarVelocity(0.0f, field0DA * 0.01f);
                    x += facing * velocityX;
                    y += velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    if (animationStage == 26 && animationFrame == 0 && field0D8 < 2) {
                        ++field0D8;
                        ResetSecondaryCounter(13);
                    }
                }
            }
        }
        break;
    case 826:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 26) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    field0DA = 2000;
                    SetPolarVelocity(0.0f, field0DA * 0.01f);
                    remainingHits = 5;
                    field0D8 = 0;
                }
                if (collisionResult == 6) {
                    collisionResult = 0;
                    ++remainingHits;
                }
                if (collisionResult != 0) {
                    if (collisionResult == 4) {
                        collisionResult = 0;
                    }
                    else {
                        remainingHits = 0;
                    }
                }
                if (remainingHits == 0 && animationStage < 26) {
                    ResetSecondaryCounter(26);
                    return;
                }
                else {
                    field0DA -= 100;
                    if (field0DA < 300) field0DA = 300;
                    SetPolarVelocity(0.0f, field0DA * 0.01f);
                    x += facing * velocityX;
                    y += velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    if (animationStage == 26 && animationFrame == 0 && field0D8 < 3) {
                        ++field0D8;
                        ResetSecondaryCounter(13);
                    }
                }
            }
        }
        break;
    case 827:
        if (collisionResult == 5) {
            ClearFrameInfo();
            return;
        }
        else {
            if (owner->action > 49 && owner->action < 150 && animationStage < 26) {
                ClearFrameInfo();
                if (owner->fieldEFA > 25) {
                    owner->fieldEFA = 0;
                    owner->SpawnBattleEffect(995, x, y, 1, 1);
                }
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                owner->SpawnBattleEffect(996, x, y, 1, 1);
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    remainingHits = 1;
                    collisionResult = 0;
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                    color[1] = 255;
                    color[2] = 255;
                    color[3] = 255;
                    field0DA = 2000;
                    SetPolarVelocity(-30.0f, field0DA * 0.01f);
                    remainingHits = 5;
                    field0D8 = 0;
                }
                if (collisionResult == 6) {
                    collisionResult = 0;
                    ++remainingHits;
                }
                if (collisionResult != 0) {
                    if (collisionResult == 4) {
                        collisionResult = 0;
                    }
                    else {
                        remainingHits = 0;
                    }
                }
                if (remainingHits == 0 && animationStage < 26) {
                    ResetSecondaryCounter(26);
                    return;
                }
                else {
                    field0DA -= 100;
                    if (field0DA < 300) field0DA = 300;
                    SetPolarVelocity(-30.0f, field0DA * 0.01f);
                    x += facing * velocityX;
                    y += velocityY;
                    if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                    if (animationStage == 26 && animationFrame == 0 && field0D8 < 3) {
                        ++field0D8;
                        ResetSecondaryCounter(13);
                    }
                }
            }
        }
        break;
    case 828:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -35;
            rotationY = 40.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        scaleX += 0.065f;
        scaleY += 0.065f;
        if (animationStage == 2) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
                color[2] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 829:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -35;
            rotationY = 40.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        scaleX += 0.065f;
        scaleY += 0.065f;
        rotationZ += 2.0f;
        if (animationStage == 2) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
                color[2] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 830:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -35;
            rotationY = 40.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        scaleX += 0.2f;
        scaleY += 0.2f;
        if (animationStage == 2) {
            if (color[0] > 20) {
                color[0] -= 20;
                color[3] -= 20;
                color[2] -= 20;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 831:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                field0D8 = 10;
                collisionResult = 0;
            }
            scaleX += field0D8 * 0.01f + 0.01f;
            scaleY += field0D8 * 0.01f + 0.01f;
            if (field0D8 > 0) --field0D8;
            if (animationStage == 2) {
                if (color[0] > 5) {
                    color[0] -= 15;
                    color[1] -= 15;
                    color[3] -= 15;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            if (animationStage == 2 && animationFrame == 0) {
                owner->SpawnBattleEffect(832, x, y, facing, 1);
                owner->SpawnBattleEffect(833, x, y, facing, 1);
                owner->SpawnBattleEffect(834, x, y, facing, 1);
            }
        }
        break;
    case 832:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                remainingHits = 1;
                collisionResult = 0;
            }
            scaleX *= 0.9f;
            scaleY += 0.05f;
            if (collisionResult == 6) {
                ++remainingHits;
                collisionResult = 0;
            }
            if (animationStage == 2) {
                if (color[0] > 5) {
                    color[0] -= 15;
                    color[1] -= 15;
                    color[3] -= 15;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 833:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                remainingHits = 1;
                collisionResult = 0;
            }
            scaleY += 0.05f;
            if (collisionResult == 6) {
                ++remainingHits;
                collisionResult = 0;
            }
            if (animationStage == 2) {
                if (color[0] > 5) {
                    color[0] -= 15;
                    color[1] -= 15;
                    color[3] -= 15;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 834:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                velocityX = 0.0f;
                velocityY = 0.0f;
                remainingHits = 1;
                collisionResult = 0;
            }
            scaleX += 0.1f;
            scaleY += 0.1f;
            if (animationStage == 2) {
                if (color[0] > 5) {
                    color[0] -= 15;
                    color[1] -= 15;
                    color[3] -= 15;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 835:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -80;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
            remainingHits = 1;
        }
        scaleX += field0D8 * 0.03 + 0.02f;
        scaleY += field0D8 * 0.03 + 0.02f;
        if (field0D8 > 0) --field0D8;
        if (animationStage == 21) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 836:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.65f;
            scaleY = 0.65f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -80;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
            remainingHits = 1;
        }
        scaleX += field0D8 * 0.03 + 0.02f;
        scaleY += field0D8 * 0.03 + 0.02f;
        if (field0D8 > 0) --field0D8;
        if (animationStage == 21) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 837:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -60;
            rotationY = 35.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
        }
        scaleX += field0D8 * 0.05f + 0.05f;
        scaleY += field0D8 * 0.05f + 0.05f;
        if (field0D8 > 0) --field0D8;
        if (animationStage == 20) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
                color[2] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 838:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        scaleX += 0.02f;
        scaleY += 0.02f;
        if (animationStage == 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                color[3] -= 10;
                color[1] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 839:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            collisionResult = 0;
        }
        scaleX += 0.05f;
        scaleY += 0.05f;
        if (animationStage == 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                color[3] -= 10;
                color[1] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 840:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 2.5f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
        }
        if (owner->action == 701 && owner->animationStage < 11) {
            x = owner->x;
            y = owner->y + 100.0f;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 841:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 255;
            rotationY = facing * 50;
            field0D8 = 1;
        }
        rotationZ += 1.0f;
        scaleX -= 0.01f;
        scaleY -= 0.01f;
        if (animationStage == 1) {
            if (color[0] < 248) {
                color[0] += 7;
                color[2] += 7;
                color[1] += 7;
            }
            else {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
        }
        if (animationStage > 1) {
            if (color[0] > 10) {
                color[0] -= 10;
                color[2] -= 10;
                color[1] -= 10;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 842:
        if (animationStage == 0 && animationFrame == 0 && field0D8 == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.2f;
            scaleY = 1.2f;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 255;
            rotationY = facing * 50;
            field0D8 = 1;
        }
        scaleX -= 0.018f;
        scaleY -= 0.018f;
        if (animationStage == 1) {
            if (color[0] < 248) {
                color[0] += 7;
                color[2] += 7;
                color[1] += 7;
            }
            else {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
        }
        if (animationStage > 1) {
            if (color[0] > 8) {
                color[0] -= 8;
                color[2] -= 8;
                color[1] -= 8;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 843:
        if (x > 1580.0f || x < -300.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (field08A > 0 && owner->opponentFreezeTimer == 0) {
                field08A = 0;
            }
            if (animationStage < 3 && owner->action != 703) {
                ClearFrameInfo();
                return;
            }
            else {
                if (animationStage == 0 && animationFrame == 0) {
                    ResetTransform(0.0f, 0.0f, 0.0f);
                    scaleX = 0.1f;
                    scaleY = 0.1f;
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0;
                    color[3] = 255;
                    remainingHits = 20;
                    velocityX = 0.0f;
                    velocityY = 0.0f;
                    field0D8 = 0;
                }
                if (animationStage < 3) {
                    rotationZ = RecordedRange(0, 360);
                }
                if (collisionResult == 6) {
                    collisionResult = 0;
                    ++remainingHits;
                }
                if (animationStage == 2 && animationFrame == 0) {
                    collisionResult = 0;
                    scaleX = 1.0f - RecordedRange(0, 10) * 0.01f;
                    scaleY = scaleX;
                }
                if (animationStage == 3 && animationFrame == 0) {
                    collisionResult = 0;
                    scaleX = 1.0f - RecordedRange(0, 20) * 0.01f;
                    scaleY = scaleX;
                    ++field0D8;
                    if (field0D8 > 0) {
                        owner->SpawnBattleEffect(844, x, y, facing, 1);
                        field0D8 = 0;
                    }
                }
                if (animationStage == 1) {
                    scaleX += 0.03f;
                    scaleY += 0.03f;
                    if (color[0] < 235) {
                        color[0] += 20;
                        color[2] += 20;
                        color[1] += 20;
                    }
                    else {
                        color[0] = 255;
                        color[1] = 255;
                        color[2] = 255;
                    }
                }
                if (animationStage < 3 && owner->action == 703) {
                    x = owner->x + owner->facing * 100;
                    y = owner->y + 110.0f;
                }
                if (animationStage == 2 && owner->action == 703 && owner->animationStage > 28) {
                    ResetSecondaryCounter(3);
                    velocityX = 20.0f;
                    rotationZ = 0.0f;
                    remainingHits = 20;
                    collisionResult = 0;
                }
                if (animationStage == 3) {
                    owner->SpawnBattleEffect(RecordedRange(0, 7) + 818, x + 150.0f - RecordedRange(0, 300), y + 150.0f - RecordedRange(0, 300), facing, 1);
                }
                if (animationStage > 3) {
                    if (color[0] > 30) {
                        color[0] -= 30;
                        color[2] -= 30;
                        color[1] -= 30;
                    }
                    else {
                        ClearFrameInfo();
                        return;
                    }
                }
                x += facing * velocityX;
                y += velocityY;
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
                if (animationStage == 3 && animationFrame == 0) {
                    ResetSecondaryCounter(2);
                    collisionResult = 0;
                }
                if (animationStage == 4 && animationFrame == 0) {
                    ResetSecondaryCounter(3);
                    collisionResult = 0;
                }
            }
        }
        break;
    case 844:
        if (x > 1380.0f || x < -100.0f) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                collisionResult = 0;
                scaleX = 0.5f;
                scaleY = 0.5f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                rotationX = RecordedRange(0, 359);
                rotationY = RecordedRange(0, 359);
                rotationZ = RecordedRange(0, 359);
                velocityX = 0.0f;
                velocityY = 0.0f;
                collisionResult = 0;
            }
            scaleX += 0.085f;
            scaleY += 0.085f;
            if (animationStage == 1) {
                if (color[0] > 12) {
                    color[0] -= 12;
                }
                else {
                    ClearFrameInfo();
                    return;
                }
            }
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 845:
        if ((owner->action == 508 || owner->action == 509) && owner->y > 0.0f) {
            x = owner->x;
            y = owner->y;
        }
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            field0D8 = 1;
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 846:
        if (owner->action == 305) {
            x = owner->x;
            y = owner->y;
        }
        else {
            ClearFrameInfo();
            return;
        }
        if (owner->hitstopFrames == 0) {
            if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        }
        break;
    case 847:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 60.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
        }
        scaleX += field0D8 * 0.02f + 0.02f;
        scaleY += field0D8 * 0.02f + 0.02f;
        if (field0D8 > 0) --field0D8;
        if (animationStage == 4) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
                color[2] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 848:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 60.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
        }
        scaleX += field0D8 * 0.05f + 0.05f;
        scaleY += field0D8 * 0.05f + 0.05f;
        if (field0D8 > 0) --field0D8;
        if (animationStage == 20) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
                color[2] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 849:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 0.5f;
            scaleY = 0.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationX = facing * -30;
            rotationY = 60.0f;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
        }
        scaleX += field0D8 * 0.05f + 0.05f;
        scaleY += field0D8 * 0.05f + 0.05f;
        if (field0D8 > 0) --field0D8;
        if (animationStage == 20) {
            if (color[0] > 15) {
                color[0] -= 15;
                color[3] -= 15;
                color[2] -= 15;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 850:
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            collisionResult = 0;
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = 0.0f;
            field0D8 = 10;
            collisionResult = 0;
        }
        scaleX -= 0.02f;
        scaleY -= 0.02f;
        if (animationStage == 0) {
            if (color[0] > 30) {
                color[0] -= 30;
            }
            else {
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
        break;
    case 990:
        if (static_cast<MeilingFighter*>(owner)->fieldF2A == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = owner->y + 100.0f;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 2.0f;
                scaleY = 2.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            rotationZ += 1.0f;
            if (animationStage == 0) {
                if (color[0] < 180) {
                    color[0] += 25;
                }
                else {
                    color[0] = 180;
                }
                if (static_cast<MeilingFighter*>(owner)->fieldF2A >= 120) {
                    ResetSecondaryCounter(1);
                    color[0] = 180;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 30) {
                    color[0] -= 30;
                }
                else {
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
    case 991:
        if (static_cast<MeilingFighter*>(owner)->fieldF2A == 0 && animationStage < 2) {
            ResetSecondaryCounter(2);
            return;
        }
        else {
            x = owner->x;
            y = owner->y + 100.0f;
            field08A = 1;
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 0.0f;
                scaleY = 0.0f;
                color[0] = 0;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            scaleX = static_cast<MeilingFighter*>(owner)->fieldF2A / 45.0f;
            scaleY = scaleX;
            if (animationStage == 0) {
                if (color[0] < 230) {
                    color[0] += 25;
                }
                else {
                    color[0] = 255;
                }
                if (static_cast<MeilingFighter*>(owner)->fieldF2A >= 120) {
                    ResetSecondaryCounter(1);
                    color[0] = 255;
                    return;
                }
            }
            if (animationStage == 2) {
                if (color[0] >= 10) {
                    color[0] -= 10;
                }
                else {
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
    case 994:
        x = owner->x;
        y = 1.0f;
        field08A = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 3.0f;
            scaleY = 3.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
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
            scaleX = static_cast<float>(owner->spellTimer) / field0D8 * 2 + 1.0f;
            scaleY = static_cast<float>(owner->spellTimer) / field0D8 * 2 + 1.0f;
            rotationZ -= 1.0f;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(1);
                return;
            }
        }
        break;
    case 950:
        if (owner->action != 700 && owner->action != 701 && owner->action != 706 && owner->action != 707) {
            ClearFrameInfo();
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(0.0f, 0.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
                collisionResult = 0;
                remainingHits = 1;
                velocityY = 15.0f;
            }
            rotationZ -= 35.0f;
            y += velocityY;
            if (y > 1000.0f) {
                ClearFrameInfo();
                return;
            }
            else {
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;
    case 951:
        if (animationStage < 1) {
            y = owner->y;
        }
        x = owner->x;
        owner->fieldF0C = 1;
        if (owner->animationStage == 0 && ((owner->action >= 70 && owner->action <= 88 && owner->action != 76) || owner->action == 181 || owner->action == 180 || owner->action == 145)) {
            ClearFrameInfo();
            owner->fieldF0C = 0;
            return;
        }
        else {
            if (animationStage == 0 && animationFrame == 0) {
                ResetTransform(-45.0f, 45.0f, 0.0f);
                scaleX = 1.0f;
                scaleY = 1.0f;
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                color[3] = 255;
            }
            if (animationStage == 0 && (owner->action == 96 || owner->action == 97) && owner->animationStage == 5) {
                ResetSecondaryCounter(1);
                rotationZ = 0.0f;
                return;
            }
            else if (animationStage == 5 && (owner->action == 95 || owner->action == 94 || owner->action == 93 || owner->action == 796 || owner->action == 771) && owner->animationStage == 3) {
                ResetSecondaryCounter(6);
                return;
            }
            else if (animationStage == 7 && (owner->action == 95 || owner->action == 94 || owner->action == 93 || owner->action == 796) && owner->animationStage == 11) {
                ClearFrameInfo();
                owner->fieldF0C = 0;
                return;
            }
            else {
                if (animationStage == 7 && animationFrame == 0 && owner->action != 771 && owner->action != 772) {
                    velocityY = 15.0f;
                    field05C = -1.0f;
                }
                if (animationStage == 7 && owner->action != 772 && owner->action != 771) {
                    velocityY += field05C;
                    y += velocityY;
                }
                if (animationStage == 7 && (owner->action == 772 || owner->action == 771)) {
                    x = owner->x + facing * 120;
                    y = owner->y + 100.0f;
                }
                if (animationStage == 0 || animationStage == 7) {
                    rotationZ -= 35.0f;
                }
                if (AdvanceNestedFrame() == animationStageCount) ClearFrameInfo();
            }
        }
        break;
    case 995:
        facing = 1;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 1.0f;
            scaleY = 1.0f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = RecordedRange(0, 360) - 180;
            field0DA = 15;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) field0DA = 3;
            SetPolarVelocity(field0D8, field0DA * 0.8f);
        }
        if (animationStage == 1) {
            field0D8 = AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f;
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ClearFrameInfo();
                if (owner->opponent->bombCount < 2) {
                    ++owner->opponent->bombCount;
                }
                else {
                    owner->opponent->score += 20000;
                }
                PlaySharedSound(46);
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
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
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            velocityX = 0.0f;
            velocityY = -1.0f;
            field0D8 = RecordedRange(0, 360) - 180;
            field0DA = 15;
        }
        if (animationStage == 0) {
            --field0DA;
            if (field0DA < 3) field0DA = 3;
            SetPolarVelocity(field0D8, field0DA * 0.8f);
        }
        if (animationStage == 1) {
            field0D8 = AngleAt00483300(owner->opponent->y + 100.0f - y, owner->opponent->x - x) / 0.017453288659453392f;
            SetPolarVelocity(field0D8, 20.0f);
            if (x - owner->opponent->x < 20.0f && x - owner->opponent->x > -20.0f && y - owner->opponent->y < 120.0f && y - owner->opponent->y > 80.0f) {
                ++owner->fieldEFA;
                PlaySharedSound(46);
                ClearFrameInfo();
                if (owner->opponent->spiritCooldown > 0) {
                    if (owner->opponent->spiritCooldown > 5) {
                        owner->opponent->spiritCooldown -= 5;
                    }
                    else {
                        owner->opponent->spiritCooldown = 0;
                        owner->opponent->spirit = 1000;
                    }
                    return;
                }
                else if (owner->opponent->spirit < 990) {
                    owner->opponent->spirit += 10;
                }
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->spellDeclarationExpired == 0) {
                        if (owner->opponent->spellPower < 998.9) {
                            owner->opponent->spellPower += 0.5f;
                        }
                        else {
                            owner->opponent->spellPower = 900.0f;
                        }
                    }
                }
                return;
            }
        }
        x += velocityX;
        y -= velocityY;
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
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            field01A = 1250;
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
            scaleX = static_cast<float>(owner->spellTimer) / field0D8 * 2;
            scaleY = static_cast<float>(owner->spellTimer) / field0D8 * 2;
            rotationZ += 1.0f;
            if (AdvanceNestedFrame() == animationStageCount) {
                ResetSecondaryCounter(10);
                break;
            } else if (animationStage < animationStageCount) {
                // A stage in progress continues on the next tick.
            }
        }
        break;
    case 998:
        facing = owner->facing;
        if (animationStage == 0 && animationFrame == 0) {
            ResetTransform(0.0f, 0.0f, 0.0f);
            scaleX = 2.5f;
            scaleY = 2.5f;
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            color[3] = 255;
            rotationY = 50.0f;
            field0D8 = 0;
        }
        if (owner->action > 149 && owner->action < 154 && field0D8 == 0) {
            x = owner->x + facing * 57;
            y = owner->y + 94.0f;
        }
        if (owner->action > 153 && owner->action < 158 && field0D8 == 0) {
            x = owner->x + facing * 57;
            y = owner->y + 60.0f;
        }
        if (owner->action == 158 && field0D8 == 0) {
            x = owner->x + facing * 57;
            y = owner->y + 100.0f;
        }
        if ((owner->action < 150 || owner->action > 158) && field0D8 == 0) {
            field0D8 = 1;
            owner->fieldF0A = 0;
        }
        rotationZ -= 3.0f;
        if (field0D8 > 0) {
            if (color[0] > 30) {
                color[0] -= 30;
            }
            else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount) {
            ResetSecondaryCounter(1);
        }
        break;
    default:
        AdvanceNestedFrame();
        break;
    }
}
