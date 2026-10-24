#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"

// All private scene/container/manager interfaces are pointer-only. Never
// instantiate or embed them, or infer their complete layouts from these views.
class SceneQuadDrawingF119 {
public:
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
};
class MusicScene425C80 {
public:
    void RenderList();
    void DrawNumber(float, float, DWORD, int, int);
};
class ResultScene430080 {
public:
    void RenderRecordPage();
    void DrawCounter(float, float, DWORD, int, int);
    void DrawNameGlyphs(float, float, DWORD, const signed char*);
    void DrawRankLabel(float, float, DWORD, signed char);
};
class SceneRecordContainerF119 { public: unsigned int Size(); };
// Read-only row projection: the native stride and consumed fields are observed.
// This is never instantiated. Original identity and any unobserved bytes remain
// unknown; the two alignment bytes are not represented as invented members.
struct ResultRowF119 {
    signed char name[8];
    signed char firstResult;
    signed char secondResult;
    int score;
};
typedef char ResultRowStrideF119[(sizeof(ResultRowF119) == 16) ? 1 : -1];
typedef char ResultRowScoreF119[(offsetof(ResultRowF119, score) == 12) ? 1 : -1];
#define SCENE_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset))
#define DRAWING reinterpret_cast<TimelineDrawing438D00*>(SCENE_FIELD(void*, 8))
#define QUAD_DRAWING reinterpret_cast<SceneQuadDrawingF119*>(SCENE_FIELD(void*, 8))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
#define POSITIONS(value) reinterpret_cast<const float (*)[4]>(&(value))
#define TEXTURE(offset) SCENE_FIELD(IDirect3DTexture8*, offset)
#define DATA SCENE_FIELD(char*, 20)
#define ROW(number) (reinterpret_cast<const ResultRowF119*>(DATA + 0x55C)[number])
#define RECORDS reinterpret_cast<SceneRecordContainerF119*>(reinterpret_cast<char*>(this) + 24)

void MusicScene425C80::RenderList() {
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 quadValue;
        SpriteQuad40CA80 iconQuad;
        RECT region;
        RECT iconRegion;
        int musicIndex;
        BYTE opacity;
        DRAWING->SetDepthMode(0);
        DRAWING->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 34, 256, 98);
        TRANSFORM(quadValue)->BuildQuad(10.0f, 10.0f, 266.0f, 74.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        TRANSFORM(quadValue)->BuildQuad(90.0f, 90.0f, 602.0f, 108.0f);
        SetRect(&iconRegion, 150, 10, 157, 16);
        TRANSFORM(iconQuad)->BuildQuad(80.0f, 100.0f, 87.0f, 106.0f);
        for (musicIndex = 0; musicIndex < 10 && SCENE_FIELD(signed char, 0x3DF) + musicIndex < SCENE_FIELD(signed char, 0x3DC); musicIndex++) {
            if (SCENE_FIELD(signed char, 0x3DF) + musicIndex != SCENE_FIELD(signed char, 0x3DE))
                opacity = 128;
            else
                opacity = 255;
            DrawNumber(80.0f, quadValue.first.y + 1.0f, D3DCOLOR_ARGB(opacity, 255, 255, 255),
                       SCENE_FIELD(signed char, 0x3DF) + 1 + musicIndex, 2);
            QUAD_DRAWING->DrawQuad(1, iconQuad, &iconRegion, D3DCOLOR_ARGB(opacity, 255, 255, 255));
            SetRect(&region, 0, (SCENE_FIELD(signed char, 0x3DF) + musicIndex) * 18, 512,
                    (SCENE_FIELD(signed char, 0x3DF) + musicIndex) * 18 + 18);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), TEXTURE(16));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), TEXTURE(16));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), TEXTURE(16));
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 0, 0, 0), TEXTURE(16));
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, D3DCOLOR_ARGB(opacity, 255, 255, 255), TEXTURE(16));
            TRANSFORM(quadValue)->TranslateQuad(0, 18.0f, 0);
            TRANSFORM(iconQuad)->TranslateQuad(0, 18.0f, 0);
        }
        SetRect(&region, 165, 0, 180, 16);
        TRANSFORM(quadValue)->BuildQuad(30.0f,
            static_cast<float>((SCENE_FIELD(signed char, 0x3DE) - SCENE_FIELD(signed char, 0x3DF)) * 18 + 90), 45.0f,
            static_cast<float>((SCENE_FIELD(signed char, 0x3DE) - SCENE_FIELD(signed char, 0x3DF)) * 18 + 106));
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 32);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(64.0f, 320.0f, 0);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(24));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(24));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(24));
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(24));
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFFFFFFFF, TEXTURE(24));
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(300.0f, 40.0f, 0);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(20));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(20));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(20));
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(20));
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFFFFFFFF, TEXTURE(20));
        SetRect(&region, 0, 16, 120, 32);
        TRANSFORM(quadValue)->BuildQuad(300.0f, 20.0f, 420.0f, 36.0f);
        QUAD_DRAWING->DrawQuad(1, quadValue, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 512);
        TRANSFORM(quadValue)->BuildQuadFromRect(&region);
        TRANSFORM(quadValue)->TranslateQuad(80.0f, 340.0f, 0);
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(12));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(12));
            TRANSFORM(quadValue)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(12));
            TRANSFORM(quadValue)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFF000000, TEXTURE(12));
            TRANSFORM(quadValue)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(quadValue), &region, 0xFFFFFFFF, TEXTURE(12));
        Graphics::EndFrame();
    }
}

void ResultScene430080::RenderRecordPage() {
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 spriteQuad;
        RECT region;
        int rankIndex;
        int entry;
        int rowLimit;
        DRAWING->SetDepthMode(0);
        DRAWING->SetBlendMode(0);
        SetRect(&region, 0, 0, 640, 480);
        TRANSFORM(spriteQuad)->BuildQuadFromRect(&region);
        QUAD_DRAWING->DrawQuad(0, spriteQuad, &region, 0xFFFFFFFF);
        SetRect(&region, 0, 0, 512, 512);
        TRANSFORM(spriteQuad)->BuildQuadFromRect(&region);
        TRANSFORM(spriteQuad)->ScaleQuad(256.0f, 0, 0, -1.0f, 1.0f, 1.0f);
        TRANSFORM(spriteQuad)->TranslateQuad(128.0f, 0, 0);
        reinterpret_cast<SceneQuadDrawingF119*>(SCENE_FIELD(void*, 12))->DrawQuad(0, spriteQuad, &region, 0xFF808080);
        if (SCENE_FIELD(signed char, 0x1C5) == 0) {
            SetRect(&region, 0, 24, 120, 120);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 120.0f, 96.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 72.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 0, 0, 240, 240);
            TRANSFORM(spriteQuad)->BuildQuadFromRect(&region);
            TRANSFORM(spriteQuad)->TranslateQuad(200.0f, 74.0f, 0);
            TRANSFORM(spriteQuad)->TranslateQuad(0.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFFFFFFFF, TEXTURE(16));
            SetRect(&region, 0, 0, 240, 24);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 240.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 20.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 0, SCENE_FIELD(signed char, 0x1C3) * 24, 128,
                    SCENE_FIELD(signed char, 0x1C3) * 24 + 24);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 128.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(320.0f, 20.0f, 0);
            QUAD_DRAWING->DrawQuad(3, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 168, SCENE_FIELD(signed char, 0x1C4) * 24 + 24, 240,
                    SCENE_FIELD(signed char, 0x1C4) * 24 + 48);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 72.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(464.0f, 20.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 24, 168, 48);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 200.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 48, 168, 72);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(160.0f, 200.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 72, 168, 96);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(300.0f, 200.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 120, 96, 168, 120);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 48.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(500.0f, 200.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            for (rankIndex = 0; rankIndex < 10; rankIndex++) {
                DrawRankLabel(80.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, rankIndex + 1);
                DrawNameGlyphs(160.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, ROW(rankIndex).name);
                DrawCounter(330.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, ROW(rankIndex).firstResult, 2);
                SetRect(&region, 228, 40, 247, 60);
                TRANSFORM(spriteQuad)->BuildQuad(325.0f, static_cast<float>(rankIndex * 20 + 230), 344.0f, static_cast<float>(rankIndex * 20 + 250));
                QUAD_DRAWING->DrawQuad(2, spriteQuad, &region, 0xFFFFFFFF);
                DrawCounter(370.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, ROW(rankIndex).secondResult, 2);
                DrawCounter(560.0f, static_cast<float>(rankIndex * 20 + 230), 0xFFFFFFFF, ROW(rankIndex).score, 0);
            }
        } else {
            rowLimit = 10;
            DRAWING->SetBlendMode(2);
            for (entry = 0; entry < rowLimit; entry++) {
                SetRect(&region, 128, 67, 130, 77);
                TRANSFORM(spriteQuad)->BuildQuad(10.0f, static_cast<float>(entry * 32 + 70), 630.0f, static_cast<float>(entry * 32 + 80));
                QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            }
            DRAWING->SetBlendMode(0);
            rowLimit = 0;
            SetRect(&region, 0, 144, 24, 168);
            for (entry = SCENE_FIELD(short, 0x1BC) * 10;
                 entry < SCENE_FIELD(short, 0x1BC) * 10 + 10 && entry < static_cast<int>(RECORDS->Size()); entry++) {
                DrawCounter(540.0f, static_cast<float>(rowLimit * 32 + 63), 0xFF8080FF,
                            reinterpret_cast<const int*>(DATA + 16)[entry], 0);
                if (reinterpret_cast<const BYTE*>(DATA)[0x4C0 + entry]) {
                    TRANSFORM(spriteQuad)->BuildQuad(535.0f, static_cast<float>(rowLimit * 32 + 61), 559.0f, static_cast<float>(rowLimit * 32 + 85));
                    QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
                }
                rowLimit++;
            }
            SetRect(&region, 0, 0, 620, 320);
            TRANSFORM(spriteQuad)->BuildQuad(10.0f, 62.0f, 630.0f, 382.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, 0.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(-1.0f, -1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFF000000, TEXTURE(16));
            TRANSFORM(spriteQuad)->TranslateQuad(0.0f, 1.0f, 0);
            Graphics::DrawTexturedQuad(POSITIONS(spriteQuad), &region, 0xFFFFFFFF, TEXTURE(16));
            SetRect(&region, 0, 120, 240, 144);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 240.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(80.0f, 20.0f, 0);
            QUAD_DRAWING->DrawQuad(1, spriteQuad, &region, 0xFFFFFFFF);
            SetRect(&region, 0, SCENE_FIELD(signed char, 0x1C3) * 24, 128,
                    SCENE_FIELD(signed char, 0x1C3) * 24 + 24);
            TRANSFORM(spriteQuad)->BuildQuad(0, 0, 128.0f, 24.0f);
            TRANSFORM(spriteQuad)->TranslateQuad(320.0f, 20.0f, 0);
            QUAD_DRAWING->DrawQuad(3, spriteQuad, &region, 0xFFFFFFFF);
        }
        Graphics::EndFrame();
    }
}
