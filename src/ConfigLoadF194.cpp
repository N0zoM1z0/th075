#include "GameSharedState.hpp"
#include "DisplayOptions.hpp"
#include <windows.h>

namespace DisplayOptions
{
    bool startFullscreen;
    bool squareTextures;
    bool use16BitBackBuffer;
}

BYTE g_KeyBindingsAt00671440[0x50];
BYTE g_OptionsFlagAt00671604;
BYTE g_SettingsByteAt006714D2;
BYTE g_OptionsFlagAt00671430;
signed char g_OptionsModeAt006714D0;
BYTE g_OptionsFlagAt00671428;
BYTE g_StreamVolumeAt006714B7;
BYTE g_SoundVolumeAt006714B6;

signed char g_CombatMode;
signed char g_StageAt0067161E;
unsigned char g_StateFadeAlpha;
int g_StateResetCounter;

namespace GameConfigF193 {
void ReadIni()
{
    DWORD readSize;
    HANDLE file = CreateFileA("config.ini", GENERIC_READ, 0, 0,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    ReadFile(file, g_KeyBindingsAt00671440, 0x50, &readSize, 0);
    ReadFile(file, &g_OptionsFlagAt00671604, 1, &readSize, 0);
    ReadFile(file, &g_SettingsByteAt006714D2, 1, &readSize, 0);
    g_SettingsByteAt006714D2 = 1;
    ReadFile(file, &g_OptionsFlagAt00671430, 1, &readSize, 0);
    ReadFile(file, &DisplayOptions::startFullscreen, 1, &readSize, 0);
    ReadFile(file, &DisplayOptions::squareTextures, 1, &readSize, 0);
    ReadFile(file, &DisplayOptions::use16BitBackBuffer, 1, &readSize, 0);
    ReadFile(file, &g_OptionsModeAt006714D0, 1, &readSize, 0);
    ReadFile(file, &g_OptionsFlagAt00671428, 1, &readSize, 0);
    ReadFile(file, &g_StreamVolumeAt006714B7, 1, &readSize, 0);
    ReadFile(file, &g_SoundVolumeAt006714B6, 1, &readSize, 0);
    CloseHandle(file);
}
}
