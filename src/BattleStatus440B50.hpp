#pragma once
#include "BattleHud43E040.hpp"

// Pointer-only view. The complete native getters return a zero-extended word
// in EAX, which their callers consume as a full integer. Original nominal
// declarations and the complete record owner layout remain unknown.
class StatusRecords440B50 {
public:
    int GetValueAt0268(signed char);
    int GetValueAt0394(signed char);
};
extern signed char g_StateRepeatLevelAt006714D0;
