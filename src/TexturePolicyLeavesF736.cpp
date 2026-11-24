#include "SpriteDraw40CA80.hpp"
#include "TextureManagerF198.hpp"
#include "Graphics.hpp"
#include "GraphicsTexturedDraw.hpp"


void TextureManagerF198::ClearSlots()
{
    entries.clear();
    textures.clear();
}

void TextureManagerF198::SetBlendMode(int mode) {
    if (mode == 2 || mode == 3 || mode == 6)
        Graphics::SetDepthMode(3);
    else
        Graphics::SetDepthMode(2);
    Graphics::SetBlendMode(mode);
}

void TextureManagerF198::DrawProjectedTriangleStrip(
    int index, Graphics::ScreenVertex* vertices, int count) {
    Graphics::DrawProjectedTriangleStrip(vertices, count,
        GetTexture(index));
}
