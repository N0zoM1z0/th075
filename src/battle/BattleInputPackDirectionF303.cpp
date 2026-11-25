#include "battle/Fighter.hpp"
#include <windows.h>
#include <string.h>

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
    inputHistory.assign(90, bits);
}
