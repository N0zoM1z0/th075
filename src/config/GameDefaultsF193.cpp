#include "battle/PlayerState.hpp"
#include "config/GameConfigStorage.hpp"
#include "engine/GameSharedState.hpp"
#include "config/DisplayOptions.hpp"
#include "config/GameDefaultsF193.hpp"
#include "input/InputDevice.hpp"
#include <windows.h>
#include <string.h>

unsigned int g_GameDefaultsUseCountAt00671614;
char g_CharacterNamesAt006714D8[11][20];
extern unsigned char g_OptionsFlagAt00671430;
extern unsigned char g_OptionsFlagAt00671604;
extern unsigned char g_SettingsByteAt006714D2;
namespace GameConfigF193 { void ReadIni(); }

enum BindingButton { ButtonA, ButtonB, ButtonC, ButtonD };

GameDefaultsF193::GameDefaultsF193()
{
    if (g_GameDefaultsUseCountAt00671614 == 0) {
        g_PlayerKeyBindings[0].device = -1;
        g_PlayerKeyBindings[0].left = DIK_G;
        g_PlayerKeyBindings[0].right = DIK_J;
        g_PlayerKeyBindings[0].up = DIK_Y;
        g_PlayerKeyBindings[0].down = DIK_N;
        g_PlayerKeyBindings[0].buttons[ButtonA] = DIK_Q;
        g_PlayerKeyBindings[0].buttons[ButtonB] = DIK_W;
        g_PlayerKeyBindings[0].buttons[ButtonC] = DIK_E;
        g_PlayerKeyBindings[0].buttons[ButtonD] = DIK_D;
        g_PlayerKeyBindings[1].device = -1;
        g_PlayerKeyBindings[1].left = DIK_LEFT;
        g_PlayerKeyBindings[1].right = DIK_RIGHT;
        g_PlayerKeyBindings[1].up = DIK_UP;
        g_PlayerKeyBindings[1].down = DIK_DOWN;
        g_PlayerKeyBindings[1].buttons[ButtonD] = DIK_RBRACKET;
        g_PlayerKeyBindings[1].buttons[ButtonA] = DIK_AT;
        g_PlayerKeyBindings[1].buttons[ButtonC] = DIK_LBRACKET;
        g_PlayerKeyBindings[1].buttons[ButtonB] = DIK_RBRACKET;
        g_BattleFightersAt00671418[0] = 0;
        g_BattleFightersAt00671418[1] = 0;
        strcpy(g_CharacterNamesAt006714D8[0], "reimu");
        strcpy(g_CharacterNamesAt006714D8[1], "marisa");
        strcpy(g_CharacterNamesAt006714D8[2], "sakuya");
        strcpy(g_CharacterNamesAt006714D8[3], "alice");
        strcpy(g_CharacterNamesAt006714D8[4], "patchouli");
        strcpy(g_CharacterNamesAt006714D8[5], "youmu");
        strcpy(g_CharacterNamesAt006714D8[6], "remilia");
        strcpy(g_CharacterNamesAt006714D8[7], "yuyuko");
        strcpy(g_CharacterNamesAt006714D8[8], "yukari");
        strcpy(g_CharacterNamesAt006714D8[9], "suika");
        strcpy(g_CharacterNamesAt006714D8[10], "meiling");
        g_OptionsFlagAt00671430 = 1;
        g_OptionsFlagAt00671604 = 1;
        g_SettingsByteAt006714D2 = 1;
        DisplayOptions::startFullscreen = false;
        DisplayOptions::squareTextures = false;
        DisplayOptions::use16BitBackBuffer = false;
        g_SoundVolumeAt006714B6 = 100;
        g_OptionsModeAt006714D0 = 1;
        g_PlayerSettingsAt00671434[1] = 2;
        g_PlayerSettingsAt00671434[0] = g_PlayerSettingsAt00671434[1];
        g_PlayerDifficultyAt00671438[0] = (g_PlayerDifficultyAt00671438[0] = 0);
        GameConfigF193::ReadIni();
    }
    ++g_GameDefaultsUseCountAt00671614;
}
