#include "YukariFighter.hpp"
#include "Fighter.hpp"
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
    fieldF10=0;
    fieldF12=0;
    fieldF14=0;
    fieldF16=0;
    fieldF18=0;
    fieldF1A=0;
    fieldEFA=0;
    fieldF0A=0;
    fieldF32=0;
    fieldF30=0;
    aiWaitTimer=0;
    aiStep=0;
    aiCardTimer=0;
    Fighter::ResetRound();
    sequenceTimer=0;
    fieldEFE=0;
}
