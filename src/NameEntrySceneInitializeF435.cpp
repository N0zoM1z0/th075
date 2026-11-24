#include "NameEntryScenes.hpp"
#include "TextureManagerF198.hpp"
#include "ReplaySegmentedQueueF219.hpp"
extern signed char g_ReplayNameModeAt006714CE;
extern char g_ReplayDataPathAt00657F84[];
extern char g_ReplayArchiveRootAt00657F7C[];

SharedNameEntryScene::SharedNameEntryScene() {
    texture = new TextureManagerF198;
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplayDataPathAt00657F84,g_ReplayArchiveRootAt00657F7C);
    field00E=0;
    field010=0;
    field012=0;
    field014=0;
    if(g_ReplayNameModeAt006714CE<0) field00C=1;
    else field00C=0;
    pathIndex = g_ReplayRecords.FindAvailablePath(replayPath);
}
