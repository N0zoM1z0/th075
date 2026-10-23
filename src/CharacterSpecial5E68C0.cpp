#include "CharacterSpecial5E68C0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define TEXTURE reinterpret_cast<RenderTexture5E68C0*>(FIELD(void*, 4))
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 0x700))

void CharacterSpecial5E68C0::RenderStage(signed char stage) {
    RenderQuadPacket5E68C0 sprite;
    switch (stage) {
        RECT rect;
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
        TEXTURE->SetTextureFilter(2);
        SetRect(&rect, 0, 0, 1024, 32);
        sprite.BuildQuad(FLOAT(0xF2C), FLOAT(0xF54), FLOAT(0xF2C) + 1024.0f, FLOAT(0xF54) + 32.0f);
        DRAWING->DrawQuad(0, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF4), 255, 255, 255));
        SetRect(&rect, 0, 0, 1024, 32);
        sprite.BuildQuad(FLOAT(0xF30), FLOAT(0xF58), FLOAT(0xF30) + 1024.0f, FLOAT(0xF58) + 32.0f);
        DRAWING->DrawQuad(1, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF5), 255, 255, 255));
        TEXTURE->SetTextureFilter(1);
        SetRect(&rect, 0, 0, 640, 128);
        sprite.BuildQuad(FLOAT(0xF34), FLOAT(0xF5C), FLOAT(0xF34) + 640.0f, FLOAT(0xF5C) + 128.0f);
        DRAWING->DrawQuad(2, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF6), 255, 255, 255));
        SetRect(&rect, 0, 0, 304, 80);
        sprite.BuildQuad(FLOAT(0xF38), FLOAT(0xF60), FLOAT(0xF38) + 304.0f, FLOAT(0xF60) + 80.0f);
        DRAWING->DrawQuad(3, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF7), 255, 255, 255));
        if (FIELD(signed char, 0x6F8) == 1 && FIELD(unsigned char, 0xFF7) < 255 && FIELD(short, 0xEFE) == 0) {
            if (FIELD(unsigned char, 0xFF7) < 250)
                FIELD(unsigned char, 0xFF7) = FIELD(unsigned char, 0xFF7) + 5;
            else
                FIELD(unsigned char, 0xFF7) = 255;
        }
        if (FIELD(unsigned char, 0xFF7) == 255)
            ++FIELD(short, 0xEFE);
        if (FIELD(short, 0xEFE) > 180) {
            if (FIELD(unsigned char, 0xFF7) > 0)
                FIELD(unsigned char, 0xFF7) = FIELD(unsigned char, 0xFF7) - 5;
            // Preserve the target's ineffective unsigned-alpha lower clamp.
            if (FIELD(unsigned char, 0xFF7) < 0)
                FIELD(unsigned char, 0xFF7) = 0;
        }
        break;
    case 8: case 9:
        SetRect(&rect, 0, 0, 640, 480);
        sprite.BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(0, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF4), 255, 255, 255));
        break;
    case 10:
        SetRect(&rect, 0, 0, 640, 480);
        sprite.BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(0, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF4), 255, 255, 255));
        SetRect(&rect, 0, 0, 640, 480);
        sprite.BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(1, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF5), 255, 255, 255));
        SetRect(&rect, 0, 0, 640, 480);
        sprite.BuildQuadFromRect(&rect);
        DRAWING->DrawQuad(2, &sprite, &rect, D3DCOLOR_ARGB(FIELD(unsigned char, 0xFF6), 255, 255, 255));
    }
}

#undef DRAWING
#undef TEXTURE
#undef FLOAT
#undef FIELD
