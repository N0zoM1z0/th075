#include "PlayerState.hpp"
#include "GameConfigStorage.hpp"
#include "GameSharedState.hpp"
#include "DisplayOptions.hpp"
#include "GameDefaultsF193.hpp"
#include <windows.h>
#include <string.h>

unsigned int g_GameDefaultsUseCountAt00671614;
extern unsigned char g_CharacterNamesAt006714D8[];
extern unsigned char g_OptionsFlagAt00671430;
extern unsigned char g_OptionsFlagAt00671604;
extern unsigned char g_SettingsByteAt006714D2;
namespace GameConfigF193 { void ReadIni(); }

#define SET_DWORD(off,val) (*reinterpret_cast<DWORD*>(g_KeyBindingsAt00671440 + (off)) = (val))
#define SET_BYTE(off,val) (g_KeyBindingsAt00671440[(off)] = (val))
#define NAME(i) (reinterpret_cast<char*>(g_CharacterNamesAt006714D8+(i)*20))

GameDefaultsF193::GameDefaultsF193()
{
    if (g_GameDefaultsUseCountAt00671614 == 0) {
        SET_BYTE(0, 255);
        SET_DWORD(4, 0x22);
        SET_DWORD(8, 0x24);
        SET_DWORD(12, 0x15);
        SET_DWORD(16, 0x31);
        SET_DWORD(20, 0x10);
        SET_DWORD(24, 0x11);
        SET_DWORD(28, 0x12);
        SET_DWORD(32, 0x20);
        SET_BYTE(40, 255);
        SET_DWORD(44, 0xcb);
        SET_DWORD(48, 0xcd);
        SET_DWORD(52, 200);
        SET_DWORD(56, 0xd0);
        SET_DWORD(72, 0x1b);
        SET_DWORD(60, 0x91);
        SET_DWORD(68, 0x1a);
        SET_DWORD(64, 0x1b);
        g_BattleFightersAt00671418[0] = 0;
        g_BattleFightersAt00671418[1] = 0;
        strcpy(NAME(0), "reimu");
        strcpy(NAME(1), "marisa");
        strcpy(NAME(2), "sakuya");
        strcpy(NAME(3), "alice");
        strcpy(NAME(4), "patchouli");
        strcpy(NAME(5), "youmu");
        strcpy(NAME(6), "remilia");
        strcpy(NAME(7), "yuyuko");
        strcpy(NAME(8), "yukari");
        strcpy(NAME(9), "suika");
        strcpy(NAME(10), "meiling");
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
#undef NAME
#undef SET_BYTE
#undef SET_DWORD
