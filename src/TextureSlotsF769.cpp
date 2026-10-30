#include <windows.h>
// Complete R017 original 0040B110; physical 44-byte used local with actual
// VC7 constructor/destructor and exception lifetime. Unknown 11-word
// envelope does not imply known private vendor/STL class fields.
struct NativeTextureElementF769 {
    DWORD physicalWords[11];
    NativeTextureElementF769();
    ~NativeTextureElementF769();
};
typedef char NativeTextureElementSizeF769[(sizeof(NativeTextureElementF769)==44)?1:-1];
class TextureSlotVectorF769 {public: void Assign(unsigned int,const NativeTextureElementF769&);};
class TexturePointerVectorF769 {public: void Assign(unsigned int,const DWORD&);};
class TextureManagerF769 {
public:
    void AllocateTextureSlots(unsigned int count,unsigned char kind);
};
#define TYPE (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this)+0x4C))
void TextureManagerF769::AllocateTextureSlots(unsigned int count,unsigned char kind) {
    NativeTextureElementF769 resource;
    TYPE = kind;
    if (TYPE!=0 && TYPE!=0x10 && TYPE==0x18 && TYPE!=0x20)
        TYPE=0x10;
    reinterpret_cast<TextureSlotVectorF769*>(reinterpret_cast<char*>(this)+8)->Assign(count,resource);
    DWORD noTexture=0;
    reinterpret_cast<TexturePointerVectorF769*>(reinterpret_cast<char*>(this)+0x18)->Assign(count,noTexture);
}
#undef TYPE
