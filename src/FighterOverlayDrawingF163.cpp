#include "FighterOverlayDrawingF163.hpp"
#include <stdlib.h>

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define DRAWING FIELD(TimelineDrawing438D00*, 0x534)

void FighterOverlayDrawingF163::RenderSideEffect()
{
    if (FIELD(signed char, 0x2CC) == 0) {
        DRAWING->DrawSprite(FIELD(signed char, 0x6E7),
            0 - FIELD(short, 0x6EA) * FIELD(short, 0x6EA) -
                FIELD(short, 0x6EC) * FIELD(short, 0x6EC) - 96,
            FIELD(short, 0x6EC) * FIELD(short, 0x6EC),
            D3DCOLOR_ARGB(FIELD(unsigned char, 0x6E9), 255, 255, 255),
            0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(FIELD(signed char, 0x6E7),
            FIELD(short, 0x6EA) * FIELD(short, 0x6EA) +
                FIELD(short, 0x6EC) * FIELD(short, 0x6EC) + 704,
            FIELD(short, 0x6EC) * FIELD(short, 0x6EC),
            D3DCOLOR_ARGB(FIELD(unsigned char, 0x6E9), 255, 255, 255),
            0, 0, 1.0f, 0, 1);
    }
}

void FighterOverlayDrawingF163::DrawFacingSprite(short sprite, float position, float y, DWORD color)
{
    if (FIELD(signed char, 0x2CC) == 0) {
        DRAWING->DrawSprite(sprite, 0.0f + position - 256.0f + 160.0f,
            y, color, 0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(sprite, 640.0f - position - 256.0f + 160.0f + 160.0f,
            y, color, 0, 0, 1.0f, 0, 1);
    }
}

void FighterOverlayDrawingF163::RenderFadeOverlay()
{
    unsigned char alpha = 160 - abs(128 - FIELD(unsigned char, 0x538)) * 5 / 4;
    if (FIELD(signed char, 0x2CC) == 0) {
        DRAWING->DrawSprite(FIELD(unsigned char, 0x539),
            0 - FIELD(unsigned char, 0x538) / 2, 0,
            D3DCOLOR_ARGB(alpha, 255, 255, 255), 0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(FIELD(unsigned char, 0x539),
            FIELD(unsigned char, 0x538) / 2 + 640, 0,
            D3DCOLOR_ARGB(alpha, 255, 255, 255), 0, 0, 1.0f, 0, 1);
    }
}

#undef DRAWING
#undef FIELD
