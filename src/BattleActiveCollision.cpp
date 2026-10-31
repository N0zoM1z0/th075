#include "FighterComboBorrowedF1006.hpp"
#include <deque>
#include "BattleActiveCollision.hpp"
#include "GameLeafHelpers.hpp"
typedef std::deque<CombatActor *> ActiveActors;
typedef char CheckedDequeSize[sizeof(ActiveActors) == 20 ? 1 : -1];
typedef char CheckedIteratorSize[sizeof(ActiveActors::iterator) == 8 ? 1 : -1];
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define ACTOR(index) (reinterpret_cast<CombatActor **>(reinterpret_cast<unsigned char *>(this) + 0x44)[index])
#define DISPLAY(index) (reinterpret_cast<ComboDisplay **>(reinterpret_cast<unsigned char *>(this) + 0x50)[index])
#define ACTIVE(actor, index) (reinterpret_cast<ActiveActors *>(reinterpret_cast<unsigned char *>(FIELD(void *, actor, 0x2EC)) + 4)[index])
void BattleActiveCollision::ResolveActiveCollisions()
{
    // cursor and end2 retain the two range ends across the inner loops.
    ActiveActors::iterator it, cursor, other, end2;
    int i, j;
    for (i = 0; i < 2; ++i) {
        reinterpret_cast<CollisionActor *>(ACTOR(i))->SaveCollisionFields();
        FIELD(short, ACTOR(i), 0x328) = FIELD(short, ACTOR(i), 0x324);
        for (j = 0; j < 2; ++j) {
            it = ACTIVE(ACTOR(i), j).begin();
            cursor = ACTIVE(ACTOR(i), j).end();
            for (; it != cursor; it++)
                reinterpret_cast<CollisionActor *>(*it)->SaveCollisionFields();
        }
    }
    for (i = 0; i < 2; ++i) {
        it = ACTIVE(ACTOR(0), i).begin();
        cursor = ACTIVE(ACTOR(0), i).end();
        for (; it != cursor; it++) {
            for (j = 0; j < 2; ++j) {
                other = ACTIVE(ACTOR(1), j).begin();
                end2 = ACTIVE(ACTOR(1), j).end();
                for (; other != end2; other++)
                    reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveBodyContact(*it, *other);
            }
        }
    }
    for (i = 0; i < 2; ++i) {
        FIELD(ComboDisplay *, this, 0x58) = DISPLAY(i);
        for (j = 0; j < 2; ++j) {
            it = ACTIVE(ACTOR(i), j).begin();
            cursor = ACTIVE(ACTOR(i), j).end();
            for (; it != cursor; it++) {
                reinterpret_cast<CollisionActor *>(*it)->SaveCollisionFields();
                reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveAttackHitboxes(*it, ACTOR(i), ACTOR(1-i));
            }
        }
    }
    FIELD(ComboDisplay *, this, 0x58) = DISPLAY(0);
    reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveAttackHitboxes(ACTOR(0), ACTOR(0), ACTOR(1));
    FIELD(ComboDisplay *, this, 0x58) = DISPLAY(1);
    reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveAttackHitboxes(ACTOR(1), ACTOR(1), ACTOR(0));
    DISPLAY(0)->UpdateCounter(F1006_COMBO(ACTOR(0)).countAt3C4, F1006_COMBO(ACTOR(0)).damageAt3C6, static_cast<short>(FIELD(float, ACTOR(0), 0x3C0) * 1000.0f));
    DISPLAY(1)->UpdateCounter(F1006_COMBO(ACTOR(1)).countAt3C4, F1006_COMBO(ACTOR(1)).damageAt3C6, static_cast<short>(FIELD(float, ACTOR(1), 0x3C0) * 1000.0f));
}

#define FRAME(type, actor, offset) FIELD(type, FIELD(void *, actor, 0xAC), offset)

bool FighterState::IsState50To149()
{
    return FIELD(short, this, 0x60) >= 50 && FIELD(short, this, 0x60) < 150;
}

bool BattleCollisionDispatch::ResolveGuard(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if (!(FRAME(unsigned long, attack, 0x40) & 0x40000) &&
        !reinterpret_cast<FighterState *>(defender)->IsState50To149() &&
        (FIELD(short, defender, 0x88) != 0 || (FRAME(unsigned long, defender, 0x3C) & 0x4000))) {
        FIELD(int, attack, 0x7C) = 6;
        --FIELD(short, attack, 0x80);
        FIELD(float, defender, 0x36C) += 0.5f;
        if (FIELD(float, defender, 0x36C) > 900.0f) FIELD(float, defender, 0x36C) = 900.0f;
        reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(52, FIELD(unsigned char, attack, 0x66));
        g_SoundBank->Play(37);
        return true;
    }
    return false;
}

bool BattleCollisionDispatch::ResolveSpecialHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if ((FRAME(unsigned long, attack, 0x40) & 0x2000) && (FRAME(unsigned long, defender, 0x3C) & 0x8000)) {
        FIELD(int, attack, 0x7C) = 3;
        --FIELD(short, attack, 0x80);
        FIELD(int, defender, 0x7C) = 3;
        return true;
    }
    if ((FRAME(unsigned long, attack, 0x40) & 0x4000) && (FRAME(unsigned long, defender, 0x3C) & 0x10000)) {
        FIELD(int, attack, 0x7C) = 3;
        --FIELD(short, attack, 0x80);
        FIELD(int, defender, 0x7C) = 3;
        return true;
    }
    if ((FRAME(unsigned long, attack, 0x40) & 0x8000) && (FRAME(unsigned long, defender, 0x3C) & 0x20000)) {
        FIELD(int, attack, 0x7C) = 3;
        --FIELD(short, attack, 0x80);
        FIELD(int, defender, 0x7C) = 3;
        return true;
    }
    return false;
}

bool BattleCollisionDispatch::ResolveContact(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if ((FRAME(unsigned long, attack, 0x40) & 2) && (FRAME(unsigned long, defender, 0x3C) & 0x200)) {
        FIELD(int, attack, 0x7C) = 3;
        --FIELD(short, attack, 0x80);
        reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, FIELD(unsigned char, defender, 0x66));
        reinterpret_cast<BattleCombatResponses *>(this)->ApplyImpact(attack, attacker, defender);
        return true;
    }
    if ((FRAME(unsigned long, attack, 0x40) & 4) && (FRAME(unsigned long, defender, 0x3C) & 0x400)) {
        FIELD(int, attack, 0x7C) = 3;
        --FIELD(short, attack, 0x80);
        reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, FIELD(unsigned char, defender, 0x66));
        reinterpret_cast<BattleCombatResponses *>(this)->ApplyImpact(attack, attacker, defender);
        return true;
    }
    return false;
}
