#include "BattleCollisionDispatch.hpp"
#include "GameLeafHelpers.hpp"

// Observed scalar views, without complete owner layouts.
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define RECORD(type, actor, pointer, offset) FIELD(type, FIELD(void *, actor, pointer), offset)
#define FRAME(type, actor, offset) RECORD(type, actor, 0xAC, offset)
#define SEQUENCE(actor, frame, offset) (*reinterpret_cast<CollisionRectSequence *>(reinterpret_cast<unsigned char *>(FIELD(void *, actor, frame)) + offset))
void BattleCollisionDispatch::ResolveAttackHitboxes(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if (FIELD(int, attack, 0xA8) != 0 || FIELD(short, attack, 0x80) <= 0) return;
    if (reinterpret_cast<FighterState *>(defender)->IsGroundedStateWindow()) return;
    if (!(FRAME(unsigned long, attack, 0x40) & 0x400000)) {
        if (FIELD(short, defender, 0x84) != 0) return;
        if (FRAME(unsigned long, defender, 0x3C) & 0x2000) return;
    }
    if ((FRAME(unsigned long, attack, 0x40) & 0x80) > 0) {
        if (FIELD(short, defender, 0x86) > 0) return;
        if (FRAME(unsigned long, defender, 0x3C) & 0x800) return;
        if (FRAME(unsigned long, defender, 0x3C) & 0x1000) return;
    }
    RECT bodyRectangle;
    RECT attackBounds[4];
    RECT defendBounds[5];
    unsigned int hit = 0;
    signed char attackSize, defenderCount;
    int i;
    int contacts[4][5];
    attackSize = static_cast<signed char>(SEQUENCE(attack, 0xAC, 0x64).Size());
    defenderCount = static_cast<signed char>(SEQUENCE(defender, 0xAC, 0x54).Size());
    for (i = 0; i < attackSize; ++i)
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&attackBounds[i], &SEQUENCE(attack, 0xAC, 0x64).At(i), attack);
    for (i = 0; i < defenderCount; ++i)
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&defendBounds[i], &SEQUENCE(defender, 0xAC, 0x54).At(i), defender);
    reinterpret_cast<BattleCollision *>(this)->TransformBounds(&bodyRectangle, &FRAME(RECT, defender, 0x44), defender);
    reinterpret_cast<BattleCollision *>(this)->ClearBounds();
    for (i = 0; i < attackSize; ++i) {
        for (int j = 0; j < defenderCount; ++j) {
            contacts[i][j] = reinterpret_cast<BattleCollision *>(this)->TestOverlap(&attackBounds[i], &defendBounds[j]);
            if (contacts[i][j]) {
                hit |= 1;
                reinterpret_cast<BattleCollision *>(this)->IncludePair(&attackBounds[i], &defendBounds[j]);
            }
        }
    }
    if (hit) {
        FIELD(signed char, defender, 0x3BE) = !(FRAME(unsigned long, attack, 0x40) & 0x400000);
        if (ResolveSpecialHit(attack, attacker, defender)) return;
        if (reinterpret_cast<BattleCombat *>(this)->ApplyConditionalHit(attack, attacker, defender)) return;
        if (ResolveContact(attack, attacker, defender)) return;
        if (FIELD(signed char, defender, 0x3BE) == 0)
            if (ResolveGuard(attack, attacker, defender)) return;
        if (reinterpret_cast<BattleCombatResponses *>(this)->ApplyHitResponse(attack, attacker, defender)) return;
        if (reinterpret_cast<BattleCombatResponses *>(this)->ApplyAttackHit(attack, attacker, defender)) return;
        reinterpret_cast<BattleCombat *>(this)->ApplyHit(attack, attacker, defender);
    }
}

void BattleCollisionDispatch::ResolveBodyContact(CombatActor *first, CombatActor *second)
{
    if (FIELD(int, first, 0xA8) != 0 || FIELD(short, first, 0x80) <= 0) return;
    if (FIELD(int, second, 0xA8) != 0 || FIELD(short, second, 0x80) <= 0) return;
    if (RECORD(short, first, 0xB0, 0x10) == 0) return;
    if (RECORD(short, second, 0xB0, 0x10) == 0) return;
    int i;
    unsigned int hit = 0;
    signed char countA = static_cast<signed char>(SEQUENCE(first, 0x74, 0x64).Size());
    signed char countB = static_cast<signed char>(SEQUENCE(second, 0x74, 0x64).Size());
    RECT attackBounds[6], defendBounds[6];
    for (i = 0; i < countA; ++i)
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&attackBounds[i], &SEQUENCE(first, 0x74, 0x64).At(i), first);
    for (i = 0; i < countB; ++i)
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&defendBounds[i], &SEQUENCE(second, 0x74, 0x64).At(i), second);
    reinterpret_cast<BattleCollision *>(this)->TransformBounds(&attackBounds[countA], &RECORD(RECT, first, 0x74, 0x44), first);
    reinterpret_cast<BattleCollision *>(this)->TransformBounds(&defendBounds[countB], &RECORD(RECT, second, 0x74, 0x44), second);
    reinterpret_cast<BattleCollision *>(this)->ClearBounds();
    for (i = 0; i <= countA; ++i) {
        for (int j = 0; j <= countB; ++j) {
            if (reinterpret_cast<BattleCollision *>(this)->TestOverlap(&attackBounds[i], &defendBounds[j])) {
                hit |= 1;
                reinterpret_cast<BattleCollision *>(this)->IncludePair(&attackBounds[i], &defendBounds[j]);
            }
        }
    }
    if (hit) {
        FIELD(float, second, 0x8C) = (FIELD(int, this, 0x34) + FIELD(int, this, 0x3C)) / 2.0f;
        FIELD(unsigned long, first, 0x8C) = FIELD(unsigned long, second, 0x8C);
        FIELD(float, second, 0x90) = (FIELD(int, this, 0x38) + FIELD(int, this, 0x40)) / 2.0f;
        FIELD(unsigned long, first, 0x90) = FIELD(unsigned long, second, 0x90);
        if (RECORD(short, first, 0x78, 0x12) >= RECORD(short, second, 0x78, 0x10) ||
            RECORD(short, second, 0x78, 0x12) >= RECORD(short, first, 0x78, 0x10)) {
            FIELD(int, first, 0x7C) = 5;
            FIELD(int, second, 0x7C) = 5;
        } else {
            if (RECORD(short, first, 0x78, 0x10) <= RECORD(short, second, 0x78, 0x10)) {
                FIELD(int, first, 0x7C) = 4;
                --FIELD(short, first, 0x80);
            }
            if (RECORD(short, first, 0x78, 0x10) >= RECORD(short, second, 0x78, 0x10)) {
                FIELD(int, second, 0x7C) = 4;
                --FIELD(short, second, 0x80);
            }
        }
    }
}

void CollisionActor::SaveCollisionFields()
{
    FIELD(unsigned long, this, 0xA8) = FIELD(unsigned long, this, 0x7C);
    FIELD(unsigned long, this, 0xAC) = FIELD(unsigned long, this, 0x74);
    FIELD(unsigned long, this, 0xB0) = FIELD(unsigned long, this, 0x78);
    FIELD(unsigned long, this, 0xB8) = FIELD(unsigned long, this, 0x44);
    FIELD(unsigned long, this, 0xBC) = FIELD(unsigned long, this, 0x48);
    FIELD(unsigned char, this, 0xC0) = FIELD(unsigned char, this, 0x66);
    FIELD(short, this, 0xB4) = FIELD(short, this, 0x60);
}
