#include "engine/GameProgress.hpp"
#include <time.h>
// F375 complete original ranked-score insertion using observed 16-byte game
// record. The date state contains exactly its two native meaningful values:
// time_t and localtime tm*, which also recovers original four EBP slots.
// No padding/fake locals and no complete original score owner assumed.
// Observed 16-byte game ranking record, not a complete original owner.
struct RankingDatesF375 { time_t timestamp; struct tm* today; };
unsigned char ProgressDifficulty::InsertRankedScore(unsigned int score) {
    if(score<=scores[9].score) return 255;
    {
        unsigned int index=9;
        RankingDatesF375 date;
        while(score>scores[index-1].score) {
            scores[index]=scores[index-1];
            --index;
            if(index==0) break;
        }
        time(&date.timestamp);
        date.today=localtime(&date.timestamp);
        scores[index].day=static_cast<unsigned char>(date.today->tm_mday);
        scores[index].month=static_cast<unsigned char>(date.today->tm_mon+1);
        scores[index].score=score;
        for (int i=0;i<8;++i) scores[index].name[i]=100;
        return static_cast<unsigned char>(index);
    }
}
