#pragma once
#include "Graphics.hpp"
#include "GraphicsDraw.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleScene.hpp"
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
public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x008 - 0x000];
    RenderStyle43D9D0* field008;
    unsigned char unknown00C[0x018 - 0x00C];
    signed char field018;
    unsigned char unknown019[0x020 - 0x019];
    int field020;
    int field024;
    unsigned long field028;
    unsigned char unknown02C[0x044 - 0x02C];
    void* field044;
    void* field048;
    unsigned char unknown04C[0x060 - 0x04C];
    int field060;
    unsigned char unknown064[0x06C - 0x064];
    int field06C;
    unsigned char unknown070[0x09C - 0x070];
    float field09C;
    unsigned char field0A0;
    unsigned char field0A1;
};
extern unsigned char g_FramePresentToggle;
extern unsigned char g_StateFadeAlpha;
extern int g_StateResetCounter;
extern unsigned char g_RenderDamageFlashAt00671428;
extern signed char g_RenderOrderAt0068C860;
