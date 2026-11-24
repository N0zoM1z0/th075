#include "Fighter.hpp"
#include "PlayerState.hpp"
#include "GameSharedState.hpp"
#include "GameProgress.hpp"
#include "TextOverlay.hpp"
#include <windows.h>
// Scene base, character actor, renderer and profile owner are limited to
// independently observed method ABI and game globals; no full layout.
class SceneBaseF288 {
    void* nativeConfiguration;
public:
    SceneBaseF288();
    virtual ~SceneBaseF288();
};
extern unsigned char g_StatusAt006714CE;
extern const char g_EndTitleAt00657B7B[];
class BattleEndInitF288 : public SceneBaseF288 {
public:
    BattleEndInitF288();
    virtual ~BattleEndInitF288();
};
BattleEndInitF288::BattleEndInitF288()
{
    g_TextRenderer->ConfigureText(35.0f,360.0f,1);
    g_TextRenderer->RenderTextToTexture(g_EndTitleAt00657B7B,120,120,255,16,1,0);
    reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->noticeEnabled=0;
    g_StageAt0067161E=reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->field713;
    reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->ConfigureStage();
    reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->LoadStageResource();
    if (g_StageAt0067161E==8) {
        g_StatusAt006714CE=0;
        g_GameProgress.SetUnlockBit(g_PlayerIdAt006714C8[0]);
    } else if (g_StageAt0067161E==9) {
        g_StatusAt006714CE=0;
        g_GameProgress.SetUnlockBit(g_PlayerIdAt006714C8[0]+20);
    } else {
        g_StatusAt006714CE=0xff;
        g_GameProgress.IncrementSelectedRecord();
        g_GameProgress.SetUnlockBit(g_PlayerIdAt006714C8[0]+40);
    }
}
