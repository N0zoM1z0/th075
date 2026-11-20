#include "BattleScene.hpp"
#include "GameLeafHelpers.hpp"

void BattleScene::ResolveAttackHitboxes(Actor *attack, Fighter *attacker, Fighter *defender)
{
    if (attack->savedField07C != 0 || attack->field080 <= 0) return;
    if (defender->IsGroundedStateWindow()) return;
    if (!(attack->savedFrameInfo->attackFlags & 0x400000)) {
        if (defender->field084 != 0) return;
        if (defender->savedFrameInfo->flags & 0x2000) return;
    }
    if ((attack->savedFrameInfo->attackFlags & 0x80) > 0) {
        if (defender->field086 > 0) return;
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
    attackSize = static_cast<signed char>(attack->savedFrameInfo->hitBoxes.Size());
    defenderCount = static_cast<signed char>(defender->savedFrameInfo->hurtBoxes.Size());
    for (i = 0; i < attackSize; ++i)
        TransformBounds(&attackBounds[i], &attack->savedFrameInfo->hitBoxes.At(i), attack);
    for (i = 0; i < defenderCount; ++i)
        TransformBounds(&defendBounds[i], &defender->savedFrameInfo->hurtBoxes.At(i), defender);
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
    if (first->savedField07C != 0 || first->field080 <= 0) return;
    if (second->savedField07C != 0 || second->field080 <= 0) return;
    if (first->savedSequenceInfo->targetPriority == 0) return;
    if (second->savedSequenceInfo->targetPriority == 0) return;
    int i;
    unsigned int hit = 0;
    signed char countA = static_cast<signed char>(first->frameInfo->hitBoxes.Size());
    signed char countB = static_cast<signed char>(second->frameInfo->hitBoxes.Size());
    RECT attackBounds[6], defendBounds[6];
    for (i = 0; i < countA; ++i)
        TransformBounds(&attackBounds[i], &first->frameInfo->hitBoxes.At(i), first);
    for (i = 0; i < countB; ++i)
        TransformBounds(&defendBounds[i], &second->frameInfo->hitBoxes.At(i), second);
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
        second->field08C = (hitBounds.left + hitBounds.right) / 2.0f;
        first->field08C = second->field08C;
        second->field090 = (hitBounds.top + hitBounds.bottom) / 2.0f;
        first->field090 = second->field090;
        if (first->sequenceInfo->priority >= second->sequenceInfo->targetPriority ||
            second->sequenceInfo->priority >= first->sequenceInfo->targetPriority) {
            first->field07C = 5;
            second->field07C = 5;
        } else {
            if (first->sequenceInfo->targetPriority <= second->sequenceInfo->targetPriority) {
                first->field07C = 4;
                --first->field080;
            }
            if (first->sequenceInfo->targetPriority >= second->sequenceInfo->targetPriority) {
                second->field07C = 4;
                --second->field080;
            }
        }
    }
}

// Preserve the collision snapshot as ordinary float members.
void Actor::SaveCollisionFields()
{
    savedField07C = field07C;
    savedFrameInfo = frameInfo;
    savedSequenceInfo = sequenceInfo;
    savedX = x;
    savedY = y;
    savedFacing = facing;
    savedAction = action;
}
