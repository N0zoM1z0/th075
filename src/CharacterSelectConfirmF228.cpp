#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
#include <stdlib.h>
// CharacterSelectScene shares its physical input and animation fields with
// the other character-select methods.
extern unsigned char g_ChoiceSelectedPairAt006714CC[];
extern signed char g_ChoiceGameModeAt006714B4;
extern const float g_ChoiceMinimumAt0065782C;
extern const float g_ChoiceBackStepAt00657874;
extern const float g_ChoiceRiseBoundAt00658268;
extern const float g_ChoiceRiseStepAt00657D14;
extern const float g_ChoiceDropBoundAt00657858;
extern const float g_ChoiceDropStepAt00657480;
extern const float g_ChoiceReadyBoundAt0065826C;
namespace ChoiceInputF228 { int __cdecl TestAction(int key); }
void CharacterSelectScene::UpdatePlayerConfirmation(signed char player)
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
    if ((choiceStop[player])<g_ChoiceReadyBoundAt0065826C &&
       ((choiceStop[player])=(choiceStop[player])+g_ChoiceDropStepAt00657480,
        g_ChoiceReadyBoundAt0065826C<(choiceStop[player])))
        (choiceStop[player])=75.0f;
    if ((input[player].vertical)==-1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=0;
    } else if (ChoiceInputF228::TestAction((input[player].horizontal))==1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=1;
    } else if ((input[player].vertical)==1) {
        g_SoundBank->Play(0x27);
        (chosenPalette[player])=2;
    }
    if ((input[player].confirm)==1) {
        if ((choiceStop[player])<g_ChoiceReadyBoundAt0065826C)
            (choiceStop[player])=75.0f;
        g_ChoiceSelectedPairAt006714CC[player]=(chosenPalette[player]);
        (playerState[player])=4;
        if (g_ChoiceGameModeAt006714B4==3 || g_ChoiceGameModeAt006714B4==4) {
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
        g_ChoiceSelectedPairAt006714CC[player]=static_cast<unsigned char>(rand()%3);
        (playerState[player])=4;
        if (g_ChoiceGameModeAt006714B4==3 || g_ChoiceGameModeAt006714B4==4) {
            playerState[0]=8;
            playerState[1]=8;
        }
        g_SoundBank->Play(0x2d);
    }
    if ((input[player].alternative)==1) (alternatePalette[player])=static_cast<unsigned int>(!(alternatePalette[player]));
}
