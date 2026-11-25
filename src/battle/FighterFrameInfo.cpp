#include <windows.h>
#include "battle/Actor.hpp"

// Memberwise copy used by the frame-record range operations at 0045A7E0,
// 0045A980 and their shared 0045AAE0 assignment routine.
FighterFrameInfo& FighterFrameInfo::operator=(const FighterFrameInfo& other)
{
    static_cast<FighterFrameInfoHeader&>(*this) = other;
    damage = other.damage;
    comboRateScale = other.comboRateScale;
    guardDamage = other.guardDamage;
    baseHitstun = other.baseHitstun;
    attackerHitStop = other.attackerHitStop;
    defenderHitStop = other.defenderHitStop;
    guardAttackerHitStop = other.guardAttackerHitStop;
    guardDefenderHitStop = other.guardDefenderHitStop;
    meterGain = other.meterGain;
    guardSpellCharge = other.guardSpellCharge;
    airHitAction = other.airHitAction;
    groundHitAction = other.groundHitAction;
    reactionVelocityX = other.reactionVelocityX;
    reactionVelocityY = other.reactionVelocityY;
    hitSound = other.hitSound;
    hitEffect = other.hitEffect;
    reactionVariant = other.reactionVariant;
    flags = other.flags;
    attackFlags = other.attackFlags;
    bodyBox = other.bodyBox;
    hurtBoxes = other.hurtBoxes;
    hitBoxes = other.hitBoxes;
    return *this;
}
