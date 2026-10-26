#include "TitleMenuRenderF183.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Existing drawing receiver only; no complete owner layout is claimed.
class TitleMenuDrawingF183 {
public:
    void SetDepthMode(int);
    void SetBlendMode(int);
    void SetTextureFilter(int);
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
};

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define ITEM(offset) (*reinterpret_cast<BYTE*>(reinterpret_cast<unsigned char*>(this) + menuIndex + (offset)))
#define DRAW FIELD(TitleMenuDrawingF183*, 8)
#define QUAD reinterpret_cast<SpriteTransform*>(&spriteQuad)
#define HIGHLIGHT (int(FIELD(signed char, 0x38) == menuIndex) * 127 + 128)

void TitleMenuRenderF183::RenderMenu()
{
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 spriteQuad;
        RECT region;
        DRAW->SetDepthMode(0);
        DRAW->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        QUAD->BuildQuadFromRect(&region);
        DRAW->DrawQuad(0, spriteQuad, &region, D3DCOLOR_ARGB(FIELD(BYTE, 0x20), 255, 255, 255));
        SetRect(&region, 0, 0, 512, 192);
        QUAD->BuildQuad(64.0f, 32.0f, 576.0f, 224.0f);
        DRAW->DrawQuad(2, spriteQuad, &region, D3DCOLOR_ARGB(FIELD(BYTE, 0x21), 255, 255, 255));
        SetRect(&region, 0, 0, 512, 32);
        QUAD->BuildQuad(64.0f, 448.0f, 576.0f, 480.0f);
        DRAW->DrawQuad(3, spriteQuad, &region, D3DCOLOR_ARGB(FIELD(BYTE, 0x22), 255, 255, 255));
        DRAW->SetTextureFilter(2);
        for (int menuIndex = 0; menuIndex < 10; menuIndex++) {
            SetRect(&region, 0, 0, 25, 256);
            QUAD->BuildQuadFromRect(&region);
            QUAD->RotateQuad(5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f);
            QUAD->TranslateQuad(220.0f, float(menuIndex * 23 + 240), 0.0f);
            QUAD->TranslateQuad(float(ITEM(0x2E)), 0.0f, 0.0f);
            DRAW->DrawQuad(1, spriteQuad, &region, D3DCOLOR_ARGB(ITEM(0x24), 255, 255, 255));
            SetRect(&region, 25, menuIndex * 25, 256, menuIndex * 25 + 25);
            QUAD->BuildQuad(245.0f, float(menuIndex * 23 + 225),
                            476.0f, float(menuIndex * 23 + 250));
            QUAD->TranslateQuad(float(ITEM(0x2E)), 0.0f, 0.0f);
            DRAW->DrawQuad(1, spriteQuad, &region,
                           D3DCOLOR_ARGB(FIELD(BYTE, 0x23), HIGHLIGHT, HIGHLIGHT, HIGHLIGHT));
        }
        DRAW->SetTextureFilter(1);
        Graphics::EndFrame();
    }
}

#undef HIGHLIGHT
#undef QUAD
#undef DRAW
#undef ITEM
#undef FIELD
