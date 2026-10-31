#include "FighterScriptCounterWindowF1022.hpp"
// The code is a complete native-observed fighter round reset, not a claim to
// reconstruct the entire parent fighter private object class or its callee.
class YukariRoundF315 {
public:
    void ResetBaseRound();
    void ResetRound();
};
#define W(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void YukariRoundF315::ResetRound()
{
    F1022_SCRIPT(this).counterAtF00=0;
    F1022_SCRIPT(this).counterAtF02=0;
    W(0xf04)=0;
    W(0xf06)=0;
    W(0xf08)=0;
    W(0xf0a)=0;
    W(0xf0c)=0;
    W(0xf0e)=0;
    W(0xf10)=0;
    W(0xf12)=0;
    W(0xf14)=0;
    W(0xf16)=0;
    W(0xf18)=0;
    W(0xf1a)=0;
    W(0xefa)=0;
    W(0xf0a)=0;
    W(0xf32)=0;
    W(0xf30)=0;
    W(0x512)=0;
    W(0x514)=0;
    W(0x516)=0;
    ResetBaseRound();
    W(0xefc)=0;
    W(0xefe)=0;
}
#undef W
