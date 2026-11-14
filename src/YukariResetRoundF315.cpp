#include "Fighter.hpp"
// The code is a complete native-observed fighter round reset, not a claim to
// reconstruct the entire parent fighter private object class or its callee.
class YukariRoundF315 : public Fighter {
public:
    void ResetBaseRound();
    void ResetRound();
public:
    // Fields after the shared Fighter layout.
    unsigned short fieldF10;
    unsigned short fieldF12;
    unsigned short fieldF14;
    unsigned short fieldF16;
    unsigned short fieldF18;
    unsigned short fieldF1A;
    unsigned char unknownF1C[0xF30 - 0xF1C];
    unsigned short fieldF30;
    unsigned short fieldF32;
};
void YukariRoundF315::ResetRound()
{
    scriptCounterF00=0;
    scriptCounterF02=0;
    reinterpret_cast<unsigned short&>(fieldF04)=0;
    fieldF06=0;
    fieldF08=0;
    reinterpret_cast<unsigned short&>(fieldF0A)=0;
    reinterpret_cast<unsigned short&>(fieldF0C)=0;
    reinterpret_cast<unsigned short&>(fieldF0E)=0;
    fieldF10=0;
    fieldF12=0;
    fieldF14=0;
    fieldF16=0;
    fieldF18=0;
    fieldF1A=0;
    fieldEFA=0;
    reinterpret_cast<unsigned short&>(fieldF0A)=0;
    fieldF32=0;
    fieldF30=0;
    reinterpret_cast<unsigned short&>(aiWaitTimer)=0;
    reinterpret_cast<unsigned short&>(aiStep)=0;
    reinterpret_cast<unsigned short&>(aiCardTimer)=0;
    ResetBaseRound();
    reinterpret_cast<unsigned short&>(sequenceTimer)=0;
    fieldEFE=0;
}
