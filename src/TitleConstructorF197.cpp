#include "BattleSessionState.hpp"
#include "TextureManagerF198.hpp"
#include "TitleScene.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <d3d8.h>

extern const char g_TitleTextureDataAt006582F0[];
extern const char g_TitleTextureRootAt006582E8[];
extern unsigned char g_TitleMenuSelectionAt00671630;
extern signed char g_ChosenPlayersAt006714C8[2];

TitleScene::TitleScene()
{
    field010 = timeGetTime();
    field00C = timeGetTime() - field010;
    textures = new TextureManagerF198();
    static_cast<TextureManagerF198*>(textures)->AllocateUnformattedSlots(4);
    static_cast<TextureManagerF198*>(textures)->LoadDefault(
        g_TitleTextureDataAt006582F0, g_TitleTextureRootAt006582E8);
    field014 = 0;
    field018 = 0;
    field020 = 255;
    field021 = 5;
    field022 = 5;
    field023 = 5;
    menuIndex = g_TitleMenuSelectionAt00671630;
    itemDelay[0] = 0;
    itemDelay[1] = 15;
    itemDelay[2] = 30;
    itemDelay[3] = 45;
    itemDelay[4] = 60;
    itemDelay[5] = 45;
    itemDelay[6] = 60;
    itemDelay[7] = 75;
    itemDelay[8] = 90;
    itemDelay[9] = 75;
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
    g_ChosenPlayersAt006714C8[0] = 0;
    g_ChosenPlayersAt006714C8[1] = 0;
    g_StageSelectionAt0067161D = 0;
    field01C = 0;
}
