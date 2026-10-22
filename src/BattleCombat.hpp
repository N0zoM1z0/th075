#ifndef TH075_BATTLE_COMBAT_HPP
#define TH075_BATTLE_COMBAT_HPP

// Partial receiver interfaces only. No original owner extent is established;
// never instantiate or embed these views.
class CombatActor {
public:
    void ResetPrimaryCounters(short state);
    void ClearByte40();
    short CalculateDamage(CombatActor *attack);
    bool UpdateFacingFromOpponent();
};
class ComboDisplay {
public:
    void UpdateCounter(short count, short damage, short rate);
};
class BattleRecords {
public:
    int GetComboDamage();
    int GetComboCount();
    void SetComboDamage(int value);
    void SetComboCount(int value);
};
class BattleCombat {
public:
    void ApplyHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender);
    bool ApplyConditionalHit(CombatActor *attack, CombatActor *attacker, CombatActor *defender);
    void ApplyReactionMode(CombatActor *attack, CombatActor *attacker, CombatActor *defender);
    void SpawnMidpointEffect(short effect, unsigned char direction);
};
extern signed char g_CombatMode;
extern short g_MaxComboCount;
extern unsigned long g_MaxCombatScore;
extern BattleRecords g_BattleRecords;
#endif
