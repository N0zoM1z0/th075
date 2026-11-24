#pragma once
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"

#include "Fighter.hpp"

class FighterHitResponseF164 : public Fighter {
public:
    bool IsState150To199();
    bool IsState95To99();
    unsigned char SelectHitResponse(unsigned int flags);
};
