#include "graphics/GraphicsTexture.hpp"
#include "graphics/TextureManagerF198.hpp"

class TextureManagerF770 {
public:
    void AllocateSharedTextures(unsigned int count, unsigned int extraCount, unsigned char kind);
};

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)
#define DEPTH MANAGER->textureDepth

void TextureManagerF770::AllocateSharedTextures(unsigned int count, unsigned int extraCount, unsigned char kind)
{
    NativeTextureElementF769 resource;
    DEPTH = kind;
    if (DEPTH != 0x10 && DEPTH != 0x18 && DEPTH != 0x20)
        DEPTH = 0x10;
    MANAGER->entries.assign(count, resource);
    IDirect3DTexture8* noTexture = 0;
    MANAGER->textures.assign(count, noTexture);
    unsigned int index;
    {
        IDirect3DTexture8* noSharedTexture = 0;
        MANAGER->paletteTextures.assign(extraCount, noSharedTexture);
    }
    for (index = 0; index < extraCount; ++index)
        Graphics::Create16BitTexture(0x100, 0x100, &MANAGER->paletteTextures[index]);
}

#undef DEPTH
#undef MANAGER
