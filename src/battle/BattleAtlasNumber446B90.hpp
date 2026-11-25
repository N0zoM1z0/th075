#pragma once
#include "characters/CharacterSpecial5E68C0.hpp"
#include "graphics/GraphicsTexturedDraw.hpp"
#include "graphics/SpriteTransform.hpp"

typedef SpriteQuad40CA80 AtlasQuad446B90;

// Observed indexed access views; outer table extents and original names unknown.
extern short g_AtlasNumberAdvanceAt0068C868[];
extern IDirect3DTexture8* g_AtlasNumberTexturesAt0068C894[];
extern short g_AtlasNumberHeightAt0068C8A0[];
extern short g_AtlasNumberWidthAt0068C8CC[];
extern RECT g_AtlasNumberRegionsAt0068C8F8[][10];
void __cdecl DrawAtlasNumberAt00446B90(float, float, D3DCOLOR, int, signed char, int);
typedef char AtlasNumberRectSize446B90[(sizeof(RECT) == 16) ? 1 : -1];
typedef char AtlasNumberRowStride446B90[(sizeof(g_AtlasNumberRegionsAt0068C8F8[0]) == 160) ? 1 : -1];
