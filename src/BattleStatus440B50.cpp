#include "GameSharedState.hpp"
#include "SpriteTransform.hpp"
#include "TextureManagerF198.hpp"
#include "BattleScene.hpp"
#include "BattleHud43E040.hpp"
#include "BattleStatusFloatPairF1096.hpp"
#include "GameProgress.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define ACTOR(type, offset) (*reinterpret_cast<type*>(FIELD(char*, 0x44 + i * 4) + (offset)))
#define DRAWING reinterpret_cast<TextureManagerF198*>(textures)
#define ACTOR_DRAWING reinterpret_cast<TextureManagerF198*>(fighters[i]->drawing)
#define QUAD reinterpret_cast<SpriteTransform*>(&packet)

void BattleScene::RenderStatus() {
    float nameSlide;
    RenderQuadPacket5E68C0 packet;
    {
        int i;
        short texture;
        RECT rect;
        int group;
        for (i = 0; i < 2; i = i + 1) {
            if (fighters[i]->field3A0 > 0) {
                if (g_CombatMode == 3 && i == 1) {
                    group = fighters[1]->field370[fighters[1]->field39D] + 42;
                    nameSlide = float(reinterpret_cast<HudDirectory43E040*>(&fighters[i]->sequenceSlots)->At(group)->At(g_OptionsModeAt006714D0 + 5)[0]);
                    texture = reinterpret_cast<HudDirectory43E040*>(&fighters[i]->sequenceSlots)->At(group)->At(g_OptionsModeAt006714D0 + 5)[3];
                } else {
                    if (fighters[i]->field39D == 2)
                        group = fighters[i]->field398[0] + 42;
                    else
                        group = fighters[i]->field398[1] + 45;
                    nameSlide = float(reinterpret_cast<HudDirectory43E040*>(&fighters[i]->sequenceSlots)->At(group)->At(i)[0]);
                    texture = reinterpret_cast<HudDirectory43E040*>(&fighters[i]->sequenceSlots)->At(group)->At(0)[3];
                }

                if (i == 0) {
                    SetRect(&rect, 641, 140, 862, 182);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, F1096_STATUS_FLOAT(this, 0xF4, i), 221.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + 42.0f);
                    DRAWING->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(field0DC[i], 255, 255, 255));
                    SetRect(&rect, 641, 124, 718, 140);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(90.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f,
                        167.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f + 16.0f);
                    DRAWING->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(field0E0[i], 255, 255, 255));
                    DrawAtlasNumberDefaultAt00446B60(160.0f,
                        F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 31.0f,
                        D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), fighters[i]->field3A0, 4);
                    DrawAtlasNumberDefaultAt00446B60(197.0f,
                        F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 33.0f,
                        D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), field0EC[i], 4);
                    SetRect(&rect, 0, 0, 256, 32);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-nameSlide, F1096_STATUS_FLOAT(this, 0xF4, i) + 5.0f,
                        256.0f - nameSlide, F1096_STATUS_FLOAT(this, 0xF4, i) + 5.0f + 32.0f);
                    QUAD->ScaleQuad(10.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + 16.0f, 0.0f,
                        F1096_STATUS_FLOAT(this, 0xE4, i), F1096_STATUS_FLOAT(this, 0xE4, i), 1.0f);
                    ACTOR_DRAWING->DrawQuad(texture, packet, &rect, D3DCOLOR_ARGB(field0DE[i], 255, 255, 255));
                } else {
                    SetRect(&rect, 641, 140, 862, 182);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(440.0f, F1096_STATUS_FLOAT(this, 0xF4, i), 661.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + 42.0f);
                    DRAWING->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(field0DC[i], 255, 255, 255));
                    if (g_CombatMode == 3) {
                        SetRect(&rect, 720, 124, 913, 140);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(425.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f,
                            618.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f + 16.0f);
                        DRAWING->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(field0E0[i], 255, 255, 255));
                        DrawAtlasNumberAt00446B90(520.0f,
                            F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f,
                            D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), fighters[i]->field3A4, 4, 7);
                        DrawAtlasNumberAt00446B90(610.0f,
                            F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 31.0f,
                            D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), g_GameProgress.ReadSelectedWord268(reinterpret_cast<signed char*>(fighters[i]->field384)[fighters[i]->field39D]), 4, 3);
                        DrawAtlasNumberAt00446B90(639.0f,
                            F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 33.0f,
                            D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), g_GameProgress.ReadSelectedWord394(reinterpret_cast<signed char*>(fighters[i]->field384)[fighters[i]->field39D]), 4, 3);
                        SetRect(&rect, 0, 0, 256, 32);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-nameSlide, F1096_STATUS_FLOAT(this, 0xF4, i) + 5.0f,
                            256.0f - nameSlide, F1096_STATUS_FLOAT(this, 0xF4, i) + 5.0f + 32.0f);
                        QUAD->ScaleQuad(630.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + 16.0f, 0.0f,
                            F1096_STATUS_FLOAT(this, 0xE4, i), F1096_STATUS_FLOAT(this, 0xE4, i), 1.0f);
                        ACTOR_DRAWING->DrawQuad(texture, packet, &rect, D3DCOLOR_ARGB(field0DE[i], 255, 255, 255));
                    } else {
                        SetRect(&rect, 641, 124, 718, 140);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(430.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f,
                            507.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 32.0f + 16.0f);
                        DRAWING->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(field0E0[i], 255, 255, 255));
                        DrawAtlasNumberDefaultAt00446B60(500.0f,
                            F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 31.0f,
                            D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), fighters[i]->field3A0, 4);
                        DrawAtlasNumberDefaultAt00446B60(537.0f,
                            F1096_STATUS_FLOAT(this, 0xF4, i) + F1096_STATUS_FLOAT(this, 0x104, i) + 33.0f,
                            D3DCOLOR_ARGB(field0E0[i], 255, 255, 255), field0EC[i], 4);
                        SetRect(&rect, 0, 0, 256, 32);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-nameSlide, F1096_STATUS_FLOAT(this, 0xF4, i) + 5.0f,
                            256.0f - nameSlide, F1096_STATUS_FLOAT(this, 0xF4, i) + 5.0f + 32.0f);
                        QUAD->ScaleQuad(630.0f, F1096_STATUS_FLOAT(this, 0xF4, i) + 16.0f, 0.0f,
                            F1096_STATUS_FLOAT(this, 0xE4, i), F1096_STATUS_FLOAT(this, 0xE4, i), 1.0f);
                        ACTOR_DRAWING->DrawQuad(texture, packet, &rect, D3DCOLOR_ARGB(field0DE[i], 255, 255, 255));
                    }
                }
            }
        }
    }
}

#undef reinterpret_cast<signed char*>(fighters[i]->field384)[fighters[i]->field39D]
#undef QUAD
#undef ACTOR_DRAWING
#undef DRAWING
#undef ACTOR
#undef FIELD
