#include "battle/BattleResultState.hpp"
#include "ui/NameEntryScenes.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "replay/ReplaySegmentedQueueF219.hpp"
extern const char g_ReplayDataPathAt00657F84[] = "data\\system\\replay.dat";
extern const char g_ReplayArchiveRootAt00657F7C[] = "datab";

SharedNameEntryScene::SharedNameEntryScene() {
    texture = new TextureManagerF198;
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplayDataPathAt00657F84,g_ReplayArchiveRootAt00657F7C);
    field00E=0;
    field010=0;
    field012=0;
    field014=0;
    if(g_StateReturnFlag<0) field00C=1;
    else field00C=0;
    pathIndex = g_ReplayRecords.FindAvailablePath(replayPath);
}
