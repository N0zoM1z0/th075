#include "BattleScene.hpp"
#include "LeafRenderF176.hpp"
#include "BattleHud43E040.hpp"
#include "FighterEffectPolicies.hpp"


void __cdecl DrawAtlasNumberDefaultAt00446B60(float x, float y, D3DCOLOR color,
                                             int number, signed char style)
{
    DrawAtlasNumberAt00446B90(x, y, color, number, style, 0);
}

void BattleScene::SetNotice(unsigned char state)
{
    field060 = 150;
    field064 = state;
}

void AuxiliaryForwardersF176::SpawnAuxEffect(short effect, float x, float y,
                                             signed char facing, signed char layer,
                                             unsigned int)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, 0, 0,
                                &field314);
}

void AuxiliaryForwardersF176::SpawnConfiguredAuxEffect(short effect, float x,
                                                       float y, signed char facing,
                                                       signed char layer,
                                                       unsigned char flagA,
                                                       unsigned char flagB)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, flagA, flagB,
                                &field314);
}
