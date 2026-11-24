#include "GameSharedState.hpp"
#include "Fighter.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>
#include <stdio.h>
#include <new>

extern const char g_StageTextureFormatAt00658FC0[];
extern const char g_StageArchiveAt00658FE0[] = "data";
void Fighter::LoadStageResource()
{
    char filename[260];
    if (g_StageAt0067161E<=0) return;
    {
        if (stageTexture)
            delete stageTexture;
        stageTexture = new TextureManagerF198();
        stageTexture->AllocateUnformattedSlots(field705[g_StageAt0067161E - 1]);
        sprintf(filename,g_StageTextureFormatAt00658FC0,name,g_StageAt0067161E);
        stageTexture->LoadDefault(filename,g_StageArchiveAt00658FE0);
    }
}
