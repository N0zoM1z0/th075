#include <string.h>
// Call-only physical constructor hierarchy, not complete original class.
class BaseFighterCtorF309 {
public:
    BaseFighterCtorF309();
    virtual ~BaseFighterCtorF309();
};
class YukariCtorF309 : public BaseFighterCtorF309 {
public:
    YukariCtorF309();
    virtual ~YukariCtorF309();
};
extern const char g_YukariNameAt00659CB0[];
extern const char g_YukariTagAt00659CB8[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
YukariCtorF309::YukariCtorF309()
{
    FIELD(unsigned short,0xefc)=0;
    FIELD(unsigned short,0xefe)=0;
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_YukariNameAt00659CB0);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_YukariTagAt00659CB8);
    FIELD(unsigned short,0x478)=0x25e;
    FIELD(unsigned char,0x532)=12;
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
