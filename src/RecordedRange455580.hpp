#pragma once

// Declaration-only receiver views. Their complete layouts remain unknown.
// Never construct or embed either owner; use only the observed call contracts.
class RecordedSamples455580View {
public:
    unsigned int Count() const;
    short& Front();
    void PopFront();
    void PushBack(const short& sample);
};
class RecordedRange455580 {
public:
    int SelectRange(int lower, int upper);
};

extern signed char g_FrameClockMode;
// External storage view only; the original container type and extent are unknown.
extern unsigned char g_RecordedSamplesAt006718B8[];
