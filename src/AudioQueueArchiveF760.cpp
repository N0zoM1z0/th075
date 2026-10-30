#include <windows.h>
#include <stddef.h>
// Original R016 00407B80 entire authored archive audio queue. The local
// record has independently observed 64-byte native storage (F758) and the
// live playback mode at +0x28. The rest of the record and registry type
// names are borrowed physical views; original private layout unknown.
class AudioRecordF760 {
    DWORD opaqueWordsBeforeMode[10];
public:
    DWORD playbackModeAt28;
private:
    DWORD opaqueWordsAfterMode[5];
public:
    AudioRecordF760();
    ~AudioRecordF760();
    void ReadLoopPointsFromArchive(const char*,const char*);
    void OpenArchiveEntry(const char*,DWORD,const char*);
};
typedef char NativeRecordSizeF760[(sizeof(AudioRecordF760)==0x40)?1:-1];
typedef char NativeModeOffsetF760[(offsetof(AudioRecordF760,playbackModeAt28)==0x28)?1:-1];
struct SharedAudioRegistryF760 {
    unsigned int Size();
    void PopBack();
    void PushBack(const AudioRecordF760&);
    AudioRecordF760* Back();
};
extern SharedAudioRegistryF760 g_SharedAudioRegistryF760;
class ArchiveContextF760 {public: HANDLE SeekNamedEntry(const char*);};
namespace ResourceLookupF760 {ArchiveContextF760* __cdecl FindByName(const char*);}
extern const char g_DefaultAudioArchiveNameF760[];
namespace AudioQueueArchiveF760 {
void __cdecl QueueArchiveEntry(const char* filename,int mode,const char* archive) {
    HANDLE handle;
    if (g_SharedAudioRegistryF760.Size() >= 2)
        g_SharedAudioRegistryF760.PopBack();
    handle=ResourceLookupF760::FindByName(g_DefaultAudioArchiveNameF760)->SeekNamedEntry(filename);
    if (handle != INVALID_HANDLE_VALUE) {
        AudioRecordF760 record;
        g_SharedAudioRegistryF760.PushBack(record);
        switch (mode) {
        case 0: g_SharedAudioRegistryF760.Back()->playbackModeAt28=0; break;
        case 1: g_SharedAudioRegistryF760.Back()->playbackModeAt28=1; break;
        case 2:
            g_SharedAudioRegistryF760.Back()->playbackModeAt28=1;
            g_SharedAudioRegistryF760.Back()->ReadLoopPointsFromArchive(filename,archive);
            break;
        }
        g_SharedAudioRegistryF760.Back()->OpenArchiveEntry(filename,0x100000,archive);
    }
}
}
