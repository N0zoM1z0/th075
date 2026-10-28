#include <windows.h>
#include <string.h>
// Borrow the native physical fighter input and command deque call boundary,
// not a complete original fighter/VC7 container layout.
class FighterCommandQueueF303 {public: void Queue(int frames,const unsigned char* packed);};
class FighterInputF303 {public: void PackDirectionBits();};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void FighterInputF303::PackDirectionBits()
{
    unsigned char bits=(FIELD(int,0x4dc)<0);
    bits|=static_cast<unsigned char>(FIELD(int,0x4dc)>0)<<1;
    bits|=static_cast<unsigned char>(FIELD(int,0x4e0)<0)<<2;
    bits|=static_cast<unsigned char>(FIELD(int,0x4e0)>0)<<3;
    bits|=static_cast<unsigned char>(FIELD(unsigned int,0x4e8)>0)<<4;
    bits|=static_cast<unsigned char>(FIELD(unsigned int,0x4ec)>0)<<5;
    bits|=static_cast<unsigned char>(FIELD(unsigned int,0x4f0)>0)<<6;
    bits|=static_cast<unsigned char>(FIELD(unsigned int,0x4f4)>0)<<7;
    unsigned int scratch[7];
    memset(scratch,0,sizeof(scratch));
    reinterpret_cast<FighterCommandQueueF303*>(reinterpret_cast<unsigned char*>(this)+0x518)->Queue(90,&bits);
}
#undef FIELD
