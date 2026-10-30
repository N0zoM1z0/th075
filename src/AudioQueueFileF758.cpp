#include <windows.h>
#include <stddef.h>
// Complete R016 original 00407A50: the observed 64-byte native audio record
// owns a real VC7 constructor/destructor lifetime. The storage envelope and
// playback-mode DWORD at +0x28 are backed by native machine code; other
// private field meanings and historical class names are unproven.
class AudioRecordF758 {
    DWORD opaqueWordsBeforeMode[10];
public:
    DWORD playbackModeAt28;
private:
    DWORD opaqueWordsAfterMode[5];
public:
    AudioRecordF758();
    ~AudioRecordF758();
    void ReadLoopPointsFromFile(const char*);
    void OpenFile(const char*, DWORD);
};
typedef char VerifyNativeRecord64F758[(sizeof(AudioRecordF758)==0x40)?1:-1];
typedef char VerifyNativeModeAt28F758[(offsetof(AudioRecordF758,playbackModeAt28)==0x28)?1:-1];
struct SharedAudioRegistryF758 {
    unsigned int Size();
    void PopBack();
    void PushBack(const AudioRecordF758&);
    AudioRecordF758* Back();
};
extern SharedAudioRegistryF758 g_SharedAudioRegistryF758;
namespace AudioQueueFileF758 {
void __cdecl QueueFile(const char* filename, int mode) {
    HANDLE handle;
    {
        AudioRecordF758 record;
        if (g_SharedAudioRegistryF758.Size() >= 2)
            g_SharedAudioRegistryF758.PopBack();
        handle=CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, 0);
        if (handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
        g_SharedAudioRegistryF758.PushBack(record);
        switch (mode) {
        case 0:
            g_SharedAudioRegistryF758.Back()->playbackModeAt28=0;
            break;
        case 1:
            g_SharedAudioRegistryF758.Back()->playbackModeAt28=1;
            break;
        case 2:
            g_SharedAudioRegistryF758.Back()->playbackModeAt28=1;
            g_SharedAudioRegistryF758.Back()->ReadLoopPointsFromFile(filename);
            break;
        }
            g_SharedAudioRegistryF758.Back()->OpenFile(filename,0x100000);
        }
    }
}
}
