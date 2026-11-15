#include "BattleScene.hpp"
#include <deque>
#include "GameLeafHelpers.hpp"
typedef std::deque<Actor *> ActiveActors;
typedef char CheckedDequeSize[sizeof(ActiveActors) == 20 ? 1 : -1];
typedef char CheckedIteratorSize[sizeof(ActiveActors::iterator) == 8 ? 1 : -1];
// The fighter's object manager (+0x2EC) keeps two lists of active objects from +4.
#define ACTIVE(actor, index) (reinterpret_cast<ActiveActors *>(reinterpret_cast<unsigned char *>((actor)->field2EC) + 4)[index])
void BattleScene::ResolveActiveCollisions()
{
    // cursor and end2 retain the two range ends across the inner loops.
    ActiveActors::iterator it, cursor, other, end2;
    int i, j;
    for (i = 0; i < 2; ++i) {
        fighters[i]->SaveCollisionFields();
        fighters[i]->field328 = fighters[i]->health;
        for (j = 0; j < 2; ++j) {
            it = ACTIVE(fighters[i], j).begin();
            cursor = ACTIVE(fighters[i], j).end();
            for (; it != cursor; it++)
                (*it)->SaveCollisionFields();
        }
    }
    for (i = 0; i < 2; ++i) {
        it = ACTIVE(fighters[0], i).begin();
        cursor = ACTIVE(fighters[0], i).end();
        for (; it != cursor; it++) {
            for (j = 0; j < 2; ++j) {
                other = ACTIVE(fighters[1], j).begin();
                end2 = ACTIVE(fighters[1], j).end();
                for (; other != end2; other++)
                    ResolveBodyContact(*it, *other);
            }
        }
    }
    for (i = 0; i < 2; ++i) {
        activeComboDisplay = comboDisplays[i];
        for (j = 0; j < 2; ++j) {
            it = ACTIVE(fighters[i], j).begin();
            cursor = ACTIVE(fighters[i], j).end();
            for (; it != cursor; it++) {
                (*it)->SaveCollisionFields();
                ResolveAttackHitboxes(*it, fighters[i], fighters[1-i]);
            }
        }
    }
    activeComboDisplay = comboDisplays[0];
    ResolveAttackHitboxes(fighters[0], fighters[0], fighters[1]);
    activeComboDisplay = comboDisplays[1];
    ResolveAttackHitboxes(fighters[1], fighters[1], fighters[0]);
    comboDisplays[0]->UpdateCounter(fighters[0]->comboCount, fighters[0]->comboDamage, static_cast<short>(fighters[0]->comboRate * 1000.0f));
    comboDisplays[1]->UpdateCounter(fighters[1]->comboCount, fighters[1]->comboDamage, static_cast<short>(fighters[1]->comboRate * 1000.0f));
}


bool Fighter::IsState50To149()
{
    return action >= 50 && action < 150;
}

bool BattleScene::ResolveGuard(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if (!(attack->savedFrameInfo->attackFlags & 0x40000) &&
        !defender->IsState50To149() &&
        (defender->field088 != 0 || (defender->savedFrameInfo->flags & 0x4000))) {
        attack->field07C = 6;
        --attack->field080;
        defender->field36C += 0.5f;
        if (defender->field36C > 900.0f) defender->field36C = 900.0f;
        SpawnMidpointEffect(52, attack->facing);
        g_SoundBank->Play(37);
        return true;
    }
    return false;
}

bool BattleScene::ResolveSpecialHit(Actor *attack, Fighter *attacker, Fighter *defender)
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

bool BattleScene::ResolveContact(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if ((attack->savedFrameInfo->attackFlags & 2) && (defender->savedFrameInfo->flags & 0x200)) {
        attack->field07C = 3;
        --attack->field080;
        SpawnMidpointEffect(51, defender->facing);
        ApplyImpact(attack, attacker, defender);
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 4) && (defender->savedFrameInfo->flags & 0x400)) {
        attack->field07C = 3;
        --attack->field080;
        SpawnMidpointEffect(51, defender->facing);
        ApplyImpact(attack, attacker, defender);
        return true;
    }
    return false;
}
