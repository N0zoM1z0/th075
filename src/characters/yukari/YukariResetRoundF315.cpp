#include "characters/yukari/YukariFighter.hpp"
#include "battle/Fighter.hpp"
// The code is a complete native-observed fighter round reset, not a claim to
// reconstruct the entire parent fighter private object class or its callee.
void YukariFighter::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    fieldF04=0;
    fieldF06=0;
    fieldF08=0;
    fieldF0A=0;
    fieldF0C=0;
    fieldF0E=0;
    bouncingSpellObjectActive=0;
    spellOrbitAngle=0;
    spellOrbitRadius=0;
    spellOrbitPhase=0;
    spellOrbitCenterX=0;
    spellOrbitCenterY=0;
    fieldEFA=0;
    fieldF0A=0;
    longRangeFrames=0;
    storedClashCount=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    Fighter::ResetRound();
    sequenceTimer=0;
    stageBannerHoldFrames=0;
}
