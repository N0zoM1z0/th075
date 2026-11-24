#pragma once
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"

#include "Fighter.hpp"
#include <deque>

class FighterHitResponseF164 : public Fighter {
public:
    bool IsState150To199();
    bool IsState95To99();
    unsigned char SelectHitResponse(unsigned int flags);
};

// Observed used byte/container views; original global names remain unknown.
extern std::deque<unsigned char> g_ReplayChoicesAt006718CC;
