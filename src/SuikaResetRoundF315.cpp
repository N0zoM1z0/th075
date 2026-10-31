#include "FighterScriptCounterWindowF1022.hpp"
// Physical fighter-offset view only; inherited game Round reset is borrowed.
class SuikaRoundF315 {
public:
    void ResetBaseRound();
    void ResetRound();
};
extern unsigned char g_SuikaGlobalMarkerAt0066C23A;
extern unsigned char g_SuikaGlobalModeAt0066C239;
#define W(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void SuikaRoundF315::ResetRound()
{
    W(0xefc)=0;
    W(0xefe)=0;
    F1022_SCRIPT(this).counterAtF00=0;
    F1022_SCRIPT(this).counterAtF02=0;
    W(0xf04)=0;
    W(0xf06)=0;
    W(0xefa)=0;
    W(0xf06)=0;
    W(0xf26)=0;
    W(0xf1c)=0;
    W(0xf1e)=0;
    W(0xf20)=0;
    W(0xf22)=0;
    W(0xf24)=0;
    W(0x512)=0;
    W(0x514)=0;
    W(0x516)=0;
    g_SuikaGlobalMarkerAt0066C23A=0xff;
    g_SuikaGlobalModeAt0066C239=0xff;
    ResetBaseRound();
    W(0xf28)=0;
    W(0xf2a)=0;
}
#undef W
