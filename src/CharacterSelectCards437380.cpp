#include "CharacterSelectCards437380.hpp"

#define SIDE(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + i + (offset)))
#define ANGLE *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0xC0 + i * 4)
#define QUAD reinterpret_cast<SpriteTransform*>(&packet)
#define DRAW FIELD(RenderDrawing5E68C0*, 0x44)
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define NORMAL(a) D3DCOLOR_ARGB(a, normal[i], normal[i], normal[i])
#define DIM(a) D3DCOLOR_ARGB(a, dim[i], dim[i], dim[i])

void CharacterSelectCards437380::RenderCards() {
    unsigned char dim[2];
    RenderQuadPacket5E68C0 packet;
    {
        unsigned char normal[2];
        {
            RECT region;
            for (int i = 0; i < 2; i = i + 1) {
                unsigned char alpha;
                D3DCOLOR color;
                int atlasOffset;
                if (g_CombatMode == 3 && i == 1)
                    break;
                if (g_CombatMode == 4 && i == 1)
                    break;
                normal[i] = 255 - (SIDE(signed char, 0xEA) << 7);
                dim[i] = 128 - (SIDE(signed char, 0xEA) << 6);
                if (ANGLE <= 15.0f)
                    alpha = static_cast<unsigned char>(ANGLE);
                else if (ANGLE <= 45.0f)
                    alpha = static_cast<unsigned char>((45.0f - ANGLE) / 2.0f);
                else
                    alpha = static_cast<unsigned char>(ANGLE - 45.0f) / 2;
                atlasOffset = (ANGLE > 45.0f) * 128;
                packet.BuildQuad(0.0f, 0.0f, 128.0f, 160.0f);
                QUAD->RotateQuad(64.0f, 80.0f, 0.0f, 0.0f, 90.0f - ANGLE * 6.0f, 0.0f);
                if (ANGLE > 30.0f && ANGLE < 60.0f)
                    SetRect(&region, 256, 480, 384, 640);
                else
                    SetRect(&region, atlasOffset + 256, 0, atlasOffset + 384, 160);
                QUAD->TranslateQuad(float(i * 320 + 150), 75.0f, 0.0f);
                if (SIDE(signed char, 0xE6) == 0 || SIDE(unsigned char, 0xE4) == 0)
                    color = NORMAL(255);
                else
                    color = DIM(255);
                DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, color);
                if (ANGLE > 30.0f && ANGLE < 60.0f)
                    SetRect(&region, 256, 480, 384, 640);
                else
                    SetRect(&region, atlasOffset + 256, 160, atlasOffset + 384, 320);
                QUAD->TranslateQuad(-120.0f, 120.0f, 0.0f);
                if (SIDE(signed char, 0xE6) == 1 || SIDE(unsigned char, 0xE4) == 0)
                    color = NORMAL(255);
                else
                    color = DIM(255);
                DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, color);
                if (ANGLE > 30.0f && ANGLE < 60.0f)
                    SetRect(&region, 256, 480, 384, 640);
                else
                    SetRect(&region, atlasOffset + 256, 320, atlasOffset + 384, 480);
                QUAD->TranslateQuad(60.0f, 120.0f, 0.0f);
                if (SIDE(signed char, 0xE6) == 2 || SIDE(unsigned char, 0xE4) == 0)
                    color = NORMAL(255);
                else
                    color = DIM(255);
                DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, color);
                atlasOffset = (ANGLE > 45.0f) * 96;
                packet.BuildQuad(0.0f, 0.0f, 256.0f, 32.0f);
                SetRect(&region, 256, atlasOffset + 640, 512, atlasOffset + 672);
                QUAD->TranslateQuad(float(i * 320 + 100), 150.0f, 0.0f);
                QUAD->TranslateQuad(0.0f, float(alpha - 15), 0.0f);
                if (SIDE(signed char, 0xE6) == 0 || SIDE(unsigned char, 0xE4) == 0)
                    color = NORMAL(alpha * 17);
                else
                    color = DIM(alpha * 17);
                DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, color);
                SetRect(&region, 256, atlasOffset + 672, 512, atlasOffset + 704);
                QUAD->TranslateQuad(-120.0f, 120.0f, 0.0f);
                QUAD->TranslateQuad(float(-(alpha - 15)), float(-(alpha - 15)), 0.0f);
                if (SIDE(signed char, 0xE6) == 1 || SIDE(unsigned char, 0xE4) == 0)
                    color = NORMAL(alpha * 17);
                else
                    color = DIM(alpha * 17);
                DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, color);
                SetRect(&region, 256, atlasOffset + 704, 512, atlasOffset + 736);
                QUAD->TranslateQuad(60.0f, 120.0f, 0.0f);
                QUAD->TranslateQuad(float(alpha - 15), float(-(alpha - 15)), 0.0f);
                if (SIDE(signed char, 0xE6) == 2 || SIDE(unsigned char, 0xE4) == 0)
                    color = NORMAL(alpha * 17);
                else
                    color = DIM(alpha * 17);
                DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, color);
                if (SIDE(unsigned char, 0xEE) != 0) {
                    short badgeRow;
                    if (SIDE(signed char, 0x96) == 1)
                        badgeRow = 0;
                    else if (SIDE(signed char, 0x96) == 2)
                        badgeRow = 192;
                    else
                        continue;
                    SetRect(&region, 0, badgeRow + 640, 256, badgeRow + 704);
                    packet.BuildQuad(0.0f, 0.0f, 256.0f, 64.0f);
                    QUAD->TranslateQuad(float(i * 320 + 32), 64.0f, 0.0f);
                    DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, 0xFFFFFFFF);
                    SetRect(&region, 0, badgeRow + 704, 256, badgeRow + 768);
                    QUAD->TranslateQuad(0.0f, 128.0f, 0.0f);
                    DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, 0xFFFFFFFF);
                    SetRect(&region, 0, badgeRow + 768, 256, badgeRow + 832);
                    QUAD->TranslateQuad(0.0f, 128.0f, 0.0f);
                    DRAW->DrawQuad(SIDE(signed char, 0xE0) * 2 + 1, &packet, &region, 0xFFFFFFFF);
                }
            }
        }
    }
}

#undef DIM
#undef NORMAL
#undef FIELD
#undef DRAW
#undef QUAD
#undef ANGLE
#undef SIDE
