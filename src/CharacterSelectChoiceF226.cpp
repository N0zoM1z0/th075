#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
#include <stdlib.h>
// Per-player choice transitions share the scene layout and the 28-byte
// input snapshots with the confirmation and option handlers.
extern unsigned char g_ChoiceRandomModeAt00671610[];
extern unsigned char g_ChoiceStageAt00671621;
extern const float g_ChoiceMinimumAt0065782C;
extern const float g_ChoiceBackStepAt00657874;
extern const float g_ChoiceRiseBoundAt00658268;
extern const float g_ChoiceRiseStepAt00657D14;
extern const float g_ChoiceDropBoundAt00657858;
extern const float g_ChoiceDropStepAt00657480;
extern const float g_ChoiceZeroAt00657CBC;
extern const float g_ChoiceReturnStepAt0065747C;
namespace ChoiceInputF226 { int __cdecl TestAction(int key); }
void CharacterSelectScene::UpdatePlayerChoice(signed char player)
{
    if (g_ChoiceMinimumAt0065782C < (portraitReturn[player]))
        (portraitReturn[player]) -= g_ChoiceBackStepAt00657874;
    if ((portraitEnterX[player]) < g_ChoiceRiseBoundAt00658268)
        (portraitEnterX[player]) = (portraitEnterX[player]) + g_ChoiceRiseStepAt00657D14;
    if ((portraitEnterY[player]) < g_ChoiceDropBoundAt00657858)
        (portraitEnterY[player]) = (portraitEnterY[player]) + g_ChoiceDropStepAt00657480;
    if ((portraitExitX[player]) < g_ChoiceRiseBoundAt00658268)
        (portraitExitX[player]) = (portraitExitX[player]) + g_ChoiceRiseStepAt00657D14;
    if ((portraitExitY[player]) < g_ChoiceDropBoundAt00657858)
        (portraitExitY[player]) = (portraitExitY[player]) + g_ChoiceDropStepAt00657480;
    if ((choiceStop[player]) < g_ChoiceZeroAt00657CBC)
        (choiceStop[player]) = (choiceStop[player]) + g_ChoiceReturnStepAt0065747C;
    else if (g_ChoiceZeroAt00657CBC < (choiceStop[player])) {
        (choiceStop[player]) -= g_ChoiceDropStepAt00657480;
        if ((choiceStop[player]) < g_ChoiceZeroAt00657CBC)
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
        g_ChoiceRandomModeAt00671610[player]=(chosenPalette[player]);
        (playerState[player])=2;
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].cancel)==1) {
        g_SoundBank->Play(0x28);
        g_ChoiceStageAt00671621=0;
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
        g_ChoiceRandomModeAt00671610[player]=static_cast<unsigned char>(rand()%3);
        (playerState[player])=2;
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].alternative)==1) (alternatePalette[player]) = static_cast<unsigned int>(!(alternatePalette[player]));
}
