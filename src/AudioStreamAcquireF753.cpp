#include <windows.h>

// Original native R015 004071C0: real four-DWORD VC7.1 vector member
// at this+0 (native STL ctor/clear and member destructor).
// Only exact, observed used subobject fields; no private audio owner
// type is claimed historically beyond native member lifetime.
class AudioBuffersF753 {
    DWORD observedAllocatorOrBaseAt0;
    DWORD actualBeginAt4;
    DWORD actualEndAt8;
    DWORD actualCapacityAt12;
public:
    AudioBuffersF753();
    ~AudioBuffersF753();
    void Clear();
};
struct GlobalAudioBuffersF753 {
    void InitShared();
};
extern GlobalAudioBuffersF753 g_GlobalAudioBuffersF753;
extern int g_AudioStreamRefCountF753;
extern HANDLE g_AudioWorkerHandleF753;
extern DWORD g_AudioWorkerIDF753;
extern "C" DWORD WINAPI AudioWorkerMainF753(LPVOID);

class AudioStreamClientF753 {
    AudioBuffersF753 actualNativeMemberAt0;
public:
    AudioStreamClientF753();
};

AudioStreamClientF753::AudioStreamClientF753() {
    if (g_AudioStreamRefCountF753 == 0) {
        g_GlobalAudioBuffersF753.InitShared();
        if (g_AudioWorkerHandleF753 == 0) {
            g_AudioWorkerHandleF753 = CreateThread(0,0,AudioWorkerMainF753,
                                                   0,0,&g_AudioWorkerIDF753);
            SetThreadPriority(g_AudioWorkerHandleF753,15);
        }
    }
    actualNativeMemberAt0.Clear();
    ++g_AudioStreamRefCountF753;
}
