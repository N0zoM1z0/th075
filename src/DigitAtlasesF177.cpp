#include "DigitAtlasesF177.hpp"
#include "BattleAtlasNumber446B90.hpp"

DigitAtlasesF177::DigitAtlasesF177(IDirect3DTexture8* primary,
                                  IDirect3DTexture8* secondary,
                                  IDirect3DTexture8* auxiliary)
{
    int i;
    g_AtlasNumberTexturesAt0068C894[0] = primary;
    g_AtlasNumberTexturesAt0068C894[1] = secondary;
    g_AtlasNumberTexturesAt0068C894[2] = auxiliary;
    for (i = 0; i < 5; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[0][i], i * 40, 0, i * 40 + 40, 47);
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[0][i + 5], i * 40, 48, i * 40 + 40, 95);
    }
    g_AtlasNumberWidthAt0068C8CC[0] = 40;
    g_AtlasNumberHeightAt0068C8A0[0] = 47;
    g_AtlasNumberAdvanceAt0068C868[0] = 30;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[1][i], i * 11, 111, i * 11 + 11, 128);
    }
    g_AtlasNumberWidthAt0068C8CC[1] = 11;
    g_AtlasNumberHeightAt0068C8A0[1] = 17;
    g_AtlasNumberAdvanceAt0068C868[1] = 10;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[2][i], i * 11, 96, i * 11 + 11, 111);
    }
    g_AtlasNumberWidthAt0068C8CC[2] = 11;
    g_AtlasNumberHeightAt0068C8A0[2] = 15;
    g_AtlasNumberAdvanceAt0068C868[2] = 10;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[3][i], i * 14, 128, i * 14 + 14, 147);
    }
    g_AtlasNumberWidthAt0068C8CC[3] = 14;
    g_AtlasNumberHeightAt0068C8A0[3] = 19;
    g_AtlasNumberAdvanceAt0068C868[3] = 13;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[4][i], i * 10, 147, i * 10 + 10, 162);
    }
    g_AtlasNumberWidthAt0068C8CC[4] = 10;
    g_AtlasNumberHeightAt0068C8A0[4] = 15;
    g_AtlasNumberAdvanceAt0068C868[4] = 7;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[5][i], i * 14, 162, i * 14 + 14, 181);
    }
    g_AtlasNumberWidthAt0068C8CC[5] = 14;
    g_AtlasNumberHeightAt0068C8A0[5] = 19;
    g_AtlasNumberAdvanceAt0068C868[5] = 13;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[6][i], i * 14, 181, i * 14 + 14, 200);
    }
    g_AtlasNumberWidthAt0068C8CC[6] = 14;
    g_AtlasNumberHeightAt0068C8A0[6] = 19;
    g_AtlasNumberAdvanceAt0068C868[6] = 13;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[7][i], i * 11, 200, i * 11 + 11, 214);
    }
    g_AtlasNumberWidthAt0068C8CC[7] = 11;
    g_AtlasNumberHeightAt0068C8A0[7] = 14;
    g_AtlasNumberAdvanceAt0068C868[7] = 10;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[8][i], i * 11, 214, i * 11 + 11, 228);
    }
    g_AtlasNumberWidthAt0068C8CC[8] = 11;
    g_AtlasNumberHeightAt0068C8A0[8] = 14;
    g_AtlasNumberAdvanceAt0068C868[8] = 10;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[9][i], i * 11, 228, i * 11 + 11, 242);
    }
    g_AtlasNumberWidthAt0068C8CC[9] = 11;
    g_AtlasNumberHeightAt0068C8A0[9] = 14;
    g_AtlasNumberAdvanceAt0068C868[9] = 10;
    for (i = 0; i < 5; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[10][i], i * 32, 0, i * 32 + 32, 39);
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[10][i + 5], i * 32, 39, i * 32 + 32, 78);
    }
    g_AtlasNumberWidthAt0068C8CC[10] = 32;
    g_AtlasNumberHeightAt0068C8A0[10] = 39;
    g_AtlasNumberAdvanceAt0068C868[10] = 31;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[11][i], i * 12, 243, i * 12 + 12, 256);
    }
    g_AtlasNumberWidthAt0068C8CC[11] = 12;
    g_AtlasNumberHeightAt0068C8A0[11] = 13;
    g_AtlasNumberAdvanceAt0068C868[11] = 11;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[12][i], i * 12 + 120, 96, i * 12 + 132, 110);
    }
    g_AtlasNumberWidthAt0068C8CC[12] = 12;
    g_AtlasNumberHeightAt0068C8A0[12] = 14;
    g_AtlasNumberAdvanceAt0068C868[12] = 11;
    for (i = 0; i < 10; i++) {
        SetRect(&g_AtlasNumberRegionsAt0068C8F8[13][i], i * 40, 40, i * 40 + 40, 120);
    }
    g_AtlasNumberWidthAt0068C8CC[13] = 40;
    g_AtlasNumberHeightAt0068C8A0[13] = 80;
    g_AtlasNumberAdvanceAt0068C868[13] = 38;
}
