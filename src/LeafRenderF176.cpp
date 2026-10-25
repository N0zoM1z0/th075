#include "LeafRenderF176.hpp"
#include "BattleHud43E040.hpp"
#include "FighterEffectPolicies.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void __cdecl DrawAtlasNumberDefaultAt00446B60(float x, float y, D3DCOLOR color,
                                             int number, signed char style)
{
    DrawAtlasNumberAt00446B90(x, y, color, number, style, 0);
}

void HudNoticeF176::SetNoticeState(unsigned char state)
{
    FIELD(int, 0x60) = 150;
    FIELD(unsigned char, 0x64) = state;
}

void AuxiliaryForwardersF176::SpawnAuxEffect(short effect, float x, float y,
                                             signed char facing, signed char layer,
                                             unsigned int)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, 0, 0,
                                &FIELD(float, 0x314));
}

void AuxiliaryForwardersF176::SpawnConfiguredAuxEffect(short effect, float x,
                                                       float y, signed char facing,
                                                       signed char layer,
                                                       unsigned char flagA,
                                                       unsigned char flagB)
{
    g_AuxiliaryEffectsF135.Spawn(effect, x, y, facing, layer, flagA, flagB,
                                &FIELD(float, 0x314));
}

#undef FIELD
