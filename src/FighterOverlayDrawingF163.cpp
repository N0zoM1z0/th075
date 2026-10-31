#include "FighterNoticeBorrowedF960.hpp"
#include "FighterOverlayDrawingF163.hpp"
#include <stdlib.h>

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define DRAWING FIELD(TimelineDrawing438D00*, 0x534)

void FighterOverlayDrawingF163::RenderSideEffect()
{
    if (FIELD(signed char, 0x2CC) == 0) {
        DRAWING->DrawSprite(F960_BADGE(this).noticeAt6E7,
            0 - F960_MOTION(this).axisAt6EA * F960_MOTION(this).axisAt6EA -
                F960_MOTION(this).extentAt6EC * F960_MOTION(this).extentAt6EC - 96,
            F960_MOTION(this).extentAt6EC * F960_MOTION(this).extentAt6EC,
            D3DCOLOR_ARGB(F960_BADGE(this).colorAt6E9, 255, 255, 255),
            0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(F960_BADGE(this).noticeAt6E7,
            F960_MOTION(this).axisAt6EA * F960_MOTION(this).axisAt6EA +
                F960_MOTION(this).extentAt6EC * F960_MOTION(this).extentAt6EC + 704,
            F960_MOTION(this).extentAt6EC * F960_MOTION(this).extentAt6EC,
            D3DCOLOR_ARGB(F960_BADGE(this).colorAt6E9, 255, 255, 255),
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
