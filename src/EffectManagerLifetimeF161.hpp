#ifndef TH075_EFFECT_MANAGER_LIFETIME_F161_HPP
#define TH075_EFFECT_MANAGER_LIFETIME_F161_HPP

#include <deque>

class Fighter;

// Observed 0x54-byte allocation: one bound Fighter pointer followed by four
// complete 20-byte vendor deque<void*> members. This is a pointer-only view of
// target-owned storage; never construct or embed it in reconstructed objects.
class EffectManagerLifetimeF161 {
public:
    ~EffectManagerLifetimeF161();
    void BindFighter(Fighter* fighter);
    void DeleteFourLists();

private:
    EffectManagerLifetimeF161();
    EffectManagerLifetimeF161(const EffectManagerLifetimeF161&);
    EffectManagerLifetimeF161& operator=(const EffectManagerLifetimeF161&);

    Fighter* fighter_;
    std::deque<void*> entries_[4];
};

typedef char EffectManagerLifetimeF161SizeCheck[
    sizeof(EffectManagerLifetimeF161) == 0x54 ? 1 : -1];

#endif
