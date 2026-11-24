#include "GameSharedState.hpp"
#include "GameSnapshot.hpp"
#include <windows.h>
#include "Fighter.hpp"

// Storage anchors are only address-compatible borrowed views. This function
// never constructs or embeds an assumed original game-state owner.
extern signed char g_SelectedSideAt006714B8;
extern unsigned char g_PlayerIdAt006714C8[];
extern unsigned char g_PlayerAltAt00671610[];
extern unsigned char g_PlayerOtherAt006714CC[];
extern unsigned char g_PlayerRoundAt006714AC[];
extern unsigned char g_PlayerDifficultyAt00671438[];
extern unsigned char g_PlayerSettingsAt00671434[];
extern unsigned char g_SnapshotAt00671862[];
extern unsigned char g_StageAt0067161D;
extern unsigned char g_StageFlagAt00671622;
extern unsigned char* g_ActorAt00671418;

#define DST(off) g_SnapshotAt00671862[(off)]
namespace GameStateF201 {
void SaveSnapshot()
{
    if (g_CombatMode == 1) {
        DST(3) = 0;
        DST(5) = g_SelectedSideAt006714B8;
        DST(0) = g_PlayerIdAt006714C8[g_SelectedSideAt006714B8];
        DST(1) = g_PlayerAltAt00671610[g_SelectedSideAt006714B8];
        DST(2) = g_PlayerOtherAt006714CC[g_SelectedSideAt006714B8];
        DST(6) = g_PlayerRoundAt006714AC[g_SelectedSideAt006714B8];
        DST(7) = g_PlayerDifficultyAt00671438[g_SelectedSideAt006714B8];
        DST(8) = g_PlayerSettingsAt00671434[g_SelectedSideAt006714B8];
        DST(0x32) = g_PlayerIdAt006714C8[1 - g_SelectedSideAt006714B8];
        DST(0x33) = g_PlayerAltAt00671610[1 - g_SelectedSideAt006714B8];
        DST(0x34) = g_PlayerOtherAt006714CC[1 - g_SelectedSideAt006714B8];
        DST(0x35) = g_PlayerRoundAt006714AC[1 - g_SelectedSideAt006714B8];
        DST(0x36) = g_PlayerDifficultyAt00671438[1 - g_SelectedSideAt006714B8];
        DST(0x37) = g_PlayerSettingsAt00671434[1 - g_SelectedSideAt006714B8];
        DST(0x38) = g_StageAt0067161D;
    } else if (g_CombatMode == 2) {
        DST(3) = 0;
        DST(0) = g_PlayerIdAt006714C8[0];
        DST(1) = g_PlayerAltAt00671610[0];
        DST(2) = g_PlayerOtherAt006714CC[0];
        DST(6) = g_PlayerRoundAt006714AC[0];
        DST(7) = g_PlayerDifficultyAt00671438[0];
        DST(8) = g_PlayerSettingsAt00671434[0];
        DST(0x32) = g_PlayerIdAt006714C8[1];
        DST(0x33) = g_PlayerAltAt00671610[1];
        DST(0x34) = g_PlayerOtherAt006714CC[1];
        DST(0x35) = g_PlayerRoundAt006714AC[1];
        DST(0x36) = g_PlayerDifficultyAt00671438[1];
        DST(0x37) = g_PlayerSettingsAt00671434[1];
        DST(5) = static_cast<unsigned char>(-1);
        DST(0x38) = g_StageAt0067161D;
    } else if (g_CombatMode == 4) {
        DST(3) = static_cast<unsigned char>(g_OptionsModeAt006714D0 + 5);
        DST(5) = 0;
        DST(0) = g_PlayerIdAt006714C8[0];
        DST(1) = g_PlayerAltAt00671610[0];
        DST(2) = g_PlayerOtherAt006714CC[0];
        DST(6) = g_PlayerRoundAt006714AC[0];
        DST(7) = g_PlayerDifficultyAt00671438[0];
        DST(8) = g_PlayerSettingsAt00671434[0];
        DST(0x32) = g_PlayerIdAt006714C8[1];
        DST(0x33) = g_PlayerAltAt00671610[1];
        DST(0x34) = g_PlayerOtherAt006714CC[1];
        DST(0x35) = g_PlayerRoundAt006714AC[1];
        DST(0x36) = g_PlayerDifficultyAt00671438[1];
        DST(0x37) = g_PlayerSettingsAt00671434[1];
        *reinterpret_cast<DWORD*>(&DST(0x3e)) =
            reinterpret_cast<Fighter*>(g_ActorAt00671418)->score;
        DST(0x38) = g_StageAt0067161D;
    } else if (g_CombatMode == 3) {
        DST(3) = static_cast<unsigned char>(g_OptionsModeAt006714D0 + 1);
        DST(0) = g_PlayerIdAt006714C8[0];
        DST(1) = g_PlayerAltAt00671610[0];
        DST(2) = g_PlayerOtherAt006714CC[0];
        DST(6) = g_PlayerRoundAt006714AC[0];
        DST(0x32) = g_PlayerIdAt006714C8[1];
        DST(0x33) = g_PlayerAltAt00671610[1];
        DST(0x34) = g_PlayerOtherAt006714CC[1];
        DST(0x35) = g_PlayerRoundAt006714AC[1];
        DST(5) = static_cast<unsigned char>(-1);
        *reinterpret_cast<unsigned short*>(&DST(0x3a)) =
            reinterpret_cast<Fighter*>(g_ActorAt00671418)->health;
        DST(0x3c) = g_StageFlagAt00671622;
        *reinterpret_cast<DWORD*>(&DST(0x3e)) =
            reinterpret_cast<Fighter*>(g_ActorAt00671418)->score;
        DST(0x38) = g_StageAt0067161E;
    }
}
}
#undef DST
