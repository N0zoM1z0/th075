#pragma once

#include <windows.h>
#include <deque>

typedef std::deque<HANDLE*> EventQueue;

extern EventQueue g_EventServiceQueueAt0068BE44;
extern int g_EventUsersAt0068BE30;
extern int g_EventWaitMsAt0066C23C;
extern HANDLE g_EventReadyAt0068BE34;
extern HANDLE g_EventThreadAt0068BE38;
extern DWORD g_EventThreadIdAt0068BE3C;
extern unsigned char g_EventRunningAt0068BE40;

namespace EventQueueGuardF457
{
    void AppendUnique(HANDLE* event);
}

class EventWorkerF334
{
public:
    static DWORD WINAPI RunWorker(LPVOID);
};

class EventServiceF335
{
public:
    EventServiceF335* AcquireSharedService(int delay);
    void ReleaseSharedService();
};
