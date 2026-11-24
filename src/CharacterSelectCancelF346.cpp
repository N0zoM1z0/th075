#include "GeometryConstants.hpp"
#include "FloatConstants.hpp"
#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
// The final stop comparison is intentionally a plain member expression:
// VC7.1 evaluates the original equality in the same x87 order.
void CharacterSelectScene::UpdateCancelAnimation(signed char player)
{
    if ((portraitEnterX[player])<GeometryConstants::Eighty)
        (portraitEnterX[player])=(portraitEnterX[player])+FloatConstants::Four;
    if ((portraitEnterY[player])<GeometryConstants::Forty)
        (portraitEnterY[player])=(portraitEnterY[player])+FloatConstants::Two;
    if ((portraitExitX[player])<GeometryConstants::Eighty)
        (portraitExitX[player])=(portraitExitX[player])+FloatConstants::Four;
    if ((portraitExitY[player])<GeometryConstants::Forty)
        (portraitExitY[player])=(portraitExitY[player])+FloatConstants::Two;
    if (FloatConstants::Zero<(choiceStop[player]))
        (choiceStop[player])=(choiceStop[player])-FloatConstants::One;
    if (choiceStop[player]==GeometryConstants::Sixty)
        *reinterpret_cast<int*>(&(choiceStop[player]))=0;
    if ((input[player].cancel)==1) {
        g_SoundBank->Play(40);
        (playerState[player])=0;
        (portraitEnterX[player])=80.0f;
        (portraitEnterY[player])=40.0f;
        (portraitExitX[player])=80.0f;
        (portraitExitY[player])=40.0f;
        (playerReady[player])=1;
    }
}
