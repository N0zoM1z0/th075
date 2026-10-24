#include "SpriteDraw40CA80.hpp"

// Pointer-only scene view; never instantiate or embed this incomplete owner.
class OpeningTimeline4277A0 { public: void RenderTimeline(); };
// Independently observed float-carrier chain; its origin remains unknown.
float __cdecl OpeningScalar428D20(float);
#define DRAWING (*reinterpret_cast<TimelineDrawing438D00**>(reinterpret_cast<char*>(this) + 8))
#define TIME (*reinterpret_cast<DWORD*>(reinterpret_cast<char*>(this) + 12))

void OpeningTimeline4277A0::RenderTimeline() {
    if (Graphics::BeginFrameValueAt00402660()) {
        // The native routine actually constructs this complete SDK-based value,
        // even though its later drawing calls do not read it.
        SpriteQuad40CA80 localQuad;
        float closingScale = 0;
        float inProgress = 0;
        DWORD begin, rangeEnd;
        float scrollPosition;
        BYTE opacity;
        int entryIndex;
        DRAWING->SetDepthMode(0);
        DRAWING->SetBlendMode(0);
        begin = 0;
        rangeEnd = 49400;
        if (TIME >= begin && TIME < rangeEnd)
            DRAWING->DrawSprite(0, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 10.0f, 0, 0);
        DRAWING->SetTextureFilter(2);
        begin = 0;
        rangeEnd = 21400;
        if (TIME >= begin && TIME < rangeEnd) {
            scrollPosition = (TIME - begin) * 896.0f / (rangeEnd - begin);
            DRAWING->DrawSprite(15, scrollPosition / 8.0f + 384.0f, 140.0f, 0xFFFFFFFF, 512.0f, 256.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(16, scrollPosition / 8.0f + 896.0f, 140.0f, 0xFFFFFFFF, 512.0f, 256.0f, 1.0f, 0, 0);
        }
        begin = 0;
        rangeEnd = 21400;
        if (TIME >= begin && TIME < rangeEnd) {
            scrollPosition = (TIME - begin) * 760.0f / (rangeEnd - begin);
            DRAWING->DrawSprite(18, scrollPosition / 2.0f + 52.0f, 140.0f, 0xFFFFFFFF, 512.0f, 256.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(19, scrollPosition / 2.0f + 564.0f, 140.0f, 0xFFFFFFFF, 512.0f, 256.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(20, scrollPosition / 2.0f + 1076.0f, 140.0f, 0xFFFFFFFF, 512.0f, 256.0f, 1.0f, 0, 0);
        }
        begin = 0;
        rangeEnd = 21400;
        if (TIME >= begin && TIME < rangeEnd) {
            scrollPosition = (TIME - begin) * 896.0f / (rangeEnd - begin);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.0f * 5 + scrollPosition, 140.0f, 0xFFFFFFFF, 512.0f * 1.0f, -128.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.0f * 4 + scrollPosition, 140.0f, 0xFFFFFFFF, 512.0f * 1.0f, -128.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.0f * 3 + scrollPosition, 140.0f, 0xFFFFFFFF, 512.0f * 1.0f, -128.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.0f * 2 + scrollPosition, 140.0f, 0xFFFFFFFF, 512.0f * 1.0f, -128.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.0f * 1 + scrollPosition, 140.0f, 0xFFFFFFFF, 512.0f * 1.0f, -128.0f, 1.0f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f + scrollPosition, 140.0f, 0xFFFFFFFF, 512.0f * 1.0f, -128.0f, 1.0f, 0, 0);
        }
        begin = 0;
        rangeEnd = 21400;
        if (TIME >= begin && TIME < rangeEnd) {
            scrollPosition = (TIME - begin) * 1408.0f / (rangeEnd - begin);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.1f * 5 + scrollPosition, 155.0f, 0xCDFFFFFF, 512.0f * 1.1f, -128.0f, 1.1f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.1f * 4 + scrollPosition, 155.0f, 0xCDFFFFFF, 512.0f * 1.1f, -128.0f, 1.1f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.1f * 3 + scrollPosition, 155.0f, 0xCDFFFFFF, 512.0f * 1.1f, -128.0f, 1.1f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.1f * 2 + scrollPosition, 155.0f, 0xCDFFFFFF, 512.0f * 1.1f, -128.0f, 1.1f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.1f * 1 + scrollPosition, 155.0f, 0xCDFFFFFF, 512.0f * 1.1f, -128.0f, 1.1f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f + scrollPosition, 155.0f, 0xCDFFFFFF, 512.0f * 1.1f, -128.0f, 1.1f, 0, 0);
        }
        begin = 0;
        rangeEnd = 21400;
        if (TIME >= begin && TIME < rangeEnd) {
            scrollPosition = (TIME - begin) * 1920.0f / (rangeEnd - begin);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.2f * 5 + scrollPosition, 170.0f, 0xCDFFFFFF, 512.0f * 1.2f, -128.0f, 1.2f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.2f * 4 + scrollPosition, 170.0f, 0xCDFFFFFF, 512.0f * 1.2f, -128.0f, 1.2f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.2f * 3 + scrollPosition, 170.0f, 0xCDFFFFFF, 512.0f * 1.2f, -128.0f, 1.2f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.2f * 2 + scrollPosition, 170.0f, 0xCDFFFFFF, 512.0f * 1.2f, -128.0f, 1.2f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f - 512.0f * 1.2f * 1 + scrollPosition, 170.0f, 0xCDFFFFFF, 512.0f * 1.2f, -128.0f, 1.2f, 0, 0);
            DRAWING->DrawSprite(17, 896.0f + scrollPosition, 170.0f, 0xCDFFFFFF, 512.0f * 1.2f, -128.0f, 1.2f, 0, 0);
        }
        begin = 21400;
        rangeEnd = 41400;
        if (TIME >= begin && TIME < rangeEnd) {
            if (TIME < 27000)
                inProgress = static_cast<float>(27000 - TIME) / (rangeEnd - 27000);
            if (TIME >= 34000)
                closingScale = static_cast<float>(TIME - 34000) / (rangeEnd - 34000);
            scrollPosition = (TIME - begin) * 736.0f / (rangeEnd - begin);
            DRAWING->DrawSprite(21, 320.0f, 480.0f - scrollPosition, 0xFFFFFFFF,
                (inProgress * inProgress * 4.0f + 1.0f) * 320.0f,
                (inProgress * inProgress * 2.0f + 1.0f) * 384.0f,
                inProgress * inProgress * 4.0f + 1.0f, 0, 0);
            DRAWING->DrawSprite(22, 320.0f, 992.0f - scrollPosition, 0xFFFFFFFF,
                (closingScale * closingScale / 3.0f + 1.0f) * 320.0f,
                (closingScale * closingScale / 8.0f + 1.0f) * 384.0f,
                closingScale * closingScale / 1.5 + 1.0, 20.0f * closingScale * closingScale / 2.0f, 0);
        }
        begin = 41400;
        rangeEnd = 48200;
        if (TIME >= begin && TIME < rangeEnd) {
            scrollPosition = static_cast<float>(TIME - begin) / (rangeEnd - begin);
            DRAWING->DrawSprite(14, 320.0f, 480.0f, 0xFFFFFFFF,
                (2.0f - OpeningScalar428D20(scrollPosition)) * 320.0f,
                (2.0f - OpeningScalar428D20(scrollPosition)) * 480.0f,
                2.0f - OpeningScalar428D20(scrollPosition), 0, 0);
        }
        begin = 48200;
        rangeEnd = 53400;
        if (TIME >= begin && TIME < rangeEnd)
            DRAWING->DrawSprite(14, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 1.0f, 0, 0);
        begin = 0;
        rangeEnd = 1400;
        if (TIME >= begin && TIME < rangeEnd) {
            opacity = static_cast<BYTE>((rangeEnd - TIME) * 255.0f / (rangeEnd - begin));
            DRAWING->DrawSprite(0, 320.0f, 240.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255), 320.0f, 240.0f, 10.0f, 0, 0);
        }
        begin = 19600;
        rangeEnd = 21400;
        if (TIME >= begin && TIME < rangeEnd) {
            opacity = static_cast<BYTE>((TIME - begin) * 255.0f / (rangeEnd - begin));
            DRAWING->DrawSprite(0, 320.0f, 240.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255), 320.0f, 240.0f, 10.0f, 0, 0);
        }
        begin = 21400;
        rangeEnd = 23200;
        if (TIME >= begin && TIME < rangeEnd) {
            opacity = static_cast<BYTE>((rangeEnd - TIME) * 255.0f / (rangeEnd - begin));
            DRAWING->DrawSprite(0, 320.0f, 240.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255), 320.0f, 240.0f, 10.0f, 0, 0);
        }
        begin = 39600;
        rangeEnd = 41400;
        if (TIME >= begin && TIME < rangeEnd) {
            opacity = static_cast<BYTE>((TIME - begin) * 255.0f / (rangeEnd - begin));
            DRAWING->DrawSprite(0, 320.0f, 240.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255), 320.0f, 240.0f, 10.0f, 0, 0);
        }
        begin = 41400;
        rangeEnd = 43200;
        if (TIME >= begin && TIME < rangeEnd) {
            opacity = static_cast<BYTE>((rangeEnd - TIME) * 255.0f / (rangeEnd - begin));
            DRAWING->DrawSprite(0, 320.0f, 240.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255), 320.0f, 240.0f, 10.0f, 0, 0);
        }
        begin = 0;
        rangeEnd = 49400;
        if (TIME >= begin && TIME < rangeEnd) {
            DRAWING->DrawSprite(13, 320.0f, -32.0f, 0xFFFFFFFF, 512.0f, 0.0f, 32.0f, 0, 0);
            DRAWING->DrawSprite(13, 320.0f, 512.0f, 0xFFFFFFFF, 512.0f, 128.0f, 32.0f, 0, 0);
        }
        for (entryIndex = 0; entryIndex < 13; entryIndex++) {
            begin = entryIndex * 4000 + 1400;
            rangeEnd = entryIndex * 4000 + 1800;
            if (TIME >= begin && TIME < rangeEnd) {
                opacity = static_cast<BYTE>((TIME - begin) * 255.0f / (rangeEnd - begin));
                DRAWING->DrawSprite(entryIndex + 1, 320.0f, 464.0f, D3DCOLOR_XRGB(opacity, opacity, opacity), 256.0f, 64.0f, 1.0f, 0, 0);
            }
            begin = entryIndex * 4000 + 1800;
            rangeEnd = entryIndex * 4000 + 5000;
            if (TIME >= begin && TIME < rangeEnd)
                DRAWING->DrawSprite(entryIndex + 1, 320.0f, 464.0f, 0xFFFFFFFF, 256.0f, 64.0f, 1.0f, 0, 0);
            begin = entryIndex * 4000 + 5000;
            rangeEnd = entryIndex * 4000 + 5400;
            if (TIME >= begin && TIME < rangeEnd) {
                opacity = static_cast<BYTE>(255.0f - static_cast<float>(TIME - begin) / (rangeEnd - begin) * 255.0f);
                DRAWING->DrawSprite(entryIndex + 1, 320.0f, 464.0f, D3DCOLOR_XRGB(opacity, opacity, opacity), 256.0f, 64.0f, 1.0f, 0, 0);
            }
        }
        begin = 48000;
        rangeEnd = 49400;
        if (TIME >= begin && TIME < rangeEnd) {
            opacity = static_cast<BYTE>((TIME - begin) * 255.0f / (rangeEnd - begin));
            DRAWING->DrawSprite(23, 320.0f, 240.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255), 320.0f, 240.0f, 1.0f, 0, 0);
        }
        begin = 49400;
        rangeEnd = 51000;
        if (TIME >= begin && TIME < rangeEnd)
            DRAWING->DrawSprite(23, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 1.0f, 0, 0);
        Graphics::EndFrame();
    }
}
