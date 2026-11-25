#include "audio/AudioStream.hpp"
#include "audio/AudioControl.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

extern signed char masterVolume;
int audioClientCount;
BYTE audioPlaying;
BYTE audioFading;
HANDLE audioWorkerEvent;
HANDLE audioWorkerHandle;
DWORD audioWorkerId;
AudioQueue audioQueue;

namespace AudioControl407CA0 {
void __cdecl ClearPlayback() {
    audioPlaying = 0;
    audioFading = 0;
    audioQueue.clear();
}
void __cdecl Start() {
    if (audioQueue.size() > 0 && audioQueue.front().buffer) {
        if (masterVolume == 0)
            audioQueue.front().buffer->SetVolume(DSBVOLUME_MIN);
        else
            audioQueue.front().buffer->SetVolume((masterVolume - 100) * 50);
        audioQueue.front().buffer->Play(0, 0, DSBPLAY_LOOPING);
        audioPlaying = 1;
    }
}
void __cdecl Stop() {
    audioPlaying = 0;
    audioFading = 0;
    if (audioQueue.size() > 0 && audioQueue.front().buffer) {
        audioQueue.front().buffer->Stop();
        audioQueue.pop_front();
    }
}
void __cdecl ApplyVolumeOffset(LONG offset) {
    if (audioQueue.size() > 0 && audioQueue.front().buffer) {
        LONG volume = (masterVolume - 100) * 50 + offset;
        if (volume < DSBVOLUME_MIN || masterVolume == 0)
            volume = DSBVOLUME_MIN;
        if (volume > DSBVOLUME_MAX)
            volume = DSBVOLUME_MAX;
        audioQueue.front().buffer->SetVolume(volume);
    }
}
void __cdecl ScheduleFade(LONG target, LONG step, BYTE stopAfter, BYTE startNext) {
    if (audioQueue.size() > 0) {
        if (audioPlaying) {
            if (audioQueue.front().buffer) {
                audioQueue.front().fadeLimit = target;
                audioQueue.front().fadeStep = step;
                audioQueue.front().field038 = stopAfter;
                audioQueue.front().field039 = startNext;
                audioFading = 1;
            }
        } else {
            audioFading = 0;
            if (startNext)
                Start();
        }
    }
}
DWORD WINAPI Worker(LPVOID) {
    DWORD position;
    DWORD status;
    if (audioWorkerEvent == 0)
        audioWorkerEvent = CreateEventA(0, 0, 0, 0);
    while (1) {
        if (audioPlaying) {
            if (audioQueue.size() > 0) {
                if (audioQueue.front().buffer) {
                    AudioStream* record = &audioQueue.front();
                    if (record->bufferBytes > 0) {
                        record->Refill(0x20000);
                        record->buffer->GetStatus(&status);
                        if ((status & DSBSTATUS_PLAYING) == 0) {
                            audioPlaying = 0;
                            audioFading = 0;
                            Stop();
                        }
                    } else {
                        if (record->loopEnabled) {
                            if (record->loopEnd > 0) {
                                record->buffer->GetCurrentPosition(0, &position);
                                if (position > record->loopEnd)
                                    record->buffer->SetCurrentPosition(position - record->loopLength);
                            }
                        } else {
                            record->buffer->GetStatus(&status);
                            if ((status & DSBSTATUS_PLAYING) == 0)
                                audioPlaying = 0;
                        }
                    }
                    if (audioFading) {
                        if (record->buffer)
                            ApplyVolumeOffset(record->volume);
                        record->volume += record->fadeStep * 4;
                        if (record->fadeStep < 0) {
                            if (record->volume < record->fadeLimit ||
                                record->volume <= DSBVOLUME_MIN)
                                audioFading = 0;
                        } else {
                            if (record->volume < record->fadeLimit ||
                                record->volume >= 0) {
                                if (record->volume >= 0)
                                    record->volume = 0;
                                audioFading = 0;
                            }
                        }
                        if (!audioFading && record->field038) {
                            if (record->field039) {
                                Stop();
                                Start();
                            } else {
                                Stop();
                            }
                        }
                    }
                }
            } else {
                audioPlaying = 0;
            }
        }
        WaitForSingleObject(audioWorkerEvent, 80);
    }
    // The native SDK thread callback has this physical zero-result epilogue;
    // the constant loop does not reach it during ordinary execution.
    return 0;
}
}
