#pragma once

// Call-only receiver view. The private owner is incomplete; never instantiate
// or embed this view. Arguments/results describe the observed used byte ABI.
class FighterInputSequenceF165 {
public:
    unsigned char MatchSequence(const char* text, signed char count, signed char historyOffset);
};
