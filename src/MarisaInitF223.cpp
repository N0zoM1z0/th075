#include <string.h>
// Call-only physical constructor hierarchy, not complete original class.
class BaseFighterCtorF223 {
public:
    BaseFighterCtorF223();
    virtual ~BaseFighterCtorF223();
};
class MarisaCtorF223 : public BaseFighterCtorF223 {
public:
    MarisaCtorF223();
    virtual ~MarisaCtorF223();
};
extern const char g_MarisaNameAt006592A8[];
extern const char g_MarisaTagAt006592B0[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
MarisaCtorF223::MarisaCtorF223()
{
    FIELD(unsigned short,0xefc)=0;
    FIELD(unsigned short,0xefe)=0;
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_MarisaNameAt006592A8);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_MarisaTagAt006592B0);
    FIELD(unsigned short,0x478)=0x299;
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
