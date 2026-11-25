#include "engine/GameProgress.hpp"
#include <string.h>

GameProgress g_GameProgress;

// The progress defaults: every ranking starts at 10000..1000 points.
// The body also initializes ten 9-byte local names that are never used.
GameProgress::GameProgress()
{
    memset(this, 0, 0x16710);
    memset(unlockBits, 0, 0x28);
    // These ten locally initialized, NUL-terminated names occur in the
    // target's stack frame even if their source-level later use is unknown.
    char fishNames[10][9] = {
        "iwashi  ", "maguro  ", "hirame  ", "katuo   ",
        "karei   ", "sanma   ", "sake    ", "buri    ",
        "saba    ", "tai     "
    };
    for (int i=0; i<15; ++i) {
        for (int j=0; j<4; ++j) {
            for (int k=0; k<10; ++k) {
                characters[i].difficulties[j].scores[k].score = (10-k)*1000;
                characters[i].difficulties[j].scores[k].name[0] = 13;
                characters[i].difficulties[j].scores[k].name[1] = 14;
                characters[i].difficulties[j].scores[k].name[2] = 100;
                characters[i].difficulties[j].scores[k].name[3] = 4;
                characters[i].difficulties[j].scores[k].name[4] = 13;
                characters[i].difficulties[j].scores[k].name[5] = 19;
                characters[i].difficulties[j].scores[k].name[6] = 17;
                characters[i].difficulties[j].scores[k].name[7] = 24;
            }
        }
        for (int t=0; t<15; ++t)
            matchWinsByFighterPair[i][t] = 10;
    }
    workingPlayerName[0]=100;
    workingPlayerName[1]=100;
    workingPlayerName[2]=100;
    workingPlayerName[3]=100;
    workingPlayerName[4]=100;
    workingPlayerName[5]=100;
    workingPlayerName[6]=100;
    workingPlayerName[7]=100;
}
