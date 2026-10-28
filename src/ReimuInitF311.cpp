#include <string.h>
// Call-only physical constructor hierarchy, not complete original class.
class BaseFighterCtorF311 {
public:
    BaseFighterCtorF311();
    virtual ~BaseFighterCtorF311();
};
class ReimuCtorF311 : public BaseFighterCtorF311 {
public:
    ReimuCtorF311();
    virtual ~ReimuCtorF311();
};
extern const char g_ReimuNameAt006590C8[];
extern const char g_ReimuTagAt006590D0[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
ReimuCtorF311::ReimuCtorF311()
{
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_ReimuNameAt006590C8);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_ReimuTagAt006590D0);
    FIELD(unsigned short,0x478)=0x287;
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
