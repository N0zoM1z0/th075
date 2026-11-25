#include "battle/BattleResultState.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "battle/PlayerState.hpp"
#include "battle/BattleSessionState.hpp"
#include "graphics/TextureManagerF198.hpp"
#include <windows.h>
#include "battle/Fighter.hpp"
#include "ui/ResultScene.hpp"
extern const char g_ResultTexturePathAt0065801C[] = "data\\system\\result.dat";
extern const char g_ResultTextureRootAt00658014[] = "data";
ResultScene::ResultScene()
{
    textures = new TextureManagerF198();
    textures->AllocateUnformattedSlots(3);
    textures->LoadDefault(g_ResultTexturePathAt0065801C,g_ResultTextureRootAt00658014);
    backdropScale=1.0f;
    rowsAlpha=0;
    tallySoundCycle=0;
    values[0]=g_BattleFightersAt00671418[1]->field460;
    values[2]=static_cast<int>(g_ResultScoreTotalAt0067160C);
    spellTimeMultiplier=static_cast<float>(static_cast<int>(g_ResultScoreTotalAt0067160C))/static_cast<float>(g_CumulativeScoreAt006714BC)+FloatConstants::One;
    values[1]=g_MaxComboCount;
    comboMultiplier=static_cast<float>(g_MaxComboCount)/GeometryConstants::Hundred+FloatConstants::One;
    values[3]=static_cast<int>(g_BattleFightersAt00671418[0]->health)+(static_cast<int>(static_cast<signed char>(g_SequenceCounterAt00671622))-1+static_cast<int>(g_BattleFightersAt00671418[0]->field39D))*10000;
    remainingHealthMultiplier=static_cast<float>(g_BattleFightersAt00671418[0]->health)/GeometryConstants::TenThousand+static_cast<float>(static_cast<signed char>(g_SequenceCounterAt00671622))+static_cast<float>(g_BattleFightersAt00671418[0]->field39D)-FloatConstants::One;
    pendingBonus=0;
    tallyFrames=0;
    tallyStep=0;
    rowSlideX[3]=900;
    rowSlideX[2]=900;
    rowSlideX[1]=900;
    rowSlideX[0]=900;
    rowSlideX[4]=1800;
    g_BattleFightersAt00671418[0]->score+=pendingBonus;
    g_BattleFightersAt00671418[0]->health=10000;
    g_BattleFightersAt00671418[0]->recoverableHealth=10000;
}
