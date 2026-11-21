#include <stddef.h>

// Borrowed receiver prefix for the complete BG05b counter callback. Only the
// three signed 32-bit fields at +0x68/+0x6C/+0x70 are observed; the preceding
// bytes and the full background owner extent remain unknown. Use only through
// the original this pointer, never instantiate or embed this view.
class BackgroundCountersF746 {
public:
    unsigned char unknown000[0x68];
    int timerAt68;
    int stageTickAt6C;
    int counterAt70;

    void AdvanceBG05bCounters();
};
typedef char BackgroundCountersF746Offsets[
    (offsetof(BackgroundCountersF746, timerAt68) == 0x68 &&
     offsetof(BackgroundCountersF746, stageTickAt6C) == 0x6C &&
     offsetof(BackgroundCountersF746, counterAt70) == 0x70) ? 1 : -1];

void BackgroundCountersF746::AdvanceBG05bCounters() {
    --timerAt68;
    if (timerAt68 < 0) timerAt68 = 0xF00;
    ++stageTickAt6C;
    if (stageTickAt6C >= 42) stageTickAt6C = 0;
    ++counterAt70;
}
