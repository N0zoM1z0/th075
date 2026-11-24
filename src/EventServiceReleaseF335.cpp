#include "EventQueue.hpp"

EventServiceF335::~EventServiceF335()
{
    --g_EventUsersAt0068BE30;
    if (g_EventUsersAt0068BE30==0) {
        g_EventRunningAt0068BE40=0;
        TerminateThread(g_EventThreadAt0068BE38,0);
        for (unsigned int index=0; index<g_EventServiceQueueAt0068BE44.size(); ++index)
            SetEvent(g_EventServiceQueueAt0068BE44[index]);
        g_EventServiceQueueAt0068BE44.clear();
        CloseHandle(g_EventReadyAt0068BE34);
        CloseHandle(g_EventThreadAt0068BE38);
    }
}
