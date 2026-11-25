#include "battle/CombatMode.hpp"
#include "engine/GameProgress.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/BattleScene.hpp"
#include "engine/GameLeafHelpers.hpp"

void BattleScene::ApplyHit(Actor *attack, Fighter *attacker, Fighter *defender)
{
    attack->field07C = 1;
    if (defender->action < 50 || defender->action >= 143) {
        attacker->comboCount = 0;
        attacker->comboDamage = 0;
        attacker->comboRate = 1.0f;
    }
    defender->ClearTransformFlag();
    if (defender->y > 0.0f || (defender->savedFrameInfo->flags & 4)) {
        if (attack->savedFrameInfo->field28)
            defender->ResetPrimaryCounters(attack->savedFrameInfo->field28);
        else
            defender->ResetPrimaryCounters(70);
    } else {
        if (attack->savedFrameInfo->field2A)
            defender->ResetPrimaryCounters(attack->savedFrameInfo->field2A);
        else if (defender->savedFrameInfo->flags & 1) {
            if (attack->savedFrameInfo->attackFlags & 1)
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 56);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 50);
        } else if (defender->savedFrameInfo->flags & 2)
            defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 62);
    }
    --attack->field080;
    attack->field082 = attack->savedFrameInfo->attackerHitStop;
    defender->field082 = attack->savedFrameInfo->defenderHitStop;
    defender->field094 = attack->savedFrameInfo->field2C;
    defender->field098 = attack->savedFrameInfo->field30;
    attacker->pendingSpellCharge += attack->savedFrameInfo->meterGain;
    if (attacker->pendingSpellCharge > 2000.0f)
        attacker->pendingSpellCharge = 2000.0f;
    defender->pendingSpellCharge += attacker->CalculateDamage(attack) * 0.5f;
    if (defender->pendingSpellCharge > 2000.0f)
        defender->pendingSpellCharge = 2000.0f;
    if ((attack->savedFrameInfo->attackFlags & 0x100) > 0)
        defender->flashGauge = 15000;
    else
        defender->flashGauge = static_cast<short>(attack->savedFrameInfo->field1A * attacker->comboRate);
    if ((attack->savedFrameInfo->attackFlags & 0x400) && (defender->savedFrameInfo->flags & 0x40)) {
        attacker->comboDamage += attacker->CalculateDamage(attack) * 1.25;
        if (attacker->field3CE.signedAt3CE == 0) {
            defender->health -= attacker->CalculateDamage(attack) * 1.25;
            if (defender->spellTimer > 0)
                defender->recoverableHealth -= attacker->CalculateDamage(attack) * 1.25;
            else
                defender->recoverableHealth -= attacker->CalculateDamage(attack) * 1.25 *
                    (0.8 - defender->spirit * 0.2 / 1000.0);
        }
        ApplyReactionMode(attack, attacker, defender);
    } else {
        attacker->comboDamage += attacker->CalculateDamage(attack);
        if (attacker->field3CE.signedAt3CE == 0) {
            defender->health -= attacker->CalculateDamage(attack);
            if (defender->spellTimer > 0)
                defender->recoverableHealth -= attacker->CalculateDamage(attack);
            else
                defender->recoverableHealth -= attacker->CalculateDamage(attack) *
                    (0.8 - defender->spirit * 0.2 / 1000.0);
        }
    }
    if (defender->health <= 0) {
        if (battlePhase != BattlePhase::Fighting)
            defender->health = 1;
        else {
            defender->health = 0;
            if (attack->savedFrameInfo->field28) {
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field28);
                defender->ClearTransformFlag();
            } else {
                defender->ResetPrimaryCounters(70);
                defender->ClearTransformFlag();
            }
        }
    }
    if (defender->spellTimer > 0 || defender->spellDeclarationExpired)
        defender->recoverableHealth = defender->health;
    ++attacker->comboCount;
    attacker->comboRate *= attack->savedFrameInfo->comboRateScale;
    activeComboDisplay->UpdateCounter(attacker->comboCount, attacker->comboDamage,
        static_cast<short>(attacker->comboRate * 1000.0f));
    defender->UpdateFacingFromOpponent();
    SpawnMidpointEffect(attack->savedFrameInfo->hitEffect, attack->facing);
    g_SoundBank->Play(attack->savedFrameInfo->field34);
    switch (attack->savedFrameInfo->field38) {
    case 0: attacker->score += 100; break;
    case 1: attacker->score += 200; break;
    case 2: attacker->score += 300; break;
    case 3: attacker->score += 500; break;
    }
    if (g_CombatMode == CombatMode::Story && attacker->playerSide == 0) {
        if (attacker->comboDamage > g_GameProgress.GetMaxComboDamage())
            g_GameProgress.SetMaxComboDamage(attacker->comboDamage);
        if (attacker->comboCount > g_GameProgress.GetMaxComboHits())
            g_GameProgress.SetMaxComboHits(attacker->comboCount);
        if (attacker->comboCount > g_MaxComboCount)
            g_MaxComboCount = attacker->comboCount;
        if (attacker->score > g_MaxCombatScore)
            g_MaxCombatScore = attacker->score;
    }
}

bool BattleScene::ApplyConditionalHit(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if (!(attack->savedFrameInfo->attackFlags & 0x20) &&
        ((defender->savedFrameInfo->flags & 0x80) ||
         ((defender->savedFrameInfo->flags & 0x100) && defender->field3CA > 0))) {
        if (defender->field3CA > 0)
            --defender->field3CA;
        if (defender->field3CC == 0) {
            attacker->comboCount = 0;
            attacker->comboDamage = 0;
            attacker->comboRate = 1.0f;
        }
        attack->field07C = 7;
        --attack->field080;
        attack->field082 = attack->savedFrameInfo->attackerHitStop;
        defender->field082 = attack->savedFrameInfo->defenderHitStop;
        defender->field094 = attack->savedFrameInfo->field2C;
        defender->field098 = attack->savedFrameInfo->field30;
        defender->field3CC = 15;
        defender->field484 = 8;
        if ((attack->savedFrameInfo->attackFlags & 0x100) > 0)
            defender->flashGauge = 30000;
        else
            defender->flashGauge = static_cast<short>(attack->savedFrameInfo->field1A * attacker->comboRate);
        if ((attack->savedFrameInfo->attackFlags & 0x400) && (defender->savedFrameInfo->flags & 0x40)) {
            attacker->comboDamage += attacker->CalculateDamage(attack) * 1.25 / 2.0;
            if (attacker->field3CE.signedAt3CE == 0) {
                defender->health -= attacker->CalculateDamage(attack) * 1.25 / 2.0;
                if (defender->spellTimer > 0)
                    defender->recoverableHealth -= attacker->CalculateDamage(attack) * 1.25 / 2.0;
                else
                    defender->recoverableHealth -= attacker->CalculateDamage(attack) * 1.25 *
                        (0.75 - defender->spirit * 0.25 / 1000.0) / 2.0;
            }
            ApplyReactionMode(attack, attacker, defender);
        } else {
            attacker->comboDamage += attacker->CalculateDamage(attack) / 2;
            if (attacker->field3CE.signedAt3CE == 0) {
                defender->health -= attacker->CalculateDamage(attack) / 2;
                if (defender->spellTimer > 0)
                    defender->recoverableHealth -= attacker->CalculateDamage(attack) / 2;
                else
                    defender->recoverableHealth -= attacker->CalculateDamage(attack) *
                        (0.75 - defender->spirit * 0.25 / 1000.0) / 2.0;
            }
        }
        if (defender->health <= 0) {
            if (battlePhase != BattlePhase::Fighting)
                defender->health = 1;
            else {
                defender->health = 0;
                if (attack->savedFrameInfo->field28) {
                    defender->ResetPrimaryCounters(attack->savedFrameInfo->field28);
                    defender->ClearTransformFlag();
                } else {
                    defender->ResetPrimaryCounters(70);
                    defender->ClearTransformFlag();
                }
            }
        }
        if (defender->spellTimer > 0 || defender->spellDeclarationExpired)
            defender->recoverableHealth = defender->health;
        ++attacker->comboCount;
        attacker->comboRate *= attack->savedFrameInfo->comboRateScale;
        activeComboDisplay->UpdateCounter(attacker->comboCount, attacker->comboDamage,
            static_cast<short>(attacker->comboRate * 1000.0f));
        attacker->pendingSpellCharge += attack->savedFrameInfo->meterGain;
        if (attacker->pendingSpellCharge > 2000.0f)
            attacker->pendingSpellCharge = 2000.0f;
        defender->pendingSpellCharge += attacker->CalculateDamage(attack) * 0.25f;
        if (defender->pendingSpellCharge > 2000.0f)
            defender->pendingSpellCharge = 2000.0f;
        SpawnMidpointEffect(attack->savedFrameInfo->hitEffect, attack->facing);
        g_SoundBank->Play(attack->savedFrameInfo->field34);
        switch (attack->savedFrameInfo->field38) {
        case 0: attacker->score += 100; break;
        case 1: attacker->score += 200; break;
        case 2: attacker->score += 300; break;
        case 3: attacker->score += 500; break;
        }
        if (g_CombatMode == CombatMode::Story && attacker->playerSide == 0) {
            if (attacker->comboDamage > g_GameProgress.GetMaxComboDamage())
                g_GameProgress.SetMaxComboDamage(attacker->comboDamage);
            if (attacker->comboCount > g_GameProgress.GetMaxComboHits())
                g_GameProgress.SetMaxComboHits(attacker->comboCount);
            if (attacker->comboCount > g_MaxComboCount)
                g_MaxComboCount = attacker->comboCount;
            if (attacker->score > g_MaxCombatScore)
                g_MaxCombatScore = attacker->score;
        }
        return true;
    } else {
        return false;
    }
}

short Fighter::CalculateDamage(Actor *attack)
{
    if (opponent->cpuControlled != 0 && g_CombatMode == CombatMode::Story) {
        return static_cast<short>(attack->savedFrameInfo->damage * attack->field09C *
            attack->field0A4 * field0A0 * comboRate *
            (opponent->healthBeforeCollision / 4.0f / opponent->healthLimits[opponent->field39D] + 0.75));
    } else {
        return static_cast<short>(attack->savedFrameInfo->damage * attack->field09C *
            attack->field0A4 * field0A0 * comboRate *
            (opponent->healthBeforeCollision / 4.0f / 10000.0f + 0.75));
    }
}

bool Fighter::UpdateFacingFromOpponent()
{
    signed char previous = facing;
    if (x <
        opponent->x) {
        facing = 1;
        return facing != previous;
    } else if (x >
        opponent->x) {
        facing = -1;
        return facing != previous;
    }
    return false;
}
