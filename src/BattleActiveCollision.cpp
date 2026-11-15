#include "ActiveCollisionPairsF1063.hpp"
#include <deque>
#include "BattleActiveCollision.hpp"
#include "GameLeafHelpers.hpp"
typedef std::deque<Actor *> ActiveActors;
typedef char CheckedDequeSize[sizeof(ActiveActors) == 20 ? 1 : -1];
typedef char CheckedIteratorSize[sizeof(ActiveActors::iterator) == 8 ? 1 : -1];
#define FIELD_AT(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define ACTOR(index) (F1063_ACTORS(this).actors[index])
#define DISPLAY(index) (F1063_DISPLAYS(this).displays[index])
#define ACTIVE(actor, index) (reinterpret_cast<ActiveActors *>(reinterpret_cast<unsigned char *>(FIELD_AT(void *, actor, 0x2EC)) + 4)[index])
void BattleActiveCollision::ResolveActiveCollisions()
{
    // cursor and end2 retain the two range ends across the inner loops.
    ActiveActors::iterator it, cursor, other, end2;
    int i, j;
    for (i = 0; i < 2; ++i) {
        ACTOR(i)->SaveCollisionFields();
        ACTOR(i)->field328 = ACTOR(i)->health;
        for (j = 0; j < 2; ++j) {
            it = ACTIVE(ACTOR(i), j).begin();
            cursor = ACTIVE(ACTOR(i), j).end();
            for (; it != cursor; it++)
                (*it)->SaveCollisionFields();
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
        FIELD_AT(ComboDisplay *, this, 0x58) = DISPLAY(i);
        for (j = 0; j < 2; ++j) {
            it = ACTIVE(ACTOR(i), j).begin();
            cursor = ACTIVE(ACTOR(i), j).end();
            for (; it != cursor; it++) {
                (*it)->SaveCollisionFields();
                reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveAttackHitboxes(*it, ACTOR(i), ACTOR(1-i));
            }
        }
    }
    FIELD_AT(ComboDisplay *, this, 0x58) = DISPLAY(0);
    reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveAttackHitboxes(ACTOR(0), ACTOR(0), ACTOR(1));
    FIELD_AT(ComboDisplay *, this, 0x58) = DISPLAY(1);
    reinterpret_cast<BattleCollisionDispatch *>(this)->ResolveAttackHitboxes(ACTOR(1), ACTOR(1), ACTOR(0));
    DISPLAY(0)->UpdateCounter(ACTOR(0)->comboCount, ACTOR(0)->comboDamage, static_cast<short>(ACTOR(0)->comboRate * 1000.0f));
    DISPLAY(1)->UpdateCounter(ACTOR(1)->comboCount, ACTOR(1)->comboDamage, static_cast<short>(ACTOR(1)->comboRate * 1000.0f));
}


bool Fighter::IsState50To149()
{
    return action >= 50 && action < 150;
}

bool BattleCollisionDispatch::ResolveGuard(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if (!(attack->savedFrameInfo->attackFlags & 0x40000) &&
        !defender->IsState50To149() &&
        (defender->field088 != 0 || (defender->savedFrameInfo->flags & 0x4000))) {
        attack->field07C = 6;
        --attack->field080;
        defender->field36C += 0.5f;
        if (defender->field36C > 900.0f) defender->field36C = 900.0f;
        reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(52, attack->facing);
        g_SoundBank->Play(37);
        return true;
    }
    return false;
}

bool BattleCollisionDispatch::ResolveSpecialHit(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if ((attack->savedFrameInfo->attackFlags & 0x2000) && (defender->savedFrameInfo->flags & 0x8000)) {
        attack->field07C = 3;
        --attack->field080;
        defender->field07C = 3;
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 0x4000) && (defender->savedFrameInfo->flags & 0x10000)) {
        attack->field07C = 3;
        --attack->field080;
        defender->field07C = 3;
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 0x8000) && (defender->savedFrameInfo->flags & 0x20000)) {
        attack->field07C = 3;
        --attack->field080;
        defender->field07C = 3;
        return true;
    }
    return false;
}

bool BattleCollisionDispatch::ResolveContact(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if ((attack->savedFrameInfo->attackFlags & 2) && (defender->savedFrameInfo->flags & 0x200)) {
        attack->field07C = 3;
        --attack->field080;
        reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, defender->facing);
        reinterpret_cast<BattleCombatResponses *>(this)->ApplyImpact(attack, attacker, defender);
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 4) && (defender->savedFrameInfo->flags & 0x400)) {
        attack->field07C = 3;
        --attack->field080;
        reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, defender->facing);
        reinterpret_cast<BattleCombatResponses *>(this)->ApplyImpact(attack, attacker, defender);
        return true;
    }
    return false;
}
