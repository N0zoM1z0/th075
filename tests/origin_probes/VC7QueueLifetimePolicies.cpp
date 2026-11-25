// Complete synthetic queue policy; original owners and element types are unknown.
#include <windows.h>
#include <mmsystem.h>
#include <deque>
extern int queue_clients_probe;
extern int queue_wait_probe;
extern HANDLE queue_event_probe;
extern HANDLE queue_thread_probe;
extern DWORD queue_thread_id_probe;
extern unsigned char queue_active_probe;
extern unsigned char window_ready_probe;
extern std::deque<void*> queue_policy_probe;
DWORD WINAPI QueueWorkerProbe(LPVOID);
struct QueueServicePolicyProbe {
    QueueServicePolicyProbe(int interval);
    ~QueueServicePolicyProbe();
};
QueueServicePolicyProbe::QueueServicePolicyProbe(int interval) {
    if (queue_clients_probe == 0) {
        queue_wait_probe = interval;
        if (queue_wait_probe < 0) queue_wait_probe = 0;
        timeBeginPeriod(1);
        queue_policy_probe.clear();
        queue_event_probe = CreateEventA(0, FALSE, FALSE, 0);
        queue_thread_probe = CreateThread(0, 0, QueueWorkerProbe, 0, 0, &queue_thread_id_probe);
        SetThreadPriority(queue_thread_probe, 15);
        queue_active_probe = 1;
    }
    ++queue_clients_probe;
}
QueueServicePolicyProbe::~QueueServicePolicyProbe() {
    if (--queue_clients_probe == 0) {
        queue_active_probe = 0;
        TerminateThread(queue_thread_probe, 0);
        for (int i = 0; i < queue_policy_probe.size(); ++i) SetEvent(queue_policy_probe[i]);
        queue_policy_probe.clear();
        CloseHandle(queue_event_probe);
        CloseHandle(queue_thread_probe);
    }
}
LRESULT CALLBACK WindowCallbackProbe(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case 1: window_ready_probe = 1; break;
    case 2: PostQuitMessage(0); break;
    case 0x12: break;
    default: return DefWindowProcA(window, message, wparam, lparam);
    }
    return 0;
}
