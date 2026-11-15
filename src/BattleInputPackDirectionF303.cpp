#include "Fighter.hpp"
#include <windows.h>
#include <string.h>
// Borrow the native physical fighter input and command deque call boundary,
// not a complete original fighter/VC7 container layout.
class FighterCommandQueueF303 {public: void Queue(int frames,const unsigned char* packed);};
void Fighter::PackDirectionBits()
{
    unsigned char bits=(inputX<0);
    bits|=static_cast<unsigned char>(inputX>0)<<1;
    bits|=static_cast<unsigned char>(inputY<0)<<2;
    bits|=static_cast<unsigned char>(inputY>0)<<3;
    bits|=static_cast<unsigned char>(reinterpret_cast<unsigned int&>(inputA)>0)<<4;
    bits|=static_cast<unsigned char>(reinterpret_cast<unsigned int&>(inputB)>0)<<5;
    bits|=static_cast<unsigned char>(reinterpret_cast<unsigned int&>(inputC)>0)<<6;
    bits|=static_cast<unsigned char>(reinterpret_cast<unsigned int&>(inputD)>0)<<7;
    unsigned int scratch[7];
    memset(scratch,0,sizeof(scratch));
    reinterpret_cast<FighterCommandQueueF303*>(reinterpret_cast<unsigned char*>(this)+0x518)->Queue(90,&bits);
}
