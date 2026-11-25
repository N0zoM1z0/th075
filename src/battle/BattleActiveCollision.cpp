#include "battle/BattleScene.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"
#include "characters/CharacterObject.hpp"
#include "engine/GameLeafHelpers.hpp"
typedef std::deque<CharacterObject*> ActiveObjects;
void BattleScene::ResolveActiveCollisions()
{
    // cursor and end2 retain the two range ends across the inner loops.
    ActiveObjects::iterator it, cursor, other, end2;
    int i, j;
    for (i = 0; i < 2; ++i) {
        fighters[i]->SaveCollisionFields();
        fighters[i]->healthBeforeCollision = fighters[i]->health;
        for (j = 0; j < 2; ++j) {
            it = fighters[i]->ownedObjects->entries_[j].begin();
            cursor = fighters[i]->ownedObjects->entries_[j].end();
            for (; it != cursor; it++)
                (*it)->SaveCollisionFields();
        }
    }
    for (i = 0; i < 2; ++i) {
        it = fighters[0]->ownedObjects->entries_[i].begin();
        cursor = fighters[0]->ownedObjects->entries_[i].end();
        for (; it != cursor; it++) {
            for (j = 0; j < 2; ++j) {
                other = fighters[1]->ownedObjects->entries_[j].begin();
                end2 = fighters[1]->ownedObjects->entries_[j].end();
                for (; other != end2; other++)
                    ResolveBodyContact(*it, *other);
            }
        }
    }
    for (i = 0; i < 2; ++i) {
        activeComboDisplay = comboDisplays[i];
        for (j = 0; j < 2; ++j) {
            it = fighters[i]->ownedObjects->entries_[j].begin();
            cursor = fighters[i]->ownedObjects->entries_[j].end();
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
        (defender->grazeFrames != 0 || (defender->savedFrameInfo->flags & 0x4000))) {
        attack->collisionResult = CollisionResult::Grazed;
        --attack->remainingHits;
        defender->spellPower += 0.5f;
        if (defender->spellPower > 900.0f) defender->spellPower = 900.0f;
        SpawnMidpointEffect(52, attack->facing);
        g_SoundBank->Play(37);
        return true;
    }
    return false;
}

bool BattleScene::ResolveSpecialHit(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if ((attack->savedFrameInfo->attackFlags & 0x2000) && (defender->savedFrameInfo->flags & 0x8000)) {
        attack->collisionResult = CollisionResult::SpecialContact;
        --attack->remainingHits;
        defender->collisionResult = CollisionResult::SpecialContact;
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 0x4000) && (defender->savedFrameInfo->flags & 0x10000)) {
        attack->collisionResult = CollisionResult::SpecialContact;
        --attack->remainingHits;
        defender->collisionResult = CollisionResult::SpecialContact;
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 0x8000) && (defender->savedFrameInfo->flags & 0x20000)) {
        attack->collisionResult = CollisionResult::SpecialContact;
        --attack->remainingHits;
        defender->collisionResult = CollisionResult::SpecialContact;
        return true;
    }
    return false;
}

bool BattleScene::ResolveContact(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if ((attack->savedFrameInfo->attackFlags & 2) && (defender->savedFrameInfo->flags & 0x200)) {
        attack->collisionResult = CollisionResult::SpecialContact;
        --attack->remainingHits;
        SpawnMidpointEffect(51, defender->facing);
        ApplyImpact(attack, attacker, defender);
        return true;
    }
    if ((attack->savedFrameInfo->attackFlags & 4) && (defender->savedFrameInfo->flags & 0x400)) {
        attack->collisionResult = CollisionResult::SpecialContact;
        --attack->remainingHits;
        SpawnMidpointEffect(51, defender->facing);
        ApplyImpact(attack, attacker, defender);
        return true;
    }
    return false;
}
