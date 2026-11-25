#include "engine/GameSharedState.hpp"
#include "battle/FighterOpponentGaugeF170.hpp"

void Fighter::ApplyOpponentGaugeChange(
    short base, short multiplier, short count)
{
    short change;
    if (opponent->field2CD != 0 && g_CombatMode == 3) {
        change = static_cast<short>(base * field09C * field0A4 *
            field0A0 * comboRate *
            (opponent->healthBeforeCollision / 4.0f /
             opponent->healthLimits[opponent->field39D] + 0.75));
    } else {
        change = static_cast<short>(base * field09C * field0A4 *
            field0A0 * comboRate *
            (opponent->healthBeforeCollision / 4.0f / 10000.0f + 0.75));
    }
    if (opponent->action < 50 || opponent->action >= 143) {
        comboCount = 0;
        comboDamage = 0;
        comboRate = 1.0f;
    }
    comboDamage += change;
    opponent->health -= change;
    if (opponent->health <= 0)
        opponent->health = 0;
    if (opponent->spellTimer > 0) {
        opponent->recoverableHealth -= change;
    } else {
        opponent->recoverableHealth -= change * (0.75 - opponent->spirit * 0.25 / 1000.0);
    }
    if (opponent->spellTimer > 0 || opponent->spellDeclarationExpired != 0)
        opponent->recoverableHealth = opponent->health;
    comboCount += count;
    comboRate = (multiplier / 100.0f) * comboRate;
}
