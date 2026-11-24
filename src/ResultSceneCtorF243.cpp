#include "BattleResultState.hpp"
#include "GeometryConstants.hpp"
#include "FloatConstants.hpp"
#include "PlayerState.hpp"
#include "BattleSessionState.hpp"
#include "TextureManagerF198.hpp"
#include <windows.h>
#include "Fighter.hpp"
#include "ResultScene.hpp"
extern const char g_ResultTexturePathAt0065801C[] = "data\\system\\result.dat";
extern const char g_ResultTextureRootAt00658014[] = "data";
ResultScene::ResultScene()
{
    textures = new TextureManagerF198();
    textures->AllocateUnformattedSlots(3);
    textures->LoadDefault(g_ResultTexturePathAt0065801C,g_ResultTextureRootAt00658014);
    field014=1.0f;
    field018=0;
    field019=0;
    values[0]=g_BattleFightersAt00671418[1]->field460;
    values[2]=static_cast<int>(g_ResultScoreTotalAt0067160C);
    field030=static_cast<float>(static_cast<int>(g_ResultScoreTotalAt0067160C))/static_cast<float>(g_CumulativeScoreAt006714BC)+FloatConstants::One;
    values[1]=g_MaxComboCount;
    field02C=static_cast<float>(g_MaxComboCount)/GeometryConstants::Hundred+FloatConstants::One;
    values[3]=static_cast<int>(g_BattleFightersAt00671418[0]->health)+(static_cast<int>(static_cast<signed char>(g_SequenceCounterAt00671622))-1+static_cast<int>(g_BattleFightersAt00671418[0]->field39D))*10000;
    field034=static_cast<float>(g_BattleFightersAt00671418[0]->health)/GeometryConstants::TenThousand+static_cast<float>(static_cast<signed char>(g_SequenceCounterAt00671622))+static_cast<float>(g_BattleFightersAt00671418[0]->field39D)-FloatConstants::One;
    field038=0;
    field03C=0;
    field040=0;
    offsets[3]=900;
    offsets[2]=900;
    offsets[1]=900;
    offsets[0]=900;
    offsets[4]=1800;
    g_BattleFightersAt00671418[0]->score+=field038;
    g_BattleFightersAt00671418[0]->health=10000;
    g_BattleFightersAt00671418[0]->recoverableHealth=10000;
}
