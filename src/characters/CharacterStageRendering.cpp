#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteQuad.hpp"
#include "graphics/SpriteTransform.hpp"
#include "characters/reimu/ReimuFighter.hpp"
#include "characters/marisa/MarisaFighter.hpp"
#include "characters/sakuya/SakuyaFighter.hpp"
#include "characters/alice/AliceFighter.hpp"
#include "characters/youmu/YoumuFighter.hpp"
#include "characters/remilia/RemiliaFighter.hpp"
#include "characters/yuyuko/YuyukoFighter.hpp"
#include "characters/yukari/YukariFighter.hpp"
#include "characters/suika/SuikaFighter.hpp"

// The renderers share their drawing code and use each fighter's named members.
#define DEFINE_STAGE_RENDERER(FighterType, fadeTimer) \
void FighterType::RenderStage(signed char stage) \
{ \
    SpriteQuad40CA80 quadValue; \
    RECT region; \
    switch (stage) { \
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: \
        static_cast<TextureManagerF198*>(drawing)->SetTextureFilter(2); \
        SetRect(&region, 0, 0, 1024, 32); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(stageLayerX[0], stageLayerY[0], stageLayerX[0] + 1024.0f, stageLayerY[0] + 32.0f); \
        stageTexture->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[0], 255, 255, 255)); \
        SetRect(&region, 0, 0, 1024, 32); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(stageLayerX[1], stageLayerY[1], stageLayerX[1] + 1024.0f, stageLayerY[1] + 32.0f); \
        stageTexture->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[1], 255, 255, 255)); \
        static_cast<TextureManagerF198*>(drawing)->SetTextureFilter(1); \
        SetRect(&region, 0, 0, 640, 128); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(stageLayerX[2], stageLayerY[2], stageLayerX[2] + 640.0f, stageLayerY[2] + 128.0f); \
        stageTexture->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[2], 255, 255, 255)); \
        SetRect(&region, 0, 0, 304, 80); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuad(stageLayerX[3], stageLayerY[3], stageLayerX[3] + 304.0f, stageLayerY[3] + 80.0f); \
        stageTexture->DrawQuad(3, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[3], 255, 255, 255)); \
        if (stageBannerEnabled == 1 && stageLayerAlpha[3] < 255 && fadeTimer == 0) { \
            if (stageLayerAlpha[3] < 250) stageLayerAlpha[3] += 5; \
            else stageLayerAlpha[3] = 255; \
        } \
        if (stageLayerAlpha[3] == 255) ++fadeTimer; \
        if (fadeTimer > 180) { \
            if (stageLayerAlpha[3] > 0) stageLayerAlpha[3] -= 5; \
            if (stageLayerAlpha[3] < 0) stageLayerAlpha[3] = 0; \
        } \
        break; \
    case 8: case 9: \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[0], 255, 255, 255)); \
        break; \
    case 10: \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(0, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[0], 255, 255, 255)); \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(1, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[1], 255, 255, 255)); \
        SetRect(&region, 0, 0, 640, 480); \
        reinterpret_cast<SpriteTransform*>(&quadValue)->BuildQuadFromRect(&region); \
        stageTexture->DrawQuad(2, quadValue, &region, D3DCOLOR_ARGB(stageLayerAlpha[2], 255, 255, 255)); \
        break; \
    } \
}

DEFINE_STAGE_RENDERER(ReimuFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(MarisaFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(SakuyaFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(AliceFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(YoumuFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(RemiliaFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(YuyukoFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(YukariFighter, stageBannerHoldFrames)
DEFINE_STAGE_RENDERER(SuikaFighter, suikaStageBannerHoldFrames)

#undef DEFINE_STAGE_RENDERER
