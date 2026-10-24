#include "BattleHud43E040.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define LEFT_FLOAT(offset) *reinterpret_cast<float*>(FIELD(char*, 0x44) + (offset))
#define RIGHT_FLOAT(offset) *reinterpret_cast<float*>(FIELD(char*, 0x48) + (offset))
#define LEFT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44) + (offset)))
#define RIGHT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x48) + (offset)))
#define LEFT_DIRECTORY reinterpret_cast<HudDirectory43E040*>(FIELD(char*, 0x44) + 0x468)
#define RIGHT_DIRECTORY reinterpret_cast<HudDirectory43E040*>(FIELD(char*, 0x48) + 0x468)
#define LEFT_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(LEFT(void*, 4))
#define RIGHT_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(RIGHT(void*, 4))
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 8))
#define STYLE reinterpret_cast<RenderStyle43D9D0*>(FIELD(void*, 8))
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)

void BattleHud43E040::RenderHud() {
    float nameSlide;
    int iconIndex;
    short tex;
    RenderQuadPacket5E68C0 packet;
    {
        // Quad submission pass; counter widgets are rendered after this scope.
        D3DCOLOR color;
        int gaugeIndex;
        RECT region;
        int gaugeHeight;
        int leftStateRow;
        int rightBand;

        STYLE->SetBlendMode(0);
        color = D3DCOLOR_ARGB(g_SequenceByteAt0066C239, 255, 255, 255);
        SetRect(&region, 0, 0, 128, 128);
        packet.BuildQuadFromRect(&region);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
        tex = LEFT_DIRECTORY->At(41)->At(0)[3];
        LEFT_DRAWING->DrawQuad(tex, &packet, &region, color);
        tex = RIGHT_DIRECTORY->At(41)->At(0)[3];
        QUAD->Scale(320.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
        RIGHT_DRAWING->DrawQuad(tex, &packet, &region, color);

        SetRect(&region, 0, 0, 640, 123);
        packet.BuildQuad(0.0f, 0.0f, 640.0f, 123.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);

        if (LEFT(signed char, 0x39D) == 2) {
            SetRect(&region, 641, 10, 866, 21);
            packet.BuildQuad(31.0f, 27.0f, 256.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239, 128, 128, 128));
            SetRect(&region, 866 - LEFT(short, 0x326) * 225 / 10000, 21, 866, 32);
            packet.BuildQuad(float(256 - LEFT(short, 0x326) * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            SetRect(&region, 865 - LEFT(short, 0x324) * 225 / 10000, 236, 865, 247);
            packet.BuildQuad(float(256 - LEFT(short, 0x324) * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        } else {
            SetRect(&region, 866 - LEFT(short, 0x326) * 225 / 10000, 21, 866, 32);
            packet.BuildQuad(float(256 - LEFT(short, 0x326) * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            SetRect(&region, 866 - LEFT(short, 0x324) * 225 / 10000, 10, 866, 21);
            packet.BuildQuad(float(256 - LEFT(short, 0x324) * 225 / 10000), 27.0f, 256.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239,
                FIELD(unsigned char, 0x98), FIELD(unsigned char, 0x98), FIELD(unsigned char, 0x98)));
        }

        if (g_CombatMode == 3) {
            switch (reinterpret_cast<signed char*>(FIELD(char*, 0x48) + 0x32A)[RIGHT(signed char, 0x39D)]) {
            case 0:
                if (FIELD(signed char, 0x18) == 9 || FIELD(signed char, 0x18) == 10) {
                    SetRect(&region, 866 - RIGHT(short, 0x326) * 225 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)], 10, 866, 21);
                    packet.BuildQuad(float(RIGHT(short, 0x326) * 56 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)] + 384), 27.0f, 384.0f, 38.0f);
                } else {
                    SetRect(&region, 641, 10, 866, 21);
                    packet.BuildQuad(440.0f, 27.0f, 384.0f, 38.0f);
                }
                if (FLOAT(0x8C) != 0.0f)
                    QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
                DRAWING->DrawQuad(0, &packet, &region, color);
                SetRect(&region, 865 - RIGHT(short, 0x324) * 225 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)], 236, 865, 247);
                packet.BuildQuad(float(RIGHT(short, 0x324) * 169 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)] + 440), 27.0f, 440.0f, 38.0f);
                if (FLOAT(0x8C) != 0.0f)
                    QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
                DRAWING->DrawQuad(0, &packet, &region, color);
                break;
            case 1:
                SetRect(&region, 866 - RIGHT(short, 0x324) * 225 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)], 10, 866, 21);
                packet.BuildQuad(float(RIGHT(short, 0x324) * 56 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)] + 384), 27.0f, 384.0f, 38.0f);
                if (FLOAT(0x8C) != 0.0f)
                    QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
                DRAWING->DrawQuad(0, &packet, &region, color);
                break;
            case 2:
                SetRect(&region, 866 - RIGHT(short, 0x324) * 225 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)], 10, 866, 21);
                packet.BuildQuad(float(RIGHT(short, 0x324) * 225 / reinterpret_cast<short*>(FIELD(char*, 0x48) + 0x33E)[RIGHT(signed char, 0x39D)] + 384), 27.0f, 384.0f, 38.0f);
                if (FLOAT(0x8C) != 0.0f)
                    QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
                DRAWING->DrawQuad(0, &packet, &region, color);
                break;
            }
        } else if (RIGHT(signed char, 0x39D) == 2) {
            SetRect(&region, 641, 10, 866, 21);
            packet.BuildQuad(609.0f, 27.0f, 384.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239, 128, 128, 128));
            SetRect(&region, 866 - RIGHT(short, 0x326) * 225 / 10000, 21, 866, 32);
            packet.BuildQuad(float(RIGHT(short, 0x326) * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            SetRect(&region, 865 - RIGHT(short, 0x324) * 225 / 10000, 236, 865, 247);
            packet.BuildQuad(float(RIGHT(short, 0x324) * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        } else {
            SetRect(&region, 866 - RIGHT(short, 0x326) * 225 / 10000, 21, 866, 32);
            packet.BuildQuad(float(RIGHT(short, 0x326) * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            SetRect(&region, 866 - RIGHT(short, 0x324) * 225 / 10000, 10, 866, 21);
            packet.BuildQuad(float(RIGHT(short, 0x324) * 225 / 10000 + 384), 27.0f, 384.0f, 38.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, D3DCOLOR_ARGB(g_SequenceByteAt0066C239,
                FIELD(unsigned char, 0x99), FIELD(unsigned char, 0x99), FIELD(unsigned char, 0x99)));
        }

        tex = LEFT_DIRECTORY->At(40)->At(0)[3];
        nameSlide = float(LEFT_DIRECTORY->At(40)->At(0)[0]);
        SetRect(&region, 0, 0, 128, 16);
        packet.BuildQuad(0.0f - nameSlide, 72.0f, 128.0f - nameSlide, 88.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
        LEFT_DRAWING->DrawQuad(tex, &packet, &region, color);
        tex = RIGHT_DIRECTORY->At(40)->At(0)[3];
        nameSlide = float(RIGHT_DIRECTORY->At(40)->At(1)[0]);
        SetRect(&region, 0, 0, 128, 16);
        packet.BuildQuad(0.0f - nameSlide, 72.0f, 128.0f - nameSlide, 88.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
        RIGHT_DRAWING->DrawQuad(tex, &packet, &region, color);

        if (g_CombatMode == 3) {
            SetRect(&region, 756, 39, 797, 53);
            packet.BuildQuad(115.0f, 5.0f, 156.0f, 19.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            DrawAtlasNumberAt00446B90(280.0f, 5.0f + FLOAT(0x8C), color, LEFT(int, 0x2D0), 12, 10);
            SetRect(&region, 803, 39, 858, 53);
            packet.BuildQuad(376.0f, 5.0f, 431.0f, 19.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            DrawAtlasNumberAt00446B90(555.0f, 5.0f + FLOAT(0x8C), color, int(g_MaxCombatScore), 12, 10);
            SetRect(&region, 866, 41, 923, 54);
            packet.BuildQuad(1.0f, 5.0f, 58.0f, 18.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            DrawAtlasNumberDefaultAt00446B60(70.0f, 5.0f + FLOAT(0x8C), color, int(static_cast<signed char>(g_SequenceCounterAt00671622)), 11);
        } else {
            SetRect(&region, 756, 39, 797, 53);
            packet.BuildQuad(115.0f, 5.0f, 156.0f, 19.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            DrawAtlasNumberAt00446B90(280.0f, 5.0f + FLOAT(0x8C), color, LEFT(int, 0x2D0), 12, 10);
            SetRect(&region, 756, 39, 797, 53);
            packet.BuildQuad(370.0f, 5.0f, 411.0f, 19.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            DrawAtlasNumberAt00446B90(535.0f, 5.0f + FLOAT(0x8C), color, RIGHT(int, 0x2D0), 12, 10);
        }

        color = D3DCOLOR_ARGB(g_SequenceByteAt0066C23A, 255, 255, 255);
        if (LEFT_FLOAT(0x36C) < 900.0f) {
            gaugeIndex = int(LEFT_FLOAT(0x36C) / 100.0f);
            gaugeHeight = ((int(LEFT_FLOAT(0x36C) * 10.0f) % 1000 + 1) * 58) / 1000;
        } else {
            gaugeIndex = 8;
            gaugeHeight = 58;
        }
        SetRect(&region, (gaugeIndex % 3) * 64, gaugeIndex / 3 * 58 + 136 - gaugeHeight,
            gaugeIndex % 3 * 64 + 64, gaugeIndex / 3 * 58 + 136);
        packet.BuildQuad(0.0f, float(58 - gaugeHeight), 64.0f, 58.0f);
        QUAD->Translate(1.0f, 416.0f - FLOAT(0x8C), 0.0f);
        DRAWING->DrawQuad(8, &packet, &region, color);
        if (RIGHT_FLOAT(0x36C) < 900.0f) {
            gaugeIndex = int(RIGHT_FLOAT(0x36C) / 100.0f);
            gaugeHeight = ((int(RIGHT_FLOAT(0x36C) * 10.0f) % 1000 + 1) * 58) / 1000;
        } else {
            gaugeIndex = 8;
            gaugeHeight = 58;
        }
        SetRect(&region, gaugeIndex % 3 * 64, gaugeIndex / 3 * 58 + 136 - gaugeHeight,
            gaugeIndex % 3 * 64 + 64, gaugeIndex / 3 * 58 + 136);
        packet.BuildQuad(0.0f, float(58 - gaugeHeight), 64.0f, 58.0f);
        QUAD->Translate(1.0f, 416.0f - FLOAT(0x8C), 0.0f);
        QUAD->Scale(320.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
        DRAWING->DrawQuad(8, &packet, &region, color);

        SetRect(&region, 0, 188, 301, 256);
        packet.BuildQuad(0.0f, 412.0f, 301.0f, 480.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);
        QUAD->Scale(320.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);

        if (LEFT(short, 0x3B6) > 0) {
            SetRect(&region, 640, 227, 844, 236);
            packet.BuildQuad(float(LEFT(short, 0x3B6) * 204 / 1000 + 75), 462.0f, 279.0f, 471.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        } else {
            leftStateRow = 0;
            if (LEFT(short, 0x3B0) <= 250.0)
                leftStateRow = (LEFT(unsigned short, 0xEF8) % 20 < 10) * 9 + 18;
            else if (LEFT(short, 0x3B0) <= 500.0)
                leftStateRow = 18;
            else if (LEFT(short, 0x3B0) <= 750.0)
                leftStateRow = 9;
            SetRect(&region, 640, leftStateRow + 200, 844, leftStateRow + 209);
            packet.BuildQuad(float(273 - LEFT(short, 0x3B0) * 198 / 1000), 462.0f, 279.0f, 471.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        }
        if (RIGHT(short, 0x3B6) > 0) {
            SetRect(&region, 640, 227, 844, 236);
            packet.BuildQuad(float(565 - RIGHT(short, 0x3B6) * 204 / 1000), 462.0f, 361.0f, 471.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        } else {
            rightBand = 0;
            if (RIGHT(short, 0x3B0) <= 250.0)
                rightBand = (RIGHT(unsigned short, 0xEF8) % 20 < 10) * 9 + 18;
            else if (RIGHT(short, 0x3B0) <= 500.0)
                rightBand = 18;
            else if (RIGHT(short, 0x3B0) <= 750.0)
                rightBand = 9;
            SetRect(&region, 640, rightBand + 200, 844, rightBand + 209);
            packet.BuildQuad(float(RIGHT(short, 0x3B0) * 204 / 1000 + 361), 462.0f, 361.0f, 471.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        }

        SetRect(&region, 866, 0, 914, 19);
        packet.BuildQuad(65.0f, 437.0f, 113.0f, 456.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);
        if (g_CombatMode != 3) {
            QUAD->Translate(431.0f, 0.0f, 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        }
        SetRect(&region, 948, 3, 964, 18);
        packet.BuildQuad(115.0f, 440.0f, 131.0f, 455.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);
        QUAD->Translate(16.0f, 0.0f, 0.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);
        if (g_CombatMode != 3) {
            QUAD->Translate(431.0f, 0.0f, 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
            QUAD->Translate(-16.0f, 0.0f, 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        }
        SetRect(&region, 916, 3, 932, 18);
        packet.BuildQuad(115.0f, 440.0f, 131.0f, 455.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
        for (iconIndex = 0; iconIndex < LEFT(signed char, 0x366); iconIndex = iconIndex + 1) {
            DRAWING->DrawQuad(0, &packet, &region, color);
            QUAD->Translate(16.0f, 0.0f, 0.0f);
        }
        if (g_CombatMode != 3) {
            packet.BuildQuad(546.0f, 440.0f, 562.0f, 455.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
            for (iconIndex = 0; iconIndex < RIGHT(signed char, 0x366); iconIndex = iconIndex + 1) {
                DRAWING->DrawQuad(0, &packet, &region, color);
                QUAD->Translate(16.0f, 0.0f, 0.0f);
            }
        }
        SetRect(&region, (2 - LEFT(signed char, 0x39D)) * 64 + 832, 64,
            (2 - LEFT(signed char, 0x39D)) * 64 + 896, 96);
        packet.BuildQuad(223.0f, 433.0f, 287.0f, 465.0f);
        if (FLOAT(0x8C) != 0.0f)
            QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
        DRAWING->DrawQuad(0, &packet, &region, color);
        if (g_CombatMode != 3) {
            SetRect(&region, (2 - RIGHT(signed char, 0x39D)) * 64 + 832, 64,
                (2 - RIGHT(signed char, 0x39D)) * 64 + 896, 96);
            packet.BuildQuad(380.0f, 433.0f, 444.0f, 465.0f);
            if (FLOAT(0x8C) != 0.0f)
                QUAD->Translate(0.0f, -FLOAT(0x8C), 0.0f);
            DRAWING->DrawQuad(0, &packet, &region, color);
        }
        DrawAtlasNumberDefaultAt00446B60(33.0f, 439.0f - FLOAT(0x8C), color, static_cast<int>(static_cast<short>(LEFT_FLOAT(0x36C) / 100.0f)), 10);
        if (g_CombatMode == 3) {
            // This mode omits the right numeric gauge.
        } else {
            DrawAtlasNumberDefaultAt00446B60(637.0f, 439.0f - FLOAT(0x8C), color, static_cast<int>(static_cast<short>(RIGHT_FLOAT(0x36C) / 100.0f)), 10);
        }
    }
    reinterpret_cast<HudCombo43E040*>(FIELD(void*, 0x50))->Render();
    reinterpret_cast<HudCombo43E040*>(FIELD(void*, 0x54))->Render();
}

#undef QUAD
#undef STYLE
#undef DRAWING
#undef RIGHT_DRAWING
#undef LEFT_DRAWING
#undef RIGHT_DIRECTORY
#undef LEFT_DIRECTORY
#undef RIGHT
#undef LEFT
#undef FIELD

#undef RIGHT_FLOAT
#undef LEFT_FLOAT
#undef FLOAT
