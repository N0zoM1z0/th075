#include "FighterScriptCounterWindowF1022.hpp"
#include "FighterVirtualActionsF159.hpp"
// Borrowed pointer receiver and 16 observed first-stage halfword fields.
class ReimuRoundF227 {
public:
    void ResetRound();
};
#define HALF(off) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(off)))
void ReimuRoundF227::ResetRound()
{
    F1022_SCRIPT(this).counterAtF00=0;
    F1022_SCRIPT(this).counterAtF02=0;
    HALF(0xf04)=0;
    HALF(0xf06)=0;
    HALF(0xf08)=0;
    HALF(0xefa)=0;
    HALF(0xf0a)=0;
    HALF(0xf2a)=0;
    HALF(0xf0c)=0;
    HALF(0xf22)=0;
    HALF(0xf24)=0;
    HALF(0xf26)=0;
    HALF(0xf28)=0;
    HALF(0x512)=0;
    HALF(0x514)=0;
    HALF(0x516)=0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
    HALF(0xefc)=0;
    HALF(0xefe)=0;
}
#undef HALF
