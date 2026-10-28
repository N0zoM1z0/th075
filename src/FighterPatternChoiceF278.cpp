#include <stdlib.h>
#include <string.h>

// Only native observed fighter state fields and game-specific pattern
// interfaces are borrowed; no complete fighter or pattern owner is inferred.
class PatternCatalogF277 {
public:
    short Count(short sequence);
    short Weight(short sequence,short index);
    signed char Flag(short sequence,short index);
    const char* Name(short sequence,short index);
};
extern signed char g_SecondFighterCharacterAt006714C8[];
extern const char g_DefaultActionNameAt00659078[];
class FighterPatternChoiceF277 {
public:
    void ChoosePatternSequence();
};
#define RAW reinterpret_cast<unsigned char*>(this)
#define FIELD(type,off) (*reinterpret_cast<type*>(RAW+(off)))
#define PATTERN reinterpret_cast<PatternCatalogF277*>(RAW+0x714)
#define INDEX FIELD(signed char,0x53a)
#define ACTION(k) (RAW+0x53b+(signed char)(k)*200)
#define KIND(k) FIELD(unsigned char,0x6cb+(signed char)(k))
void FighterPatternChoiceF277::ChoosePatternSequence()
{
    unsigned int cursor;
    short accumulated;
    {
    short target = static_cast<short>(rand()%256);
    accumulated=0;
    INDEX=0;
    short sequence=static_cast<short>(g_SecondFighterCharacterAt006714C8[1-FIELD(signed char,0x2cc)]+200);
    cursor=0;
    while(static_cast<int>(cursor)<static_cast<int>(PATTERN->Count(sequence))) {
        accumulated+=PATTERN->Weight(sequence,static_cast<short>(cursor));
        ++cursor;
        if(target<accumulated) {
            KIND(INDEX)=static_cast<unsigned char>(PATTERN->Weight(sequence,static_cast<short>(cursor)));
            strcpy(reinterpret_cast<char*>(ACTION(INDEX)),PATTERN->Name(sequence,static_cast<short>(cursor)));
            ++cursor;
            ++INDEX;
            if (static_cast<int>(cursor)<static_cast<int>(PATTERN->Count(sequence))) {
            if (PATTERN->Flag(sequence,static_cast<short>(cursor))==0) {
            KIND(INDEX)=static_cast<unsigned char>(PATTERN->Weight(sequence,static_cast<short>(cursor)));
            strcpy(reinterpret_cast<char*>(ACTION(INDEX)),PATTERN->Name(sequence,static_cast<short>(cursor)));
            ++INDEX;
            }
            }
            return;
        }
        if(cursor==static_cast<unsigned int>(PATTERN->Count(sequence))) break;
        while(PATTERN->Flag(sequence,static_cast<short>(cursor))!='\r') {
            ++cursor;
            if(cursor==static_cast<unsigned int>(PATTERN->Count(sequence))) break;
        }
    }
    target=static_cast<short>(rand()%256);
    accumulated=0;
    sequence=300;
    INDEX=0;
    cursor=0;
    while (static_cast<int>(cursor)<static_cast<int>(PATTERN->Count(sequence))) {
        accumulated+=PATTERN->Weight(sequence,static_cast<short>(cursor));
        ++cursor;
        if (target<accumulated) {
            KIND(INDEX)=static_cast<unsigned char>(PATTERN->Weight(sequence,static_cast<short>(cursor)));
            strcpy(reinterpret_cast<char*>(ACTION(INDEX)),PATTERN->Name(sequence,static_cast<short>(cursor)));
            ++cursor;
            ++INDEX;
            if (static_cast<int>(cursor)<static_cast<int>(PATTERN->Count(sequence))) {
            if(PATTERN->Flag(sequence,static_cast<short>(cursor))==0) {
            KIND(INDEX)=static_cast<unsigned char>(PATTERN->Weight(sequence,static_cast<short>(cursor)));
            strcpy(reinterpret_cast<char*>(ACTION(INDEX)),PATTERN->Name(sequence,static_cast<short>(cursor)));
            ++INDEX;
            }
            }
            return;
        }
        if(cursor==static_cast<unsigned int>(PATTERN->Count(sequence))) break;
        while(PATTERN->Flag(sequence,static_cast<short>(cursor))!='\r') {
            ++cursor;
            if(cursor==static_cast<unsigned int>(PATTERN->Count(sequence))) break;
        }
    }
    INDEX=0;
    KIND(INDEX)=0;
    strcpy(reinterpret_cast<char*>(ACTION(INDEX)),g_DefaultActionNameAt00659078);
    }
}
#undef KIND
#undef ACTION
#undef INDEX
#undef PATTERN
#undef FIELD
#undef RAW
