#include "BattleScene.hpp"
#include "GameLeafHelpers.hpp"
// Scalar views refer only to observed fields of existing objects.
#define FIELD(type, object, offset) \
    (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
// Native owner+0x34 is a 16-byte borrowed RECT window (not an allocated pointer).
#define F1056_BOUNDS(owner) (*reinterpret_cast<RECT *>(reinterpret_cast<unsigned char *>(owner) + 0x34))
void BattleScene::ApplyImpact(Actor *attack, Fighter *attacker, Fighter *defender)
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


void BattleScene::ClearBounds()
{
    hitBounds.left = -10000;
    hitBounds.top = -10000;
    hitBounds.right = 10000;
    hitBounds.bottom = 10000;
}
void BattleScene::IncludePair(const RECT *first, const RECT *second)
{
    if (hitBounds.left < first->left)
        hitBounds.left = first->left;
    if (hitBounds.left < second->left)
        hitBounds.left = second->left;
    if (hitBounds.top < first->top)
        hitBounds.top = first->top;
    if (hitBounds.top < second->top)
        hitBounds.top = second->top;
    if (hitBounds.right > first->right)
        hitBounds.right = first->right;
    if (hitBounds.right > second->right)
        hitBounds.right = second->right;
    if (hitBounds.bottom > first->bottom)
        hitBounds.bottom = first->bottom;
    if (hitBounds.bottom > second->bottom)
        hitBounds.bottom = second->bottom;
}
int BattleScene::TestOverlap(const RECT *first, const RECT *second)
{
    return ((second->left - first->right) & (first->left - second->right) &
            (second->top - first->bottom) & (first->top - second->bottom)) >> 31;
}
void BattleScene::TransformBounds(RECT *destination, const RECT *source, Actor *actor)
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
