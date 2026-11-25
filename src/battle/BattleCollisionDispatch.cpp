#include "battle/BattleScene.hpp"
#include "engine/GameLeafHelpers.hpp"

void BattleScene::ResolveAttackHitboxes(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if (attack->savedCollisionResult != CollisionResult::None || attack->remainingHits <= 0) return;
    if (defender->IsGroundedStateWindow()) return;
    if (!(attack->savedFrameInfo->attackFlags & 0x400000)) {
        if (defender->hitInvulnerabilityFrames != 0) return;
        if (defender->savedFrameInfo->flags & 0x2000) return;
    }
    if ((attack->savedFrameInfo->attackFlags & 0x80) > 0) {
        if (defender->throwInvulnerabilityFrames > 0) return;
        if (defender->savedFrameInfo->flags & 0x800) return;
        if (defender->savedFrameInfo->flags & 0x1000) return;
    }
    RECT bodyRectangle;
    RECT attackBounds[4];
    RECT defendBounds[5];
    unsigned int hit = 0;
    signed char attackSize, defenderCount;
    int i;
    int contacts[4][5];
    attackSize = static_cast<signed char>(attack->savedFrameInfo->hitBoxes.size());
    defenderCount = static_cast<signed char>(defender->savedFrameInfo->hurtBoxes.size());
    for (i = 0; i < attackSize; ++i)
        TransformBounds(&attackBounds[i], &attack->savedFrameInfo->hitBoxes.at(i), attack);
    for (i = 0; i < defenderCount; ++i)
        TransformBounds(&defendBounds[i], &defender->savedFrameInfo->hurtBoxes.at(i), defender);
    TransformBounds(&bodyRectangle, reinterpret_cast<RECT*>(&defender->savedFrameInfo->bodyBox), defender);
    ClearBounds();
    for (i = 0; i < attackSize; ++i) {
        for (int j = 0; j < defenderCount; ++j) {
            contacts[i][j] = TestOverlap(&attackBounds[i], &defendBounds[j]);
            if (contacts[i][j]) {
                hit |= 1;
                IncludePair(&attackBounds[i], &defendBounds[j]);
            }
        }
    }
    if (hit) {
        defender->field3BE = !(attack->savedFrameInfo->attackFlags & 0x400000);
        if (ResolveSpecialHit(attack, attacker, defender)) return;
        if (ApplyConditionalHit(attack, attacker, defender)) return;
        if (ResolveContact(attack, attacker, defender)) return;
        if (defender->field3BE == 0)
            if (ResolveGuard(attack, attacker, defender)) return;
        if (ApplyHitResponse(attack, attacker, defender)) return;
        if (ApplyAttackHit(attack, attacker, defender)) return;
        ApplyHit(attack, attacker, defender);
    }
}

void BattleScene::ResolveBodyContact(Actor *first, Actor *second)
{
    if (first->savedCollisionResult != CollisionResult::None || first->remainingHits <= 0) return;
    if (second->savedCollisionResult != CollisionResult::None || second->remainingHits <= 0) return;
    if (first->savedSequenceInfo->targetPriority == 0) return;
    if (second->savedSequenceInfo->targetPriority == 0) return;
    int i;
    unsigned int hit = 0;
    signed char countA = static_cast<signed char>(first->frameInfo->hitBoxes.size());
    signed char countB = static_cast<signed char>(second->frameInfo->hitBoxes.size());
    RECT attackBounds[6], defendBounds[6];
    for (i = 0; i < countA; ++i)
        TransformBounds(&attackBounds[i], &first->frameInfo->hitBoxes.at(i), first);
    for (i = 0; i < countB; ++i)
        TransformBounds(&defendBounds[i], &second->frameInfo->hitBoxes.at(i), second);
    TransformBounds(&attackBounds[countA], reinterpret_cast<RECT*>(&first->frameInfo->bodyBox), first);
    TransformBounds(&defendBounds[countB], reinterpret_cast<RECT*>(&second->frameInfo->bodyBox), second);
    ClearBounds();
    for (i = 0; i <= countA; ++i) {
        for (int j = 0; j <= countB; ++j) {
            if (TestOverlap(&attackBounds[i], &defendBounds[j])) {
                hit |= 1;
                IncludePair(&attackBounds[i], &defendBounds[j]);
            }
        }
    }
    if (hit) {
        second->collisionPointX = (hitBounds.left + hitBounds.right) / 2.0f;
        first->collisionPointX = second->collisionPointX;
        second->collisionPointY = (hitBounds.top + hitBounds.bottom) / 2.0f;
        first->collisionPointY = second->collisionPointY;
        if (first->sequenceInfo->priority >= second->sequenceInfo->targetPriority ||
            second->sequenceInfo->priority >= first->sequenceInfo->targetPriority) {
            first->collisionResult = CollisionResult::ClashPreservedHits;
            second->collisionResult = CollisionResult::ClashPreservedHits;
        } else {
            if (first->sequenceInfo->targetPriority <= second->sequenceInfo->targetPriority) {
                first->collisionResult = CollisionResult::ClashConsumedHit;
                --first->remainingHits;
            }
            if (first->sequenceInfo->targetPriority >= second->sequenceInfo->targetPriority) {
                second->collisionResult = CollisionResult::ClashConsumedHit;
                --second->remainingHits;
            }
        }
    }
}

// Preserve the collision snapshot as ordinary float members.
void Actor::SaveCollisionFields()
{
    savedCollisionResult = collisionResult;
    savedFrameInfo = frameInfo;
    savedSequenceInfo = sequenceInfo;
    savedX = x;
    savedY = y;
    savedFacing = facing;
    savedAction = action;
}
