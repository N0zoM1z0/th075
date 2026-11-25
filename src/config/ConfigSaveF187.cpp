#include "config/GameConfigStorage.hpp"
#include "engine/GameSharedState.hpp"
#include "config/DisplayOptions.hpp"
#include <windows.h>

// These are independently observed slices of settings, not a synthesized
// complete owner, and this translation unit defines no target data.
extern BYTE g_OptionsFlagAt00671604;
extern BYTE g_SettingsByteAt006714D2;
extern BYTE g_OptionsFlagAt00671430;
extern BYTE g_OptionsFlagAt00671428;

namespace OptionsSettingsF186 {
void SaveConfiguration()
{
    DWORD written;
    HANDLE file = CreateFileA("config.ini", GENERIC_WRITE, 0, 0,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    SetFilePointer(file, 0, 0, FILE_BEGIN);
    WriteFile(file, g_PlayerKeyBindings, sizeof(g_PlayerKeyBindings), &written, 0);
    WriteFile(file, &g_OptionsFlagAt00671604, 1, &written, 0);
    WriteFile(file, &g_SettingsByteAt006714D2, 1, &written, 0);
    g_SettingsByteAt006714D2 = 1;
    WriteFile(file, &g_OptionsFlagAt00671430, 1, &written, 0);
    WriteFile(file, &DisplayOptions::startFullscreen, 1, &written, 0);
    WriteFile(file, &DisplayOptions::squareTextures, 1, &written, 0);
    WriteFile(file, &DisplayOptions::use16BitBackBuffer, 1, &written, 0);
    WriteFile(file, &g_OptionsModeAt006714D0, 1, &written, 0);
    WriteFile(file, &g_OptionsFlagAt00671428, 1, &written, 0);
    WriteFile(file, &g_StreamVolumeAt006714B7, 1, &written, 0);
    WriteFile(file, &g_SoundVolumeAt006714B6, 1, &written, 0);
    CloseHandle(file);
}
}
