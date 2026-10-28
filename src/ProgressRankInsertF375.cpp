#include <time.h>
// F375 complete original ranked-score insertion using observed 16-byte game
// record. The date state contains exactly its two native meaningful values:
// time_t and localtime tm*, which also recovers original four EBP slots.
// No padding/fake locals and no complete original score owner assumed.
// Observed 16-byte game ranking record, not a complete original owner.
struct RankedEntryF375 {
    unsigned char name[8];
    unsigned char month;
    unsigned char day;
    unsigned short otherObservedRecordBytes;
    unsigned int score;
};
typedef char VerifyRankedEntry16F375[(sizeof(RankedEntryF375)==16)?1:-1];
class ProgressRankingF375 {public: unsigned char InsertRankedScore(unsigned int score);};
#define RANK(i) (reinterpret_cast<RankedEntryF375*>(reinterpret_cast<unsigned char*>(this)+0x55C)[(i)])
#define MINIMUM (*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this)+0x5F8))
struct RankingDatesF375 { time_t timestamp; struct tm* today; };
unsigned char ProgressRankingF375::InsertRankedScore(unsigned int score) {
    if(score<=MINIMUM) return 255;
    {
        unsigned int index=9;
        RankingDatesF375 date;
        while(score>RANK(index-1).score) {
            RANK(index)=RANK(index-1);
            --index;
            if(index==0) break;
        }
        time(&date.timestamp);
        date.today=localtime(&date.timestamp);
        RANK(index).day=static_cast<unsigned char>(date.today->tm_mday);
        RANK(index).month=static_cast<unsigned char>(date.today->tm_mon+1);
        RANK(index).score=score;
        for (int i=0;i<8;++i) RANK(index).name[i]=100;
        return static_cast<unsigned char>(index);
    }
}
#undef MINIMUM
#undef RANK
