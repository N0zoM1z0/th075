#include <windows.h>
#include <string.h>

// Borrowed global storage anchors only; these do not define or allocate any
// original data or assert a complete settings structure layout.
extern unsigned int g_GameDefaultsUseCountAt00671614;
extern unsigned char g_KeyBindingsAt00671440[];
extern unsigned char g_CharacterNamesAt006714D8[];
extern DWORD g_SelectedCharacterAAt00671418;
extern DWORD g_SelectedCharacterBAt0067141C;
extern unsigned char g_OptionFlagAt00671430;
extern unsigned char g_OptionFlagAt00671604;
extern unsigned char g_OptionFlagAt006714D2;
extern unsigned char g_OptionFlagAt00671605;
extern unsigned char g_OptionFlagAt006714B5;
extern unsigned char g_OptionFlagAt006714A0;
extern unsigned char g_OptionVolumeAt006714B6;
extern unsigned char g_OptionModeAt006714D0;
extern unsigned char g_GameSettingAt00671435;
extern unsigned char g_GameSettingAt00671434;
extern unsigned char g_GameSettingAt00671438;
namespace GameConfigF193 { void ReadIni(); }

class GameDefaultsF193 {
public:
    GameDefaultsF193();
};
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
        g_SelectedCharacterAAt00671418 = 0;
        g_SelectedCharacterBAt0067141C = 0;
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
        g_OptionFlagAt00671430 = 1;
        g_OptionFlagAt00671604 = 1;
        g_OptionFlagAt006714D2 = 1;
        g_OptionFlagAt00671605 = 0;
        g_OptionFlagAt006714B5 = 0;
        g_OptionFlagAt006714A0 = 0;
        g_OptionVolumeAt006714B6 = 100;
        g_OptionModeAt006714D0 = 1;
        g_GameSettingAt00671435 = 2;
        g_GameSettingAt00671434 = g_GameSettingAt00671435;
        g_GameSettingAt00671438 = (g_GameSettingAt00671438 = 0);
        GameConfigF193::ReadIni();
    }
    ++g_GameDefaultsUseCountAt00671614;
}
#undef NAME
#undef SET_BYTE
#undef SET_DWORD
