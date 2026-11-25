#include "battle/CombatMode.hpp"
#include "battle/PlayerState.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameSharedState.hpp"
#include "engine/GameSnapshot.hpp"
#include <windows.h>


namespace GameStateF202 {
void RestoreFromSnapshot()
{
    g_ReplayRecords.ReadSnapshotHeader();
    if (static_cast<signed char>(g_ReplayRecords.fileHeader.mode) == 0) {
        g_ReplayRecords.LoadRecord(0);
        if (static_cast<signed char>(g_ReplayRecords.fileHeader.activeSide) >= 0) {
            g_CombatMode = CombatMode::DuelCpu;
            g_SelectedSideAt006714B8 = g_ReplayRecords.fileHeader.activeSide;
            g_PlayerIdAt006714C8[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryFighter;
            g_PlayerAltAt00671610[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryFirstSpellCard;
            g_PlayerOtherAt006714CC[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primarySecondSpellCard;
            g_PlayerRoundAt006714AC[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryPalette;
            g_PlayerDifficultyAt00671438[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryAutoGuard;
            g_PlayerSettingsAt00671434[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryDamageSetting;
            g_PlayerIdAt006714C8[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.recordHeader.secondaryFighter;
            g_PlayerAltAt00671610[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.recordHeader.secondaryFirstSpellCard;
            g_PlayerOtherAt006714CC[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.recordHeader.secondarySecondSpellCard;
            g_PlayerRoundAt006714AC[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.recordHeader.secondaryPalette;
            g_PlayerDifficultyAt00671438[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.recordHeader.secondaryAutoGuard;
            g_PlayerSettingsAt00671434[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.recordHeader.secondaryDamageSetting;
        } else {
            g_CombatMode = CombatMode::DuelHuman;
            g_PlayerIdAt006714C8[0] = g_ReplayRecords.fileHeader.primaryFighter;
            g_PlayerAltAt00671610[0] = g_ReplayRecords.fileHeader.primaryFirstSpellCard;
            g_PlayerOtherAt006714CC[0] = g_ReplayRecords.fileHeader.primarySecondSpellCard;
            g_PlayerRoundAt006714AC[0] = g_ReplayRecords.fileHeader.primaryPalette;
            g_PlayerDifficultyAt00671438[0] = g_ReplayRecords.fileHeader.primaryAutoGuard;
            g_PlayerSettingsAt00671434[0] = g_ReplayRecords.fileHeader.primaryDamageSetting;
            g_PlayerIdAt006714C8[1] = g_ReplayRecords.recordHeader.secondaryFighter;
            g_PlayerAltAt00671610[1] = g_ReplayRecords.recordHeader.secondaryFirstSpellCard;
            g_PlayerOtherAt006714CC[1] = g_ReplayRecords.recordHeader.secondarySecondSpellCard;
            g_PlayerRoundAt006714AC[1] = g_ReplayRecords.recordHeader.secondaryPalette;
            g_PlayerDifficultyAt00671438[1] = g_ReplayRecords.recordHeader.secondaryAutoGuard;
            g_PlayerSettingsAt00671434[1] = g_ReplayRecords.recordHeader.secondaryDamageSetting;
        }
        g_StageSelectionAt0067161D = g_ReplayRecords.recordHeader.stage;
    } else if (static_cast<signed char>(g_ReplayRecords.fileHeader.mode) >= 5) {
        g_ReplayRecords.LoadRecord(g_RecordSequenceAt006714A4 - 1);
        ++g_RecordSequenceAt006714A4;
        g_OptionsModeAt006714D0 = static_cast<signed char>(g_ReplayRecords.fileHeader.mode) - 5;
        g_CombatMode = CombatMode::Arcade;
        g_SelectedSideAt006714B8 = 0;
        g_PlayerIdAt006714C8[0] = g_ReplayRecords.fileHeader.primaryFighter;
        g_PlayerAltAt00671610[0] = g_ReplayRecords.fileHeader.primaryFirstSpellCard;
        g_PlayerOtherAt006714CC[0] = g_ReplayRecords.fileHeader.primarySecondSpellCard;
        g_PlayerRoundAt006714AC[0] = g_ReplayRecords.fileHeader.primaryPalette;
        g_PlayerDifficultyAt00671438[0] = g_ReplayRecords.fileHeader.primaryAutoGuard;
        g_PlayerSettingsAt00671434[0] = g_ReplayRecords.fileHeader.primaryDamageSetting;
        g_PlayerIdAt006714C8[1] = g_ReplayRecords.recordHeader.secondaryFighter;
        g_PlayerAltAt00671610[1] = g_ReplayRecords.recordHeader.secondaryFirstSpellCard;
        g_PlayerOtherAt006714CC[1] = g_ReplayRecords.recordHeader.secondarySecondSpellCard;
        g_PlayerRoundAt006714AC[1] = g_ReplayRecords.recordHeader.secondaryPalette;
        g_PlayerDifficultyAt00671438[1] = g_ReplayRecords.recordHeader.secondaryAutoGuard;
        g_PlayerSettingsAt00671434[1] = g_ReplayRecords.recordHeader.secondaryDamageSetting;
        g_StageSelectionAt0067161D = g_ReplayRecords.recordHeader.stage;
    } else {
        g_SelectedSideAt006714B8 = 0;
        g_ReplayRecords.LoadRecord(g_RecordSequenceAt006714A4 - 1);
        ++g_RecordSequenceAt006714A4;
        g_CombatMode = CombatMode::Story;
        g_OptionsModeAt006714D0 = static_cast<signed char>(g_ReplayRecords.fileHeader.mode) - 1;
        g_PlayerIdAt006714C8[0] = g_ReplayRecords.fileHeader.primaryFighter;
        g_PlayerAltAt00671610[0] = g_ReplayRecords.fileHeader.primaryFirstSpellCard;
        g_PlayerOtherAt006714CC[0] = g_ReplayRecords.fileHeader.primarySecondSpellCard;
        g_PlayerRoundAt006714AC[0] = g_ReplayRecords.fileHeader.primaryPalette;
        g_StageAt0067161E = g_ReplayRecords.recordHeader.stage;
        g_SequenceCounterAt00671622 = g_ReplayRecords.recordHeader.remainingLives;
    }
}
}
