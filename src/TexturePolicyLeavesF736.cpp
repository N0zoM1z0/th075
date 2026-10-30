#include "Graphics.hpp"
#include "GraphicsTexturedDraw.hpp"

// F736: three R014/R019 authored texture wrappers. Real original
// vector storage +8/+24, policy routing, and projected vertex forwarding.
// Layout names are provisional; neither native callee receives extra CODE.
class NativeTextureNamesF736 {
    unsigned int nativeStorage[4];
public: void Clear();
};
class NativeTextureSlotsF736 {
    unsigned int nativeStorage[4];
public: void Clear();
};
struct TextureManagerSlotsF736 {
    unsigned int existingPrefix[2];
    NativeTextureNamesF736 names;
    NativeTextureSlotsF736 textures;
    void ClearSlots();
};
void TextureManagerSlotsF736::ClearSlots() {
    names.Clear();
    textures.Clear();
}

class TextureManagerF736 {
public:
    void SetBlendMode(int mode);
};
void TextureManagerF736::SetBlendMode(int mode) {
    if (mode == 2 || mode == 3 || mode == 6)
        Graphics::SetDepthMode(3);
    else
        Graphics::SetDepthMode(2);
    Graphics::SetBlendMode(mode);
}

class SpriteTexturesF736 {
public:
    IDirect3DTexture8* GetTexture(int index);
    void DrawProjectedTriangleStrip(int index, Graphics::ScreenVertex* vertices, int count);
};
void SpriteTexturesF736::DrawProjectedTriangleStrip(
    int index, Graphics::ScreenVertex* vertices, int count) {
    Graphics::DrawProjectedTriangleStrip(vertices, count, GetTexture(index));
}
