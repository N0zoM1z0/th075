#include "ArchiveCatalog.hpp"
#include "AudioControl.hpp"
#include "DataArchive.hpp"
#include <windows.h>
#include <stddef.h>
#include "AudioStream.hpp"
extern const char g_DefaultAudioArchiveNameF760[] = "sound";

namespace AudioQueueArchiveF760 {
void __cdecl QueueArchiveEntry(const char* filename,int mode,const char* archive) {
    HANDLE handle;
    if (audioQueue.size() >= 2)
        audioQueue.pop_back();
    handle=ResourceLookupF217::FindByName(g_DefaultAudioArchiveNameF760)->SeekNamedEntry(filename);
    if (handle != INVALID_HANDLE_VALUE) {
        AudioStream record;
        audioQueue.push_back(record);
        switch (mode) {
        case 0: audioQueue.back().loopEnabled=0; break;
        case 1: audioQueue.back().loopEnabled=1; break;
        case 2:
            audioQueue.back().loopEnabled=1;
            audioQueue.back().ReadLoopPointsFromArchive(filename,archive);
            break;
        }
        audioQueue.back().OpenArchiveEntry(filename,0x100000,archive);
    }
}
}
