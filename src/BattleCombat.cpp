#include "BattleCombat.hpp"
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
#define Score(actor) FIELD(unsigned long, actor, 0x2D0)

void BattleCombat::ApplyHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    FIELD(int, attack, 0x7C) = 1;
    if (FIELD(short, defender, 0x60) < 50 || FIELD(short, defender, 0x60) >= 143) {
        ComboCount(attacker) = 0;
        ComboDamage(attacker) = 0;
        ComboRate(attacker) = 1.0f;
    }
    defender->ClearByte40();
    if (FIELD(float, defender, 0x48) > 0.0f || (FRAME(unsigned long, defender, 0x3C) & 4)) {
        if (FRAME(short, attack, 0x28))
            defender->ResetPrimaryCounters(FRAME(short, attack, 0x28));
        else
            defender->ResetPrimaryCounters(70);
    } else {
        if (FRAME(short, attack, 0x2A))
            defender->ResetPrimaryCounters(FRAME(short, attack, 0x2A));
        else if (FRAME(unsigned long, defender, 0x3C) & 1) {
            if (FRAME(unsigned long, attack, 0x40) & 1)
                defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 56);
            else
                defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 50);
        } else if (FRAME(unsigned long, defender, 0x3C) & 2)
            defender->ResetPrimaryCounters(FRAME(signed char, attack, 0x38) + 62);
    }
    --FIELD(short, attack, 0x80);
    FIELD(short, attack, 0x82) = FRAME(short, attack, 0x1C);
    FIELD(short, defender, 0x82) = FRAME(short, attack, 0x1E);
    FIELD(unsigned long, defender, 0x94) = FRAME(unsigned long, attack, 0x2C);
    FIELD(unsigned long, defender, 0x98) = FRAME(unsigned long, attack, 0x30);
    Meter(attacker) += FRAME(short, attack, 0x24);
    if (Meter(attacker) > 2000.0f)
        Meter(attacker) = 2000.0f;
    Meter(defender) += attacker->CalculateDamage(attack) * 0.5f;
    if (Meter(defender) > 2000.0f)
        Meter(defender) = 2000.0f;
    if ((FRAME(unsigned long, attack, 0x40) & 0x100) > 0)
        FIELD(short, defender, 0x3C8) = 15000;
    else
        FIELD(short, defender, 0x3C8) = static_cast<short>(FRAME(short, attack, 0x1A) * ComboRate(attacker));
    if ((FRAME(unsigned long, attack, 0x40) & 0x400) && (FRAME(unsigned long, defender, 0x3C) & 0x40)) {
        ComboDamage(attacker) += attacker->CalculateDamage(attack) * 1.25;
        if (FIELD(signed char, attacker, 0x3CE) == 0) {
            Health(defender) -= attacker->CalculateDamage(attack) * 1.25;
            if (FIELD(short, defender, 0x3A0) > 0)
                RecoverableHealth(defender) -= attacker->CalculateDamage(attack) * 1.25;
            else
                RecoverableHealth(defender) -= attacker->CalculateDamage(attack) * 1.25 *
                    (0.8 - FIELD(short, defender, 0x3B0) * 0.2 / 1000.0);
        }
        ApplyReactionMode(attack, attacker, defender);
    } else {
        ComboDamage(attacker) += attacker->CalculateDamage(attack);
        if (FIELD(signed char, attacker, 0x3CE) == 0) {
            Health(defender) -= attacker->CalculateDamage(attack);
            if (FIELD(short, defender, 0x3A0) > 0)
                RecoverableHealth(defender) -= attacker->CalculateDamage(attack);
            else
                RecoverableHealth(defender) -= attacker->CalculateDamage(attack) *
                    (0.8 - FIELD(short, defender, 0x3B0) * 0.2 / 1000.0);
        }
    }
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
    ++ComboCount(attacker);
    *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(attacker) + 0x3C0) *=
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(
            *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(attack) + 0xAC)) + 0x14);
    FIELD(ComboDisplay *, this, 0x58)->UpdateCounter(ComboCount(attacker), ComboDamage(attacker),
        static_cast<short>(ComboRate(attacker) * 1000.0f));
    defender->UpdateFacingFromOpponent();
    SpawnMidpointEffect(FRAME(short, attack, 0x36), FIELD(unsigned char, attack, 0x66));
    g_SoundBank->Play(FRAME(short, attack, 0x34));
    switch (FRAME(signed char, attack, 0x38)) {
    case 0: Score(attacker) += 100; break;
    case 1: Score(attacker) += 200; break;
    case 2: Score(attacker) += 300; break;
    case 3: Score(attacker) += 500; break;
    }
    if (g_CombatMode == 3 && FIELD(signed char, attacker, 0x2CC) == 0) {
        if (ComboDamage(attacker) > g_BattleRecords.GetComboDamage())
            g_BattleRecords.SetComboDamage(ComboDamage(attacker));
        if (ComboCount(attacker) > g_BattleRecords.GetComboCount())
            g_BattleRecords.SetComboCount(ComboCount(attacker));
        if (ComboCount(attacker) > g_MaxComboCount)
            g_MaxComboCount = ComboCount(attacker);
        if (Score(attacker) > g_MaxCombatScore)
            g_MaxCombatScore = Score(attacker);
    }
}

bool BattleCombat::ApplyConditionalHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    if (!(FRAME(unsigned long, attack, 0x40) & 0x20) &&
        ((FRAME(unsigned long, defender, 0x3C) & 0x80) ||
         ((FRAME(unsigned long, defender, 0x3C) & 0x100) && FIELD(short, defender, 0x3CA) > 0))) {
        if (FIELD(short, defender, 0x3CA) > 0)
            --FIELD(short, defender, 0x3CA);
        if (FIELD(short, defender, 0x3CC) == 0) {
            ComboCount(attacker) = 0;
            ComboDamage(attacker) = 0;
            ComboRate(attacker) = 1.0f;
        }
        FIELD(int, attack, 0x7C) = 7;
        --FIELD(short, attack, 0x80);
        FIELD(short, attack, 0x82) = FRAME(short, attack, 0x1C);
        FIELD(short, defender, 0x82) = FRAME(short, attack, 0x1E);
        FIELD(unsigned long, defender, 0x94) = FRAME(unsigned long, attack, 0x2C);
        FIELD(unsigned long, defender, 0x98) = FRAME(unsigned long, attack, 0x30);
        FIELD(short, defender, 0x3CC) = 15;
        FIELD(unsigned char, defender, 0x484) = 8;
        if ((FRAME(unsigned long, attack, 0x40) & 0x100) > 0)
            FIELD(short, defender, 0x3C8) = 30000;
        else
            FIELD(short, defender, 0x3C8) = static_cast<short>(FRAME(short, attack, 0x1A) * ComboRate(attacker));
        if ((FRAME(unsigned long, attack, 0x40) & 0x400) && (FRAME(unsigned long, defender, 0x3C) & 0x40)) {
            ComboDamage(attacker) += attacker->CalculateDamage(attack) * 1.25 / 2.0;
            if (FIELD(signed char, attacker, 0x3CE) == 0) {
                Health(defender) -= attacker->CalculateDamage(attack) * 1.25 / 2.0;
                if (FIELD(short, defender, 0x3A0) > 0)
                    RecoverableHealth(defender) -= attacker->CalculateDamage(attack) * 1.25 / 2.0;
                else
                    RecoverableHealth(defender) -= attacker->CalculateDamage(attack) * 1.25 *
                        (0.75 - FIELD(short, defender, 0x3B0) * 0.25 / 1000.0) / 2.0;
            }
            ApplyReactionMode(attack, attacker, defender);
        } else {
            ComboDamage(attacker) += attacker->CalculateDamage(attack) / 2;
            if (FIELD(signed char, attacker, 0x3CE) == 0) {
                Health(defender) -= attacker->CalculateDamage(attack) / 2;
                if (FIELD(short, defender, 0x3A0) > 0)
                    RecoverableHealth(defender) -= attacker->CalculateDamage(attack) / 2;
                else
                    RecoverableHealth(defender) -= attacker->CalculateDamage(attack) *
                        (0.75 - FIELD(short, defender, 0x3B0) * 0.25 / 1000.0) / 2.0;
            }
        }
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
        ++ComboCount(attacker);
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(attacker) + 0x3C0) *=
            *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(
                *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(attack) + 0xAC)) + 0x14);
        FIELD(ComboDisplay *, this, 0x58)->UpdateCounter(ComboCount(attacker), ComboDamage(attacker),
            static_cast<short>(ComboRate(attacker) * 1000.0f));
        Meter(attacker) += FRAME(short, attack, 0x24);
        if (Meter(attacker) > 2000.0f)
            Meter(attacker) = 2000.0f;
        Meter(defender) += attacker->CalculateDamage(attack) * 0.25f;
        if (Meter(defender) > 2000.0f)
            Meter(defender) = 2000.0f;
        SpawnMidpointEffect(FRAME(short, attack, 0x36), FIELD(unsigned char, attack, 0x66));
        g_SoundBank->Play(FRAME(short, attack, 0x34));
        switch (FRAME(signed char, attack, 0x38)) {
        case 0: Score(attacker) += 100; break;
        case 1: Score(attacker) += 200; break;
        case 2: Score(attacker) += 300; break;
        case 3: Score(attacker) += 500; break;
        }
        if (g_CombatMode == 3 && FIELD(signed char, attacker, 0x2CC) == 0) {
            if (ComboDamage(attacker) > g_BattleRecords.GetComboDamage())
                g_BattleRecords.SetComboDamage(ComboDamage(attacker));
            if (ComboCount(attacker) > g_BattleRecords.GetComboCount())
                g_BattleRecords.SetComboCount(ComboCount(attacker));
            if (ComboCount(attacker) > g_MaxComboCount)
                g_MaxComboCount = ComboCount(attacker);
            if (Score(attacker) > g_MaxCombatScore)
                g_MaxCombatScore = Score(attacker);
        }
        return true;
    } else {
        return false;
    }
}

short CombatActor::CalculateDamage(CombatActor *attack)
{
    if (FIELD(signed char, FIELD(CombatActor *, this, 0x2E8), 0x2CD) != 0 && g_CombatMode == 3) {
        return static_cast<short>(FRAME(short, attack, 0x10) * FIELD(float, attack, 0x9C) *
            FIELD(float, attack, 0xA4) * FIELD(float, this, 0xA0) * ComboRate(this) *
            (FIELD(short, FIELD(CombatActor *, this, 0x2E8), 0x328) / 4.0f /
             FIELD(short, FIELD(CombatActor *, this, 0x2E8),
                 0x33E + FIELD(signed char, FIELD(CombatActor *, this, 0x2E8), 0x39D) * 2) + 0.75));
    } else {
        return static_cast<short>(FRAME(short, attack, 0x10) * FIELD(float, attack, 0x9C) *
            FIELD(float, attack, 0xA4) * FIELD(float, this, 0xA0) * ComboRate(this) *
            (FIELD(short, FIELD(CombatActor *, this, 0x2E8), 0x328) / 4.0f / 10000.0f + 0.75));
    }
}

bool CombatActor::UpdateFacingFromOpponent()
{
    signed char previous = FIELD(signed char, this, 0x66);
    if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) <
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(
            *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) + 0x2E8)) + 0x44)) {
        FIELD(signed char, this, 0x66) = 1;
        return FIELD(signed char, this, 0x66) != previous;
    } else if (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x44) >
        *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(
            *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) + 0x2E8)) + 0x44)) {
        FIELD(signed char, this, 0x66) = -1;
        return FIELD(signed char, this, 0x66) != previous;
    }
    return false;
}
