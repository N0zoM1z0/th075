#include "FighterAnimationPhaseBorrowedF1024.hpp"
#include "AnimationProgress40FA30.hpp"
#include "CharacterAuxAction.hpp"
#include "CharacterAIPolicy.hpp"
#include "ObjectMotion40FB70.hpp"
#include "SpriteTransform40FBB0.hpp"

// Pointer-only interfaces: original owner identities and complete layouts unknown.
class AuxiliaryActor4A80F0 {
public:
    void Update();
};
class EffectEmitterF120 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer);
};
class CharacterAI507B20 {
public:
    void ChooseAction();
};
extern int g_AI507B20Countdown;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FIELD_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OWNER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset)))
#define OTHER(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset)))
#define OWNER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0xE4)) + (offset))
#define OTHER_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(OWNER(void*, 0x2E8)) + (offset))
#define RESET(n) reinterpret_cast<AnimationState*>(this)->ResetSecondaryCounter(n)
#define POLAR(a, s) reinterpret_cast<ObjectMotion40FB70*>(this)->SetPolarVelocity(a, s)
#define SPAWN(id, x, y, f, l) reinterpret_cast<EffectEmitterF120*>(FIELD(void*, 0xE4))->Spawn(id, x, y, f, l)

void AuxiliaryActor4A80F0::Update()
{
    if (F1024_PHASE(this).stageAt62 == 0 && F1024_PHASE(this).frameAt64 == 0) {
        FIELD(short, 0xD8) = 0;
        FIELD(short, 0xDA) = 0;
        FIELD(short, 0xDC) = 0;
        FIELD(short, 0xDE) = 0;
        FIELD(short, 0xE0) = 0;
        reinterpret_cast<SpriteTransform40FBB0*>(this)->ResetNodeTransform(0.0f, 0.0f, 0.0f);
        FIELD(short, 0x80) = 1;
        FIELD(int, 0x7C) = 0;
        FIELD_FLOAT(0x1C) = 1.0f;
        FIELD_FLOAT(0x20) = 1.0f;
        FIELD(unsigned char, 0x11) = 255;
        FIELD(unsigned char, 0x12) = 255;
        FIELD(unsigned char, 0x13) = 255;
        FIELD(unsigned char, 0x14) = 255;
    }
    if (FIELD(short, 0x60) == 828) {
        OWNER(short, 0xF1A) = static_cast<short>(FIELD_FLOAT(0x44));
        OWNER(short, 0xF26) = static_cast<short>(FIELD_FLOAT(0x48));
    }
    if (FIELD(short, 0x60) == 829) {
        OWNER(short, 0xF1C) = static_cast<short>(FIELD_FLOAT(0x44));
        OWNER(short, 0xF28) = static_cast<short>(FIELD_FLOAT(0x48));
    }
    if (FIELD(short, 0x60) == 830) {
        OWNER(short, 0xF1E) = static_cast<short>(FIELD_FLOAT(0x44));
        OWNER(short, 0xF2A) = static_cast<short>(FIELD_FLOAT(0x48));
    }
    if (FIELD(short, 0x60) == 831) {
        OWNER(short, 0xF20) = static_cast<short>(FIELD_FLOAT(0x44));
        OWNER(short, 0xF2C) = static_cast<short>(FIELD_FLOAT(0x48));
    }
    if (FIELD(short, 0x60) == 832) {
        OWNER(short, 0xF22) = static_cast<short>(FIELD_FLOAT(0x44));
        OWNER(short, 0xF2E) = static_cast<short>(FIELD_FLOAT(0x48));
    }
    if (FIELD(short, 0x60) == 833) {
        OWNER(short, 0xF24) = static_cast<short>(FIELD_FLOAT(0x44));
        OWNER(short, 0xF30) = static_cast<short>(FIELD_FLOAT(0x48));
    }
    if ((OWNER(short, 0x60) == 709 || OWNER(short, 0x60) == 710) &&
        F1024_PHASE(FIELD(void*, 0xE4)).stageAt62 == 5 && F1024_PHASE(FIELD(void*, 0xE4)).frameAt64 == 0 &&
        FIELD(short, 0xDC) == 0 && F1024_PHASE(this).stageAt62 == 1 &&
        ((FIELD(short, 0x60) == 833 && OWNER(short, 0xF16) == 6) ||
         (FIELD(short, 0x60) == 832 && OWNER(short, 0xF16) == 5) ||
         (FIELD(short, 0x60) == 831 && OWNER(short, 0xF16) == 4) ||
         (FIELD(short, 0x60) == 830 && OWNER(short, 0xF16) == 3) ||
         (FIELD(short, 0x60) == 829 && OWNER(short, 0xF16) == 2) ||
         (FIELD(short, 0x60) == 828 && OWNER(short, 0xF16) == 1))) {
        FIELD(short, 0xDC) = 1;
        FIELD(short, 0xDE) = static_cast<short>(AngleAt00483300(
            OTHER_FLOAT(0x48) + 100.0f - FIELD_FLOAT(0x48),
            (OTHER_FLOAT(0x44) - FIELD_FLOAT(0x44)) * FIELD(signed char, 0x66)) / 0.017453288659453392f);
        RESET(2);
        --OWNER(short, 0xF14);
        --OWNER(short, 0xF16);
    }
    if ((OWNER(short, 0x60) == 716 || OWNER(short, 0x60) == 717) &&
        F1024_PHASE(FIELD(void*, 0xE4)).stageAt62 == 5 && F1024_PHASE(FIELD(void*, 0xE4)).frameAt64 == 0 &&
        (F1024_PHASE(this).stageAt62 == 1 || F1024_PHASE(this).stageAt62 == 2) &&
        ((FIELD(short, 0x60) == 833 && OWNER(short, 0xF16) == 6) ||
         (FIELD(short, 0x60) == 832 && OWNER(short, 0xF16) == 5) ||
         (FIELD(short, 0x60) == 831 && OWNER(short, 0xF16) == 4) ||
         (FIELD(short, 0x60) == 830 && OWNER(short, 0xF16) == 3) ||
         (FIELD(short, 0x60) == 829 && OWNER(short, 0xF16) == 2) ||
         (FIELD(short, 0x60) == 828 && OWNER(short, 0xF16) == 1))) {
        RESET(3);
        --OWNER(short, 0xF16);
        FIELD_FLOAT(0x50) = 0.0f;
        FIELD_FLOAT(0x54) = 0.0f;
    }
    if (OWNER(short, 0xF12) == 2) {
        SPAWN(836, FIELD_FLOAT(0x44), FIELD_FLOAT(0x48), 1, 0);
    }
    if (OWNER(short, 0xF12) == 99 && F1024_PHASE(this).stageAt62 < 7 && FIELD(short, 0xDC) == 0) RESET(7);
    if (OWNER(short, 0xF12) == 3 && F1024_PHASE(this).stageAt62 < 2) RESET(2);
    FIELD(short, 0xD8) = static_cast<short>((OWNER(short, 0xF10) - 180) + FIELD_FLOAT(0xC8));
    if (FIELD(short, 0xD8) > 180) FIELD(short, 0xD8) -= 360;
    if (FIELD(short, 0xD8) < -180) FIELD(short, 0xD8) += 360;
    FIELD(short, 0xDA) += 5;
    if (OWNER(short, 0xF12) != 6 && OWNER(signed char, 0x39D) > 1 && FIELD(short, 0xDA) > 120) FIELD(short, 0xDA) = 120;
    if (OWNER(signed char, 0x39D) == 1 && FIELD(short, 0xDA) > 140) FIELD(short, 0xDA) = 140;
    if (OWNER(short, 0xF12) == 6 && FIELD(short, 0xDA) > 180) FIELD(short, 0xDA) = 180;
    if (F1024_PHASE(this).stageAt62 == 1) {
        POLAR(FIELD(short, 0xD8), FIELD(short, 0xDA));
        FIELD_FLOAT(0x44) = static_cast<int>(OWNER(short, 0xF0C) + FIELD(signed char, 0x66) * FIELD_FLOAT(0x50));
        FIELD_FLOAT(0x48) = static_cast<int>(OWNER(short, 0xF0E) + FIELD_FLOAT(0x54));
        FIELD(short, 0x80) = 1;
        FIELD(int, 0x7C) = 0;
    }
    if (F1024_PHASE(this).stageAt62 == 2 && OWNER(short, 0xF12) == 3 && FIELD(short, 0xDC) == 0) {
        POLAR(FIELD(short, 0xD8), FIELD(short, 0xDA));
        FIELD_FLOAT(0x44) = static_cast<int>(OWNER(short, 0xF0C) + FIELD(signed char, 0x66) * FIELD_FLOAT(0x50));
        FIELD_FLOAT(0x48) = static_cast<int>(OWNER(short, 0xF0E) + FIELD_FLOAT(0x54));
        SPAWN(836, FIELD_FLOAT(0x44), FIELD_FLOAT(0x48), 1, 0);
        if (FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 4 && FIELD(int, 0x7C) != 5 && FIELD(int, 0x7C) != 6) { RESET(7); return; }
        if (FIELD(int, 0x7C) == 4 || FIELD(int, 0x7C) == 5 || FIELD(int, 0x7C) == 6) {
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
    }
    if (F1024_PHASE(this).stageAt62 == 2 && FIELD(short, 0xDC) > 0) {
        POLAR(FIELD(short, 0xDE), FIELD(short, 0xDC) * 0.5f + 5.0f);
        ++FIELD(short, 0xDC);
        FIELD(short, 0xE0) = 1;
        FIELD_FLOAT(0x44) = FIELD(signed char, 0x66) * FIELD_FLOAT(0x50) + FIELD_FLOAT(0x44);
        FIELD_FLOAT(0x48) = FIELD_FLOAT(0x48) - FIELD_FLOAT(0x54);
        SPAWN(836, FIELD_FLOAT(0x44), FIELD_FLOAT(0x48), 1, 0);
        if (FIELD(int, 0x7C) == 4 || (FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 4 && FIELD(int, 0x7C) != 5 && FIELD(int, 0x7C) != 6)) { RESET(7); return; }
        if (FIELD(int, 0x7C) == 5 || FIELD(int, 0x7C) == 6) {
            FIELD(short, 0x80) = 1;
            FIELD(int, 0x7C) = 0;
        }
    }
    if (F1024_PHASE(this).stageAt62 == 3) {
        POLAR(FIELD(short, 0xD8), FIELD(short, 0xDA));
        FIELD_FLOAT(0x44) = static_cast<int>(OWNER(short, 0xF0C) + FIELD(signed char, 0x66) * FIELD_FLOAT(0x50));
        FIELD_FLOAT(0x48) = static_cast<int>(OWNER(short, 0xF0E) + FIELD_FLOAT(0x54));
        OWNER_FLOAT(0x314) = FIELD(short, 0x60) - 828;
        if (FIELD(short, 0xDC) == 0) SPAWN(841, OWNER(signed char, 0x66) * 20 + FIELD_FLOAT(0x44), FIELD_FLOAT(0x48), OWNER(signed char, 0x66), 1);
        if (FIELD(short, 0xDC) > 120 || FIELD(int, 0x7C) == 4 || (FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 4 && FIELD(int, 0x7C) != 5 && FIELD(int, 0x7C) != 6)) {
            RESET(7);
            FIELD(short, 0xDC) = 0;
            return;
        }
        ++FIELD(short, 0xDC);
        FIELD(short, 0xE0) = 1;
    }
    if (F1024_PHASE(this).stageAt62 == 4) {
        if (FIELD(short, 0xDC) == 1) SPAWN(841, OWNER(signed char, 0x66) * 20 + FIELD_FLOAT(0x44), FIELD_FLOAT(0x48), OWNER(signed char, 0x66), 1);
        if (FIELD(short, 0xDC) > 120 || FIELD(int, 0x7C) == 4 || (FIELD(int, 0x7C) != 0 && FIELD(int, 0x7C) != 4 && FIELD(int, 0x7C) != 5 && FIELD(int, 0x7C) != 6)) { RESET(7); return; }
        ++FIELD(short, 0xDC);
    }
    if (F1024_PHASE(this).stageAt62 == 7) FIELD(unsigned char, 0x11) = FIELD(unsigned char, 0x11) - 25;
    if (OWNER(short, 0xF12) == 6) SPAWN(843, FIELD_FLOAT(0x44), FIELD_FLOAT(0x48), 1, 1);
    if (reinterpret_cast<AnimationProgress40FA30*>(this)->AdvanceNestedFrame() == FIELD(short, 0x70)) {
        reinterpret_cast<BattleEffect*>(this)->ClearField74();
        if (FIELD(short, 0xDC) == 0) --OWNER(short, 0xF14);
        if (FIELD(short, 0xE0) == 0) --OWNER(short, 0xF16);
    } else {
        if (F1024_PHASE(this).stageAt62 == 2 && F1024_PHASE(this).frameAt64 == 0) RESET(1);
        if (F1024_PHASE(this).stageAt62 == 3 && F1024_PHASE(this).frameAt64 == 0) RESET(2);
        if (F1024_PHASE(this).stageAt62 == 4 && F1024_PHASE(this).frameAt64 == 0) RESET(3);
        if (F1024_PHASE(this).stageAt62 == 5 && F1024_PHASE(this).frameAt64 == 0) RESET(4);
        if (F1024_PHASE(this).stageAt62 == 6 && F1024_PHASE(this).frameAt64 == 0) RESET(5);
        if (F1024_PHASE(this).stageAt62 == 7 && F1024_PHASE(this).frameAt64 == 0) RESET(6);
    }
}

#undef SPAWN
#undef POLAR
#undef RESET
#undef OTHER
#undef OWNER
#undef FIELD

#undef OTHER_FLOAT
#undef OWNER_FLOAT
#undef FIELD_FLOAT

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset)))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))
#define OPPONENT_GUARD reinterpret_cast<FighterState*>(FIELD(void*, 0x2E8))->IsState50To149()

// Independent two-component local value. Both stores are present in the target;
// the vertical component is computed but not subsequently read by this policy.
struct AISeparation507B20 { float x, y; };

void CharacterAI507B20::ChooseAction()
{
    AISeparation507B20 distance;
    distance.x = AbsFloatAt00412D90(OPPONENT_FLOAT(0x44) - FLOAT(0x44));
    distance.y = OPPONENT_FLOAT(0x48) - FLOAT(0x48);
    if (rand() < 50) FIELD(int, 0x4E0) = -1;
    if (distance.x > 120.0f && rand() < 200) {
        FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        FIELD(int, 0x4E0) = -1;
        return;
    }
    if (distance.x > 120.0f && FLOAT(0x48) > 0.0f && rand() < 500) {
        FIELD(unsigned char, 0x511) = 1;
        return;
    }
    if (distance.x > 120.0f && FLOAT(0x48) == 0.0f && rand() < 200) {
        FIELD(unsigned char, 0x511) = 1;
        return;
    }
    if (distance.x < 120.0f && rand() < 200) {
        FIELD(unsigned char, 0x511) = 2;
        return;
    }
    if (FIELD(short, 0x3A0) == 0) {
        if (FIELD(short, 0x324) < 2400 && FLOAT(0x36C) > 100.0f && rand() < 200) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
        if (distance.x > 100.0f && FLOAT(0x36C) > 100.0f && rand() < 10) {
            FIELD(unsigned char, 0x511) = 103;
            return;
        }
        if (distance.x > 100.0f && FLOAT(0x36C) > 200.0f && rand() < 20) {
            FIELD(unsigned char, 0x511) = 103;
            return;
        }
        if (distance.x > 100.0f && FLOAT(0x36C) > 300.0f && rand() < 100) {
            FIELD(unsigned char, 0x511) = 103;
            return;
        }
    } else {
        if (FIELD(short, 0x324) < 1000 && OPPONENT_FLOAT(0x48) < 100.0f && rand() < 1000) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
        if (FIELD(short, 0x324) < 2400 && OPPONENT_FLOAT(0x48) < 100.0f && rand() < 100) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
        if (FIELD(short, 0x3A0) < 500 && OPPONENT_FLOAT(0x48) < 100.0f && rand() < 200) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
        if (FIELD(short, 0x3A0) < 1000 && OPPONENT_FLOAT(0x48) < 100.0f && rand() < 20) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
        if (distance.x > 60.0f && OPPONENT_FLOAT(0x48) < 100.0f && OPPONENT_GUARD) {
            if ((FIELD(short, 0x60) == 308 || FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 310) && rand() < 10000) {
                FIELD(unsigned char, 0x511) = 113;
                return;
            }
            if (FIELD(short, 0x60) <= 10 && OPPONENT(short, 0x60) != 95 && OPPONENT(short, 0x60) != 97 && rand() < 400) {
                FIELD(unsigned char, 0x511) = 113;
                return;
            }
        }
        if (distance.x > 200.0f && OPPONENT_FLOAT(0x48) < 100.0f && rand() < 40) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
        if (distance.x > 60.0f && OPPONENT_FLOAT(0x48) == 0.0f && rand() < 10) {
            FIELD(unsigned char, 0x511) = 113;
            return;
        }
    }
    if (OPPONENT_GUARD) {
        if (FIELD(short, 0x60) == 307 && rand() < 6000) {
            FIELD(unsigned char, 0x511) = 21;
            return;
        }
        if (FIELD(short, 0x60) == 307 && rand() < 5000) {
            FIELD(unsigned char, 0x511) = 20;
            return;
        }
        if (distance.x < 140.0f && (FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 308) && rand() < 20000) {
            FIELD(unsigned char, 0x511) = 31;
            return;
        }
        if (FIELD(short, 0x60) == 300 && rand() < 20000) {
            FIELD(int, 0x4EC) = 1;
            return;
        }
        if (distance.x < 140.0f && FIELD(short, 0x60) == 303 && rand() < 20000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (distance.x < 60.0f && rand() < 10000) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
    }
    if (distance.x < 140.0f && OPPONENT_FLOAT(0x54) > 0.0f &&
        (OPPONENT(short, 0x60) == 500 || OPPONENT(short, 0x60) == 501)) {
        FIELD(int, 0x4DC) = -FIELD(signed char, 0x66);
        return;
    }
    if (distance.x < 200.0f && OPPONENT_FLOAT(0x48) > 0.0f && OPPONENT(short, 0x60) == 307) {
        FIELD(int, 0x4DC) = -FIELD(signed char, 0x66);
        return;
    }
    if (distance.x < 60.0f && rand() < 6000) {
        FIELD(int, 0x4E8) = 1;
        FIELD(int, 0x4E0) = (rand() > 20000);
        if (OPPONENT_FLOAT(0x48) > 0.0f) FIELD(int, 0x4E0) = 0;
        return;
    }
    if (distance.x < 60.0f && rand() < 10000) {
        FIELD(int, 0x4EC) = 1;
        FIELD(int, 0x4E0) = 1;
        return;
    }
    if (distance.x < 60.0f && rand() < 10000) {
        FIELD(int, 0x4EC) = 1;
        FIELD(int, 0x4E0) = (rand() > 20000);
        if (OPPONENT_FLOAT(0x48) > 0.0f) FIELD(int, 0x4E0) = 0;
        return;
    }
    if (distance.x > 300.0f && distance.x < 500.0f && rand() < 30) {
        FIELD(unsigned char, 0x511) = 12;
        return;
    }
    if (distance.x < 100.0f && rand() < 30) {
        FIELD(unsigned char, 0x511) = 102;
        return;
    }
    if (distance.x < 120.0f && OPPONENT_FLOAT(0x48) == 0.0f && rand() < 300) {
        FIELD(int, 0x4EC) = 1;
        FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        return;
    }
    if (distance.x > 60.0f && distance.x < 160.0f && OPPONENT_FLOAT(0x48) == 0.0f && rand() < 300) {
        FIELD(unsigned char, 0x511) = 100;
        return;
    }
    if (distance.x > 60.0f && distance.x < 160.0f && OPPONENT_FLOAT(0x48) == 0.0f && rand() < 200) {
        FIELD(unsigned char, 0x511) = 101;
        return;
    }
    if (distance.x > 60.0f && distance.x < 240.0f && rand() < 400) {
        FIELD(int, 0x4E8) = 1;
        FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        return;
    }
    if (distance.x > 480.0f) {
        if (rand() < 1000) { FIELD(unsigned char, 0x511) = 20; return; }
        if (rand() < 1000) { FIELD(int, 0x4F0) = 1; return; }
    }
    if (distance.x > 200.0f) {
        if (FLOAT(0x48) == 0.0f && OPPONENT_FLOAT(0x48) > 0.0f && rand() < 200) { FIELD(unsigned char, 0x511) = 21; return; }
        if (FLOAT(0x48) > 0.0f && OPPONENT_FLOAT(0x48) == 0.0f && rand() < 200) { FIELD(unsigned char, 0x511) = 21; return; }
        if (rand() < 200) { FIELD(unsigned char, 0x511) = 20; return; }
        if (rand() < 200) { FIELD(int, 0x4F0) = 1; return; }
    }
    if (OPPONENT_FLOAT(0x48) > FLOAT(0x48) + 150.0f && AbsFloatAt00412D90(OPPONENT_FLOAT(0x44) - FLOAT(0x44)) < 110.0f) {
        FIELD(unsigned char, 0x511) = 30;
        return;
    }
    if (g_AI507B20Countdown > 0) {
        FIELD(int, 0x4DC) = 1;
        --g_AI507B20Countdown;
    } else if (g_AI507B20Countdown < 0) {
        FIELD(int, 0x4DC) = -1;
        ++g_AI507B20Countdown;
    } else {
        g_AI507B20Countdown = (rand() % 90 + 10) * (1 - (rand() % 2) * 2);
    }
}

#undef OPPONENT_GUARD
#undef OPPONENT_FLOAT
#undef OPPONENT
#undef FLOAT
#undef FIELD
