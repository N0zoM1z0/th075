#ifndef TH075_BATTLE_COLLISION_DISPATCH_HPP
#define TH075_BATTLE_COLLISION_DISPATCH_HPP
#include "BattleCollision.hpp"

// Partial interfaces on existing owners. No container or actor is instantiated.
class CollisionRectSequence {
public:
    unsigned int Size();
    RECT &At(unsigned int index);
};
class CollisionActor {
public:
    void SaveCollisionFields();
};
class BattleCollisionDispatch {
public:
    void ResolveAttackHitboxes(CombatActor *attack, CombatActor *attacker, CombatActor *defender);
    void ResolveBodyContact(CombatActor *first, CombatActor *second);
    bool ResolveSpecialHit(CombatActor *, CombatActor *, CombatActor *);
    bool ResolveContact(CombatActor *, CombatActor *, CombatActor *);
    bool ResolveGuard(CombatActor *, CombatActor *, CombatActor *);
};
#endif
