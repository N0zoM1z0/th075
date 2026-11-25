#include "battle/CombatMode.hpp"
#include "engine/GameSharedState.hpp"
#include "battle/CombatTimers.hpp"
void Fighter::UpdateCounters()
{
    // Opponent freeze suspends counters but not view bounds and the frame count.
    if (opponent->opponentFreezeSnapshot > 0) goto updateViewBounds;
    {
        if (field082 > 0) --field082;
        else if (field3CC > 0) --field3CC;
        field490 = 0.0f;
        opponent->field490 = 0.0f;
        if (field084 > 0) --field084;
        if (field086 > 0) --field086;
        if (frameInfo->flags & 0x1000) field086 = 6;
        if (field088 > 0) --field088;
        if (guardResponseCooldown > 0) --guardResponseCooldown;
        if (spellTimer > 0) {
            if (cpuControlled == 0 || g_CombatMode != CombatMode::Story) {
                spellTimer -= 2;
                if (spellTimer <= 0) {
                    spellTimer = 0;
                    spellDeclarationExpired = 1;
                    spellPower = 0.0f;
                }
            } else {
                field3A4 -= static_cast<int>(field430[field39D]);
                if (field3A4 < 0) field3A4 = 0;
                --field3A8;
                if (field3A8 < 0) field3A8 = 0;
            }
        }
        if (pendingSpellCharge > 0.0f && spellDeclarationExpired == 0) {
            if (spellTimer != 0) {
                pendingSpellCharge -= 0.4f;
                spellPower += 0.02f;
            } else {
                pendingSpellCharge -= 4.0f;
                spellPower += 0.2f;
            }
        }
        if (spellPower < 0.0f) spellPower = 0.0f;
        if (spellPower > 900.0f) spellPower = 900.0f;
        if (pendingSpellCharge < 0.0f) pendingSpellCharge = 0.0f;
        if (pendingSpellCharge > 1000.0f) pendingSpellCharge = 1000.0f;
        if (g_CombatMode == CombatMode::Story && cpuControlled != 0) spellPower = 900.0f;
        if (g_CombatMode != CombatMode::Story || cpuControlled == 0) {
            if (spellTimer > 0 && recoverableHealth > health) health += 100;
            if (recoverableHealth < health) health = recoverableHealth;
        }
        if (spiritCooldown > 0) {
            spiritCooldown -= 2;
            spirit = 0;
            if (spiritCooldown <= 0) {
                PlaySharedSound(47);
                spirit = 1000;
            }
        } else if (spirit < spiritPrevious) {
            spiritWait = 60;
        } else if (spiritWait > 0) {
            --spiritWait;
        } else {
            if ((!IsState150To199() ||
                (action != 209 && action != 210)) && spiritWait == 0)
                spirit += 3;
            if (spirit > 1000) spirit = 1000;
        }
        spiritPrevious = spirit;
    }
updateViewBounds:
    if (health < 0) health = 0;
    if (recoverableHealth < 0) recoverableHealth = 0;
    if (field47C > 0) --field47C;
    if (field484 > 0) --field484;
    if (fadeAlpha > 0) fadeAlpha -= 3;
    cameraState.field04 = (-g_CombatViewOffsetX - 320.0f + 640.0f) - (320.0f - g_CombatViewSpan) * 0.5f;
    field2DC = (-g_CombatViewOffsetX + 320.0f + 640.0f) + (320.0f - g_CombatViewSpan) * 0.5f;
    field2E0 = (g_CombatViewOffsetY - 300.0f + 420.0f) + (320.0f - g_CombatViewSpan) * 210.0f / 320.0f;
    field2E4 = (g_CombatViewOffsetY - 300.0f - 60.0f) - (320.0f - g_CombatViewSpan) * 30.0f / 320.0f;
    ++fieldEF8;
}
