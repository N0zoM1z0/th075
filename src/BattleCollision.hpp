#ifndef TH075_BATTLE_COLLISION_HPP
#define TH075_BATTLE_COLLISION_HPP
#include <windows.h>
#include "BattleCombatResponses.hpp"

// Partial receiver interface only; never instantiate or embed this view.
// RECT is a complete SDK coordinate value, not a reconstructed owner layout.
class BattleCollision {
public:
    void TransformBounds(RECT *destination, const RECT *source, CombatActor *actor);
    int TestOverlap(const RECT *first, const RECT *second);
    void ClearBounds();
    void IncludePair(const RECT *first, const RECT *second);
};
// Existing float wrapper; original declaration and ownership remain unresolved.
float __cdecl CeilCollisionCoordinate(float value);
#endif
