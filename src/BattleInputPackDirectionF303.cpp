#include <windows.h>
#include <string.h>
// Borrow the native physical fighter input and command deque call boundary,
// not a complete original fighter/VC7 container layout.
class FighterCommandQueueF303 {public: void Queue(int frames,const unsigned char* packed);};
class FighterInputF303 {public: void PackDirectionBits();public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x4DC - 0x000];
    int field4DC;
    int field4E0;
    unsigned char unknown4E4[0x4E8 - 0x4E4];
    unsigned int field4E8;
    unsigned int field4EC;
    unsigned int field4F0;
    unsigned int field4F4;
};
void FighterInputF303::PackDirectionBits()
{
    unsigned char bits=(field4DC<0);
    bits|=static_cast<unsigned char>(field4DC>0)<<1;
    bits|=static_cast<unsigned char>(field4E0<0)<<2;
    bits|=static_cast<unsigned char>(field4E0>0)<<3;
    bits|=static_cast<unsigned char>(field4E8>0)<<4;
    bits|=static_cast<unsigned char>(field4EC>0)<<5;
    bits|=static_cast<unsigned char>(field4F0>0)<<6;
    bits|=static_cast<unsigned char>(field4F4>0)<<7;
    unsigned int scratch[7];
    memset(scratch,0,sizeof(scratch));
    reinterpret_cast<FighterCommandQueueF303*>(reinterpret_cast<unsigned char*>(this)+0x518)->Queue(90,&bits);
}
