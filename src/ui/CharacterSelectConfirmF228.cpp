#include "battle/CombatMode.hpp"
#include "engine/GeometryConstants.hpp"
#include "engine/FloatConstants.hpp"
#include "battle/PlayerState.hpp"
#include "engine/GameSharedState.hpp"
#include "ui/CharacterSelectScene.hpp"
#include "audio/SoundBank.hpp"
#include <math.h>
// CharacterSelectScene shares its physical input and animation fields with
// the other character-select methods.
void CharacterSelectScene::UpdatePlayerConfirmation(signed char player)
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
    if ((choiceStop[player])<GeometryConstants::SeventyFive &&
       ((choiceStop[player])=(choiceStop[player])+FloatConstants::Two,
        GeometryConstants::SeventyFive<(choiceStop[player])))
        (choiceStop[player])=75.0f;
    if ((input[player].vertical)==-1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=0;
    } else if (::abs(static_cast<long>((input[player].horizontal)))==1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=1;
    } else if ((input[player].vertical)==1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=2;
    }
    if ((input[player].confirm)==1) {
        if ((choiceStop[player])<GeometryConstants::SeventyFive)
            (choiceStop[player])=75.0f;
        g_PlayerOtherAt006714CC[player]=(chosenPalette[player]);
        (playerState[player])=4;
        if (g_CombatMode==CombatMode::Story || g_CombatMode==CombatMode::Arcade) {
            playerState[0]=8;
            playerState[1]=8;
        }
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].cancel)==1) {
        g_SoundBank->Play(0x28);
        (playerState[player])=1;
    }
    if ((input[player].toggle)==1) (choiceRandom[player])=static_cast<unsigned int>(!(choiceRandom[player]));
    if ((input[player].special)==1) {
        g_PlayerOtherAt006714CC[player]=static_cast<unsigned char>(rand()%3);
        (playerState[player])=4;
        if (g_CombatMode==CombatMode::Story || g_CombatMode==CombatMode::Arcade) {
            playerState[0]=8;
            playerState[1]=8;
        }
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].alternative)==1) (alternatePalette[player])=static_cast<unsigned int>(!(alternatePalette[player]));
}
