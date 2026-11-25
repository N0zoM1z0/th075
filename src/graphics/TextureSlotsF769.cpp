#include "graphics/TextureManagerF198.hpp"

void TextureManagerF198::AllocateTextureSlots(unsigned int count, unsigned char kind)
{
    NativeTextureElementF769 resource;
    textureDepth = kind;
    if (textureDepth != 0 && textureDepth != 0x10 && textureDepth == 0x18 && textureDepth != 0x20)
        textureDepth = 0x10;
    entries.assign(count, resource);
    IDirect3DTexture8* noTexture = 0;
    textures.assign(count, noTexture);
}
