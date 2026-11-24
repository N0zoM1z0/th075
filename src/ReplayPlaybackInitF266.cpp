#include "ReplayBrowserScene.hpp"
#include "Fighter.hpp"
#include "PlayerState.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>

extern const char g_ReplayCatalogFileAt00657FC0[];
extern const char g_ReplayCatalogRootAt00657FB8[];
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
    field051=0;
    field048=g_ReplayControllerAt0067162C;
    field04C=5;
}
