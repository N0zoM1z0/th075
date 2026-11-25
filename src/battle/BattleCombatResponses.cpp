#include "battle/BattleScene.hpp"
#include "battle/FighterFrameFlags.hpp"
#include "battle/CombatEffects.hpp"
#include "engine/GameLeafHelpers.hpp"

bool BattleScene::ApplyHitResponse(Actor *attack, Fighter *attacker, Fighter *defender)
{
    signed char response = static_cast<signed char>(defender->SelectHitResponse(attack->savedFrameInfo->attackFlags));
    if (response > 0) {
        short damage = 0;
        switch (response) {
        case 11:
            damage = attack->savedFrameInfo->guardDamage;
            if (defender->field3BE == 0)
                defender->spirit -= attack->savedFrameInfo->damage / 4;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 143);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->reactionVariant + 150);
            SpawnMidpointEffect(50, defender->facing);
            break;
        case 12:
            damage = attack->savedFrameInfo->guardDamage;
            defender->spirit -= attack->savedFrameInfo->damage / 2;
            if (attack->savedFrameInfo->attackFlags & AttackFlags::CrushesWrongGroundGuard) defender->spirit = 0;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 143);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->reactionVariant + 150);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 13:
            damage = attack->savedFrameInfo->guardDamage + attack->savedFrameInfo->damage / 10;
            defender->ResetPrimaryCounters(attack->savedFrameInfo->reactionVariant + 159);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 21:
            damage = attack->savedFrameInfo->guardDamage;
            if (defender->field3BE == 0)
                defender->spirit -= attack->savedFrameInfo->damage / 4;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 144);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->reactionVariant + 154);
            SpawnMidpointEffect(50, defender->facing);
            break;
        case 22:
            damage = attack->savedFrameInfo->guardDamage;
            defender->spirit -= attack->savedFrameInfo->damage / 2;
            if (attack->savedFrameInfo->attackFlags & AttackFlags::CrushesWrongGroundGuard) defender->spirit = 0;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 144);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->reactionVariant + 154);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 23:
            damage = attack->savedFrameInfo->guardDamage + attack->savedFrameInfo->damage / 10;
            defender->ResetPrimaryCounters(attack->savedFrameInfo->reactionVariant + 163);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 31:
            damage = attack->savedFrameInfo->guardDamage;
            defender->spirit -= attack->savedFrameInfo->damage / 4;
            SpawnMidpointEffect(50, defender->facing);
            if (defender->spirit <= 0)
                StartHitSequence(defender, 145);
            else
                defender->ResetPrimaryCounters(158);
            break;
        case 41:
            ApplyGuardHit(attack, attacker, defender);
            return true;
        }
        if (attacker->field3CE.signedAt3CE == 0)
            defender->health -= damage * attacker->field09C * attacker->field0A0;
        ApplyImpact(attack, attacker, defender);
        return true;
    }
    return false;
}

bool BattleScene::ApplyAttackHit(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if ((!(attack->savedFrameInfo->attackFlags & AttackFlags::CanCounterHit) || !(defender->savedFrameInfo->flags & FrameFlags::CounterHitVulnerable)) &&
        (attack->savedFrameInfo->attackFlags & AttackFlags::ForcesGroundStagger) && defender->y <= 0.0f) {
    if (defender->action < 50 || defender->action >= 143) {
        attacker->comboCount = 0;
        attacker->comboDamage = 0;
        attacker->comboRate = 1.0f;
    }
    defender->ResetPrimaryCounters(140);
    defender->ClearTransformFlag();
    attack->collisionResult = CollisionResult::Hit;
    --attack->remainingHits;
    attack->hitstopFrames = attack->savedFrameInfo->attackerHitStop;
    defender->hitstopFrames = attack->savedFrameInfo->defenderHitStop;
    defender->hitReactionVelocityX = attack->savedFrameInfo->reactionVelocityX;
    defender->hitReactionVelocityY = attack->savedFrameInfo->reactionVelocityY;
    if (attacker->field3CE.signedAt3CE == 0)
        defender->health -= attacker->CalculateDamage(attack);
    if (defender->health <= 0) {
        if (battlePhase != BattlePhase::Fighting)
            defender->health = 1;
        else {
            defender->health = 0;
            if (attack->savedFrameInfo->airHitAction) {
                defender->ResetPrimaryCounters(attack->savedFrameInfo->airHitAction);
                defender->ClearTransformFlag();
            } else {
                defender->ResetPrimaryCounters(70);
                defender->ClearTransformFlag();
            }
        }
    }
    if (defender->spellTimer > 0 || defender->spellDeclarationExpired)
        defender->recoverableHealth = defender->health;
    else
        defender->recoverableHealth -= attacker->CalculateDamage(attack) * 0.25;
    ++attacker->comboCount;
    attacker->comboDamage += attacker->CalculateDamage(attack);
    attacker->comboRate *= attack->savedFrameInfo->comboRateScale;
    activeComboDisplay->UpdateCounter(attacker->comboCount, attacker->comboDamage,
        static_cast<short>(attacker->comboRate * 1000.0f));
    attacker->pendingSpellCharge += attack->savedFrameInfo->meterGain;
    if (attacker->pendingSpellCharge > 2000.0f) attacker->pendingSpellCharge = 2000.0f;
    defender->flashGauge = attack->savedFrameInfo->baseHitstun;
    defender->UpdateFacingFromOpponent();
    SpawnMidpointEffect(attack->savedFrameInfo->hitEffect, attack->facing);
    g_SoundBank->Play(attack->savedFrameInfo->hitSound);
    return true;
    }
    return false;
}

void BattleScene::ApplyGuardHit(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if (defender->action < 50 || defender->action >= 143) {
        attacker->comboCount = 0;
        attacker->comboDamage = 0;
        attacker->comboRate = 1.0f;
    }
    defender->ResetPrimaryCounters(140);
    defender->ClearTransformFlag();
    attack->collisionResult = CollisionResult::Hit;
    --attack->remainingHits;
    attack->hitstopFrames = attack->savedFrameInfo->attackerHitStop;
    defender->hitstopFrames = attack->savedFrameInfo->defenderHitStop;
    defender->hitReactionVelocityX = attack->savedFrameInfo->reactionVelocityX;
    defender->hitReactionVelocityY = attack->savedFrameInfo->reactionVelocityY;
    ++attacker->comboCount;
    attacker->comboDamage += attacker->CalculateDamage(attack) / 2;
    attacker->comboRate *= attack->savedFrameInfo->comboRateScale;
    activeComboDisplay->UpdateCounter(attacker->comboCount, attacker->comboDamage,
        static_cast<short>(attacker->comboRate * 1000.0f / 2.0f));
    if (attacker->field3CE.signedAt3CE == 0)
        defender->health -= attacker->CalculateDamage(attack) / 2;
    if (defender->health <= 0) defender->health = 1;
    if (defender->spellTimer > 0 || defender->spellDeclarationExpired)
        defender->recoverableHealth = defender->health;
    attacker->pendingSpellCharge += attack->savedFrameInfo->meterGain;
    if (attacker->pendingSpellCharge > 2000.0f) attacker->pendingSpellCharge = 2000.0f;
    defender->flashGauge = attack->savedFrameInfo->baseHitstun;
    defender->UpdateFacingFromOpponent();
    SpawnMidpointEffect(attack->savedFrameInfo->hitEffect, attack->facing);
    g_SoundBank->Play(attack->savedFrameInfo->hitSound);
}

void BattleScene::ApplyReactionMode(Actor *attack, Fighter *attacker, Fighter *defender)
{
    switch (defender->action) {
    case 50: case 51: case 52: case 56: case 57: case 58:
    case 62: case 63: case 64: case 70: case 84:
        defender->ResetPrimaryCounters(defender->action + 1); break;
    case 71: case 72: case 74: case 77:
        defender->hitReactionVelocityX *= 1.25f;
        defender->hitReactionVelocityY *= 1.25f;
        defender->flashGauge = defender->flashGauge << 1; break;
    case 73:
        defender->flashGauge = 32767;
        defender->ResetPrimaryCounters(88); break;
    case 75: case 81: case 83: case 86: case 87:
        defender->flashGauge = defender->flashGauge << 1; break;
    }
    g_SoundBank->Play(25);
    SpawnMidpointEffect(54, attack->facing);
}
void BattleScene::SpawnMidpointEffect(short effect, unsigned char direction)
{
    g_CombatEffects.Spawn(effect,
        (hitBounds.left + hitBounds.right) / 2.0f,
        (hitBounds.top + hitBounds.bottom) / 2.0f,
        direction, 1, 0, 0);
}



void BattleScene::StartHitSequence(Fighter *fighter, short value)
{
    fighter->spirit = 0;
    fighter->spiritCooldown = 1000;
    fighter->ResetPrimaryCounters(value);
    fighter->ClearTransformFlag();
    SpawnMidpointEffect(0x35, fighter->facing);
    g_SoundBank->Play(0x26);
}
