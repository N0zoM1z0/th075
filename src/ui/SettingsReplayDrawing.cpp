#include "replay/ReplayBrowserScene.hpp"
#include "config/GameConfigStorage.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "ui/OptionsScene.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"

// Pointer-only entry views. Original identities and complete layouts unknown.
class SceneQuadDrawingF124 { public: void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD); };
extern unsigned char g_OptionsFlagAt00671604;
extern unsigned char g_OptionsFlagAt00671430;
extern unsigned char g_OptionsFlagAt00671428;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define DRAWING reinterpret_cast<TextureManagerF198*>(textures)
#define QUAD_DRAWING reinterpret_cast<SceneQuadDrawingF124*>(textures)
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
#define POSITIONS(value) reinterpret_cast<const float (*)[4]>(&(value))

void OptionsScene::Render() {
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 quadValue;
        RECT region;
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetDepthMode(0);
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(0, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 224, 128, 256);
        TRANSFORM(quadValue)->BuildQuad(0, 32.0f, 128.0f, 64.0f);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 128, 224, 256, 256);
        TRANSFORM(quadValue)->BuildQuad(128.0f, 32.0f, 640.0f, 64.0f);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 256, 224);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(144.0f, 64.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 0, 0, 256, 32);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(240.0f, 64.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 64, 64, 64));
        switch (g_OptionsModeAt006714D0) {
        case 0: SetRect(&region, 0, 0, 56, 32); break;
        case 1: SetRect(&region, 56, 0, 128, 32); break;
        case 2: SetRect(&region, 128, 0, 180, 32); break;
        case 3: SetRect(&region, 180, 0, 256, 32); break;
        }
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(240.0f, 64.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 0, g_OptionsFlagAt00671604 * 32 + 32, 64, g_OptionsFlagAt00671604 * 32 + 64);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(432.0f, 96.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 0, g_OptionsFlagAt00671430 * 32 + 32, 64, g_OptionsFlagAt00671430 * 32 + 64);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(432.0f, 128.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 0, (1 - g_OptionsFlagAt00671428) * 32 + 32, 64, (1 - g_OptionsFlagAt00671428) * 32 + 64);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(432.0f, 160.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 64, 52, 256, 72);
        TRANSFORM(quadValue)->BuildQuad(0, 20.0f, 192.0f, 40.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 79, 109, 241, 115);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 13.0f, 177.0f, 19.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 79, 45, 241, 51);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 13.0f, 177.0f, 19.0f);
        TRANSFORM(quadValue)->ScaleQuad(15.0f, 13.0f, 0, static_cast<float>(static_cast<signed char>(g_StreamVolumeAt006714B7)) / 100.0f, 1.0f, 1.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 79, 109, 241, 115);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 45.0f, 177.0f, 51.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 79, 77, 241, 83);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 45.0f, 177.0f, 51.0f);
        TRANSFORM(quadValue)->ScaleQuad(15.0f, 45.0f, 0, static_cast<float>(static_cast<signed char>(g_SoundVolumeAt006714B6)) / 100.0f, 1.0f, 1.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(field014, 255, 255, 255));
        SetRect(&region, 0, 96, 64, 128);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(96.0f, static_cast<float>(currentItem * 32 + 64), 0);
        reinterpret_cast<TextureManagerF198*>(QUAD_DRAWING)->DrawQuad(2, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 500, 64);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(100.0f, 400.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(field014, 0, 0, 0), canvas);
        TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(field014, 0, 0, 0), canvas);
        TRANSFORM(quadValue)->TranslateQuad(-1.0f, 1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(field014, 0, 0, 0), canvas);
        TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(field014, 0, 0, 0), canvas);
        TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(field014, 255, 255, 255), canvas);
        Graphics::EndFrame();
    }
}

#undef POSITIONS
#undef TRANSFORM
#undef QUAD_DRAWING
#undef DRAWING
#undef FIELD

#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

void ReplayBrowserScene::Render() {
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 quadValue;
        RECT region;
        int firstRow;
        int pageRows;
        DWORD textTint;
        int recordIndex;
        DWORD shadowColor;
        int selectionIndex;
        BYTE opacity;
        texture->SetDepthMode(0);
        texture->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        texture->DrawQuad(0, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 192, 96, 512, 128);
        TRANSFORM(quadValue)->BuildQuad(160.0f, 10.0f, 480.0f, 42.0f);
        texture->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 20);
        TRANSFORM(quadValue)->BuildQuad(64.0f, 50.0f, 576.0f, 70.0f);
        texture->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        pageRows = 10;
        firstRow = (field048 / 10) * 10;
        if (field048 / 10 == filenames.size() / 10) pageRows = filenames.size() % 10;
        for (recordIndex = 0; recordIndex < pageRows; recordIndex++) {
            if (firstRow + recordIndex == field048)
                textTint = D3DCOLOR_ARGB(field04C, 255, 255, 255);
            else
                textTint = D3DCOLOR_ARGB(field04C / 2, 255, 255, 255);
            DrawFilename(50.0f, static_cast<float>(recordIndex * 24 + 80), textTint, filenames[firstRow + recordIndex]);
            DrawNameGlyphs(160.0f, static_cast<float>(recordIndex * 24 + 80), textTint, reinterpret_cast<const signed char*>(headers[firstRow + recordIndex].playerName));
            DrawMetadataNumber(330.0f, static_cast<float>(recordIndex * 24 + 80), textTint, static_cast<signed char>(headers[firstRow + recordIndex].month), 2);
            SetRect(&region, 228, 40, 247, 60);
            TRANSFORM(quadValue)->BuildQuad(325.0f, static_cast<float>(recordIndex * 24 + 80), 344.0f, static_cast<float>(recordIndex * 24 + 100));
            texture->DrawQuad(2, quadValue, &region, textTint);
            DrawMetadataNumber(370.0f, static_cast<float>(recordIndex * 24 + 80), textTint, static_cast<signed char>(headers[firstRow + recordIndex].day), 2);
            if (static_cast<signed char>(headers[firstRow + recordIndex].mode) == 0) {
                if (firstRow + recordIndex == field048)
                    shadowColor = D3DCOLOR_ARGB(field04C, 192, 192, 192);
                else
                    shadowColor = D3DCOLOR_ARGB(field04C / 2, 192, 192, 192);
                SetRect(&region, 0, secondaryModes[firstRow + recordIndex] * 20 + 20, 100, secondaryModes[firstRow + recordIndex] * 20 + 40);
                TRANSFORM(quadValue)->BuildQuad(380.0f, static_cast<float>(recordIndex * 24 + 86), 480.0f, static_cast<float>(recordIndex * 24 + 100));
                TRANSFORM(quadValue)->TranslateQuad(36.0f, 8.0f, 0);
                texture->DrawQuad(1, quadValue, &region, shadowColor);
            }
            SetRect(&region, 0, static_cast<signed char>(headers[firstRow + recordIndex].primaryFighter) * 20 + 20, 100, static_cast<signed char>(headers[firstRow + recordIndex].primaryFighter) * 20 + 40);
            TRANSFORM(quadValue)->BuildQuad(380.0f, static_cast<float>(recordIndex * 24 + 80), 480.0f, static_cast<float>(recordIndex * 24 + 100));
            texture->DrawQuad(1, quadValue, &region, textTint);
            SetRect(&region, 100, static_cast<signed char>(headers[firstRow + recordIndex].mode) * 20 + 20, 180, static_cast<signed char>(headers[firstRow + recordIndex].mode) * 20 + 40);
            TRANSFORM(quadValue)->BuildQuad(500.0f, static_cast<float>(recordIndex * 24 + 80), 580.0f, static_cast<float>(recordIndex * 24 + 100));
            texture->DrawQuad(1, quadValue, &region, textTint);
        }
        if (field051 == 1) {
            for (selectionIndex = 0; selectionIndex < headers[field048].recordCount; selectionIndex++) {
                if (field04A == selectionIndex) opacity = 255;
                else opacity = 128;
                SetRect(&region, 100, selectionIndex * 17 + 224, 200, selectionIndex * 17 + 241);
                TRANSFORM(quadValue)->BuildQuad(40.0f, static_cast<float>(selectionIndex * 20 + 320), 140.0f, static_cast<float>(selectionIndex * 20 + 337));
                if (selectionIndex >= 5) TRANSFORM(quadValue)->TranslateQuad(120.0f, -100.0f, 0);
                texture->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(opacity, 255, 255, 255));
            }
        }
        Graphics::EndFrame();
    }
}

#undef TRANSFORM
