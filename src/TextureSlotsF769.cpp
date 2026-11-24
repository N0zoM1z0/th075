#include "TextureManagerF198.hpp"

class TextureManagerF769 {
public:
    void AllocateTextureSlots(unsigned int count, unsigned char kind);
};

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)
#define DEPTH MANAGER->textureDepth

void TextureManagerF769::AllocateTextureSlots(unsigned int count, unsigned char kind)
{
    NativeTextureElementF769 resource;
    DEPTH = kind;
    if (DEPTH != 0 && DEPTH != 0x10 && DEPTH == 0x18 && DEPTH != 0x20)
        DEPTH = 0x10;
    MANAGER->entries.assign(count, resource);
    IDirect3DTexture8* noTexture = 0;
    MANAGER->textures.assign(count, noTexture);
}

#undef DEPTH
#undef MANAGER
