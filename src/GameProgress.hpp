#ifndef TH075_GAME_PROGRESS_HPP
#define TH075_GAME_PROGRESS_HPP

// One ranked score (16 bytes).
struct ProgressScore {
    unsigned char name[8];
    unsigned char month;
    unsigned char day;
    unsigned short field0A;
    unsigned int score;
};

// One difficulty of one character (0x5FC bytes); the ranking ends it.
struct ProgressDifficulty {
    unsigned char InsertRankedScore(unsigned int score);           // 00416EE0

    unsigned int field000;
    unsigned int selectionCount;        // +0x004
    unsigned char unknown008[0x55C - 0x008];
    ProgressScore scores[10];           // +0x55C best first
};

struct ProgressCharacter {
    ProgressDifficulty difficulties[4];
};

// The game's progress and score records (the global g_BattleRecords).
// The extent past +0x16BC6 is unknown.
class GameProgress {
public:
    GameProgress();                                                 // 00416640 the defaults
    void SetUnlockBit(short bit);                                   // 00416CE0
    void ClearUnlockBit(short bit);                                 // 00416D50
    unsigned char TestUnlockBit(short bit);                         // 00416DC0

    ProgressCharacter characters[15];   // +0x00000
    int modeCounts[15][15];             // +0x16710
    unsigned char field16A94[8];        // +0x16A94
    unsigned int unlockBits[10];        // +0x16A9C bits 0..320
    signed char selectedFighter;        // +0x16AC4
    signed char selectedDifficulty;     // +0x16AC5
    unsigned char field16AC6[256];      // +0x16AC6 saved with the scores
};

typedef char ProgressSizes[(sizeof(ProgressScore) == 16 && sizeof(ProgressDifficulty) == 0x5FC &&
                            sizeof(ProgressCharacter) == 0x17F0) ? 1 : -1];
#endif
