#include "BattleCollisionDispatch.hpp"
#include "GameLeafHelpers.hpp"

// Observed scalar views, without complete owner layouts.
#define FIELD(type, object, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define RECORD(type, actor, pointer, offset) FIELD(type, FIELD(void *, actor, pointer), offset)
#define FRAME(type, actor, offset) RECORD(type, actor, 0xAC, offset)
// Native battle collision owner+0x34 is four actual signed Win32 RECT
// boundary DWORDs; this is only a borrowed window, not a new owner.
#define F1079_BOUNDS(owner) (*reinterpret_cast<RECT*>(reinterpret_cast<unsigned char*>(owner)+0x34))
// Actual attack/collision FRAME record bitflags (32-bit at +0x3C/+0x40).
void BattleCollisionDispatch::ResolveAttackHitboxes(Actor *attack, Fighter *attacker, Fighter *defender)
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
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&attackBounds[i], &attack->savedFrameInfo->hitBoxes.At(i), attack);
    for (i = 0; i < defenderCount; ++i)
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&defendBounds[i], &defender->savedFrameInfo->hurtBoxes.At(i), defender);
    reinterpret_cast<BattleCollision *>(this)->TransformBounds(&bodyRectangle, reinterpret_cast<RECT*>(defender->savedFrameInfo->bodyBox), defender);
    reinterpret_cast<BattleCollision *>(this)->ClearBounds();
    for (i = 0; i < attackSize; ++i) {
        for (int j = 0; j < defenderCount; ++j) {
            contacts[i][j] = reinterpret_cast<BattleCollision *>(this)->TestOverlap(&attackBounds[i], &defendBounds[j]);
            if (contacts[i][j]) {
                hit |= 1;
                reinterpret_cast<BattleCollision *>(this)->IncludePair(&attackBounds[i], &defendBounds[j]);
            }
        }
    }
    if (hit) {
        defender->field3BE = !(attack->savedFrameInfo->attackFlags & 0x400000);
        if (ResolveSpecialHit(attack, attacker, defender)) return;
        if (reinterpret_cast<BattleCombat *>(this)->ApplyConditionalHit(attack, attacker, defender)) return;
        if (ResolveContact(attack, attacker, defender)) return;
        if (defender->field3BE == 0)
            if (ResolveGuard(attack, attacker, defender)) return;
        if (reinterpret_cast<BattleCombatResponses *>(this)->ApplyHitResponse(attack, attacker, defender)) return;
        if (reinterpret_cast<BattleCombatResponses *>(this)->ApplyAttackHit(attack, attacker, defender)) return;
        reinterpret_cast<BattleCombat *>(this)->ApplyHit(attack, attacker, defender);
    }
}

void BattleCollisionDispatch::ResolveBodyContact(Actor *first, Actor *second)
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
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&attackBounds[i], &first->frameInfo->hitBoxes.At(i), first);
    for (i = 0; i < countB; ++i)
        reinterpret_cast<BattleCollision *>(this)->TransformBounds(&defendBounds[i], &second->frameInfo->hitBoxes.At(i), second);
    reinterpret_cast<BattleCollision *>(this)->TransformBounds(&attackBounds[countA], reinterpret_cast<RECT*>(first->frameInfo->bodyBox), first);
    reinterpret_cast<BattleCollision *>(this)->TransformBounds(&defendBounds[countB], reinterpret_cast<RECT*>(second->frameInfo->bodyBox), second);
    reinterpret_cast<BattleCollision *>(this)->ClearBounds();
    for (i = 0; i <= countA; ++i) {
        for (int j = 0; j <= countB; ++j) {
            if (reinterpret_cast<BattleCollision *>(this)->TestOverlap(&attackBounds[i], &defendBounds[j])) {
                hit |= 1;
                reinterpret_cast<BattleCollision *>(this)->IncludePair(&attackBounds[i], &defendBounds[j]);
            }
        }
    }
    if (hit) {
        second->field08C = (F1079_BOUNDS(this).left + F1079_BOUNDS(this).right) / 2.0f;
        reinterpret_cast<unsigned long&>(first->field08C) = reinterpret_cast<unsigned long&>(second->field08C);
        second->field090 = (F1079_BOUNDS(this).top + F1079_BOUNDS(this).bottom) / 2.0f;
        reinterpret_cast<unsigned long&>(first->field090) = reinterpret_cast<unsigned long&>(second->field090);
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

// Positions are copied as raw DWORDs, not as floats.
void Actor::SaveCollisionFields()
{
    savedField07C = field07C;
    savedFrameInfo = frameInfo;
    savedSequenceInfo = sequenceInfo;
    reinterpret_cast<unsigned long&>(savedX) = reinterpret_cast<unsigned long&>(x);
    reinterpret_cast<unsigned long&>(savedY) = reinterpret_cast<unsigned long&>(y);
    savedFacing = facing;
    savedAction = action;
}

#undef F1079_BOUNDS
#undef F1079_ATTACK_FLAGS
#undef F1079_DEFENSE_FLAGS
