#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/TextureManagerF198.hpp"

struct LocalDrawContextF780 {
    __declspec(align(4)) struct QuadCopy {
        float positions[4][4];
        DWORD payload[17];
    } quad;
    IDirect3DTexture8* texture;
    int count;
};
typedef char LocalDrawContextSizeF780[(sizeof(LocalDrawContextF780) == 140) ? 1 : -1];

void TextureManagerF198::DrawQuad(int texture,
    const SpriteQuad40CA80& quad, const RECT* rect, DWORD color)
{
    LocalDrawContextF780 scratch;
    scratch.texture = GetTexture(texture);
    scratch.count = entries.size();
    scratch.quad = reinterpret_cast<const LocalDrawContextF780::QuadCopy&>(quad);
    Graphics::DrawTexturedQuad(scratch.quad.positions,
        rect, color, GetTexture(texture));
}
