#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

// These interfaces are pointer-only views. Their complete owners are unknown;
// never instantiate or embed them.
class AudioStreamRefill408BD0 {
public:
    void Refill(DWORD);
};
class AudioQueue407CA0 {
public:
    unsigned int Size();
    AudioStreamRefill408BD0& Front();
    void PopFront();
    void Clear();
};
// An external unsized object-representation anchor declares no queue storage.
extern BYTE audioQueueStorage[];
extern signed char masterVolume;
extern BYTE audioPlaying;
extern BYTE audioFading;
extern HANDLE audioWorkerEvent;
#define QUEUE reinterpret_cast<AudioQueue407CA0*>(audioQueueStorage)
#define FRONT_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(&QUEUE->Front()) + offset))
#define FRONT_BUFFER FRONT_FIELD(IDirectSoundBuffer8*, 0)
#define RECORD_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(record) + offset))
#define RECORD_BUFFER RECORD_FIELD(IDirectSoundBuffer8*, 0)

namespace AudioControl407CA0 {
void __cdecl ClearPlayback() {
    audioPlaying = 0;
    audioFading = 0;
    QUEUE->Clear();
}
void __cdecl Start() {
    if (QUEUE->Size() > 0 && FRONT_BUFFER) {
        if (masterVolume == 0)
            FRONT_BUFFER->SetVolume(DSBVOLUME_MIN);
        else
            FRONT_BUFFER->SetVolume((masterVolume - 100) * 50);
        FRONT_BUFFER->Play(0, 0, DSBPLAY_LOOPING);
        audioPlaying = 1;
    }
}
void __cdecl Stop() {
    audioPlaying = 0;
    audioFading = 0;
    if (QUEUE->Size() > 0 && FRONT_BUFFER) {
        FRONT_BUFFER->Stop();
        QUEUE->PopFront();
    }
}
void __cdecl ApplyVolumeOffset(LONG offset) {
    if (QUEUE->Size() > 0 && FRONT_BUFFER) {
        LONG volume = (masterVolume - 100) * 50 + offset;
        if (volume < DSBVOLUME_MIN || masterVolume == 0)
            volume = DSBVOLUME_MIN;
        if (volume > DSBVOLUME_MAX)
            volume = DSBVOLUME_MAX;
        FRONT_BUFFER->SetVolume(volume);
    }
}
void __cdecl ScheduleFade(LONG target, LONG step, BYTE stopAfter, BYTE startNext) {
    if (QUEUE->Size() > 0) {
        if (audioPlaying) {
            if (FRONT_BUFFER) {
                FRONT_FIELD(LONG, 48) = target;
                FRONT_FIELD(LONG, 52) = step;
                FRONT_FIELD(BYTE, 56) = stopAfter;
                FRONT_FIELD(BYTE, 57) = startNext;
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
                if (FRONT_BUFFER) {
                    AudioStreamRefill408BD0* record = &QUEUE->Front();
                    if (RECORD_FIELD(DWORD, 8) > 0) {
                        record->Refill(0x20000);
                        RECORD_BUFFER->GetStatus(&status);
                        if ((status & DSBSTATUS_PLAYING) == 0) {
                            audioPlaying = 0;
                            audioFading = 0;
                            Stop();
                        }
                    } else {
                        if (RECORD_FIELD(DWORD, 40)) {
                            if (RECORD_FIELD(DWORD, 32) > 0) {
                                RECORD_BUFFER->GetCurrentPosition(0, &position);
                                if (position > RECORD_FIELD(DWORD, 32))
                                    RECORD_BUFFER->SetCurrentPosition(position - RECORD_FIELD(DWORD, 36));
                            }
                        } else {
                            RECORD_BUFFER->GetStatus(&status);
                            if ((status & DSBSTATUS_PLAYING) == 0)
                                audioPlaying = 0;
                        }
                    }
                    if (audioFading) {
                        if (RECORD_BUFFER)
                            ApplyVolumeOffset(RECORD_FIELD(LONG, 44));
                        RECORD_FIELD(LONG, 44) += RECORD_FIELD(LONG, 52) * 4;
                        if (RECORD_FIELD(LONG, 52) < 0) {
                            if (RECORD_FIELD(LONG, 44) < RECORD_FIELD(LONG, 48) ||
                                RECORD_FIELD(LONG, 44) <= DSBVOLUME_MIN)
                                audioFading = 0;
                        } else {
                            if (RECORD_FIELD(LONG, 44) < RECORD_FIELD(LONG, 48) ||
                                RECORD_FIELD(LONG, 44) >= 0) {
                                if (RECORD_FIELD(LONG, 44) >= 0)
                                    RECORD_FIELD(LONG, 44) = 0;
                                audioFading = 0;
                            }
                        }
                        if (!audioFading && RECORD_FIELD(BYTE, 56)) {
                            if (RECORD_FIELD(BYTE, 57)) {
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
