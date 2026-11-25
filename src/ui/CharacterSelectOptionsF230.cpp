#include <math.h>
#include "battle/PlayerState.hpp"
#include "ui/CharacterSelectScene.hpp"
#include "audio/SoundBank.hpp"
// Option handling uses the same signed selectors and input snapshots as
// the scene update.
void CharacterSelectScene::ProcessPlayerOptions(signed char player)
{
    if (::abs(static_cast<long>((input[player].vertical)))==1) {
        g_SoundBank->Play(0x27);
        (optionsCursor[player])=1-(optionsCursor[player]);
    }
    if ((optionsCursor[player])==0) {
        if ((input[player].confirm)==1 || ::abs(static_cast<long>((input[player].horizontal)))==1) {
            g_SoundBank->Play(0x2d);
            g_PlayerDifficultyAt00671438[player]=(static_cast<int>(g_PlayerDifficultyAt00671438[player])?0:1);
        }
    } else {
        if ((input[player].confirm)==1 || (input[player].horizontal)==1) {
            g_SoundBank->Play(0x2d);
            g_PlayerSettingsAt00671434[player]=(g_PlayerSettingsAt00671434[player]+1)%5;
        }
        if ((input[player].horizontal)==-1) {
            g_SoundBank->Play(0x2d);
            g_PlayerSettingsAt00671434[player]=(g_PlayerSettingsAt00671434[player]+4)%5;
        }
    }
    if ((input[player].alternative)==1) {
        g_SoundBank->Play(0x28);
        (optionsOpen[player])=!(optionsOpen[player]);
    }
}
