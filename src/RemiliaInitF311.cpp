#include <string.h>
// Call-only physical constructor hierarchy, not complete original class.
class BaseFighterCtorF311 {
public:
    BaseFighterCtorF311();
    virtual ~BaseFighterCtorF311();
};
class RemiliaCtorF311 : public BaseFighterCtorF311 {
public:
    RemiliaCtorF311();
    virtual ~RemiliaCtorF311();
};
extern const char g_RemiliaNameAt00659A34[];
extern const char g_RemiliaTagAt00659A3C[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
RemiliaCtorF311::RemiliaCtorF311()
{
    FIELD(unsigned short,0xefc)=0;
    FIELD(unsigned short,0xefe)=0;
    FIELD(unsigned short,0x6fa)=0;
    FIELD(unsigned short,0x6fc)=0;
    FIELD(unsigned char,0x6f8)=0;
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_RemiliaNameAt00659A34);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_RemiliaTagAt00659A3C);
    FIELD(unsigned short,0x478)=0x2a0;
    FIELD(unsigned char,0x532)=11;
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
