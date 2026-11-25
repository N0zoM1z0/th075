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
        if (fighters[1]->remainingSpellBonus > 0) {
            if (g_ReplayModeAt0066C238 == ReplayMode::Recording) {
                if (fighters[0]->field464 != 0)
                    CARD_RECORDS->MarkSpellCapture(
                        reinterpret_cast<signed char*>(fighters[1]->roundSpellRecordIds)[fighters[1]->roundsRemaining]);
                CARD_RECORDS->RecordSpellBonusClear(
                    reinterpret_cast<signed char*>(fighters[1]->roundSpellRecordIds)[fighters[1]->roundsRemaining]);
                if (fighters[1]->remainingSpellBonus > CARD_RECORDS->GetBestSpellBonus(
                        reinterpret_cast<signed char*>(fighters[1]->roundSpellRecordIds)[fighters[1]->roundsRemaining])) {
                    CARD_RECORDS->SetBestSpellBonus(
                        reinterpret_cast<signed char*>(fighters[1]->roundSpellRecordIds)[fighters[1]->roundsRemaining],
                        fighters[1]->remainingSpellBonus);
                }
            }
            g_ResultScoreTotalAt0067160C += fighters[1]->remainingSpellBonusFrames;
            fighters[0]->score = static_cast<int>(
                static_cast<unsigned long>(fighters[0]->score) + fighters[1]->remainingSpellBonus);
            if (fighters[0]->score > g_MaxCombatScore)
                g_MaxCombatScore = fighters[0]->score;
            spellBonusBannerFrames = 120;
            awardedSpellBonus = fighters[1]->remainingSpellBonus;
            fighters[1]->remainingSpellBonus = 0;
        }
        if (fighters[0]->spellTimer > 0)
            fighters[0]->spellPower = 0.0f;
        fighters[0]->spellTimer = 0;
        fighters[1]->spellTimer = 0;
        fighters[0]->spellDeclarationExpired = 0;
        fighters[1]->spellDeclarationExpired = 0;
        fighters[1]->roundsRemaining--;
        fighters[1]->field3CF = 0;
        fighters[1]->recoverableHealth = 0;
        fighters[0]->field464 = 1;
        if (fighters[0]->health <= 0)
            fighters[0]->health = 1;
        if (fighters[1]->roundsRemaining > 0) {
            battlePhase = BattlePhase::StoryRoundRecovery;
            phaseFrames = 147;
            if (reinterpret_cast<signed char*>(fighters[1]->roundKind + 1)[fighters[1]->roundsRemaining] == 0) {
                fighters[1]->health = fighters[1]->healthLimits[fighters[1]->roundsRemaining];
                fighters[1]->recoverableHealth = fighters[1]->healthLimits[fighters[1]->roundsRemaining];
                fighters[1]->remainingSpellBonusFrames = 0;
            }
        } else {
            battlePhase = BattlePhase::StoryMatchKnockout;
            phaseFrames = 180;
            knockoutFreezeFrames = 60;
        }
    } else if (fighters[0]->health <= 0) {
        fighters[1]->recoverableHealth = fighters[1]->healthLimits[fighters[1]->roundsRemaining];
        fighters[0]->spellTimer = 0;
        fighters[0]->spellDeclarationExpired = 0;
        fighters[0]->roundsRemaining--;
        fighters[0]->field3CE.unsignedAt3CE = 1;
        fighters[1]->field3CE.unsignedAt3CE = 0;
        fighters[0]->field3CF = 0;
        fighters[0]->field464 = 0;
        if (fighters[0]->roundsRemaining != 0) {
            fighters[0]->recoverableHealth = 10000;
            fighters[0]->health = 10000;
            battlePhase = BattlePhase::StoryRoundKnockout;
            phaseFrames = 300;
            knockoutFreezeFrames = 60;
        } else if (static_cast<signed char>(g_SequenceCounterAt00671622) > 0) {
            g_SequenceCounterAt00671622--;
            fighters[0]->roundsRemaining = 2;
            battlePhase = BattlePhase::StoryRoundKnockout;
            phaseFrames = 300;
            knockoutFreezeFrames = 60;
        } else {
            battlePhase = BattlePhase::StoryMatchKnockout;
            phaseFrames = 180;
            knockoutFreezeFrames = 60;
        }
    }
}

#undef CARD_RECORDS
