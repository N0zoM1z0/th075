#include "battle/BattleScene.hpp"
#include "graphics/LeafRenderF176.hpp"
#include "battle/BattleHud43E040.hpp"
#include "battle/CombatEffects.hpp"


void __cdecl DrawAtlasNumberDefaultAt00446B60(float x, float y, D3DCOLOR color,
                                             int number, signed char style)
{
    DrawAtlasNumberAt00446B90(x, y, color, number, style, 0);
}

void BattleScene::SetNotice(unsigned char state)
{
    noticeFrames = 150;
    noticeKind = state;
}

void AuxiliaryForwardersF176::SpawnAuxEffect(short effect, float x, float y,
                                             signed char facing, signed char layer,
                                             unsigned int)
{
    g_CombatEffects.SpawnConfigured(effect, x, y, facing, layer, 0, 0,
                                effectParameters);
}

void AuxiliaryForwardersF176::SpawnConfiguredAuxEffect(short effect, float x,
                                                       float y, signed char facing,
                                                       signed char layer,
                                                       unsigned char flagA,
                                                       unsigned char flagB)
{
    g_CombatEffects.SpawnConfigured(effect, x, y, facing, layer, flagA, flagB,
                                effectParameters);
}
