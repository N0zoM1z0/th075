#include "EffectManagerLifetimeF161.hpp"
#include "FighterVirtualActionsF159.hpp"

EffectManagerLifetimeF161::EffectManagerLifetimeF161()
{
    for (int index = 0; index < 4; ++index) {
        entries_[index].clear();
    }
}

void EffectManagerLifetimeF161::BindFighter(Fighter* fighter)
{
    fighter_ = fighter;
}

EffectManagerLifetimeF161::~EffectManagerLifetimeF161()
{
    reinterpret_cast<RoundResetEffectsF159*>(this)->DeleteFourLists();
}
