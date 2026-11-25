#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/SpriteTransform.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/BattleScene.hpp"
#include "battle/BattleHud43E040.hpp"
#include "engine/GameProgress.hpp"

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
            if (fighters[i]->spellTimer > 0) {
                if (g_CombatMode == CombatMode::Story && i == 1) {
                    group = fighters[1]->field370[fighters[1]->field39D] + 42;
                    nameSlide = float(fighters[i]->sequenceSlots.at(group)->frames.at(g_OptionsModeAt006714D0 + 5).originX);
                    texture = fighters[i]->sequenceSlots.at(group)->frames.at(g_OptionsModeAt006714D0 + 5).textureIndex;
                } else {
                    if (fighters[i]->field39D == 2)
                        group = fighters[i]->selectedSpellCards[0] + 42;
                    else
                        group = fighters[i]->selectedSpellCards[1] + 45;
                    nameSlide = float(fighters[i]->sequenceSlots.at(group)->frames.at(i).originX);
                    texture = fighters[i]->sequenceSlots.at(group)->frames.at(0).textureIndex;
                }

                if (i == 0) {
                    SetRect(&rect, 641, 140, 862, 182);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(0.0f, spellPanelY[i], 221.0f, spellPanelY[i] + 42.0f);
                    textureManager->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(spellPanelAlpha[i], 255, 255, 255));
                    SetRect(&rect, 641, 124, 718, 140);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(90.0f, spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f,
                        167.0f, spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f + 16.0f);
                    textureManager->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255));
                    DrawAtlasNumberDefaultAt00446B60(160.0f,
                        spellPanelY[i] + spellNumbersOffsetY[i] + 31.0f,
                        D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), fighters[i]->spellTimer, 4);
                    DrawAtlasNumberDefaultAt00446B60(197.0f,
                        spellPanelY[i] + spellNumbersOffsetY[i] + 33.0f,
                        D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), initialSpellTimer[i], 4);
                    SetRect(&rect, 0, 0, 256, 32);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-nameSlide, spellPanelY[i] + 5.0f,
                        256.0f - nameSlide, spellPanelY[i] + 5.0f + 32.0f);
                    QUAD->ScaleQuad(10.0f, spellPanelY[i] + 16.0f, 0.0f,
                        spellTitleScale[i], spellTitleScale[i], 1.0f);
                    ACTOR_DRAWING->DrawQuad(texture, packet, &rect, D3DCOLOR_ARGB(spellTitleAlpha[i], 255, 255, 255));
                } else {
                    SetRect(&rect, 641, 140, 862, 182);
                    reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(440.0f, spellPanelY[i], 661.0f, spellPanelY[i] + 42.0f);
                    textureManager->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(spellPanelAlpha[i], 255, 255, 255));
                    if (g_CombatMode == CombatMode::Story) {
                        SetRect(&rect, 720, 124, 913, 140);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(425.0f, spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f,
                            618.0f, spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f + 16.0f);
                        textureManager->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255));
                        DrawAtlasNumberAt00446B90(520.0f,
                            spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f,
                            D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), fighters[i]->field3A4, 4, 7);
                        DrawAtlasNumberAt00446B90(610.0f,
                            spellPanelY[i] + spellNumbersOffsetY[i] + 31.0f,
                            D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), g_GameProgress.GetSpellBonusClears(reinterpret_cast<signed char*>(fighters[i]->field384)[fighters[i]->field39D]), 4, 3);
                        DrawAtlasNumberAt00446B90(639.0f,
                            spellPanelY[i] + spellNumbersOffsetY[i] + 33.0f,
                            D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), g_GameProgress.GetSpellAttempts(reinterpret_cast<signed char*>(fighters[i]->field384)[fighters[i]->field39D]), 4, 3);
                        SetRect(&rect, 0, 0, 256, 32);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-nameSlide, spellPanelY[i] + 5.0f,
                            256.0f - nameSlide, spellPanelY[i] + 5.0f + 32.0f);
                        QUAD->ScaleQuad(630.0f, spellPanelY[i] + 16.0f, 0.0f,
                            spellTitleScale[i], spellTitleScale[i], 1.0f);
                        ACTOR_DRAWING->DrawQuad(texture, packet, &rect, D3DCOLOR_ARGB(spellTitleAlpha[i], 255, 255, 255));
                    } else {
                        SetRect(&rect, 641, 124, 718, 140);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(430.0f, spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f,
                            507.0f, spellPanelY[i] + spellNumbersOffsetY[i] + 32.0f + 16.0f);
                        textureManager->DrawQuad(0, packet, &rect, D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255));
                        DrawAtlasNumberDefaultAt00446B60(500.0f,
                            spellPanelY[i] + spellNumbersOffsetY[i] + 31.0f,
                            D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), fighters[i]->spellTimer, 4);
                        DrawAtlasNumberDefaultAt00446B60(537.0f,
                            spellPanelY[i] + spellNumbersOffsetY[i] + 33.0f,
                            D3DCOLOR_ARGB(spellNumbersAlpha[i], 255, 255, 255), initialSpellTimer[i], 4);
                        SetRect(&rect, 0, 0, 256, 32);
                        reinterpret_cast<SpriteTransform*>(&packet)->BuildQuad(-nameSlide, spellPanelY[i] + 5.0f,
                            256.0f - nameSlide, spellPanelY[i] + 5.0f + 32.0f);
                        QUAD->ScaleQuad(630.0f, spellPanelY[i] + 16.0f, 0.0f,
                            spellTitleScale[i], spellTitleScale[i], 1.0f);
                        ACTOR_DRAWING->DrawQuad(texture, packet, &rect, D3DCOLOR_ARGB(spellTitleAlpha[i], 255, 255, 255));
                    }
                }
            }
        }
    }
}

#undef QUAD
#undef ACTOR_DRAWING
