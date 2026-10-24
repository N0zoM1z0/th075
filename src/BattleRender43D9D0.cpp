#include "BattleRender43D9D0.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define ACTOR(offset) FIELD(RenderActor43D9D0*, offset)
#define ACTOR_FIELD(type, actor, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*, actor)) + (offset)))
#define STYLE FIELD(RenderStyle43D9D0*, 0x08)
#define LISTS(actor) ACTOR_FIELD(RenderLists43D9D0*, actor, 0x2EC)
#define SEQUENCE(actor) ACTOR_FIELD(RenderSequence43D9D0*, actor, 0x480)
#define AUX reinterpret_cast<RenderAux43D9D0*>(&g_CombatEffects)

void BattleRender43D9D0::RenderFrame() {
    if (FIELD(unsigned char, 0xA0) == 0 && FIELD(unsigned char, 0xA1) == 0) {
        CameraUpdate4126C0::Advance();
        if (FLOAT(0x9C) < 1.0f) {
            if (FLOAT(0x9C) < 0.0f)
                FLOAT(0x9C) = 0.0f;
            FLOAT(0x9C) += 0.01f;
            if (FLOAT(0x9C) > 1.0f)
                FLOAT(0x9C) = 1.0f;
        }
        if (ACTOR_FIELD(short, 0x48, 0x60) >= 300) {
            if (ACTOR_FIELD(short, 0x44, 0x60) < 300)
                g_RenderOrderAt0068C860 = 1;
        } else if (ACTOR_FIELD(short, 0x44, 0x60) >= 300) {
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
            STYLE->SetColorMultiplier(FLOAT(0x9C));
            g_DrawDispatcher->Slot4();
            STYLE->SetDepthMode(0);
            STYLE->SetDepthMode(3);
            LISTS(0x44)->DispatchFourLists();
            LISTS(0x48)->DispatchFourLists();
            ACTOR(0x44)->DrawMirrored();
            ACTOR(0x48)->DrawMirrored();
            STYLE->SetColorMultiplier(1.0f);
            g_DrawDispatcher->Slot3();
            STYLE->SetDepthMode(0);
            STYLE->SetDepthMode(3);
            LISTS(0x44)->DispatchSelected(2);
            LISTS(0x48)->DispatchSelected(2);
            STYLE->SetDepthMode(1);
            STYLE->SetDepthMode(2);
            SEQUENCE(0x44)->RenderElements();
            SEQUENCE(0x48)->RenderElements();
            AUX->DispatchSelected(0);
            LISTS(0x44)->DispatchSelected(0);
            LISTS(0x48)->DispatchSelected(0);
            if (g_RenderOrderAt0068C860 != 0) {
                ACTOR(0x44)->DrawMain();
                ACTOR(0x48)->DrawMain();
                ACTOR(0x44)->DrawAuxiliary();
                ACTOR(0x48)->DrawAuxiliary();
            } else {
                ACTOR(0x48)->DrawMain();
                ACTOR(0x44)->DrawMain();
                ACTOR(0x48)->DrawAuxiliary();
                ACTOR(0x44)->DrawAuxiliary();
            }
            LISTS(0x44)->DispatchSelected(1);
            LISTS(0x48)->DispatchSelected(1);
            AUX->DispatchSelected(1);
            STYLE->SetColorMultiplier(FLOAT(0x9C));
            g_DrawDispatcher->Slot2();
            STYLE->SetColorMultiplier(1.0f);
            STYLE->SetDepthMode(0);
            if (g_RenderDamageFlashAt00671428)
                DrawDamageFlash();
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
        LISTS(0x44)->DispatchSelected(3);
        LISTS(0x48)->DispatchSelected(3);
        if (ACTOR_FIELD(unsigned char, 0x44, 0x538) > 0)
            ACTOR(0x44)->RenderFadeOverlay();
        if (ACTOR_FIELD(unsigned char, 0x48, 0x538) > 0)
            ACTOR(0x48)->RenderFadeOverlay();
        RenderStatusEffects();
        if (FIELD(signed char, 0x18) == 5) {
            reinterpret_cast<BattleHud*>(this)->DrawSelectedNotice();
        } else if (FIELD(signed char, 0x18) == 7) {
            if (ACTOR_FIELD(signed char, 0x44, 0x6E8) == 0) {
                if (ACTOR_FIELD(signed char, 0x44, 0x6E7) >= 0)
                    ACTOR(0x44)->RenderSideEffect();
                if (ACTOR_FIELD(signed char, 0x48, 0x6E7) >= 0)
                    ACTOR(0x48)->RenderSideEffect();
            } else {
                if (ACTOR_FIELD(signed char, 0x48, 0x6E7) >= 0)
                    ACTOR(0x48)->RenderSideEffect();
                if (ACTOR_FIELD(signed char, 0x44, 0x6E7) >= 0)
                    ACTOR(0x44)->RenderSideEffect();
            }
            if (ACTOR_FIELD(unsigned char, 0x44, 0x6EE))
                g_TextRenderer->DrawBox();
            ACTOR(0x44)->RenderStage(g_NoticeSelection);
        }
        if (FIELD(int, 0x60) > 0)
            RenderOverlayTimeline();
        if (FIELD(int, 0x6C) > 0)
            RenderRoundBanner();
        if (FIELD(unsigned char, 0xA1))
            RenderEndOverlay();
        if (FIELD(DWORD, 0x28) + 1000U < timeGetTime()) {
            FIELD(int, 0x20) = FIELD(int, 0x24);
            FIELD(int, 0x24) = 0;
            FIELD(DWORD, 0x28) = timeGetTime();
        }
        ++FIELD(int, 0x24);
        DrawAtlasNumberDefaultAt00446B60(640.0f, 0.0f, 0xFFFFFFFF,
                                       FIELD(int, 0x20), 4);
        Graphics::EndFrame();
    }
}

#undef AUX
#undef SEQUENCE
#undef LISTS
#undef STYLE
#undef ACTOR_FIELD
#undef ACTOR
#undef FLOAT
#undef FIELD
