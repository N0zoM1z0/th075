#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// Pointer-only entry views. Original identities and complete layouts unknown.
class SceneRenderer4292E0 { public: void Draw(); };
class ReplayBrowser42CA60 { public: void RenderList(); void DrawFilename(float, float, DWORD, const char*); void DrawNameGlyphs(float, float, DWORD, const signed char*); void DrawMetadataNumber(float, float, DWORD, int, int); };
class SceneQuadDrawingF124 { public: void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD); };
extern signed char g_SettingsDifficulty;
extern unsigned char g_SettingsByte00671604;
extern unsigned char g_SettingsByte00671430;
extern unsigned char g_SettingsByte00671428;
extern signed char g_SettingsVolume006714B7;
extern signed char g_SettingsVolume006714B6;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define DRAWING reinterpret_cast<TimelineDrawing438D00*>(FIELD(void*, 8))
#define QUAD_DRAWING reinterpret_cast<SceneQuadDrawingF124*>(FIELD(void*, 8))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
#define POSITIONS(value) reinterpret_cast<const float (*)[4]>(&(value))
#define OPACITY FIELD(unsigned char, 0x14)

void SceneRenderer4292E0::Draw() {
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 quadValue;
        RECT region;
        DRAWING->SetDepthMode(0);
        DRAWING->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 224, 128, 256);
        TRANSFORM(quadValue)->BuildQuad(0, 32.0f, 128.0f, 64.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 128, 224, 256, 256);
        TRANSFORM(quadValue)->BuildQuad(128.0f, 32.0f, 640.0f, 64.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 256, 224);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(144.0f, 64.0f, 0);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 0, 0, 256, 32);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(240.0f, 64.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 64, 64, 64));
        switch (g_SettingsDifficulty) {
        case 0: SetRect(&region, 0, 0, 56, 32); break;
        case 1: SetRect(&region, 56, 0, 128, 32); break;
        case 2: SetRect(&region, 128, 0, 180, 32); break;
        case 3: SetRect(&region, 180, 0, 256, 32); break;
        }
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(240.0f, 64.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 0, g_SettingsByte00671604 * 32 + 32, 64, g_SettingsByte00671604 * 32 + 64);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(432.0f, 96.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 0, g_SettingsByte00671430 * 32 + 32, 64, g_SettingsByte00671430 * 32 + 64);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(432.0f, 128.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 0, (1 - g_SettingsByte00671428) * 32 + 32, 64, (1 - g_SettingsByte00671428) * 32 + 64);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(432.0f, 160.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 64, 52, 256, 72);
        TRANSFORM(quadValue)->BuildQuad(0, 20.0f, 192.0f, 40.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 79, 109, 241, 115);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 13.0f, 177.0f, 19.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 79, 45, 241, 51);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 13.0f, 177.0f, 19.0f);
        TRANSFORM(quadValue)->ScaleQuad(15.0f, 13.0f, 0, static_cast<float>(g_SettingsVolume006714B7) / 100.0f, 1.0f, 1.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 79, 109, 241, 115);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 45.0f, 177.0f, 51.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 79, 77, 241, 83);
        TRANSFORM(quadValue)->BuildQuad(15.0f, 45.0f, 177.0f, 51.0f);
        TRANSFORM(quadValue)->ScaleQuad(15.0f, 45.0f, 0, static_cast<float>(g_SettingsVolume006714B6) / 100.0f, 1.0f, 1.0f);
        TRANSFORM(quadValue)->TranslateQuad(304.0f, 192.0f, 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255));
        SetRect(&region, 0, 96, 64, 128);
        TRANSFORM(quadValue)->BuildQuad(0, 0, 64.0f, 32.0f);
        TRANSFORM(quadValue)->TranslateQuad(96.0f, static_cast<float>(FIELD(short, 0x10) * 32 + 64), 0);
        QUAD_DRAWING->DrawQuad(2, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 500, 64);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(100.0f, 400.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(OPACITY, 0, 0, 0), FIELD(IDirect3DTexture8*, 12));
        TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(OPACITY, 0, 0, 0), FIELD(IDirect3DTexture8*, 12));
        TRANSFORM(quadValue)->TranslateQuad(-1.0f, 1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(OPACITY, 0, 0, 0), FIELD(IDirect3DTexture8*, 12));
        TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(OPACITY, 0, 0, 0), FIELD(IDirect3DTexture8*, 12));
        TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
        Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(OPACITY, 255, 255, 255), FIELD(IDirect3DTexture8*, 12));
        Graphics::EndFrame();
    }
}

#undef OPACITY
#undef POSITIONS
#undef TRANSFORM
#undef QUAD_DRAWING
#undef DRAWING
#undef FIELD

class ReplayFilesF124 { public: unsigned int Size(); const char** At(unsigned int); };
class ReplayRecordsF124 { public: void* At(unsigned int); };
class ReplayModesF124 { public: unsigned char* At(unsigned int); };

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define DRAWING reinterpret_cast<TimelineDrawing438D00*>(FIELD(void*, 8))
#define QUAD_DRAWING reinterpret_cast<SceneQuadDrawingF124*>(FIELD(void*, 8))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
#define FILES reinterpret_cast<ReplayFilesF124*>(reinterpret_cast<char*>(this) + 12)
#define RECORDS reinterpret_cast<ReplayRecordsF124*>(reinterpret_cast<char*>(this) + 32)
#define MODES reinterpret_cast<ReplayModesF124*>(reinterpret_cast<char*>(this) + 52)
#define RECORD_BYTE(index, offset) (*(static_cast<signed char*>(RECORDS->At(index)) + (offset)))

void ReplayBrowser42CA60::RenderList() {
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 quadValue;
        RECT region;
        int firstRow;
        int pageRows;
        DWORD textTint;
        int recordIndex;
        DWORD shadowColor;
        int selectionIndex;
        BYTE opacity;
        DRAWING->SetDepthMode(0);
        DRAWING->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 192, 96, 512, 128);
        TRANSFORM(quadValue)->BuildQuad(160.0f, 10.0f, 480.0f, 42.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 20);
        TRANSFORM(quadValue)->BuildQuad(64.0f, 50.0f, 576.0f, 70.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        pageRows = 10;
        firstRow = (FIELD(short, 0x48) / 10) * 10;
        if (FIELD(short, 0x48) / 10 == FILES->Size() / 10) pageRows = FILES->Size() % 10;
        for (recordIndex = 0; recordIndex < pageRows; recordIndex++) {
            if (firstRow + recordIndex == FIELD(short, 0x48))
                textTint = D3DCOLOR_ARGB(FIELD(unsigned char, 0x4C), 255, 255, 255);
            else
                textTint = D3DCOLOR_ARGB(FIELD(unsigned char, 0x4C) / 2, 255, 255, 255);
            DrawFilename(50.0f, static_cast<float>(recordIndex * 24 + 80), textTint, *FILES->At(firstRow + recordIndex));
            DrawNameGlyphs(160.0f, static_cast<float>(recordIndex * 24 + 80), textTint, static_cast<signed char*>(RECORDS->At(firstRow + recordIndex)));
            DrawMetadataNumber(330.0f, static_cast<float>(recordIndex * 24 + 80), textTint, RECORD_BYTE(firstRow + recordIndex, 8), 2);
            SetRect(&region, 228, 40, 247, 60);
            TRANSFORM(quadValue)->BuildQuad(325.0f, static_cast<float>(recordIndex * 24 + 80), 344.0f, static_cast<float>(recordIndex * 24 + 100));
            QUAD_DRAWING->DrawQuad(2, quadValue, &region, textTint);
            DrawMetadataNumber(370.0f, static_cast<float>(recordIndex * 24 + 80), textTint, RECORD_BYTE(firstRow + recordIndex, 9), 2);
            if (RECORD_BYTE(firstRow + recordIndex, 13) == 0) {
                if (firstRow + recordIndex == FIELD(short, 0x48))
                    shadowColor = D3DCOLOR_ARGB(FIELD(unsigned char, 0x4C), 192, 192, 192);
                else
                    shadowColor = D3DCOLOR_ARGB(FIELD(unsigned char, 0x4C) / 2, 192, 192, 192);
                SetRect(&region, 0, *MODES->At(firstRow + recordIndex) * 20 + 20, 100, *MODES->At(firstRow + recordIndex) * 20 + 40);
                TRANSFORM(quadValue)->BuildQuad(380.0f, static_cast<float>(recordIndex * 24 + 86), 480.0f, static_cast<float>(recordIndex * 24 + 100));
                TRANSFORM(quadValue)->TranslateQuad(36.0f, 8.0f, 0);
                QUAD_DRAWING->DrawQuad(1, quadValue, &region, shadowColor);
            }
            SetRect(&region, 0, RECORD_BYTE(firstRow + recordIndex, 10) * 20 + 20, 100, RECORD_BYTE(firstRow + recordIndex, 10) * 20 + 40);
            TRANSFORM(quadValue)->BuildQuad(380.0f, static_cast<float>(recordIndex * 24 + 80), 480.0f, static_cast<float>(recordIndex * 24 + 100));
            QUAD_DRAWING->DrawQuad(1, quadValue, &region, textTint);
            SetRect(&region, 100, RECORD_BYTE(firstRow + recordIndex, 13) * 20 + 20, 180, RECORD_BYTE(firstRow + recordIndex, 13) * 20 + 40);
            TRANSFORM(quadValue)->BuildQuad(500.0f, static_cast<float>(recordIndex * 24 + 80), 580.0f, static_cast<float>(recordIndex * 24 + 100));
            QUAD_DRAWING->DrawQuad(1, quadValue, &region, textTint);
        }
        if (FIELD(signed char, 0x51) == 1) {
            for (selectionIndex = 0; selectionIndex < RECORD_BYTE(FIELD(short, 0x48), 14); selectionIndex++) {
                if (FIELD(short, 0x4A) == selectionIndex) opacity = 255;
                else opacity = 128;
                SetRect(&region, 100, selectionIndex * 17 + 224, 200, selectionIndex * 17 + 241);
                TRANSFORM(quadValue)->BuildQuad(40.0f, static_cast<float>(selectionIndex * 20 + 320), 140.0f, static_cast<float>(selectionIndex * 20 + 337));
                if (selectionIndex >= 5) TRANSFORM(quadValue)->TranslateQuad(120.0f, -100.0f, 0);
                QUAD_DRAWING->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(opacity, 255, 255, 255));
            }
        }
        Graphics::EndFrame();
    }
}

#undef RECORD_BYTE
#undef MODES
#undef RECORDS
#undef FILES
#undef TRANSFORM
#undef QUAD_DRAWING
#undef DRAWING
#undef FIELD
