#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include "Graphics.hpp"
#include "GraphicsTexturedDraw.hpp"

class TextureManagerSlotsF736 {
public:
    void ClearSlots();
};

void TextureManagerSlotsF736::ClearSlots()
{
    reinterpret_cast<TextureManagerF198*>(this)->entries.clear();
    reinterpret_cast<TextureManagerF198*>(this)->textures.clear();
}

void TextureManagerF198::SetBlendMode(int mode) {
    if (mode == 2 || mode == 3 || mode == 6)
        Graphics::SetDepthMode(3);
    else
        Graphics::SetDepthMode(2);
    Graphics::SetBlendMode(mode);
}

class SpriteTexturesF736 {
public:
    void DrawProjectedTriangleStrip(int index, Graphics::ScreenVertex* vertices, int count);
};
void SpriteTexturesF736::DrawProjectedTriangleStrip(
    int index, Graphics::ScreenVertex* vertices, int count) {
    Graphics::DrawProjectedTriangleStrip(vertices, count,
        reinterpret_cast<SpriteTextures40CA80*>(this)->GetTexture(index));
}
