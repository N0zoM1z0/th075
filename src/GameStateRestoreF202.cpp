#include "ReplaySegmentedQueueF219.hpp"
#include "BattleSessionState.hpp"
#include "GameSharedState.hpp"
#include "GameSnapshot.hpp"
#include <windows.h>

extern short g_RecordSequenceAt006714A4;
extern unsigned char g_PlayerIdAt006714C8[];
extern unsigned char g_PlayerAltAt00671610[];
extern unsigned char g_PlayerOtherAt006714CC[];
extern unsigned char g_PlayerRoundAt006714AC[];
extern unsigned char g_PlayerDifficultyAt00671438[];
extern unsigned char g_PlayerSettingsAt00671434[];

namespace GameStateF202 {
void RestoreFromSnapshot()
{
    g_ReplayRecords.ReadSnapshotHeader();
    if (static_cast<signed char>(g_ReplayRecords.fileHeader.mode) == 0) {
        g_ReplayRecords.LoadRecord(0);
        if (static_cast<signed char>(g_ReplayRecords.fileHeader.activeSide) >= 0) {
            g_CombatMode = 1;
            g_SelectedSideAt006714B8 = g_ReplayRecords.fileHeader.activeSide;
            g_PlayerIdAt006714C8[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryFighter;
            g_PlayerAltAt00671610[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryPalette;
            g_PlayerOtherAt006714CC[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryFlags;
            g_PlayerRoundAt006714AC[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryRound;
            g_PlayerDifficultyAt00671438[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primaryDifficulty;
            g_PlayerSettingsAt00671434[g_SelectedSideAt006714B8] = g_ReplayRecords.fileHeader.primarySettings;
            g_PlayerIdAt006714C8[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.header.field144;
            g_PlayerAltAt00671610[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.header.field145;
            g_PlayerOtherAt006714CC[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.header.field146;
            g_PlayerRoundAt006714AC[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.header.field147;
            g_PlayerDifficultyAt00671438[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.header.field148;
            g_PlayerSettingsAt00671434[1 - g_SelectedSideAt006714B8] = g_ReplayRecords.header.field149;
        } else {
            g_CombatMode = 2;
            g_PlayerIdAt006714C8[0] = g_ReplayRecords.fileHeader.primaryFighter;
            g_PlayerAltAt00671610[0] = g_ReplayRecords.fileHeader.primaryPalette;
            g_PlayerOtherAt006714CC[0] = g_ReplayRecords.fileHeader.primaryFlags;
            g_PlayerRoundAt006714AC[0] = g_ReplayRecords.fileHeader.primaryRound;
            g_PlayerDifficultyAt00671438[0] = g_ReplayRecords.fileHeader.primaryDifficulty;
            g_PlayerSettingsAt00671434[0] = g_ReplayRecords.fileHeader.primarySettings;
            g_PlayerIdAt006714C8[1] = g_ReplayRecords.header.field144;
            g_PlayerAltAt00671610[1] = g_ReplayRecords.header.field145;
            g_PlayerOtherAt006714CC[1] = g_ReplayRecords.header.field146;
            g_PlayerRoundAt006714AC[1] = g_ReplayRecords.header.field147;
            g_PlayerDifficultyAt00671438[1] = g_ReplayRecords.header.field148;
            g_PlayerSettingsAt00671434[1] = g_ReplayRecords.header.field149;
        }
        g_StageSelectionAt0067161D = g_ReplayRecords.header.field14A;
    } else if (static_cast<signed char>(g_ReplayRecords.fileHeader.mode) >= 5) {
        g_ReplayRecords.LoadRecord(g_RecordSequenceAt006714A4 - 1);
        ++g_RecordSequenceAt006714A4;
        g_OptionsModeAt006714D0 = static_cast<signed char>(g_ReplayRecords.fileHeader.mode) - 5;
        g_CombatMode = 4;
        g_SelectedSideAt006714B8 = 0;
        g_PlayerIdAt006714C8[0] = g_ReplayRecords.fileHeader.primaryFighter;
        g_PlayerAltAt00671610[0] = g_ReplayRecords.fileHeader.primaryPalette;
        g_PlayerOtherAt006714CC[0] = g_ReplayRecords.fileHeader.primaryFlags;
        g_PlayerRoundAt006714AC[0] = g_ReplayRecords.fileHeader.primaryRound;
        g_PlayerDifficultyAt00671438[0] = g_ReplayRecords.fileHeader.primaryDifficulty;
        g_PlayerSettingsAt00671434[0] = g_ReplayRecords.fileHeader.primarySettings;
        g_PlayerIdAt006714C8[1] = g_ReplayRecords.header.field144;
        g_PlayerAltAt00671610[1] = g_ReplayRecords.header.field145;
        g_PlayerOtherAt006714CC[1] = g_ReplayRecords.header.field146;
        g_PlayerRoundAt006714AC[1] = g_ReplayRecords.header.field147;
        g_PlayerDifficultyAt00671438[1] = g_ReplayRecords.header.field148;
        g_PlayerSettingsAt00671434[1] = g_ReplayRecords.header.field149;
        g_StageSelectionAt0067161D = g_ReplayRecords.header.field14A;
    } else {
        g_SelectedSideAt006714B8 = 0;
        g_ReplayRecords.LoadRecord(g_RecordSequenceAt006714A4 - 1);
        ++g_RecordSequenceAt006714A4;
        g_CombatMode = 3;
        g_OptionsModeAt006714D0 = static_cast<signed char>(g_ReplayRecords.fileHeader.mode) - 1;
        g_PlayerIdAt006714C8[0] = g_ReplayRecords.fileHeader.primaryFighter;
        g_PlayerAltAt00671610[0] = g_ReplayRecords.fileHeader.primaryPalette;
        g_PlayerOtherAt006714CC[0] = g_ReplayRecords.fileHeader.primaryFlags;
        g_PlayerRoundAt006714AC[0] = g_ReplayRecords.fileHeader.primaryRound;
        g_StageAt0067161E = g_ReplayRecords.header.field14A;
        g_SequenceCounterAt00671622 = g_ReplayRecords.header.field14E;
    }
}
}
