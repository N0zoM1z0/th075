#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"

class TexturePalette40C8C0 { public: void Refresh(int); };

#define MANAGER reinterpret_cast<TextureManagerF198*>(this)

IDirect3DTexture8* SpriteTextures40CA80::GetTexture(int index) {
    static int cachedIndex = index;
    if (index < 0 || index >= static_cast<int>(MANAGER->entries.size()))
        return 0;
    if (MANAGER->entries[index].paletteFlag) {
        if (cachedIndex != index) {
            reinterpret_cast<TexturePalette40C8C0*>(this)->Refresh(index);
            cachedIndex = index;
        }
        return MANAGER->paletteTextures[0];
    }
    return MANAGER->textures[index];
}

#undef MANAGER
