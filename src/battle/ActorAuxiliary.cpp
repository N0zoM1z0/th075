#include "characters/PatchouliFighter.hpp"
#include "characters/MarisaFighter.hpp"
#include "battle/Fighter.hpp"
#include "characters/CharacterObject.hpp"
#include "battle/FighterAnimationPhaseBorrowedF1024.hpp"
#include "characters/CharacterAuxAction.hpp"
#include "characters/CharacterAIPolicy.hpp"

int g_AI507B20Countdown;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(owner) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(owner) + (offset))

void MarisaObject::UpdateTrackingNode()
{
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        field0DE = 0;
        field0E0 = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        remainingHits = 1;
        collisionResult = CollisionResult::None;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (action == 828) {
        static_cast<MarisaFighter*>(owner)->fieldF1A = static_cast<short>(x);
        static_cast<MarisaFighter*>(owner)->fieldF26 = static_cast<short>(y);
    }
    if (action == 829) {
        static_cast<MarisaFighter*>(owner)->fieldF1C = static_cast<short>(x);
        static_cast<MarisaFighter*>(owner)->fieldF28 = static_cast<short>(y);
    }
    if (action == 830) {
        static_cast<MarisaFighter*>(owner)->fieldF1E = static_cast<short>(x);
        static_cast<MarisaFighter*>(owner)->fieldF2A = static_cast<short>(y);
    }
    if (action == 831) {
        static_cast<MarisaFighter*>(owner)->fieldF20 = static_cast<short>(x);
        static_cast<MarisaFighter*>(owner)->fieldF2C = static_cast<short>(y);
    }
    if (action == 832) {
        static_cast<MarisaFighter*>(owner)->fieldF22 = static_cast<short>(x);
        static_cast<MarisaFighter*>(owner)->fieldF2E = static_cast<short>(y);
    }
    if (action == 833) {
        static_cast<MarisaFighter*>(owner)->fieldF24 = static_cast<short>(x);
        static_cast<MarisaFighter*>(owner)->fieldF30 = static_cast<short>(y);
    }
    if ((owner->action == 709 || owner->action == 710) &&
        owner->animationStage == 5 && owner->animationFrame == 0 &&
        field0DC == 0 && animationStage == 1 &&
        ((action == 833 && static_cast<MarisaFighter*>(owner)->fieldF16 == 6) ||
         (action == 832 && static_cast<MarisaFighter*>(owner)->fieldF16 == 5) ||
         (action == 831 && static_cast<MarisaFighter*>(owner)->fieldF16 == 4) ||
         (action == 830 && static_cast<MarisaFighter*>(owner)->fieldF16 == 3) ||
         (action == 829 && static_cast<MarisaFighter*>(owner)->fieldF16 == 2) ||
         (action == 828 && static_cast<MarisaFighter*>(owner)->fieldF16 == 1))) {
        field0DC = 1;
        field0DE = static_cast<short>(AngleAt00483300(
            owner->opponent->y + 100.0f - y,
            (owner->opponent->x - x) * facing) / 0.017453288659453392f);
        ResetSecondaryCounter(2);
        --static_cast<MarisaFighter*>(owner)->fieldF14;
        --static_cast<MarisaFighter*>(owner)->fieldF16;
    }
    if ((owner->action == 716 || owner->action == 717) &&
        owner->animationStage == 5 && owner->animationFrame == 0 &&
        (animationStage == 1 || animationStage == 2) &&
        ((action == 833 && static_cast<MarisaFighter*>(owner)->fieldF16 == 6) ||
         (action == 832 && static_cast<MarisaFighter*>(owner)->fieldF16 == 5) ||
         (action == 831 && static_cast<MarisaFighter*>(owner)->fieldF16 == 4) ||
         (action == 830 && static_cast<MarisaFighter*>(owner)->fieldF16 == 3) ||
         (action == 829 && static_cast<MarisaFighter*>(owner)->fieldF16 == 2) ||
         (action == 828 && static_cast<MarisaFighter*>(owner)->fieldF16 == 1))) {
        ResetSecondaryCounter(3);
        --static_cast<MarisaFighter*>(owner)->fieldF16;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (static_cast<MarisaFighter*>(owner)->fieldF12 == 2) {
        owner->SpawnBattleEffect(836, x, y, 1, 0);
    }
    if (static_cast<MarisaFighter*>(owner)->fieldF12 == 99 && animationStage < 7 && field0DC == 0) ResetSecondaryCounter(7);
    if (static_cast<MarisaFighter*>(owner)->fieldF12 == 3 && animationStage < 2) ResetSecondaryCounter(2);
    field0D8 = static_cast<short>((static_cast<MarisaFighter*>(owner)->fieldF10 - 180) + field0C8);
    if (field0D8 > 180) field0D8 -= 360;
    if (field0D8 < -180) field0D8 += 360;
    field0DA += 5;
    if (static_cast<MarisaFighter*>(owner)->fieldF12 != 6 && owner->roundsRemaining > 1 && field0DA > 120) field0DA = 120;
    if (owner->roundsRemaining == 1 && field0DA > 140) field0DA = 140;
    if (static_cast<MarisaFighter*>(owner)->fieldF12 == 6 && field0DA > 180) field0DA = 180;
    if (animationStage == 1) {
        SetPolarVelocity(field0D8, field0DA);
        x = static_cast<int>(owner->fieldF0C + facing * velocityX);
        y = static_cast<int>(owner->fieldF0E + velocityY);
        remainingHits = 1;
        collisionResult = CollisionResult::None;
    }
    if (animationStage == 2 && static_cast<MarisaFighter*>(owner)->fieldF12 == 3 && field0DC == 0) {
        SetPolarVelocity(field0D8, field0DA);
        x = static_cast<int>(owner->fieldF0C + facing * velocityX);
        y = static_cast<int>(owner->fieldF0E + velocityY);
        owner->SpawnBattleEffect(836, x, y, 1, 0);
        if (collisionResult != CollisionResult::None && collisionResult != CollisionResult::ClashConsumedHit && collisionResult != CollisionResult::ClashPreservedHits && collisionResult != CollisionResult::Grazed) { ResetSecondaryCounter(7); return; }
        if (collisionResult == CollisionResult::ClashConsumedHit || collisionResult == CollisionResult::ClashPreservedHits || collisionResult == CollisionResult::Grazed) {
            remainingHits = 1;
            collisionResult = CollisionResult::None;
        }
    }
    if (animationStage == 2 && field0DC > 0) {
        SetPolarVelocity(field0DE, field0DC * 0.5f + 5.0f);
        ++field0DC;
        field0E0 = 1;
        x = facing * velocityX + x;
        y = y - velocityY;
        owner->SpawnBattleEffect(836, x, y, 1, 0);
        if (collisionResult == CollisionResult::ClashConsumedHit || (collisionResult != CollisionResult::None && collisionResult != CollisionResult::ClashConsumedHit && collisionResult != CollisionResult::ClashPreservedHits && collisionResult != CollisionResult::Grazed)) { ResetSecondaryCounter(7); return; }
        if (collisionResult == CollisionResult::ClashPreservedHits || collisionResult == CollisionResult::Grazed) {
            remainingHits = 1;
            collisionResult = CollisionResult::None;
        }
    }
    if (animationStage == 3) {
        SetPolarVelocity(field0D8, field0DA);
        x = static_cast<int>(owner->fieldF0C + facing * velocityX);
        y = static_cast<int>(owner->fieldF0E + velocityY);
        owner->field314 = action - 828;
        if (field0DC == 0) owner->SpawnBattleEffect(841, owner->facing * 20 + x, y, owner->facing, 1);
        if (field0DC > 120 || collisionResult == CollisionResult::ClashConsumedHit || (collisionResult != CollisionResult::None && collisionResult != CollisionResult::ClashConsumedHit && collisionResult != CollisionResult::ClashPreservedHits && collisionResult != CollisionResult::Grazed)) {
            ResetSecondaryCounter(7);
            field0DC = 0;
            return;
        }
        ++field0DC;
        field0E0 = 1;
    }
    if (animationStage == 4) {
        if (field0DC == 1) owner->SpawnBattleEffect(841, owner->facing * 20 + x, y, owner->facing, 1);
        if (field0DC > 120 || collisionResult == CollisionResult::ClashConsumedHit || (collisionResult != CollisionResult::None && collisionResult != CollisionResult::ClashConsumedHit && collisionResult != CollisionResult::ClashPreservedHits && collisionResult != CollisionResult::Grazed)) { ResetSecondaryCounter(7); return; }
        ++field0DC;
    }
    if (animationStage == 7) color[0] = color[0] - 25;
    if (static_cast<MarisaFighter*>(owner)->fieldF12 == 6) owner->SpawnBattleEffect(843, x, y, 1, 1);
    if (AdvanceNestedFrame() == animationStageCount) {
        ClearFrameInfo();
        if (field0DC == 0) --static_cast<MarisaFighter*>(owner)->fieldF14;
        if (field0E0 == 0) --static_cast<MarisaFighter*>(owner)->fieldF16;
    } else {
        if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        if (animationStage == 4 && animationFrame == 0) ResetSecondaryCounter(3);
        if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(4);
        if (animationStage == 6 && animationFrame == 0) ResetSecondaryCounter(5);
        if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
    }
}

#undef OWNER
#undef FIELD

#undef OTHER_FLOAT
#undef OWNER_FLOAT

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define OPPONENT_GUARD static_cast<Fighter*>(opponent)->IsState50To149()

// Independent two-component local value. Both stores are present in the target;
// the vertical component is computed but not subsequently read by this policy.
struct AISeparation507B20 { float x, y; };

void PatchouliFighter::ChooseAction()
{
    AISeparation507B20 distance;
    distance.x = AbsFloatAt00412D90(opponent->x - x);
    distance.y = opponent->y - y;
    if (rand() < 50) inputY = -1;
    if (distance.x > 120.0f && rand() < 200) {
        inputX = facing;
        inputY = -1;
        return;
    }
    if (distance.x > 120.0f && y > 0.0f && rand() < 500) {
        aiCommand = 1;
        return;
    }
    if (distance.x > 120.0f && y == 0.0f && rand() < 200) {
        aiCommand = 1;
        return;
    }
    if (distance.x < 120.0f && rand() < 200) {
        aiCommand = 2;
        return;
    }
    if (spellTimer == 0) {
        if (health < 2400 && spellPower > 100.0f && rand() < 200) {
            aiCommand = 113;
            return;
        }
        if (distance.x > 100.0f && spellPower > 100.0f && rand() < 10) {
            aiCommand = 103;
            return;
        }
        if (distance.x > 100.0f && spellPower > 200.0f && rand() < 20) {
            aiCommand = 103;
            return;
        }
        if (distance.x > 100.0f && spellPower > 300.0f && rand() < 100) {
            aiCommand = 103;
            return;
        }
    } else {
        if (health < 1000 && opponent->y < 100.0f && rand() < 1000) {
            aiCommand = 113;
            return;
        }
        if (health < 2400 && opponent->y < 100.0f && rand() < 100) {
            aiCommand = 113;
            return;
        }
        if (spellTimer < 500 && opponent->y < 100.0f && rand() < 200) {
            aiCommand = 113;
            return;
        }
        if (spellTimer < 1000 && opponent->y < 100.0f && rand() < 20) {
            aiCommand = 113;
            return;
        }
        if (distance.x > 60.0f && opponent->y < 100.0f && OPPONENT_GUARD) {
            if ((action == 308 || action == 309 || action == 310) && rand() < 10000) {
                aiCommand = 113;
                return;
            }
            if (action <= 10 && opponent->action != 95 && opponent->action != 97 && rand() < 400) {
                aiCommand = 113;
                return;
            }
        }
        if (distance.x > 200.0f && opponent->y < 100.0f && rand() < 40) {
            aiCommand = 113;
            return;
        }
        if (distance.x > 60.0f && opponent->y == 0.0f && rand() < 10) {
            aiCommand = 113;
            return;
        }
    }
    if (OPPONENT_GUARD) {
        if (action == 307 && rand() < 6000) {
            aiCommand = 21;
            return;
        }
        if (action == 307 && rand() < 5000) {
            aiCommand = 20;
            return;
        }
        if (distance.x < 140.0f && (action == 301 || action == 308) && rand() < 20000) {
            aiCommand = 31;
            return;
        }
        if (action == 300 && rand() < 20000) {
            inputB = 1;
            return;
        }
        if (distance.x < 140.0f && action == 303 && rand() < 20000) {
            inputB = 1;
            inputX = facing;
            return;
        }
        if (distance.x < 60.0f && rand() < 10000) {
            inputA = 1;
            return;
        }
    }
    if (distance.x < 140.0f && opponent->velocityY > 0.0f &&
        (opponent->action == 500 || opponent->action == 501)) {
        inputX = -facing;
        return;
    }
    if (distance.x < 200.0f && opponent->y > 0.0f && opponent->action == 307) {
        inputX = -facing;
        return;
    }
    if (distance.x < 60.0f && rand() < 6000) {
        inputA = 1;
        inputY = (rand() > 20000);
        if (opponent->y > 0.0f) inputY = 0;
        return;
    }
    if (distance.x < 60.0f && rand() < 10000) {
        inputB = 1;
        inputY = 1;
        return;
    }
    if (distance.x < 60.0f && rand() < 10000) {
        inputB = 1;
        inputY = (rand() > 20000);
        if (opponent->y > 0.0f) inputY = 0;
        return;
    }
    if (distance.x > 300.0f && distance.x < 500.0f && rand() < 30) {
        aiCommand = 12;
        return;
    }
    if (distance.x < 100.0f && rand() < 30) {
        aiCommand = 102;
        return;
    }
    if (distance.x < 120.0f && opponent->y == 0.0f && rand() < 300) {
        inputB = 1;
        inputX = facing;
        return;
    }
    if (distance.x > 60.0f && distance.x < 160.0f && opponent->y == 0.0f && rand() < 300) {
        aiCommand = 100;
        return;
    }
    if (distance.x > 60.0f && distance.x < 160.0f && opponent->y == 0.0f && rand() < 200) {
        aiCommand = 101;
        return;
    }
    if (distance.x > 60.0f && distance.x < 240.0f && rand() < 400) {
        inputA = 1;
        inputX = facing;
        return;
    }
    if (distance.x > 480.0f) {
        if (rand() < 1000) { aiCommand = 20; return; }
        if (rand() < 1000) { inputC = 1; return; }
    }
    if (distance.x > 200.0f) {
        if (y == 0.0f && opponent->y > 0.0f && rand() < 200) { aiCommand = 21; return; }
        if (y > 0.0f && opponent->y == 0.0f && rand() < 200) { aiCommand = 21; return; }
        if (rand() < 200) { aiCommand = 20; return; }
        if (rand() < 200) { inputC = 1; return; }
    }
    if (opponent->y > y + 150.0f && AbsFloatAt00412D90(opponent->x - x) < 110.0f) {
        aiCommand = 30;
        return;
    }
    if (g_AI507B20Countdown > 0) {
        inputX = 1;
        --g_AI507B20Countdown;
    } else if (g_AI507B20Countdown < 0) {
        inputX = -1;
        ++g_AI507B20Countdown;
    } else {
        g_AI507B20Countdown = (rand() % 90 + 10) * (1 - (rand() % 2) * 2);
    }
}

#undef OPPONENT_GUARD
#undef FIELD
