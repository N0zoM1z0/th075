#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "GameLeafHelpers.hpp"

// Pointer-only private interfaces; original identities/layouts are unknown.
class FighterRender453F70 { public: void Render(); };
class FighterDrawingF126 {
public:
    void GetTextureRect(int, RECT*);
    void SetBlendMode(int);
    void SetPixelShaderMode(signed char);
    void DrawQuad(int, const SpriteQuad40CA80&, const RECT*, DWORD);
    void DrawProjectedQuad(int, const SpriteQuad40CA80&, const RECT*, float, float, float, DWORD);
};
class FighterHistoryF126 {
public:
    void AppendElement(short, float, float, SpriteQuad40CA80, D3DVECTOR, DWORD, signed char);
    void RemoveFrontIfPresent();
};
extern float g_RenderCameraX;
extern float g_RenderCameraY;
extern unsigned char g_RenderByte0067161C;
extern unsigned char g_RenderByte0066C237;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + (offset))
#define FRAME(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(FIELD(void*, 0x74)) + (offset)))
#define POSE(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(FRAME(void*, 8)) + (offset)))
#define POSE_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<char*>(FRAME(void*, 8)) + (offset))
#define DRAWING reinterpret_cast<FighterDrawingF126*>(FIELD(void*, 4))
#define HISTORY reinterpret_cast<FighterHistoryF126*>(FIELD(void*, 0x480))
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

// The history call copies a complete quad and SDK vector by value.
void FighterRender453F70::Render() {
    RECT textureRect;
    D3DVECTOR spriteOffset;
    float cameraHorizontal;
    DWORD drawColor;
    float cameraY;
    SpriteQuad40CA80 transformedQuad;
    cameraHorizontal = g_RenderCameraX - 160.0f;
    cameraY = g_RenderCameraY;
    if (FIELD(short, 0x82) > 0 && reinterpret_cast<FighterState*>(this)->IsState50To149())
        cameraHorizontal += 2 - (FIELD(short, 0x82) % 2) * 4;
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
    TRANSFORM(transformedQuad)->TranslateQuad(FLOAT(0x44) - FIELD(signed char, 0x66) * FRAME(short, 0), -FLOAT(0x48) - FRAME(short, 2), 0);
    if (g_RenderByte0067161C == 0) {
        HISTORY->AppendElement(FRAME(short, 6), FLOAT(0x44), FLOAT(0x48), transformedQuad, spriteOffset, drawColor, 1);
        if (g_RenderByte0066C237 != 0 && FIELD(int, 0x47C) <= 0) {
            HISTORY->RemoveFrontIfPresent();
            HISTORY->RemoveFrontIfPresent();
        }
    }
    TRANSFORM(transformedQuad)->TranslateQuad(cameraHorizontal, cameraY + 420.0f, 0);
    if (spriteOffset.x != 0.0f || spriteOffset.y != 0.0f || spriteOffset.z != 0.0f)
        DRAWING->DrawProjectedQuad(FRAME(short, 6), transformedQuad, &textureRect, spriteOffset.x, spriteOffset.y, spriteOffset.z, drawColor);
    else
        DRAWING->DrawQuad(FRAME(short, 6), transformedQuad, &textureRect, drawColor);
    if (FIELD(signed char, 0x484) > 0) {
        DRAWING->SetBlendMode(2);
        if (spriteOffset.x != 0.0f || spriteOffset.y != 0.0f || spriteOffset.z != 0.0f)
            DRAWING->DrawProjectedQuad(FRAME(short, 6), transformedQuad, &textureRect, spriteOffset.x, spriteOffset.y, spriteOffset.z, drawColor);
        else
            DRAWING->DrawQuad(FRAME(short, 6), transformedQuad, &textureRect, drawColor);
    }
    DRAWING->SetPixelShaderMode(-1);
}

#undef TRANSFORM
#undef HISTORY
#undef DRAWING
#undef POSE_FLOAT
#undef POSE
#undef FRAME
#undef FLOAT
#undef FIELD

// C sine entry and pointer-only drawing view; no private owner allocation.
extern "C" double __cdecl sin(double);
class EffectPattern44E930 { public: void Render(); };
class EffectDrawingF126 {
public:
    void SetDepthEnabled(int);
    void SetBlendMode(int);
    void SetFilterMode(int);
    void DrawSprite(int, float, float, DWORD, float, float, float, float, unsigned char);
    void DrawProjectedQuad(int, const SpriteQuad40CA80&, const RECT*, float, float, float, DWORD);
};
#define EFFECT_INT(offset) (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + (offset)))
#define EFFECT_DRAWING reinterpret_cast<EffectDrawingF126*>(reinterpret_cast<char*>(this) + 0x18)
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
// Keep double arithmetic until the native float arguments or integer truncations.
void EffectPattern44E930::Render() {
    RECT rectangle;
    int spriteIndexThird;
    int firstImageIndex;
    int verticalShiftThree;
    int fourthImageIndex;
    int oscillationOne;
    int stripCount;
    int frameIndexSecond;
    int cameraHorizontal;
    int verticalWaveFour;
    int cameraY;
    int verticalWaveTwo;
    cameraHorizontal = static_cast<int>(g_RenderCameraX + 160.0f);
    cameraY = static_cast<int>(g_RenderCameraY);
    oscillationOne = static_cast<int>(sin(EFFECT_INT(0x70) * 0.1 + 1.0) * 5.0);
    verticalWaveTwo = static_cast<int>(sin(EFFECT_INT(0x70) * 0.1 + 2.0) * 4.0);
    verticalShiftThree = static_cast<int>(sin(EFFECT_INT(0x70) * 0.1 + 3.0) * 5.0);
    verticalWaveFour = static_cast<int>(sin(EFFECT_INT(0x70) * 0.1 + 4.0) * 6.0);
    firstImageIndex = EFFECT_INT(0x6C) / 3 + 4;
    frameIndexSecond = firstImageIndex + 3;
    spriteIndexThird = firstImageIndex + 7;
    fourthImageIndex = firstImageIndex + 11;
    if (firstImageIndex + 3 >= 18) frameIndexSecond = firstImageIndex - 11;
    if (firstImageIndex + 7 >= 18) spriteIndexThird = firstImageIndex - 7;
    if (firstImageIndex + 11 >= 18) fourthImageIndex = firstImageIndex - 3;
    EFFECT_DRAWING->SetDepthEnabled(0);
    EFFECT_DRAWING->SetBlendMode(0);
    EFFECT_DRAWING->DrawSprite(2, cameraHorizontal * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(1, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 150.0, 0xFFFFFFFF, 700.0f, 200.0f, 1.0f, 0.0f, 0);
    stripCount = static_cast<int>((1536.0 - EFFECT_INT(0x68) * 0.4) / 384.0);
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = stripCount * 128;
    rectangle.bottom = 128;
    EFFECT_DRAWING->SetFilterMode(2);
    SpriteQuad40CA80 spriteQuadFirst(0, 0, stripCount * 128 * 3, 256.0f);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal * 0.75 + EFFECT_INT(0x68) * 0.4, cameraY * 0.75 + 160.0, 0);
    EFFECT_DRAWING->DrawProjectedQuad(3, spriteQuadFirst, &rectangle, 320.0f, 240.0f, 1500.0f, 0x7FFFFFFF);
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = (5 - stripCount) * 128;
    rectangle.bottom = 128;
    SpriteQuad40CA80 secondStrip(0, 0, (5 - stripCount) * 128 * 3, 256.0f);
    TRANSFORM(secondStrip)->TranslateQuad(cameraHorizontal * 0.75 + EFFECT_INT(0x68) * 0.4 - (5 - stripCount) * 128 * 3, cameraY * 0.75 + 160.0, 0);
    EFFECT_DRAWING->DrawProjectedQuad(3, secondStrip, &rectangle, 320.0f, 240.0f, 1500.0f, 0x7FFFFFFF);
    EFFECT_DRAWING->SetFilterMode(1);
    EFFECT_DRAWING->SetBlendMode(2);
    EFFECT_DRAWING->SetFilterMode(2);
    EFFECT_DRAWING->DrawSprite(frameIndexSecond, cameraHorizontal - 260, cameraY + 200 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 0.6f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(spriteIndexThird, cameraHorizontal + 680, cameraY + 170 + verticalShiftThree, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    EFFECT_DRAWING->SetFilterMode(1);
    EFFECT_DRAWING->SetBlendMode(0);
    EFFECT_DRAWING->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0.0f, 0);
    EFFECT_DRAWING->SetBlendMode(2);
    EFFECT_DRAWING->SetFilterMode(2);
    EFFECT_DRAWING->DrawSprite(fourthImageIndex, cameraHorizontal - 250, cameraY + 240 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 1.1f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(spriteIndexThird, cameraHorizontal - 150, cameraY + 200 + verticalShiftThree, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(firstImageIndex, cameraHorizontal + 150, cameraY + 200 + oscillationOne, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(spriteIndexThird, cameraHorizontal + 360, cameraY + 190 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 0.8f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(firstImageIndex, cameraHorizontal + 450, cameraY + 200 + oscillationOne, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(frameIndexSecond, cameraHorizontal + 650, cameraY + 230 + verticalWaveTwo, 0x87FFFFFF, 32.0f, 64.0f, 1.3f, 0.0f, 0);
    EFFECT_DRAWING->DrawSprite(spriteIndexThird, cameraHorizontal + 760, cameraY + 200 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 0.8f, 0.0f, 0);
    EFFECT_DRAWING->SetFilterMode(1);
    EFFECT_DRAWING->SetBlendMode(0);
}
#undef TRANSFORM
#undef EFFECT_DRAWING
#undef EFFECT_INT
