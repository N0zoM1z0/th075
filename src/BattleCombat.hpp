#ifndef TH075_BATTLE_COMBAT_HPP
#define TH075_BATTLE_COMBAT_HPP
#include "Fighter.hpp"

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
    void ApplyHit(Actor *attack, Fighter *attacker, Fighter *defender);
    bool ApplyConditionalHit(Actor *attack, Fighter *attacker, Fighter *defender);
    void ApplyReactionMode(Actor *attack, Fighter *attacker, Fighter *defender);
    void SpawnMidpointEffect(short effect, unsigned char direction);
};
extern signed char g_CombatMode;
extern short g_MaxComboCount;
extern unsigned long g_MaxCombatScore;
extern BattleRecords g_BattleRecords;
#endif
