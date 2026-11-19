#include "BattleScene.hpp"
#include "BattleMode5OptionsF168.hpp"
#include "GameLeafHelpers.hpp"
#include "SelectionInput4388D0.hpp"

// Used caller-cleaned dword argument/EAX contract only. R163 retains unknown
// ownership and original int/long overload spelling for this complete wrapper.
int __cdecl Unknown438A60(int value);


void BattleScene::HandleMode5Options()
{
    if (field0A0 == 0)
        return;

    if (Unknown438A60(g_HeldInputAt00671664.counts[0]) == 1) {
        g_SoundBank->Play(39);
        signed char horizontal = *reinterpret_cast<signed char*>(&g_HeldInputAt00671664);
        switch (field118) {
        case 0:
            fighters[1]->field52C = (fighters[1]->field52C + 6 + horizontal) % 6;
            break;
        case 1:
            fighters[1]->field52D = (fighters[1]->field52D + 10 + horizontal) % 10;
            break;
        case 2:
            fighters[1]->field52F = (fighters[1]->field52F + 4 + horizontal) % 4;
            break;
        case 3:
            fighters[1]->field52E = (fighters[1]->field52E + 2 + horizontal) % 2;
            break;
        case 4:
            fighters[1]->field530 = (fighters[1]->field530 + 4 + horizontal) % 4;
            break;
        case 5:
            fighters[1]->field531 = (fighters[1]->field531 + 2 + horizontal) % 2;
            break;
        }
    }

    if (g_HeldInputAt00671664.counts[2] == 1) {
        switch (field118) {
        case 6:
            fighters[0]->field3A0 = 1;
            g_SoundBank->Play(45);
            break;
        case 7:
            field0A0 = 0;
            g_SoundBank->Play(45);
            break;
        case 8:
            field0A0 = 0;
            g_SoundBank->Play(45);
            field018 = 6;
            break;
        }
    }
    if (g_HeldInputAt00671664.counts[3] == 1)
        field0A0 = 0;
    if (g_HeldInputAt00671664.counts[1] == 1 || g_HeldInputAt006716AC.counts[1] == 1) {
        g_SoundBank->Play(39);
        field118 = (field118 + 1) % 9;
    }
    if (g_HeldInputAt00671664.counts[1] == -1 || g_HeldInputAt006716AC.counts[1] == -1) {
        g_SoundBank->Play(39);
        field118 = (field118 + 8) % 9;
    }
    fighters[0]->field39D = 2 - fighters[1]->field52C / 3;
    fighters[0]->field398[0] = fighters[1]->field52C % 3;
    fighters[0]->field398[1] = fighters[1]->field52C % 3;
}
