#include <windows.h>
#include <dsound.h>
// R015 original 00407270: complete 292-byte client destructor.
// The 16-byte VC7.1 vector subobject is physically witnessed by 004071C0.
// The global call at 00409740 is a VC7 deque destructor (R077), not
// an independently owned game helper. These class names are provisional.
// Direct COM Stop/Release calls reproduce naturally generated MSVC temps.
class AudioBuffersF755 {
    DWORD observedAllocatorOrBaseAt0;
    DWORD actualBeginAt4;
    DWORD actualEndAt8;
    DWORD actualCapacityAt12;
public:
    ~AudioBuffersF755();
    unsigned int Size();
    IDirectSoundBuffer8*& At(unsigned int);
    void Clear();
};
struct GlobalAudioBuffersF755 { void ReleaseSharedDequeAt409740(); };
extern GlobalAudioBuffersF755 g_GlobalAudioBuffersF755;
extern int g_AudioStreamRefCountF755;
extern char g_AudioWorkerRunningF755;
extern HANDLE g_AudioWaitHandleF755;
extern HANDLE g_AudioWorkerHandleF755;
class AudioStreamClientF755 {
    AudioBuffersF755 actualNativeMemberAt0;
public:
    ~AudioStreamClientF755();
};
AudioStreamClientF755::~AudioStreamClientF755() {
    if (--g_AudioStreamRefCountF755 == 0) {
        g_AudioWorkerRunningF755 = 0;
        WaitForSingleObject(g_AudioWorkerHandleF755, 0);
        CloseHandle(g_AudioWaitHandleF755);
        CloseHandle(g_AudioWorkerHandleF755);
        g_AudioWaitHandleF755 = 0;
        g_AudioWorkerHandleF755 = 0;
        g_GlobalAudioBuffersF755.ReleaseSharedDequeAt409740();
    }
    for (unsigned int index = 0; index < actualNativeMemberAt0.Size(); ++index) {
        if (actualNativeMemberAt0.At(index) != 0) {
            actualNativeMemberAt0.At(index)->Stop();
            actualNativeMemberAt0.At(index)->Release();
            actualNativeMemberAt0.At(index) = 0;
        }
    }
    actualNativeMemberAt0.Clear();
}
