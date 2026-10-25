#ifndef TH075_BATTLE_EFFECT_SPAWNER_F136_HPP
#define TH075_BATTLE_EFFECT_SPAWNER_F136_HPP

// Pointer-only interfaces. Never construct or embed these private owners;
// their complete layouts, original names and allocation sizes remain unknown.
class SpawnedEffectF136 {
public:
    void ResetPrimaryCounters(short effect);
    void ResetNodeTransform(float x, float y, float z);
};

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
    virtual void Acquire(SpawnedEffectF136** output);
};

class EffectDequeF136 {
public:
    void PushBack(SpawnedEffectF136* const& effect);
};

class BattleEffectSpawnerF136 {
public:
    void Spawn(short effect, float x, float y, signed char facing, signed char layer,
               unsigned char flagA, unsigned char flagB, const float* parameters,
               const void* transform, unsigned char mode);
};

#endif
