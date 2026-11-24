#include "EventQueue.hpp"
#include <mmsystem.h>

int g_EventUsersAt0068BE30;
int g_EventWaitMsAt0066C23C = 16;
HANDLE g_EventReadyAt0068BE34;
HANDLE g_EventThreadAt0068BE38;
DWORD g_EventThreadIdAt0068BE3C;
unsigned char g_EventRunningAt0068BE40;

EventServiceF335* EventServiceF335::AcquireSharedService(int delay)
{
    if(g_EventUsersAt0068BE30==0) {
        g_EventWaitMsAt0066C23C=delay;
        if (g_EventWaitMsAt0066C23C<0)
            g_EventWaitMsAt0066C23C=0;
        timeBeginPeriod(1);
        g_EventServiceQueueAt0068BE44.clear();
        g_EventReadyAt0068BE34=CreateEventA(0,FALSE,FALSE,0);
        g_EventThreadAt0068BE38=CreateThread(0,0,
            &EventWorkerF334::RunWorker,
            0,0,&g_EventThreadIdAt0068BE3C);
        SetThreadPriority(g_EventThreadAt0068BE38,15);
        g_EventRunningAt0068BE40=1;
    }
    ++g_EventUsersAt0068BE30;
    return this;
}
