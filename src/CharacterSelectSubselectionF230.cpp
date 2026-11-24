#include "CharacterSelectScene.hpp"
#include "SoundBank.hpp"
// Subselection uses player zero of the scene and the native progress-card receiver.
class ProgressCardViewF230 {public: signed char GetSelectedValue();};
extern ProgressCardViewF230 g_SelectedCardAt006718F8;
extern unsigned char g_SelectedFighterAt006714C8;
extern unsigned char g_PlayerPadAt00671620;
extern unsigned char g_SelectStageAt00671621;
extern unsigned char g_ChosenModeAt006714AC;
namespace ChoiceInputF230 {int __cdecl TestAction(int input);}
void CharacterSelectScene::ProcessSubselection()
{
    if (ChoiceInputF230::TestAction((input[0].vertical))==1) {
        g_SoundBank->Play(0x27);
        (optionsCursor[0])=((optionsCursor[0])+(input[0].vertical)+g_SelectedCardAt006718F8.GetSelectedValue())%g_SelectedCardAt006718F8.GetSelectedValue();
    }
    if ((input[0].confirm)==1) {
        g_SoundBank->Play(0x2d);
        g_SelectedFighterAt006714C8=(chosenCharacter[0]);
        g_PlayerPadAt00671620=(optionsCursor[0])+1;
        g_SelectStageAt00671621=1;
        g_ChosenModeAt006714AC=0;
        (playerState[0])=1;
        *reinterpret_cast<int*>(&(choiceStop[0]))=0;
        (optionsOpen[0])=0;
    }
    if ((input[0].alternative)==1 || (input[0].cancel)==1) {
        g_PlayerPadAt00671620=1;
        g_SoundBank->Play(0x28);
        (optionsOpen[0])=0;
        (optionsCursor[0])=0;
    }
}
