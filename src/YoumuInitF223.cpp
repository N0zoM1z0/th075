#include "YoumuFighter.hpp"
#include <string.h>
// Call-only derived constructor. Base receiver used for real C++ EH cleanup;
// subcomponent at +0xFEC is an observed existing subobject, not padding.
class YoumuSubcomponentF223 {
public:
    void Initialize();
};
extern const char g_YoumuNameAt006598C0[];
extern const char g_YoumuTagAt006598C8[];
YoumuFighter::YoumuFighter()
{
    reinterpret_cast<YoumuSubcomponentF223*>(reinterpret_cast<unsigned char*>(this)+0xfec)->Initialize();
    sequenceTimer=0;
    fieldEFE=0;
    field713=1;
    strcpy(name,g_YoumuNameAt006598C0);
    strcpy(tag,g_YoumuTagAt006598C8);
    field478=0x2ef;
    reinterpret_cast<unsigned char&>(field532)=10;
    field06C=-10.0f;
    fieldF0C=0;
    field705[0]=4;
    field705[1]=4;
    field705[2]=4;
    field705[3]=4;
    field705[4]=4;
    field705[5]=4;
    field705[6]=4;
    field705[7]=1;
    field705[8]=1;
    field705[9]=3;
}
