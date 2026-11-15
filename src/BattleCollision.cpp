#include "BattleCollision.hpp"
#include "BattleCombatResponses.hpp"
#include "GameLeafHelpers.hpp"
// Scalar views refer only to observed fields of existing objects.
#define FIELD(type, object, offset) \
    (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
// Native owner+0x34 is a 16-byte borrowed RECT window (not an allocated pointer).
#define F1056_BOUNDS(owner) (*reinterpret_cast<RECT *>(reinterpret_cast<unsigned char *>(owner) + 0x34))
void BattleCombatResponses::ApplyImpact(Actor *attack, Fighter *attacker, Fighter *defender)
{
    attack->field07C = 2;
    --attack->field080;
    attack->field082 = attack->savedFrameInfo->field20;
    defender->field082 = attack->savedFrameInfo->field22;
    defender->field094 = attack->savedFrameInfo->field2C;
    defender->field098 = attack->savedFrameInfo->field30;
    if (defender->health <= 0) defender->health = 1;
    if (defender->field3A0 > 0 || defender->field39C)
        defender->recoverableHealth = defender->health;
    attacker->cardGauge += attack->savedFrameInfo->field26;
    if (attacker->cardGauge > 2000.0f) attacker->cardGauge = 2000.0f;
    defender->UpdateFacingFromOpponent();
    g_SoundBank->Play(20);
}


void BattleCollision::ClearBounds()
{
    F1056_BOUNDS(this).left = -10000;
    F1056_BOUNDS(this).top = -10000;
    F1056_BOUNDS(this).right = 10000;
    F1056_BOUNDS(this).bottom = 10000;
}
void BattleCollision::IncludePair(const RECT *first, const RECT *second)
{
    if (F1056_BOUNDS(this).left < first->left)
        F1056_BOUNDS(this).left = first->left;
    if (F1056_BOUNDS(this).left < second->left)
        F1056_BOUNDS(this).left = second->left;
    if (F1056_BOUNDS(this).top < first->top)
        F1056_BOUNDS(this).top = first->top;
    if (F1056_BOUNDS(this).top < second->top)
        F1056_BOUNDS(this).top = second->top;
    if (F1056_BOUNDS(this).right > first->right)
        F1056_BOUNDS(this).right = first->right;
    if (F1056_BOUNDS(this).right > second->right)
        F1056_BOUNDS(this).right = second->right;
    if (F1056_BOUNDS(this).bottom > first->bottom)
        F1056_BOUNDS(this).bottom = first->bottom;
    if (F1056_BOUNDS(this).bottom > second->bottom)
        F1056_BOUNDS(this).bottom = second->bottom;
}
int BattleCollision::TestOverlap(const RECT *first, const RECT *second)
{
    return ((second->left - first->right) & (first->left - second->right) &
            (second->top - first->bottom) & (first->top - second->bottom)) >> 31;
}
void BattleCollision::TransformBounds(RECT *destination, const RECT *source, Actor *actor)
{
    if (actor->facing == 1) {
        destination->left = static_cast<long>(CeilCollisionCoordinate(actor->x) + source->left);
        destination->right = static_cast<long>(CeilCollisionCoordinate(actor->x) + source->right);
    } else {
        destination->left = static_cast<long>(CeilCollisionCoordinate(actor->x) - source->right);
        destination->right = static_cast<long>(CeilCollisionCoordinate(actor->x) - source->left);
    }
    destination->top = static_cast<long>(CeilCollisionCoordinate(actor->y) - source->bottom);
    destination->bottom = static_cast<long>(CeilCollisionCoordinate(actor->y) - source->top);
}
