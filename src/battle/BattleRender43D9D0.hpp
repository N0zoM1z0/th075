#pragma once
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/GraphicsDraw.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "battle/BattleScene.hpp"
#include "battle/CameraUpdate4126C0.hpp"
#include <mmsystem.h>

void __cdecl DrawAtlasNumberDefaultAt00446B60(float, float, D3DCOLOR, int, signed char);

// Pointer-only interfaces; never construct or embed these partial receivers.
class RenderStyle43D9D0 {
public:
    void SetBlendMode(int);
    void SetDepthMode(int);
    void SetColorMultiplier(float);
};
extern unsigned char g_OptionsFlagAt00671428;
extern signed char g_RenderOrderAt0068C860;
