#include "CharacterAI532950.hpp"

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(this) + offset))
#define FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(this) + offset)
#define OPPONENT(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float *>(reinterpret_cast<u8 *>(FIELD(void *, 0x2E8)) + offset)
#define OPPONENT_GUARD reinterpret_cast<FighterState *>(FIELD(void *, 0x2E8))->IsState50To149()
#define FORWARD_COMMAND (2 - (FIELD(signed char, 0x66) == 1))
#define AIR_FORWARD_COMMAND (2 - (FIELD(signed char, 0x66) == -1))
#define AIR_BACK_COMMAND (1 + (FIELD(signed char, 0x66) == -1))

// Source-defined local value; the original target declaration is unknown.
// Both observed floating components are used; this is not an owner layout.
struct AISeparation532950 { float x, y; };

void CharacterAI532950::ChooseAction()
{
    AISeparation532950 distance;
    distance.x = AbsFloatAt00412D90(OPPONENT_FLOAT(0x44) - FLOAT(0x44));
    distance.y = AbsFloatAt00412D90(OPPONENT_FLOAT(0x48) - FLOAT(0x48));
    --FIELD(short, 0x512);
    if (FIELD(short, 0x60) > 49 && FIELD(short, 0x60) < 150) {
        FIELD(short, 0x514) = 0;
        FIELD(short, 0x512) = 0;
    }
    if (FIELD(short, 0x514) == 1) {
        if (FIELD(short, 0x512) > 0) {
            FIELD(int, 0x4F0) = 5;
        } else {
            FIELD(short, 0x514) = 0;
        }
        return;
    }
    if (FIELD(short, 0x514) == 2) {
        if (FIELD(short, 0x60) == 391) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4EC) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 3) {
        if (FIELD(short, 0x60) == 390) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 4) {
        if (FIELD(short, 0x60) == 392) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FIELD(short, 0x514) == 5) {
        if (FIELD(short, 0x60) == 393) {
            FIELD(short, 0x514) = 0;
            return;
        }
        if (FIELD(short, 0x60) == 200) {
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) != 200) {
            FIELD(u8, 0x511) = FORWARD_COMMAND;
            return;
        }
    }
    if (FLOAT(0x36C) > 300.0f) {
        if (distance.x > 560.0f &&
            rand() < 3 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            FIELD(u8, 0x511) = 103;
            return;
        }
        if (OPPONENT(short, 0x60) == 98 &&
            rand() < 20 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            FIELD(u8, 0x511) = 103;
            return;
        }
    }
    if (FLOAT(0x36C) > 100.0f) {
        if (FIELD(short, 0x324) < 4000 &&
            distance.x > 560.0f &&
            rand() < 50 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            FIELD(u8, 0x511) = 103;
            return;
        }
        if (FIELD(short, 0x324) < 4000 &&
            rand() < 5 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            FIELD(u8, 0x511) = 103;
            return;
        }
        if (OPPONENT_GUARD &&
            FIELD(short, 0x324) < 3000 &&
            FIELD(u8, 0x39C) == 0 &&
            FIELD(short, 0x3A0) <= 0) {
            FIELD(u8, 0x511) = 103;
            return;
        }
    }
    if ((FIELD(short, 0x60) > 399 && FIELD(short, 0x60) < 500) ||
        (FIELD(short, 0x60) > 599 && FIELD(short, 0x60) < 700)) {
        if (distance.x > 0.0f) {
            if (FLOAT(0x48) == 0.0f) {
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = 3;
                    return;
                }
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = 4;
                    return;
                }
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = 5;
                    return;
                }
            }
            if (FLOAT(0x48) > 0.0f) {
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = AIR_BACK_COMMAND;
                    return;
                }
                if (rand() < 4000) {
                    FIELD(u8, 0x511) = AIR_FORWARD_COMMAND;
                    return;
                }
            }
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x < 300.0f &&
            rand() < 4000) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) > 399 &&
            FIELD(short, 0x60) < 500 &&
            distance.x > 400.0f &&
            distance.x < 500.0f &&
            rand() < 500) {
            FIELD(u8, 0x511) = 21;
            return;
        }
    }
    if (OPPONENT_GUARD && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if ((FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 503 || FIELD(short, 0x60) == 501 || (FIELD(short, 0x60) > 399 && FIELD(short, 0x60) < 500) || (FIELD(short, 0x60) > 599 && FIELD(short, 0x60) < 700)) &&
            rand() < 5000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 1 &&
            FIELD(signed char, 0x39D) == 1) {
            FIELD(u8, 0x511) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 503 || FIELD(short, 0x60) == 501 || (FIELD(short, 0x60) > 399 && FIELD(short, 0x60) < 500) || (FIELD(short, 0x60) > 599 && FIELD(short, 0x60) < 700)) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 1 &&
            FIELD(signed char, 0x39D) == 2) {
            FIELD(u8, 0x511) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 310 || FIELD(short, 0x60) == 500 || FIELD(short, 0x60) == 501 || FIELD(short, 0x60) == 503 || FIELD(short, 0x60) == 390) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 2 &&
            FIELD(signed char, 0x39D) == 1 &&
            FIELD(short, 0xF10) <= 0) {
            FIELD(u8, 0x511) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 310 || FIELD(short, 0x60) == 500 || FIELD(short, 0x60) == 501 || FIELD(short, 0x60) == 503 || FIELD(short, 0x60) == 390) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 2 &&
            FIELD(signed char, 0x39D) == 2 &&
            FIELD(short, 0xF10) <= 0) {
            FIELD(u8, 0x511) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 307 || FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 391 || FIELD(short, 0x60) == 308 || FIELD(short, 0x60) == 502) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 0 &&
            FIELD(signed char, 0x39D) == 1) {
            FIELD(u8, 0x511) = 13;
            return;
        }
        if ((FIELD(short, 0x60) == 301 || FIELD(short, 0x60) == 307 || FIELD(short, 0x60) == 309 || FIELD(short, 0x60) == 391 || FIELD(short, 0x60) == 308 || FIELD(short, 0x60) == 502) &&
            rand() < 10000 &&
            FIELD(short, 0x3A0) > 0 &&
            FLOAT(0x36C) >= 100.0f &&
            FIELD(short, 0x39A) == 0 &&
            FIELD(signed char, 0x39D) == 2) {
            FIELD(u8, 0x511) = 13;
            return;
        }
        if (FIELD(short, 0x60) == 502 &&
            rand() < 10000 &&
            distance.x < 150.0f) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) == 503 &&
            rand() < 10000) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 250) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 5000 &&
            distance.x < 120.0f &&
            FIELD(int, 0x7C) == 1) {
            FIELD(u8, 0x511) = 30;
            if (rand() < 18000) FIELD(u8, 0x511) = 31;
            return;
        }
        if (FIELD(short, 0x60) == 307 &&
            rand() < 2000) {
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x < 80.0f &&
            FIELD(short, 0x60) == 307 &&
            rand() < 2000) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 300 &&
            rand() < 10000 &&
            distance.x < 120.0f &&
            FIELD(int, 0x7C) == 1) {
            FIELD(u8, 0x511) = 30;
            if (rand() < 18000) FIELD(u8, 0x511) = 31;
            return;
        }
        if (FIELD(short, 0x60) == 300 &&
            rand() < 20000 &&
            distance.x < 80.0f) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 300 &&
            rand() < 2000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 15000) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 15000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 1500) {
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x < 150.0f &&
            FIELD(short, 0x60) == 301 &&
            rand() < 1500) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 3000 &&
            FIELD(short, 0x3B0) > 350) {
            FIELD(int, 0x4F0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 301 &&
            rand() < 8000) {
            FIELD(short, 0x514) = 2;
            return;
        }
        if (FIELD(short, 0x60) == 302 &&
            rand() < 5000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (FIELD(short, 0x60) == 303 &&
            rand() < 1500) {
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x > 150.0f &&
            FIELD(short, 0x60) == 303 &&
            rand() < 1500) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (FIELD(short, 0x60) == 303 &&
            rand() < 10000 &&
            distance.x < 80.0f) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (FIELD(short, 0x60) == 303 &&
            rand() < 5000 &&
            FIELD(int, 0x7C) == 1) {
            FIELD(u8, 0x511) = 30;
            if (rand() < 18000) FIELD(u8, 0x511) = 31;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 10000 &&
            FIELD(short, 0x3B0) > 250) {
            FIELD(u8, 0x511) = 20;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 5000 &&
            distance.x < 120.0f &&
            FIELD(int, 0x7C) == 1) {
            FIELD(u8, 0x511) = 30;
            if (rand() < 18000) FIELD(u8, 0x511) = 31;
            return;
        }
        if (FIELD(short, 0x60) == 308 &&
            rand() < 2500) {
            FIELD(u8, 0x511) = 100;
            return;
        }
        if (distance.x < 80.0f &&
            FIELD(short, 0x60) == 308 &&
            rand() < 2500) {
            FIELD(u8, 0x511) = 101;
            return;
        }
        if (distance.x < 60.0f &&
            rand() < 10000) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.8f + 0.0f &&
        distance.x > 200.0f &&
        FIELD(short, 0x3B0) > 350) {
        FIELD(int, 0x4F0) = 1;
        if (rand() < 2000) FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 2000) FIELD(int, 0x4E0) = 1;
        return;
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        FIELD(short, 0x3B0) > 750 &&
        FIELD(short, 0xF12) == 0) {
        FIELD(int, 0x4E8) = 1;
        if (rand() < 4000) FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 4000) FIELD(int, 0x4E0) = 1;
        return;
    }
    if (static_cast<float>(rand()) < FIELD(short, 0x3B0) * 0.5f + 0.0f &&
        distance.x > 560.0f &&
        FIELD(short, 0x3B0) > 750 &&
        FIELD(short, 0xF12) == 0) {
        FIELD(int, 0x4EC) = 1;
        if (rand() < 15000) FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        return;
    }
    if (rand() < 50) FIELD(int, 0x4E0) = -1;
    if (FLOAT(0x48) == 0.0f) {
        if (static_cast<float>(rand()) < distance.x / 2.0f + 100.0f) {
            FIELD(u8, 0x511) = 3;
            return;
        }
        if (static_cast<float>(rand()) < distance.x / 2.0f + 100.0f) {
            FIELD(u8, 0x511) = 4;
            return;
        }
        if (distance.x > 400.0f &&
            static_cast<float>(rand()) < 100.0f + distance.x) {
            FIELD(u8, 0x511) = 5;
            return;
        }
    }
    if (FLOAT(0x48) > 0.0f) {
        if (rand() < 1500) {
            FIELD(u8, 0x511) = AIR_BACK_COMMAND;
            return;
        }
        if (rand() < 100) {
            FIELD(u8, 0x511) = AIR_FORWARD_COMMAND;
            return;
        }
    }
    if (distance.x > 120.0f &&
        rand() < 200) {
        FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
        if (rand() < 18000) FIELD(int, 0x4DC) = 0;
        FIELD(int, 0x4E0) = -1;
        return;
    }
    if (distance.x > 150.0f &&
        FLOAT(0x48) > 0.0f &&
        rand() < 500) {
        FIELD(u8, 0x511) = FIELD(u8, 0x511) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x > 300.0f &&
        FLOAT(0x48) == 0.0f &&
        rand() < 2500) {
        FIELD(u8, 0x511) = FIELD(u8, 0x511) = AIR_BACK_COMMAND;
        return;
    }
    if (distance.x < 200.0f &&
        rand() < 100) {
        FIELD(u8, 0x511) = FIELD(u8, 0x511) = AIR_FORWARD_COMMAND;
        return;
    }
    if (FLOAT(0x48) == 0.0f && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if (distance.x < 70.0f &&
            rand() < 4000) {
            FIELD(int, 0x4E8) = 1;
            return;
        }
        if (distance.x < 120.0f &&
            rand() < 4000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 0;
            return;
        }
        if (distance.x < 170.0f &&
            rand() < 4000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 1;
            return;
        }
        if (distance.x < 80.0f &&
            distance.x > 0.0f &&
            OPPONENT_FLOAT(0x48) == 0.0f &&
            rand() < 2000) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (distance.x > 100.0f &&
            distance.x < 400.0f &&
            rand() < 100) {
            FIELD(int, 0x4E8) = 1;
            FIELD(int, 0x4DC) = FIELD(signed char, 0x66);
            return;
        }
        if (distance.x > 300.0f &&
            distance.x < 400.0f &&
            rand() < 1000) {
            FIELD(short, 0x514) = 3;
            return;
        }
        if (distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 2000) {
            FIELD(short, 0x514) = 2;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 200.0f &&
            distance.x < 400.0f &&
            rand() < 1000) {
            FIELD(short, 0x514) = 4;
            return;
        }
        if (OPPONENT_FLOAT(0x48) == 0.0f &&
            distance.x > 100.0f &&
            distance.x < 300.0f &&
            rand() < 500) {
            FIELD(short, 0x514) = 5;
            return;
        }
    }
    if (FLOAT(0x48) > 0.0f && (OPPONENT(short, 0x60) < 93 || OPPONENT(short, 0x60) > 99)) {
        if (distance.x < 150.0f) {
            if (rand() < (OPPONENT_FLOAT(0x48) > 0.0f ? 1 : 0) * 4000 + 4000 &&
                distance.y < 200.0f) {
                FIELD(int, 0x4E8) = 1;
                return;
            }
        }
        if (distance.x < 150.0f &&
            rand() < 6000 &&
            distance.y < 200.0f &&
            distance.y > 100.0f) {
            FIELD(int, 0x4EC) = 1;
            FIELD(int, 0x4E0) = 0;
            return;
        }
    }
    if (rand() < (OPPONENT(short, 0x60) == 98) * 2900 + 100 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 2 &&
        FIELD(signed char, 0x39D) == 1 &&
        FIELD(short, 0xF10) <= 0) {
        FIELD(u8, 0x511) = 13;
        return;
    }
    if (rand() < (distance.x < 500.0f ? 1 : 0) * 1000 + 500 + (OPPONENT_FLOAT(0x48) > 0.0f ? 1 : 0) * 3000 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 1 &&
        FIELD(signed char, 0x39D) == 1) {
        FIELD(u8, 0x511) = 13;
    }
    if (static_cast<float>(rand()) < 3000.0f - distance.x * 4.0f &&
        distance.x < 600.0f &&
        distance.y < 100.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 0 &&
        FIELD(signed char, 0x39D) == 1) {
        FIELD(u8, 0x511) = 13;
        return;
    }
    if (rand() < (OPPONENT(short, 0x60) == 98) * 2900 + 100 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 2 &&
        FIELD(signed char, 0x39D) == 2 &&
        FIELD(short, 0xF10) <= 0) {
        FIELD(u8, 0x511) = 13;
        return;
    }
    if (static_cast<float>(rand()) < 3000.0f - distance.x * 10.0f &&
        distance.x < 200.0f &&
        distance.y < 100.0f &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 0 &&
        FIELD(signed char, 0x39D) == 1) {
        FIELD(u8, 0x511) = 13;
        return;
    }
    if (rand() < (distance.x < 500.0f ? 1 : 0) * 1000 + 500 + (OPPONENT_FLOAT(0x48) > 0.0f ? 1 : 0) * 3000 &&
        FIELD(short, 0x3A0) > 0 &&
        FLOAT(0x36C) >= 100.0f &&
        FIELD(short, 0x39A) == 1 &&
        FIELD(signed char, 0x39D) == 2) {
        FIELD(u8, 0x511) = 13;
    }
    if (distance.y < 150.0f && distance.x < 110.0f) {
        if (rand() < (OPPONENT_FLOAT(0x48) > 0.0f ? 1 : 0) * 2500 + 500 &&
            OPPONENT(short, 0x60) != 93 &&
            OPPONENT(short, 0x60) != 94) {
            FIELD(u8, 0x511) = 30;
            return;
        }
    }
    if (OPPONENT_FLOAT(0x48) == 0.0f &&
        distance.x < 50.0f &&
        rand() < 500 &&
        !OPPONENT_GUARD) {
        FIELD(u8, 0x511) = 50;
        if (rand() < 18000) FIELD(u8, 0x511) = 51;
        return;
    }
    if (distance.x > 100.0f &&
        distance.x < 240.0f &&
        rand() < 200) {
        FIELD(u8, 0x511) = 100;
        return;
    }
    if (distance.x < 100.0f &&
        OPPONENT_FLOAT(0x48) == 0.0f &&
        rand() < 200) {
        FIELD(u8, 0x511) = 101;
        return;
    }
    if (distance.x > 250.0f &&
        distance.x < 350.0f &&
        rand() < 300) {
        FIELD(u8, 0x511) = 21;
        return;
    }
    if (distance.x < 200.0f &&
        distance.x > 100.0f &&
        rand() < 300) {
        FIELD(u8, 0x511) = 20;
        return;
    }
    if (distance.x > 300.0f &&
        static_cast<float>(rand()) < 200.0f + distance.x &&
        FIELD(short, 0x3B0) > 350) {
        FIELD(u8, 0x511) = 10;
        return;
    }
    if (distance.x > 300.0f &&
        static_cast<float>(rand()) < distance.x * 0.3f + 100.0f &&
        FIELD(short, 0x3B0) > 600) {
        FIELD(u8, 0x511) = 11;
        return;
    }
    if (countdown > 0) {
        FIELD(int, 0x4DC) = 1;
        --countdown;
    } else if (countdown < 0) {
        FIELD(int, 0x4DC) = -1;
        ++countdown;
    } else {
        countdown = (rand() % 90 + 10) * (1 - 2 * (rand() % 2));
    }
}
