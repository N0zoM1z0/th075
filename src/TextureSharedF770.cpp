#include <windows.h>
#include <d3d8.h>
// Original R017 0040B000 entire 261-B game allocation policy.
// The real local element has an observed 44-B VC7 ctor/dtor lifetime.
// Third-vector zero value is scoped to Assign; real loop index is outside
// that scope. This is the original compiler-lifetime stack ownership,
// not an unused stack padding variable. Private member types provisional.
struct NativeTextureElementF769 {
    DWORD physicalWords[11];
    NativeTextureElementF769();
    ~NativeTextureElementF769();
};
typedef char NativeTextureElementSizeF770[(sizeof(NativeTextureElementF769)==44)?1:-1];
class TextureSlotVectorF769 {public: void Assign(unsigned int,const NativeTextureElementF769&);};
class TexturePointerVectorF769 {
public:
    void Assign(unsigned int,const DWORD&);
    IDirect3DTexture8*& At(unsigned int);
};
namespace Graphics {bool Create16BitTexture(unsigned short, unsigned short, IDirect3DTexture8**);}
class TextureManagerF770 {
public:
    void AllocateSharedTextures(unsigned int count,unsigned int extraCount,unsigned char kind);
};
#define TYPE (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this)+0x4C))
#define SLOTS reinterpret_cast<TextureSlotVectorF769*>(reinterpret_cast<char*>(this)+8)
#define TEXTURES reinterpret_cast<TexturePointerVectorF769*>(reinterpret_cast<char*>(this)+0x18)
#define SHARED reinterpret_cast<TexturePointerVectorF769*>(reinterpret_cast<char*>(this)+0x28)
void TextureManagerF770::AllocateSharedTextures(unsigned int count,unsigned int extraCount,unsigned char kind) {
    NativeTextureElementF769 resource;
    TYPE=kind;
    if (TYPE!=0x10 && TYPE!=0x18 && TYPE!=0x20)
        TYPE=0x10;
    SLOTS->Assign(count,resource);
    DWORD noTexture=0;
    TEXTURES->Assign(count,noTexture);
    unsigned int index;
    {
        DWORD noSharedTexture=0;
        SHARED->Assign(extraCount,noSharedTexture);
    }
    for (index=0; index<extraCount; ++index)
        Graphics::Create16BitTexture(0x100,0x100,&SHARED->At(index));
}
#undef SHARED
#undef TEXTURES
#undef SLOTS
#undef TYPE
