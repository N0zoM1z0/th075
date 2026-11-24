#include "SpriteTransform.hpp"
#include "TextureManagerF198.hpp"
#include "CharacterSpecial5E68C0.hpp"

#define TEXTURE reinterpret_cast<TextureManagerF198*>(drawing)
#define DRAWING reinterpret_cast<TextureManagerF198*>(stageDrawing)

void MeilingFighter::RenderStage(signed char stage) {
    RenderQuadPacket5E68C0 sprite;
    switch (stage) {
        RECT rect;
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        TEXTURE->SetTextureFilter(2);
        SetRect(&rect, 0, 0, 1024, 32);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(fieldF2C, fieldF54, fieldF2C + 1024.0f, fieldF54 + 32.0f);
        DRAWING->DrawQuad(0, sprite, &rect, D3DCOLOR_ARGB(fieldFF4, 255, 255, 255));
        SetRect(&rect, 0, 0, 1024, 32);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(fieldF30, fieldF58, fieldF30 + 1024.0f, fieldF58 + 32.0f);
        DRAWING->DrawQuad(1, sprite, &rect, D3DCOLOR_ARGB(fieldFF5, 255, 255, 255));
        TEXTURE->SetTextureFilter(1);
        SetRect(&rect, 0, 0, 640, 128);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(fieldF34, fieldF5C, fieldF34 + 640.0f, fieldF5C + 128.0f);
        DRAWING->DrawQuad(2, sprite, &rect, D3DCOLOR_ARGB(fieldFF6, 255, 255, 255));
        SetRect(&rect, 0, 0, 304, 80);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuad(fieldF38, fieldF60, fieldF38 + 304.0f, fieldF60 + 80.0f);
        DRAWING->DrawQuad(3, sprite, &rect, D3DCOLOR_ARGB(fieldFF7, 255, 255, 255));
        if ((field6F8) == 1 && (fieldFF7) < 255 && (fieldEFE) == 0) {
            if ((fieldFF7) < 250)
                fieldFF7 = (fieldFF7) + 5;
            else
                fieldFF7 = 255;
        }
        if ((fieldFF7) == 255)
            ++fieldEFE;
        if ((fieldEFE) > 180) {
            if ((fieldFF7) > 0)
                fieldFF7 = (fieldFF7) - 5;
            // Preserve the target's ineffective unsigned-alpha lower clamp.
            if ((fieldFF7) < 0)
                fieldFF7 = 0;
        }
        break;
    case 8: case 9:
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(0, sprite, &rect, D3DCOLOR_ARGB(fieldFF4, 255, 255, 255));
        break;
    case 10:
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(0, sprite, &rect, D3DCOLOR_ARGB(fieldFF4, 255, 255, 255));
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(1, sprite, &rect, D3DCOLOR_ARGB(fieldFF5, 255, 255, 255));
        SetRect(&rect, 0, 0, 640, 480);
        reinterpret_cast<SpriteTransform*>(&sprite)->BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(2, sprite, &rect, D3DCOLOR_ARGB(fieldFF6, 255, 255, 255));
    }
}

#undef DRAWING
#undef TEXTURE
