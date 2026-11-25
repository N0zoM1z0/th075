#include "battle/Fighter.hpp"
#include "battle/PlayerState.hpp"
#include <stdlib.h>
#include <string.h>

extern const char g_DefaultActionNameAt00659078[] = "";
void Fighter::ChoosePatternSequence()
{
    unsigned int cursor;
    short accumulated;
    {
    short target = static_cast<short>(rand()%256);
    accumulated=0;
    quoteLineCount=0;
    short sequence=static_cast<short>(g_PlayerIdAt006714C8[1-playerSide]+200);
    cursor=0;
    while(static_cast<int>(cursor)<static_cast<int>(script.CountPatternEntries(sequence))) {
        accumulated+=script.GetWordField(sequence,static_cast<short>(cursor));
        ++cursor;
        if(target<accumulated) {
            quoteBadges[quoteLineCount]=static_cast<unsigned char>(script.GetWordField(sequence,static_cast<short>(cursor)));
            strcpy(quoteLines[quoteLineCount],static_cast<const char*>(script.GetDwordField(sequence,static_cast<short>(cursor))));
            ++cursor;
            ++quoteLineCount;
            if (static_cast<int>(cursor)<static_cast<int>(script.CountPatternEntries(sequence))) {
            if (script.GetByteField(sequence,static_cast<short>(cursor))==0) {
            quoteBadges[quoteLineCount]=static_cast<unsigned char>(script.GetWordField(sequence,static_cast<short>(cursor)));
            strcpy(quoteLines[quoteLineCount],static_cast<const char*>(script.GetDwordField(sequence,static_cast<short>(cursor))));
            ++quoteLineCount;
            }
            }
            return;
        }
        if(cursor==static_cast<unsigned int>(script.CountPatternEntries(sequence))) break;
        while(script.GetByteField(sequence,static_cast<short>(cursor))!='\r') {
            ++cursor;
            if(cursor==static_cast<unsigned int>(script.CountPatternEntries(sequence))) break;
        }
    }
    target=static_cast<short>(rand()%256);
    accumulated=0;
    sequence=300;
    quoteLineCount=0;
    cursor=0;
    while (static_cast<int>(cursor)<static_cast<int>(script.CountPatternEntries(sequence))) {
        accumulated+=script.GetWordField(sequence,static_cast<short>(cursor));
        ++cursor;
        if (target<accumulated) {
            quoteBadges[quoteLineCount]=static_cast<unsigned char>(script.GetWordField(sequence,static_cast<short>(cursor)));
            strcpy(quoteLines[quoteLineCount],static_cast<const char*>(script.GetDwordField(sequence,static_cast<short>(cursor))));
            ++cursor;
            ++quoteLineCount;
            if (static_cast<int>(cursor)<static_cast<int>(script.CountPatternEntries(sequence))) {
            if(script.GetByteField(sequence,static_cast<short>(cursor))==0) {
            quoteBadges[quoteLineCount]=static_cast<unsigned char>(script.GetWordField(sequence,static_cast<short>(cursor)));
            strcpy(quoteLines[quoteLineCount],static_cast<const char*>(script.GetDwordField(sequence,static_cast<short>(cursor))));
            ++quoteLineCount;
            }
            }
            return;
        }
        if(cursor==static_cast<unsigned int>(script.CountPatternEntries(sequence))) break;
        while(script.GetByteField(sequence,static_cast<short>(cursor))!='\r') {
            ++cursor;
            if(cursor==static_cast<unsigned int>(script.CountPatternEntries(sequence))) break;
        }
    }
    quoteLineCount=0;
    quoteBadges[quoteLineCount]=0;
    strcpy(quoteLines[quoteLineCount],g_DefaultActionNameAt00659078);
    }
}
