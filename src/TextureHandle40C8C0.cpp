#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"

IDirect3DTexture8* TextureManagerF198::GetTexture(int index) {
    static int cachedIndex = index;
    if (index < 0 || index >= static_cast<int>(entries.size()))
        return 0;
    if (entries[index].paletteFlag) {
        if (cachedIndex != index) {
            Refresh(index);
            cachedIndex = index;
        }
        return paletteTextures[0];
    }
    return textures[index];
}
