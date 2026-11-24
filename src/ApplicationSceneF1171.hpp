#pragma once

#include "GameDefaultsF193.hpp"

// The application uses the scene's three virtual slots through this base.
class GameScenesF1171 {
    GameDefaultsF193 defaults;

public:
    virtual ~GameScenesF1171();
    virtual unsigned short Advance();
    virtual void DrawCurrent();
    unsigned short TranslateState(unsigned short mode);
};

typedef char ApplicationSceneBaseSize[(sizeof(GameScenesF1171) == 8) ? 1 : -1];
