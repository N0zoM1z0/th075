#include "graphics/TextureManagerF198.hpp"

void TextureManagerF198::AllocateUnformattedSlots(int count)
{
    NativeTextureElementF769 defaultEntry;
    textureDepth = 0;
    entries.assign(count, defaultEntry);
    IDirect3DTexture8* noTexture = 0;
    textures.assign(count, noTexture);
}
