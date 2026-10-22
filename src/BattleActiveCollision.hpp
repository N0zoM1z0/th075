#ifndef TH075_BATTLE_ACTIVE_COLLISION_HPP
#define TH075_BATTLE_ACTIVE_COLLISION_HPP
#include "BattleCollisionDispatch.hpp"

// Partial receiver interface; used only on an existing battle object.
class BattleActiveCollision {
public:
    void ResolveActiveCollisions();
};
#endif
