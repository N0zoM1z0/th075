#include <d3d8.h>
// Private independent physical 80-byte receiver model. Member extents are
// from 0x40AD80 native constructor and 0x40AE40 native destructor. The
// original full type name and vector allocator/element names remain unknown.
class TextureCountBaseF199 {
    unsigned int nativeCountAt0;
public:
    TextureCountBaseF199();
    ~TextureCountBaseF199();
};
class TextureNameVectorF199 {
    unsigned int nativeSlots[4];
public:
    TextureNameVectorF199();
    ~TextureNameVectorF199();
    unsigned int Count();
    void ClearStorage();
};
class TexturePointerVectorF199 {
    unsigned int nativeSlots[4];
public:
    TexturePointerVectorF199();
    ~TexturePointerVectorF199();
    unsigned int Count();
    IDirect3DTexture8*& At(unsigned int index);
    void ClearStorage();
};
class TextureQueueF199 {
    unsigned int nativeSlots[5];
public:
    TextureQueueF199();
    ~TextureQueueF199();
};
class TextureManagerF199 : public TextureCountBaseF199 {
    unsigned char* rawTextureStorageAt4;
    TextureNameVectorF199 names;
    TexturePointerVectorF199 palettes;
    TexturePointerVectorF199 textures;
    TextureQueueF199 queue;
    unsigned char depthAt76;
public:
    ~TextureManagerF199();
};
typedef char AssertTextureManager80F199[(sizeof(TextureManagerF199)==80)?1:-1];

TextureManagerF199::~TextureManagerF199()
{
    if (rawTextureStorageAt4) delete[] rawTextureStorageAt4;
    if (palettes.Count() > 0) {
        for (unsigned int i=0; i<palettes.Count(); ++i) {
            if (palettes.At(i)) {
                // Native 0040AEE8 explicitly stores the COM Release return
                // value to a stack slot. Capturing the post-release count is
                // required to reproduce the real API-result storage, not
                // an arbitrary unused padding variable.
                ULONG remainingReferenceCount = palettes.At(i)->Release();
                palettes.At(i) = 0;
            }
        }
        palettes.ClearStorage();
    }
    if (textures.Count() > 0) {
        for (unsigned int j=0; j<textures.Count(); ++j) {
            if (textures.At(j)) textures.At(j)->Release();
        }
        textures.ClearStorage();
    }
    if (names.Count() > 0) names.ClearStorage();
}
