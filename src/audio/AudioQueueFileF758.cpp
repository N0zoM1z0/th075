#include <windows.h>
#include <stddef.h>
#include "audio/AudioStream.hpp"

namespace AudioQueueFileF758 {
void __cdecl QueueFile(const char* filename, int mode) {
    HANDLE handle;
    {
        AudioStream record;
        if (audioQueue.size() >= 2)
            audioQueue.pop_back();
        handle=CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, 0);
        if (handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
        audioQueue.push_back(record);
        switch (mode) {
        case 0:
            audioQueue.back().loopEnabled=0;
            break;
        case 1:
            audioQueue.back().loopEnabled=1;
            break;
        case 2:
            audioQueue.back().loopEnabled=1;
            audioQueue.back().ReadLoopPointsFromFile(filename);
            break;
        }
            audioQueue.back().OpenFile(filename,0x100000);
        }
    }
}
}
