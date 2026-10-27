#include <windows.h>

// Independently observed config bytes, not a source-level complete data
// owner. Extern declarations allocate no storage.
extern BYTE g_SettingsBlockAt00671440[];
extern BYTE g_OptionsFlagAt00671604;
extern BYTE g_SettingsByteAt006714D2;
extern BYTE g_OptionsFlagAt00671430;
extern BYTE g_SettingsFlagAt00671605;
extern BYTE g_SettingsByteAt006714B5;
extern BYTE g_SettingsByteAt006714A0;
extern BYTE g_OptionsModeAt006714D0;
extern BYTE g_OptionsFlagAt00671428;
extern BYTE g_StreamVolumeAt006714B7;
extern BYTE g_SoundVolumeAt006714B6;

namespace GameConfigF193 {
void ReadIni()
{
    DWORD readSize;
    HANDLE file = CreateFileA("config.ini", GENERIC_READ, 0, 0,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    ReadFile(file, g_SettingsBlockAt00671440, 0x50, &readSize, 0);
    ReadFile(file, &g_OptionsFlagAt00671604, 1, &readSize, 0);
    ReadFile(file, &g_SettingsByteAt006714D2, 1, &readSize, 0);
    g_SettingsByteAt006714D2 = 1;
    ReadFile(file, &g_OptionsFlagAt00671430, 1, &readSize, 0);
    ReadFile(file, &g_SettingsFlagAt00671605, 1, &readSize, 0);
    ReadFile(file, &g_SettingsByteAt006714B5, 1, &readSize, 0);
    ReadFile(file, &g_SettingsByteAt006714A0, 1, &readSize, 0);
    ReadFile(file, &g_OptionsModeAt006714D0, 1, &readSize, 0);
    ReadFile(file, &g_OptionsFlagAt00671428, 1, &readSize, 0);
    ReadFile(file, &g_StreamVolumeAt006714B7, 1, &readSize, 0);
    ReadFile(file, &g_SoundVolumeAt006714B6, 1, &readSize, 0);
    CloseHandle(file);
}
}
