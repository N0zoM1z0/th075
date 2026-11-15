#include "FighterVitalBorrowedF999.hpp"
#include "FighterGaugeBorrowedF980.hpp"
#include "FighterOpponentGaugeF170.hpp"
#include "BattleCombat.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))

void Fighter::ApplyOpponentGaugeChange(
    short base, short multiplier, short count)
{
    short change;
    if (opponent->field2CD != 0 && g_CombatMode == 3) {
        change = static_cast<short>(base * field09C * field0A4 *
            field0A0 * field3C0 *
            (opponent->field328 / 4.0f /
             reinterpret_cast<const short*>(reinterpret_cast<unsigned char*&>(opponent) + 0x33E)
                 [opponent->field39D] + 0.75));
    } else {
        change = static_cast<short>(base * field09C * field0A4 *
            field0A0 * field3C0 *
            (opponent->field328 / 4.0f / 10000.0f + 0.75));
    }
    if (opponent->action < 50 || opponent->action >= 143) {
        comboCount = 0;
        comboDamage = 0;
        field3C0 = 1.0f;
    }
    comboDamage += change;
    F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).currentAt324 -= change;
    if (F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).currentAt324 <= 0)
        F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).currentAt324 = 0;
    if (opponent->field3A0 > 0) {
        F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).recoverableAt326 -= change;
    } else {
        F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).recoverableAt326 -= change * (0.75 - F980_GAUGE(reinterpret_cast<unsigned char*&>(opponent)).meterAt3B0 * 0.25 / 1000.0);
    }
    if (opponent->field3A0 > 0 || opponent->field39C != 0)
        F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).recoverableAt326 = F999_VITAL(reinterpret_cast<unsigned char*&>(opponent)).currentAt324;
    comboCount += count;
    field3C0 = (multiplier / 100.0f) * field3C0;
}

#undef FIELD
