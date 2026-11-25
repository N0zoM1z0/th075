#include "engine/GameSharedState.hpp"
#include "battle/BackgroundStageBaseF479.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/TextOverlay.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "battle/BattleScene.hpp"
#include "battle/CombatEffects.hpp"
#include "battle/BattleRender43D9D0.hpp"
#include "battle/CommandListF283.hpp"
#include "battle/EffectManagerLifetimeF161.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
signed char g_RenderOrderAt0068C860;

void BattleScene::Render() {
    if (field0A0 == 0 && field0A1 == 0) {
        CameraUpdate4126C0::Advance();
        if (field09C < 1.0f) {
            if (field09C < 0.0f)
                field09C = 0.0f;
            field09C += 0.01f;
            if (field09C > 1.0f)
                field09C = 1.0f;
        }
        if ((fighters[1]->action) >= 300) {
            if ((fighters[0]->action) < 300)
                g_RenderOrderAt0068C860 = 1;
        } else if ((fighters[0]->action) >= 300) {
            g_RenderOrderAt0068C860 = 0;
        }
    }

    Graphics::SetDrawTransform(
        1.0f - ((320.0f - g_CombatViewSpan) / 320.0f) / 3.0f,
        (320.0f - g_CombatViewSpan) * 0.5f - 160.0f,
        (g_CombatViewSpan / 320.0f) * -240.0f - 60.0f +
        ((((320.0f - g_CombatViewSpan) * 0.0f) / 320.0f) * 280.0f) / 2.0f);
    if (Graphics::BeginFrame()) {
        if (g_FramePresentToggle) {
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetColorMultiplier(field09C);
            g_CurrentBattleStageAt00671424->Render();
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(0);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(3);
            fighters[0]->field2EC->DispatchAll();
            fighters[1]->field2EC->DispatchAll();
            fighters[0]->RenderMirroredNode();
            fighters[1]->RenderMirroredNode();
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetColorMultiplier(1.0f);
            g_CurrentBattleStageAt00671424->Slot3();
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(0);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(3);
            fighters[0]->field2EC->DispatchSelected(2);
            fighters[1]->field2EC->DispatchSelected(2);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(1);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(2);
            fighters[0]->field480->RenderElements();
            fighters[1]->field480->RenderElements();
            g_CombatEffects.DispatchSelectedList(0);
            fighters[0]->field2EC->DispatchSelected(0);
            fighters[1]->field2EC->DispatchSelected(0);
            if (g_RenderOrderAt0068C860 != 0) {
                fighters[0]->Render();
                fighters[1]->Render();
                fighters[0]->RenderChain();
                fighters[1]->RenderChain();
            } else {
                fighters[1]->Render();
                fighters[0]->Render();
                fighters[1]->RenderChain();
                fighters[0]->RenderChain();
            }
            fighters[0]->field2EC->DispatchSelected(1);
            fighters[1]->field2EC->DispatchSelected(1);
            g_CombatEffects.DispatchSelectedList(1);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetColorMultiplier(field09C);
            g_CurrentBattleStageAt00671424->Slot2();
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetColorMultiplier(1.0f);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetDepthMode(0);
            if (g_OptionsFlagAt00671428)
                RenderDamageFlash();
        }
        Graphics::SetDrawTransform(1.0f, 0.0f, 0.0f);
        if (g_StateFadeAlpha > 0) {
            RECT rectangle;
            SetRect(&rectangle, 0, 0, 640, 480);
            reinterpret_cast<TextureManagerF198*>(STYLE)->SetBlendMode(0);
            Graphics::DrawFilledRectangle(&rectangle,
                (static_cast<D3DCOLOR>(g_StateFadeAlpha) << 24) | g_StateResetCounter);
        }
        RenderHud();
        fighters[0]->field2EC->DispatchSelected(3);
        fighters[1]->field2EC->DispatchSelected(3);
        if (fighters[0]->fadeAlpha > 0)
            fighters[0]->RenderFadeOverlay();
        if (fighters[1]->fadeAlpha > 0)
            fighters[1]->RenderFadeOverlay();
        RenderStatus();
        if (field018 == 5) {
            DrawSelectedNotice();
        } else if (field018 == 7) {
            if ((fighters[0]->noticeFirst) == 0) {
                if ((fighters[0]->noticeBadge) >= 0)
                    fighters[0]->RenderSideEffect();
                if ((fighters[1]->noticeBadge) >= 0)
                    fighters[1]->RenderSideEffect();
            } else {
                if ((fighters[1]->noticeBadge) >= 0)
                    fighters[1]->RenderSideEffect();
                if ((fighters[0]->noticeBadge) >= 0)
                    fighters[0]->RenderSideEffect();
            }
            if ((fighters[0]->noticeEnabled))
                g_TextRenderer->DrawBox();
            fighters[0]->RenderStage(g_StageAt0067161E);
        }
        if (field060 > 0)
            RenderOverlayTimeline();
        if (field06C > 0)
            RenderRoundBanner();
        if (field0A1)
            RenderEndOverlay();
        if (field028 + 1000U < timeGetTime()) {
            field020 = field024;
            field024 = 0;
            field028 = timeGetTime();
        }
        ++field024;
        DrawAtlasNumberDefaultAt00446B60(640.0f, 0.0f, 0xFFFFFFFF,
                                       field020, 4);
        Graphics::EndFrame();
    }
}

#undef STYLE
