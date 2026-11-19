#ifndef TH075_REPLAY_SEGMENTED_QUEUE_F219_HPP
#define TH075_REPLAY_SEGMENTED_QUEUE_F219_HPP
#include <stddef.h>
#include <windows.h>

// Native replay queues are segmented circular collections. The first word
// is an as-yet-unclassified control/allocator value; the remaining words are
// the block map, map length, logical first index, and element count.
template<class T> struct ReplaySegmentedQueueStorageF219 {
    unsigned int unknown000;
    T** blockMap;
    unsigned int blockCount;
    unsigned int firstIndex;
    unsigned int size;
};
typedef char ReplayQueueByteSizeF219[(sizeof(ReplaySegmentedQueueStorageF219<char>)==0x14)?1:-1];
typedef char ReplayQueueWordSizeF219[(sizeof(ReplaySegmentedQueueStorageF219<short>)==0x14)?1:-1];
typedef char ReplayQueueDwordSizeF219[(sizeof(ReplaySegmentedQueueStorageF219<unsigned int>)==0x14)?1:-1];
typedef char ReplayQueueMapOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,blockMap)==0x04)?1:-1];
typedef char ReplayQueueBlockCountOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,blockCount)==0x08)?1:-1];
typedef char ReplayQueueFirstIndexOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,firstIndex)==0x0C)?1:-1];
typedef char ReplayQueueSizeOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,size)==0x10)?1:-1];

// Serialized record header observed at ReplayRecords+0x144.
struct ReplayRecordHeaderF219 {
    unsigned char field144;
    unsigned char field145;
    unsigned char field146;
    unsigned char field147;
    unsigned char field148;
    unsigned char field149;
    unsigned char field14A;
    unsigned char unknown14B;
    short field14C;
    unsigned char field14E;
    unsigned char unknown14F;
    DWORD field150;
};
typedef char ReplayRecordHeaderSizeF219[(sizeof(ReplayRecordHeaderF219)==0x10)?1:-1];

// Shared ReplayRecords owner layout. Queue wrapper types are supplied by each
// translation unit so their native member-call symbols remain independently
// nameable while all four physical queue objects share the same proven ABI.
template<class ByteQueue, class WordQueue, class DwordQueue>
struct ReplayRecordsLayoutF219 {
    HANDLE fileHandle;                   // +0x000
    char filePath[0x112];                // +0x004 .. +0x115
    signed char field116;                // +0x116 next record-offset slot
    unsigned char unknown117[5];         // +0x117 .. +0x11B
    DWORD recordOffsets[10];             // +0x11C ten file offsets
    ReplayRecordHeaderF219 header;       // +0x144 .. +0x153
    ByteQueue byteInputs;                // +0x154
    WordQueue wordInputs;                // +0x168
    ByteQueue secondaryInputs;           // +0x17C
    DwordQueue dwordInputs;              // +0x190
};

#endif
