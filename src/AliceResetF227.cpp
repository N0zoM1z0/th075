#include "FighterVirtualActionsF159.hpp"
// Borrowed pointer receiver and 17 observed halfword fields.
class AliceRoundF227 {
public:
    void ResetRound();
};
#define HALF(off) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(off)))
void AliceRoundF227::ResetRound()
{
    HALF(0xefc)=0;
    HALF(0xefe)=0;
    HALF(0xefa)=0;
    HALF(0xf14)=0;
    HALF(0xf00)=0;
    HALF(0xf02)=0;
    HALF(0xf04)=0;
    HALF(0xf06)=0;
    HALF(0xf08)=0;
    HALF(0xf0a)=0;
    HALF(0xf0c)=0;
    HALF(0xf0e)=0;
    HALF(0xf10)=0;
    HALF(0xf12)=0;
    HALF(0x512)=0;
    HALF(0x514)=0;
    HALF(0x516)=0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
}
#undef HALF
