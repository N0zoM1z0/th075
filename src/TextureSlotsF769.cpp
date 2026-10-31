#include <windows.h>
#include "TextureManagerBorrowedF925.hpp"
// Complete R017 original 0040B110; physical 44-byte used local with actual
// VC7 constructor/destructor and exception lifetime. Unknown 11-word
// envelope does not imply known private vendor/STL class fields.
// Real 44-byte local element shared with native 0040B000.
class TextureSlotVectorF769 {public: void Assign(unsigned int,const NativeTextureElementF769&);};
class TexturePointerVectorF769 {public: void Assign(unsigned int,const DWORD&);};
class TextureManagerF769 {
public:
    void AllocateTextureSlots(unsigned int count,unsigned char kind);
};
#define TYPE (reinterpret_cast<NativeTextureManagerModeF925*>(this)->allocationKindAt4C)
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
