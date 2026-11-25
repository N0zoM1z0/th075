#ifndef TH075_CHARACTER_AUX_ACTION_HPP
#define TH075_CHARACTER_AUX_ACTION_HPP
#include "battle/Actor.hpp"
class CombatEffects;
struct EffectPatternSequence;

class CharacterAuxObject : public ActorRenderingBase {
public:
    CharacterAuxObject(CombatEffects* owner);
    void BindAnimation();
    void Advance();
    int ChooseIntegerRange(int lower, int upper);
    void SpawnPeer(short effect, float x, float y, signed char facing, signed char layer);
    void SpawnConfiguredPeer(short effect, float x, float y, signed char facing, signed char layer,
                             unsigned char flags, unsigned char mode);
    void ClearField8();

    short field074;              // +0x74 action-local counter, angle, speed or state
    short particleAngle;         // +0x76 direction used by the decelerating particles
    short initialScalePercent;   // +0x78 read by action 0x6B
    short field07A;              // +0x7A no recovered accesses
    std::vector<EffectPatternSequence*>* patterns;  // +0x7C
    union {
        float spawnParameters[4];
        float field080Angle;
    };
    CombatEffects* owner;                          // +0x90
};

typedef char CharacterAuxObjectLayout[
    sizeof(CharacterAuxObject) == 0x94 &&
    offsetof(CharacterAuxObject, patterns) == 0x7C &&
    offsetof(CharacterAuxObject, spawnParameters) == 0x80 &&
    offsetof(CharacterAuxObject, owner) == 0x90 ? 1 : -1];

// Observed cdecl / two floats / ST0 caller view. Origin remains unknown.
float AngleAt00483300(float first, float second);
extern "C" int __cdecl rand(void);
#endif
