#pragma once
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "Graphics.hpp"
#include "GraphicsDraw.hpp"
#include "GameLeafHelpers.hpp"
#include "BattleScene.hpp"
#include "CameraUpdate4126C0.hpp"
#include <mmsystem.h>

void __cdecl DrawAtlasNumberDefaultAt00446B60(float, float, D3DCOLOR, int, signed char);

// Pointer-only interfaces; never construct or embed these partial receivers.
class RenderStyle43D9D0 {
public:
    void SetBlendMode(int);
    void SetDepthMode(int);
    void SetColorMultiplier(float);
};
class RenderAux43D9D0 { public: void DispatchSelected(signed char); };
class RenderSequence43D9D0 { public: void RenderElements(); };
extern unsigned char g_OptionsFlagAt00671428;
extern signed char g_RenderOrderAt0068C860;
