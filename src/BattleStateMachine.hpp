#include "GameSharedState.hpp"
#include "AudioControl.hpp"
#ifndef TH075_BATTLE_STATE_MACHINE_HPP
#define TH075_BATTLE_STATE_MACHINE_HPP
#include "PlayerState.hpp"
#include "BattleSessionState.hpp"
#include "BattleResultState.hpp"
#include "BattleFrame.hpp"
#include "BattleScene.hpp"
// Partial interfaces, used only on existing receivers.
class StateReplay { public: void AppendRecord(); };
extern StateReplay g_StateReplay;
extern float g_StateFadeValue;
#endif
