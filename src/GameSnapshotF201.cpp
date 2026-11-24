#include "PlayerState.hpp"
#include "ReplaySegmentedQueueF219.hpp"
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "GameSnapshot.hpp"
#include <windows.h>
#include "Fighter.hpp"

// Storage anchors are only address-compatible borrowed views. This function
// never constructs or embeds an assumed original game-state owner.

namespace GameStateF201 {
void SaveSnapshot()
{
    if (g_CombatMode == 1) {
        g_ReplayRecords.fileHeader.mode = 0;
        g_ReplayRecords.fileHeader.activeSide = g_SelectedSideAt006714B8;
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerAltAt00671610[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryFlags = g_PlayerOtherAt006714CC[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryRound = g_PlayerRoundAt006714AC[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primaryDifficulty = g_PlayerDifficultyAt00671438[g_SelectedSideAt006714B8];
        g_ReplayRecords.fileHeader.primarySettings = g_PlayerSettingsAt00671434[g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field144 = g_PlayerIdAt006714C8[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field145 = g_PlayerAltAt00671610[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field146 = g_PlayerOtherAt006714CC[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field147 = g_PlayerRoundAt006714AC[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field148 = g_PlayerDifficultyAt00671438[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field149 = g_PlayerSettingsAt00671434[1 - g_SelectedSideAt006714B8];
        g_ReplayRecords.header.field14A = g_StageSelectionAt0067161D;
    } else if (g_CombatMode == 2) {
        g_ReplayRecords.fileHeader.mode = 0;
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[0];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerAltAt00671610[0];
        g_ReplayRecords.fileHeader.primaryFlags = g_PlayerOtherAt006714CC[0];
        g_ReplayRecords.fileHeader.primaryRound = g_PlayerRoundAt006714AC[0];
        g_ReplayRecords.fileHeader.primaryDifficulty = g_PlayerDifficultyAt00671438[0];
        g_ReplayRecords.fileHeader.primarySettings = g_PlayerSettingsAt00671434[0];
        g_ReplayRecords.header.field144 = g_PlayerIdAt006714C8[1];
        g_ReplayRecords.header.field145 = g_PlayerAltAt00671610[1];
        g_ReplayRecords.header.field146 = g_PlayerOtherAt006714CC[1];
        g_ReplayRecords.header.field147 = g_PlayerRoundAt006714AC[1];
        g_ReplayRecords.header.field148 = g_PlayerDifficultyAt00671438[1];
        g_ReplayRecords.header.field149 = g_PlayerSettingsAt00671434[1];
        g_ReplayRecords.fileHeader.activeSide = static_cast<unsigned char>(-1);
        g_ReplayRecords.header.field14A = g_StageSelectionAt0067161D;
    } else if (g_CombatMode == 4) {
        g_ReplayRecords.fileHeader.mode = static_cast<unsigned char>(g_OptionsModeAt006714D0 + 5);
        g_ReplayRecords.fileHeader.activeSide = 0;
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[0];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerAltAt00671610[0];
        g_ReplayRecords.fileHeader.primaryFlags = g_PlayerOtherAt006714CC[0];
        g_ReplayRecords.fileHeader.primaryRound = g_PlayerRoundAt006714AC[0];
        g_ReplayRecords.fileHeader.primaryDifficulty = g_PlayerDifficultyAt00671438[0];
        g_ReplayRecords.fileHeader.primarySettings = g_PlayerSettingsAt00671434[0];
        g_ReplayRecords.header.field144 = g_PlayerIdAt006714C8[1];
        g_ReplayRecords.header.field145 = g_PlayerAltAt00671610[1];
        g_ReplayRecords.header.field146 = g_PlayerOtherAt006714CC[1];
        g_ReplayRecords.header.field147 = g_PlayerRoundAt006714AC[1];
        g_ReplayRecords.header.field148 = g_PlayerDifficultyAt00671438[1];
        g_ReplayRecords.header.field149 = g_PlayerSettingsAt00671434[1];
        g_ReplayRecords.header.field150 =
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score;
        g_ReplayRecords.header.field14A = g_StageSelectionAt0067161D;
    } else if (g_CombatMode == 3) {
        g_ReplayRecords.fileHeader.mode = static_cast<unsigned char>(g_OptionsModeAt006714D0 + 1);
        g_ReplayRecords.fileHeader.primaryFighter = g_PlayerIdAt006714C8[0];
        g_ReplayRecords.fileHeader.primaryPalette = g_PlayerAltAt00671610[0];
        g_ReplayRecords.fileHeader.primaryFlags = g_PlayerOtherAt006714CC[0];
        g_ReplayRecords.fileHeader.primaryRound = g_PlayerRoundAt006714AC[0];
        g_ReplayRecords.header.field144 = g_PlayerIdAt006714C8[1];
        g_ReplayRecords.header.field145 = g_PlayerAltAt00671610[1];
        g_ReplayRecords.header.field146 = g_PlayerOtherAt006714CC[1];
        g_ReplayRecords.header.field147 = g_PlayerRoundAt006714AC[1];
        g_ReplayRecords.fileHeader.activeSide = static_cast<unsigned char>(-1);
        g_ReplayRecords.header.field14C =
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->health;
        g_ReplayRecords.header.field14E = g_SequenceCounterAt00671622;
        g_ReplayRecords.header.field150 =
            reinterpret_cast<Fighter*>(g_BattleFightersAt00671418[0])->score;
        g_ReplayRecords.header.field14A = g_StageAt0067161E;
    }
}
}
