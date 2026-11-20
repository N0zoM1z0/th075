#include "CharacterInput5E6F70.hpp"


void MeilingFighter::PollCommands() {
    aiCommand = 0;
    if (MatchInputPattern("236236D", 7, 30))
        aiCommand = 113;
    else if (MatchInputPattern("421B", 4, 15))
        aiCommand = 41;
    else if (MatchInputPattern("421A", 4, 15))
        aiCommand = 40;
    else if (MatchInputPattern("623C", 4, 15))
        aiCommand = 32;
    else if (MatchInputPattern("623B", 4, 15))
        aiCommand = 31;
    else if (MatchInputPattern("623A", 4, 15))
        aiCommand = 30;
    else if (MatchInputPattern("214B", 4, 15))
        aiCommand = 21;
    else if (MatchInputPattern("214A", 4, 15))
        aiCommand = 20;
    else if (MatchInputPattern("236D", 4, 15))
        aiCommand = 13;
    else if (MatchInputPattern("236B", 4, 15))
        aiCommand = 11;
    else if (MatchInputPattern("236A", 4, 15))
        aiCommand = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        aiCommand = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        aiCommand = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        aiCommand = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        aiCommand = 100;
    else if (MatchInputPattern("NRNR", 4, 15))
        aiCommand = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        aiCommand = 2;
    else if (MatchInputPattern("N29", 3, 10))
        aiCommand = 5;
    else if (MatchInputPattern("N39", 3, 10))
        aiCommand = 5;
    else if (MatchInputPattern("N19", 3, 10))
        aiCommand = 5;
    else if (MatchInputPattern("N27", 3, 10))
        aiCommand = 4;
    else if (MatchInputPattern("N37", 3, 10))
        aiCommand = 4;
    else if (MatchInputPattern("N17", 3, 10))
        aiCommand = 4;
    else if (MatchInputPattern("N28", 3, 10))
        aiCommand = 3;
    else if (MatchInputPattern("N38", 3, 10))
        aiCommand = 3;
    else if (MatchInputPattern("N18", 3, 10))
        aiCommand = 3;
}
