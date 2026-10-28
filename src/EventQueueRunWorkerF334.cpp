#include <windows.h>
// All 28 bytes of the two live checked iterators' actual original state
// are observed: three initialized tracking DWORDs and two 8-byte values.
class QueueIteratorF334 {
    DWORD physical[2];
public:
    void Initialize();
    bool operator!=(const QueueIteratorF334&) const;
    int*& operator*() const;
    QueueIteratorF334 operator++(int);
};
struct LiveWorkerIteratorsF334 {
    DWORD endCheckedA;
    DWORD endCheckedB;
    QueueIteratorF334 end;
    DWORD beginChecked;
    QueueIteratorF334 it;
};
typedef char CheckLiveWorker28F334[(sizeof(LiveWorkerIteratorsF334)==28)?1:-1];
class QueueCollectionF334 {
public:
    QueueIteratorF334 Begin();
    QueueIteratorF334 End();
    QueueIteratorF334 Erase(QueueIteratorF334 it);
    void** Front();
};
extern HANDLE g_QueueReadyEventAt0068BE34;
extern DWORD g_QueueWaitTimeoutAt0066C23C;
extern QueueCollectionF334 g_EventQueueAt0068BE44;
class EventWorkerF334 {public: static int __stdcall RunWorker(int unused);};
int __stdcall EventWorkerF334::RunWorker(int unused)
{
    LiveWorkerIteratorsF334 state;
    state.beginChecked=0;
    state.endCheckedB=0;
    state.endCheckedA=0;
    state.it.Initialize();
    state.end.Initialize();
    while (true) {
        WaitForSingleObject(g_QueueReadyEventAt0068BE34,g_QueueWaitTimeoutAt0066C23C);
        state.it=g_EventQueueAt0068BE44.Begin();
        state.end=g_EventQueueAt0068BE44.End();
        while (state.it!=state.end) {
            if (**state.it!=0) {
                SetEvent(*reinterpret_cast<HANDLE*>(*g_EventQueueAt0068BE44.Front()));
                state.it++;
            } else {
                state.it=g_EventQueueAt0068BE44.Erase(state.it);
                state.end=g_EventQueueAt0068BE44.End();
            }
        }
    }
    return 0;
}
