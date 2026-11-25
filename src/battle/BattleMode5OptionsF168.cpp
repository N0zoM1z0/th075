#include "input/InputControl.hpp"
#include <math.h>
#include "battle/BattleScene.hpp"
#include "battle/BattleMode5OptionsF168.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "ui/SelectionInput4388D0.hpp"


void BattleScene::HandleMode5Options()
{
    if (field0A0 == 0)
        return;

    if (::abs(static_cast<long>(g_InputMappings[0].held.counts[InputControl::Horizontal])) == 1) {
        g_SoundBank->Play(39);
        signed char horizontal = *reinterpret_cast<signed char*>(&g_InputMappings[0].held);
        switch (field118) {
        case 0:
            fighters[1]->practiceSpellSelection = (fighters[1]->practiceSpellSelection + 6 + horizontal) % 6;
            break;
        case 1:
            fighters[1]->practiceSpellStock = (fighters[1]->practiceSpellStock + 10 + horizontal) % 10;
            break;
        case 2:
            fighters[1]->practiceGuardMode = (fighters[1]->practiceGuardMode + 4 + horizontal) % 4;
            break;
        case 3:
            fighters[1]->practiceManualAirRecovery = (fighters[1]->practiceManualAirRecovery + 2 + horizontal) % 2;
            break;
        case 4:
            fighters[1]->practiceActionMode = (fighters[1]->practiceActionMode + 4 + horizontal) % 4;
            break;
        case 5:
            fighters[1]->practiceCenterPosition = (fighters[1]->practiceCenterPosition + 2 + horizontal) % 2;
            break;
        }
    }

    if (g_InputMappings[0].held.counts[InputControl::ButtonA] == 1) {
        switch (field118) {
        case 6:
            fighters[0]->spellTimer = 1;
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
    if (g_InputMappings[0].held.counts[InputControl::ButtonB] == 1)
        field0A0 = 0;
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == 1 || g_InputMappings[1].held.counts[InputControl::Vertical] == 1) {
        g_SoundBank->Play(39);
        field118 = (field118 + 1) % 9;
    }
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == -1 || g_InputMappings[1].held.counts[InputControl::Vertical] == -1) {
        g_SoundBank->Play(39);
        field118 = (field118 + 8) % 9;
    }
    fighters[0]->field39D = 2 - fighters[1]->practiceSpellSelection / 3;
    fighters[0]->selectedSpellCards[0] = fighters[1]->practiceSpellSelection % 3;
    fighters[0]->selectedSpellCards[1] = fighters[1]->practiceSpellSelection % 3;
}
