#include "SpriteDraw40CA80.hpp"

// Pointer-only count/handle/refresh interfaces; complete owner layouts unknown.
class TextureEntryCount40C8C0 { public: unsigned int Size(); };
class TextureHandles40C8C0 { public: IDirect3DTexture8*& At(unsigned int); };
class TexturePalette40C8C0 { public: void Refresh(int); };

#define COUNT reinterpret_cast<TextureEntryCount40C8C0*>(reinterpret_cast<char*>(this) + 8)
#define ENTRIES reinterpret_cast<SpriteEntries40CA80*>(reinterpret_cast<char*>(this) + 8)
#define PALETTE reinterpret_cast<TexturePalette40C8C0*>(this)
#define PALETTE_HANDLES reinterpret_cast<TextureHandles40C8C0*>(reinterpret_cast<char*>(this) + 0x28)
#define HANDLES reinterpret_cast<TextureHandles40C8C0*>(reinterpret_cast<char*>(this) + 0x18)

IDirect3DTexture8* SpriteTextures40CA80::GetTexture(int index) {
    static int cachedIndex = index;
    if (index < 0 || index >= static_cast<int>(COUNT->Size()))
        return 0;
    if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(ENTRIES->At(index)) + 0x28)) {
        if (cachedIndex != index) {
            PALETTE->Refresh(index);
            cachedIndex = index;
        }
        return PALETTE_HANDLES->At(0);
    }
    return HANDLES->At(index);
}

#undef HANDLES
#undef PALETTE_HANDLES
#undef PALETTE
#undef ENTRIES
#undef COUNT
