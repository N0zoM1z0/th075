#include "BattleCollision.hpp"
#include "BattleCombatResponses.hpp"
#include "GameLeafHelpers.hpp"
// Scalar views refer only to observed fields of existing objects.
#define FIELD(type, object, offset) \
    (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(object) + offset))
#define FRAME(type, actor, offset) FIELD(type, FIELD(void *, actor, 0xAC), offset)
void BattleCombatResponses::ApplyImpact(CombatActor *attack, CombatActor *attacker, CombatActor *defender)
{
    FIELD(int, attack, 0x7C) = 2;
    --FIELD(short, attack, 0x80);
    FIELD(short, attack, 0x82) = FRAME(short, attack, 0x20);
    FIELD(short, defender, 0x82) = FRAME(short, attack, 0x22);
    FIELD(unsigned long, defender, 0x94) = FRAME(unsigned long, attack, 0x2C);
    FIELD(unsigned long, defender, 0x98) = FRAME(unsigned long, attack, 0x30);
    if (FIELD(short, defender, 0x324) <= 0) FIELD(short, defender, 0x324) = 1;
    if (FIELD(short, defender, 0x3A0) > 0 || FIELD(unsigned char, defender, 0x39C))
        FIELD(short, defender, 0x326) = FIELD(short, defender, 0x324);
    FIELD(float, attacker, 0x368) += FRAME(short, attack, 0x26);
    if (FIELD(float, attacker, 0x368) > 2000.0f) FIELD(float, attacker, 0x368) = 2000.0f;
    defender->UpdateFacingFromOpponent();
    g_SoundBank->Play(20);
}


void BattleCollision::ClearBounds()
{
    FIELD(int, this, 0x34) = -10000;
    FIELD(int, this, 0x38) = -10000;
    FIELD(int, this, 0x3C) = 10000;
    FIELD(int, this, 0x40) = 10000;
}
void BattleCollision::IncludePair(const RECT *first, const RECT *second)
{
    if (FIELD(long, this, 0x34) < first->left)
        FIELD(long, this, 0x34) = first->left;
    if (FIELD(long, this, 0x34) < second->left)
        FIELD(long, this, 0x34) = second->left;
    if (FIELD(long, this, 0x38) < first->top)
        FIELD(long, this, 0x38) = first->top;
    if (FIELD(long, this, 0x38) < second->top)
        FIELD(long, this, 0x38) = second->top;
    if (FIELD(long, this, 0x3C) > first->right)
        FIELD(long, this, 0x3C) = first->right;
    if (FIELD(long, this, 0x3C) > second->right)
        FIELD(long, this, 0x3C) = second->right;
    if (FIELD(long, this, 0x40) > first->bottom)
        FIELD(long, this, 0x40) = first->bottom;
    if (FIELD(long, this, 0x40) > second->bottom)
        FIELD(long, this, 0x40) = second->bottom;
}
int BattleCollision::TestOverlap(const RECT *first, const RECT *second)
{
    return ((second->left - first->right) & (first->left - second->right) &
            (second->top - first->bottom) & (first->top - second->bottom)) >> 31;
}
void BattleCollision::TransformBounds(RECT *destination, const RECT *source, CombatActor *actor)
{
    if (FIELD(signed char, actor, 0x66) == 1) {
        destination->left = static_cast<long>(CeilCollisionCoordinate(*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(actor) + 0x44)) + source->left);
        destination->right = static_cast<long>(CeilCollisionCoordinate(*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(actor) + 0x44)) + source->right);
    } else {
        destination->left = static_cast<long>(CeilCollisionCoordinate(*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(actor) + 0x44)) - source->right);
        destination->right = static_cast<long>(CeilCollisionCoordinate(*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(actor) + 0x44)) - source->left);
    }
    destination->top = static_cast<long>(CeilCollisionCoordinate(*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(actor) + 0x48)) - source->bottom);
    destination->bottom = static_cast<long>(CeilCollisionCoordinate(*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(actor) + 0x48)) - source->top);
}
