#include "BattleScene.hpp"
#include "BattleRender43D9D0.hpp"
#include "EffectManagerLifetimeF161.hpp"

#define STYLE reinterpret_cast<RenderStyle43D9D0*>(textures)
#define AUX reinterpret_cast<RenderAux43D9D0*>(&g_CombatEffects)

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
    if (BeginGraphicsFrameWithStatusAt00402660()) {
        if (g_FramePresentToggle) {
            STYLE->SetColorMultiplier(field09C);
            g_DrawDispatcher->Slot4();
            STYLE->SetDepthMode(0);
            STYLE->SetDepthMode(3);
            fighters[0]->field2EC->DispatchAll();
            fighters[1]->field2EC->DispatchAll();
            reinterpret_cast<RenderActor43D9D0*>(fighters[0])->DrawMirrored();
            reinterpret_cast<RenderActor43D9D0*>(fighters[1])->DrawMirrored();
            STYLE->SetColorMultiplier(1.0f);
            g_DrawDispatcher->Slot3();
            STYLE->SetDepthMode(0);
            STYLE->SetDepthMode(3);
            fighters[0]->field2EC->DispatchSelected(2);
            fighters[1]->field2EC->DispatchSelected(2);
            STYLE->SetDepthMode(1);
            STYLE->SetDepthMode(2);
            reinterpret_cast<RenderSequence43D9D0*>(fighters[0]->field480)->RenderElements();
            reinterpret_cast<RenderSequence43D9D0*>(fighters[1]->field480)->RenderElements();
            AUX->DispatchSelected(0);
            fighters[0]->field2EC->DispatchSelected(0);
            fighters[1]->field2EC->DispatchSelected(0);
            if (g_RenderOrderAt0068C860 != 0) {
                reinterpret_cast<RenderActor43D9D0*>(fighters[0])->DrawMain();
                reinterpret_cast<RenderActor43D9D0*>(fighters[1])->DrawMain();
                reinterpret_cast<RenderActor43D9D0*>(fighters[0])->DrawAuxiliary();
                reinterpret_cast<RenderActor43D9D0*>(fighters[1])->DrawAuxiliary();
            } else {
                reinterpret_cast<RenderActor43D9D0*>(fighters[1])->DrawMain();
                reinterpret_cast<RenderActor43D9D0*>(fighters[0])->DrawMain();
                reinterpret_cast<RenderActor43D9D0*>(fighters[1])->DrawAuxiliary();
                reinterpret_cast<RenderActor43D9D0*>(fighters[0])->DrawAuxiliary();
            }
            fighters[0]->field2EC->DispatchSelected(1);
            fighters[1]->field2EC->DispatchSelected(1);
            AUX->DispatchSelected(1);
            STYLE->SetColorMultiplier(field09C);
            g_DrawDispatcher->Slot2();
            STYLE->SetColorMultiplier(1.0f);
            STYLE->SetDepthMode(0);
            if (g_OptionsFlagAt00671428)
                RenderDamageFlash();
        }
        Graphics::SetDrawTransform(1.0f, 0.0f, 0.0f);
        if (g_StateFadeAlpha > 0) {
            RECT rectangle;
            SetRect(&rectangle, 0, 0, 640, 480);
            STYLE->SetBlendMode(0);
            Graphics::DrawFilledRectangle(&rectangle,
                (static_cast<D3DCOLOR>(g_StateFadeAlpha) << 24) | g_StateResetCounter);
        }
        RenderHud();
        fighters[0]->field2EC->DispatchSelected(3);
        fighters[1]->field2EC->DispatchSelected(3);
        if (fighters[0]->fadeAlpha > 0)
            reinterpret_cast<RenderActor43D9D0*>(fighters[0])->RenderFadeOverlay();
        if (fighters[1]->fadeAlpha > 0)
            reinterpret_cast<RenderActor43D9D0*>(fighters[1])->RenderFadeOverlay();
        RenderStatus();
        if (field018 == 5) {
            DrawSelectedNotice();
        } else if (field018 == 7) {
            if ((fighters[0]->noticeFirst) == 0) {
                if ((fighters[0]->noticeBadge) >= 0)
                    reinterpret_cast<RenderActor43D9D0*>(fighters[0])->RenderSideEffect();
                if ((fighters[1]->noticeBadge) >= 0)
                    reinterpret_cast<RenderActor43D9D0*>(fighters[1])->RenderSideEffect();
            } else {
                if ((fighters[1]->noticeBadge) >= 0)
                    reinterpret_cast<RenderActor43D9D0*>(fighters[1])->RenderSideEffect();
                if ((fighters[0]->noticeBadge) >= 0)
                    reinterpret_cast<RenderActor43D9D0*>(fighters[0])->RenderSideEffect();
            }
            if ((fighters[0]->noticeEnabled))
                g_TextRenderer->DrawBox();
            reinterpret_cast<RenderActor43D9D0*>(fighters[0])->RenderStage(g_NoticeSelection);
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

#undef AUX
#undef STYLE
