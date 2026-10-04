// Complete small observations preserve operations without copying unknown owner layouts.
#include <deque>
#include <list>
#include <new>
#include <string.h>
struct IndexedEightByteObservation { unsigned long first; unsigned long second; };
struct IndexedWorkingObservation {
    IndexedEightByteObservation working;
    void store(IndexedEightByteObservation& entry) { memcpy(&entry, &working, 8); }
    void load(const IndexedEightByteObservation& entry) { memcpy(&working, &entry, 8); }
};
struct IndexedQueueValueObservation { unsigned long value; };
typedef std::deque<IndexedQueueValueObservation> IndexedDequeObservation;
struct ExplicitIndexedQueueOwner {
    IndexedDequeObservation queue;
    ~ExplicitIndexedQueueOwner() { queue.clear(); }
};
struct ImplicitIndexedQueueOwner { IndexedDequeObservation queue; };
struct IndexedArchiveEntryObservation {
    char name[100];
    unsigned long file_size;
    unsigned long initial_state;
};
typedef std::list<IndexedArchiveEntryObservation> IndexedArchiveListObservation;
struct ExplicitIndexedArchiveOwner {
    unsigned long state;
    IndexedArchiveListObservation files;
    ExplicitIndexedArchiveOwner() { state = 0; files.clear(); }
};
struct ImplicitIndexedArchiveOwner {
    unsigned long state;
    IndexedArchiveListObservation files;
};
void ObserveIndexedStore(IndexedWorkingObservation& p, IndexedEightByteObservation& entry) { p.store(entry); }
void ObserveIndexedLoad(IndexedWorkingObservation& p, const IndexedEightByteObservation& entry) { p.load(entry); }
void DestroyExplicitIndexedQueue(ExplicitIndexedQueueOwner* p) { p->~ExplicitIndexedQueueOwner(); }
void DestroyImplicitIndexedQueue(ImplicitIndexedQueueOwner* p) { p->~ImplicitIndexedQueueOwner(); }
void ConstructExplicitIndexedArchive(ExplicitIndexedArchiveOwner* p) { new (p) ExplicitIndexedArchiveOwner; }
void ConstructImplicitIndexedArchive(ImplicitIndexedArchiveOwner* p) { new (p) ImplicitIndexedArchiveOwner; }
extern "C" const unsigned long IndexedOwnerPolicyLayout[] = {
    sizeof(IndexedEightByteObservation), sizeof(IndexedWorkingObservation),
    sizeof(IndexedQueueValueObservation), sizeof(IndexedDequeObservation),
    sizeof(ExplicitIndexedQueueOwner), sizeof(ImplicitIndexedQueueOwner),
    sizeof(IndexedArchiveEntryObservation), sizeof(IndexedArchiveListObservation),
    sizeof(ExplicitIndexedArchiveOwner), sizeof(ImplicitIndexedArchiveOwner)
};
