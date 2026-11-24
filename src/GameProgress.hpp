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

    int field000;                       // +0x000 counted by IncrementSelectedRecordCount
    unsigned int field004;              // +0x004 counted by IncrementSelectedRecord
    int field008;                       // +0x008
    int field00C;                       // +0x00C
    int cardValues[150];                // +0x010 per spell card
    unsigned short cardCounters[150];   // +0x268
    unsigned short cardCounters2[150];  // +0x394
    unsigned char cardFlags[150];       // +0x4C0
    signed char field556;               // +0x556 only ever raised (RaiseSelectedValue)
    unsigned char unknown557[0x55C - 0x557];
    ProgressScore scores[10];           // +0x55C best first
};

// The card arrays are per character: the code uses difficulty block 0's.
struct ProgressCharacter {
    ProgressDifficulty difficulties[4];
};

// The progress records end before the cosine table in the native image.
class GameProgress {
public:
    GameProgress();                                                 // 00416640 the defaults
    ~GameProgress();                                                // 004169D0
    void SetUnlockBit(short bit);                                   // 00416CE0
    void ClearUnlockBit(short bit);                                 // 00416D50
    unsigned char TestUnlockBit(short bit);                         // 00416DC0
    void SaveScoreFile();                                           // 004169E0
    void LoadScoreFile();                                           // 00416B10
    void SetSelection(signed char fighter, signed char difficulty); // 0041A1A0
    void RaiseSelectedValue(signed char value);                     // 0041A1D0
    ProgressDifficulty* GetSelectedRecordAddress();                 // 0041A240
    void IncrementSelectedRecordCount();                            // 0041A270
    void StoreWorkingEightBytes(signed char slot);                  // 00416E20
    void LoadWorkingEightBytes(signed char slot);                   // 00416E80
    void IncrementSelectedWordCounter(signed char index);           // 00454D00
    signed char GetSelectedValue();                                 // 00438A80
    void IncrementSelectedRecord();                                 // 00425130
    void IncrementModeCounter(signed char category, signed char key);  // 0043D360
    void SetCardValue(signed char key, int value);                  // 0043D3B0
    void IncrementCardCounter(signed char key);                     // 0043D3E0
    void MarkCardFlag(signed char key);                             // 0043D430
    int GetCardValue(signed char key);                              // 0043D460
    unsigned int ReadSelectedWord268(signed char key);              // 00441FE0
    unsigned int ReadSelectedWord394(signed char key);              // 00442010
    void SetSelectedValue8(int value);                              // 004451D0
    void SetSelectedValue12(int value);                             // 00445210
    int GetSelectedValue8();                                        // 00445250
    int GetSelectedValue12();                                       // 00445290

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
typedef char ProgressTotalSize[(sizeof(GameProgress) == 0x16BC8) ? 1 : -1];
extern GameProgress g_GameProgress;

namespace GameProgressF203 {
    unsigned char CheckSelection(signed char selection, signed char mode);
}

namespace ProgressRecordsF736 {
    unsigned char CheckEncodedItem(signed char code);
}
#endif
