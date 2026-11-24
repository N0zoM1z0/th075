#include "BattleSessionState.hpp"
#include "GameProgress.hpp"
#include "AudioControl.hpp"
#include <windows.h>
#include <stdio.h>

extern const char g_WaveFormatAAt00657A7C[] = "wave\\bgm\\%02da.wav";
extern const char g_WaveFormatBAt00657A90[] = "wave\\bgm\\%02db.wav";
extern const char g_WaveFormatCAt00657AA4[] = "wave\\bgm\\%02dc.wav";
extern const char g_WaveOpeningAt00657AB8[] = "wave\\bgm\\sys00_op.wav";
extern const char g_WaveEndingAt00657AD0[] = "wave\\bgm\\sys99_ed.wav";
extern const char g_WaveFormatDefaultAt00657AE8[] = "wave\\bgm\\%02d.wav";
extern const char g_NormalSoundFolderAt00657AFC[] = "sound";
extern const char g_EndingSoundFolderAt00657B04[] = "sound";


namespace MusicF204 {
void PlayTrackByIndex(int track)
{
    char wavePath[128];
    if (track < 0)
        return;
    if (track < 10)
        sprintf(wavePath, g_WaveFormatAAt00657A7C, track);
    else if (track < 20)
        sprintf(wavePath, g_WaveFormatBAt00657A90, track - 10);
    else if (track < 30)
        sprintf(wavePath, g_WaveFormatCAt00657AA4, track - 20);
    else if (track == 40)
        sprintf(wavePath, g_WaveOpeningAt00657AB8);
    else if (track == 41)
        sprintf(wavePath, g_WaveEndingAt00657AD0);
    else
        sprintf(wavePath, g_WaveFormatDefaultAt00657AE8, track);

    if (track != 41)
        AudioQueueArchiveF760::QueueArchiveEntry(wavePath, 2, g_NormalSoundFolderAt00657AFC);
    else
        AudioQueueArchiveF760::QueueArchiveEntry(wavePath, 0, g_EndingSoundFolderAt00657B04);

    if (g_ReplayModeAt0066C238 != 2 &&
        g_ReplayModeAt0066C238 != 4)
        g_GameProgress.SetUnlockBit(track + 100);
}
}
