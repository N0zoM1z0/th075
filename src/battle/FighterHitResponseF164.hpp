#pragma once
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"

#include "battle/Fighter.hpp"

class FighterHitResponseF164 : public Fighter {
public:
    bool IsState150To199();
    bool IsState95To99();
    unsigned char SelectHitResponse(unsigned int flags);
};
