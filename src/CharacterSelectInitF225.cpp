#include "BattleSessionState.hpp"
#include "GameProgress.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>
#include "CharacterSelectScene.hpp"
// The original scene constructs three 80-byte texture manager instances.
class ActorResourceF225 {
public:
    virtual void Reserved0();
    virtual void Reserved1();
    virtual void Reserved2();
    virtual void Reserved3();
    virtual void Reserved4();
    virtual ~ActorResourceF225(); // Native deleting destructor in slot five.
};
extern ActorResourceF225* g_ActorAAt00671418;
extern ActorResourceF225* g_ActorBAt0067141C;
extern const char g_SelectTextureDataAt006581EC[];
extern const char g_SelectTextureRootAt006581E4[];
extern const char g_CharacterTextureDataAt0065820C[];
extern const char g_CharacterTextureRootAt00658204[];
extern const char g_BackgroundTextureDataAt00658230[];
extern const char g_BackgroundTextureRootAt00658228[];
extern unsigned char g_FramePadAt00671620;
namespace GameConfigF193 { void ReadIni(); }
CharacterSelectScene::CharacterSelectScene()
{
    if (g_ActorAAt00671418) {
        delete g_ActorAAt00671418;
        g_ActorAAt00671418=0;
    }
    if (g_ActorBAt0067141C) {
        delete g_ActorBAt0067141C;
        g_ActorBAt0067141C=0;
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
    g_FramePadAt00671620=0;
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
