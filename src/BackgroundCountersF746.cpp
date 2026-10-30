// F746 native authored R212 BackgroundStage counters; no dummy locals.
// Original whole 0044E8D0: decrement timer at +0x68, wrap below 0
// to 0xF00, advance modulo-42 stage tick at +0x6C, and add +0x70.
class BackgroundCountersF746 {
public:
 void AdvanceBG05bCounters();
};
#define FIELD(off) (*reinterpret_cast<int*>(reinterpret_cast<char*>(this)+(off)))
void BackgroundCountersF746::AdvanceBG05bCounters() {
    --FIELD(0x68);
    if (FIELD(0x68)<0) FIELD(0x68)=0xF00;
    ++FIELD(0x6C);
    if (FIELD(0x6C)>=42) FIELD(0x6C)=0;
    ++FIELD(0x70);
}
#undef FIELD
