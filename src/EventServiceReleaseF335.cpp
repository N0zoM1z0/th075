#include <windows.h>
#include <mmsystem.h>
// Borrowed native global service/queue at original addresses. Callee bodies
// and original private queue/worker class layouts are separately owned.
extern int g_EventUsersAt0068BE30;
extern int g_EventWaitMsAt0066C23C;
extern HANDLE g_EventReadyAt0068BE34;
extern HANDLE g_EventThreadAt0068BE38;
extern DWORD g_EventThreadIdAt0068BE3C;
extern unsigned char g_EventRunningAt0068BE40;
class EventServiceQueueF335 {public: void Reset(); unsigned int Size(); HANDLE* At(unsigned int index);};
extern EventServiceQueueF335 g_EventServiceQueueAt0068BE44;
class EventWorkerF335 {public: static int __stdcall RunWorker(int unused);};
class EventServiceF335 {
public:
    EventServiceF335* AcquireSharedService(int delay);
    void ReleaseSharedService();
};
void EventServiceF335::ReleaseSharedService()
{
    --g_EventUsersAt0068BE30;
    if (g_EventUsersAt0068BE30==0) {
        g_EventRunningAt0068BE40=0;
        TerminateThread(g_EventThreadAt0068BE38,0);
        for (unsigned int index=0; index<g_EventServiceQueueAt0068BE44.Size(); ++index)
            SetEvent(*g_EventServiceQueueAt0068BE44.At(index));
        g_EventServiceQueueAt0068BE44.Reset();
        CloseHandle(g_EventReadyAt0068BE34);
        CloseHandle(g_EventThreadAt0068BE38);
    }
}
