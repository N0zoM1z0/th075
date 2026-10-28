#include <string.h>
// Call-only derived constructor. Base receiver used for real C++ EH cleanup;
// subcomponent at +0xFEC is an observed existing subobject, not padding.
class BaseFighterCtorF223 {
public:
    BaseFighterCtorF223();
    virtual ~BaseFighterCtorF223();
};
class YoumuSubcomponentF223 {
public:
    void Initialize();
};
class YoumuCtorF223 : public BaseFighterCtorF223 {
public:
    YoumuCtorF223();
    virtual ~YoumuCtorF223();
};
extern const char g_YoumuNameAt006598C0[];
extern const char g_YoumuTagAt006598C8[];
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
YoumuCtorF223::YoumuCtorF223()
{
    reinterpret_cast<YoumuSubcomponentF223*>(reinterpret_cast<unsigned char*>(this)+0xfec)->Initialize();
    FIELD(unsigned short,0xefc)=0;
    FIELD(unsigned short,0xefe)=0;
    FIELD(unsigned char,0x713)=1;
    strcpy(reinterpret_cast<char*>(this)+0xc4,g_YoumuNameAt006598C0);
    strcpy(reinterpret_cast<char*>(this)+0x1c8,g_YoumuTagAt006598C8);
    FIELD(unsigned short,0x478)=0x2ef;
    FIELD(unsigned char,0x532)=10;
    FIELD(float,0x6c)=-10.0f;
    FIELD(unsigned short,0xf0c)=0;
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
