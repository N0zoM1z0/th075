#include "battle/BattleResultState.hpp"
#include "ui/BattleEndScene.hpp"
#include "battle/Fighter.hpp"
#include "battle/PlayerState.hpp"
#include "engine/GameSharedState.hpp"
#include "engine/GameProgress.hpp"
#include "graphics/TextOverlay.hpp"
#include <windows.h>

extern const char g_EndTitleAt00657B7B[] = "";

BattleEndScene::BattleEndScene()
{
    g_TextRenderer->ConfigureText(35.0f,360.0f,1);
    g_TextRenderer->RenderTextToTexture(g_EndTitleAt00657B7B,120,120,255,16,1,0);
    g_BattleFightersAt00671418[0]->noticeEnabled=0;
    g_StageAt0067161E=g_BattleFightersAt00671418[0]->field713;
    g_BattleFightersAt00671418[0]->ConfigureStage();
    g_BattleFightersAt00671418[0]->LoadStageResource();
    if (g_StageAt0067161E==8) {
        g_StateReturnFlag=0;
        g_GameProgress.SetUnlockBit(g_PlayerIdAt006714C8[0]);
    } else if (g_StageAt0067161E==9) {
        g_StateReturnFlag=0;
        g_GameProgress.SetUnlockBit(g_PlayerIdAt006714C8[0]+20);
    } else {
        g_StateReturnFlag=-1;
        g_GameProgress.RecordStoryClear();
        g_GameProgress.SetUnlockBit(g_PlayerIdAt006714C8[0]+40);
    }
}
