#include <string.h>
// Call-only physical constructor hierarchy, not complete original class.
class BaseFighterCtorF311 {
public:
    BaseFighterCtorF311();
    virtual ~BaseFighterCtorF311();
};
class YuyukoCtorF311 : public BaseFighterCtorF311 {
public:
    YuyukoCtorF311();
    virtual ~YuyukoCtorF311();
};
extern const char g_YuyukoNameAt00659B74[];
extern const char g_YuyukoTagAt00659B7C[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
YuyukoCtorF311::YuyukoCtorF311()
{
    FIELD(unsigned short,0xefc)=0;
    FIELD(unsigned short,0xefe)=0;
    FIELD(unsigned short,0xefa)=0;
    FIELD(unsigned short,0xf10)=0;
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_YuyukoNameAt00659B74);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_YuyukoTagAt00659B7C);
    FIELD(unsigned short,0x478)=0x21c;
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
