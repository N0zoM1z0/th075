#include "characters/YoumuFighter.hpp"
// Complete borrowed 27-pattern command-priority input controller. Each
// genuine pattern has its own original constant pool address. The receiver
// class and command string contents are not asserted beyond these reads.
extern const char g_ComboPatternAt00659920[];
extern const char g_ComboPatternAt00659928[];
extern const char g_ComboPatternAt00659930[] = "4136B";
extern const char g_ComboPatternAt00659938[] = "4136A";
extern const char g_ComboPatternAt00659940[] = "623B";
extern const char g_ComboPatternAt00659948[] = "623A";
extern const char g_ComboPatternAt00659950[] = "214B";
extern const char g_ComboPatternAt00659958[] = "214A";
extern const char g_ComboPatternAt00659960[] = "236D";
extern const char g_ComboPatternAt00659968[] = "236C";
extern const char g_ComboPatternAt00659970[] = "236B";
extern const char g_ComboPatternAt00659978[] = "236A";
extern const char g_ComboPatternAt00659980[] = "2N2D";
extern const char g_ComboPatternAt00659988[] = "2N2C";
extern const char g_ComboPatternAt00659990[] = "2N2B";
extern const char g_ComboPatternAt00659998[] = "2N2A";
extern const char g_ComboPatternAt006599A0[] = "N29";
extern const char g_ComboPatternAt006599A4[] = "N39";
extern const char g_ComboPatternAt006599A8[] = "N19";
extern const char g_ComboPatternAt006599AC[] = "N27";
extern const char g_ComboPatternAt006599B0[] = "N37";
extern const char g_ComboPatternAt006599B4[] = "N17";
extern const char g_ComboPatternAt006599B8[] = "N28";
extern const char g_ComboPatternAt006599BC[] = "N38";
extern const char g_ComboPatternAt006599C0[] = "N18";
extern const char g_ComboPatternAt006599C4[] = "NRNR";
extern const char g_ComboPatternAt006599CC[] = "NLNL";
#define STATUS aiCommand
void YoumuFighter::PollCommands() {
    STATUS = 0;
    if (MatchInputPattern(g_ComboPatternAt00659920,5,15)) STATUS=61;
    else if (MatchInputPattern(g_ComboPatternAt00659928,5,15)) STATUS=60;
    else if (MatchInputPattern(g_ComboPatternAt00659930,5,15)) STATUS=51;
    else if (MatchInputPattern(g_ComboPatternAt00659938,5,15)) STATUS=50;
    else if (MatchInputPattern(g_ComboPatternAt00659940,4,15)) STATUS=31;
    else if (MatchInputPattern(g_ComboPatternAt00659948,4,15)) STATUS=30;
    else if (MatchInputPattern(g_ComboPatternAt00659950,4,15)) STATUS=21;
    else if (MatchInputPattern(g_ComboPatternAt00659958,4,15)) STATUS=20;
    else if (MatchInputPattern(g_ComboPatternAt00659960,4,15)) STATUS=13;
    else if (MatchInputPattern(g_ComboPatternAt00659968,4,15)) STATUS=12;
    else if (MatchInputPattern(g_ComboPatternAt00659970,4,15)) STATUS=11;
    else if (MatchInputPattern(g_ComboPatternAt00659978,4,15)) STATUS=10;
    else if (MatchInputPattern(g_ComboPatternAt00659980,4,15)) STATUS=103;
    else if (MatchInputPattern(g_ComboPatternAt00659988,4,15)) STATUS=102;
    else if (MatchInputPattern(g_ComboPatternAt00659990,4,15)) STATUS=101;
    else if (MatchInputPattern(g_ComboPatternAt00659998,4,15)) STATUS=100;
    else if (MatchInputPattern(g_ComboPatternAt006599A0,3,10)) STATUS=5;
    else if (MatchInputPattern(g_ComboPatternAt006599A4,3,10)) STATUS=5;
    else if (MatchInputPattern(g_ComboPatternAt006599A8,3,10)) STATUS=5;
    else if (MatchInputPattern(g_ComboPatternAt006599AC,3,10)) STATUS=4;
    else if (MatchInputPattern(g_ComboPatternAt006599B0,3,10)) STATUS=4;
    else if (MatchInputPattern(g_ComboPatternAt006599B4,3,10)) STATUS=4;
    else if (MatchInputPattern(g_ComboPatternAt006599B8,3,10)) STATUS=3;
    else if (MatchInputPattern(g_ComboPatternAt006599BC,3,10)) STATUS=3;
    else if (MatchInputPattern(g_ComboPatternAt006599C0,3,10)) STATUS=3;
    else if (MatchInputPattern(g_ComboPatternAt006599C4,4,15)) STATUS=1;
    else if (MatchInputPattern(g_ComboPatternAt006599CC,4,15)) STATUS=2;
}
#undef STATUS
