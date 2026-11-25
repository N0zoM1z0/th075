#include "engine/MathFloatHelpers.hpp"
#include "engine/GameSharedState.hpp"
#include "characters/CharacterObject.hpp"
#include "characters/remilia/RemiliaFighter.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "battle/BattleSessionState.hpp"
#include "battle/EffectServices.hpp"

// F1194: complete natural C++ reconstruction of RemiliaObject::Advance.
// The 28,432-byte native CODE body and its 232-byte jump table plus 198-byte
// remap are compared in one complete extent; table bytes are not CODE credit.
// All 696 physical COFF relocations resolve to their original destinations.
void RemiliaObject::Advance()
{
    if (owner->opponent->opponentFreezeSnapshot != 0) return;
    if (owner->opponentFreezeSnapshot != 0 && field08A == 0) return;
    if (hitstopFrames != 0) {
        hitstopFrames--;
        return;
    }
    switch (action) {

// Native0055AD32..0055B0DA observation chunk; no standalone unit or credit.
case 800:
    if (collisionResult == 6 && animationStage == 4) {
        collisionResult = 0;
        remainingHits = 1;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (x > 1400.0f || x < -120.0f) {
        ClearFrameInfo();
        return;
    }
    rotationZ = rotationZ + 5.0f;
    x = facing * velocityX + x;
    y = y + velocityY;
    if (remainingHits == 0 && animationStage < 5) {
        ResetSecondaryCounter(5);
        scaleX = scaleX + 0.5f;
        scaleY = scaleY + 0.5f;
        return;
    } else {
        if (animationStage == 5) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            scaleX = scaleX * 0.75f;
            scaleY = scaleY * 0.75f;
        }
        if (animationStage == 1) {
            scaleX = scaleX + 0.05f;
            scaleY = scaleY + 0.05f;
            if (scaleX > 2.5f) {
                scaleX = 2.5f;
                scaleY = 2.5f;
            }
            if (owner->action == 400 && owner->animationStage > 4) {
                ResetSecondaryCounter(field0D8 + 2);
                remainingHits = field0D8 + 1;
                velocityX = field0D8 * 4.0f + 12.0f;
                return;
            }
            if (owner->action != 400)
                ResetSecondaryCounter(5);
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0) {
            ResetSecondaryCounter(1);
            field0D8++;
            if (field0D8 > 2) field0D8 = 2;
        }
        if (animationStage == 3 && animationFrame == 0) {
            collisionResult = 0;
            ResetSecondaryCounter(2);
        }
        if (animationStage == 4 && animationFrame == 0) {
            collisionResult = 0;
            ResetSecondaryCounter(3);
        }
        if (animationStage == 5 && animationFrame == 0) {
            collisionResult = 0;
            ResetSecondaryCounter(4);
        }
    }
    return;

// Native0055B0DA..0055B21F observation chunk; no standalone unit or credit.
case 801:
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 0;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationY = 60.0f;
    }
    scaleX = scaleX + 0.3f;
    scaleY = scaleY + 0.3f;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (color[0] > 15)
        color[0] = color[0] - 15;
    else
        color[0] = 0;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055B21F..0055B599 observation chunk; no standalone unit or credit.
case 802: {
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i802 = 0; i802 < 2; i802++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        SetPolarVelocity(field0C8, field0CC);
    }
    if (animationStage == 1 && animationFrame == 0 && owner->spirit > 0) {
        owner->UpdateGaugeTimer(15);
        owner->PlaySound(0);
        owner->SpawnBattleEffect(803, x, y, facing, 1);
    }
    y = y - velocityY;
    x = facing * velocityX + x;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (animationStage < 2 &&
        (owner->action != 600 || (owner->action == 600 && owner->animationStage > 9))) {
        ResetSecondaryCounter(2);
        return;
    } else {
        if (animationStage == 2) {
            if (color[0] > 15) {
                color[0] = color[0] - 15;
            } else {
                color[0] = 0;
                ClearFrameInfo();
                return;
            }
        }
        if (AdvanceNestedFrame() == animationStageCount)
            ClearFrameInfo();
        if (animationStage == 2 && animationFrame == 0 && owner->action == 600 &&
            field0D8 < 3 && owner->spirit > 0)
            ResetSecondaryCounter(1);
    }
    return;
}

// Native0055B599..0055B7B7 observation chunk; no standalone unit or credit.
case 803: {
    if (owner->action > 49 && owner->action < 150 && remainingHits > 0) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i803 = 0; i803 < 2; i803++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 1;
        collisionResult = 0;
        velocityX = 15.0f;
    }
    x = facing * velocityX + x;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (remainingHits == 0) {
        if (color[0] > 10)
            color[0] = color[0] - 10;
        else
            ClearFrameInfo();
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(1);
    return;
}

// Native0055B7B7..0055BAAA observation chunk; no standalone unit or credit.
case 804: {
    if (collisionResult == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i804 = 0; i804 < 2; i804++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0DA = field0C8;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(
            field0DA + 15 - RecordedRange(0, 30),
            RecordedRange(1600, 2400) * 0.01f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    }
    if ((collisionResult == 1 || collisionResult == 2 ||
         collisionResult == 4) && animationStage < 2) {
        ResetSecondaryCounter(2);
        return;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (color[0] > 20 && animationStage == 2)
        color[0] = color[0] - 20;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;
}

// Native0055BAAA..0055BC84 observation chunk; no standalone unit or credit.
case 805:
    if (animationStage == 0 && animationFrame == 0) {
        collisionResult = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 0.5f;
        scaleY = 0.5f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 5;
        velocityX = 15.0f;
    }
    x = facing * velocityX + x;
    velocityX = velocityX - 0.5f;
    if (velocityX < 8.0f) velocityX = 8.0f;
    if (collisionResult == 4) {
        collisionResult = 0;
        remainingHits--;
    }
    if (collisionResult == 6) {
        collisionResult = 0;
        remainingHits++;
    }
    if (collisionResult != 0) remainingHits = 0;
    if (animationStage == 1 && remainingHits == 0)
        ResetSecondaryCounter(2);
    if (animationStage == 0) {
        scaleX = scaleX + 0.2f;
        scaleY = scaleY + 0.2f;
    }
    if (animationStage == 2) {
        if (color[0] > 20) {
            color[0] = color[0] - 20;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055BC84..0055BE29 observation chunk; no standalone unit or credit.
case 806:
    if (owner->action == 700 && animationStage < 19)
        x = owner->x;
    if (owner->action != 700 && animationStage < 19) {
        ResetSecondaryCounter(19);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        remainingHits = 12;
        collisionResult = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = 0;
        field0DA = 0;
    }
    if (collisionResult != 0 && ++field0DA > 5) {
        field0DA = 0;
        collisionResult = 0;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 19 && animationFrame == 0 && field0D8 < 3) {
        field0D8++;
        collisionResult = 0;
        ResetSecondaryCounter(9);
    }
    return;

// Native0055BE29..0055BF3E observation chunk; no standalone unit or credit.
case 807:
    if (owner->action == 394) {
        x = owner->x + facing * 151;
        y = owner->y + 104.0f;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 3.0f;
        scaleY = 3.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    scaleX = scaleX * 0.8f;
    scaleY = scaleY * 0.8f;
    if (animationStage > 1 && color[0] > 10)
        color[0] = color[0] - 10;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055BF3E..0055C03D observation chunk; no standalone unit or credit.
case 808:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 5;
        collisionResult = 0;
        velocityX = 45.0f;
        velocityY = 0.0f;
    }
    x = facing * velocityX + x;
    if (x > 1800.0f || x < -680.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(1);
        collisionResult = 0;
    }
    return;

// Native0055C03D..0055C154 observation chunk; no standalone unit or credit.
case 809:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = facing * -35;
        rotationY = 70.0f;
        rotationZ = RecordedRange(0, 359);
    }
    scaleX = scaleX * 1.05f;
    scaleY = scaleY * 1.05f;
    rotationZ = rotationZ + 6.0f;
    if (color[0] > 10) {
        color[0] = color[0] - 10;
    } else {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055C154..0055C2FE observation chunk; no standalone unit or credit.
case 810:
    if (owner->action == 705 && animationStage < 19)
        x = owner->x + 0.0f;
    if (owner->action != 705 && animationStage < 19) {
        ResetSecondaryCounter(19);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        remainingHits = 20;
        collisionResult = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.5f;
        scaleY = 1.25f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = 0;
        field0DA = 0;
    }
    if (collisionResult != 0 && ++field0DA > 5) {
        field0DA = 0;
        collisionResult = 0;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 19 && animationFrame == 0 && field0D8 < 6) {
        field0D8++;
        collisionResult = 0;
        ResetSecondaryCounter(9);
    }
    return;

// Native0055C2FE..0055C3FD observation chunk; no standalone unit or credit.
case 811:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 1;
        collisionResult = 0;
        velocityX = 45.0f;
        velocityY = 0.0f;
    }
    x = facing * velocityX + x;
    if (x > 1800.0f || x < -680.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(1);
        collisionResult = 0;
    }
    return;

// Native0055C3FD..0055C514 observation chunk; no standalone unit or credit.
case 814:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = facing * -30;
        rotationY = 70.0f;
        rotationZ = RecordedRange(0, 359);
    }
    scaleX = scaleX * 1.05f;
    scaleY = scaleY * 1.05f;
    rotationZ = rotationZ + 6.0f;
    if (color[0] > 10) {
        color[0] = color[0] - 10;
    } else {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055C514..0055C7D8 observation chunk; no standalone unit or credit.
case 816: {
    if (collisionResult == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i816 = 0; i816 < 3; i816++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(
            field0C8 + 15.0f - RecordedRange(0, 30), 25.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    }
    if ((collisionResult == 1 || collisionResult == 2 ||
         collisionResult == 4) && animationStage < 2) {
        ResetSecondaryCounter(2);
        return;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (color[0] > 20 && animationStage == 2)
        color[0] = color[0] - 20;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;
}

// Native0055C7D8..0055CCD6 observation chunk; no standalone unit or credit.
case 817: {
    if (x > 1380.0f || x < -100.0f ||
        y > 1000.0f || y < -240.0f) {
        ClearFrameInfo();
        return;
    }
    if (collisionResult == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i817 = 0; i817 < 5; i817++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
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
        field0DA = 0;
        field0DE = 0;
        field0DC = field0C8;
        SetPolarVelocity(field0DC, field0D8 * 0.1f + 10.0f);
    }
    if (animationStage < 5) {
        field0DA = AngleAt00483300(
            owner->opponent->y - y + 100.0f,
            (owner->opponent->x - x) * facing) / 0.01745328866f;
        if (field0DA > field0DC + 10)
            field0DC = field0DC + 1;
        if (field0DA < field0DC - 10)
            field0DC = field0DC - 1;
        if (field0DC > 90) field0DC = 90;
        if (field0DC < -90) field0DC = -90;
        SetPolarVelocity(field0DC, field0D8 * 0.15f + 7.0f);
    }
    field0D8 = field0D8 + 2;
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (collisionResult != 0 && collisionResult != 6) {
        ResetSecondaryCounter(5);
        velocityX = 0.0f;
        velocityY = 0.0f;
        scaleX = 2.0f;
        scaleY = 2.0f;
    }
    if (animationStage == 5) {
        scaleX = scaleX * 0.85f;
        scaleY = scaleY * 0.85f;
        if (color[0] >= 25) {
            color[0] = color[0] - 25;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    if (animationStage == 5 && animationFrame == 0)
        ResetSecondaryCounter(1);
    return;
}

// Native0055CCD6..0055CDFD observation chunk; no standalone unit or credit.
case 819:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = facing * 35;
        rotationY = 70.0f;
        rotationZ = RecordedRange(0, 359);
    }
    scaleX = scaleX * 1.05f;
    scaleY = scaleY * 1.05f;
    rotationZ = rotationZ + 6.0f;
    if (color[0] > 10) {
        color[0] = color[0] - 10;
    } else {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055CDFD..0055CEE8 observation chunk; no standalone unit or credit.
case 820:
    if (owner->action == 703 || owner->action == 708 || owner->action == 741) {
        x = owner->x;
        y = owner->y;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055CEE8..0055D2B4 observation chunk; no standalone unit or credit.
case 821: {
    if (collisionResult == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i821 = 0; i821 < 10; i821++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        field0DA = field0C8;
        field0DC = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 6;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    SetPolarVelocity(field0DA, 25.0f);
    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    if (collisionResult == 4 && remainingHits > 0)
        collisionResult = 0;
    // Preserve both independently observed nonzero flag reads.
    if (collisionResult != 0 && collisionResult != 0)
        remainingHits = 0;
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (collisionResult != 0) {
        if (color[0] > 20) {
            color[0] = color[0] - 20;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(4);
    if (animationStage == 4 && animationFrame == 0) {
        owner->field314 = field0DA;
        owner->SpawnBattleEffect(837, x, y, facing, 1);
    }
    if (animationStage == 9 && animationFrame == 0) {
        owner->field314 = field0DA;
        owner->SpawnBattleEffect(837, x, y, facing, 1);
    }
    return;
}

// Native0055D2B4..0055D3BF observation chunk; no standalone unit or credit.
case 822:
    if (owner->action == 502) {
        x = owner->x;
        y = owner->y;
    }
    if (owner->action != 502 || (owner->action == 502 && owner->animationStage > 15)) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055D3BF..0055D4CA observation chunk; no standalone unit or credit.
case 823:
    if (owner->action == 503) {
        x = owner->x;
        y = owner->y;
    }
    if (owner->action != 503 || (owner->action == 503 && owner->animationStage > 15)) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055D4CA..0055D5EF observation chunk; no standalone unit or credit.
case 824:
    if (owner->action == 504) {
        x = owner->x;
        y = owner->y;
    }
    if (owner->action != 504 || (owner->action == 504 && owner->animationStage > 15)) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 80.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationZ = -(field0C8 + 15.0f);
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055D5EF..0055D6D4 observation chunk; no standalone unit or credit.
case 825:
    if (owner->action == 304) {
        x = owner->x;
        y = owner->y;
    }
    if (owner->action != 304) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055D6D4..0055D883 observation chunk; no standalone unit or credit.
case 826:
    if (owner->action == 510 || owner->action == 511) {
        x = owner->x;
        y = owner->y;
    }
    if ((owner->action != 510 && owner->action != 511) ||
        (owner->action == 510 && owner->animationStage > 7) ||
        (owner->action == 511 && owner->animationStage > 11)) {
        if (color[0] > 30) {
            color[0] = color[0] - 30;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        if (owner->action == 511) {
            scaleX = 1.5f;
            scaleY = 1.5f;
            rotationZ = 20.0f;
        }
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(0);
    return;

// Native0055D883..0055D9C5 observation chunk; no standalone unit or credit.
case 827:
    if ((owner->action == 700 || owner->action == 705) && animationStage < 19)
        x = owner->x;
    if ((owner->action != 700 && owner->action != 705) ||
        (owner->action == 700 && owner->animationStage > 7)) {
        if (color[0] > 20) {
            color[0] = color[0] - 20;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055D9C5..0055DAA5 observation chunk; no standalone unit or credit.
case 828:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 45.0f;
    }
    x = facing * velocityX + x;
    if (x > 1640.0f || x < -360.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055DAA5..0055DB85 observation chunk; no standalone unit or credit.
case 829:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 2.0f;
        scaleY = 2.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 45.0f;
    }
    x = facing * velocityX + x;
    if (x > 1640.0f || x < -360.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055DB85..0055DC5D observation chunk; no standalone unit or credit.
case 830:
    if (owner->action == 310) x = owner->x;
    if (owner->action != 310) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    return;

// Native0055DC5D..0055DD22 observation chunk; no standalone unit or credit.
case 831:
    if (owner->action == 309) x = owner->x;
    if (owner->action != 309) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    return;

// Native0055DD22..0055DE5F observation chunk; no standalone unit or credit.
case 832:
    if ((owner->action == 700 || owner->action == 705) && animationStage < 19)
        x = owner->x;
    if ((owner->action != 700 && owner->action != 705) ||
        (owner->action == 705 && owner->animationStage > 7)) {
        if (color[0] > 20) {
            color[0] = color[0] - 20;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 2.0f;
        scaleY = 2.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055DE5F..0055DF37 observation chunk; no standalone unit or credit.
case 833:
    if (owner->action == 307) x = owner->x;
    if (owner->action != 307) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    return;

// Native0055DF37..0055E00F observation chunk; no standalone unit or credit.
case 834:
    if (owner->action == 307) x = owner->x;
    if (owner->action != 307) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (owner->hitstopFrames == 0 && AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    return;

// Native0055E00F..0055E158 observation chunk; no standalone unit or credit.
case 835:
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 0;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        rotationZ = RecordedRange(0, 359);
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (collisionResult == 6) {
        collisionResult = 0;
        remainingHits++;
    }
    if (collisionResult == 4) collisionResult = 0;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055E158..0055E250 observation chunk; no standalone unit or credit.
case 836:
    if (owner->action == 709 && animationStage < 16) {
        x = owner->x + facing * 55;
        y = owner->y + 86.0f;
    } else {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.5f;
        scaleY = 3.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationZ = -120.0f;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(0);
        return;
    }
    return;

// Native0055E250..0055E41C observation chunk; no standalone unit or credit.
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
        rotationY = 60.0f;
        rotationX = -facing * field0C8;
        velocityX = 0.0f;
        velocityY = 0.0f;
        field0D8 = 10;
        collisionResult = 0;
    }
    rotationZ = rotationZ + 1.0f;
    scaleX = field0D8 * 0.05f + 0.05f + scaleX;
    scaleY = field0D8 * 0.05f + 0.05f + scaleY;
    if (field0D8 > 0) field0D8--;
    if (animationStage == 2) {
        if (color[0] > 20) {
            color[0] = color[0] - 20;
            color[3] = color[3] - 20;
            color[2] = color[2] - 20;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055E41C..0055E813 observation chunk; no standalone unit or credit.
case 838: {
    if (collisionResult == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i838 = 0; i838 < 10; i838++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        field0DA = field0C8;
        field0DC = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 6;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    SetPolarVelocity(field0DA, 3.0f);
    rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    if (collisionResult == 4 && remainingHits > 0)
        collisionResult = 0;
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (remainingHits == 0) {
        if (color[0] > 20) {
            color[0] = color[0] - 20;
        } else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(4);
    if (animationStage == 4 && animationFrame == 0) {
        owner->field314 = field0DA;
        owner->SpawnBattleEffect(837, x, y, facing, 1);
        if (collisionResult == 2)
            collisionResult = 0;
        else
            ResetPrimaryCounters(821);
    }
    if (animationStage == 9 && animationFrame == 0) {
        owner->field314 = field0DA;
        owner->SpawnBattleEffect(837, x, y, facing, 1);
        if (collisionResult == 2)
            collisionResult = 0;
        else
            ResetPrimaryCounters(821);
    }
    return;
}

// Native0055E813..0055EB1A observation chunk; no standalone unit or credit.
case 839: {
    if (collisionResult == 5) {
        ClearFrameInfo();
        return;
    }
    if (owner->action > 49 && owner->action < 150 && animationStage < 2) {
        ClearFrameInfo();
        if (owner->fieldEFA > 25) {
            owner->fieldEFA = 0;
            owner->SpawnBattleEffect(995, x, y, 1, 1);
        }
        for (int i839 = 0; i839 < 10; i839++)
            owner->SpawnBattleEffect(996, x, y, 1, 1);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 3;
        collisionResult = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 0;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 18.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 1 && animationFrame == 0)
        owner->SpawnBattleEffect(835, x, y, facing, 1);
    velocityX = velocityX - 0.45f;
    if (velocityX < -18.0f) velocityX = -18.0f;
    if (collisionResult == 4) collisionResult = 0;
    if (remainingHits == 0) {
        ClearFrameInfo();
        return;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        if (field0D8 < 7) {
            ResetSecondaryCounter(1);
            collisionResult = 0;
            field0D8++;
            return;
        } else {
            ClearFrameInfo();
        }
    }
    return;
}

// Native0055EB1A..0055ED0A observation chunk; no standalone unit or credit.
case 850:
    facing = owner->facing;
    if (owner->action > 149 && owner->action < 154) {
        x = owner->x + facing * 30;
        y = owner->y + 94.0f;
    }
    if (owner->action > 153 && owner->action < 158) {
        x = owner->x + facing * 70;
        y = owner->y + 60.0f;
    }
    if (owner->action == 158) {
        x = owner->x + facing * 57;
        y = owner->y + 100.0f;
    }
    if ((owner->action < 150 || owner->action > 158) && animationStage == 0)
        ResetSecondaryCounter(1);
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055ED0A..0055EF01 observation chunk; no standalone unit or credit.
case 900:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(field0C8, 40.0f);
        rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    owner->field314 = -field0C8;
    owner->SpawnBattleEffect(901,
        RecordedRange(0, 60) + x - 30.0f,
        y + 30.0f - RecordedRange(0, 60),
        facing, 1);
    if (x > 1800.0f || x < -680.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(1);
        collisionResult = 0;
    }
    return;

// Native0055EF01..0055F14D observation chunk; no standalone unit or credit.
case 901:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = RecordedRange(0, 5);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(
            -field0C8 + 20.0f - RecordedRange(0, 40),
            RecordedRange(5, 10));
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1300.0f || x < -60.0f ||
        y > 960.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0) {
        if (field0D8 * 0.1f + 0.5f > scaleX) {
            scaleX = scaleX + 0.1f;
            scaleY = scaleX;
        } else {
            ResetSecondaryCounter(1);
            return;
        }
    }
    if (animationStage == 2) {
        scaleX = scaleX * 0.9f;
        scaleY = scaleX;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055F14D..0055F208 observation chunk; no standalone unit or credit.
case 902:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 4.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationZ = -field0C8;
    }
    // The actual multiplier is the complete eight-byte0.85 literal.
    scaleY = scaleY * 0.85;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055F208..0055F43A observation chunk; no standalone unit or credit.
case 903:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = RecordedRange(0, 5);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(
            RecordedRange(0, 359),
            RecordedRange(5, 10));
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1300.0f || x < -60.0f ||
        y > 960.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0) {
        if (field0D8 * 0.1f + 0.5f > scaleX) {
            scaleX = scaleX + 0.1f;
            scaleY = scaleX;
        } else {
            ResetSecondaryCounter(1);
            return;
        }
    }
    if (animationStage == 2) {
        scaleX = scaleX * 0.9f;
        scaleY = scaleX;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055F43A..0055F631 observation chunk; no standalone unit or credit.
case 904:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(field0C8, 40.0f);
        rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    owner->field314 = -field0C8;
    owner->SpawnBattleEffect(901,
        RecordedRange(0, 60) + x - 30.0f,
        y + 30.0f - RecordedRange(0, 60),
        facing, 1);
    if (x > 1800.0f || x < -680.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(1);
        collisionResult = 0;
    }
    return;

// Native0055F631..0055F8F2 observation chunk; no standalone unit or credit.
case 905:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (owner->action == 751 && animationStage < 2) {
        x = owner->x;
        y = owner->y + 250.0f;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 0.0f;
        velocityY = 0.0f;
    } else if (animationStage != 0 || animationFrame != 0) {
        // Non-initial frames preserve the existing transform state.
    }
    if (animationStage == 1) {
        scaleX = scaleX + 0.05f;
        scaleY = scaleY + 0.05f;
        if (scaleX > 1.0f) {
            scaleX = 1.0f;
            scaleY = 1.0f;
        }
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    rotationZ = rotationZ + 2.0f;
    if (x > 1800.0f || x < -680.0f ||
        y > 1280.0f || y < -380.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(2);
        collisionResult = 0;
        return;
    }
    if (animationFrame == 0) collisionResult = 0;
    if (animationStage == 2 && animationFrame == 0) {
        owner->PlaySound(17);
        SetPolarVelocity(AngleAt00483300(
            owner->opponent->y + 100.0f - y,
            (owner->opponent->x - x) * facing) / 0.01745328866f, 20.0f);
    }
    return;

// Native0055F8F2..0055FA76 observation chunk; no standalone unit or credit.
case 906:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 1) {
        scaleX = scaleX + 0.1f;
        scaleY = scaleY + 0.1f;
        if (animationFrame > 15) {
            if (color[0] > 15)
                color[0] = color[0] - 15;
            else
                color[0] = 0;
        }
    }
    rotationZ = rotationZ + 2.0f;
    if (x > 1800.0f || x < -680.0f ||
        y > 1280.0f || y < -380.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055FA76..0055FD08 observation chunk; no standalone unit or credit.
case 907:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if ((owner->action == 751 || owner->action == 753) && animationStage < 2) {
        x = owner->x;
        y = owner->y + 250.0f;
    }
    if ((owner->action == 751 || owner->action == 753) &&
        owner->animationStage > 7 && animationStage < 2) {
        ResetSecondaryCounter(2);
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 0) {
        scaleX = scaleX + 0.1f;
        scaleY = scaleY + 0.1f;
        if (scaleX > 1.0f) {
            scaleX = 1.0f;
            scaleY = 1.0f;
        }
    }
    if (animationStage == 2) {
        scaleX = scaleY * 0.85f;
        scaleY = scaleY * 0.85f;
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(2);
        collisionResult = 0;
        return;
    }
    if (animationFrame == 0) collisionResult = 0;
    if (animationStage == 2 && animationFrame == 0) {
        field0DA = RecordedRange(0, 40);
        scaleX = field0DA * 0.01f + 0.8f;
        scaleY = field0DA * 0.01f + 0.8f;
        ResetSecondaryCounter(1);
    }
    return;

// Native0055FD08..0055FEFA observation chunk; no standalone unit or credit.
case 908:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (owner->action == 752 && animationStage < 2) {
        x = owner->x;
        y = 0.0f;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = 75.0f;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 1) {
        scaleX = scaleX + 0.1f;
        scaleY = scaleY + 0.1f;
        if (scaleX > 1.0f) {
            scaleX = 1.0f;
            scaleY = 1.0f;
        }
    }
    if (animationStage == 2) {
        if (color[0] > 15)
            color[0] = color[0] - 15;
        else
            color[0] = 0;
    }
    rotationZ = rotationZ + 2.0f;
    if (x > 1800.0f || x < -680.0f ||
        y > 1280.0f || y < -380.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0055FEFA..0056001A observation chunk; no standalone unit or credit.
case 909:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        remainingHits = 1;
        collisionResult = 0;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 0) {
        scaleX = scaleX + 0.5f;
        scaleY = scaleY + 2.0f;
    }
    if (animationStage > 0) {
        scaleX = scaleX * 0.85f;
        scaleY = scaleY + 0.2f;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0056001A..00560140 observation chunk; no standalone unit or credit.
case 910:
    if (owner->action == 741) {
        x = owner->x;
        y = owner->y;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0DA = 0;
    }
    if (owner->hitstopFrames == 0) {
        if (AdvanceNestedFrame() == animationStageCount)
            ClearFrameInfo();
        if (animationStage == 38 && animationFrame == 0 &&
            field0DA < (3 - g_OptionsModeAt006714D0) * 2) {
            field0DA++;
            ResetSecondaryCounter(37);
        }
    }
    break;

// Native00560140..0056030A observation chunk; no standalone unit or credit.
case 911:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (owner->action == 752 && animationStage < 2) {
        x = owner->x;
        y = 0.0f;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        scaleX = 0.0f;
        scaleY = 0.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        rotationX = 75.0f;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (animationStage == 1) {
        scaleX = scaleX + 0.1f;
        scaleY = scaleY + 0.1f;
        if (animationFrame > 15) {
            if (color[0] > 15)
                color[0] = color[0] - 15;
            else
                color[0] = 0;
        }
    }
    rotationZ = rotationZ + 2.0f;
    if (x > 1800.0f || x < -680.0f ||
        y > 1280.0f || y < -380.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0056030A..0056052B observation chunk; no standalone unit or credit.
case 912:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = -RecordedRange(
            0, g_OptionsModeAt006714D0 * 3 + 40) - 20;
        velocityX = 0.0f;
        velocityY = 0.0f;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        scaleX = 0.25f;
        scaleY = 0.25f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        SetPolarVelocity(field0D8, 30.0f);
        rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (y + velocityY <= 0.0f) {
        velocityX = 0.0f;
        velocityY = 0.0f;
        y = 0.0f;
        owner->SetCameraShake(3.0f);
        ResetPrimaryCounters(909);
        rotationZ = 0.0f;
        color[0] = 0;
        owner->PlaySound(22);
        return;
    }
    if (x > 1400.0f || x < -120.0f) {
        ClearFrameInfo();
        return;
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native0056052B..005606D8 observation chunk; no standalone unit or credit.
case 913:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0DA = field0C8;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(field0DA, 18.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (color[0] > 20 && animationStage == 2)
        color[0] = color[0] - 20;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native005606D8..005608E6 observation chunk; no standalone unit or credit.
case 914:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0DA = field0C8;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(
            field0DA + 10 - RecordedRange(0, 20),
            RecordedRange(0, 9) + 6);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if ((collisionResult == 1 || collisionResult == 2 ||
         collisionResult == 4) && animationStage < 2) {
        ResetSecondaryCounter(2);
        return;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (color[0] > 20 && animationStage == 2)
        color[0] = color[0] - 20;
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native005608E6..00560F35 observation chunk; no standalone unit or credit.
case 915:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        field0DA = field0C8;
        field0DC = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        SetPolarVelocity(field0DA, 7.0f);
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    x = facing * velocityX + x;
    y = y - velocityY;
    field0D8--;
    if (g_OptionsModeAt006714D0 == 3 && ++field0DA > 180)
        field0DA = field0DA - 360;
    SetPolarVelocity(field0DA, 7.0f);
    if (field0D8 <= 0) {
        owner->field314 = field0DA;
        owner->SpawnBattleEffect(
            916, x, y, facing, 1);
        field0D8 = 10 - g_OptionsModeAt006714D0;
    }
    if (g_OptionsModeAt006714D0 > 0) {
        if (y > owner->viewTop && field0DC < 1 && velocityY < 0.0f) {
            owner->PlaySound(11);
            field0DA = -field0DA;
            field0DC++;
            collisionResult = 0;
            remainingHits = 1;
            field0CC = 4.0f;
        }
        if (y < 0.0f && field0DC < 1 && velocityY > 0.0f) {
            owner->PlaySound(11);
            field0DA = -field0DA;
            field0DC++;
            collisionResult = 0;
            remainingHits = 1;
            field0CC = 4.0f;
        }
        if (x < owner->cameraState.viewLeft && field0DC < 1 &&
            ((facing == -1 && velocityX > 0.0f) ||
             (facing == 1 && velocityX < 0.0f))) {
            owner->PlaySound(11);
            if (field0DA > 0)
                field0DA = 180 - field0DA;
            if (field0DA < 0)
                field0DA = -180 - field0DA;
            field0DC++;
            collisionResult = 0;
            remainingHits = 1;
            field0CC = 4.0f;
        }
        if (x > owner->viewRight && field0DC < 1 &&
            ((facing == -1 && velocityX < 0.0f) ||
             (facing == 1 && velocityX > 0.0f))) {
            owner->PlaySound(11);
            if (field0DA > 0)
                field0DA = 180 - field0DA;
            if (field0DA < 0)
                field0DA = -180 - field0DA;
            field0DC++;
            collisionResult = 0;
            remainingHits = 1;
            field0CC = 4.0f;
        }
    }
    if (x > 1400.0f || x < -160.0f ||
        y > 1000.0f || y < -160.0f) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 2) {
        if (color[0] > 20)
            color[0] = color[0] - 20;
        else {
            ClearFrameInfo();
            return;
        }
    }
    if (AdvanceNestedFrame() == animationStageCount)
        ClearFrameInfo();
    return;

// Native00560F35..00561265 observation chunk; no standalone unit or credit.
case 916:
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 0 && animationFrame == 0) {
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = 0;
        scaleX = 3.0f;
        scaleY = 3.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
        field0D8 = 0;
        field0DA = RecordedRange(0, 40) + field0C8 - 20.0f;
        SetPolarVelocity(
            field0DA, field0D8 * 0.05f);
        rotationZ = AngleAt00483300(velocityY, velocityX) / 0.01745328866f;
        collisionResult = 0;
        remainingHits = 1;
    }
    if (animationStage == 1) {
        scaleX = scaleX - 0.1f;
        scaleY = scaleY - 0.1f;
        if (scaleX < 1.0f) {
            scaleX = 1.0f;
            scaleY = 1.0f;
        }
    }
    if (animationStage == 2 && collisionResult != 0) {
        ResetSecondaryCounter(3);
        velocityX = 0.0f;
        velocityY = 0.0f;
        return;
    }
    if (animationStage == 3) {
        scaleX = scaleX * 0.8f;
        scaleY = scaleY * 0.8f;
    }
    if (x > 1380.0f || x < -100.0f ||
        y > 960.0f || y < -100.0f) {
        ClearFrameInfo();
        return;
    }
    if (animationStage == 2) {
        field0D8++;
        x = facing * velocityX + x;
        y = y - velocityY;
        SetPolarVelocity(
            field0DA, field0D8 * 0.05f);
    }
    if (AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        return;
    }
    break;

// Native00561265..00561591 observation chunk; no standalone unit or credit.
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
        field0DA--;
        if (field0DA < 3)
            field0DA = 3;
        SetPolarVelocity(
            field0D8, field0DA * 0.8f);
    }
    if (animationStage == 1) {
        field0D8 = AngleAt00483300(
            owner->opponent->y + 100.0f - y,
            owner->opponent->x - x) / 0.01745328866f;
        SetPolarVelocity(field0D8, 20.0f);
        if (x - owner->opponent->x < 20.0f &&
            x - owner->opponent->x > -20.0f &&
            y - owner->opponent->y < 120.0f &&
            y - owner->opponent->y > 80.0f) {
            ClearFrameInfo();
            if (owner->opponent->bombCount < 2)
                owner->opponent->bombCount++;
            else
                owner->opponent->score = owner->opponent->score + 20000;
            PlaySharedSound(46);
            return;
        }
    }
    x = x + velocityX;
    y = y - velocityY;
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(1);
    break;

// Native00561591..005619F7 observation chunk; no standalone unit or credit.
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
        field0DA--;
        if (field0DA < 3)
            field0DA = 3;
        SetPolarVelocity(
            field0D8, field0DA * 0.8f);
    }
    if (animationStage == 1) {
        field0D8 = AngleAt00483300(
            owner->opponent->y + 100.0f - y,
            owner->opponent->x - x) / 0.01745328866f;
        SetPolarVelocity(field0D8, 20.0f);
        if (x - owner->opponent->x < 20.0f &&
            x - owner->opponent->x > -20.0f &&
            y - owner->opponent->y < 120.0f &&
            y - owner->opponent->y > 80.0f) {
            owner->fieldEFA++;
            PlaySharedSound(46);
            ClearFrameInfo();
            if (owner->opponent->spiritCooldown > 0) {
                if (owner->opponent->spiritCooldown > 5)
                    owner->opponent->spiritCooldown = owner->opponent->spiritCooldown - 5;
                else {
                    owner->opponent->spiritCooldown = 0;
                    owner->opponent->spirit = 1000;
                }
                return;
            } else {
                if (owner->opponent->spirit < 990)
                    owner->opponent->spirit = owner->opponent->spirit + 10;
                else {
                    owner->opponent->spirit = 1000;
                    if (owner->opponent->spellDeclarationExpired == 0) {
                        if (owner->opponent->spellPower < 998.9)
                            owner->opponent->spellPower = owner->opponent->spellPower + 0.5f;
                        else
                            owner->opponent->spellPower = 900.0f;
                    }
                }
            }
            return;
        }
    }
    x = x + velocityX;
    y = y - velocityY;
    if (AdvanceNestedFrame() == animationStageCount)
        ResetSecondaryCounter(1);
    break;

// Native005619F7..00561B83 observation chunk; no standalone unit or credit.
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
        spriteOffsetZ = 1250;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        rotationX = -80.0f;
        field0D8 = owner->spellTimer;
    }
    if (owner->spellTimer <= 0) {
        ClearFrameInfo();
        return;
    }
    scaleX = static_cast<float>(owner->spellTimer) / field0D8 * 2.0f;
    scaleY = static_cast<float>(owner->spellTimer) / field0D8 * 2.0f;
    rotationZ = rotationZ + 1.0f;
    if (AdvanceNestedFrame() == animationStageCount) {
        ResetSecondaryCounter(9);
        return;
    }
    break;

    default:
        AdvanceNestedFrame();
        break;
    }
}
