#include "replay/ReplayMode.hpp"
#include "battle/BattleResultState.hpp"
#include "battle/BattleSessionState.hpp"
#include "engine/GameProgress.hpp"
#include "battle/KnockoutProgressF172.hpp"
#include "battle/BattleScene.hpp"
#include "battle/FighterResourceParameters452B30.hpp"

// Existing byte storage keeps its canonical unsigned carrier. The continuation
// test below explicitly uses the signed byte interpretation observed here.
// Observed dword accumulation; original name and signedness remain unknown.

#define CARD_RECORDS (&g_GameProgress)

void GameProgress::MarkSpellCapture(signed char key)
{
    characters[selectedFighter].difficulties[0].spellCaptureFlags[key] = 1;
}

void GameProgress::RecordSpellBonusClear(signed char key)
{
    characters[selectedFighter].difficulties[0].spellBonusClears[key]++;
}

int GameProgress::GetBestSpellBonus(signed char key)
{
    return characters[selectedFighter].difficulties[0].bestSpellBonus[key];
}

void GameProgress::SetBestSpellBonus(signed char key, int value)
{
    characters[selectedFighter].difficulties[0].bestSpellBonus[key] = value;
}

void BattleScene::ResolveKnockout()
{
    if (fighters[1]->health <= 0) {
        fighters[0]->field3CE.unsignedAt3CE = 0;
        fighters[1]->field3CE.unsignedAt3CE = 1;
        if (fighters[1]->field3A4 > 0) {
            if (g_ReplayModeAt0066C238 == ReplayMode::Recording) {
                if (fighters[0]->field464 != 0)
                    CARD_RECORDS->MarkSpellCapture(
                        reinterpret_cast<signed char*>(fighters[1]->field384)[fighters[1]->field39D]);
                CARD_RECORDS->RecordSpellBonusClear(
                    reinterpret_cast<signed char*>(fighters[1]->field384)[fighters[1]->field39D]);
                if (fighters[1]->field3A4 > CARD_RECORDS->GetBestSpellBonus(
                        reinterpret_cast<signed char*>(fighters[1]->field384)[fighters[1]->field39D])) {
                    CARD_RECORDS->SetBestSpellBonus(
                        reinterpret_cast<signed char*>(fighters[1]->field384)[fighters[1]->field39D],
                        fighters[1]->field3A4);
                }
            }
            g_ResultScoreTotalAt0067160C += fighters[1]->field3A8;
            fighters[0]->score = static_cast<int>(
                static_cast<unsigned long>(fighters[0]->score) + fighters[1]->field3A4);
            if (fighters[0]->score > g_MaxCombatScore)
                g_MaxCombatScore = fighters[0]->score;
            field06C = 120;
            field068 = fighters[1]->field3A4;
            fighters[1]->field3A4 = 0;
        }
        if (fighters[0]->spellTimer > 0)
            fighters[0]->spellPower = 0.0f;
        fighters[0]->spellTimer = 0;
        fighters[1]->spellTimer = 0;
        fighters[0]->spellDeclarationExpired = 0;
        fighters[1]->spellDeclarationExpired = 0;
        fighters[1]->field39D--;
        fighters[1]->field3CF = 0;
        fighters[1]->recoverableHealth = 0;
        fighters[0]->field464 = 1;
        if (fighters[0]->health <= 0)
            fighters[0]->health = 1;
        if (fighters[1]->field39D > 0) {
            field018 = 9;
            field00C = 147;
            if (reinterpret_cast<signed char*>(fighters[1]->field32A + 1)[fighters[1]->field39D] == 0) {
                fighters[1]->health = fighters[1]->healthLimits[fighters[1]->field39D];
                fighters[1]->recoverableHealth = fighters[1]->healthLimits[fighters[1]->field39D];
                fighters[1]->field3A8 = 0;
            }
        } else {
            field018 = 11;
            field00C = 180;
            field01A = 60;
        }
    } else if (fighters[0]->health <= 0) {
        fighters[1]->recoverableHealth = fighters[1]->healthLimits[fighters[1]->field39D];
        fighters[0]->spellTimer = 0;
        fighters[0]->spellDeclarationExpired = 0;
        fighters[0]->field39D--;
        fighters[0]->field3CE.unsignedAt3CE = 1;
        fighters[1]->field3CE.unsignedAt3CE = 0;
        fighters[0]->field3CF = 0;
        fighters[0]->field464 = 0;
        if (fighters[0]->field39D != 0) {
            fighters[0]->recoverableHealth = 10000;
            fighters[0]->health = 10000;
            field018 = 10;
            field00C = 300;
            field01A = 60;
        } else if (static_cast<signed char>(g_SequenceCounterAt00671622) > 0) {
            g_SequenceCounterAt00671622--;
            fighters[0]->field39D = 2;
            field018 = 10;
            field00C = 300;
            field01A = 60;
        } else {
            field018 = 11;
            field00C = 180;
            field01A = 60;
        }
    }
}

#undef CARD_RECORDS
