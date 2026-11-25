#include "ui/NameEntryScenes.hpp"
#include "engine/GameProgress.hpp"
#include "replay/ReplayRecords.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "characters/CharacterObject.hpp"
#include "graphics/SpriteDraw40CA80.hpp"
#include "graphics/SpriteTransform.hpp"
#include <mmsystem.h>

// Pointer-only owner/frame/pose views; complete private layouts are unknown.
class NodeDrawingF129 {
public:
};
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
#define DRAWING reinterpret_cast<NodeDrawingF129*>(drawing)
#define TRANSFORM(value) reinterpret_cast<SpriteTransform*>(&(value))
// Draw the actor relative to the battle camera.
void ActorRenderingBase::Render() {
    RECT textureRect;
    D3DVECTOR spriteOffset;
    float cameraHorizontal;
    DWORD drawColor;
    float cameraY;
    SpriteQuad40CA80 transformedQuad;
    cameraHorizontal = g_CombatViewOffsetX - 160.0f;
    cameraY = g_CombatViewOffsetY;
    reinterpret_cast<TextureManagerF198*>(DRAWING)->GetTextureRect(drawFrame->textureIndex, &textureRect);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    if (drawFrame->pose != 0) {
        switch (drawFrame->pose->blendMode) {
        case 0: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0); break;
        case 1: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(2); break;
        case 2: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(3); break;
        }
        TRANSFORM(transformedQuad)->ScaleQuad(drawFrame->originX, drawFrame->originY, 0, drawFrame->pose->scaleX, drawFrame->pose->scaleY, drawFrame->pose->scaleZ);
        TRANSFORM(transformedQuad)->RotateQuad(drawFrame->originX, drawFrame->originY, 0, drawFrame->pose->rotationX, drawFrame->pose->rotationY, drawFrame->pose->rotationZ);
        TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, facing, 1.0f, 1.0f);
        drawColor = D3DCOLOR_ARGB(drawFrame->pose->color[0], drawFrame->pose->color[1], drawFrame->pose->color[2], drawFrame->pose->color[3]);
        spriteOffset.x = drawFrame->pose->offsetX;
        spriteOffset.y = drawFrame->pose->offsetY;
        spriteOffset.z = drawFrame->pose->offsetZ;
    } else {
        spriteOffset.x = 0.0f;
        spriteOffset.y = 0.0f;
        spriteOffset.z = 0.0f;
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0);
        if (drawFrame->doubleScale != 0)
            TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, (facing) * 2, 2.0f, 2.0f);
        drawColor = 0xFFFFFFFF;
    }
    if (field040 != 0) {
        if (field010 & 0x80) reinterpret_cast<TextureManagerF198*>(DRAWING)->SetPixelShaderMode(0);
        TRANSFORM(transformedQuad)->ScaleQuad((facing) * ((drawFrame->originX) + pivotX),
            (drawFrame->originY) - pivotY, pivotZ, scaleX, scaleY, scaleZ);
        TRANSFORM(transformedQuad)->RotateQuad((facing) * ((drawFrame->originX) + pivotX),
            (drawFrame->originY) - pivotY, pivotZ, rotationX, rotationY, (facing) * rotationZ);
        spriteOffset.x = field016;
        spriteOffset.y = field018;
        spriteOffset.z = field01A;
        drawColor = D3DCOLOR_ARGB(color[0], color[1], color[2], color[3]);
    }
    TRANSFORM(transformedQuad)->TranslateQuad(cameraHorizontal + x - (facing) * (drawFrame->originX),
        cameraY + 420.0f - y - (drawFrame->originY), 0);
    if (spriteOffset.x != 0 || spriteOffset.y != 0 || spriteOffset.z != 0)
        reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawProjectedQuad(drawFrame->textureIndex, transformedQuad, &textureRect,
            cameraHorizontal + x + spriteOffset.x, cameraY + 420.0f - y + spriteOffset.y, spriteOffset.z, drawColor);
    else
        reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawQuad(drawFrame->textureIndex, transformedQuad, &textureRect, drawColor);
    reinterpret_cast<TextureManagerF198*>(DRAWING)->SetPixelShaderMode(-1);
}

// Actor vtable slot 3.
void ActorRenderingBase::RenderNode() {
    RECT textureRect;
    D3DVECTOR spriteOffset;
    DWORD drawColor;
    SpriteQuad40CA80 transformedQuad;
    reinterpret_cast<TextureManagerF198*>(DRAWING)->GetTextureRect(drawFrame->textureIndex, &textureRect);
    TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
    if (drawFrame->pose != 0) {
        switch (drawFrame->pose->blendMode) {
        case 0: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0); break;
        case 1: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(2); break;
        case 2: reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(3); break;
        }
        TRANSFORM(transformedQuad)->ScaleQuad(drawFrame->originX, drawFrame->originY, 0, drawFrame->pose->scaleX, drawFrame->pose->scaleY, drawFrame->pose->scaleZ);
        TRANSFORM(transformedQuad)->RotateQuad(drawFrame->originX, drawFrame->originY, 0, drawFrame->pose->rotationX, drawFrame->pose->rotationY, drawFrame->pose->rotationZ);
        TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, facing, 1.0f, 1.0f);
        drawColor = D3DCOLOR_ARGB(drawFrame->pose->color[0], drawFrame->pose->color[1], drawFrame->pose->color[2], drawFrame->pose->color[3]);
        spriteOffset.x = drawFrame->pose->offsetX;
        spriteOffset.y = drawFrame->pose->offsetY;
        spriteOffset.z = drawFrame->pose->offsetZ;
    } else {
        spriteOffset.x = 0.0f;
        spriteOffset.y = 0.0f;
        spriteOffset.z = 0.0f;
        reinterpret_cast<TextureManagerF198*>(DRAWING)->SetBlendMode(0);
        if (drawFrame->doubleScale != 0)
            TRANSFORM(transformedQuad)->ScaleQuad(0, 0, 0, (facing) * 2, 2.0f, 2.0f);
        drawColor = 0xFFFFFFFF;
    }
    if (field040 != 0) {
        if (field010 & 0x80) reinterpret_cast<TextureManagerF198*>(DRAWING)->SetPixelShaderMode(0);
        TRANSFORM(transformedQuad)->ScaleQuad((facing) * ((drawFrame->originX) + pivotX),
            (drawFrame->originY) - pivotY, pivotZ, scaleX, scaleY, scaleZ);
        TRANSFORM(transformedQuad)->RotateQuad((facing) * ((drawFrame->originX) + pivotX),
            (drawFrame->originY) - pivotY, pivotZ, rotationX, rotationY, (facing) * rotationZ);
        spriteOffset.x = field016;
        spriteOffset.y = field018;
        spriteOffset.z = field01A;
        drawColor = D3DCOLOR_ARGB(color[0], color[1], color[2], color[3]);
    }
    TRANSFORM(transformedQuad)->TranslateQuad(x - (facing) * (drawFrame->originX), y - (drawFrame->originY), 0);
    if (spriteOffset.x != 0 || spriteOffset.y != 0 || spriteOffset.z != 0)
        reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawProjectedQuad(drawFrame->textureIndex, transformedQuad, &textureRect,
            spriteOffset.x + x, spriteOffset.y + y, spriteOffset.z, drawColor);
    else
        reinterpret_cast<TextureManagerF198*>(DRAWING)->DrawQuad(drawFrame->textureIndex, transformedQuad, &textureRect, drawColor);
    reinterpret_cast<TextureManagerF198*>(DRAWING)->SetPixelShaderMode(-1);
}

#undef DRAWING

void PlayerNameEntryScene::Render() {
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 transformedQuad;
        float pulseScale = CameraSineAt0040D940(timeGetTime() / 100.0f) * 0.25f + 1.25f;
        texture->SetDepthMode(0);
        texture->SetBlendMode(0);
        RECT textureRect;
        SetRect(&textureRect, 0, 0, 640, 480);
        TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
        texture->DrawQuad(0, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, 192, 128, 512, 160);
        TRANSFORM(transformedQuad)->BuildQuad(160.0f, 10.0f, 480.0f, 42.0f);
        texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, 0, 80, 500, 160);
        TRANSFORM(transformedQuad)->BuildQuad(70.0f, 300.0f, 570.0f, 380.0f);
        texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, glyphColumn * 19, glyphRow * 20 + 160,
            glyphColumn * 19 + 19, glyphRow * 20 + 180);
        TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
        TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
        TRANSFORM(transformedQuad)->TranslateQuad(glyphColumn * 19 + 70, glyphRow * 20 + 300, 0);
        texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
        for (int entry = 0; entry < 10; ++entry) {
            DWORD rowColor;
            if (entry != rank) rowColor = 0xFF808080;
            else rowColor = 0xFFFFFFFF;
            DrawRankLabel(80.0f, entry * 20 + 80, rowColor, entry + 1);
            DrawNameGlyphs(160.0f, entry * 20 + 80, rowColor, reinterpret_cast<const signed char*>(selectedRecord->scores[entry].name));
            DrawNumber(330.0f, entry * 20 + 80, rowColor, static_cast<signed char>(selectedRecord->scores[entry].month), 2);
            SetRect(&textureRect, 228, 40, 247, 60);
            TRANSFORM(transformedQuad)->BuildQuad(325.0f, entry * 20 + 80, 344.0f, entry * 20 + 100);
            texture->DrawQuad(2, transformedQuad, &textureRect, rowColor);
            DrawNumber(370.0f, entry * 20 + 80, rowColor, static_cast<signed char>(selectedRecord->scores[entry].day), 2);
            DrawNumber(560.0f, entry * 20 + 80, rowColor, selectedRecord->scores[entry].score, 0);
        }
        if (nameCursor < 8 && glyphColumn + glyphRow * 26 != 92) {
            SetRect(&textureRect, glyphColumn * 19, glyphRow * 20 + 160,
                glyphColumn * 19 + 19, glyphRow * 20 + 180);
            TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
            TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
            TRANSFORM(transformedQuad)->TranslateQuad(nameCursor * 14 + 160, rank * 20 + 80, 0);
            texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
        }
        Graphics::EndFrame();
    }
}

void SharedNameEntryScene::Render() {
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 transformedQuad;
        float pulseScale = CameraSineAt0040D940(timeGetTime() / 100.0f) * 0.25f + 1.25f;
        texture->SetDepthMode(0);
        texture->SetBlendMode(0);
        RECT textureRect;
        SetRect(&textureRect, 0, 0, 640, 480);
        TRANSFORM(transformedQuad)->BuildQuadFromRect(&textureRect);
        texture->DrawQuad(0, transformedQuad, &textureRect, 0xFFFFFFFF);
        SetRect(&textureRect, 192, 160, 512, 192);
        TRANSFORM(transformedQuad)->BuildQuad(160.0f, 20.0f, 480.0f, 52.0f);
        texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        if (confirmingCancel == 0) {
            SetRect(&textureRect, 0, 80, 500, 160);
            TRANSFORM(transformedQuad)->BuildQuad(70.0f, 300.0f, 570.0f, 380.0f);
            texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            SetRect(&textureRect, glyphColumn * 19, glyphRow * 20 + 160,
                glyphColumn * 19 + 19, glyphRow * 20 + 180);
            TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
            TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
            TRANSFORM(transformedQuad)->TranslateQuad(glyphColumn * 19 + 70, glyphRow * 20 + 300, 0);
            texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            SetRect(&textureRect, 0, 0, 512, 20);
            TRANSFORM(transformedQuad)->BuildQuad(64.0f, 100.0f, 576.0f, 120.0f);
            texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
            DrawSaveFilename(50.0f, 130.0f, 0xFFFFFFFF, replayPath);
            DrawNameGlyphs(160.0f, 130.0f, 0xFFFFFFFF, reinterpret_cast<signed char*>(g_ReplayRecords.fileHeader.playerName));
            if (nameCursor < 8 && glyphColumn + glyphRow * 26 != 92) {
                SetRect(&textureRect, glyphColumn * 19, glyphRow * 20 + 160,
                    glyphColumn * 19 + 19, glyphRow * 20 + 180);
                TRANSFORM(transformedQuad)->BuildQuad(0, 0, 19.0f, 20.0f);
                TRANSFORM(transformedQuad)->ScaleQuad(10.0f, 10.0f, 0, pulseScale, pulseScale, 1.0f);
                TRANSFORM(transformedQuad)->TranslateQuad(nameCursor * 14 + 160, 130.0f, 0);
                texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            }
            DrawNumber(330.0f, 130.0f, 0xFFFFFFFF, static_cast<signed char>(g_ReplayRecords.fileHeader.month), 2);
            SetRect(&textureRect, 228, 40, 247, 60);
            TRANSFORM(transformedQuad)->BuildQuad(325.0f, 130.0f, 344.0f, 150.0f);
            texture->DrawQuad(2, transformedQuad, &textureRect, 0xFFFFFFFF);
            DrawNumber(370.0f, 130.0f, 0xFFFFFFFF, static_cast<signed char>(g_ReplayRecords.fileHeader.day), 2);
            if (static_cast<signed char>(g_ReplayRecords.fileHeader.mode) == 0) {
                SetRect(&textureRect, 0, g_ReplayRecords.recordHeader.secondaryFighter * 20 + 20, 100, g_ReplayRecords.recordHeader.secondaryFighter * 20 + 40);
                TRANSFORM(transformedQuad)->BuildQuad(380.0f, 136.0f, 480.0f, 150.0f);
                TRANSFORM(transformedQuad)->TranslateQuad(36.0f, 8.0f, 0);
                texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFB0B0B0);
            }
            SetRect(&textureRect, 0, static_cast<signed char>(g_ReplayRecords.fileHeader.primaryFighter) * 20 + 20, 100, static_cast<signed char>(g_ReplayRecords.fileHeader.primaryFighter) * 20 + 40);
            TRANSFORM(transformedQuad)->BuildQuad(380.0f, 130.0f, 480.0f, 150.0f);
            texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
            SetRect(&textureRect, 100, static_cast<signed char>(g_ReplayRecords.fileHeader.mode) * 20 + 20, 180, static_cast<signed char>(g_ReplayRecords.fileHeader.mode) * 20 + 40);
            TRANSFORM(transformedQuad)->BuildQuad(500.0f, 130.0f, 580.0f, 150.0f);
            texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        } else {
            SetRect(&textureRect, 200, 20, 460, 60);
            TRANSFORM(transformedQuad)->BuildQuad(190.0f, 200.0f, 450.0f, 240.0f);
            texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
            if (cancelChoice == 0) SetRect(&textureRect, 320, 192, 448, 224);
            else SetRect(&textureRect, 192, 192, 320, 224);
            TRANSFORM(transformedQuad)->BuildQuad(256.0f, 280.0f, 384.0f, 312.0f);
            texture->DrawQuad(1, transformedQuad, &textureRect, 0xFFFFFFFF);
        }
        Graphics::EndFrame();
    }
}
#undef TRANSFORM
