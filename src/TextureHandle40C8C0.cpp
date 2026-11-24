#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)

IDirect3DTexture8* SpriteTextures40CA80::GetTexture(int index) {
    static int cachedIndex = index;
    if (index < 0 || index >= static_cast<int>(MANAGER->entries.size()))
        return 0;
    if (MANAGER->entries[index].paletteFlag) {
        if (cachedIndex != index) {
            MANAGER->Refresh(index);
            cachedIndex = index;
        }
        return MANAGER->paletteTextures[0];
    }
    return MANAGER->textures[index];
}

#undef MANAGER
