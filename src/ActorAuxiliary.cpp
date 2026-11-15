#include "PatchouliFighter.hpp"
#include "Fighter.hpp"
#include "CharacterObject.hpp"
#include "FighterAnimationPhaseBorrowedF1024.hpp"
#include "CharacterAuxAction.hpp"
#include "CharacterAIPolicy.hpp"

class AuxiliaryActor4A80F0 : public CharacterObject {
public:
    void Update();
};
class EffectEmitterF120 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer);
};
extern int g_AI507B20Countdown;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(owner) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(owner) + (offset))
#define OTHER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define SPAWN(id, x, y, f, l) reinterpret_cast<EffectEmitterF120*>(owner)->Spawn(id, x, y, f, l)

void AuxiliaryActor4A80F0::Update()
{
    if (animationStage == 0 && animationFrame == 0) {
        field0D8 = 0;
        field0DA = 0;
        field0DC = 0;
        field0DE = 0;
        field0E0 = 0;
        ResetTransform(0.0f, 0.0f, 0.0f);
        field080 = 1;
        field07C = 0;
        scaleX = 1.0f;
        scaleY = 1.0f;
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        color[3] = 255;
    }
    if (action == 828) {
        OWNER(short, 0xF1A) = static_cast<short>(x);
        OWNER(short, 0xF26) = static_cast<short>(y);
    }
    if (action == 829) {
        OWNER(short, 0xF1C) = static_cast<short>(x);
        OWNER(short, 0xF28) = static_cast<short>(y);
    }
    if (action == 830) {
        OWNER(short, 0xF1E) = static_cast<short>(x);
        OWNER(short, 0xF2A) = static_cast<short>(y);
    }
    if (action == 831) {
        OWNER(short, 0xF20) = static_cast<short>(x);
        OWNER(short, 0xF2C) = static_cast<short>(y);
    }
    if (action == 832) {
        OWNER(short, 0xF22) = static_cast<short>(x);
        OWNER(short, 0xF2E) = static_cast<short>(y);
    }
    if (action == 833) {
        OWNER(short, 0xF24) = static_cast<short>(x);
        OWNER(short, 0xF30) = static_cast<short>(y);
    }
    if ((OWNER(short, 0x60) == 709 || OWNER(short, 0x60) == 710) &&
        F1024_PHASE(owner).stageAt62 == 5 && F1024_PHASE(owner).frameAt64 == 0 &&
        field0DC == 0 && animationStage == 1 &&
        ((action == 833 && OWNER(short, 0xF16) == 6) ||
         (action == 832 && OWNER(short, 0xF16) == 5) ||
         (action == 831 && OWNER(short, 0xF16) == 4) ||
         (action == 830 && OWNER(short, 0xF16) == 3) ||
         (action == 829 && OWNER(short, 0xF16) == 2) ||
         (action == 828 && OWNER(short, 0xF16) == 1))) {
        field0DC = 1;
        field0DE = static_cast<short>(AngleAt00483300(
            OTHER_FLOAT(0x48) + 100.0f - y,
            (OTHER_FLOAT(0x44) - x) * facing) / 0.017453288659453392f);
        ResetSecondaryCounter(2);
        --OWNER(short, 0xF14);
        --OWNER(short, 0xF16);
    }
    if ((OWNER(short, 0x60) == 716 || OWNER(short, 0x60) == 717) &&
        F1024_PHASE(owner).stageAt62 == 5 && F1024_PHASE(owner).frameAt64 == 0 &&
        (animationStage == 1 || animationStage == 2) &&
        ((action == 833 && OWNER(short, 0xF16) == 6) ||
         (action == 832 && OWNER(short, 0xF16) == 5) ||
         (action == 831 && OWNER(short, 0xF16) == 4) ||
         (action == 830 && OWNER(short, 0xF16) == 3) ||
         (action == 829 && OWNER(short, 0xF16) == 2) ||
         (action == 828 && OWNER(short, 0xF16) == 1))) {
        ResetSecondaryCounter(3);
        --OWNER(short, 0xF16);
        velocityX = 0.0f;
        velocityY = 0.0f;
    }
    if (OWNER(short, 0xF12) == 2) {
        SPAWN(836, x, y, 1, 0);
    }
    if (OWNER(short, 0xF12) == 99 && animationStage < 7 && field0DC == 0) ResetSecondaryCounter(7);
    if (OWNER(short, 0xF12) == 3 && animationStage < 2) ResetSecondaryCounter(2);
    field0D8 = static_cast<short>((OWNER(short, 0xF10) - 180) + field0C8);
    if (field0D8 > 180) field0D8 -= 360;
    if (field0D8 < -180) field0D8 += 360;
    field0DA += 5;
    if (OWNER(short, 0xF12) != 6 && OWNER(signed char, 0x39D) > 1 && field0DA > 120) field0DA = 120;
    if (OWNER(signed char, 0x39D) == 1 && field0DA > 140) field0DA = 140;
    if (OWNER(short, 0xF12) == 6 && field0DA > 180) field0DA = 180;
    if (animationStage == 1) {
        SetPolarVelocity(field0D8, field0DA);
        x = static_cast<int>(OWNER(short, 0xF0C) + facing * velocityX);
        y = static_cast<int>(OWNER(short, 0xF0E) + velocityY);
        field080 = 1;
        field07C = 0;
    }
    if (animationStage == 2 && OWNER(short, 0xF12) == 3 && field0DC == 0) {
        SetPolarVelocity(field0D8, field0DA);
        x = static_cast<int>(OWNER(short, 0xF0C) + facing * velocityX);
        y = static_cast<int>(OWNER(short, 0xF0E) + velocityY);
        SPAWN(836, x, y, 1, 0);
        if (field07C != 0 && field07C != 4 && field07C != 5 && field07C != 6) { ResetSecondaryCounter(7); return; }
        if (field07C == 4 || field07C == 5 || field07C == 6) {
            field080 = 1;
            field07C = 0;
        }
    }
    if (animationStage == 2 && field0DC > 0) {
        SetPolarVelocity(field0DE, field0DC * 0.5f + 5.0f);
        ++field0DC;
        field0E0 = 1;
        x = facing * velocityX + x;
        y = y - velocityY;
        SPAWN(836, x, y, 1, 0);
        if (field07C == 4 || (field07C != 0 && field07C != 4 && field07C != 5 && field07C != 6)) { ResetSecondaryCounter(7); return; }
        if (field07C == 5 || field07C == 6) {
            field080 = 1;
            field07C = 0;
        }
    }
    if (animationStage == 3) {
        SetPolarVelocity(field0D8, field0DA);
        x = static_cast<int>(OWNER(short, 0xF0C) + facing * velocityX);
        y = static_cast<int>(OWNER(short, 0xF0E) + velocityY);
        OWNER_FLOAT(0x314) = action - 828;
        if (field0DC == 0) SPAWN(841, OWNER(signed char, 0x66) * 20 + x, y, OWNER(signed char, 0x66), 1);
        if (field0DC > 120 || field07C == 4 || (field07C != 0 && field07C != 4 && field07C != 5 && field07C != 6)) {
            ResetSecondaryCounter(7);
            field0DC = 0;
            return;
        }
        ++field0DC;
        field0E0 = 1;
    }
    if (animationStage == 4) {
        if (field0DC == 1) SPAWN(841, OWNER(signed char, 0x66) * 20 + x, y, OWNER(signed char, 0x66), 1);
        if (field0DC > 120 || field07C == 4 || (field07C != 0 && field07C != 4 && field07C != 5 && field07C != 6)) { ResetSecondaryCounter(7); return; }
        ++field0DC;
    }
    if (animationStage == 7) color[0] = color[0] - 25;
    if (OWNER(short, 0xF12) == 6) SPAWN(843, x, y, 1, 1);
    if (AdvanceNestedFrame() == field070) {
        ClearFrameInfo();
        if (field0DC == 0) --OWNER(short, 0xF14);
        if (field0E0 == 0) --OWNER(short, 0xF16);
    } else {
        if (animationStage == 2 && animationFrame == 0) ResetSecondaryCounter(1);
        if (animationStage == 3 && animationFrame == 0) ResetSecondaryCounter(2);
        if (animationStage == 4 && animationFrame == 0) ResetSecondaryCounter(3);
        if (animationStage == 5 && animationFrame == 0) ResetSecondaryCounter(4);
        if (animationStage == 6 && animationFrame == 0) ResetSecondaryCounter(5);
        if (animationStage == 7 && animationFrame == 0) ResetSecondaryCounter(6);
    }
}

#undef SPAWN
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
    if (field3A0 == 0) {
        if (health < 2400 && field36C > 100.0f && rand() < 200) {
            aiCommand = 113;
            return;
        }
        if (distance.x > 100.0f && field36C > 100.0f && rand() < 10) {
            aiCommand = 103;
            return;
        }
        if (distance.x > 100.0f && field36C > 200.0f && rand() < 20) {
            aiCommand = 103;
            return;
        }
        if (distance.x > 100.0f && field36C > 300.0f && rand() < 100) {
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
        if (field3A0 < 500 && opponent->y < 100.0f && rand() < 200) {
            aiCommand = 113;
            return;
        }
        if (field3A0 < 1000 && opponent->y < 100.0f && rand() < 20) {
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
