#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
// The final stop comparison is intentionally a plain member expression:
// VC7.1 evaluates the original equality in the same x87 order.
extern const float g_ChoiceCancelHorizontalLimitAt00658268;
extern const float g_ChoiceCancelHorizontalStepAt00657D14;
extern const float g_ChoiceCancelVerticalLimitAt00657858;
extern const float g_ChoiceCancelVerticalStepAt00657480;
extern const float g_ChoiceZeroAt0065782C;
extern const float g_ChoiceCancelReturnStepAt0065747C;
extern const float g_ChoiceCancelStopAt00658264;
void CharacterSelectScene::UpdateCancelAnimation(signed char player)
{
    if ((portraitEnterX[player])<g_ChoiceCancelHorizontalLimitAt00658268)
        (portraitEnterX[player])=(portraitEnterX[player])+g_ChoiceCancelHorizontalStepAt00657D14;
    if ((portraitEnterY[player])<g_ChoiceCancelVerticalLimitAt00657858)
        (portraitEnterY[player])=(portraitEnterY[player])+g_ChoiceCancelVerticalStepAt00657480;
    if ((portraitExitX[player])<g_ChoiceCancelHorizontalLimitAt00658268)
        (portraitExitX[player])=(portraitExitX[player])+g_ChoiceCancelHorizontalStepAt00657D14;
    if ((portraitExitY[player])<g_ChoiceCancelVerticalLimitAt00657858)
        (portraitExitY[player])=(portraitExitY[player])+g_ChoiceCancelVerticalStepAt00657480;
    if (g_ChoiceZeroAt0065782C<(choiceStop[player]))
        (choiceStop[player])=(choiceStop[player])-g_ChoiceCancelReturnStepAt0065747C;
    if (choiceStop[player]==g_ChoiceCancelStopAt00658264)
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
