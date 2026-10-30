#include "SpriteDraw40CA80.hpp"
#include "Graphics.hpp"
#include "GraphicsTexturedDraw.hpp"
// Full original R011 0040CA20: 92 native CODE B, 34 x86, 2 PE calls.
// The physically observed 132-byte quad has explicit 4-byte alignment.
// This eliminates a spurious VC7.1 4-byte stack slot; the real used
// copy begins EBP-0x84 and this is stored at EBP-0x88.
namespace Graphics {
void DrawProjectedTexturedQuad(const float (*)[4], const RECT*,
                              float, float, float, DWORD, IDirect3DTexture8*);
}
// Native actual 132-byte object view: 64B four position vectors plus
// 68B real position/animation payload. No guessed whole sprite owner.
__declspec(align(4)) struct NativeSpriteQuadF751 {float positions[4][4]; DWORD payload[17];};
typedef char NativeSpriteQuadSizeF751[(sizeof(NativeSpriteQuadF751)==132)?1:-1];
class SpriteDrawingF751 {
public:
    IDirect3DTexture8* GetTexture(int);
    void DrawProjectedQuad(int, const NativeSpriteQuadF751&, const RECT*,
                           float,float,float,DWORD);
};
void SpriteDrawingF751::DrawProjectedQuad(int texture,
    const NativeSpriteQuadF751& quad, const RECT* rect,
    float x,float y,float z,DWORD color) {
    NativeSpriteQuadF751 usedQuad(quad);
    Graphics::DrawProjectedTexturedQuad(usedQuad.positions,
                                        rect,x,y,z,color,GetTexture(texture));
}
