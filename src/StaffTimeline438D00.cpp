#include "StaffTimeline438D00.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define TICK FIELD(DWORD, 0x0C)
#define DRAW FIELD(TimelineDrawing438D00*, 8)
#define WHITE(a) D3DCOLOR_ARGB(a, 255, 255, 255)

void StaffTimeline438D00::RenderTimeline() {
    DWORD begin, end;
    if (Graphics::BeginFrameValueAt00402660()) {
        float offset;
        {
            unsigned char alpha;
            DRAW->SetDepthMode(0);
            DRAW->SetBlendMode(0);
            begin = 0;
            end = 7900;
            if (TICK >= begin && TICK < end)
                DRAW->DrawSprite(0, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 10.0f, 0.0f, 0);
            DRAW->SetTextureFilter(2);
            begin = 1000;
            end = 5300;
            if (TICK >= begin && TICK < end) {
                alpha = static_cast<unsigned char>(float(TICK - begin) * 255.0f / float(end - begin));
                offset = float(end - TICK) / 100.0f;
                DRAW->DrawSprite(6, 260.0f - offset, 220.0f, WHITE(alpha), 128.0f, 32.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(7, 300.0f + offset, 350.0f, WHITE(alpha), 256.0f, 128.0f, 1.0f, 0.0f, 0);
            }
            begin = 5300;
            end = 6500;
            if (TICK >= begin && TICK < end) {
                DRAW->DrawSprite(6, 260.0f, 220.0f, 0xFFFFFFFF, 128.0f, 32.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(7, 300.0f, 350.0f, 0xFFFFFFFF, 256.0f, 128.0f, 1.0f, 0.0f, 0);
            }
            begin = 6500;
            end = 7500;
            if (TICK >= begin && TICK < end) {
                alpha = static_cast<unsigned char>(255.0f - float(TICK - begin) / float(end - begin) * 255.0f);
                DRAW->DrawSprite(6, 260.0f, 220.0f, WHITE(alpha), 128.0f, 32.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(7, 300.0f, 350.0f, WHITE(alpha), 256.0f, 128.0f, 1.0f, 0.0f, 0);
            }
            begin = 7800;
            end = 61000;
            if (TICK >= begin && TICK < end)
                DRAW->DrawSprite(1, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 10.0f, 0.0f, 0);
            begin = 7800;
            end = 8500;
            if (TICK >= begin && TICK < end) {
                offset = -float(TICK - begin) / float(end - begin) * 64.0f * 16.0f * 4.0f;
                DRAW->SetTextureFilter(1);
                DRAW->DrawSprite(2, 320.0f, offset + 480.0f, 0xFFFFFFFF, 512.0f, 0.0f, 16.0f, 0.0f, 0);
                DRAW->DrawSprite(3, 320.0f, offset + 480.0f + 1024.0f, 0xFFFFFFFF, 512.0f, 0.0f, 16.0f, 0.0f, 0);
                DRAW->DrawSprite(4, 320.0f, offset + 480.0f + 2048.0f, 0xFFFFFFFF, 512.0f, 0.0f, 16.0f, 0.0f, 0);
                DRAW->DrawSprite(5, 320.0f, offset + 480.0f + 3072.0f, 0xFFFFFFFF, 512.0f, 0.0f, 16.0f, 0.0f, 0);
                DRAW->SetTextureFilter(2);
            }
            begin = 7900;
            end = 8000;
            if (TICK >= begin && TICK < end) {
                offset = float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(8, 320.0f - offset, 220.0f, 0xFFFFFFFF, 192.0f, 12.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(9, 320.0f + offset, 260.0f, 0xFFFFFFFF, 32.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 8000;
            end = 11700;
            if (TICK >= begin && TICK < end) {
                DRAW->DrawSprite(8, 320.0f, 220.0f, 0xFFFFFFFF, 192.0f, 12.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(9, 320.0f, 260.0f, 0xFFFFFFFF, 32.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 11700;
            end = 11800;
            if (TICK >= begin && TICK < end) {
                offset = 320.0f - float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(8, 320.0f + offset, 220.0f, 0xFFFFFFFF, 192.0f, 12.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(9, 320.0f - offset, 260.0f, 0xFFFFFFFF, 32.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 12100;
            end = 12200;
            if (TICK >= begin && TICK < end) {
                offset = float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(10, 320.0f - offset, 220.0f, 0xFFFFFFFF, 128.0f, 12.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(11, 320.0f + offset, 260.0f, 0xFFFFFFFF, 96.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 12200;
            end = 14900;
            if (TICK >= begin && TICK < end) {
                DRAW->DrawSprite(10, 320.0f, 220.0f, 0xFFFFFFFF, 128.0f, 12.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(11, 320.0f, 260.0f, 0xFFFFFFFF, 96.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 14900;
            end = 15000;
            if (TICK >= begin && TICK < end) {
                offset = 320.0f - float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(10, 320.0f + offset, 220.0f, 0xFFFFFFFF, 128.0f, 12.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(11, 320.0f - offset, 260.0f, 0xFFFFFFFF, 96.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 16000;
            end = 63000;
            if (TICK >= begin && TICK < end) {
                DRAW->DrawSprite(12, 320.0f, 480.0f - float(TICK - begin) / 20.0f, 0xFFFFFFFF, 256.0f, 0.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(13, 320.0f, 864.0f - float(TICK - begin) / 19.0f, 0xFFFFFFFF, 256.0f, 0.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(14, 320.0f, 1376.0f - float(TICK - begin) / 19.0f, 0xFFFFFFFF, 256.0f, 0.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(15, 320.0f, 1824.0f - float(TICK - begin) / 19.0f, 0xFFFFFFFF, 256.0f, 0.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(16, 320.0f, 2112.0f - float(TICK - begin) / 19.0f, 0xFFFFFFFF, 256.0f, 0.0f, 1.0f, 0.0f, 0);
            }
            begin = 60000;
            end = 63000;
            if (TICK >= begin && TICK < end) {
                alpha = static_cast<unsigned char>(float(TICK - begin) / float(end - begin) * 255.0f);
                DRAW->DrawSprite(0, 320.0f, 240.0f, WHITE(alpha), 320.0f, 240.0f, 10.0f, 0.0f, 0);
            }
            begin = 63000;
            end = 90000;
            if (TICK >= begin)
                DRAW->DrawSprite(0, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 10.0f, 0.0f, 0);
            begin = 63000;
            end = 65000;
            if (TICK >= begin && TICK < end) {
                alpha = static_cast<unsigned char>(float(TICK - begin) / float(end - begin) * 255.0f);
                DRAW->DrawSprite(17, 320.0f, 240.0f, WHITE(alpha), 320.0f, 240.0f, 1.0f, 0.0f, 0);
            }
            begin = 65000;
            end = 69000;
            if (TICK >= begin && TICK < end)
                DRAW->DrawSprite(17, 320.0f, 240.0f, 0xFFFFFFFF, 320.0f, 240.0f, 1.0f, 0.0f, 0);
            begin = 69000;
            end = 71000;
            if (TICK >= begin && TICK < end) {
                alpha = static_cast<unsigned char>(255.0f - float(TICK - begin) / float(end - begin) * 255.0f);
                DRAW->DrawSprite(17, 320.0f, 240.0f, WHITE(alpha), 320.0f, 240.0f, 1.0f, 0.0f, 0);
            }
            begin = 71400;
            end = 71500;
            if (TICK >= begin && TICK < end) {
                offset = float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(18, 320.0f - offset, 200.0f, 0xFFFFFFFF, 64.0f, 16.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(19, 320.0f + offset, 240.0f, 0xFFFFFFFF, 160.0f, 16.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(20, 320.0f - offset, 280.0f, 0xFFFFFFFF, 160.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 71500;
            end = 78700;
            if (TICK >= begin && TICK < end) {
                DRAW->DrawSprite(18, 320.0f, 200.0f, 0xFFFFFFFF, 64.0f, 16.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(19, 320.0f, 240.0f, 0xFFFFFFFF, 160.0f, 16.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(20, 320.0f, 280.0f, 0xFFFFFFFF, 160.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 78700;
            end = 78800;
            if (TICK >= begin && TICK < end) {
                offset = 320.0f - float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(18, 320.0f + offset, 200.0f, 0xFFFFFFFF, 64.0f, 16.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(19, 320.0f - offset, 240.0f, 0xFFFFFFFF, 160.0f, 16.0f, 1.0f, 0.0f, 0);
                DRAW->DrawSprite(20, 320.0f + offset, 280.0f, 0xFFFFFFFF, 160.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 79400;
            end = 79500;
            if (TICK >= begin && TICK < end) {
                offset = float(end - TICK) / float(end - begin) * 320.0f;
                DRAW->DrawSprite(21, 320.0f - offset, 200.0f, 0xFFFFFFFF, 128.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 79500;
            end = 90000;
            if (TICK >= begin)
                DRAW->DrawSprite(21, 320.0f, 200.0f, 0xFFFFFFFF, 128.0f, 16.0f, 1.0f, 0.0f, 0);
            begin = 79900;
            end = 80000;
            if (TICK >= begin && TICK < end) {
                alpha = static_cast<unsigned char>(float(TICK - begin) * 255.0f / float(end - begin));
                DRAW->DrawSprite(22, 320.0f, 280.0f, WHITE(alpha), 32.0f, 16.0f, 1.0f, 0.0f, 0);
            }
            begin = 80000;
            end = 90000;
            if (TICK >= begin)
                DRAW->DrawSprite(22, 320.0f, 280.0f, 0xFFFFFFFF, 32.0f, 16.0f, 1.0f, 0.0f, 0);
            DRAW->SetTextureFilter(1);
            Graphics::EndFrame();
        }
    }
}

#undef WHITE
#undef DRAW
#undef TICK
#undef FIELD
