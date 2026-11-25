#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/TextureManagerF198.hpp"

namespace Graphics {
    void DrawProjectedTexturedQuad(const float (*)[4], const RECT*,
        float, float, float, DWORD, IDirect3DTexture8*);
}

__declspec(align(4)) struct ProjectedQuadCopyF779 {
    float positions[4][4];
    DWORD payload[17];
};
typedef char ProjectedQuadCopySizeF779[(sizeof(ProjectedQuadCopyF779) == 132) ? 1 : -1];

void TextureManagerF198::DrawProjectedQuad(int texture,
    const SpriteQuad40CA80& quad, const RECT* rect, float x, float y, float z, DWORD color)
{
    ProjectedQuadCopyF779 drawQuad(reinterpret_cast<const ProjectedQuadCopyF779&>(quad));
    Graphics::DrawProjectedTexturedQuad(drawQuad.positions,
        rect, x, y, z, color, GetTexture(texture));
}
