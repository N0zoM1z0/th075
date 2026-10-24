#pragma once
#include "Graphics.hpp"
#include "GraphicsDraw.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleCombatResponses.hpp"
#include "CameraUpdate4126C0.hpp"
#include <mmsystem.h>

// Actual AL status is forwarded by the full native wrapper. This declaration-only
// consumed-result view does not change the older accepted ignored-result body.
bool __cdecl BeginGraphicsFrameWithStatusAt00402660();
void __cdecl DrawAtlasNumberDefaultAt00446B60(float, float, D3DCOLOR, int, signed char);

// Pointer-only interfaces; never construct or embed these partial receivers.
class RenderStyle43D9D0 {
public:
    void SetBlendMode(int);
    void SetDepthMode(int);
    void SetColorMultiplier(float);
};
class RenderLists43D9D0 {
public:
    void DispatchSelected(signed char);
    void DispatchFourLists();
};
class RenderAux43D9D0 { public: void DispatchSelected(signed char); };
class RenderSequence43D9D0 { public: void RenderElements(); };
// Slots are observed indices, not recovered original declarations. Only slots
// 2,4,9,17 below are invoked. All eleven recorded fighter families support
// ret0 for 2/4/9 and signed-byte/ret4 for17; unused signatures remain unknown.
class RenderActor43D9D0 {
public:
    virtual void Slot0(); virtual void Slot1(); virtual void DrawMain();
    virtual void Slot3(); virtual void DrawMirrored(); virtual void Slot5();
    virtual void Slot6(); virtual void Slot7(); virtual void Slot8();
    virtual void DrawAuxiliary(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void RenderStage(signed char);
    void RenderSideEffect();
    void RenderFadeOverlay();
};
class BattleRender43D9D0 {
public:
    void RenderFrame();
    void RenderHud();
    void DrawDamageFlash();
    void RenderStatusEffects();
    void RenderEndOverlay();
    void RenderRoundBanner();
    void RenderOverlayTimeline();
};
extern unsigned char g_FramePresentToggle;
extern unsigned char g_StateFadeAlpha;
extern int g_StateResetCounter;
extern unsigned char g_RenderDamageFlashAt00671428;
extern signed char g_RenderOrderAt0068C860;
