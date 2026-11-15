#ifndef TH075_BATTLE_EFFECT_SPAWNER_F136_HPP
#define TH075_BATTLE_EFFECT_SPAWNER_F136_HPP
#include "Actor.hpp"

// Pointer-only interfaces. Never construct or embed these private owners;
// their complete layouts, original names and allocation sizes remain unknown.

// Only slot 7 is called. The uncalled prefix names describe slot positions,
// not recovered original method meanings or usable call contracts.
class EffectFactoryF136 {
public:
    virtual void UnknownSlot0();
    virtual void UnknownSlot1();
    virtual void UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual void UnknownSlot6();
    virtual void Acquire(Actor** output);
};

class EffectDequeF136 {
public:
    void PushBack(Actor* const& effect);
};

class BattleEffectSpawnerF136 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer,
               unsigned char flagA, unsigned char flagB, const float* parameters,
               const void* transform, unsigned char mode);
public:
    // Observed fields; meanings not yet known.
    EffectFactoryF136* field000;
};

#endif
