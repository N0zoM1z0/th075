// Full SDK front operations and a complete synthetic derived alternative.
#include "VC7ReplayDequeIterators.cpp"

unsigned char& ObserveReplayFrontByte(ReplayDequeByte& entries) { return entries.front(); }
unsigned short& ObserveReplayFrontWord(ReplayDequeWord& entries) { return entries.front(); }
unsigned long& ObserveReplayFrontDword(ReplayDequeDword& entries) { return entries.front(); }

struct OrdinaryReplayFront : ReplayDequeByte {
    unsigned char& first() { return *begin(); }
};
unsigned char& ObserveOrdinaryReplayFront(OrdinaryReplayFront& entries) { return entries.first(); }
extern "C" const unsigned long ReplayFrontLayout[] = {
    sizeof(unsigned char), sizeof(unsigned short), sizeof(unsigned long),
    sizeof(ReplayDequeByte), sizeof(ReplayDequeWord), sizeof(ReplayDequeDword),
    sizeof(OrdinaryReplayFront)
};
