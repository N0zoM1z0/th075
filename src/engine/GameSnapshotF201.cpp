#include "battle/CombatMode.hpp"
#include "battle/PlayerState.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "engine/GameSnapshot.hpp"
#include <windows.h>
#include "battle/Fighter.hpp"

// Storage anchors are only address-compatible borrowed views. This function
// never constructs or embeds an assumed original game-state owner.

namespace GameStateF201 {
void SaveSnapshot()
{
    if (g_CombatMode == CombatMode::DuelCpu) {
        g_ReplayRecords.fileHeader.mode = 0;
        g_ReplayRecords.fileHeader.activeSide = g_SelectedSideAt006714B8;
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryFirstSpellCard = g_PlayerAltAt00671610[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primarySecondSpellCard = g_PlayerOtherAt006714CC[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerRoundAt006714AC[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryAutoGuard = g_PlayerDifficultyAt00671438[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryDamageSetting = g_PlayerSettingsAt00671434[g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.secondaryFighter = g_PlayerIdAt006714C8[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.secondaryFirstSpellCard = g_PlayerAltAt00671610[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.secondarySecondSpellCard = g_PlayerOtherAt006714CC[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.secondaryPalette = g_PlayerRoundAt006714AC[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.secondaryAutoGuard = g_PlayerDifficultyAt00671438[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.secondaryDamageSetting = g_PlayerSettingsAt00671434[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.recordHeader.stage = g_StageSelectionAt0067161D;
    } else if (g_CombatMode == CombatMode::DuelHuman) {
        g_ReplayRecords.fileHeader.mode = 0;
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[0];
        g_ReplayRecords.fileHeader.primaryFirstSpellCard = g_PlayerAltAt00671610[0];
        g_ReplayRecords.fileHeader.primarySecondSpellCard = g_PlayerOtherAt006714CC[0];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerRoundAt006714AC[0];
        g_ReplayRecords.fileHeader.primaryAutoGuard = g_PlayerDifficultyAt00671438[0];
        g_ReplayRecords.fileHeader.primaryDamageSetting = g_PlayerSettingsAt00671434[0];
        g_ReplayRecords.recordHeader.secondaryFighter = g_PlayerIdAt006714C8[1];
        g_ReplayRecords.recordHeader.secondaryFirstSpellCard = g_PlayerAltAt00671610[1];
        g_ReplayRecords.recordHeader.secondarySecondSpellCard = g_PlayerOtherAt006714CC[1];
        g_ReplayRecords.recordHeader.secondaryPalette = g_PlayerRoundAt006714AC[1];
        g_ReplayRecords.recordHeader.secondaryAutoGuard = g_PlayerDifficultyAt00671438[1];
        g_ReplayRecords.recordHeader.secondaryDamageSetting = g_PlayerSettingsAt00671434[1];
        g_ReplayRecords.fileHeader.activeSide = static_cast<unsigned char>(-1);
        g_ReplayRecords.recordHeader.stage = g_StageSelectionAt0067161D;
    } else if (g_CombatMode == CombatMode::Arcade) {
        g_ReplayRecords.fileHeader.mode = static_cast<unsigned char>(g_OptionsModeAt006714D0 + 5);
        g_ReplayRecords.fileHeader.activeSide = 0;
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[0];
        g_ReplayRecords.fileHeader.primaryFirstSpellCard = g_PlayerAltAt00671610[0];
        g_ReplayRecords.fileHeader.primarySecondSpellCard = g_PlayerOtherAt006714CC[0];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerRoundAt006714AC[0];
        g_ReplayRecords.fileHeader.primaryAutoGuard = g_PlayerDifficultyAt00671438[0];
        g_ReplayRecords.fileHeader.primaryDamageSetting = g_PlayerSettingsAt00671434[0];
        g_ReplayRecords.recordHeader.secondaryFighter = g_PlayerIdAt006714C8[1];
        g_ReplayRecords.recordHeader.secondaryFirstSpellCard = g_PlayerAltAt00671610[1];
        g_ReplayRecords.recordHeader.secondarySecondSpellCard = g_PlayerOtherAt006714CC[1];
        g_ReplayRecords.recordHeader.secondaryPalette = g_PlayerRoundAt006714AC[1];
        g_ReplayRecords.recordHeader.secondaryAutoGuard = g_PlayerDifficultyAt00671438[1];
        g_ReplayRecords.recordHeader.secondaryDamageSetting = g_PlayerSettingsAt00671434[1];
        g_ReplayRecords.recordHeader.startingScore =
            g_BattleFightersAt00671418[0]->score;
        g_ReplayRecords.recordHeader.stage = g_StageSelectionAt0067161D;
    } else if (g_CombatMode == CombatMode::Story) {
        g_ReplayRecords.fileHeader.mode = static_cast<unsigned char>(g_OptionsModeAt006714D0 + 1);
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[0];
        g_ReplayRecords.fileHeader.primaryFirstSpellCard = g_PlayerAltAt00671610[0];
        g_ReplayRecords.fileHeader.primarySecondSpellCard = g_PlayerOtherAt006714CC[0];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerRoundAt006714AC[0];
        g_ReplayRecords.recordHeader.secondaryFighter = g_PlayerIdAt006714C8[1];
        g_ReplayRecords.recordHeader.secondaryFirstSpellCard = g_PlayerAltAt00671610[1];
        g_ReplayRecords.recordHeader.secondarySecondSpellCard = g_PlayerOtherAt006714CC[1];
        g_ReplayRecords.recordHeader.secondaryPalette = g_PlayerRoundAt006714AC[1];
        g_ReplayRecords.fileHeader.activeSide = static_cast<unsigned char>(-1);
        g_ReplayRecords.recordHeader.startingHealth =
            g_BattleFightersAt00671418[0]->health;
        g_ReplayRecords.recordHeader.remainingLives = g_SequenceCounterAt00671622;
        g_ReplayRecords.recordHeader.startingScore =
            g_BattleFightersAt00671418[0]->score;
        g_ReplayRecords.recordHeader.stage = g_StageAt0067161E;
    }
}
}
