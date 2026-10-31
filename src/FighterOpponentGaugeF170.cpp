#include "FighterGaugeBorrowedF980.hpp"
#include "FighterOpponentGaugeF170.hpp"
#include "BattleCombat.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this) + (offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OTHER(type, offset) (*reinterpret_cast<type*>(FIELD(unsigned char*, 0x2E8) + (offset)))

void FighterOpponentGaugeF170::ApplyOpponentGaugeChange(
    short base, short multiplier, short count)
{
    short change;
    if (OTHER(signed char, 0x2CD) != 0 && g_CombatMode == 3) {
        change = static_cast<short>(base * FLOAT(0x9C) * FLOAT(0xA4) *
            FLOAT(0xA0) * FLOAT(0x3C0) *
            (OTHER(short, 0x328) / 4.0f /
             reinterpret_cast<const short*>(FIELD(unsigned char*, 0x2E8) + 0x33E)
                 [OTHER(signed char, 0x39D)] + 0.75));
    } else {
        change = static_cast<short>(base * FLOAT(0x9C) * FLOAT(0xA4) *
            FLOAT(0xA0) * FLOAT(0x3C0) *
            (OTHER(short, 0x328) / 4.0f / 10000.0f + 0.75));
    }
    if (OTHER(short, 0x60) < 50 || OTHER(short, 0x60) >= 143) {
        FIELD(short, 0x3C4) = 0;
        FIELD(short, 0x3C6) = 0;
        FLOAT(0x3C0) = 1.0f;
    }
    FIELD(short, 0x3C6) += change;
    OTHER(short, 0x324) -= change;
    if (OTHER(short, 0x324) <= 0)
        OTHER(short, 0x324) = 0;
    if (OTHER(short, 0x3A0) > 0) {
        OTHER(short, 0x326) -= change;
    } else {
        OTHER(short, 0x326) -= change * (0.75 - F980_GAUGE(FIELD(unsigned char*, 0x2E8)).meterAt3B0 * 0.25 / 1000.0);
    }
    if (OTHER(short, 0x3A0) > 0 || OTHER(unsigned char, 0x39C) != 0)
        OTHER(short, 0x326) = OTHER(short, 0x324);
    FIELD(short, 0x3C4) += count;
    FLOAT(0x3C0) = (multiplier / 100.0f) * FLOAT(0x3C0);
}

#undef OTHER
#undef FLOAT
#undef FIELD
