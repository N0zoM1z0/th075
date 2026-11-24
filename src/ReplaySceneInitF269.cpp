#include "PlayerState.hpp"
#include "GameSharedState.hpp"
#include "GameProgress.hpp"
#include "Fighter.hpp"
#include "ReplaySegmentedQueueF219.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>

// Only physical scene-base boundary, game globals and observed file/texture
// interfaces are represented. No complete private scene ABI is assumed.
class ReplayBaseF269 {
    void* configuration;
public:
    ReplayBaseF269();
    virtual ~ReplayBaseF269();
};
extern const char g_ReplaySceneRootAt00657F44[];
extern const char g_ReplaySceneFileAt00657F4C[];
class ReplaySceneInitF269 : public ReplayBaseF269 {
    TextureManagerF198* texture;
    ProgressDifficulty* selectedRecord;
    short field010;
    short field012;
    short field014;
    unsigned char unknown016[2];
    int pathIndex;
    char replayPath[MAX_PATH];
    unsigned char rank;
public:
    ReplaySceneInitF269();
    virtual ~ReplaySceneInitF269();
};
ReplaySceneInitF269::ReplaySceneInitF269()
{
    texture=new TextureManagerF198();
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplaySceneFileAt00657F4C,g_ReplaySceneRootAt00657F44);
    field010 = 0;
    field012 = 0;
    field014 = 0;
    g_GameProgress.SetSelection(g_PlayerIdAt006714C8[0],static_cast<unsigned char>(g_OptionsModeAt006714D0));
    selectedRecord = g_GameProgress.GetSelectedRecordAddress();
    rank = selectedRecord->InsertRankedScore(reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score);
    g_GameProgress.StoreWorkingEightBytes(rank);
    pathIndex = g_ReplayRecords.FindAvailablePath(replayPath);
}
