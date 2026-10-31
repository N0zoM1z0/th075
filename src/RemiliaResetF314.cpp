#include "FighterScriptCounterWindowF1022.hpp"
#include "FighterVirtualActionsF159.hpp"
// Exact native-observed fighter short fields only; no full private layout.
class RemiliaRoundF314 {public: void ResetRound();};
#define HALF(off) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(off)))
void RemiliaRoundF314::ResetRound()
{
    HALF(0xefc)=0;
    HALF(0xefe)=0;
    HALF(0xefa)=0;
    HALF(0xf0c)=0;
    F1022_SCRIPT(this).counterAtF00=0;
    F1022_SCRIPT(this).counterAtF02=0;
    HALF(0xf04)=0;
    HALF(0xf06)=0;
    HALF(0xf08)=0;
    HALF(0xf0a)=0;
    HALF(0x512)=0;
    HALF(0x514)=0;
    HALF(0x516)=0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
}
#undef HALF
