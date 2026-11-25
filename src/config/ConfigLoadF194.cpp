#include "battle/BattleResultState.hpp"
#include "battle/PlayerState.hpp"
#include "config/GameConfigStorage.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "config/DisplayOptions.hpp"
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

unsigned char g_FramePresentToggle = 1;
signed char g_ReplayModeAt0066C238 = 1;
unsigned char g_SequenceByteAt0066C239 = 1;
unsigned char g_SequenceByteAt0066C23A = 1;
signed char g_SelectedSideAt006714B8;
int g_CumulativeScoreAt006714BC;
signed char g_StageSelectionAt0067161D;
signed char g_CharacterCountAt0067161F;
unsigned char g_StoryResultAt00671621;
unsigned char g_SequenceCounterAt00671622;
signed char g_ContinueCountAt00671623;
unsigned char g_ContinueUsedAt00671624;
unsigned char g_InputCanCancelAt00671632;

signed char g_PlayerIdAt006714C8[2];
signed char g_PlayerAltAt00671610[2];
signed char g_PlayerOtherAt006714CC[2];
signed char g_PlayerRoundAt006714AC[2];
unsigned char g_PlayerDifficultyAt00671438[2];
signed char g_PlayerSettingsAt00671434[2];
short g_RecordSequenceAt006714A4;
Fighter* g_BattleFightersAt00671418[2];

unsigned long g_StateScoreThreshold;
unsigned long g_MaxCombatScore;
short g_MaxComboCount;
signed char g_StateReturnFlag;
unsigned int g_ResultScoreTotalAt0067160C;
unsigned char g_RenderByte0067161C;
signed char g_StoryChoiceAt00671620;

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
