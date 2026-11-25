#ifndef TH075_REPLAY_RECORDS_HPP
#define TH075_REPLAY_RECORDS_HPP
#include <stddef.h>
#include <windows.h>
#include <deque>

// In-memory header for one replay record. The reader and writer transfer the
// fields individually, omitting the two padding bytes.
struct ReplayRecordHeaderF219 {
    unsigned char secondaryFighter;
    unsigned char secondaryFirstSpellCard;
    unsigned char secondarySecondSpellCard;
    unsigned char secondaryPalette;
    unsigned char secondaryAutoGuard;
    unsigned char secondaryDamageSetting;
    unsigned char stage;                // arena ID, or the stage index in Story mode
    unsigned char unknown14B;
    short startingHealth;
    unsigned char remainingLives;
    unsigned char unknown14F;
    DWORD startingScore;
};
typedef char ReplayRecordHeaderLayout[(
    sizeof(ReplayRecordHeaderF219) == 0x10 &&
    offsetof(ReplayRecordHeaderF219, stage) == 0x06 &&
    offsetof(ReplayRecordHeaderF219, startingHealth) == 0x08 &&
    offsetof(ReplayRecordHeaderF219, remainingLives) == 0x0A &&
    offsetof(ReplayRecordHeaderF219, startingScore) == 0x0C) ? 1 : -1];

// The prefix written at the start of a replay file.
struct ReplayFileHeaderF219 {
    unsigned char playerName[8];
    unsigned char month;
    unsigned char day;
    unsigned char primaryFighter;
    unsigned char primaryFirstSpellCard;
    unsigned char primarySecondSpellCard;
    unsigned char mode;
    signed char recordCount;
    unsigned char activeSide;
    unsigned char primaryPalette;
    unsigned char primaryAutoGuard;
    unsigned char primaryDamageSetting;
    unsigned char unknown11B;
    DWORD recordOffsets[10];
};
typedef char ReplayFileHeaderLayout[(
    sizeof(ReplayFileHeaderF219) == 0x3C &&
    offsetof(ReplayFileHeaderF219, primaryFirstSpellCard) == 0x0B &&
    offsetof(ReplayFileHeaderF219, mode) == 0x0D &&
    offsetof(ReplayFileHeaderF219, recordOffsets) == 0x14) ? 1 : -1];

// The replay reader, writer, and input handlers share the native four-queue layout.
template<class ByteQueue, class WordQueue, class DwordQueue>
struct ReplayRecordsLayoutF219 {
    ReplayRecordsLayoutF219();
    ~ReplayRecordsLayoutF219();
    void LoadRecord(signed char slot);
    void AppendRecord();
    void ClearFourQueues();
    unsigned char IsPrimaryInputQueueEmpty();
    void BeginCapture();
    void FinalizeFile();
    int FindAvailablePath(char* path);
    void ReadSnapshotHeader();

    HANDLE fileHandle;                   // +0x000
    char filePath[MAX_PATH];              // +0x004 .. +0x107
    ReplayFileHeaderF219 fileHeader;      // +0x108 .. +0x143
    ReplayRecordHeaderF219 recordHeader; // +0x144 .. +0x153
    ByteQueue frameInputBits;             // +0x154 human and CPU input masks
    WordQueue randomSamplesAndAiTimers;  // +0x168 both in the order they occur
    ByteQueue aiCommandsAndGuardChoices;  // +0x17C both in the order they occur
    DwordQueue timedBattleCommands;       // +0x190 frame index and command pairs
};

typedef std::deque<unsigned char> ReplayByteQueue;
typedef std::deque<short> ReplayWordQueue;
typedef std::deque<unsigned int> ReplayDwordQueue;
typedef ReplayRecordsLayoutF219<ReplayByteQueue, ReplayWordQueue, ReplayDwordQueue> ReplayRecords;

typedef char ReplayRecordsNativeLayout[(
    sizeof(ReplayRecords) == 0x1A4 &&
    offsetof(ReplayRecords, fileHeader) == 0x108 &&
    offsetof(ReplayRecords, recordHeader) == 0x144 &&
    offsetof(ReplayRecords, frameInputBits) == 0x154 &&
    offsetof(ReplayRecords, randomSamplesAndAiTimers) == 0x168 &&
    offsetof(ReplayRecords, aiCommandsAndGuardChoices) == 0x17C &&
    offsetof(ReplayRecords, timedBattleCommands) == 0x190) ? 1 : -1];

extern ReplayRecords g_ReplayRecords;

#endif
