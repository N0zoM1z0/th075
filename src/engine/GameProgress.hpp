#ifndef TH075_GAME_PROGRESS_HPP
#define TH075_GAME_PROGRESS_HPP

#include <stddef.h>

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
    unsigned char InsertRankedScore(unsigned int score);              // 00416EE0

    int storyAttempts;                      // +0x000
    unsigned int storyClears;                // +0x004 normal story ending
    int maxComboHits;                        // +0x008
    int maxComboDamage;                      // +0x00C
    int bestSpellBonus[150];                 // +0x010
    unsigned short spellBonusClears[150];    // +0x268 defeated while the bonus was positive
    unsigned short spellAttempts[150];       // +0x394
    unsigned char spellCaptureFlags[150];    // +0x4C0
    signed char highestStoryStage;           // +0x556 stage-selection limit
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
    GameProgress();                                                   // 00416640 the defaults
    ~GameProgress();                                                  // 004169D0
    void SetUnlockBit(short bit);                                     // 00416CE0
    void ClearUnlockBit(short bit);                                   // 00416D50
    unsigned char TestUnlockBit(short bit);                           // 00416DC0
    void SaveScoreFile();                                             // 004169E0
    void LoadScoreFile();                                             // 00416B10
    void SetSelection(signed char fighter, signed char difficulty);   // 0041A1A0
    void UpdateHighestStoryStage(signed char stage);                  // 0041A1D0
    ProgressDifficulty* GetSelectedDifficultyRecord();                // 0041A240
    void RecordStoryAttempt();                                        // 0041A270
    void CopyWorkingNameToRank(signed char slot);                     // 00416E20
    void CopyRankNameToWorking(signed char slot);                     // 00416E80
    void RecordSpellAttempt(signed char index);                       // 00454D00
    signed char GetHighestStoryStage();                               // 00438A80
    void RecordStoryClear();                                          // 00425130
    void RecordMatchWin(signed char winner, signed char opponent);    // 0043D360
    void SetBestSpellBonus(signed char key, int value);               // 0043D3B0
    void RecordSpellBonusClear(signed char key);                      // 0043D3E0
    void MarkSpellCapture(signed char key);                           // 0043D430
    int GetBestSpellBonus(signed char key);                           // 0043D460
    unsigned int GetSpellBonusClears(signed char key);                // 00441FE0
    unsigned int GetSpellAttempts(signed char key);                   // 00442010
    void SetMaxComboHits(int value);                                  // 004451D0
    void SetMaxComboDamage(int value);                                // 00445210
    int GetMaxComboHits();                                            // 00445250
    int GetMaxComboDamage();                                          // 00445290

    ProgressCharacter characters[15];   // +0x00000
    int matchWinsByFighterPair[15][15];       // +0x16710 indexed by winner, then opponent
    unsigned char workingPlayerName[8];       // +0x16A94
    unsigned int unlockBits[10];              // +0x16A9C unlock flags
    signed char selectedFighter;              // +0x16AC4
    signed char selectedDifficulty;           // +0x16AC5
    unsigned char randomizedSaveTail[256];    // +0x16AC6 partially refreshed on save
};

typedef char ProgressSizes[(sizeof(ProgressScore) == 16 && sizeof(ProgressDifficulty) == 0x5FC &&
                            sizeof(ProgressCharacter) == 0x17F0) ? 1 : -1];
typedef char ProgressTotalSize[(sizeof(GameProgress) == 0x16BC8) ? 1 : -1];
typedef char ProgressRecordOffsets[(offsetof(ProgressDifficulty, spellBonusClears) == 0x268 &&
                                   offsetof(ProgressDifficulty, spellAttempts) == 0x394 &&
                                   offsetof(ProgressDifficulty, highestStoryStage) == 0x556 &&
                                   offsetof(ProgressDifficulty, scores) == 0x55C) ? 1 : -1];
extern GameProgress g_GameProgress;

namespace GameProgressF203 {
    unsigned char CheckSelection(signed char selection, signed char mode);
}

namespace ProgressRecordsF736 {
    unsigned char CheckEncodedItem(signed char code);
}
#endif
