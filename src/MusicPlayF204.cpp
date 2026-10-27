#include <windows.h>
#include <stdio.h>

// External, target-anchored format/path strings. This file does not define
// the filename data or the audio/progress resource owners.
extern const char g_WaveFormatAAt00657A7C[];
extern const char g_WaveFormatBAt00657A90[];
extern const char g_WaveFormatCAt00657AA4[];
extern const char g_WaveOpeningAt00657AB8[];
extern const char g_WaveEndingAt00657AD0[];
extern const char g_WaveFormatDefaultAt00657AE8[];
extern const char g_NormalSoundFolderAt00657AFC[];
extern const char g_EndingSoundFolderAt00657B04[];
extern signed char g_FrameClockModeAt0066C238;

class MusicProgressArchiveF204 {
public:
    void MarkPlayed(int item);
};
extern MusicProgressArchiveF204 g_MusicProgressAt006718F8;
namespace AudioStreamF204 {
void QueueArchiveEntry(const char*, int, const char*);
}

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
        AudioStreamF204::QueueArchiveEntry(wavePath, 2, g_NormalSoundFolderAt00657AFC);
    else
        AudioStreamF204::QueueArchiveEntry(wavePath, 0, g_EndingSoundFolderAt00657B04);

    if (g_FrameClockModeAt0066C238 != 2 &&
        g_FrameClockModeAt0066C238 != 4)
        g_MusicProgressAt006718F8.MarkPlayed(track + 100);
}
}
