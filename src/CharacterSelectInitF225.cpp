#include "BattleResultState.hpp"
#include "Fighter.hpp"
#include "PlayerState.hpp"
#include "BattleSessionState.hpp"
#include "GameProgress.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>
#include "CharacterSelectScene.hpp"
// The original scene constructs three 80-byte texture manager instances.
extern const char g_SelectTextureDataAt006581EC[];
extern const char g_SelectTextureRootAt006581E4[] = "datab";
extern const char g_CharacterTextureDataAt0065820C[];
extern const char g_CharacterTextureRootAt00658204[] = "datab";
extern const char g_BackgroundTextureDataAt00658230[];
extern const char g_BackgroundTextureRootAt00658228[] = "datab";
namespace GameConfigF193 { void ReadIni(); }
CharacterSelectScene::CharacterSelectScene()
{
    if (g_BattleFightersAt00671418[0]) {
        delete g_BattleFightersAt00671418[0];
        g_BattleFightersAt00671418[0]=0;
    }
    if (g_BattleFightersAt00671418[1]) {
        delete g_BattleFightersAt00671418[1];
        g_BattleFightersAt00671418[1]=0;
    }
    (menuTextures)=new TextureManagerF198();
    (menuTextures)->AllocateUnformattedSlots(8);
    (menuTextures)->LoadDefault(g_SelectTextureDataAt006581EC,g_SelectTextureRootAt006581E4);
    (characterTextures)=new TextureManagerF198();
    (characterTextures)->AllocateUnformattedSlots(22);
    (characterTextures)->LoadDefault(g_CharacterTextureDataAt0065820C,g_CharacterTextureRootAt00658204);
    (backgroundTextures)=new TextureManagerF198();
    (backgroundTextures)->AllocateUnformattedSlots(17);
    (backgroundTextures)->LoadDefault(g_BackgroundTextureDataAt00658230,g_BackgroundTextureRootAt00658228);
    g_ReplayModeAt0066C238=1;
    g_StoryChoiceAt00671620=0;
    g_ContinueUsedAt00671624=0;
    GameConfigF193::ReadIni();
    int i;
    for (i=0;i<30;++i)
        (stageAvailable[i]) = ProgressRecordsF736::CheckEncodedItem(static_cast<unsigned char>(i));
    for (i=0;i<15;++i) {
        (leftCharacterAvailable[i]) = GameProgressF203::CheckSelection(static_cast<unsigned char>(i),0);
        (rightCharacterAvailable[i]) = GameProgressF203::CheckSelection(static_cast<unsigned char>(i),1);
    }
    (stageCountdown[0])=0;
    (stageCountdown[1])=0;
    ResetSelection();
}
