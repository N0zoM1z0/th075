#include "AudioControl.hpp"
#ifndef TH075_BATTLE_STATE_MACHINE_HPP
#define TH075_BATTLE_STATE_MACHINE_HPP
#include "BattleFrame.hpp"
#include "BattleScene.hpp"
// Partial interfaces, used only on existing receivers.
class StatePatternActor { public: void ChoosePattern(); };
class StateReplay { public: void AppendRecord(); bool IsInputEmpty(); };
class StateCapture { public: void InstallCallback(); void EnableDirectDraw(); void CapturePrimary(); };
class StateRecords { public: void IncrementCounter(signed char first, signed char second); };
class StateEffects { public: void ReleaseEntries(); };
extern StateReplay g_StateReplay;
extern StateCapture *g_StateCapture;
extern signed char g_StateReplayLimit;
extern signed char g_StateRecordLimit;
extern signed char g_StateContinueCount;
extern signed char g_StateReturnFlag;
extern signed char g_StatePlayerIds[2];
extern unsigned char g_StateReplayChanged;
extern unsigned char g_StateFadeAlpha;
extern unsigned long g_StateScoreThreshold;
extern int g_StateStageTotal;
extern int g_StateResetCounter;
extern float g_StateFadeValue;
#endif
