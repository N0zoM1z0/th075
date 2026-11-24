#pragma once

#include <windows.h>

namespace AudioVolume4073B0 {
    void SetSoundBankVolume(signed char volume);
    void SetStreamVolume(signed char volume);
}

namespace AudioControl407CA0 {
    void ClearPlayback();
    void Start();
    void Stop();
    void ApplyVolumeOffset(LONG offset);
    void ScheduleFade(LONG target, LONG step, BYTE stopAfter, BYTE startNext);
    DWORD WINAPI Worker(LPVOID argument);
}

namespace AudioQueueArchiveF760 {
    void QueueArchiveEntry(const char* filename, int mode, const char* archive);
}

namespace MusicF204 {
    void PlayTrackByIndex(int track);
}

namespace MusicF205 {
    void ScheduleTransitionFade();
}
