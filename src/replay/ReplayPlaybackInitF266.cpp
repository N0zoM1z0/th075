#include "replay/ReplayBrowserScene.hpp"
#include "battle/Fighter.hpp"
#include "battle/PlayerState.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <windows.h>

extern const char g_ReplayCatalogFileAt00657FC0[] = "data\\system\\replay.dat";
extern const char g_ReplayCatalogRootAt00657FB8[] = "datab";
unsigned short g_ReplayControllerAt0067162C;

ReplayBrowserScene::ReplayBrowserScene()
{
    filenames.clear();
    texture=new TextureManagerF198();
    texture->AllocateUnformattedSlots(3);
    texture->LoadDefault(g_ReplayCatalogFileAt00657FC0,g_ReplayCatalogRootAt00657FB8);
    if (g_BattleFightersAt00671418[0]) {
        delete g_BattleFightersAt00671418[0];
        g_BattleFightersAt00671418[0]=0;
    }
    if (g_BattleFightersAt00671418[1]) {
        delete g_BattleFightersAt00671418[1];
        g_BattleFightersAt00671418[1]=0;
    }
    ScanFiles();
    choosingRecord=0;
    selectedFile=g_ReplayControllerAt0067162C;
    displayAlpha=5;
}
