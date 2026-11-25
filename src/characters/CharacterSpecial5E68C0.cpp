#include "graphics/SpriteTransform.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "characters/CharacterSpecial5E68C0.hpp"

#define TEXTURE reinterpret_cast<TextureManagerF198*>(drawing)
#define DRAWING stageTexture

void MeilingFighter::RenderStage(signed char stage) {
    RenderQuadPacket5E68C0 sprite;
    switch (stage) {
        RECT rect;
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        TEXTURE->SetTextureFilter(2);
        SetRect(&rect, 0, 0, 1024, 32);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(stageLayerX[0], stageLayerY[0], stageLayerX[0] + 1024.0f, stageLayerY[0] + 32.0f);
        DRAWING->DrawQuad(0, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[0], 255, 255, 255));
        SetRect(&rect, 0, 0, 1024, 32);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(stageLayerX[1], stageLayerY[1], stageLayerX[1] + 1024.0f, stageLayerY[1] + 32.0f);
        DRAWING->DrawQuad(1, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[1], 255, 255, 255));
        TEXTURE->SetTextureFilter(1);
        SetRect(&rect, 0, 0, 640, 128);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(stageLayerX[2], stageLayerY[2], stageLayerX[2] + 640.0f, stageLayerY[2] + 128.0f);
        DRAWING->DrawQuad(2, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[2], 255, 255, 255));
        SetRect(&rect, 0, 0, 304, 80);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(stageLayerX[3], stageLayerY[3], stageLayerX[3] + 304.0f, stageLayerY[3] + 80.0f);
        DRAWING->DrawQuad(3, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[3], 255, 255, 255));
        if ((stageBannerEnabled) == 1 && (stageLayerAlpha[3]) < 255 && (stageBannerHoldFrames) == 0) {
            if ((stageLayerAlpha[3]) < 250)
                stageLayerAlpha[3] = (stageLayerAlpha[3]) + 5;
            else
                stageLayerAlpha[3] = 255;
        }
        if ((stageLayerAlpha[3]) == 255)
            ++stageBannerHoldFrames;
        if ((stageBannerHoldFrames) > 180) {
            if ((stageLayerAlpha[3]) > 0)
                stageLayerAlpha[3] = (stageLayerAlpha[3]) - 5;
            // Preserve the target's ineffective unsigned-alpha lower clamp.
            if ((stageLayerAlpha[3]) < 0)
                stageLayerAlpha[3] = 0;
        }
        break;
    case 8: case 9:
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(0, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[0], 255, 255, 255));
        break;
    case 10:
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(0, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[0], 255, 255, 255));
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(1, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[1], 255, 255, 255));
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(2, sprite, &rect, D3DCOLOR_ARGB(stageLayerAlpha[2], 255, 255, 255));
    }
}

#undef DRAWING
#undef TEXTURE
