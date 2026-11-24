#ifndef TH075_CHARACTER_AUX_ACTION_HPP
#define TH075_CHARACTER_AUX_ACTION_HPP
#include "Actor.hpp"
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

    short field074;
    short field076;
    short field078;
    short field07A;
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
