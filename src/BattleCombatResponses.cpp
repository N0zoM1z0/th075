#include "BattleCombatResponses.hpp"
#include "GameLeafHelpers.hpp"

// Typed views of independently observed fields, without guessed intervening
// storage or complete owner layouts. Names describe inferred combat roles.
#define FIELD(type, object, offset) \
    (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define FRAME(type, actor, offset) FIELD(type, FIELD(void *, actor, 0xAC), offset)
#define Health(actor) FIELD(short, actor, 0x324)
#define RecoverableHealth(actor) FIELD(short, actor, 0x326)
#define Meter(actor) FIELD(float, actor, 0x368)
#define ComboCount(actor) FIELD(short, actor, 0x3C4)
#define ComboDamage(actor) FIELD(short, actor, 0x3C6)
#define ComboRate(actor) FIELD(float, actor, 0x3C0)

bool BattleCombatResponses::ApplyHitResponse(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    signed char response = reinterpret_cast<CombatResponseActor *>(defender)->ClassifyResponse(FRAME(unsigned long, attack, 0x40));
    if (response > 0) {
        short damage = 0;
        switch (response) {
        case 11:
            damage = FRAME(short, attack, 0x18);
            if (FIELD(signed char, defender, 0x3BE) == 0)
                FIELD(short, defender, 0x3B0) -= FRAME(short, attack, 0x10) / 4;
            if (FIELD(short, defender, 0x3B0) <= 0)
                reinterpret_cast<BattleState *>(this)->StartHitSequence(reinterpret_cast<AnimationState *>(defender), 143);
            else
                defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 150);
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(50, FIELD(unsigned char, defender, 0x66));
            break;
        case 12:
            damage = FRAME(short, attack, 0x18);
            FIELD(short, defender, 0x3B0) -= FRAME(short, attack, 0x10) / 2;
            if (FRAME(unsigned long, attack, 0x40) & 0x80000) FIELD(short, defender, 0x3B0) = 0;
            if (FIELD(short, defender, 0x3B0) <= 0)
                reinterpret_cast<BattleState *>(this)->StartHitSequence(reinterpret_cast<AnimationState *>(defender), 143);
            else
                defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 150);
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, FIELD(unsigned char, defender, 0x66));
            break;
        case 13:
            damage = FRAME(short, attack, 0x18) + FRAME(short, attack, 0x10) / 10;
            defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 159);
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, FIELD(unsigned char, defender, 0x66));
            break;
        case 21:
            damage = FRAME(short, attack, 0x18);
            if (FIELD(signed char, defender, 0x3BE) == 0)
                FIELD(short, defender, 0x3B0) -= FRAME(short, attack, 0x10) / 4;
            if (FIELD(short, defender, 0x3B0) <= 0)
                reinterpret_cast<BattleState *>(this)->StartHitSequence(reinterpret_cast<AnimationState *>(defender), 144);
            else
                defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 154);
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(50, FIELD(unsigned char, defender, 0x66));
            break;
        case 22:
            damage = FRAME(short, attack, 0x18);
            FIELD(short, defender, 0x3B0) -= FRAME(short, attack, 0x10) / 2;
            if (FRAME(unsigned long, attack, 0x40) & 0x80000) FIELD(short, defender, 0x3B0) = 0;
            if (FIELD(short, defender, 0x3B0) <= 0)
                reinterpret_cast<BattleState *>(this)->StartHitSequence(reinterpret_cast<AnimationState *>(defender), 144);
            else
                defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 154);
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, FIELD(unsigned char, defender, 0x66));
            break;
        case 23:
            damage = FRAME(short, attack, 0x18) + FRAME(short, attack, 0x10) / 10;
            defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 163);
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(51, FIELD(unsigned char, defender, 0x66));
            break;
        case 31:
            damage = FRAME(short, attack, 0x18);
            FIELD(short, defender, 0x3B0) -= FRAME(short, attack, 0x10) / 4;
            reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(50, FIELD(unsigned char, defender, 0x66));
            if (FIELD(short, defender, 0x3B0) <= 0)
                reinterpret_cast<BattleState *>(this)->StartHitSequence(reinterpret_cast<AnimationState *>(defender), 145);
            else
                defender->ResetPrimaryCounters(158);
            break;
        case 41:
            ApplyGuardHit(attack, attacker, defender);
            return true;
        }
        if (FIELD(signed char, attacker, 0x3CE) == 0)
            Health(defender) -= damage * FIELD(float, attacker, 0x9C) * FIELD(float, attacker, 0xA0);
        ApplyImpact(attack, attacker, defender);
        return true;
    }
    return false;
}

bool BattleCombatResponses::ApplyAttackHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if ((!(FRAME(unsigned long, attack, 0x40) & 0x400) || !(FRAME(unsigned long, defender, 0x3C) & 0x40)) &&
        (FRAME(unsigned long, attack, 0x40) & 0x100000) && FIELD(float, defender, 0x48) <= 0.0f) {
    if (FIELD(short, defender, 0x60) < 50 || FIELD(short, defender, 0x60) >= 143) {
        ComboCount(attacker) = 0;
        ComboDamage(attacker) = 0;
        ComboRate(attacker) = 1.0f;
    }
    defender->ResetPrimaryCounters(140);
    defender->ClearByte40();
    FIELD(int, attack, 0x7C) = 1;
    --FIELD(short, attack, 0x80);
    FIELD(short, attack, 0x82) = FRAME(short, attack, 0x1C);
    FIELD(short, defender, 0x82) = FRAME(short, attack, 0x1E);
    FIELD(unsigned long, defender, 0x94) = FRAME(unsigned long, attack, 0x2C);
    FIELD(unsigned long, defender, 0x98) = FRAME(unsigned long, attack, 0x30);
    if (FIELD(signed char, attacker, 0x3CE) == 0)
        Health(defender) -= attacker->CalculateDamage(attack);
    if (Health(defender) <= 0) {
        if (FIELD(signed char, this, 0x18) != 1)
            Health(defender) = 1;
        else {
            Health(defender) = 0;
            if (FRAME(short, attack, 0x28)) {
                defender->ResetPrimaryCounters(FRAME(short, attack, 0x28));
                defender->ClearByte40();
            } else {
                defender->ResetPrimaryCounters(70);
                defender->ClearByte40();
            }
        }
    }
    if (FIELD(short, defender, 0x3A0) > 0 || FIELD(unsigned char, defender, 0x39C))
        RecoverableHealth(defender) = Health(defender);
    else
        RecoverableHealth(defender) -= attacker->CalculateDamage(attack) * 0.25;
    ++ComboCount(attacker);
    ComboDamage(attacker) += attacker->CalculateDamage(attack);
    *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(attacker) + 0x3C0) *=
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(
            *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(attack) + 0xAC)) + 0x14);
    FIELD(ComboDisplay *, this, 0x58)->UpdateCounter(ComboCount(attacker), ComboDamage(attacker),
        static_cast<short>(ComboRate(attacker) * 1000.0f));
    Meter(attacker) += FRAME(short, attack, 0x24);
    if (Meter(attacker) > 2000.0f) Meter(attacker) = 2000.0f;
    FIELD(short, defender, 0x3C8) = FRAME(short, attack, 0x1A);
    defender->UpdateFacingFromOpponent();
    reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(FRAME(short, attack, 0x36), FIELD(unsigned char, attack, 0x66));
    g_SoundBank->Play(FRAME(short, attack, 0x34));
    return true;
    }
    return false;
}

void BattleCombatResponses::ApplyGuardHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if (FIELD(short, defender, 0x60) < 50 || FIELD(short, defender, 0x60) >= 143) {
        ComboCount(attacker) = 0;
        ComboDamage(attacker) = 0;
        ComboRate(attacker) = 1.0f;
    }
    defender->ResetPrimaryCounters(140);
    defender->ClearByte40();
    FIELD(int, attack, 0x7C) = 1;
    --FIELD(short, attack, 0x80);
    FIELD(short, attack, 0x82) = FRAME(short, attack, 0x1C);
    FIELD(short, defender, 0x82) = FRAME(short, attack, 0x1E);
    FIELD(unsigned long, defender, 0x94) = FRAME(unsigned long, attack, 0x2C);
    FIELD(unsigned long, defender, 0x98) = FRAME(unsigned long, attack, 0x30);
    ++ComboCount(attacker);
    ComboDamage(attacker) += attacker->CalculateDamage(attack) / 2;
    *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(attacker) + 0x3C0) *=
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(
            *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(attack) + 0xAC)) + 0x14);
    FIELD(ComboDisplay *, this, 0x58)->UpdateCounter(ComboCount(attacker), ComboDamage(attacker),
        static_cast<short>(ComboRate(attacker) * 1000.0f / 2.0f));
    if (FIELD(signed char, attacker, 0x3CE) == 0)
        Health(defender) -= attacker->CalculateDamage(attack) / 2;
    if (Health(defender) <= 0) Health(defender) = 1;
    if (FIELD(short, defender, 0x3A0) > 0 || FIELD(unsigned char, defender, 0x39C))
        RecoverableHealth(defender) = Health(defender);
    Meter(attacker) += FRAME(short, attack, 0x24);
    if (Meter(attacker) > 2000.0f) Meter(attacker) = 2000.0f;
    FIELD(short, defender, 0x3C8) = FRAME(short, attack, 0x1A);
    defender->UpdateFacingFromOpponent();
    reinterpret_cast<BattleCombat *>(this)->SpawnMidpointEffect(FRAME(short, attack, 0x36), FIELD(unsigned char, attack, 0x66));
    g_SoundBank->Play(FRAME(short, attack, 0x34));
}

void BattleCombat::ApplyReactionMode(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    switch (FIELD(short, defender, 0x60)) {
    case 50: case 51: case 52: case 56: case 57: case 58:
    case 62: case 63: case 64: case 70: case 84:
        defender->ResetPrimaryCounters(FIELD(short, defender, 0x60) + 1); break;
    case 71: case 72: case 74: case 77:
        FIELD(float, defender, 0x94) *= 1.25f;
        FIELD(float, defender, 0x98) *= 1.25f;
        FIELD(short, defender, 0x3C8) = FIELD(short, defender, 0x3C8) << 1; break;
    case 73:
        FIELD(short, defender, 0x3C8) = 32767;
        defender->ResetPrimaryCounters(88); break;
    case 75: case 81: case 83: case 86: case 87:
        FIELD(short, defender, 0x3C8) = FIELD(short, defender, 0x3C8) << 1; break;
    }
    g_SoundBank->Play(25);
    SpawnMidpointEffect(54, FIELD(unsigned char, attack, 0x66));
}
void BattleCombat::SpawnMidpointEffect(short effect, unsigned char direction)
{
    g_CombatEffects.Spawn(effect,
        (FIELD(int, this, 0x34) + FIELD(int, this, 0x3C)) / 2.0f,
        (FIELD(int, this, 0x38) + FIELD(int, this, 0x40)) / 2.0f,
        direction, 1, 0, 0);
}
