#include "FighterVirtualActionsF159.hpp"
// Physical field receiver, not a complete reconstructed fighter object.
class YoumuSubcomponentF224 {
public:
    void ResetRound();
};
class YoumuRoundF224 {
public:
    void ResetRound();
};
#define HALF(offset) (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void YoumuRoundF224::ResetRound()
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
    HALF(0xf0e)=0;
    HALF(0xf10)=0;
    HALF(0xf12)=0;
    HALF(0x512)=0;
    HALF(0x514)=0;
    HALF(0x516)=0;
    reinterpret_cast<FighterBaseActionsF159*>(this)->ResetRound();
    reinterpret_cast<YoumuSubcomponentF224*>(reinterpret_cast<unsigned char*>(this)+0xfec)->ResetRound();
}
#undef HALF
