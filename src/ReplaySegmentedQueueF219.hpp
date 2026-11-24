#ifndef TH075_REPLAY_SEGMENTED_QUEUE_F219_HPP
#define TH075_REPLAY_SEGMENTED_QUEUE_F219_HPP
#include <stddef.h>
#include <windows.h>
#include <deque>

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

// The prefix written at the start of a replay file.
struct ReplayFileHeaderF219 {
    unsigned char playerName[8];
    unsigned char month;
    unsigned char day;
    unsigned char primaryFighter;
    unsigned char primaryPalette;
    unsigned char primaryFlags;
    unsigned char mode;
    signed char recordCount;
    unsigned char activeSide;
    unsigned char primaryRound;
    unsigned char primaryDifficulty;
    unsigned char primarySettings;
    unsigned char unknown11B;
    DWORD recordOffsets[10];
};
typedef char ReplayFileHeaderSizeF219[(sizeof(ReplayFileHeaderF219) == 0x3C) ? 1 : -1];

// The replay reader and input handlers share the native four-queue layout.
// The writer still uses this layout with its iterator call declarations.
template<class ByteQueue, class WordQueue, class DwordQueue>
struct ReplayRecordsLayoutF219 {
    ReplayRecordsLayoutF219();
    ~ReplayRecordsLayoutF219();
    void LoadRecord(signed char slot);
    void ClearFourQueues();
    unsigned char IsPrimaryInputQueueEmpty();
    void BeginCapture();
    void FinalizeFile();
    int FindAvailablePath(char* path);
    void ReadSnapshotHeader();

    HANDLE fileHandle;                   // +0x000
    char filePath[MAX_PATH];             // +0x004 .. +0x107
    ReplayFileHeaderF219 fileHeader;     // +0x108 .. +0x143
    ReplayRecordHeaderF219 header;       // +0x144 .. +0x153
    ByteQueue byteInputs;                // +0x154
    WordQueue wordInputs;                // +0x168
    ByteQueue secondaryInputs;           // +0x17C
    DwordQueue dwordInputs;              // +0x190
};

typedef std::deque<unsigned char> ReplayByteQueue;
typedef std::deque<short> ReplayWordQueue;
typedef std::deque<unsigned int> ReplayDwordQueue;
typedef ReplayRecordsLayoutF219<ReplayByteQueue, ReplayWordQueue, ReplayDwordQueue> ReplayRecords;

typedef char ReplayRecordsNativeLayout[(
    sizeof(ReplayRecords) == 0x1A4 &&
    offsetof(ReplayRecords, fileHeader) == 0x108 &&
    offsetof(ReplayRecords, byteInputs) == 0x154 &&
    offsetof(ReplayRecords, wordInputs) == 0x168 &&
    offsetof(ReplayRecords, secondaryInputs) == 0x17C &&
    offsetof(ReplayRecords, dwordInputs) == 0x190) ? 1 : -1];

extern ReplayRecords g_ReplayRecords;

#endif
