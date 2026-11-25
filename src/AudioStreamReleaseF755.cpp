#include <windows.h>
#include "AudioStream.hpp"
#include "SoundBank.hpp"
#include <dsound.h>
// R015 original 00407270: complete 292-byte client destructor.
// The 16-byte VC7.1 vector subobject is physically witnessed by 004071C0.
// The global call at 00409740 is a VC7 deque destructor (R077), not
// an independently owned game helper. These class names are provisional.
// Direct COM Stop/Release calls reproduce naturally generated MSVC temps.
SoundBank::~SoundBank() {
    if (--audioClientCount == 0) {
        audioPlaying = 0;
        TerminateThread(audioWorkerHandle, 0);
        CloseHandle(audioWorkerEvent);
        CloseHandle(audioWorkerHandle);
        audioWorkerEvent = 0;
        audioWorkerHandle = 0;
        audioQueue.clear();
    }
    for (unsigned int index = 0; index < buffers.size(); ++index) {
        if (buffers[index] != 0) {
            buffers[index]->Stop();
            buffers[index]->Release();
            buffers[index] = 0;
        }
    }
    buffers.clear();
}
