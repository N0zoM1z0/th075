#include "CharacterSelectScene.hpp"
// Option handling uses the same signed selectors and input snapshots as
// the scene update.
class ChoiceSoundF230 {public: void Play(int id);};
extern ChoiceSoundF230* g_ChoiceSoundAt00671618;
extern signed char g_SelectOptionAt00671434[2];
extern unsigned char g_SelectOptionFlagAt00671438[2];
namespace ChoiceInputF230 {int __cdecl TestAction(int input);}
void CharacterSelectScene::ProcessPlayerOptions(signed char player)
{
    if (ChoiceInputF230::TestAction((input[player].vertical))==1) {
        g_ChoiceSoundAt00671618->Play(0x27);
        (optionsCursor[player])=1-(optionsCursor[player]);
    }
    if ((optionsCursor[player])==0) {
        if ((input[player].confirm)==1 || ChoiceInputF230::TestAction((input[player].horizontal))==1) {
            g_ChoiceSoundAt00671618->Play(0x2d);
            g_SelectOptionFlagAt00671438[player]=(static_cast<int>(g_SelectOptionFlagAt00671438[player])?0:1);
        }
    } else {
        if ((input[player].confirm)==1 || (input[player].horizontal)==1) {
            g_ChoiceSoundAt00671618->Play(0x2d);
            g_SelectOptionAt00671434[player]=(g_SelectOptionAt00671434[player]+1)%5;
        }
        if ((input[player].horizontal)==-1) {
            g_ChoiceSoundAt00671618->Play(0x2d);
            g_SelectOptionAt00671434[player]=(g_SelectOptionAt00671434[player]+4)%5;
        }
    }
    if ((input[player].alternative)==1) {
        g_ChoiceSoundAt00671618->Play(0x28);
        (optionsOpen[player])=!(optionsOpen[player]);
    }
}
