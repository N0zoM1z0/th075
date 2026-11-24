#include "GeometryConstants.hpp"
#include "FloatConstants.hpp"
#include "PlayerState.hpp"
#include "BattleSessionState.hpp"
#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
#include <stdlib.h>
// Per-player choice transitions share the scene layout and the 28-byte
// input snapshots with the confirmation and option handlers.
namespace ChoiceInputF226 { int __cdecl TestAction(int key); }
void CharacterSelectScene::UpdatePlayerChoice(signed char player)
{
    if (FloatConstants::Zero < (portraitReturn[player]))
        (portraitReturn[player]) -= FloatConstants::Five;
    if ((portraitEnterX[player]) < GeometryConstants::Eighty)
        (portraitEnterX[player]) = (portraitEnterX[player]) + FloatConstants::Four;
    if ((portraitEnterY[player]) < GeometryConstants::Forty)
        (portraitEnterY[player]) = (portraitEnterY[player]) + FloatConstants::Two;
    if ((portraitExitX[player]) < GeometryConstants::Eighty)
        (portraitExitX[player]) = (portraitExitX[player]) + FloatConstants::Four;
    if ((portraitExitY[player]) < GeometryConstants::Forty)
        (portraitExitY[player]) = (portraitExitY[player]) + FloatConstants::Two;
    if ((choiceStop[player]) < GeometryConstants::Fifteen)
        (choiceStop[player]) = (choiceStop[player]) + FloatConstants::One;
    else if (GeometryConstants::Fifteen < (choiceStop[player])) {
        (choiceStop[player]) -= FloatConstants::Two;
        if ((choiceStop[player]) < GeometryConstants::Fifteen)
            (choiceStop[player])=0.0f;
    }
    if ((input[player].vertical)==-1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=0;
    } else if (ChoiceInputF226::TestAction((input[player].horizontal))==1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=1;
    } else if ((input[player].vertical)==1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=2;
    }
    if ((input[player].confirm)==1) {
        g_PlayerAltAt00671610[player]=(chosenPalette[player]);
        (playerState[player])=2;
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].cancel)==1) {
        g_SoundBank->Play(0x28);
        g_StoryResultAt00671621=0;
        optionsCursor[0]=0;
        (playerState[player])=0;
        (portraitEnterX[player])=80.0f;
        (portraitEnterY[player])=40.0f;
        (portraitExitX[player])=80.0f;
        (portraitExitY[player])=40.0f;
        (playerReady[player])=1;
    }
    if ((input[player].toggle)==1) (choiceRandom[player]) = static_cast<unsigned int>(!(choiceRandom[player]));
    if ((input[player].special)==1) {
        g_PlayerAltAt00671610[player]=static_cast<unsigned char>(rand()%3);
        (playerState[player])=2;
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].alternative)==1) (alternatePalette[player]) = static_cast<unsigned int>(!(alternatePalette[player]));
}
