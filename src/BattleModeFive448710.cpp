#include "BattleModeFive448710.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define RIGHT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x48) + (offset)))
#define LEFT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44) + (offset)))
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(FIELD(void*, 8))
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 8))
#define PORTRAIT reinterpret_cast<RenderDrawing5E68C0*>(LEFT(void*, 0x534))
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)

void BattleModeFive448710::RenderMenu() {
    int i;
    RenderQuadPacket5E68C0 packet;
    {
        D3DCOLOR color;
        RECT region;
        STYLE->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        Graphics::DrawFilledRectangle(&region, D3DCOLOR_ARGB(FIELD(unsigned char, 0xA1), 0, 0, 0));
        if (FIELD(unsigned char, 0xA1) < 50)
            return;
        for (i = 0; i < 9; i = i + 1) {
            if (i == FIELD(signed char, 0x118)) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, 0, i * 24, 240, i * 24 + 24);
            packet.BuildQuadFromRect(&region);
            if (i > 5)
                QUAD->Translate(0.0f, 24.0f, 0.0f);
            QUAD->Translate(10.0f, 90.0f, 0.0f);
            DRAWING->DrawQuad(10, &packet, &region, color);
        }
        for (i = 0; i < 6; i = i + 1) {
            if (i == RIGHT(signed char, 0x52C)) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, i % 3 * 72, i / 3 * 24 + 216, i % 3 * 72 + 72, i / 3 * 24 + 240);
            packet.BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
            QUAD->Translate(float(i * 60 + 260), 90.0f, 0.0f);
            DRAWING->DrawQuad(10, &packet, &region, color);
        }
        for (i = 0; i < 10; i = i + 1) {
            if (i == RIGHT(signed char, 0x52D)) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, i * 24, 264, i * 24 + 24, 288);
            packet.BuildQuad(float(i * 24), 0.0f, float(i * 24 + 24), 24.0f);
            QUAD->Translate(260.0f, 114.0f, 0.0f);
            DRAWING->DrawQuad(10, &packet, &region, color);
        }
        if (RIGHT(signed char, 0x52F) == 0) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 288, 72, 312);
        packet.BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->Translate(260.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x52F) == 1) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 288, 168, 312);
        packet.BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->Translate(332.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x52F) == 2) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 312, 120, 336);
        packet.BuildQuad(0.0f, 0.0f, 120.0f, 24.0f);
        QUAD->Translate(428.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x52F) == 3) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 120, 312, 168, 336);
        packet.BuildQuad(0.0f, 0.0f, 48.0f, 24.0f);
        QUAD->Translate(548.0f, 138.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        for (i = 0; i < 2; i = i + 1) {
            if (i == RIGHT(signed char, 0x52E)) color = 0xFFFFFFFF;
            else color = 0xFF808080;
            SetRect(&region, i * 72, 336, i * 72 + 72, 360);
            packet.BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
            QUAD->Translate(float(i * 72 + 260), 162.0f, 0.0f);
            DRAWING->DrawQuad(10, &packet, &region, color);
        }
        if (RIGHT(signed char, 0x530) == 0) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 360, 72, 384);
        packet.BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->Translate(260.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x530) == 1) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 360, 168, 384);
        packet.BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->Translate(332.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x530) == 2) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 384, 72, 408);
        packet.BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->Translate(428.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x530) == 3) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 384, 168, 408);
        packet.BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->Translate(500.0f, 186.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x531) == 0) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 0, 408, 72, 432);
        packet.BuildQuad(0.0f, 0.0f, 72.0f, 24.0f);
        QUAD->Translate(260.0f, 210.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        if (RIGHT(signed char, 0x531) == 1) color = 0xFFFFFFFF;
        else color = 0xFF808080;
        SetRect(&region, 72, 408, 168, 432);
        packet.BuildQuad(0.0f, 0.0f, 96.0f, 24.0f);
        QUAD->Translate(332.0f, 210.0f, 0.0f);
        DRAWING->DrawQuad(10, &packet, &region, color);
        SetRect(&region, 0, 0, 256, 256);
        packet.BuildQuadFromRect(&region);
        QUAD->Translate(340.0f, 280.0f, 0.0f);
        PORTRAIT->DrawQuad(LEFT(signed char, 0x532) - 1, &packet, &region, 0xFFFFFFFF);
    }
}

#undef QUAD
#undef PORTRAIT
#undef DRAWING
#undef STYLE
#undef LEFT
#undef RIGHT
#undef FIELD
