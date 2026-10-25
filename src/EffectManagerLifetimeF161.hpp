#ifndef TH075_EFFECT_MANAGER_LIFETIME_F161_HPP
#define TH075_EFFECT_MANAGER_LIFETIME_F161_HPP

#include <deque>

class FighterBaseActionsF159;

// Observed lifetime prefix only: bound fighter followed by four complete
// vendor containers. Never construct or embed this view, infer a complete
// game-owner size, or use it to allocate original objects.
class EffectManagerLifetimeF161 {
public:
    ~EffectManagerLifetimeF161();
    void BindFighter(FighterBaseActionsF159* fighter);

private:
    EffectManagerLifetimeF161();
    EffectManagerLifetimeF161(const EffectManagerLifetimeF161&);
    EffectManagerLifetimeF161& operator=(const EffectManagerLifetimeF161&);

    FighterBaseActionsF159* fighter_;
    std::deque<void*> entries_[4];
};

#endif
