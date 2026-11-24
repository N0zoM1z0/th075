#include "BattleSessionState.hpp"
#include "TextureManagerF198.hpp"
#include "Fighter.hpp"
#include "SpriteDraw40CA80.hpp"
#include "SpriteTransform.hpp"
#include "GameLeafHelpers.hpp"

class FighterDrawingF126 {
public:
};
class FighterHistoryF126 {
public:
    void AppendElement(short, float, float, SpriteQuad40CA80, D3DVECTOR, DWORD, signed char);
    void RemoveFrontIfPresent();
};
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
extern unsigned char g_RenderByte0067161C;

#define DRAWING reinterpret_cast<FighterDrawingF126*>(drawing)
#define HISTORY reinterpret_cast<FighterHistoryF126*>(field480)
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))

// The history call copies a complete quad and SDK vector by value.
void Fighter::Render() {
    RECT textureRect;
    D3DVECTOR spriteOffset;
    float cameraHorizontal;
    DWORD drawColor;
    float cameraY;
    SpriteQuad40CA80 transformedQuad;
    cameraHorizontal = g_CombatViewOffsetX - 160.0f;
    cameraY = g_CombatViewOffsetY;
    if (field082 > 0 && reinterpret_cast<Fighter*>(this)->IsState50To149())
        cameraHorizontal += 2 - (field082 % 2) * 4;
    reinterpret_cast<TextureManagerF198*>(DRAWING)->GetTextureRect(frameInfo->textureIndex, &textureRect);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    if (frameInfo->pose != 0) {
        switch (frameInfo->pose->blendMode) {
        case 0: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0); break;
        case 1: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(2); break;
        case 2: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(3); break;
        }
        TRANSFORM(transformedQuad)->ScaleQuad(frameInfo->originX, frameInfo->originY, 0, frameInfo->pose->scaleX, frameInfo->pose->scaleY, frameInfo->pose->scaleZ);
        TRANSFORM(transformedQuad)->RotateQuad(frameInfo->originX, frameInfo->originY, 0, frameInfo->pose->rotationX, frameInfo->pose->rotationY, frameInfo->pose->rotationZ);
        TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, facing, 1.0f, 1.0f);
        drawColor = D3DCOLOR_ARGB(frameInfo->pose->color[0], frameInfo->pose->color[1], frameInfo->pose->color[2], frameInfo->pose->color[3]);
        spriteOffset.x = frameInfo->pose->offsetX;
        spriteOffset.y = frameInfo->pose->offsetY;
        spriteOffset.z = frameInfo->pose->offsetZ;
    } else {
        spriteOffset.x = 0.0f;
        spriteOffset.y = 0.0f;
        spriteOffset.z = 0.0f;
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0);
        if (frameInfo->field0C != 0)
            TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, facing * 2, 2.0f, 2.0f);
        drawColor = 0xFFFFFFFF;
    }
    if (field040 != 0) {
        if (field010 & 0x80) reinterpret_cast<TextureManagerF198*>(DRAWING)->SetPixelShaderMode(0);
        TRANSFORM(transformedQuad)->ScaleQuad(facing * ((frameInfo->originX) + pivotX),
            (frameInfo->originY) - pivotY, pivotZ, scaleX, scaleY, scaleZ);
        TRANSFORM(transformedQuad)->RotateQuad(facing * ((frameInfo->originX) + pivotX),
            (frameInfo->originY) - pivotY, pivotZ, rotationX, rotationY, facing * rotationZ);
        spriteOffset.x = field016;
        spriteOffset.y = field018;
        spriteOffset.z = field01A;
        drawColor = D3DCOLOR_ARGB(color[0], color[1], color[2], color[3]);
    }
    TRANSFORM(transformedQuad)->TranslateQuad(x - facing * (frameInfo->originX), -y - (frameInfo->originY), 0);
    if (g_RenderByte0067161C == 0) {
        HISTORY->AppendElement(frameInfo->textureIndex, x, y, transformedQuad, spriteOffset, drawColor, 1);
        if (g_FramePresentToggle != 0 && field47C <= 0) {
            HISTORY->RemoveFrontIfPresent();
            HISTORY->RemoveFrontIfPresent();
        }
    }
    TRANSFORM(transformedQuad)->TranslateQuad(cameraHorizontal, cameraY + 420.0f, 0);
    if (spriteOffset.x != 0.0f || spriteOffset.y != 0.0f || spriteOffset.z != 0.0f)
        reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawProjectedQuad(frameInfo->textureIndex, transformedQuad, &textureRect, spriteOffset.x, spriteOffset.y, spriteOffset.z, drawColor);
    else
        reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawQuad(frameInfo->textureIndex, transformedQuad, &textureRect, drawColor);
    if (field484 > 0) {
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(2);
        if (spriteOffset.x != 0.0f || spriteOffset.y != 0.0f || spriteOffset.z != 0.0f)
            reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawProjectedQuad(frameInfo->textureIndex, transformedQuad, &textureRect, spriteOffset.x, spriteOffset.y, spriteOffset.z, drawColor);
        else
            reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawQuad(frameInfo->textureIndex, transformedQuad, &textureRect, drawColor);
    }
    reinterpret_cast<TextureManagerF198*>(DRAWING)->SetPixelShaderMode(-1);
}

#undef TRANSFORM
#undef HISTORY
#undef DRAWING

// C sine entry and pointer-only drawing view; no private owner allocation.
extern "C" double __cdecl sin(double);
class EffectPattern44E930 { public: void Render(); };
class EffectDrawingF126 {
public:
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
    cameraHorizontal = static_cast<int>(g_CombatViewOffsetX + 160.0f);
    cameraY = static_cast<int>(g_CombatViewOffsetY);
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
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetDepthMode(0);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetBlendMode(0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(2, cameraHorizontal * 0.6 + 320.0, cameraY * 0.6 + 200.0, 0xFFFFFFFF, 768.0f, 384.0f, 3.0f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(1, cameraHorizontal * 0.75 + 320.0, cameraY * 0.75 + 150.0, 0xFFFFFFFF, 700.0f, 200.0f, 1.0f, 0.0f, 0);
    stripCount = static_cast<int>((1536.0 - EFFECT_INT(0x68) * 0.4) / 384.0);
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = stripCount * 128;
    rectangle.bottom = 128;
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetTextureFilter(2);
    SpriteQuad40CA80 spriteQuadFirst(0, 0, stripCount * 128 * 3, 256.0f);
    TRANSFORM(spriteQuadFirst)->TranslateQuad(cameraHorizontal * 0.75 + EFFECT_INT(0x68) * 0.4, cameraY * 0.75 + 160.0, 0);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->DrawProjectedQuad(3, spriteQuadFirst, &rectangle, 320.0f, 240.0f, 1500.0f, 0x7FFFFFFF);
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = (5 - stripCount) * 128;
    rectangle.bottom = 128;
    SpriteQuad40CA80 secondStrip(0, 0, (5 - stripCount) * 128 * 3, 256.0f);
    TRANSFORM(secondStrip)->TranslateQuad(cameraHorizontal * 0.75 + EFFECT_INT(0x68) * 0.4 - (5 - stripCount) * 128 * 3, cameraY * 0.75 + 160.0, 0);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->DrawProjectedQuad(3, secondStrip, &rectangle, 320.0f, 240.0f, 1500.0f, 0x7FFFFFFF);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetTextureFilter(1);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetBlendMode(2);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetTextureFilter(2);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(frameIndexSecond, cameraHorizontal - 260, cameraY + 200 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 0.6f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(spriteIndexThird, cameraHorizontal + 680, cameraY + 170 + verticalShiftThree, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetTextureFilter(1);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetBlendMode(0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(0, cameraHorizontal + 320, cameraY + 240, 0xFFFFFFFF, 700.0f, 620.0f, 1.0f, 0.0f, 0);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetBlendMode(2);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetTextureFilter(2);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(fourthImageIndex, cameraHorizontal - 250, cameraY + 240 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 1.1f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(spriteIndexThird, cameraHorizontal - 150, cameraY + 200 + verticalShiftThree, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(firstImageIndex, cameraHorizontal + 150, cameraY + 200 + oscillationOne, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(spriteIndexThird, cameraHorizontal + 360, cameraY + 190 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 0.8f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(firstImageIndex, cameraHorizontal + 450, cameraY + 200 + oscillationOne, 0x87FFFFFF, 32.0f, 64.0f, 1.0f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(frameIndexSecond, cameraHorizontal + 650, cameraY + 230 + verticalWaveTwo, 0x87FFFFFF, 32.0f, 64.0f, 1.3f, 0.0f, 0);
    reinterpret_cast<TimelineDrawing438D00*>(EFFECT_DRAWING)->DrawSprite(spriteIndexThird, cameraHorizontal + 760, cameraY + 200 + verticalWaveFour, 0x87FFFFFF, 32.0f, 64.0f, 0.8f, 0.0f, 0);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetTextureFilter(1);
    reinterpret_cast<TextureManagerF198*>(EFFECT_DRAWING)->SetBlendMode(0);
}
#undef TRANSFORM
#undef EFFECT_DRAWING
#undef EFFECT_INT
