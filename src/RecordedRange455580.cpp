#include "RecordedRange455580.hpp"
#include <cstdlib>

#define SAMPLES reinterpret_cast<RecordedSamples455580View*>(g_RecordedSamplesAt006718B8)

int RecordedRange455580::SelectRange(int lower, int upper) {
    short sample = 0;
    if (g_FrameClockMode == 2) {
        if (SAMPLES->Count() > 0) {
            sample = SAMPLES->Front();
            SAMPLES->PopFront();
        }
    } else {
        sample = static_cast<short>(std::rand());
        if (g_FrameClockMode == 1)
            SAMPLES->PushBack(sample);
    }
    return (upper - lower) * sample / 32768 + lower;
}

#undef SAMPLES
