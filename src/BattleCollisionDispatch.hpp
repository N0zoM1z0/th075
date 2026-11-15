#ifndef TH075_BATTLE_COLLISION_DISPATCH_HPP
#define TH075_BATTLE_COLLISION_DISPATCH_HPP
#include "BattleCollision.hpp"

// Partial interfaces on existing owners. No container or actor is instantiated.
class BattleCollisionDispatch {
public:
    void ResolveAttackHitboxes(Actor *attack, Fighter *attacker, Fighter *defender);
    void ResolveBodyContact(Actor *first, Actor *second);
    bool ResolveSpecialHit(Actor *, Fighter *, Fighter *);
    bool ResolveContact(Actor *, Fighter *, Fighter *);
    bool ResolveGuard(Actor *, Fighter *, Fighter *);
};
#endif
