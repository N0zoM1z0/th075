#include "ui/MusicRoomScene.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"
#include "ui/ResultListScene.hpp"
#include "engine/GameProgress.hpp"

#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
#define POSITIONS(value) reinterpret_cast<const float (*)[4]>(&(value))

void MusicRoomScene::Render() {
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 quadValue;
        SpriteQuad40CA80 iconQuad;
        RECT region;
        RECT iconRegion;
        int musicIndex;
        BYTE opacity;
        texture->SetDepthMode(0);
        texture->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        texture->DrawQuad(0, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 34, 256, 98);
        TRANSFORM(quadValue)->BuildQuad(10.0f, 10.0f, 266.0f, 74.0f);
        texture->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        TRANSFORM(quadValue)->BuildQuad(90.0f, 90.0f, 602.0f, 108.0f);
        SetRect(&iconRegion, 150, 10, 157, 16);
        TRANSFORM(iconQuad)->BuildQuad(80.0f, 100.0f, 87.0f, 106.0f);
        for (musicIndex = 0; musicIndex < 10 && firstVisibleTrack + musicIndex < trackCount; musicIndex++) {
            if (firstVisibleTrack + musicIndex != selectedTrack)
                opacity = 128;
            else
                opacity = 255;
            DrawNumber(80.0f, quadValue.first.y + 1.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255),
                       firstVisibleTrack + 1 + musicIndex, 2);
            texture->DrawQuad(1, iconQuad, &iconRegion, D3DCOLOR_ARGB(opacity, 255, 255, 255));
            SetRect(&region, 0, (firstVisibleTrack + musicIndex) * 18, 512,
                    (firstVisibleTrack + musicIndex) * 18 + 18);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), canvasB);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), canvasB);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), canvasB);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), canvasB);
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 255, 255, 255), canvasB);
            TRANSFORM(quadValue)->TranslateQuad(0, 18.0f, 0);
            TRANSFORM(iconQuad)->TranslateQuad(0, 18.0f, 0);
        }
        SetRect(&region, 165, 0, 180, 16);
        TRANSFORM(quadValue)->BuildQuad(30.0f,
            static_cast<float>((selectedTrack - firstVisibleTrack) * 18 + 90), 45.0f,
            static_cast<float>((selectedTrack - firstVisibleTrack) * 18 + 106));
        texture->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 32);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(64.0f, 320.0f, 0);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasD);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasD);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasD);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasD);
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFFFFFFFF, canvasD);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(300.0f, 40.0f, 0);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasC);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasC);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasC);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasC);
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFFFFFFFF, canvasC);
        SetRect(&region, 0, 16, 120, 32);
        TRANSFORM(quadValue)->BuildQuad(300.0f, 20.0f, 420.0f, 36.0f);
        texture->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 512);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(80.0f, 340.0f, 0);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasA);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasA);
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasA);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, canvasA);
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFFFFFFFF, canvasA);
        Graphics::EndFrame();
    }
}

void ResultListScene::Render() {
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 spriteQuad;
        RECT region;
        int rankIndex;
        int entry;
        int rowLimit;
        mainTexture->SetDepthMode(0);
        mainTexture->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(spriteQuad)->BuildQuadFromRect(&region);
        mainTexture->DrawQuad(0, spriteQuad, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 512);
        TRANSFORM(spriteQuad)->BuildQuadFromRect(&region);
        TRANSFORM(spriteQuad)->ScaleQuad(256.0f, 0, 0, -1.0f, 1.0f, 1.0f);
        TRANSFORM(spriteQuad)->TranslateQuad(128.0f, 0, 0);
        auxiliaryTexture->DrawQuad(0, spriteQuad, &region, 0xFF808080);
        if ((showingRecords) == 0) {
            SetRect(&region, 0, 24, 120, 120);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 120.0f, 96.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 72.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 0, 0, 240, 240);
            TRANSFORM(spriteQuad)->BuildQuadFromRect(&region);
            TRANSFORM(spriteQuad)->TranslateQuad(200.0f, 74.0f, 0);
            TRANSFORM(spriteQuad)->TranslateQuad(0.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFFFFFFFF, (canvas));
            SetRect(&region, 0, 0, 240, 24);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 240.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 20.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 0, (selectedCharacter) * 24, 128,
                    (selectedCharacter) * 24 + 24);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 128.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(320.0f, 20.0f, 0);
            mainTexture->DrawQuad(3, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 168, (difficultyIndex) * 24 + 24, 240,
                    (difficultyIndex) * 24 + 48);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 72.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(464.0f, 20.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 24, 168, 48);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 200.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 48, 168, 72);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(160.0f, 200.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 72, 168, 96);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(300.0f, 200.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 96, 168, 120);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(500.0f, 200.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            for (rankIndex = 0; rankIndex < 10; rankIndex++) {
                DrawRankLabel(80.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, rankIndex + 1);
                DrawNameGlyphs(160.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, reinterpret_cast<const signed char*>(selectedRecord->scores[rankIndex].name));
                DrawCounter(330.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, static_cast<signed char>(selectedRecord->scores[rankIndex].month), 2);
                SetRect(&region, 228, 40, 247, 60);
                TRANSFORM(spriteQuad)->BuildQuad(325.0f, static_cast<float>(rankIndex * 20 + 230), 344.0f, static_cast<float>(rankIndex * 20 + 250));
                mainTexture->DrawQuad(2, spriteQuad, &region, 0xFFFFFFFF);
                DrawCounter(370.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, static_cast<signed char>(selectedRecord->scores[rankIndex].day), 2);
                DrawCounter(560.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, static_cast<int>(selectedRecord->scores[rankIndex].score), 0);
            }
        } else {
            rowLimit = 10;
            mainTexture->SetBlendMode(2);
            for (entry = 0; entry < rowLimit; entry++) {
                SetRect(&region, 128, 67, 130, 77);
                TRANSFORM(spriteQuad)->BuildQuad(10.0f, static_cast<float>(entry * 32 + 70), 630.0f, static_cast<float>(entry * 32 + 80));
                mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            }
            mainTexture->SetBlendMode(0);
            rowLimit = 0;
            SetRect(&region, 0, 144, 24, 168);
            for (entry = (pageIndex) * 10;
                 entry < (pageIndex) * 10 + 10 && entry < static_cast<int>(records.size()); entry++) {
                DrawCounter(540.0f, static_cast<float>(rowLimit * 32 + 63), 0xFF8080FF,
                            selectedRecord->bestSpellBonus[entry], 0);
                if (selectedRecord->spellCaptureFlags[entry]) {
                    TRANSFORM(spriteQuad)->BuildQuad(535.0f, static_cast<float>(rowLimit * 32 + 61), 559.0f, static_cast<float>(rowLimit * 32 + 85));
                    mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
                }
                rowLimit++;
            }
            SetRect(&region, 0, 0, 620, 320);
            TRANSFORM(spriteQuad)->BuildQuad(10.0f, 62.0f, 630.0f, 382.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, (canvas));
            TRANSFORM(spriteQuad)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFFFFFFFF, (canvas));
            SetRect(&region, 0, 120, 240, 144);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 240.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 20.0f, 0);
            mainTexture->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 0, (selectedCharacter) * 24, 128,
                    (selectedCharacter) * 24 + 24);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 128.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(320.0f, 20.0f, 0);
            mainTexture->DrawQuad(3, spriteQuad, &region, 0xFFFFFFFF);
        }
        Graphics::EndFrame();
    }
}
