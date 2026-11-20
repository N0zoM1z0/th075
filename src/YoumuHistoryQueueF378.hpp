#ifndef TH075_YOUMU_HISTORY_QUEUE_F378_HPP
#define TH075_YOUMU_HISTORY_QUEUE_F378_HPP
#include <list>

// One borrowed 16-byte history value shared by Youmu's per-frame snapshot
// writer (R049/F378) and the object history relay (R243/F1211).
// The record is copied into the list; neither caller owns the list or its
// nodes. Its natural member alignment accounts for byte +0x0D.
struct ObservedInputSnapshotF378 {
    union { short action; short actionAt00; };
    union { short guard; short stageAt02; };
    union { float x; float xAt04; };
    union { float y; float yAt08; };
    union { signed char facing; signed char facingAt0C; };
    union { short bearing; short counterAt0E; };
};
typedef char CheckSnapshot16F378[(sizeof(ObservedInputSnapshotF378)==16)?1:-1];

// VC7.1's 12-byte std::list of the 16-byte action snapshots, embedded at
// YoumuFighter +0xFEC. The native allocation ends at +0xFF8. The queue
// exposes native insert/count/prune helpers and the list-front worker;
// their original private member names remain unknown.
class ObservedEffectQueueF378 : public std::list<ObservedInputSnapshotF378> {
public:
    void AddSnapshot(ObservedInputSnapshotF378 const*);
    unsigned int Count();
    void PruneOld();
    ObservedInputSnapshotF378& FrontAt00540220();
};

#endif
