// F739: natural original game record constructors with real member
// lifetime and EH cleanup. Private member type/layout names unproved.
#include <windows.h>
#include "battle/Actor.hpp"

FighterSequenceInfo::FighterSequenceInfo()
{
    frames.clear();
    targetPriority = 0;
    priority = 0;
}
FighterSequenceInfo::~FighterSequenceInfo()
{
    frames.clear();
}
