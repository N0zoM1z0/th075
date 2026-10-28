#include <windows.h>
// Only real physical font surface slots are borrowed, not a full owner.
class FontConfigureF293 {
public:
 void ConfigureText(DWORD x,DWORD y,unsigned char mode);
};
#define F(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void FontConfigureF293::ConfigureText(DWORD x,DWORD y,unsigned char mode)
{
 F(DWORD,4)=x;
 F(DWORD,8)=y;
 F(DWORD,0x10)=0;
 F(unsigned char,0x15)=0;
 F(unsigned char,0x14)=0;
 F(unsigned char,0x25)=mode;
}
#undef F
