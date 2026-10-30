#include "SpriteDraw40CA80.hpp"
#include "Graphics.hpp"
#include "GraphicsTexturedDraw.hpp"
// Original R011 0040C9A0 complete 115 CODE B/37 native x86/4 PE calls.
// Physical scratch view: a 132-B quad and two saved call results.
// This is a source-compatible observed stack view, not an assertion that
// the historical C++ source declared a full class with this identity.
__declspec(align(4)) struct NativeSpriteQuadF780 {
    float positions[4][4]; DWORD payload[17];
};
struct LocalDrawContextF780 {
    NativeSpriteQuadF780 quad;
    IDirect3DTexture8* texture;
    int count;
};
typedef char LocalDrawContextSizeF780[(sizeof(LocalDrawContextF780)==140)?1:-1];
class SpriteEntryVectorF780 { public: int size() const; };
class SpriteDrawingF780 {
public:
    IDirect3DTexture8* GetTexture(int);
    void DrawQuad(int, const NativeSpriteQuadF780&, const RECT*, DWORD);
};
void SpriteDrawingF780::DrawQuad(int texture,
    const NativeSpriteQuadF780& quad, const RECT* rect, DWORD color) {
    LocalDrawContextF780 scratch;
    scratch.texture = GetTexture(texture); // Original prior texture lookup (EBP-8).
    scratch.count = reinterpret_cast<const SpriteEntryVectorF780*>(
        reinterpret_cast<const char*>(this)+8)->size(); // Original size query (EBP-4).
    scratch.quad = quad;
    Graphics::DrawTexturedQuad(scratch.quad.positions, rect, color, GetTexture(texture));
}
