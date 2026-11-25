#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteQuad.hpp"
#include "graphics/SpriteTransform.hpp"
#include "characters/ReimuFighter.hpp"
#include "characters/MarisaFighter.hpp"
#include "characters/SakuyaFighter.hpp"
#include "characters/AliceFighter.hpp"
#include "characters/YoumuFighter.hpp"
#include "characters/RemiliaFighter.hpp"
#include "characters/YuyukoFighter.hpp"
#include "characters/YukariFighter.hpp"
#include "characters/SuikaFighter.hpp"

// The renderers share their drawing code and use each fighter's named members.
#define DEFINE_STAGE_RENDERER(FighterType, left0, left1, left2, left3, top0, top1, top2, top3, \
                              alpha0, alpha1, alpha2, alpha3, fadeTimer) \
void FighterType::RenderStage(signed char stage) \
{ \
    SpriteQuad40CA80 quadValue; \
    RECT region; \
    switch (stage) { \
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: \
        static_cast<TextureManagerF198*>(drawing)->SetTextureFilter(2); \
        SetRect(&region, 0, 0, 1024, 32); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(left0, top0, left0 + 1024.0f, top0 + 32.0f); \
        stageTexture->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(alpha0, 255, 255, 255)); \
        SetRect(&region, 0, 0, 1024, 32); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(left1, top1, left1 + 1024.0f, top1 + 32.0f); \
        stageTexture->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(alpha1, 255, 255, 255)); \
        static_cast<TextureManagerF198*>(drawing)->SetTextureFilter(1); \
        SetRect(&region, 0, 0, 640, 128); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(left2, top2, left2 + 640.0f, top2 + 128.0f); \
        stageTexture->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(alpha2, 255, 255, 255)); \
        SetRect(&region, 0, 0, 304, 80); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(left3, top3, left3 + 304.0f, top3 + 80.0f); \
        stageTexture->DrawQuad(3, quadValue, &region, D3DCOLOR_ARGB(alpha3, 255, 255, 255)); \
        if (field6F8 == 1 && alpha3 < 255 && fadeTimer == 0) { \
            if (alpha3 < 250) alpha3 += 5; \
            else alpha3 = 255; \
        } \
        if (alpha3 == 255) ++fadeTimer; \
        if (fadeTimer > 180) { \
            if (alpha3 > 0) alpha3 -= 5; \
            if (alpha3 < 0) alpha3 = 0; \
        } \
        break; \
    case 8: case 9: \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(alpha0, 255, 255, 255)); \
        break; \
    case 10: \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(alpha0, 255, 255, 255)); \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(alpha1, 255, 255, 255)); \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(alpha2, 255, 255, 255)); \
        break; \
    } \
}

DEFINE_STAGE_RENDERER(ReimuFighter, fieldF2C, fieldF30, fieldF34, fieldF38,
                      fieldF54, fieldF58, fieldF5C, fieldF60, fieldFF4, fieldFF5, fieldFF6, fieldFF7, fieldEFE)
DEFINE_STAGE_RENDERER(MarisaFighter, fieldF34, fieldF38, fieldF3C, fieldF40,
                      fieldF5C, fieldF60, fieldF64, fieldF68, fieldFFC, fieldFFD, fieldFFE, fieldFFF, fieldEFE)
DEFINE_STAGE_RENDERER(SakuyaFighter, fieldF18, fieldF1C, fieldF20, fieldF24,
                      fieldF40, fieldF44, fieldF48, fieldF4C, fieldFE0, fieldFE1, fieldFE2, fieldFE3, fieldEFE)
DEFINE_STAGE_RENDERER(AliceFighter, fieldF18, fieldF1C, fieldF20, fieldF24,
                      fieldF40, fieldF44, fieldF48, fieldF4C, fieldFE0, fieldFE1, fieldFE2, fieldFE3, fieldEFE)
DEFINE_STAGE_RENDERER(YoumuFighter, fieldF18, fieldF1C, fieldF20, fieldF24,
                      fieldF40, fieldF44, fieldF48, fieldF4C, fieldFE0, fieldFE1, fieldFE2, fieldFE3, fieldEFE)
DEFINE_STAGE_RENDERER(RemiliaFighter, fieldF10, fieldF14, fieldF18, fieldF1C,
                      fieldF38, fieldF3C, fieldF40, fieldF44, fieldFD8, fieldFD9, fieldFDA, fieldFDB, fieldEFE)
DEFINE_STAGE_RENDERER(YuyukoFighter, fieldF14, fieldF18, fieldF1C, fieldF20,
                      fieldF3C, fieldF40, fieldF44, fieldF48, fieldFDC, fieldFDD, fieldFDE, fieldFDF, fieldEFE)
DEFINE_STAGE_RENDERER(YukariFighter, fieldF34, fieldF38, fieldF3C, fieldF40,
                      fieldF5C, fieldF60, fieldF64, fieldF68, fieldFFC, fieldFFD, fieldFFE, fieldFFF, fieldEFE)
DEFINE_STAGE_RENDERER(SuikaFighter, fieldF2C, fieldF30, fieldF34, fieldF38,
                      fieldF54, fieldF58, fieldF5C, fieldF60, fieldFF4, fieldFF5, fieldFF6, fieldFF7, fieldF2A)

#undef DEFINE_STAGE_RENDERER
