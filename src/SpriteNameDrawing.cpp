#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include <mmsystem.h>

// Pointer-only owner/frame/pose views; complete private layouts are unknown.
class SpriteNodeCameraF129 { public: void Render(); };
class SpriteNodeF129 { public: void Render(); };
class NodeDrawingF129 {
public:
    void GetTextureRect(int, RECT*);
    void SetBlendMode(int);
    void SetPixelShaderMode(signed char);
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
    void DrawProjectedQuad(int, const SpriteQuad40CA80&, const RECT*, float, float, float, DWORD);
};
extern float g_NodeCameraX;
extern float g_NodeCameraY;
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define FRAME(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(FIELD(void*, 8)) + (offset)))
#define POSE(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(FRAME(void*, 8)) + (offset)))
#define POSE_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(FRAME(void*, 8)) + (offset))
#define DRAWING reinterpret_cast<NodeDrawingF129*>(FIELD(void*, 4))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
void SpriteNodeCameraF129::Render() {
    RECT textureRect;
    D3DVECTOR spriteOffset;
    float cameraHorizontal;
    DWORD drawColor;
    float cameraY;
    SpriteQuad40CA80 transformedQuad;
    cameraHorizontal = g_NodeCameraX - 160.0f;
    cameraY = g_NodeCameraY;
    DRAWING->GetTextureRect(FRAME(short, 6), &textureRect);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    if (FRAME(void*, 8) != 0) {
        switch (POSE(unsigned char, 0)) {
        case 0: DRAWING->SetBlendMode(0); break;
        case 1: DRAWING->SetBlendMode(2); break;
        case 2: DRAWING->SetBlendMode(3); break;
        }
        TRANSFORM(transformedQuad)->ScaleQuad(FRAME(short, 0), FRAME(short, 2), 0, POSE_FLOAT(12), POSE_FLOAT(16), POSE_FLOAT(20));
        TRANSFORM(transformedQuad)->RotateQuad(FRAME(short, 0), FRAME(short, 2), 0, POSE_FLOAT(24), POSE_FLOAT(28), POSE_FLOAT(32));
        TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, FIELD(signed char, 0x66), 1.0f, 1.0f);
        drawColor = D3DCOLOR_ARGB(POSE(unsigned char, 1), POSE(unsigned char, 2), POSE(unsigned char, 3), POSE(unsigned char, 4));
        spriteOffset.x = POSE(short, 6);
        spriteOffset.y = POSE(short, 8);
        spriteOffset.z = POSE(short, 10);
    } else {
        spriteOffset.x = 0.0f;
        spriteOffset.y = 0.0f;
        spriteOffset.z = 0.0f;
        DRAWING->SetBlendMode(0);
        if (FRAME(unsigned char, 12) != 0)
            TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, FIELD(signed char, 0x66) * 2, 2.0f, 2.0f);
        drawColor = 0xFFFFFFFF;
    }
    if (FIELD(unsigned char, 0x40) != 0) {
        if (FIELD(unsigned char, 0x10) & 0x80) DRAWING->SetPixelShaderMode(0);
        TRANSFORM(transformedQuad)->ScaleQuad(FIELD(signed char, 0x66) * (FRAME(short, 0) + FLOAT(0x34)),
            FRAME(short, 2) - FLOAT(0x38), FLOAT(0x3C), FLOAT(0x1C), FLOAT(0x20), FLOAT(0x24));
        TRANSFORM(transformedQuad)->RotateQuad(FIELD(signed char, 0x66) * (FRAME(short, 0) + FLOAT(0x34)),
            FRAME(short, 2) - FLOAT(0x38), FLOAT(0x3C), FLOAT(0x28), FLOAT(0x2C), FIELD(signed char, 0x66) * FLOAT(0x30));
        spriteOffset.x = FIELD(short, 0x16);
        spriteOffset.y = FIELD(short, 0x18);
        spriteOffset.z = FIELD(short, 0x1A);
        drawColor = D3DCOLOR_ARGB(FIELD(unsigned char, 0x11), FIELD(unsigned char, 0x12), FIELD(unsigned char, 0x13), FIELD(unsigned char, 0x14));
    }
    TRANSFORM(transformedQuad)->TranslateQuad(cameraHorizontal + FLOAT(0x44) - FIELD(signed char, 0x66) * FRAME(short, 0),
        cameraY + 420.0f - FLOAT(0x48) - FRAME(short, 2), 0);
    if (spriteOffset.x != 0 || spriteOffset.y != 0 || spriteOffset.z != 0)
        DRAWING->DrawProjectedQuad(FRAME(short, 6), transformedQuad, &textureRect,
            cameraHorizontal + FLOAT(0x44) + spriteOffset.x, cameraY + 420.0f - FLOAT(0x48) + spriteOffset.y, spriteOffset.z, drawColor);
    else
        DRAWING->DrawQuad(FRAME(short, 6), transformedQuad, &textureRect, drawColor);
    DRAWING->SetPixelShaderMode(-1);
}

void SpriteNodeF129::Render() {
    RECT textureRect;
    D3DVECTOR spriteOffset;
    DWORD drawColor;
    SpriteQuad40CA80 transformedQuad;
    DRAWING->GetTextureRect(FRAME(short, 6), &textureRect);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    if (FRAME(void*, 8) != 0) {
        switch (POSE(unsigned char, 0)) {
        case 0: DRAWING->SetBlendMode(0); break;
        case 1: DRAWING->SetBlendMode(2); break;
        case 2: DRAWING->SetBlendMode(3); break;
        }
        TRANSFORM(transformedQuad)->ScaleQuad(FRAME(short, 0), FRAME(short, 2), 0, POSE_FLOAT(12), POSE_FLOAT(16), POSE_FLOAT(20));
        TRANSFORM(transformedQuad)->RotateQuad(FRAME(short, 0), FRAME(short, 2), 0, POSE_FLOAT(24), POSE_FLOAT(28), POSE_FLOAT(32));
        TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, FIELD(signed char, 0x66), 1.0f, 1.0f);
        drawColor = D3DCOLOR_ARGB(POSE(unsigned char, 1), POSE(unsigned char, 2), POSE(unsigned char, 3), POSE(unsigned char, 4));
        spriteOffset.x = POSE(short, 6);
        spriteOffset.y = POSE(short, 8);
        spriteOffset.z = POSE(short, 10);
    } else {
        spriteOffset.x = 0.0f;
        spriteOffset.y = 0.0f;
        spriteOffset.z = 0.0f;
        DRAWING->SetBlendMode(0);
        if (FRAME(unsigned char, 12) != 0)
            TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, FIELD(signed char, 0x66) * 2, 2.0f, 2.0f);
        drawColor = 0xFFFFFFFF;
    }
    if (FIELD(unsigned char, 0x40) != 0) {
        if (FIELD(unsigned char, 0x10) & 0x80) DRAWING->SetPixelShaderMode(0);
        TRANSFORM(transformedQuad)->ScaleQuad(FIELD(signed char, 0x66) * (FRAME(short, 0) + FLOAT(0x34)),
            FRAME(short, 2) - FLOAT(0x38), FLOAT(0x3C), FLOAT(0x1C), FLOAT(0x20), FLOAT(0x24));
        TRANSFORM(transformedQuad)->RotateQuad(FIELD(signed char, 0x66) * (FRAME(short, 0) + FLOAT(0x34)),
            FRAME(short, 2) - FLOAT(0x38), FLOAT(0x3C), FLOAT(0x28), FLOAT(0x2C), FIELD(signed char, 0x66) * FLOAT(0x30));
        spriteOffset.x = FIELD(short, 0x16);
        spriteOffset.y = FIELD(short, 0x18);
        spriteOffset.z = FIELD(short, 0x1A);
        drawColor = D3DCOLOR_ARGB(FIELD(unsigned char, 0x11), FIELD(unsigned char, 0x12), FIELD(unsigned char, 0x13), FIELD(unsigned char, 0x14));
    }
    TRANSFORM(transformedQuad)->TranslateQuad(FLOAT(0x44) - FIELD(signed char, 0x66) * FRAME(short, 0), FLOAT(0x48) - FRAME(short, 2), 0);
    if (spriteOffset.x != 0 || spriteOffset.y != 0 || spriteOffset.z != 0)
        DRAWING->DrawProjectedQuad(FRAME(short, 6), transformedQuad, &textureRect,
            spriteOffset.x + FLOAT(0x44), spriteOffset.y + FLOAT(0x48), spriteOffset.z, drawColor);
    else
        DRAWING->DrawQuad(FRAME(short, 6), transformedQuad, &textureRect, drawColor);
    DRAWING->SetPixelShaderMode(-1);
}

#undef DRAWING
#undef POSE_FLOAT
#undef POSE
#undef FRAME
#undef FLOAT
#undef FIELD

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
// Only pointer reads are exposed; the profile record and both owners are incomplete.
#define SLOT_ADDRESS(offset) (reinterpret_cast<char*>(FIELD(void*, 0xC)) + (offset) + entry * 16)
#define SLOT(type, offset) (*reinterpret_cast<type*>(SLOT_ADDRESS(offset)))
class NameDrawingF129 {
public:
    void SetDepthMode(int);
    void SetBlendMode(int);
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
};
#define NAME_DRAWING reinterpret_cast<NameDrawingF129*>(FIELD(void*, 8))
class NameEntryPlayerF129 {
public:
    void Render();
    void DrawRank(float, float, DWORD, signed char);
    void DrawName(float, float, DWORD, const signed char*);
    void DrawNumber(float, float, DWORD, int, int);
};
class NameEntrySharedF129 {
public:
    void Render();
    void DrawFilename(float, float, DWORD, const char*);
    void DrawName(float, float, DWORD, const signed char*);
    void DrawNumber(float, float, DWORD, int, int);
};
extern signed char g_NameSharedGlyphs[];
extern signed char g_NameSharedCodeOne;
extern signed char g_NameSharedCodeTwo;
extern signed char g_NameSharedType;
extern signed char g_NameSharedFlag;
extern unsigned char g_NameSharedAlternate;
void NameEntryPlayerF129::Render() {
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 transformedQuad;
        float pulseScale = CameraSineAt0040D940(timeGetTime() / 100.0f) * 0.25f + 1.25f;
        NAME_DRAWING->SetDepthMode(0);
        NAME_DRAWING->SetBlendMode(0);
        RECT textureRect;
        SetRect(&textureRect, 0, 0, 640, 480);
        TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
        NAME_DRAWING->DrawQuad(0, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, 192, 128, 512, 160);
        TRANSFORM(transformedQuad)->BuildQuad(160.0f, 10.0f, 480.0f, 42.0f);
        NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, 0, 80, 500, 160);
        TRANSFORM(transformedQuad)->BuildQuad(70.0f, 300.0f, 570.0f, 380.0f);
        NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, FIELD(short, 0x10) * 19, FIELD(short, 0x12) * 20 + 160,
            FIELD(short, 0x10) * 19 + 19, FIELD(short, 0x12) * 20 + 180);
        TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
        TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
        TRANSFORM(transformedQuad)->TranslateQuad(FIELD(short, 0x10) * 19 + 70, FIELD(short, 0x12) * 20 + 300, 0);
        NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
        for (int entry = 0; entry < 10; ++entry) {
            DWORD rowColor;
            if (entry != FIELD(signed char, 0x120)) rowColor = 0xFF808080;
            else rowColor = 0xFFFFFFFF;
            DrawRank(80.0f, entry * 20 + 80, rowColor, entry + 1);
            DrawName(160.0f, entry * 20 + 80, rowColor, reinterpret_cast<const signed char*>(SLOT_ADDRESS(0x55C)));
            DrawNumber(330.0f, entry * 20 + 80, rowColor, SLOT(signed char, 0x564), 2);
            SetRect(&textureRect, 228, 40, 247, 60);
            TRANSFORM(transformedQuad)->BuildQuad(325.0f, entry * 20 + 80, 344.0f, entry * 20 + 100);
            NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, rowColor);
            DrawNumber(370.0f, entry * 20 + 80, rowColor, SLOT(signed char, 0x565), 2);
            DrawNumber(560.0f, entry * 20 + 80, rowColor, SLOT(int, 0x568), 0);
        }
        if (FIELD(short, 0x14) < 8 && FIELD(short, 0x10) + FIELD(short, 0x12) * 26 != 92) {
            SetRect(&textureRect, FIELD(short, 0x10) * 19, FIELD(short, 0x12) * 20 + 160,
                FIELD(short, 0x10) * 19 + 19, FIELD(short, 0x12) * 20 + 180);
            TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
            TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
            TRANSFORM(transformedQuad)->TranslateQuad(FIELD(short, 0x14) * 14 + 160, FIELD(signed char, 0x120) * 20 + 80, 0);
            NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
        }
        Graphics::EndFrame();
    }
}

void NameEntrySharedF129::Render() {
    if (Graphics::BeginFrameValueAt00402660()) {
        SpriteQuad40CA80 transformedQuad;
        float pulseScale = CameraSineAt0040D940(timeGetTime() / 100.0f) * 0.25f + 1.25f;
        NAME_DRAWING->SetDepthMode(0);
        NAME_DRAWING->SetBlendMode(0);
        RECT textureRect;
        SetRect(&textureRect, 0, 0, 640, 480);
        TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
        NAME_DRAWING->DrawQuad(0, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, 192, 160, 512, 192);
        TRANSFORM(transformedQuad)->BuildQuad(160.0f, 20.0f, 480.0f, 52.0f);
        NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        if (FIELD(signed char, 0xC) == 0) {
            SetRect(&textureRect, 0, 80, 500, 160);
            TRANSFORM(transformedQuad)->BuildQuad(70.0f, 300.0f, 570.0f, 380.0f);
            NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            SetRect(&textureRect, FIELD(short, 0xE) * 19, FIELD(short, 0x10) * 20 + 160,
                FIELD(short, 0xE) * 19 + 19, FIELD(short, 0x10) * 20 + 180);
            TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
            TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
            TRANSFORM(transformedQuad)->TranslateQuad(FIELD(short, 0xE) * 19 + 70, FIELD(short, 0x10) * 20 + 300, 0);
            NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            SetRect(&textureRect, 0, 0, 512, 20);
            TRANSFORM(transformedQuad)->BuildQuad(64.0f, 100.0f, 576.0f, 120.0f);
            NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
            DrawFilename(50.0f, 130.0f, 0xFFFFFFFF, reinterpret_cast<const char*>(this) + 0x1C);
            DrawName(160.0f, 130.0f, 0xFFFFFFFF, g_NameSharedGlyphs);
            if (FIELD(short, 0x12) < 8 && FIELD(short, 0xE) + FIELD(short, 0x10) * 26 != 92) {
                SetRect(&textureRect, FIELD(short, 0xE) * 19, FIELD(short, 0x10) * 20 + 160,
                    FIELD(short, 0xE) * 19 + 19, FIELD(short, 0x10) * 20 + 180);
                TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
                TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
                TRANSFORM(transformedQuad)->TranslateQuad(FIELD(short, 0x12) * 14 + 160, 130.0f, 0);
                NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            }
            DrawNumber(330.0f, 130.0f, 0xFFFFFFFF, g_NameSharedCodeOne, 2);
            SetRect(&textureRect, 228, 40, 247, 60);
            TRANSFORM(transformedQuad)->BuildQuad(325.0f, 130.0f, 344.0f, 150.0f);
            NAME_DRAWING->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            DrawNumber(370.0f, 130.0f, 0xFFFFFFFF, g_NameSharedCodeTwo, 2);
            if (g_NameSharedFlag == 0) {
                SetRect(&textureRect, 0, g_NameSharedAlternate * 20 + 20, 100, g_NameSharedAlternate * 20 + 40);
                TRANSFORM(transformedQuad)->BuildQuad(380.0f, 136.0f, 480.0f, 150.0f);
                TRANSFORM(transformedQuad)->TranslateQuad(36.0f, 8.0f, 0);
                NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFB0B0B0);
            }
            SetRect(&textureRect, 0, g_NameSharedType * 20 + 20, 100, g_NameSharedType * 20 + 40);
            TRANSFORM(transformedQuad)->BuildQuad(380.0f, 130.0f, 480.0f, 150.0f);
            NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
            SetRect(&textureRect, 100, g_NameSharedFlag * 20 + 20, 180, g_NameSharedFlag * 20 + 40);
            TRANSFORM(transformedQuad)->BuildQuad(500.0f, 130.0f, 580.0f, 150.0f);
            NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        } else {
            SetRect(&textureRect, 200, 20, 460, 60);
            TRANSFORM(transformedQuad)->BuildQuad(190.0f, 200.0f, 450.0f, 240.0f);
            NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
            if (FIELD(short, 0x14) == 0) SetRect(&textureRect, 320, 192, 448, 224);
            else SetRect(&textureRect, 192, 192, 320, 224);
            TRANSFORM(transformedQuad)->BuildQuad(256.0f, 280.0f, 384.0f, 312.0f);
            NAME_DRAWING->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        }
        Graphics::EndFrame();
    }
}
#undef NAME_DRAWING
#undef SLOT
#undef SLOT_ADDRESS
#undef FIELD
#undef TRANSFORM
