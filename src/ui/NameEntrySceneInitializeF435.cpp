#include "battle/BattleResultState.hpp"
#include "ui/NameEntryScenes.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "replay/ReplayRecords.hpp"
extern const char g_ReplayDataPathAt00657F84[] = "data\\system\\replay.dat";
extern const char g_ReplayArchiveRootAt00657F7C[] = "datab";

SharedNameEntryScene::SharedNameEntryScene() {
    texture = new TextureManagerF198;
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplayDataPathAt00657F84,g_ReplayArchiveRootAt00657F7C);
    glyphColumn=0;
    glyphRow=0;
    nameCursor=0;
    cancelChoice=0;
    if(g_StateReturnFlag<0) confirmingCancel=1;
    else confirmingCancel=0;
    pathIndex = g_ReplayRecords.FindAvailablePath(replayPath);
}
