#include "BattleStatus440B50.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define ACTOR(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44 + i * 4) + (offset)))
#define RIGHT(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x48) + (offset)))
#define DIRECTORY reinterpret_cast<HudDirectory43E040*>(FIELD(char*, 0x44 + i * 4) + 0x468)
#define DRAWING reinterpret_cast<RenderDrawing5E68C0*>(FIELD(void*, 8))
#define ACTOR_DRAWING reinterpret_cast<RenderDrawing5E68C0*>(ACTOR(void*, 4))
#define QUAD reinterpret_cast<HudQuadOperations43E040*>(&packet)
#define RECORDS reinterpret_cast<StatusRecords440B50*>(&g_BattleRecords)
#define ALPHA(offset) D3DCOLOR_ARGB(FIELD(unsigned char, (offset) + i), 255, 255, 255)
#define SELECTOR reinterpret_cast<signed char*>(FIELD(char*, 0x44 + i * 4) + 0x384)[ACTOR(signed char, 0x39D)]

void BattleStatus440B50::RenderStatus() {
    float nameSlide;
    RenderQuadPacket5E68C0 packet;
    {
        int i;
        short texture;
        RECT rect;
        int group;
        for (i = 0; i < 2; i = i + 1) {
            if (ACTOR(short, 0x3A0) > 0) {
                if (g_CombatMode == 3 && i == 1) {
                    group = reinterpret_cast<signed char*>(FIELD(char*, 0x48) + 0x370)[RIGHT(signed char, 0x39D)] + 42;
                    nameSlide = float(DIRECTORY->At(group)->At(g_StateRepeatLevelAt006714D0 + 5)[0]);
                    texture = DIRECTORY->At(group)->At(g_StateRepeatLevelAt006714D0 + 5)[3];
                } else {
                    if (ACTOR(signed char, 0x39D) == 2)
                        group = ACTOR(short, 0x398) + 42;
                    else
                        group = ACTOR(short, 0x39A) + 45;
                    nameSlide = float(DIRECTORY->At(group)->At(i)[0]);
                    texture = DIRECTORY->At(group)->At(0)[3];
                }

                if (i == 0) {
                    SetRect(&rect, 641, 140, 862, 182);
                    packet.BuildQuad(0.0f, FLOAT(0xF4 + i * 4), 221.0f, FLOAT(0xF4 + i * 4) + 42.0f);
                    DRAWING->DrawQuad(0, &packet, &rect, ALPHA(0xDC));
                    SetRect(&rect, 641, 124, 718, 140);
                    packet.BuildQuad(90.0f, FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f,
                        167.0f, FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f + 16.0f);
                    DRAWING->DrawQuad(0, &packet, &rect, ALPHA(0xE0));
                    DrawAtlasNumberDefaultAt00446B60(160.0f,
                        FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 31.0f,
                        ALPHA(0xE0), ACTOR(short, 0x3A0), 4);
                    DrawAtlasNumberDefaultAt00446B60(197.0f,
                        FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 33.0f,
                        ALPHA(0xE0), FIELD(int, 0xEC + i * 4), 4);
                    SetRect(&rect, 0, 0, 256, 32);
                    packet.BuildQuad(-nameSlide, FLOAT(0xF4 + i * 4) + 5.0f,
                        256.0f - nameSlide, FLOAT(0xF4 + i * 4) + 5.0f + 32.0f);
                    QUAD->Scale(10.0f, FLOAT(0xF4 + i * 4) + 16.0f, 0.0f,
                        FLOAT(0xE4 + i * 4), FLOAT(0xE4 + i * 4), 1.0f);
                    ACTOR_DRAWING->DrawQuad(texture, &packet, &rect, ALPHA(0xDE));
                } else {
                    SetRect(&rect, 641, 140, 862, 182);
                    packet.BuildQuad(440.0f, FLOAT(0xF4 + i * 4), 661.0f, FLOAT(0xF4 + i * 4) + 42.0f);
                    DRAWING->DrawQuad(0, &packet, &rect, ALPHA(0xDC));
                    if (g_CombatMode == 3) {
                        SetRect(&rect, 720, 124, 913, 140);
                        packet.BuildQuad(425.0f, FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f,
                            618.0f, FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f + 16.0f);
                        DRAWING->DrawQuad(0, &packet, &rect, ALPHA(0xE0));
                        DrawAtlasNumberAt00446B90(520.0f,
                            FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f,
                            ALPHA(0xE0), ACTOR(int, 0x3A4), 4, 7);
                        DrawAtlasNumberAt00446B90(610.0f,
                            FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 31.0f,
                            ALPHA(0xE0), RECORDS->GetValueAt0268(SELECTOR), 4, 3);
                        DrawAtlasNumberAt00446B90(639.0f,
                            FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 33.0f,
                            ALPHA(0xE0), RECORDS->GetValueAt0394(SELECTOR), 4, 3);
                        SetRect(&rect, 0, 0, 256, 32);
                        packet.BuildQuad(-nameSlide, FLOAT(0xF4 + i * 4) + 5.0f,
                            256.0f - nameSlide, FLOAT(0xF4 + i * 4) + 5.0f + 32.0f);
                        QUAD->Scale(630.0f, FLOAT(0xF4 + i * 4) + 16.0f, 0.0f,
                            FLOAT(0xE4 + i * 4), FLOAT(0xE4 + i * 4), 1.0f);
                        ACTOR_DRAWING->DrawQuad(texture, &packet, &rect, ALPHA(0xDE));
                    } else {
                        SetRect(&rect, 641, 124, 718, 140);
                        packet.BuildQuad(430.0f, FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f,
                            507.0f, FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 32.0f + 16.0f);
                        DRAWING->DrawQuad(0, &packet, &rect, ALPHA(0xE0));
                        DrawAtlasNumberDefaultAt00446B60(500.0f,
                            FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 31.0f,
                            ALPHA(0xE0), ACTOR(short, 0x3A0), 4);
                        DrawAtlasNumberDefaultAt00446B60(537.0f,
                            FLOAT(0xF4 + i * 4) + FLOAT(0x104 + i * 4) + 33.0f,
                            ALPHA(0xE0), FIELD(int, 0xEC + i * 4), 4);
                        SetRect(&rect, 0, 0, 256, 32);
                        packet.BuildQuad(-nameSlide, FLOAT(0xF4 + i * 4) + 5.0f,
                            256.0f - nameSlide, FLOAT(0xF4 + i * 4) + 5.0f + 32.0f);
                        QUAD->Scale(630.0f, FLOAT(0xF4 + i * 4) + 16.0f, 0.0f,
                            FLOAT(0xE4 + i * 4), FLOAT(0xE4 + i * 4), 1.0f);
                        ACTOR_DRAWING->DrawQuad(texture, &packet, &rect, ALPHA(0xDE));
                    }
                }
            }
        }
    }
}

#undef SELECTOR
#undef ALPHA
#undef RECORDS
#undef QUAD
#undef ACTOR_DRAWING
#undef DRAWING
#undef DIRECTORY
#undef RIGHT
#undef ACTOR
#undef FLOAT
#undef FIELD
