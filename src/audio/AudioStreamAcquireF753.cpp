#include <windows.h>
#include "audio/AudioControl.hpp"
#include "audio/AudioStream.hpp"
#include "audio/SoundBank.hpp"

SoundBank::SoundBank() {
    if (audioClientCount == 0) {
        audioQueue.clear();
        if (audioWorkerHandle == 0) {
            audioWorkerHandle = CreateThread(0, 0, AudioControl407CA0::Worker,
                                             0, 0, &audioWorkerId);
            SetThreadPriority(audioWorkerHandle, 15);
        }
    }
    buffers.clear();
    ++audioClientCount;
}
