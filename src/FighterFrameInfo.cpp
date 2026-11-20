#include <windows.h>
#include "Actor.hpp"

// Memberwise copy used by the frame-record range operations at 0045A7E0,
// 0045A980 and their shared 0045AAE0 assignment routine.
FighterFrameInfo& FighterFrameInfo::operator=(const FighterFrameInfo& other)
{
    header = other.header;
    damage = other.damage;
    comboRateScale = other.comboRateScale;
    field18 = other.field18;
    field1A = other.field1A;
    attackerHitStop = other.attackerHitStop;
    defenderHitStop = other.defenderHitStop;
    field20 = other.field20;
    field22 = other.field22;
    meterGain = other.meterGain;
    field26 = other.field26;
    field28 = other.field28;
    field2A = other.field2A;
    field2C = other.field2C;
    field30 = other.field30;
    field34 = other.field34;
    hitEffect = other.hitEffect;
    field38 = other.field38;
    flags = other.flags;
    attackFlags = other.attackFlags;
    bodyBox = other.bodyBox;
    hurtBoxes = other.hurtBoxes;
    hitBoxes = other.hitBoxes;
    return *this;
}
