#include <math.h>
#include "battle/BattleResultState.hpp"
#include "battle/PlayerState.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameProgress.hpp"
#include "ui/CharacterSelectScene.hpp"
#include "audio/SoundBank.hpp"
// Subselection uses player zero of the scene and the native progress-card receiver.
void CharacterSelectScene::ProcessSubselection()
{
    if (::abs(static_cast<long>((input[0].vertical)))==1) {
        g_SoundBank->Play(0x27);
        (optionsCursor[0])=((optionsCursor[0])+(input[0].vertical)+g_GameProgress.GetHighestStoryStage())%g_GameProgress.GetHighestStoryStage();
    }
    if ((input[0].confirm)==1) {
        g_SoundBank->Play(0x2d);
        g_PlayerIdAt006714C8[0]=(chosenCharacter[0]);
        g_StoryChoiceAt00671620=(optionsCursor[0])+1;
        g_StoryResultAt00671621=1;
        g_PlayerRoundAt006714AC[0]=0;
        (playerState[0])=1;
        *reinterpret_cast<int*>(&(choiceStop[0]))=0;
        (optionsOpen[0])=0;
    }
    if ((input[0].alternative)==1 || (input[0].cancel)==1) {
        g_StoryChoiceAt00671620=1;
        g_SoundBank->Play(0x28);
        (optionsOpen[0])=0;
        (optionsCursor[0])=0;
    }
}
