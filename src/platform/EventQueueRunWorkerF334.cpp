#include "platform/EventQueue.hpp"

DWORD WINAPI EventWorkerF334::RunWorker(LPVOID)
{
    // The native worker zero-initializes these values before the two cursors.
    DWORD firstState = 0;
    DWORD endState = 0;
    DWORD lastState = 0;
    EventQueue::iterator queueEntry;
    EventQueue::iterator endOfQueue;
    while (true) {
        WaitForSingleObject(g_EventReadyAt0068BE34, g_EventWaitMsAt0066C23C);
        queueEntry = g_EventServiceQueueAt0068BE44.begin();
        endOfQueue = g_EventServiceQueueAt0068BE44.end();
        while (queueEntry != endOfQueue) {
            if (**queueEntry) {
                SetEvent(*g_EventServiceQueueAt0068BE44.front());
                queueEntry++;
            } else {
                queueEntry = g_EventServiceQueueAt0068BE44.erase(queueEntry);
                endOfQueue = g_EventServiceQueueAt0068BE44.end();
            }
        }
    }
    return 0;
}
