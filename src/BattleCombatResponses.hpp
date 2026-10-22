#ifndef TH075_BATTLE_COMBAT_RESPONSES_HPP
#define TH075_BATTLE_COMBAT_RESPONSES_HPP

#include "BattleCombat.hpp"
// Partial interfaces used only on existing receivers.
class CombatResponseActor { public: signed char ClassifyResponse(unsigned long flags); };
class BattleCombatResponses {
public:
 bool ApplyHitResponse(CombatActor *, CombatActor *, CombatActor *);
 bool ApplyAttackHit(CombatActor *, CombatActor *, CombatActor *);
 void ApplyGuardHit(CombatActor *, CombatActor *, CombatActor *);
 void ApplyImpact(CombatActor *, CombatActor *, CombatActor *);
};
class CombatEffects { public: void Spawn(short, float, float, unsigned char, signed char, unsigned char, unsigned char); };
extern CombatEffects g_CombatEffects;

#endif
