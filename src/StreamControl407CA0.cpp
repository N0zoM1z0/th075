#include "AudioStream.hpp"
#include "AudioControl.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

// These interfaces are pointer-only views. Their complete owners are unknown;
// never instantiate or embed them.
class AudioQueue407CA0 {
public:
    unsigned int Size();
    AudioStream& Front();
    void PopFront();
    void Clear();
};
// An external unsized object-representation anchor declares no queue storage.
extern BYTE audioQueueStorage[];
extern signed char masterVolume;
int audioClientCount;
BYTE audioPlaying;
BYTE audioFading;
HANDLE audioWorkerEvent;
HANDLE audioWorkerHandle;
DWORD audioWorkerId;
#define QUEUE reinterpret_cast<AudioQueue407CA0*>(audioQueueStorage)

namespace AudioControl407CA0 {
void __cdecl ClearPlayback() {
    audioPlaying = 0;
    audioFading = 0;
    QUEUE->Clear();
}
void __cdecl Start() {
    if (QUEUE->Size() > 0 && QUEUE->Front().buffer) {
        if (masterVolume == 0)
            QUEUE->Front().buffer->SetVolume(DSBVOLUME_MIN);
        else
            QUEUE->Front().buffer->SetVolume((masterVolume - 100) * 50);
        QUEUE->Front().buffer->Play(0, 0, DSBPLAY_LOOPING);
        audioPlaying = 1;
    }
}
void __cdecl Stop() {
    audioPlaying = 0;
    audioFading = 0;
    if (QUEUE->Size() > 0 && QUEUE->Front().buffer) {
        QUEUE->Front().buffer->Stop();
        QUEUE->PopFront();
    }
}
void __cdecl ApplyVolumeOffset(LONG offset) {
    if (QUEUE->Size() > 0 && QUEUE->Front().buffer) {
        LONG volume = (masterVolume - 100) * 50 + offset;
        if (volume < DSBVOLUME_MIN || masterVolume == 0)
            volume = DSBVOLUME_MIN;
        if (volume > DSBVOLUME_MAX)
            volume = DSBVOLUME_MAX;
        QUEUE->Front().buffer->SetVolume(volume);
    }
}
void __cdecl ScheduleFade(LONG target, LONG step, BYTE stopAfter, BYTE startNext) {
    if (QUEUE->Size() > 0) {
        if (audioPlaying) {
            if (QUEUE->Front().buffer) {
                QUEUE->Front().fadeLimit = target;
                QUEUE->Front().fadeStep = step;
                QUEUE->Front().field038 = stopAfter;
                QUEUE->Front().field039 = startNext;
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
            if (QUEUE->Size() > 0) {
                if (QUEUE->Front().buffer) {
                    AudioStream* record = &QUEUE->Front();
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
