#include "Fighter.hpp"
#include <windows.h>
#include <string.h>
// The input-history subobject begins with Fighter::inputHistory; its native
// queue operation is exposed through a borrowed call-only interface.
class FighterCommandQueueF303 {public: void Queue(int frames,const unsigned char* packed);};
void Fighter::PackDirectionBits()
{
    unsigned char bits=(inputX<0);
    bits|=static_cast<unsigned char>(inputX>0)<<1;
    bits|=static_cast<unsigned char>(inputY<0)<<2;
    bits|=static_cast<unsigned char>(inputY>0)<<3;
    bits|=static_cast<unsigned char>(static_cast<unsigned int>(inputA)>0)<<4;
    bits|=static_cast<unsigned char>(static_cast<unsigned int>(inputB)>0)<<5;
    bits|=static_cast<unsigned char>(static_cast<unsigned int>(inputC)>0)<<6;
    bits|=static_cast<unsigned char>(static_cast<unsigned int>(inputD)>0)<<7;
    unsigned int scratch[7];
    memset(scratch,0,sizeof(scratch));
    reinterpret_cast<FighterCommandQueueF303*>(&inputHistory)->Queue(90,&bits);
}
