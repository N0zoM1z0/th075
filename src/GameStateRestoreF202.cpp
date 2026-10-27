#include <windows.h>

// The archive receiver and global player/snapshot bytes are borrowed anchor
// declarations only. No complete original scene or serialization layout.
class SnapshotArchiveF202 {
public:
    void ReadSnapshotHeader();
    void LoadRecord(int number);
};
extern SnapshotArchiveF202 g_SnapshotArchiveAt00671750;
extern signed char g_CombatModeAt006714B4;
extern signed char g_SelectedSideAt006714B8;
extern signed char g_OptionsModeAt006714D0;
extern short g_RecordSequenceAt006714A4;
extern unsigned char g_PlayerIdAt006714C8[];
extern unsigned char g_PlayerAltAt00671610[];
extern unsigned char g_PlayerOtherAt006714CC[];
extern unsigned char g_PlayerRoundAt006714AC[];
extern unsigned char g_PlayerDifficultyAt00671438[];
extern unsigned char g_PlayerSettingsAt00671434[];
extern unsigned char g_SnapshotAt00671862[];
extern unsigned char g_StageAt0067161D;
extern unsigned char g_ExtraStageAt0067161E;
extern unsigned char g_StageFlagAt00671622;

#define SNAP(off) g_SnapshotAt00671862[(off)]
namespace GameStateF202 {
void RestoreFromSnapshot()
{
    g_SnapshotArchiveAt00671750.ReadSnapshotHeader();
    if (static_cast<signed char>(SNAP(3)) == 0) {
        g_SnapshotArchiveAt00671750.LoadRecord(0);
        if (static_cast<signed char>(SNAP(5)) >= 0) {
            g_CombatModeAt006714B4 = 1;
            g_SelectedSideAt006714B8 = SNAP(5);
            g_PlayerIdAt006714C8[g_SelectedSideAt006714B8] = SNAP(0);
            g_PlayerAltAt00671610[g_SelectedSideAt006714B8] = SNAP(1);
            g_PlayerOtherAt006714CC[g_SelectedSideAt006714B8] = SNAP(2);
            g_PlayerRoundAt006714AC[g_SelectedSideAt006714B8] = SNAP(6);
            g_PlayerDifficultyAt00671438[g_SelectedSideAt006714B8] = SNAP(7);
            g_PlayerSettingsAt00671434[g_SelectedSideAt006714B8] = SNAP(8);
            g_PlayerIdAt006714C8[1 - g_SelectedSideAt006714B8] = SNAP(0x32);
            g_PlayerAltAt00671610[1 - g_SelectedSideAt006714B8] = SNAP(0x33);
            g_PlayerOtherAt006714CC[1 - g_SelectedSideAt006714B8] = SNAP(0x34);
            g_PlayerRoundAt006714AC[1 - g_SelectedSideAt006714B8] = SNAP(0x35);
            g_PlayerDifficultyAt00671438[1 - g_SelectedSideAt006714B8] = SNAP(0x36);
            g_PlayerSettingsAt00671434[1 - g_SelectedSideAt006714B8] = SNAP(0x37);
        } else {
            g_CombatModeAt006714B4 = 2;
            g_PlayerIdAt006714C8[0] = SNAP(0);
            g_PlayerAltAt00671610[0] = SNAP(1);
            g_PlayerOtherAt006714CC[0] = SNAP(2);
            g_PlayerRoundAt006714AC[0] = SNAP(6);
            g_PlayerDifficultyAt00671438[0] = SNAP(7);
            g_PlayerSettingsAt00671434[0] = SNAP(8);
            g_PlayerIdAt006714C8[1] = SNAP(0x32);
            g_PlayerAltAt00671610[1] = SNAP(0x33);
            g_PlayerOtherAt006714CC[1] = SNAP(0x34);
            g_PlayerRoundAt006714AC[1] = SNAP(0x35);
            g_PlayerDifficultyAt00671438[1] = SNAP(0x36);
            g_PlayerSettingsAt00671434[1] = SNAP(0x37);
        }
        g_StageAt0067161D = SNAP(0x38);
    } else if (static_cast<signed char>(SNAP(3)) >= 5) {
        g_SnapshotArchiveAt00671750.LoadRecord(g_RecordSequenceAt006714A4 - 1);
        ++g_RecordSequenceAt006714A4;
        g_OptionsModeAt006714D0 = static_cast<signed char>(SNAP(3)) - 5;
        g_CombatModeAt006714B4 = 4;
        g_SelectedSideAt006714B8 = 0;
        g_PlayerIdAt006714C8[0] = SNAP(0);
        g_PlayerAltAt00671610[0] = SNAP(1);
        g_PlayerOtherAt006714CC[0] = SNAP(2);
        g_PlayerRoundAt006714AC[0] = SNAP(6);
        g_PlayerDifficultyAt00671438[0] = SNAP(7);
        g_PlayerSettingsAt00671434[0] = SNAP(8);
        g_PlayerIdAt006714C8[1] = SNAP(0x32);
        g_PlayerAltAt00671610[1] = SNAP(0x33);
        g_PlayerOtherAt006714CC[1] = SNAP(0x34);
        g_PlayerRoundAt006714AC[1] = SNAP(0x35);
        g_PlayerDifficultyAt00671438[1] = SNAP(0x36);
        g_PlayerSettingsAt00671434[1] = SNAP(0x37);
        g_StageAt0067161D = SNAP(0x38);
    } else {
        g_SelectedSideAt006714B8 = 0;
        g_SnapshotArchiveAt00671750.LoadRecord(g_RecordSequenceAt006714A4 - 1);
        ++g_RecordSequenceAt006714A4;
        g_CombatModeAt006714B4 = 3;
        g_OptionsModeAt006714D0 = static_cast<signed char>(SNAP(3)) - 1;
        g_PlayerIdAt006714C8[0] = SNAP(0);
        g_PlayerAltAt00671610[0] = SNAP(1);
        g_PlayerOtherAt006714CC[0] = SNAP(2);
        g_PlayerRoundAt006714AC[0] = SNAP(6);
        g_ExtraStageAt0067161E = SNAP(0x38);
        g_StageFlagAt00671622 = SNAP(0x3c);
    }
}
}
#undef SNAP
