#ifndef TH075_EFFECT_MANAGER_LIFETIME_F161_HPP
#define TH075_EFFECT_MANAGER_LIFETIME_F161_HPP

#include <deque>
#include "Actor.hpp"

class Fighter;
class CharacterObject;

// Native 0x54-byte Fighter-owned manager: one bound Fighter pointer followed
// by four complete 20-byte VC7.1 deques of character object pointers. Fighter initialization
// constructs it at +0x2EC; later code accesses it through that owned pointer.
class EffectManagerLifetimeF161 {
public:
    ~EffectManagerLifetimeF161();
    void BindFighter(Fighter* fighter);
    void DeleteFourLists();
    void AdvanceAll();             // 0045BDB0, updates and prunes all four effect lists
    void DispatchSelected(signed char layer);  // 0045BC30, per-layer render
    void DispatchAll();           // 0045BCE0, four layers of overlay renders
    void Spawn(short effect, float x, float y, signed char facing, signed char layer,
               unsigned char flagA, unsigned char flagB, const float* parameters,
               const void* transform, unsigned char mode);

private:
    friend class Fighter;
    EffectManagerLifetimeF161();
    EffectManagerLifetimeF161(const EffectManagerLifetimeF161&);
    EffectManagerLifetimeF161& operator=(const EffectManagerLifetimeF161&);

    Fighter* fighter_;
    std::deque<CharacterObject*> entries_[4];
};

typedef char EffectManagerLifetimeF161SizeCheck[
    sizeof(EffectManagerLifetimeF161) == 0x54 ? 1 : -1];

#endif
