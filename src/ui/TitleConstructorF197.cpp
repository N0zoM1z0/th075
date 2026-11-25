#include "battle/PlayerState.hpp"
#include "battle/BattleSessionState.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "ui/TitleScene.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>

extern const char g_TitleTextureDataAt006582F0[] = "data\\system\\title.dat";
extern const char g_TitleTextureRootAt006582E8[] = "data";

TitleScene::TitleScene()
{
    openedAtMs = timeGetTime();
    elapsedMs = timeGetTime() - openedAtMs;
    textures = new TextureManagerF198();
    textures->AllocateUnformattedSlots(4);
    textures->LoadDefault(
        g_TitleTextureDataAt006582F0, g_TitleTextureRootAt006582E8);
    field014 = 0;
    verticalInput = 0;
    backgroundAlpha = 255;
    logoAlpha = 5;
    footerAlpha = 5;
    menuAlpha = 5;
    menuIndex = reinterpret_cast<const unsigned char&>(g_TitleSelectionAt00671630);
    itemSlideX[0] = 0;
    itemSlideX[1] = 15;
    itemSlideX[2] = 30;
    itemSlideX[3] = 45;
    itemSlideX[4] = 60;
    itemSlideX[5] = 45;
    itemSlideX[6] = 60;
    itemSlideX[7] = 75;
    itemSlideX[8] = 90;
    itemSlideX[9] = 75;
    itemAlpha[0] = 0;
    itemAlpha[1] = 0;
    itemAlpha[2] = 0;
    itemAlpha[3] = 0;
    itemAlpha[4] = 0;
    itemAlpha[5] = 0;
    itemAlpha[6] = 0;
    itemAlpha[7] = 0;
    itemAlpha[8] = 0;
    itemAlpha[9] = 0;
    g_PlayerIdAt006714C8[0] = 0;
    g_PlayerIdAt006714C8[1] = 0;
    g_StageSelectionAt0067161D = 0;
    escapeHeldFrames = 0;
}
