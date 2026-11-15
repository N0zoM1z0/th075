#include "FighterOpponentGaugeF170.hpp"
extern signed char g_CombatMode;

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void Fighter::ApplyOpponentGaugeChange(
    short base, short multiplier, short count)
{
    short change;
    if (opponent->field2CD != 0 && g_CombatMode == 3) {
        change = static_cast<short>(base * field09C * field0A4 *
            field0A0 * comboRate *
            (opponent->field328 / 4.0f /
             reinterpret_cast<const short*>(reinterpret_cast<unsigned char*&>(opponent) + 0x33E)
                 [opponent->field39D] + 0.75));
    } else {
        change = static_cast<short>(base * field09C * field0A4 *
            field0A0 * comboRate *
            (opponent->field328 / 4.0f / 10000.0f + 0.75));
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
    if (opponent->field3A0 > 0) {
        opponent->recoverableHealth -= change;
    } else {
        opponent->recoverableHealth -= change * (0.75 - opponent->spirit * 0.25 / 1000.0);
    }
    if (opponent->field3A0 > 0 || opponent->field39C != 0)
        opponent->recoverableHealth = opponent->health;
    comboCount += count;
    comboRate = (multiplier / 100.0f) * comboRate;
}

#undef FIELD
