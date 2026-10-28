#include <string.h>
// Call-only physical constructor hierarchy, not complete original class.
class BaseFighterCtorF309 {
public:
    BaseFighterCtorF309();
    virtual ~BaseFighterCtorF309();
};
class SuikaCtorF309 : public BaseFighterCtorF309 {
public:
    SuikaCtorF309();
    virtual ~SuikaCtorF309();
};
extern const char g_SuikaNameAt00659E24[];
extern const char g_SuikaTagAt00659E2C[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
SuikaCtorF309::SuikaCtorF309()
{
    FIELD(unsigned short,0xf28)=0;
    FIELD(unsigned short,0xf2a)=0;
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_SuikaNameAt00659E24);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_SuikaTagAt00659E2C);
    FIELD(unsigned short,0x478)=0x2a6;
    FIELD(unsigned char,0x532)=10;
    FIELD(float,0x6c)=-10.0f;
    FIELD(unsigned char,0x705)=4;
    FIELD(unsigned char,0x706)=4;
    FIELD(unsigned char,0x707)=4;
    FIELD(unsigned char,0x708)=4;
    FIELD(unsigned char,0x709)=4;
    FIELD(unsigned char,0x70a)=4;
    FIELD(unsigned char,0x70b)=4;
    FIELD(unsigned char,0x70c)=1;
    FIELD(unsigned char,0x70d)=1;
    FIELD(unsigned char,0x70e)=3;
}
#undef FIELD
