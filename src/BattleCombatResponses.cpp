#include "BattleScene.hpp"
#include "GameLeafHelpers.hpp"

// Typed views of independently observed fields, without guessed intervening
// storage or complete owner layouts. Names describe inferred combat roles.
#define FIELD(type, object, offset) \
    (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
// Native signed 16-bit flash bar length is at original actor+0x3C8.
// These are two independently observed adjacent native signed WORDs.

bool BattleScene::ApplyHitResponse(Actor *attack, Fighter *attacker, Fighter *defender)
{
    signed char response = reinterpret_cast<CombatResponseActor *>(defender)->ClassifyResponse(attack->savedFrameInfo->attackFlags);
    if (response > 0) {
        short damage = 0;
        switch (response) {
        case 11:
            damage = attack->savedFrameInfo->field18;
            if (defender->field3BE == 0)
                defender->spirit -= attack->savedFrameInfo->damage / 4;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 143);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 150);
            SpawnMidpointEffect(50, defender->facing);
            break;
        case 12:
            damage = attack->savedFrameInfo->field18;
            defender->spirit -= attack->savedFrameInfo->damage / 2;
            if (attack->savedFrameInfo->attackFlags & 0x80000) defender->spirit = 0;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 143);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 150);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 13:
            damage = attack->savedFrameInfo->field18 + attack->savedFrameInfo->damage / 10;
            defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 159);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 21:
            damage = attack->savedFrameInfo->field18;
            if (defender->field3BE == 0)
                defender->spirit -= attack->savedFrameInfo->damage / 4;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 144);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 154);
            SpawnMidpointEffect(50, defender->facing);
            break;
        case 22:
            damage = attack->savedFrameInfo->field18;
            defender->spirit -= attack->savedFrameInfo->damage / 2;
            if (attack->savedFrameInfo->attackFlags & 0x80000) defender->spirit = 0;
            if (defender->spirit <= 0)
                StartHitSequence(defender, 144);
            else
                defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 154);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 23:
            damage = attack->savedFrameInfo->field18 + attack->savedFrameInfo->damage / 10;
            defender->ResetPrimaryCounters(attack->savedFrameInfo->field38 + 163);
            SpawnMidpointEffect(51, defender->facing);
            break;
        case 31:
            damage = attack->savedFrameInfo->field18;
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
    if ((!(attack->savedFrameInfo->attackFlags & 0x400) || !(defender->savedFrameInfo->flags & 0x40)) &&
        (attack->savedFrameInfo->attackFlags & 0x100000) && defender->y <= 0.0f) {
    if (defender->action < 50 || defender->action >= 143) {
        attacker->comboCount = 0;
        attacker->comboDamage = 0;
        attacker->comboRate = 1.0f;
    }
    defender->ResetPrimaryCounters(140);
    defender->ClearTransformFlag();
    attack->field07C = 1;
    --attack->field080;
    attack->field082 = attack->savedFrameInfo->attackerHitStop;
    defender->field082 = attack->savedFrameInfo->defenderHitStop;
    defender->field094 = attack->savedFrameInfo->field2C;
    defender->field098 = attack->savedFrameInfo->field30;
    if (attacker->field3CE.signedAt3CE == 0)
        defender->health -= attacker->CalculateDamage(attack);
    if (defender->health <= 0) {
        if (field018 != 1)
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
    if (defender->field3A0 > 0 || defender->field39C)
        defender->recoverableHealth = defender->health;
    else
        defender->recoverableHealth -= attacker->CalculateDamage(attack) * 0.25;
    ++attacker->comboCount;
    attacker->comboDamage += attacker->CalculateDamage(attack);
    attacker->comboRate *= attack->savedFrameInfo->comboRateScale;
    activeComboDisplay->UpdateCounter(attacker->comboCount, attacker->comboDamage,
        static_cast<short>(attacker->comboRate * 1000.0f));
    attacker->cardGauge += attack->savedFrameInfo->meterGain;
    if (attacker->cardGauge > 2000.0f) attacker->cardGauge = 2000.0f;
    defender->flashGauge = attack->savedFrameInfo->field1A;
    defender->UpdateFacingFromOpponent();
    SpawnMidpointEffect(attack->savedFrameInfo->hitEffect, attack->facing);
    g_SoundBank->Play(attack->savedFrameInfo->field34);
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
    attack->field07C = 1;
    --attack->field080;
    attack->field082 = attack->savedFrameInfo->attackerHitStop;
    defender->field082 = attack->savedFrameInfo->defenderHitStop;
    defender->field094 = attack->savedFrameInfo->field2C;
    defender->field098 = attack->savedFrameInfo->field30;
    ++attacker->comboCount;
    attacker->comboDamage += attacker->CalculateDamage(attack) / 2;
    attacker->comboRate *= attack->savedFrameInfo->comboRateScale;
    activeComboDisplay->UpdateCounter(attacker->comboCount, attacker->comboDamage,
        static_cast<short>(attacker->comboRate * 1000.0f / 2.0f));
    if (attacker->field3CE.signedAt3CE == 0)
        defender->health -= attacker->CalculateDamage(attack) / 2;
    if (defender->health <= 0) defender->health = 1;
    if (defender->field3A0 > 0 || defender->field39C)
        defender->recoverableHealth = defender->health;
    attacker->cardGauge += attack->savedFrameInfo->meterGain;
    if (attacker->cardGauge > 2000.0f) attacker->cardGauge = 2000.0f;
    defender->flashGauge = attack->savedFrameInfo->field1A;
    defender->UpdateFacingFromOpponent();
    SpawnMidpointEffect(attack->savedFrameInfo->hitEffect, attack->facing);
    g_SoundBank->Play(attack->savedFrameInfo->field34);
}

void BattleScene::ApplyReactionMode(Actor *attack, Fighter *attacker, Fighter *defender)
{
    switch (defender->action) {
    case 50: case 51: case 52: case 56: case 57: case 58:
    case 62: case 63: case 64: case 70: case 84:
        defender->ResetPrimaryCounters(defender->action + 1); break;
    case 71: case 72: case 74: case 77:
        defender->field094 *= 1.25f;
        defender->field098 *= 1.25f;
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
// Four consecutive original native signed-32bit collision bounds.
// Raw borrowed array avoids proposing a guessed original owner class.
#define CombatBoundsF1072(owner) (reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(owner)+0x34))
void BattleScene::SpawnMidpointEffect(short effect, unsigned char direction)
{
    g_CombatEffects.Spawn(effect,
        (hitBounds.left + hitBounds.right) / 2.0f,
        (hitBounds.top + hitBounds.bottom) / 2.0f,
        direction, 1, 0, 0);
}

#undef CombatBoundsF1072
#undef FlashBarSpanF1072

#undef TimerWordF1072
#undef ActionWordF1072

void BattleScene::StartHitSequence(Fighter *fighter, short value)
{
    fighter->spirit = 0;
    fighter->spiritCooldown = 1000;
    fighter->ResetPrimaryCounters(value);
    fighter->ClearTransformFlag();
    SpawnMidpointEffect(0x35, fighter->facing);
    g_SoundBank->Play(0x26);
}
