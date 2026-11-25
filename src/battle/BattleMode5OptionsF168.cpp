#include "input/InputControl.hpp"
#include <math.h>
#include "battle/BattleScene.hpp"
#include "battle/BattleMode5OptionsF168.hpp"
#include "engine/GameLeafHelpers.hpp"
#include "ui/SelectionInput4388D0.hpp"


void BattleScene::HandleMode5Options()
{
    if (pauseMenuOpen == 0)
        return;

    if (::abs(static_cast<long>(g_InputMappings[0].held.counts[InputControl::Horizontal])) == 1) {
        g_SoundBank->Play(39);
        signed char horizontal = *reinterpret_cast<signed char*>(&g_InputMappings[0].held);
        switch (pauseMenuRow) {
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
        switch (pauseMenuRow) {
        case 6:
            fighters[0]->spellTimer = 1;
            g_SoundBank->Play(45);
            break;
        case 7:
            pauseMenuOpen = 0;
            g_SoundBank->Play(45);
            break;
        case 8:
            pauseMenuOpen = 0;
            g_SoundBank->Play(45);
            battlePhase = BattlePhase::LeaveBattle;
            break;
        }
    }
    if (g_InputMappings[0].held.counts[InputControl::ButtonB] == 1)
        pauseMenuOpen = 0;
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == 1 || g_InputMappings[1].held.counts[InputControl::Vertical] == 1) {
        g_SoundBank->Play(39);
        pauseMenuRow = (pauseMenuRow + 1) % 9;
    }
    if (g_InputMappings[0].held.counts[InputControl::Vertical] == -1 || g_InputMappings[1].held.counts[InputControl::Vertical] == -1) {
        g_SoundBank->Play(39);
        pauseMenuRow = (pauseMenuRow + 8) % 9;
    }
    fighters[0]->field39D = 2 - fighters[1]->practiceSpellSelection / 3;
    fighters[0]->selectedSpellCards[0] = fighters[1]->practiceSpellSelection % 3;
    fighters[0]->selectedSpellCards[1] = fighters[1]->practiceSpellSelection % 3;
}
