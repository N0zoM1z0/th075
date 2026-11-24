#include "TextureManagerF198.hpp"
#include "TitleScene.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Existing drawing receiver only; no complete owner layout is claimed.
class TitleMenuDrawingF183 {
public:
};


#define DRAW static_cast<TitleMenuDrawingF183*>(textures)
#define QUAD reinterpret_cast<SpriteTransform*>(&spriteQuad)
#define HIGHLIGHT (int(menuIndex == item) * 127 + 128)

void TitleScene::Render()
{
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 spriteQuad;
        RECT region;
        reinterpret_cast<TextureManagerF198*>(DRAW)->SetDepthMode(0);
        reinterpret_cast<TextureManagerF198*>(DRAW)->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        QUAD->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(DRAW)->DrawQuad(0, spriteQuad, &region, D3DCOLOR_ARGB(field020, 255, 255, 255));
        SetRect(&region, 0, 0, 512, 192);
        QUAD->BuildQuad(64.0f, 32.0f, 576.0f, 224.0f);
        reinterpret_cast<TextureManagerF198*>(DRAW)->DrawQuad(2, spriteQuad, &region, D3DCOLOR_ARGB(field021, 255, 255, 255));
        SetRect(&region, 0, 0, 512, 32);
        QUAD->BuildQuad(64.0f, 448.0f, 576.0f, 480.0f);
        reinterpret_cast<TextureManagerF198*>(DRAW)->DrawQuad(3, spriteQuad, &region, D3DCOLOR_ARGB(field022, 255, 255, 255));
        reinterpret_cast<TextureManagerF198*>(DRAW)->SetTextureFilter(2);
        for (int item = 0; item < 10; item++) {
            SetRect(&region, 0, 0, 25, 256);
            QUAD->BuildQuadFromRect(&region);
            QUAD->RotateQuad(5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f);
            QUAD->TranslateQuad(220.0f, float(item * 23 + 240), 0.0f);
            QUAD->TranslateQuad(float(itemDelay[item]), 0.0f, 0.0f);
            reinterpret_cast<TextureManagerF198*>(DRAW)->DrawQuad(1, spriteQuad, &region, D3DCOLOR_ARGB(itemAlpha[item], 255, 255, 255));
            SetRect(&region, 25, item * 25, 256, item * 25 + 25);
            QUAD->BuildQuad(245.0f, float(item * 23 + 225),
                            476.0f, float(item * 23 + 250));
            QUAD->TranslateQuad(float(itemDelay[item]), 0.0f, 0.0f);
            reinterpret_cast<TextureManagerF198*>(DRAW)->DrawQuad(1, spriteQuad, &region,
                           D3DCOLOR_ARGB(field023, HIGHLIGHT, HIGHLIGHT, HIGHLIGHT));
        }
        reinterpret_cast<TextureManagerF198*>(DRAW)->SetTextureFilter(1);
        Graphics::EndFrame();
    }
}

#undef HIGHLIGHT
#undef QUAD
#undef DRAW
#undef ITEM
