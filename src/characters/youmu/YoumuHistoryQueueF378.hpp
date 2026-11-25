#ifndef TH075_YOUMU_HISTORY_QUEUE_F378_HPP
#define TH075_YOUMU_HISTORY_QUEUE_F378_HPP
#include <list>

// A native 16-byte animation snapshot shared by Youmu's auxiliary writer
// and the object-history relay. The fighter's std::list owns its copies;
// natural alignment leaves byte +0x0D between facing and counter.
struct ObservedInputSnapshotF378 {
    short action;
    short stage;
    float x;
    float y;
    signed char facing;
    short counter;
};
typedef char CheckSnapshot16F378[(sizeof(ObservedInputSnapshotF378)==16)?1:-1];


#endif
