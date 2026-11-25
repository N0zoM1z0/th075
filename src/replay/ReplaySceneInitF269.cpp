#include "ui/NameEntryScenes.hpp"
#include "battle/PlayerState.hpp"
#include "engine/GameSharedState.hpp"
#include "engine/GameProgress.hpp"
#include "battle/Fighter.hpp"
#include "replay/ReplayRecords.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <windows.h>

extern const char g_ReplaySceneRootAt00657F44[] = "data";
extern const char g_ReplaySceneFileAt00657F4C[] = "data\\system\\replay.dat";

PlayerNameEntryScene::PlayerNameEntryScene()
{
    texture=new TextureManagerF198();
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplaySceneFileAt00657F4C,g_ReplaySceneRootAt00657F44);
    field010 = 0;
    field012 = 0;
    field014 = 0;
    g_GameProgress.SetSelection(g_PlayerIdAt006714C8[0],static_cast<unsigned char>(g_OptionsModeAt006714D0));
    selectedRecord = g_GameProgress.GetSelectedRecordAddress();
    rank = selectedRecord->InsertRankedScore(g_BattleFightersAt00671418[0]->score);
    g_GameProgress.StoreWorkingEightBytes(rank);
    pathIndex = g_ReplayRecords.FindAvailablePath(replayPath);
}
