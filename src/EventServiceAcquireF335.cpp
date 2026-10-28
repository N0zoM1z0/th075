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
EventServiceF335* EventServiceF335::AcquireSharedService(int delay)
{
    if(g_EventUsersAt0068BE30==0) {
        g_EventWaitMsAt0066C23C=delay;
        if (g_EventWaitMsAt0066C23C<0)
            g_EventWaitMsAt0066C23C=0;
        timeBeginPeriod(1);
        g_EventServiceQueueAt0068BE44.Reset();
        g_EventReadyAt0068BE34=CreateEventA(0,FALSE,FALSE,0);
        g_EventThreadAt0068BE38=CreateThread(0,0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(&EventWorkerF335::RunWorker),
            0,0,&g_EventThreadIdAt0068BE3C);
        SetThreadPriority(g_EventThreadAt0068BE38,15);
        g_EventRunningAt0068BE40=1;
    }
    ++g_EventUsersAt0068BE30;
    return this;
}
