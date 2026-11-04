#include "FighterActionTimerPairF1027.hpp"
#include "FighterVitalBorrowedF999.hpp"
#include "FrameActorMotionPairsF1037.hpp"
#include "BattleCollision.hpp"
#include "BattleCombatResponses.hpp"
#include "GameLeafHelpers.hpp"
// Scalar views refer only to observed fields of existing objects.
#define FIELD(type, object, offset) \
    (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define FRAME(type, actor, offset) FIELD(type, FIELD(void *, actor, 0xAC), offset)
// Native owner+0x34 is a 16-byte borrowed RECT window (not an allocated pointer).
#define F1056_BOUNDS(owner) (*reinterpret_cast<RECT *>(reinterpret_cast<unsigned char *>(owner) + 0x34))
void BattleCombatResponses::ApplyImpact(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    FIELD(int, attack, 0x7C) = 2;
    --F1027_TIMERS(attack).wordAt80;
    F1027_TIMERS(attack).timerAt82 = FRAME(short, attack, 0x20);
    F1027_TIMERS(defender).timerAt82 = FRAME(short, attack, 0x22);
    FIELD(unsigned long, defender, 0x94) = FRAME(unsigned long, attack, 0x2C);
    FIELD(unsigned long, defender, 0x98) = FRAME(unsigned long, attack, 0x30);
    if (F999_VITAL(defender).currentAt324 <= 0) F999_VITAL(defender).currentAt324 = 1;
    if (FIELD(short, defender, 0x3A0) > 0 || FIELD(unsigned char, defender, 0x39C))
        F999_VITAL(defender).recoverableAt326 = F999_VITAL(defender).currentAt324;
    FIELD(float, attacker, 0x368) += FRAME(short, attack, 0x26);
    if (FIELD(float, attacker, 0x368) > 2000.0f) FIELD(float, attacker, 0x368) = 2000.0f;
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
void BattleCollision::TransformBounds(RECT *destination, const RECT *source, CombatActor *actor)
{
    if (FIELD(signed char, actor, 0x66) == 1) {
        destination->left = static_cast<long>(CeilCollisionCoordinate(F1037_POSITION(actor).xPosition) + source->left);
        destination->right = static_cast<long>(CeilCollisionCoordinate(F1037_POSITION(actor).xPosition) + source->right);
    } else {
        destination->left = static_cast<long>(CeilCollisionCoordinate(F1037_POSITION(actor).xPosition) - source->right);
        destination->right = static_cast<long>(CeilCollisionCoordinate(F1037_POSITION(actor).xPosition) - source->left);
    }
    destination->top = static_cast<long>(CeilCollisionCoordinate(F1037_POSITION(actor).yPosition) - source->bottom);
    destination->bottom = static_cast<long>(CeilCollisionCoordinate(F1037_POSITION(actor).yPosition) - source->top);
}
