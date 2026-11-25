#include "battle/FighterOverlayDrawingF163.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <stdlib.h>

#define DRAWING reinterpret_cast<TextureManagerF198*>(field534)

void Fighter::RenderSideEffect()
{
    if (field2CC == 0) {
        DRAWING->DrawSprite(noticeBadge,
            0 - noticeAxis * noticeAxis -
                noticeExtent * noticeExtent - 96,
            noticeExtent * noticeExtent,
            D3DCOLOR_ARGB(noticeColor, 255, 255, 255),
            0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(noticeBadge,
            noticeAxis * noticeAxis +
                noticeExtent * noticeExtent + 704,
            noticeExtent * noticeExtent,
            D3DCOLOR_ARGB(noticeColor, 255, 255, 255),
            0, 0, 1.0f, 0, 1);
    }
}

void Fighter::DrawFacingSprite(short sprite, float position, float y, DWORD color)
{
    if (field2CC == 0) {
        DRAWING->DrawSprite(sprite, 0.0f + position - 256.0f + 160.0f,
            y, color, 0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(sprite, 640.0f - position - 256.0f + 160.0f + 160.0f,
            y, color, 0, 0, 1.0f, 0, 1);
    }
}

void Fighter::RenderFadeOverlay()
{
    unsigned char alpha = 160 - abs(128 - fadeAlpha) * 5 / 4;
    if (field2CC == 0) {
        DRAWING->DrawSprite(drawMode,
            0 - fadeAlpha / 2, 0,
            D3DCOLOR_ARGB(alpha, 255, 255, 255), 0, 0, 1.0f, 0, 0);
    } else {
        DRAWING->DrawSprite(drawMode,
            fadeAlpha / 2 + 640, 0,
            D3DCOLOR_ARGB(alpha, 255, 255, 255), 0, 0, 1.0f, 0, 1);
    }
}

#undef DRAWING
